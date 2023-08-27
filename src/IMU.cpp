#include "IMU.h"

MPU6050 mpu;

unsigned long lastTime, now;

int16_t ax, ay, az, gx, gy, gz;

float aax=0, aay=0, aaz=0;                                  //加速度变量
float agx=0, agy=0, agz=0;                                  //角度变量

long ax0 = 0, ay0 = 0, az0 = 0;                             //加速度计偏移量
long gx0 = 0, gy0 = 0, gz0 = 0;                             //陀螺仪偏移量
 
float AcceRatio = 16384.0;                                  //加速度计比例系数
float GyroRatio = 131.0;                                    //陀螺仪比例系数
float RadinToAngle = 180.0 / 3.1415926;

uint8_t n_sample = 8;                                       //加速度计滤波算法采样个数
float aaxs[8] = {0}, aays[8] = {0}, aazs[8] = {0};          //x,y轴采样队列
long aax_sum, aay_sum,aaz_sum;                              //x,y轴采样和
 
float a_x[10]={0}, a_y[10]={0}, a_z[10]={0};
float g_x[10]={0} ,g_y[10]={0}, g_z[10]={0};                //加速度计协方差计算队列
float Px=1, Rx, Kx, Sx, Vx, Qx;                             //x轴卡尔曼变量
float Py=1, Ry, Ky, Sy, Vy, Qy;                             //y轴卡尔曼变量
float Pz=1, Rz, Kz, Sz, Vz, Qz;                             //z轴卡尔曼变量

float currentRoll, currentPitch, currentYaw;                //当前姿态角度

boolean imuDataInitTrue = false;                            //IMU数据初始化

void imuInit(void){
    while (!Serial)
    delay(10); // Wait for serial monitor to open
    Wire.begin();

    // Initialize the MPU6050
    mpu.initialize();
    mpu.testConnection();
    imuDataInit();
}

void imuDeal(void *pvParameters){
    while(1){
        if(startOpen == true && imuDataInitTrue == false){
            imuDataInit();
            imuDataInitTrue = true;
        }
        else if(startOpen == false){
            imuDataInitTrue = false;
        }
        now = millis();                                 //当前时间(ms)
        float dt = (now - lastTime) / 1000.0;           //微分时间(s)
        lastTime = now;                                 //上一次采样时间(ms)
    
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
        float accx = ax / AcceRatio;                    //x轴加速度
        float accy = ay / AcceRatio;                    //y轴加速度
        float accz = az / AcceRatio;                    //z轴加速度
        
        aax = atan(accy / accz) * (-RadinToAngle);      //y轴对于z轴的夹角
        aay = atan(accx / accz) * RadinToAngle;         //x轴对于z轴的夹角
        aaz = atan(accz / accy) * RadinToAngle;         //z轴对于y轴的夹角

        aax_sum = 0;                                    // 对于加速度计原始数据的滑动加权滤波算法
        aay_sum = 0;
        aaz_sum = 0;
    
        for(int i=1;i<n_sample;i++){
            aaxs[i-1] = aaxs[i];
            aax_sum += aaxs[i] * i;
            aays[i-1] = aays[i];
            aay_sum += aays[i] * i;
            aazs[i-1] = aazs[i];
            aaz_sum += aazs[i] * i;
        }
        
        aaxs[n_sample-1] = aax;
        aax_sum += aax * n_sample;
        aax = (aax_sum / (11*n_sample/2.0)) * 9 / 7.0; //角度调幅至0-90°
        aays[n_sample-1] = aay;                        //此处应用实验法取得合适的系数
        aay_sum += aay * n_sample;                     //本例系数为9/7
        aay = (aay_sum / (11*n_sample/2.0)) * 9 / 7.0;
        aazs[n_sample-1] = aaz; 
        aaz_sum += aaz * n_sample;
        aaz = (aaz_sum / (11*n_sample/2.0)) * 9 / 7.0;
    
        float gyrox = - (gx-gx0) / GyroRatio * dt;  //x轴角速度
        float gyroy = - (gy-gy0) / GyroRatio * dt;  //y轴角速度
        float gyroz = - (gz-gz0) / GyroRatio * dt;  //z轴角速度

        agx += gyrox;                               //x轴角速度积分
        agy += gyroy;                               //y轴角速度积分
        agz += gyroz - 0.00000017;

        /* kalman start */
        Sx = 0; Rx = 0;
        Sy = 0; Ry = 0;
        Sz = 0; Rz = 0;
        
        for(int i=1;i<10;i++){                      //测量值平均值运算
            a_x[i-1] = a_x[i];                      //即加速度平均值
            Sx += a_x[i];
            a_y[i-1] = a_y[i];
            Sy += a_y[i];
            a_z[i-1] = a_z[i];
            Sz += a_z[i];
        }
        
        a_x[9] = aax;
        Sx += aax;
        Sx /= 10;                                 //x轴加速度平均值
        a_y[9] = aay;
        Sy += aay;
        Sy /= 10;                                 //y轴加速度平均值
        a_z[9] = aaz;
        Sz += aaz;
        Sz /= 10;
    
        for(int i=0;i<10;i++){
            Rx += sq(a_x[i] - Sx);
            Ry += sq(a_y[i] - Sy);
            Rz += sq(a_z[i] - Sz);
        }
        
        Rx = Rx / 9;                              //得到方差
        Ry = Ry / 9;                        
        Rz = Rz / 9;
    
        Px = Px + 0.0025;                         // 0.0025在下面有说明...
        Kx = Px / (Px + Rx);                      //计算卡尔曼增益
        agx = agx + Kx * (aax - agx);             //陀螺仪角度与加速度计速度叠加
        Px = (1 - Kx) * Px;                       //更新p值
    
        Py = Py + 0.0025;
        Ky = Py / (Py + Ry);
        agy = agy + Ky * (aay - agy); 
        Py = (1 - Ky) * Py;
    
        // Pz = Pz + 0.0025;
        // Kz = Pz / (Pz + Rz);
        // agz = agz + Kz * (aaz - agz); 
        // Pz = (1 - Kz) * Pz;
    
        if(agx > 180){agx -= 180;}
        else if(agx < -180){agx += 180;}

        if(agy > 180){agy -= 180;}
        else if(agy < -180){agy += 180;}

        if(agz > 180){agz -= 180;}
        else if(agz < -180){agz += 180;}

        /* kalman end */

        currentRoll     = agx - 0.8;
        currentPitch    = agy - 2.5;
        currentYaw      = agz;

        // Serial.print((int)currentRoll);Serial.print(",");
        // Serial.print((int)currentPitch);Serial.print(",");
        // Serial.print((int)currentYaw);Serial.println();

        
    }
    delay(5);
}

void imuDataInit(void){
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 

    unsigned short times = 200;             //采样次数
    for(int i=0;i<times;i++)
    {
        ax0 += ax; ay0 += ay; az0 += az;
        gx0 += gx; gy0 += gy; gz0 += gz;
    }
    ax0 /= times; ay0 /= times; az0 /= times; //计算加速度计偏移
    gx0 /= times; gy0 /= times; gz0 /= times; //计算陀螺仪偏移
}