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

void rollPID(void *pvParameters){
    while(1){
        
    }
    delay(10); 
}

void pitchPID(void *pvParameters){
    while(1){
       
    }
    delay(10);
}