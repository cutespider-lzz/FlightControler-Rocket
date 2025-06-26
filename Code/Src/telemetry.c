#include "telemetry.h"

uint8_t TelemetrySendBuff[100];



void TelemetrySend(void)
{
	sprintf(TelemetrySendBuff,"Height:%0.2f,Satellites:%.0f\r\n",Geodetic_Position_data.Height,Satellites_data.GNSS_satellites);
	HAL_UART_Transmit_DMA(&huart8,TelemetrySendBuff,sizeof(TelemetrySendBuff));

}
