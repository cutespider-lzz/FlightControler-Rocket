#include "telemetry.h"

uint8_t TelemetrySendBuff[100];



void TelemetrySend(void)
{
	sprintf(TelemetrySendBuff,"Roll:%0.2f Pitch:%0.2f \r\n",AHRSData.Roll,AHRSData.Pitch);
	HAL_UART_Transmit_DMA(&huart8,TelemetrySendBuff,sizeof(TelemetrySendBuff));

}
