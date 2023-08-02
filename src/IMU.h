#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#ifndef __IMU_H__
#define __IMU_H__

#define IMU_SCL 22
#define IMU_SDA 21

void imuInit(void);
void imuDeal(void *pvParameters);

#endif
