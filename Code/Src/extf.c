#include "extf.h"

//外接储存模块

uint8_t ExtfSendBuff[2000];//数组长度过短会导致飞控卡死



void ExtfSend(void)
{
  sprintf(ExtfSendBuff,"%0.f,%0.f,%0.f,%0.f,%0.f,%0.f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.5f,%0.5f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f%0.5f,%0.5f,%0.2f,%0.2f,%0.2f,%0.2f,%0.f,\r\n",FTimeData.Year,FTimeData.Month,FTimeData.Month_Day,FTimeData.Hour,FTimeData.Minute,FTimeData.Second,AHRSData.RollSpeed,AHRSData.PitchSpeed,AHRSData.HeadingSpeed,AHRSData.Roll,AHRSData.Pitch,AHRSData.Heading,Geodetic_Position_data.Longitude,Geodetic_Position_data.Latitude,Geodetic_Position_data.Height,INSGPSData.Location_Down,INSGPSData.Location_East,INSGPSData.Location_North,INSGPSData.Velocity_Down,INSGPSData.Velocity_East,INSGPSData.Velocity_North,Raw_Sensors_data.Pressure,Raw_Sensors_data.Pressure_Temperature,Raw_GNSS_data.Longitude,Raw_GNSS_data.Latitude,Raw_GNSS_data.Height,Raw_GNSS_data.Velocity_down,Raw_GNSS_data.Velocity_east,Raw_GNSS_data.Velocity_north,Satellites_data.GNSS_satellites);
	
	HAL_UART_Transmit_DMA(&huart7,ExtfSendBuff,sizeof(ExtfSendBuff));
}