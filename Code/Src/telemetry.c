#include "telemetry.h"
#include "control.h"

uint8_t TelemetrySendBuff[2000];



void TelemetrySend(void)
{
	sprintf(TelemetrySendBuff,"%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.5f,%0.5f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.1f,%0.1f,%0.1f,%0.2f,%0.2f,%0.2f \r\n",AHRSData.RollSpeed,AHRSData.PitchSpeed,AHRSData.HeadingSpeed,AHRSData.Roll,AHRSData.Pitch,AHRSData.Heading,Geodetic_Position_data.Longitude,Geodetic_Position_data.Latitude,Geodetic_Position_data.Height,INSGPSData.Location_Down,INSGPSData.Location_East,INSGPSData.Location_North,INSGPSData.Velocity_Down,INSGPSData.Velocity_East,INSGPSData.Velocity_North,servo_roll,servo_yaw,servo_pitch,Ny,Nz,ControlTime);
	
	HAL_UART_Transmit_DMA(&huart8,TelemetrySendBuff,sizeof(TelemetrySendBuff));

}
