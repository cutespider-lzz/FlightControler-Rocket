#include "extf.h"
#include "control.h"

//外接储存模块

uint8_t ExtfSendBuff[2000];//数组长度过短会导致飞控卡死



void ExtfSend(void)
{
  sprintf(ExtfSendBuff,"%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.5f,%0.5f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.1f,%0.1f,%0.1f,%0.2f,%0.2f,%0.2f \r\n",AHRSData.RollSpeed,AHRSData.PitchSpeed,AHRSData.HeadingSpeed,AHRSData.Roll,AHRSData.Pitch,AHRSData.Heading,Geodetic_Position_data.Longitude,Geodetic_Position_data.Latitude,Geodetic_Position_data.Height,INSGPSData.Location_Down,INSGPSData.Location_East,INSGPSData.Location_North,INSGPSData.Velocity_Down,INSGPSData.Velocity_East,INSGPSData.Velocity_North,servo_roll,servo_yaw,servo_pitch,Ny,Nz,ControlTime);
	
	HAL_UART_Transmit_DMA(&huart7,ExtfSendBuff,sizeof(ExtfSendBuff));
}