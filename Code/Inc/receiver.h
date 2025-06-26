#ifndef __RECEIVER_H
#define __RECEIVER_H

#include "main.h"
#include "cmsis_os.h"

#define SIYI_Enable 1

#define ReceiverChannelMin 256
#define ReceiverChannelMax 1729

typedef enum
{
	Receiver_ERR,
	Receiver_OK,
	Receiver_NOSignal
}ReceiverStatus;

extern uint8_t ReceiverReceiveBuff[];//Receiver接收缓存数组
extern uint8_t ReceiverFifoBuff[];//Receiver数据处理数组，缓存数组接收数据后保存至处理数组中

extern uint16_t ReceiverChannel[];//Receiver接收通道数据
extern uint16_t ReceiverChannelNeutral[];//接收机通道中立位置

extern SemaphoreHandle_t ReceiverSemaphore;//Receiver二值信号量
extern BaseType_t ReceiverHigherTaskSwitch;

extern ReceiverStatus ReceiverRet;//接收机接收数据状态变量

ReceiverStatus ReceiverDataConvert(uint8_t *ReceiverBuff);//接收机通道转换函数
void ReceiverSolution(void);//接收机通道状态切换函数

#endif
