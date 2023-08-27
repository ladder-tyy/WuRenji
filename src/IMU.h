#include <Wire.h>
#include <MPU6050.h>
#include <PS2.h>

#ifndef __IMU_H__
#define __IMU_H__

#define IMU_SCL 22
#define IMU_SDA 21

extern float currentRoll, currentPitch, currentYaw;

void imuInit(void);
void imuDeal(void *pvParameters);
void imuDataInit(void);

#endif
