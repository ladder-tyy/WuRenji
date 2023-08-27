#include "PWM.h"

const int fan1Freq = 1000;     //设置频率
const int fan1Channel = 1;     //通道号，取值0 ~ 15
const int fan1Resolution = 8;  //计数位数，取值0 ~ 20

const int fan2Freq = 1000;     //设置频率
const int fan2Channel = 1;     //通道号，取值0 ~ 15
const int fan2Resolution = 8;  //计数位数，取值0 ~ 20

const int fan3Freq = 1000;     //设置频率
const int fan3Channel = 1;     //通道号，取值0 ~ 15
const int fan3Resolution = 8;  //计数位数，取值0 ~ 20

const int fan4Freq = 1000;     //设置频率
const int fan4Channel = 1;     //通道号，取值0 ~ 15
const int fan4Resolution = 8;  //计数位数，取值0 ~ 20

int motorPower1 = 0; // Motor 1 power (0 to 255)
int motorPower2 = 0; // Motor 2 power (0 to 255)
int motorPower3 = 0; // Motor 3 power (0 to 255)
int motorPower4 = 0; // Motor 4 power (0 to 255)

double rollKp = 0.5;
double rollKi = 0.01;
double prevRollError = 0.0;
double integralRoll = 0.0;

double pitchKp = 0.5;
double pitchKi = 0.01;
double prevPitchError = 0.0;
double integralPitch = 0.0;

double yawKp = 0.5;
double yawKi = 0.01;
double prevYawError = 0.0;
double integralYaw = 0.0;

int HIGH_SPEED = SPEED + 0.2 * SPEED;
int LOW_SPEED = 0;

int dataDealPWM(int amt, int low, int high){
    int outPut = ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
    return outPut;
}

void pwmInit(void){
    ledcSetup(fan1Channel, fan1Freq, fan1Resolution);
    ledcSetup(fan2Channel, fan2Freq, fan2Resolution);
    ledcSetup(fan3Channel, fan3Freq, fan3Resolution);
    ledcSetup(fan4Channel, fan4Freq, fan4Resolution);
    ledcAttachPin(FAN1PIN, fan1Channel);
    ledcAttachPin(FAN2PIN, fan2Channel);
    ledcAttachPin(FAN3PIN, fan3Channel);
    ledcAttachPin(FAN4PIN, fan4Channel);
}

void fanControl(void *pvParameters){
    while(1){
        //print "1|2|3|4

        //all
        motorPower1 = dataDealPWM(targetPower + rollPID(targetRoll,currentRoll) - pitchPID(targetPitch,currentPitch) - yawPID(targetYaw,currentYaw) ,LOW_SPEED, HIGH_SPEED);
        motorPower2 = dataDealPWM(targetPower + rollPID(targetRoll,currentRoll) + pitchPID(targetPitch,currentPitch) - yawPID(targetYaw,currentYaw) ,LOW_SPEED, HIGH_SPEED);
        motorPower3 = dataDealPWM(targetPower - rollPID(targetRoll,currentRoll) + pitchPID(targetPitch,currentPitch) + yawPID(targetYaw,currentYaw) ,LOW_SPEED, HIGH_SPEED);
        motorPower4 = dataDealPWM(targetPower - rollPID(targetRoll,currentRoll) - pitchPID(targetPitch,currentPitch) + yawPID(targetYaw,currentYaw) ,LOW_SPEED, HIGH_SPEED);

        if(startOpen == true){
            ledcWrite(fan1Channel, motorPower1);
            ledcWrite(fan2Channel, motorPower2);
            ledcWrite(fan3Channel, motorPower3);
            ledcWrite(fan4Channel, motorPower4);
        }
        else{ // all data clean
            motorPower1 = 0;
            motorPower2 = 0;
            motorPower3 = 0;
            motorPower4 = 0;

            prevPitchError = 0;
            integralPitch = 0;
            
            prevRollError = 0;
            integralRoll = 0;

            ledcWrite(fan1Channel, 0);
            ledcWrite(fan2Channel, 0);
            ledcWrite(fan3Channel, 0);
            ledcWrite(fan4Channel, 0);
        }

        Serial.print("");Serial.print(motorPower1);
        Serial.print("| ");Serial.print(motorPower2);
        Serial.print("| ");Serial.print(motorPower3);
        Serial.print("| ");Serial.print(motorPower4);
        Serial.print("| StartOpen :");Serial.println(startOpen);

        // Serial.print("target(Roll, Pitch): ");Serial.print(targetRoll);Serial.print(", ");Serial.print(targetPitch);
        // Serial.print(" | target (Yaw, Power): ");Serial.print(targetYaw);Serial.print(", ");Serial.println(targetPower);

        // Serial.print((int)currentRoll);Serial.print(",");
        // Serial.print((int)currentPitch);Serial.print(",");
        // Serial.print((int)currentYaw);Serial.println();

        // motorPower1 = rollPID(targetRoll,currentRoll);
        // motorPower2 = pitchPID(100,motorPower2);
        // Serial.print("roll PID : ");Serial.println(motorPower1);
        // Serial.print(" | pitch PID: ");Serial.println(motorPower2);

    } 
    delay(5);    
}

int rollPID(int target, int current){
   double Error = (double)target - (double)current;

    double KP = Error * rollKp;

    integralRoll += Error * rollKi;
    if (integralRoll > 250) {integralRoll = 250;}
    else if (integralRoll < -250) {integralRoll = -250;}

    prevRollError = Error;

    double rollOutput = KP + integralRoll ;

    return (int)rollOutput;
}

int pitchPID(int target, int current){
    double Error = (double)target - (double)current;

    double KP = Error * pitchKp;

    integralPitch += Error * pitchKi;
    if (integralPitch > 250) {integralPitch = 250;}           //积分限幅
    else if (integralPitch < -250) {integralPitch = -250;}

    prevPitchError = Error;

    double pitchOutput = KP + integralPitch ;

    return (int)pitchOutput;
}

int yawPID(int target, int current){
    double Error = (double)target - (double)current;

    double KP = Error * yawKp;

    integralYaw += Error * yawKi;         
    if (integralYaw > 250) {integralYaw = 250;}           //积分限幅
    else if (integralYaw < -250) {integralYaw = -250;}

    prevYawError = Error;

    double yawOutput = KP + integralYaw ;

    return (int)yawOutput;
}