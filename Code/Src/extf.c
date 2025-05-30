#include "extf.h"

//Íâ½Ó´¢´æÄ£¿é

uint8_t ExtfSendBuff[100];



void ExtfSend(void)
{
	sprintf(ExtfSendBuff,"Roll:%0.2f Pitch:%0.2f Heading:%0.2f \r\n",AHRSData.Roll,AHRSData.Pitch,AHRSData.Heading);
	HAL_UART_Transmit_DMA(&huart7,ExtfSendBuff,sizeof(ExtfSendBuff));
}