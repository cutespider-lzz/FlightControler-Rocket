#ifndef __TASKINIT_H
#define __TASKINIT_H

#include "main.h"
#include "cmsis_os.h"
#include "fatfs.h"
#include "tf.h"
#include "receiver.h"
#include "navigation.h"
#include "control.h"
#include "telemetry.h"
#include "extf.h"

//任务初始化
void TaskInit(void);

//LEDTwinkTask函数声明
extern BaseType_t LEDTwinkTask_Ret;
extern UBaseType_t LEDTwinkTask_Prio;
extern TaskHandle_t LEDTwinkTask_TCB;

void LEDTwinkTask(void *pvParameters);

//ReceiverTask函数声明
extern BaseType_t ReceiverTask_Ret;
extern UBaseType_t ReceiverTask_Prio;
extern TaskHandle_t ReceiverTask_TCB;

void ReceiverTask(void *pvParameters);

//NavigationTask函数声明
extern BaseType_t NavigationTask_Ret;
extern UBaseType_t NavigationTask_Prio;
extern TaskHandle_t NavigationTask_TCB;

void NavigationTask(void *pvParameters);

//ControlTask函数声明
extern BaseType_t ControlTask_Ret;
extern UBaseType_t ControlTask_Prio;
extern TaskHandle_t ControlTask_TCB;

void ControlTask(void *pvParameters);

//TFStorageTask函数声明
extern BaseType_t TFStorageTask_Ret;
extern UBaseType_t TFStorageTask_Prio;
extern TaskHandle_t TFStorageTask_TCB;

void TFStorageTask(void *pvParameters);

//TelemetrySendTask函数声明
extern BaseType_t TelemetrySendTask_Ret;
extern UBaseType_t TelemetrySendTask_Prio;
extern TaskHandle_t TelemetrySendTask_TCB;

void TelemetrySendTask(void *pvParameters);

//ExtfSendTask函数声明
extern BaseType_t ExtfSendTask_Ret;
extern UBaseType_t ExtfSendTask_Prio;
extern TaskHandle_t ExtfSendTask_TCB;

void ExtfSendTask(void *pvParameters);

#endif
