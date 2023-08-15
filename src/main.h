#include <Arduino.h>
#include <RTOS.h>
#include "IMU.h"
#include "PS2.h"
#include "PWM.h"

#ifndef __MAIN_H__
#define __MAIN_H__

// 电机1
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄

// 电机2
#define TASK2_TASK_PRIO  1      // 任务优先级
#define TASK2_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks2_TaskHandle; // 任务句柄

// 电机3
#define TASK3_TASK_PRIO  1      // 任务优先级
#define TASK3_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks3_TaskHandle; // 任务句柄

// 电机4
#define TASK4_TASK_PRIO  1      // 任务优先级
#define TASK4_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks4_TaskHandle; // 任务句柄

// PS2
#define TASK5_TASK_PRIO  1      // 任务优先级
#define TASK5_STK_SIZE   2048   // 任务堆栈大小
TaskHandle_t Tasks5_TaskHandle; // 任务句柄

// MPU6050
#define TASK6_TASK_PRIO  1      // 任务优先级
#define TASK6_STK_SIZE   2048   // 任务堆栈大小
TaskHandle_t Tasks6_TaskHandle; // 任务句柄

// 4个fan
#define TASK7_TASK_PRIO  1      // 任务优先级
#define TASK7_STK_SIZE   2048   // 任务堆栈大小
TaskHandle_t Tasks7_TaskHandle; // 任务句柄


void taskInit(){
    // xTaskCreate(fan1Control,    "task1_task",TASK1_STK_SIZE,NULL,TASK1_TASK_PRIO,NULL);
    // xTaskCreate(fan2Control,    "task2_task",TASK2_STK_SIZE,NULL,TASK2_TASK_PRIO,NULL);
    // xTaskCreate(fan3Control,    "task3_task",TASK3_STK_SIZE,NULL,TASK3_TASK_PRIO,NULL);
    // xTaskCreate(fan4Control,    "task4_task",TASK4_STK_SIZE,NULL,TASK4_TASK_PRIO,NULL);
    // xTaskCreate(ps2Deal,        "task5_task",TASK5_STK_SIZE,NULL,TASK5_TASK_PRIO,NULL);
    xTaskCreate(imuDeal,        "task6_task",TASK6_STK_SIZE,NULL,TASK6_TASK_PRIO,NULL);
    xTaskCreate(fanControl,     "task7_task",TASK7_STK_SIZE,NULL,TASK7_TASK_PRIO,NULL);

}


#endif
