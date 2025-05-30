#include "main.h"
#include "fdilink_decode.h"
#include "FDILink.h"
#include "FDI_send.h"
#include "navigation.h"
//----------------------------------------------------------------------//
//				          - FDI_LINK Packet sending protocol                 -//
//----------------------------------------------------------------------//
//--TEST_2023
void MX_USART2_UART_Init(uint32_t baudrate);
void UART2_ReceiveHandler(void);
//extern uint8_t 	USART2_RX_BUF[256];     //接收缓冲,最大USART_REC_LEN个字节.（一般给200，接收数据量大就增加）
//extern uint16_t    USART2_RX_STA;       			  //接收状态标记
//extern uint16_t    USART2_RX_LEN;
//extern UART_HandleTypeDef huart2;
//extern UART_HandleTypeDef huart1;
//extern uint8_t		Res;
//static uint8_t USB_Tx_Buffer[2048];
//uint8_t		count;

/*!
*	Sends a FDI message based on the received data.
*@param[in] None.
*@return None.
*/
void fdiUsart2UserSentInstruction(void)
{
//		USART2_RX_STA = 0;
//		USART2_RX_BUF[USART2_RX_STA] = Res;

//			if(USART2_RX_BUF[2]=='4'&&USART2_RX_BUF[3]=='0')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_AHRSDATA_PACKET_ID\r\n",sizeof("#FDILINK_AHRSDATA_PACKET_ID\r\n"));
//				fdiGetPacket(FDILINK_AHRSDATA_PACKET_ID);
//			}
//			else if(USART2_RX_BUF[0]=='9'&&USART2_RX_BUF[3]=='0')
//			{
//				MX_USART2_UART_Init(9600);
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#9600\r\n",sizeof("9600\r\n"));
//			}
//			else if(USART2_RX_BUF[0]=='9'&&USART2_RX_BUF[5]=='0')
//			{
//				MX_USART2_UART_Init(921600);
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#9600\r\n",sizeof("9600\r\n"));
//			}			
//			else if(USART2_RX_BUF[0]=='1'&&USART2_RX_BUF[5]=='0')
//			{
//				MX_USART2_UART_Init(115200);
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#115200\r\n",sizeof("115200\r\n"));
//			}
//			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='2')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Formatted_Time_Packet_ID\r\n",sizeof("#Formatted_Time_Packet_ID\r\n"));
//				fdiGetPacket(Formatted_Time_Packet_ID);
//			}
//			else if(USART2_RX_BUF[2]=='4'&&USART2_RX_BUF[3]=='1')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_AHRSDATA_PACKET_ID\r\n",sizeof("#FDILINK_AHRSDATA_PACKET_ID\r\n"));
//				fdiGetPacket(FDILINK_AHRSDATA_PACKET_ID);
//			}
//			else if(USART2_RX_BUF[2]=='4'&&USART2_RX_BUF[3]=='2')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_INSGPSDATA_PACKET_ID\r\n",sizeof("#FDILINK_INSGPSDATA_PACKET_ID\r\n"));
//				fdiGetPacket(FDILINK_INSGPSDATA_PACKET_ID);
//			}
//			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='1')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Unix_Time_Packet_ID\r\n",sizeof("#Unix_Time_Packet_ID\r\n"));
//				fdiGetPacket(Unix_Time_Packet_ID);
//			}
//			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='4')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Position_Standard_Deviation_Packet_ID\r\n",sizeof("#Position_Standard_Deviation_Packet_ID\r\n"));
//				fdiGetPacket(Position_Standard_Deviation_Packet_ID);
//			}
////			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='5')
////			{
////				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Velocity_Standard_Deviation_Packet_ID\r\n",sizeof("#Velocity_Standard_Deviation_Packet_ID\r\n"));
////				fdiGetPacket(Velocity_Standard_Deviation_Packet_ID);
////			}
//			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='6')
//			{
//				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Euler_Orientation_Standard_Deviation_Packet_ID\r\n",sizeof("Euler_Orientation_Standard_Deviation_Packet_ID\r\n"));
//				fdiGetPacket(Euler_Orientation_Standard_Deviation_Packet_ID);
//			}
//			else if(USART2_RX_BUF[2]=='5'&&USART2_RX_BUF[3]=='7')
//			{
// 				HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Quaternion_Orientation_Standard_Deviation_Packet_ID\r\n",sizeof("Quaternion_Orientation_Standard_Deviation_Packet_ID\r\n"));
//				fdiGetPacket(Quaternion_Orientation_Standard_Deviation_Packet_ID);
//			}
//		USART2_RX_STA ++;
//		if(USART2_RX_STA>=255)
//		{
//			USART2_RX_STA = 0;
//		}
//		//等待下一次接收中断
//		HAL_UART_Receive_IT(&huart2,&Res,1);

}
/*!
*	Decode the FDI link packet based on the packet ID.
*	@param[in] PACKET_ID Packet ID (0-255)
*	@param[in] buf Pointer to the buffer containing the packet data.
*	@return None.
*/
void fdiDecodeBuffer(int PACKET_ID,void* buf)
{
	switch(PACKET_ID)
	{
		case FDILINK_VERSIONDATA_PACKET_ID:       //FDILINK_VERSIONDATA 0x39 OK
		{
//			FDILink_VersionData_Packet_t VersionData;
			memcpy(&VersionData,buf,sizeof(FDILink_VersionData_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"SN:%d\tHardware_Version:%d\tHardware_Name:%d\tFirmware_Version:%d\tFirmware_Name:%d\n"
//				,VersionData.SN[4],VersionData.Hardware_Version,VersionData.Hardware_Name,
//				VersionData.Firmware_Version,VersionData.Firmware_Name);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
						break;
		}
		case FDILINK_IMUDATA_PACKET_ID:  		 //MSG_IMU 0x40 OK
		{
//			FDILink_IMUData_Packet_t IMUData;
			memcpy(&IMUData,buf,sizeof(FDILink_IMUData_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"GX:%f\tGY:%f\tGZ:%f\tAX:%f\tAY:%f\tAZ:%f\tMX:%f\tMY:%f\tMZ:%f\tIT:%f\tPre:%f\tPT:%f\n"
//				,IMUData.Gyroscope_X,IMUData.Gyroscope_Y,IMUData.Gyroscope_Z,
//				IMUData.Accelerometer_X,IMUData.Accelerometer_Y,IMUData.Accelerometer_Z,
//				IMUData.Magnetometer_X,IMUData.Magnetometer_Y,IMUData.Magnetometer_Z,
//				IMUData.IMU_Temperature,IMUData.Pressure,IMUData.Pressure_Temperature);
////				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
//						break;
		}
		case FDILINK_AHRSDATA_PACKET_ID:  	 //MSG_AHRS 0x41 OK
		{
//			FDILink_AHRSData_Packet_t AHRSData;
			memcpy(&AHRSData,buf,sizeof(FDILink_AHRSData_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"RS:%f\tPS:%f\tHS:%f\tR:%f\tP:%f\tH:%f\tQ1:%f\tQ2:%f\tQ3:%f\tQ4:%f\n"
//				,AHRSData.RollSpeed,AHRSData.PitchSpeed,AHRSData.HeadingSpeed,
//				AHRSData.Roll,AHRSData.Pitch,AHRSData.Heading,
//				AHRSData.Q1,AHRSData.Q2,AHRSData.Q3,AHRSData.Q4);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
						break;
		}
		case FDILINK_INSGPSDATA_PACKET_ID:   //MSG_INS/GPS 0x42 OK
		{
//			FDILink_INSGPSData_Packet_t INSGPSData;
			memcpy(&INSGPSData,buf,sizeof(FDILink_INSGPSData_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"BVX:%f\tBVY:%f\tBVZ:%f\tBAX:%f\tBAY:%f\tBAZ:%f\tLN:%lf\tLE:%lf\tLD:%lf\tVN:%f\tVE:%f\tVD:%f\tAN:%f\tAE:%lf\tAD:%lf\tPA:%lf\n"
//				,INSGPSData.BodyVelocity_X,INSGPSData.BodyVelocity_Y,INSGPSData.BodyVelocity_Z,
//				INSGPSData.BodyAcceleration_X,INSGPSData.BodyAcceleration_Y,INSGPSData.BodyAcceleration_Z,
//				INSGPSData.Location_North,INSGPSData.Location_East,INSGPSData.Location_Down,INSGPSData.Velocity_North,INSGPSData.Velocity_East,INSGPSData.Velocity_Down,
//				INSGPSData.Acceleration_North,INSGPSData.Acceleration_East,INSGPSData.Acceleration_Down,
//				INSGPSData.Pressure_Altitude);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}			
			  		break;
		}
		case System_State_Packet_ID: 				 //MSG_SYS_STATE 0x50 OK
		{
//			System_State_Packet_t data;
			memcpy(&System_State_data,buf,sizeof(System_State_Packet_t));
						break;
		}
		case Unix_Time_Packet_ID:   		     //UNIX_TIME 0X51 OK
		{
//			Unix_Time_Packet_t TimeData;
			memcpy(&TimeData,buf,sizeof(Unix_Time_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Unix_time:%d\tMicroseconds:%d\n"
//				,TimeData.Unix_time,TimeData.Microseconds);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}			
						break;
		}
		case Formatted_Time_Packet_ID:       //FORMATTED_TIME 0X52 OK
		{
//			Formatted_Time_Packet_t FTimeData;
			memcpy(&FTimeData,buf,sizeof(Formatted_Time_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Microseconds:%d\tYear:%d\tYear_day:%d\tMonth:%d\tMonth_Day:%d\tWeek_Day:%d\tHour:%d\tMinute:%d\tSecond:%d\n"
//				,FTimeData.Microseconds,FTimeData.Year,FTimeData.Year_day,FTimeData.Month,FTimeData.Month_Day,FTimeData.Week_Day,FTimeData.Hour,FTimeData.Minute,FTimeData.Second);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}			
						break;
		}	
		case Position_Standard_Deviation_Packet_ID:   //POSITION_STANDARD OX54 OK
		{
//			Position_Standard_Deviation_Packet_t data;
			memcpy(&Position_Standard_Deviation_data,buf,sizeof(Position_Standard_Deviation_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Latitude_standard_deviation:%f\tLongitude_standard_deviation:%f\tHeight_standard_deviation:%f\n"
//				,data.Latitude_standard_deviation,data.Latitude_standard_deviation,data.Height_standard_deviation);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}	
			break;
		}
		case Velocity_Standard_Deviation_Packet_ID:   //VELOCITY_STANDARD OX55 OK
		{
//			Velocity_Standard_Deviation_Packet_t data;
			memcpy(&Velocity_Standard_Deviation_data,buf,sizeof(Velocity_Standard_Deviation_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Velocity_north_standard_deviation:%f\tVelocity_east_standard_deviation:%f\tVelocity_down_standard_deviation:%f\n"
//				,data.Velocity_north_standard_deviation,data.Velocity_east_standard_deviation,data.Velocity_down_standard_deviation);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
			break;
		}
		case Euler_Orientation_Standard_Deviation_Packet_ID:   //EULER_ORIENTATION_STANDARD OX56 OK
		{
//			Euler_Orientation_Standard_Deviation_Packet_t data;
			memcpy(&Euler_Orientation_Standard_Deviation_data,buf,sizeof(Euler_Orientation_Standard_Deviation_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Roll_standard_deviation:%f\tPitch_standard_deviation:%f\tHeading_standard_deviation:%f\n"
//				,data.Roll_standard_deviation,data.Pitch_standard_deviation,data.Heading_standard_deviation);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
			break;
		}
		case Quaternion_Orientation_Standard_Deviation_Packet_ID:   //QUATERNION_ORIENTATION_STANDARD OX57
		{
//			Quaternion_Orientation_Standard_Deviation_Packet_t data;
			memcpy(&Quaternion_Orientation_Standard_Deviation_data,buf,sizeof(Quaternion_Orientation_Standard_Deviation_Packet_t));
//			count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Q0:%f\tQ1:%f\tQ2:%f\tQ3:%f\n"
//				,data.Q0_standard_deviation,data.Q1_standard_deviation,data.Q2_standard_deviation,data.Q3_standard_deviation);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
			break;
		}
		case Raw_Sensors_Packet_ID:   			 //RAW_SENSORS OX58
		{
//			Raw_Sensors_Packet_t data;
			memcpy(&Raw_Sensors_data,buf,sizeof(Raw_Sensors_Packet_t));
//						count++;
//			if(count > 100)
//			{
//				int len = sprintf((char*)USB_Tx_Buffer,
//				"Accelerometer_X:%f\tAccelerometer_Y:%f\tAccelerometer_Z:%f\tGyroscope_X:%f\tGyroscope_Y:%f\tGyroscope_Z:%f\tMagnetometer_X:%f\tMagnetometer_Y:%f\tMagnetometer_Z:%f\tIMU_Temperature:%f\tPressure:%f\tPressure_Temperature:%f\n"
//				,data.Accelerometer_X,data.Accelerometer_Y,data.Accelerometer_Z,data.Gyroscope_X,data.Gyroscope_Y,data.Gyroscope_Z,data.Magnetometer_X,data.Magnetometer_Y,data.Magnetometer_Z,data.IMU_Temperature,data.Pressure,data.Pressure_Temperature);
//				CDC_Transmit_FS(USB_Tx_Buffer,len);
//				HAL_UART_Transmit_DMA(&huart1, USB_Tx_Buffer, len);
//				count = 0;
//			}
						break;
		}		
		case Raw_GNSS_Packet_ID:             //MSG_RAW_GNSS 0x59
		{
//			Raw_GNSS_Packet_t data;
			memcpy(&Raw_GNSS_data,buf,sizeof(Raw_GNSS_Packet_t));
						break;
		}
		case Satellites_Packet_ID:           //SATELLITES 0x5A
		{
//			Satellites_Packet_t data;
			memcpy(&Satellites_data,buf,sizeof(Satellites_Packet_t));
						break;
		}
		case Detailed_Satellites_Packet_ID:  //DETAILED_SATELLITES 0x5B
		{
//			Detailed_Satellites_Packet_t data;
			memcpy(&Detailed_Satellites_data,buf,sizeof(Detailed_Satellites_Packet_t));
						break;
		}
		case Geodetic_Position_Packet_ID:    //GEODETIC_POSITION 0x5C
		{
//			Geodetic_Position_Packet_t data;
			memcpy(&Geodetic_Position_data,buf,sizeof(Geodetic_Position_Packet_t));
						break;
		}
		case ECEF_Position_Packet_ID:        //GEODETIC_POSITION 0x5D
		{
//			ECEF_Position_Packet_t data;
			memcpy(&ECEF_Position_data,buf,sizeof(ECEF_Position_Packet_t));
						break;
		}
		case UTM_Position_Packet_ID:         //UIM_POSITION 0x5E
		{
//			UTM_Position_Packet_t data;
			memcpy(&UTM_Position_data,buf,sizeof(UTM_Position_Packet_t));
						break;
		}
		case NED_Velocity_Packet_ID:         //NED_VELOCITY 0x5F
		{
//			NED_Velocity_Packet_t data;
			memcpy(&NED_Velocity_data,buf,sizeof(NED_Velocity_Packet_t));
						break;
		}
		case Body_Velocity_Packet_ID:        //BODY_VELOCITY 0x60
		{
//			Body_Velocity_Packet_t data;
			memcpy(&Body_Velocity_data,buf,sizeof(Body_Velocity_Packet_t));
						break;
		}
		case Acceleration_Packet_ID:         //ACCELERATION 0x61
		{
//			Acceleration_Packet_t data;
			memcpy(&Acceleration_data,buf,sizeof(Acceleration_Packet_t));
						break;
		}		
		case Body_Acceleration_Packet_ID:    //BODT_ACCELERATION 0x62
		{
//			Body_Acceleration_Packet_t data;
			memcpy(&Body_Acceleration_data,buf,sizeof(Body_Acceleration_Packet_t));
						break;
		}		
		case Euler_Orientation_Packet_ID:    //EULER_ORIENTATION 0x63
		{
//			Euler_Orientation_Packet_t data;
			memcpy(&Euler_Orientation_data,buf,sizeof(Euler_Orientation_Packet_t));
						break;
		}
		case Quaternion_Orientation_Packet_ID://QUATERNOION_ORIENTATION 0x64
		{
//			Quaternion_Orientation_Packet_t data;
			memcpy(&Quaternion_Orientation_data,buf,sizeof(Quaternion_Orientation_Packet_t));
						break;
		}
		case DCM_Orientation_Packet_ID:      //DCM_ORIENTATION 0x65
		{
//			DCM_Orientation_Packet_t data;
			memcpy(&DCM_Orientation_data,buf,sizeof(DCM_Orientation_Packet_t));
						break;
		}
		case Angular_Velocity_Packet_ID:     //ANGUAR_VELOCITY 0x66
		{
//			Angular_Velocity_Packet_t data;
			memcpy(&Angular_Velocity_data,buf,sizeof(Angular_Velocity_Packet_t));
						break;
		}
		case Angular_Acceleration_Packet_ID: //ANGUAR_ACCELERATION 0x67
		{
//			Angular_Acceleration_Packet_t data;
			memcpy(&Angular_Acceleration_data,buf,sizeof(Angular_Acceleration_Packet_t));
						break;
		}
		case External_Position_And_Velocity_Packet_ID://EXTERNAL_POSITION_AND_VELOCITY 0x68
		{
//			External_Position_And_Velocity_Packet_t data;
			memcpy(&External_Position_And_Velocity_data,buf,sizeof(External_Position_And_Velocity_Packet_t));
						break;
		}
		case External_Position_Packet_ID:    //EXTERNAL_POSITION 0x69
		{
//			External_Position_Packet_t data;
			memcpy(&External_Position_data,buf,sizeof(External_Position_Packet_t));
						break;
		}
		case External_Velocity_Packet_ID:    //EXTERNAL_VELOCITY 0x6A
		{
//			External_Velocity_Packet_t data;
			memcpy(&External_Velocity_data,buf,sizeof(External_Velocity_Packet_t));
						break;
		}
		case External_Body_Velocity_Packet_ID://EXTERNAL_BODT_VELOCITY 0x6B
		{
//			External_Body_Velocity_Packet_t data;
			memcpy(&External_Body_Velocity_data,buf,sizeof(External_Body_Velocity_Packet_t));
						break;
		}
		case External_Heading_Packet_ID:     //EXTERNAL_HEADING 0x6C
		{
//			External_Heading_Packet_t data;
			memcpy(&External_Heading_data,buf,sizeof(External_Heading_Packet_t));
						break;
		}
		case External_Time_Packet_ID:        //EXTERNAL_TIME 0x70
		{
//			External_Time_Packet_t data;
			memcpy(&External_Time_data,buf,sizeof(External_Time_Packet_t));
						break;
		}
		case External_Depth_Packet_ID:       //EXTERNAL_DEPTH 0x71
		{
//			External_Depth_Packet_t data;
			memcpy(&External_Depth_data,buf,sizeof(External_Depth_Packet_t));
						break;
		}
		case External_Pitot_Pressure_Packet_ID://EXTERNAL_DEPTH 072
		{
//			External_Pitot_Pressure_Packet_t data;
			memcpy(&External_Pitot_Pressure_data,buf,sizeof(External_Pitot_Pressure_Packet_t));
						break;
		}
		case External_Air_Data_Packet_ID:    //EXTERNAL_AIE_DATA 0x69
		{
			External_Air_Data_Packet_t data;
			memcpy(&data,buf,sizeof(External_Air_Data_Packet_t));
						break;
		}
		case External_LIDAR_Packet_ID:       //EXTERNAL_LIDAR_DATA 0x91
		{
			External_LIDAR_Packet_t data;
			memcpy(&data,buf,sizeof(External_LIDAR_Packet_t));
						break;
		}		
		case External_Odom_Data_Packet_ID:   //EXTERNAL_ODOM_DATA 0x90
		{
			External_Odom_Data_Packet_t data;
			memcpy(&data,buf,sizeof(External_Odom_Data_Packet_t));
						break;
		}
		case External_SLAM1_Packet_ID:       //EXTERNAL_SALAM1 0x91
		{
			External_SLAM1_Packet_t data;
			memcpy(&data,buf,sizeof(External_SLAM1_Packet_t));
						break;
		}
		case External_SLAM2_Packet_ID:       //EXTERNAL_SALAM2 0x92
		{
			External_SLAM2_Packet_t data;
			memcpy(&data,buf,sizeof(External_SLAM2_Packet_t));
						break;
		}
		case Running_Time_Packet_ID:         //RUNNING_TIME_PACKET 0x6D
		{
			Running_Time_Packet_t data;
			memcpy(&data,buf,sizeof(Running_Time_Packet_t));
						break;
		}
		case Local_Magnetic_Field_Packet_ID: //LOCAL 0x6E
		{
			Local_Magnetic_Field_Packet_t data;
			memcpy(&data,buf,sizeof(Local_Magnetic_Field_Packet_t));
						break;
		}
		case Odometer_State_Packet_ID:       //ODOMETER 0x6F
		{
			Odometer_State_Packet_t data;
			memcpy(&data,buf,sizeof(Odometer_State_Packet_t));
						break;
		}
		case Geoid_Height_Packet_ID:         //GEOID_HEIGHT 0x72
		{
			Geoid_Height_Packet_t data;
			memcpy(&data,buf,sizeof(Geoid_Height_Packet_t));
						break;
		}
		case RTCM_Corrections_Packet_ID:     //RTCM_CORRECTIONS 0x73
		{
			RTCM_Corrections_Packet_t data;
			memcpy(&data,buf,sizeof(RTCM_Corrections_Packet_t));
						break;
		}
		case Wind_Packet_ID:                 //WIND 0x75
		{
			Wind_Packet_t data;
			memcpy(&data,buf,sizeof(Wind_Packet_t));
						break;
		}
		case Heave_Packet_ID:                //HEAVE 0x76
		{
			Heave_Packet_t data;
			memcpy(&data,buf,sizeof(Heave_Packet_t));
						break;
		}
		case Raw_Satellite_Data_Packet_ID:   //RAW_SATELLITE 0x77
		{
			Raw_Satellite_Data_Packet_t data;
			memcpy(&data,buf,sizeof(Raw_Satellite_Data_Packet_t));
						break;
		}
		case GNSS_DUAL_ANT_Data_Packet_ID:   //GNSS_DUAL 0x78
		{
			GNSS_DUAL_ANT_Data_Packet_t data;
			memcpy(&data,buf,sizeof(GNSS_DUAL_ANT_Data_Packet_t));
						break;
		}
		case Gimbal_State_Packet_ID:         //GIMBAL_STATE 0x7A
		{
			Gimbal_State_Packet_t data;
			memcpy(&data,buf,sizeof(Gimbal_State_Packet_t));
						break;
		}		
		case Automotive_Packet_ID:           //AUTOMOTIVE 0x7B
		{
			Automotive_Packet_t data;
			memcpy(&data,buf,sizeof(Automotive_Packet_t));
						break;
		}
		case Installation_Alignment_Packet_ID://INSTALLATION_ALIGNMENT 0x80
		{
			Installation_Alignment_Packet_t data;
			memcpy(&data,buf,sizeof(Installation_Alignment_Packet_t));
						break;
		}
		case Filter_Options_Packet_ID:       //FILTER_OPTIONS 0x81
		{
			Filter_Options_Packet_t data;
			memcpy(&data,buf,sizeof(Filter_Options_Packet_t));
						break;
		}
		case GPIO_Configuration_Packet_ID:   //GPIO_CONFIG Ox82
		{
			GPIO_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(GPIO_Configuration_Packet_t));
						break;
		}		
		case Magnetic_Calibration_Values_Packet_ID://MAGNETIC_CAIL 0x83
		{
			Magnetic_Calibration_Values_Packet_t data;
			memcpy(&data,buf,sizeof(Magnetic_Calibration_Values_Packet_t));
						break;
		}		
		case Magnetic_Calibration_Configuration_Packet_ID://MAGNETIC_CAIL_CONFIG 0x84
		{
			Magnetic_Calibration_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(Magnetic_Calibration_Configuration_Packet_t));
						break;
		}			
		case Magnetic_Calibration_Status_Packet_ID://MAGNETIC_CAIL_STATUS 0x85
		{
			Magnetic_Calibration_Status_Packet_t data;
			memcpy(&data,buf,sizeof(Magnetic_Calibration_Status_Packet_t));
						break;
		}			
		case Odometer_Configuration_Packet_ID://ODOMETER_CONFIG 0x86
		{
			Odometer_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(Odometer_Configuration_Packet_t));
						break;
		}		
		case Set_Zero_Orientation_Alignment_Packet_ID://SET_ZERO 0x87
		{
			Set_Zero_Orientation_Alignment_Packet_t data;
			memcpy(&data,buf,sizeof(Set_Zero_Orientation_Alignment_Packet_t));
						break;
		}		
		case Reference_Point_Offsets_Packet_ID://REFERENCE_POINT 0x88
		{
			Reference_Point_Offsets_Packet_t data;
			memcpy(&data,buf,sizeof(Reference_Point_Offsets_Packet_t));
						break;
		}			
		case User_Data_Packet_ID:             //USER_DATA 0x8A
		{
			User_Data_Packet_t data;
			memcpy(&data,buf,sizeof(User_Data_Packet_t));
						break;
		}			
		case Baud_Rates_Packet_ID:            //BAUD_SATES 0xA0
		{
			Baud_Rates_Packet_t data;
			memcpy(&data,buf,sizeof(Baud_Rates_Packet_t));
						break;
		}		
		case Sensor_Ranges_Packet_ID:         //SENSOR_RANGES 0xA1
		{
			Sensor_Ranges_Packet_t data;
			memcpy(&data,buf,sizeof(Sensor_Ranges_Packet_t));
						break;
		}		
		case GPIO_Output_Configuration_Packet_ID://GPIO_OUTPUT_CONFIG 0xA2
		{
			GPIO_Output_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(GPIO_Output_Configuration_Packet_t));
						break;
		}		
		case GPIO_Input_Configuration_Packet_ID: //GPIO_INPUT_CONFIG 0xA3
		{
			GPIO_Input_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(GPIO_Input_Configuration_Packet_t));
						break;
		}			
		case Dual_Antenna_Configuration_Packet_ID://DUAL_ANTENNA_CONFIG 0xA4
		{
			Dual_Antenna_Configuration_Packet_t data;
			memcpy(&data,buf,sizeof(Dual_Antenna_Configuration_Packet_t));
						break;
		}
		
	}
	
}
void fdiComInterfaceDisplay(void)
{
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#You can set the baud rate to 115200\r\n",sizeof("#You can set the baud rate to 115200\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#You can set the baud rate to 9600\r\n",sizeof("#You can set the baud rate to 9600\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#You can set the baud rate to 921600\r\n",sizeof("#You can set the baud rate to 921600\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_IMUDATA_PACKET_ID 0x40\r\n",sizeof("#FDILINK_IMUDATA_PACKET_ID 0x40\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_AHRSDATA_PACKET_ID 0x41\r\n",sizeof("#FDILINK_AHRSDATA_PACKET_ID 0x41\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#FDILINK_INSGPSDATA_PACKET_ID 0x42\r\n",sizeof("#FDILINK_INSGPSDATA_PACKET_ID 0x42\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Unix_Time_Packet_ID 0x51\r\n",			 sizeof("#Unix_Time_Packet_ID 0x51\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Formatted_Time_Packet_ID 0x52\r\n", sizeof("#Formatted_Time_Packet_ID 0x52\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Position_Standard_Deviation_Packet_ID 0x54\r\n",sizeof("#Position_Standard_Deviation_Packet_ID 0x54\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Velocity_Standard_Deviation_Packet_ID 0x55\r\n",sizeof("#Velocity_Standard_Deviation_Packet_ID 0x55\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Euler_Orientation_Standard_Deviation_Packet_ID 0x56\r\n",sizeof("#Euler_Orientation_Standard_Deviation_Packet_ID 0x56\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Raw_Sensors_Packet_ID 0x58\r\n",sizeof("#Raw_Sensors_Packet_ID 0x58\r\n"));
//HAL_Delay(20);	
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Raw_GNSS_Packet_ID 0x59\r\n",sizeof("#Raw_GNSS_Packet_ID 0x59\r\n"));
//HAL_Delay(20);
//HAL_UART_Transmit_IT(&huart2,(uint8_t*)"#Please enter the baud rate or ID above\r\n",sizeof("#Please enter the baud rate or ID above\r\n"));
//HAL_Delay(20);
}
/*!
 *  FDILink_SDK说明
 *  此SDK配置了DETA系列主串口（MAIN）可以接收的各式指令，通过此单片机的串口2收发来实现
 *  此单片机的串口2波特率为921600，波特率随着DETA系列主串口（MAIN）的波特率更改而更改
 *  宏定义参数请在 FDILink.h 中查询
 *  HAL_UART_Transmit_IT	用户可以根据设备变化修改此处的串口发送函数来适配
 *  HAL_UART_RxCpltCallback		此处为串口的中断接收函数，用户参考此函数来适配
 */


/*!
 *  配置外部SLAM1数据包，所有外部数据包依照此格式配置（所有结构体在fdiDecodeBuffer中）
 *	Configure external SLAM1 packets. All external packets are configured in this format.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		None
 */
void fdiSendSLAM1Datapacke(void)
{
	External_SLAM1_Packet_t SLAMData;
	
	SLAMData.Position_X 				   = 1.23456;
	SLAMData.Position_Y 				   = 2.23456;
	SLAMData.Position_Z 				   = 3.23456;
	SLAMData.Velocity_X 				   = 4.23456;
	SLAMData.Velocity_Y 				   = 5.23456;
	SLAMData.Velocity_Z					   = 6.23456;
	SLAMData.Roll       				   = 7.23456;
	SLAMData.Pitch     					   = 8.23456;
	SLAMData.Yaw        				   = 9.23456;
	SLAMData.Position_X_standard_deviation = 0.23456;
	SLAMData.Position_Y_standard_deviation = 0.23456;
	SLAMData.Position_Z_standard_deviation = 0.23456;
	SLAMData.Velocity_X_standard_deviation = 0.23456;
	SLAMData.Velocity_Y_standard_deviation = 0.23456;
	SLAMData.Velocity_Z_standard_deviation = 0.23456;
	SLAMData.Roll_standard_deviation       = 2.23456;
	SLAMData.Pitch_standard_deviation      = 2.23456;
	SLAMData.Yaw_standard_deviation        = 2.23456;
	
	fdiSendExternalData(External_SLAM1_Packet_ID, &SLAMData, sizeof(External_SLAM1_Packet_t));
}

/*!
 *  发送配置后的外部数据包给DETA10，type为数据包ID，buffer为配置后的数据包，length为buffer包含字节的长度
 *	Send configured external packets.
 *	\param[out]	None
 *	\param[in]	ID - the data frame ID number to be requested.
 *	\return		FDI_NO_ERROR if we have entered configuration mode.
 */
int fdiSendExternalData(int type, void* buffer, int length)
{
//	uint8_t buf[256];
//	fdiComBufferTrans(buf, &_FDILink, type, buffer, length);
//	HAL_Delay(10);
//	HAL_UART_Transmit_IT(&huart2, buf, strlen(buf));
//	HAL_UART_Transmit_IT(&huart1, buf, strlen(buf));
//	//USART2_RX_STA = 0;
//	return FDI_NO_ERROR;
}


