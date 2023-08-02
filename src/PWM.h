#include "IMU.h"
#include "PS2.h"

#ifndef __PWM_H__
#define __PWM_H__

//可用参数
//IMU: agx, agy, ayz(no);
//PS2: joyLX, joyLY, joyRX, joyRY;

#define FAN1PIN    32
#define FAN2PIN    33
#define FAN3PIN    26
#define FAN4PIN    25
#define LIGHT      12

void pwmInit(void);

void fan1Control(void *pvParameters);
void fan2Control(void *pvParameters);
void fan3Control(void *pvParameters);
void fan4Control(void *pvParameters);

void rollPID(void *pvParameters);
void pitchPID(void *pvParameters);

#endif
