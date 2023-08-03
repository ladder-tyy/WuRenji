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

double rollKp = 0.05;
double rollKi = 0.01;
double rollKd = 0.05;
double prevRollError = 0.0;
double integralRoll = 0.0;

double pitchKp = 0.05;
double pitchKi = 0.01;
double pitchKd = 0.05;
double prevPitchError = 0.0;
double integralPitch = 0.0;

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

void fan1Control(void *pvParameters){
    while(1){
       ledcWrite(fan1Channel,255);
    }
    delay(10);
}

void fan2Control(void *pvParameters){
    while(1){
        
    }
    delay(10);    
}

void fan3Control(void *pvParameters){
    while(1){
               
    }  
    delay(10);   
}

void fan4Control(void *pvParameters){
    while(1){
    
    } 
    delay(10);    
}

void fanControl(void *pvParameters){
    while(1){
        motorPower1 = dataDealPWM(targetPower + rollPID(targetRoll,agx) - pitchPID(targetPitch,agy) ,0,300);
        motorPower2 = dataDealPWM(targetPower + rollPID(targetRoll,agx) + pitchPID(targetPitch,agy) ,0,300);
        motorPower3 = dataDealPWM(targetPower - rollPID(targetRoll,agx) + pitchPID(targetPitch,agy) ,0,300);
        motorPower4 = dataDealPWM(targetPower - rollPID(targetRoll,agx) - pitchPID(targetPitch,agy) ,0,300);

        // ledcWrite(fan1Channel,motorPower1);
        // ledcWrite(fan2Channel,motorPower2);
        // ledcWrite(fan3Channel,motorPower3);
        // ledcWrite(fan4Channel,motorPower4);

        Serial.print("");Serial.print(motorPower1);
        Serial.print("| ");Serial.print(motorPower2);
        Serial.print("| ");Serial.print(motorPower3);
        Serial.print("| ");Serial.println(motorPower4);

        // Serial.print("target(Roll, Pitch): ");Serial.print(targetRoll);Serial.print(", ");Serial.print(targetPitch);
        // Serial.print(" | target (Yaw, Power): ");Serial.print(targetYaw);Serial.print(", ");Serial.println(targetPower);

        // Serial.print(agx);Serial.print(",");
        // Serial.print(agy);Serial.print(",");
        // Serial.print(agz);Serial.println();

        // motorPower1 = rollPID(targetRoll,currentRoll);
        // motorPower2 = pitchPID(100,motorPower2);
        // Serial.print("roll PID : ");Serial.println(motorPower1);
        // Serial.print(" | pitch PID: ");Serial.println(motorPower2);



    } 
    delay(10);    
}

int rollPID(int target, int current){
    double rollError = (double)target - (double)current;

    double KP = rollError * rollKp;

    integralRoll += rollError * rollKi;
    if (integralRoll > target) {integralRoll = target;}
    else if (integralRoll < -target) {integralRoll = -target;}

    double KD = (rollError - prevRollError) * rollKd;

    prevRollError = rollError;

    double rollOutput = KP + integralRoll + KD;

    // Serial.print("rollOutput : ");Serial.println(integralRoll);

    return (int)rollOutput;
}

int pitchPID(int target, int current){
    double pitchError = (double)target - (double)current;

    double KP = pitchError * pitchKp;

    integralPitch += pitchError * pitchKi;
    if (integralPitch > 250) {integralPitch = 250;}
    else if (integralPitch < -250) {integralPitch = -250;}

    double KD = (pitchError - prevPitchError) * pitchKd;

    prevPitchError = pitchError;

    double pitchOutput = KP + integralPitch + KD;

    // Serial.print("pitchOutput : ");Serial.println(integralPitch);

    return (int)pitchOutput;
}

