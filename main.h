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
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
// PS2
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
// MPU6050
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
// roll轴PID
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
// pitch轴PID
#define TASK1_TASK_PRIO  1      // 任务优先级
#define TASK1_STK_SIZE   1024   // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄

void taskInit(){
    xTaskCreate(task1, "task1_task",TASK1_STK_SIZE,NULL,TASK1_TASK_PRIO,NULL);
    
}


#endif
