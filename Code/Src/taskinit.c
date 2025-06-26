#include "taskinit.h"
#include "cmsis_os.h"
#include "stdio.h"

void TaskInit(void)
{
	//Create LEDTwinkTask
	LEDTwinkTask_Ret = xTaskCreate((TaskFunction_t)LEDTwinkTask,"LEDTwinkTask",32,(void *)1,LEDTwinkTask_Prio,(TaskHandle_t *)(&LEDTwinkTask_TCB));
	if(LEDTwinkTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
//	//Create ReceiverTask
//	ReceiverTask_Ret = xTaskCreate((TaskFunction_t)ReceiverTask,"ReceiverTask",256,(void *)1,ReceiverTask_Prio,(TaskHandle_t *)(&ReceiverTask_TCB));
//	if(ReceiverTask_Ret == pdPASS) ;
//	else
//	{
//		while(1) ;
//	}
	//Create NavigationTask
	NavigationTask_Ret = xTaskCreate((TaskFunction_t)NavigationTask,"NavigationTask",512,(void *)1,NavigationTask_Prio,(TaskHandle_t *)(&NavigationTask_TCB));
	if(NavigationTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	//Create ControlTask
	ControlTask_Ret = xTaskCreate((TaskFunction_t)ControlTask,"ControlTask",512,(void *)1,ControlTask_Prio,(TaskHandle_t *)(&ControlTask_TCB));
	if(ControlTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	//Create TFStorageTask
	TFStorageTask_Ret = xTaskCreate((TaskFunction_t)TFStorageTask,"TFStorageTask",256,(void *)1,TFStorageTask_Prio,(TaskHandle_t *)(&TFStorageTask_TCB));
	if(TFStorageTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	//Create TelemetrySendTask
	TelemetrySendTask_Ret = xTaskCreate((TaskFunction_t)TelemetrySendTask,"TelemetrySendTask",256,(void *)1,TelemetrySendTask_Prio,(TaskHandle_t *)(&TelemetrySendTask_TCB));
	if(TelemetrySendTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	
	//Create ExtfSendTask
	ExtfSendTask_Ret = xTaskCreate((TaskFunction_t)ExtfSendTask,"ExtfSendTask",256,(void *)1,ExtfSendTask_Prio,(TaskHandle_t *)(&ExtfSendTask_TCB));
	if(ExtfSendTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	
	//Create TimerCheckerTask
	TimerCheckerTask_Ret = xTaskCreate((TaskFunction_t)TimerCheckerTask,"TimerCheckerTask",256,(void *)1,TimerCheckerTask_Prio,(TaskHandle_t *)(&TimerCheckerTask_TCB));
	if(TimerCheckerTask_Ret == pdPASS) ;
	else
	{
		while(1) ;
	}
	
	vTaskStartScheduler();
}

//LEDTwinkTask函数声明
BaseType_t LEDTwinkTask_Ret;
UBaseType_t LEDTwinkTask_Prio=2;
TaskHandle_t LEDTwinkTask_TCB;

void LEDTwinkTask(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		vTaskDelay(100);
	}
}

////ReceiverTask函数声明
//BaseType_t ReceiverTask_Ret;
//UBaseType_t ReceiverTask_Prio=18;
//TaskHandle_t ReceiverTask_TCB;

//void ReceiverTask(void *pvParameters)
//{
//	ReceiverSemaphore = xSemaphoreCreateBinary();
//	HAL_UART_Receive_DMA(&huart5,ReceiverReceiveBuff,25);
//	__HAL_UART_ENABLE_IT(&huart5,UART_IT_IDLE);
//	while(1)
//	{
//		xSemaphoreTake(ReceiverSemaphore,100);
//		ReceiverRet = ReceiverDataConvert(ReceiverFifoBuff);
//		if(ReceiverRet == Receiver_OK)
//		{
//			ReceiverSolution();
//		}
//	}
//}

//NavigationTask函数声明
BaseType_t NavigationTask_Ret;
UBaseType_t NavigationTask_Prio=25;
TaskHandle_t NavigationTask_TCB;

void NavigationTask(void *pvParameters)
{
//	NavQueue = xQueueCreate(400,sizeof(uint8_t));
	NavSemaphore = xSemaphoreCreateBinary();
	HAL_UART_Receive_DMA(&huart6, NavRecBuff, NavDMARecLength);
//	__HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);
	while(1)
	{
		xSemaphoreTake(NavSemaphore,portMAX_DELAY);
		NavigationSolution();

	}

//	while(1)
//	{
//		vTaskDelay(1);
//		HAL_UART_AbortReceive(&huart6);
//		if(NavRecBuff[0]==0xFC)
//		{
//			memcpy(NavRecFifoBuff,NavRecBuff,306);
//			memset(NavRecBuff,0,306);
//			HAL_UART_Receive_DMA(&huart6, NavRecBuff, 400);
//			NavigationSolution();
//		}
//		else
//		{
//			vTaskDelay(1);
//			HAL_UART_Receive_DMA(&huart6, NavRecBuff, 400);
//		}
//	}
}

//ControlTask函数声明
BaseType_t ControlTask_Ret;
UBaseType_t ControlTask_Prio=24;
TaskHandle_t ControlTask_TCB;

void ControlTask(void *pvParameters)
{
	ControlSemaphore = xSemaphoreCreateBinary();
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);

	 while(1) {
		xSemaphoreTake(ControlSemaphore, portMAX_DELAY);
		if(ControlTime >= 5) HAL_GPIO_WritePin(BAT1_GPIO_Port,BAT1_Pin,GPIO_PIN_SET);//5s一口爆炸螺栓点燃
		if(ControlTime >= 10) HAL_GPIO_WritePin(BAT2_GPIO_Port,BAT2_Pin,GPIO_PIN_SET);//10s二口爆炸螺栓点燃
    // 添加判断条件：当ControlTime > 4时执行MYZControl
    if(ControlTime < 4.0f)
		{
		 	ServoSet(ServoChannel_1,0);
			ServoSet(ServoChannel_2,0);
			ServoSet(ServoChannel_3,0);
			ServoSet(ServoChannel_4,0);
		}
		else 
		{
			MYZControl();  // 调用控制函数
    }
  }
}


	

//TimerCheckerTask函数声明
BaseType_t TimerCheckerTask_Ret;
UBaseType_t TimerCheckerTask_Prio=5;
TaskHandle_t TimerCheckerTask_TCB;


void TimerCheckerTask(void *pvParameters)
{
    static uint8_t lastTriggerState = GPIO_PIN_RESET; // 初始化为低电平
    
    while(1)
    {
        uint8_t currentState = HAL_GPIO_ReadPin(TRIGGER_GPIO_Port, TRIGGER_Pin);
        
        // 1. 无论状态如何，都执行初始化
        ControlInit();

        
        // 2. 检测下降沿（高->低）
        if((lastTriggerState == GPIO_PIN_SET) && (currentState == GPIO_PIN_RESET))
        {
            // 触发ControlTime计时
						ControlTime = 0;
            __HAL_TIM_SET_COUNTER(&htim6, 0);
            HAL_TIM_Base_Start_IT(&htim6);
        }
        
        // 更新状态记录
        lastTriggerState = currentState;
        
        vTaskDelay(10); // 短暂延时
    }
}

//TFStorageTask函数声明
BaseType_t TFStorageTask_Ret;
UBaseType_t TFStorageTask_Prio=12;
TaskHandle_t TFStorageTask_TCB;

void TFStorageTask(void *pvParameters)
{
	TFInit();
	vTaskSuspend(NULL);
	while(1)
	{
		xTaskGetTickCount();
	}
}

//TelemetrySendTask函数声明
BaseType_t TelemetrySendTask_Ret;
UBaseType_t TelemetrySendTask_Prio=5;
TaskHandle_t TelemetrySendTask_TCB;

void TelemetrySendTask(void *pvParameters)
{
	while(1)
	{
		TelemetrySend();
		vTaskDelay(20);
	}
}


//ExtfSendTask函数声明
BaseType_t ExtfSendTask_Ret;
UBaseType_t ExtfSendTask_Prio=5;
TaskHandle_t ExtfSendTask_TCB;

void ExtfSendTask(void *pvParameters)
{
	while(1)
	{
		ExtfSend();
		vTaskDelay(20);
	}
}


