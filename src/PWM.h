#include <IMU.h>

#ifndef __PWM_H__
#define __PWM_H__

void pwmInit(void);

void fan1Control(void *pvParameters);
void fan2Control(void *pvParameters);
void fan3Control(void *pvParameters);
void fan4Control(void *pvParameters);

void rollPID(void *pvParameters);
void pitchPID(void *pvParameters);

#endif
