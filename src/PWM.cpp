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

int motorPower1; // Motor 1 power (0 to 255)
int motorPower2; // Motor 2 power (0 to 255)
int motorPower3; // Motor 3 power (0 to 255)
int motorPower4; // Motor 4 power (0 to 255)

float currentRoll  = agx;
float currentPitch = agy;
float currentYaw   = agz;

double Kp_roll = 2.0;
double Ki_roll = 0.1;
double Kd_roll = 1.0;

double Kp_pitch = 2.0;
double Ki_pitch = 0.1;
double Kd_pitch = 1.0;

double prevPitchError = 0.0;
double integralPitch = 0.0;
double prevRollError = 0.0;
double integralRoll = 0.0;

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
        motorPower1 = dataDealPWM(targetPower + (int)rollPID + (int)pitchPID ,0,300);
        motorPower2 = dataDealPWM(targetPower + (int)rollPID - (int)pitchPID ,0,300);
        motorPower3 = dataDealPWM(targetPower - (int)rollPID - (int)pitchPID ,0,300);
        motorPower4 = dataDealPWM(targetPower - (int)rollPID + (int)pitchPID ,0,300);

        ledcWrite(fan1Channel,motorPower1);
        ledcWrite(fan2Channel,motorPower2);
        ledcWrite(fan3Channel,motorPower3);
        ledcWrite(fan4Channel,motorPower4);

        // Serial.print("");Serial.print(motorPower1);
        // Serial.print("| ");Serial.print(motorPower2);
        // Serial.print("| ");Serial.print(motorPower3);
        // Serial.print("| ");Serial.println(motorPower4);

        Serial.print("target(Roll, Pitch): ");Serial.print(targetRoll);Serial.print(", ");Serial.print(targetPitch);
        Serial.print(" | target (Yaw, Power): ");Serial.print(targetYaw);Serial.print(", ");Serial.println(targetPower);

        // Serial.print(agx);Serial.print(",");
        // Serial.print(agy);Serial.print(",");
        // Serial.print(agz);Serial.println();

    } 
    delay(10);    
}

double rollPID(void){
    double rollError = targetRoll - currentRoll;
    double rollOutput = Kp_roll * rollError + Ki_roll * integralRoll + Kd_roll * (rollError - prevRollError);
    prevRollError = rollError;
    integralRoll += rollError;
    return rollOutput;
}

double pitchPID(void){
    double pitchError = targetPitch - currentPitch;
    double pitchOutput = Kp_pitch * pitchError + Ki_pitch * integralPitch + Kd_pitch * (pitchError - prevPitchError);
    prevPitchError = pitchError;
    integralPitch += pitchError;
    return pitchOutput; 
}

