#include "main.h"
#include "fdilink_decode.h"
#include "FDILink.h"
#include "FDI_send.h"
#include "FDI_config.h"
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
uint8_t 	USART2_RX_BUF[256];     //接收缓冲,最大USART_REC_LEN个字节.（一般给200，接收数据量大就增加）
uint8_t		Res;
uint16_t    USART2_RX_STA;       			  //接收状态标记
uint16_t    USART2_RX_LEN;
uint32_t		YU=0;
int fdiComSetConfig(void)
{
	HAL_UART_Transmit_IT(&huart1,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart1,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart2,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart2,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	USART2_RX_STA = 0;
	HAL_Delay(200);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  进入配置模式
 *	Enter configuration mode.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have entered configuration mode.
 */
int fdiEnterSetConfig(void)
{
	HAL_UART_Transmit_IT(&huart1,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart1,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart2,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	HAL_Delay(500);
	HAL_UART_Transmit_IT(&huart2,"#fconfig\r\n",sizeof("#fconfig\r\n"));
	USART2_RX_STA = 0;
	HAL_Delay(200);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
void fdiResetAll(FDILink_Status_t* FDILink)
{
	FDILink->RxStatus = FDILink_Frame_Start;
	FDILink->RxDataLeft = 0;
	FDILink->RxType = 0;
	FDILink->BufferIndex = 0;
	FDILink->TxNumber = 0;
}
/*!
 *  进入配置模式
 *	Enter configuration mode.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have entered configuration mode.
 */
//int fdiEnterSetConfig(char* ID,int num)
//{
//	char send_buff1[128];
//	char send_buff2[128];
//	sprintf(send_buff1, "#fparam get %s\r\n ", ID);
//	sprintf(send_buff2, "#fparam set %s %d\r\n ", ID,num);
//	fdiSetConfig();
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff1,strlen(send_buff1));
//	HAL_Delay(1000);HAL_Delay(1000);	
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff2,strlen(send_buff2));
//	HAL_Delay(1000);HAL_Delay(1000);	
//	fdiSetSave();
//	fdiSetReboot();

//	USART2_RX_STA = 0;
//	HAL_Delay(200);

//	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
//	while(huart1.gState != HAL_UART_STATE_READY){};
//	
//	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
//	if(res)
//		return FDI_NO_ERROR;
//	else
//		return FDI_ERROR;
//	HAL_Delay(100);
//}
/*!
 *  退出配置模式
 *	Exit configuration mode.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have exited configuration mode.
 */
int fdiSetDeconfig(void)
{
	HAL_UART_Transmit_IT(&huart1,"#fdeconfig\r\n",sizeof("#fdeconfig\r\n"));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,"#fdeconfig\r\n",sizeof("#fdeconfig\r\n"));
	USART2_RX_STA = 0;

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  重启设备（重要数据的更新需要重启设备）
 *	Restart the device (the device needs to be restarted for the update of important data).
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have restarted the device.
 */
int fdiSetReboot(void)
{
	HAL_UART_Transmit_IT(&huart1,"#freboot\r\n",sizeof("#freboot\r\n"));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,"#freboot\r\n",sizeof("#freboot\r\n"));
	HAL_Delay(1500);
	HAL_UART_Transmit_IT(&huart1,"y\r\n",sizeof("y\r\n"));
	USART2_RX_STA = 0;
	HAL_Delay(200);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  恢复出厂设置
 *	Restore factory settings.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have restored factory settings.
 */
int fdiSetReset(void)
{
	HAL_UART_Transmit_IT(&huart1,"#freset\r\n",sizeof("#freset\r\n"));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,"#freset\r\n",sizeof("#freset\r\n"));
	HAL_Delay(1500);
	HAL_UART_Transmit_IT(&huart2,"y\r\n",sizeof("y\r\n"));
	USART2_RX_STA = 0;
	HAL_Delay(200);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  保存已修改的配置（重要的数据更新需要保存）
 *	Save modified configuration.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiSetSave(void)
{
	HAL_UART_Transmit_IT(&huart1,"#fsave\r\n",sizeof("#fsave\r\n"));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,"#fsave\r\n",sizeof("#fsave\r\n"));
	USART2_RX_STA = 0;
	HAL_Delay(200);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  设置设备的安装方向：flip可选为绕x、y、z轴旋转，rot（0-360度）为从设备顶部看去顺时针为正方向
 *	Set the installation direction of the equipment.
 *	\param[out]	None
 *	\param[in]	flip - choose one of value from x, y or z; rot - range from 0 to 360(degree)
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigAxis(char* flip, int rot)
{
	char send_buff[128];
	sprintf(send_buff, "#faxis %s %d\r\n", flip, rot);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
		
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置双天线航向偏角，其中angle为角度值（0-360度）
 *	Configure dual antenna heading angle.
 *	\param[out]	None
 *	\param[in]	angle - dual antenna heading angle.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigAnteHeadbias(int angle)
{
	char send_buff[128];
	sprintf(send_buff, "#fanteheadbias %d\r\n", angle);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
		
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
*  配置双天线之间的基线长度，length单位为米（m）
 *	Configure dual antenna baseline length.
 *	\param[out]	None
 *	\param[in]	length - dual antenna baseline length.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigAnteBaseline(int length)
{
	char send_buff[128];
	sprintf(send_buff, "#fantebaseline %d\r\n", length);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
		
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置GNSS主天线到IMU的杆臂命令
 *	Configure lever arm command from GNSS main antenna to IMU.
 *	\param[out]	None
 *	\param[in]	(x,y,z)
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigAnteArm(int x, int y, int z)
{
	char send_buff[128];
	sprintf(send_buff, "#fantearm %d %d %d\r\n", x, y, z);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
		
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  校准陀螺仪、加表的常值零偏以及调平，Level和Acce需要在水平静止的状态下执行该命令，Gyro只需要模块保持静止
 *	Calibrate the constant zero bias and leveling of gyroscope and meter.
 *	\param[out]	None
 *	\param[in]	Level, Acce or Gyro
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigImucailed(int num)
{
	char send_buff[128];
	switch(num)
	{
		case Level:
			sprintf(send_buff, "#fimucal_level\r\n");//将IMU坐标系调至水平面，不改变陀螺和加表零偏
		case Acce:
			sprintf(send_buff, "#fimucal_acce\r\n");//执行加速度计零偏校准
		case Gyro:
			sprintf(send_buff, "#fimucal_gyro\r\n");//执行陀螺仪零偏校准
		default:
			break;
	}
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
		
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置发送的数据内容，msg为2位16进制数字表示数据包ID，freq为设置指定数据包的发送频率
 *	Configure the data content to be sent.
 *	\param[out]	None
 *	\param[in]	msg - Represents the packet ID; freq - Packet transmit frequency.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigPacketSentMsg(char* msg, int freq)
{
	char send_buff[128];
	sprintf(send_buff, "#fmsg %s %d\r\n", msg, freq);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	return FDI_NO_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置GNSS设置参数，paramName为需要设置的参数名称，paramValue为设置参数的数值（10进制）
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetDgnss(int DGNSS, char* paramValue)
{
	char* paramName;
	memset(paramName, 0, strlen(paramName));
	switch(DGNSS)
	{
		case QXWZ_DSK_KEY:
			memcpy(paramName, "QXWZ_DSK_KEY", strlen("QXWZ_DSK_KEY"));break;
		case QXWZ_DSK_SECRET:
			memcpy(paramName, "QXWZ_DSK_SECRET", strlen("QXWZ_DSK_SECRET"));break;
		case QXWZ_DEV_ID:
			memcpy(paramName, "QXWZ_DEV_ID", strlen("QXWZ_DEV_ID"));break;
		case QXWZ_DEV_TYPE:
			memcpy(paramName, "QXWZ_DEV_TYPE", strlen("QXWZ_DEV_TYPE"));break;
		case NTRIP_SVR_DOMAIN:
			memcpy(paramName, "NTRIP_SVR_DOMAIN", strlen("NTRIP_SVR_DOMAIN"));break;
		case NTRIP_SVR_PORT:
			memcpy(paramName, "NTRIP_SVR_PORT", strlen("NTRIP_SVR_PORT"));break;
		case NTRIP_ACCOUNT:
			memcpy(paramName, "NTRIP_ACCOUNT", strlen("NTRIP_ACCOUNT"));break;
		case NTRIP_PASSWORD:
			memcpy(paramName, "NTRIP_PASSWORD", strlen("NTRIP_PASSWORD"));break;
		case NTRIP_MOUNT:
			memcpy(paramName, "NTRIP_MOUNT", strlen("NTRIP_MOUNT"));break;
		case BASE_STATION_SOURCE:
			memcpy(paramName, "BASE_STATION_SOURCE", strlen("BASE_STATION_SOURCE"));break;
		case USR_AUTHEMTICATION:
			memcpy(paramName, "USR_AUTHEMTICATION", strlen("USR_AUTHEMTICATION"));break;
		case NET_INFO_IMEI:
			memcpy(paramName, "NET_INFO_IMEI", strlen("NET_INFO_IMEI"));break;
		case NET_INFO_CCID:
			memcpy(paramName, "NET_INFO_CCID", strlen("NET_INFO_CCID"));break;
	}
	char send_buff[128];
	sprintf(send_buff, "#fdgnss set %s %s\r\n", paramName, paramValue);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	return FDI_NO_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置参数，paramName为需要设置的参数名称，paramValue为设置参数的数值（10进制）
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiSetParam(char* paramName, float paramValue)
{
	char send_buff[128];
	sprintf(send_buff, "#fparam set %s %f\r\n", paramName, paramValue);
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
	HAL_Delay(1000);
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
	USART2_RX_STA = 0;
	HAL_Delay(100);

	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	return FDI_NO_ERROR;
	HAL_Delay(100);
}
/*!
 *  配置设备数据口的波特率，随着设备型号的改变可用数据口也会发生变化，具体参考各型号手册
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigBaud(int COM, int BAUD)
{
	switch(COM)
	{
		case 1:
			fdiSetParam("COMM_BAUD1", BAUD);break;
		case 2:
			fdiSetParam("COMM_BAUD2", BAUD);break;
		case 3:
			fdiSetParam("COMM_BAUD3", BAUD);break;
		case 4:
			fdiSetParam("COMM_BAUD4", BAUD);break;
		case 5:
			fdiSetParam("COMM_BAUD5", BAUD);break;
		case 6:
			fdiSetParam("COMM_BAUD6", BAUD);break;
		case 7:
			fdiSetParam("COMM_BAUD7", BAUD);break;
	}
}
/*!
 *  配置设备数据口的功能，随着设备型号的改变功能也会发生变化，具体参考各型号手册
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigType(int COM, int Type)
{
	switch(COM)
	{
		case 1:
			fdiSetParam("COMM_STREAM_TYP1", Type);break;
		case 2:
			fdiSetParam("COMM_STREAM_TYP2", Type);break;
		case 3:
			fdiSetParam("COMM_STREAM_TYP3", Type);break;
		case 4:
			fdiSetParam("COMM_STREAM_TYP4", Type);break;
		case 5:
			fdiSetParam("COMM_STREAM_TYP5", Type);break;
		case 6:
			fdiSetParam("COMM_STREAM_TYP6", Type);break;
		case 7:
			fdiSetParam("COMM_STREAM_TYP7", Type);break;
	}
}

/*!
 *  配置USER_DEFINE数据
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigUserDefine(int type, float num)
{
	switch(type)
	{
		case USER_DEFINE_ROLL:
			fdiSetParam("USER_DEFINE_ROLL", num);break;
		case USER_DEFINE_PITCH:
			fdiSetParam("USER_DEFINE_PITCH", num);break;
		case USER_DEFINE_YAW:
			fdiSetParam("USER_DEFINE_YAW", num);break;
		case USER_DEFINE_VELN:
			fdiSetParam("USER_DEFINE_VELN", num);break;
		case USER_DEFINE_VELE:
			fdiSetParam("USER_DEFINE_VELE", num);break;
		case USER_DEFINE_VELD:
			fdiSetParam("USER_DEFINE_VELD", num);break;
		case USER_DEFINE_HOLDLAT_1:
			fdiSetParam("USER_DEFINE_HOLDLAT_1", num);break;
		case USER_DEFINE_HOLDLAT_2:
			fdiSetParam("USER_DEFINE_HOLDLAT_2", num);break;
		case USER_DEFINE_HOLDLON_1:
			fdiSetParam("USER_DEFINE_HOLDLON_1", num);break;
		case USER_DEFINE_HOLDLON_2:
			fdiSetParam("USER_DEFINE_HOLDLON_2", num);break;
		case USER_DEFINE_CAN_ID:
			fdiSetParam("USER_DEFINE_CAN_ID", num);break;
	}
}

/*!
 *  配置GPIOs功能
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigGPIOs(int GPIO, int Fun)
{
	switch(GPIO)
	{
		case 1:
			fdiSetParam("GPIO_1_FUNCTION", Fun);break;
		case 2:
			fdiSetParam("GPIO_2_FUNCTION", Fun);break;
	}
}

/*!
 *  配置AID开关
 *	configuration parameter.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained; paramValue - Set the value of the parameter.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComSetConfigAID(int AID, int Status)
{
	switch(AID)
	{
		case AID_ACCEL_GRAVITY:
			fdiSetParam("AID_ACCEL_GRAVITY", Status);break;
		case AID_MAG_V_MAGNETIC:
			fdiSetParam("AID_MAG_V_MAGNETIC", Status);break;
		case AID_INIT_YAW_USE_MAG:
			fdiSetParam("AID_INIT_YAW_USE_MAG", Status);break;
		case AID_EXT_HEADING_UPDATE:
			fdiSetParam("AID_EXT_HEADING_UPDATE", Status);break;
		case AID_EXT_ATT_UPDATE:
			fdiSetParam("AID_EXT_ATT_UPDATE", Status);break;
		case AID_EXT_VEL_UPDATE:
			fdiSetParam("AID_EXT_VEL_UPDATE", Status);break;
		case AID_EXT_POS_UPDATE:
			fdiSetParam("AID_EXT_POS_UPDATE", Status);break;
		case AID_GNSS_VEL_UPDATE:
			fdiSetParam("AID_GNSS_VEL_UPDATE", Status);break;
		case AID_GNSS_POS_UPDATE:
			fdiSetParam("AID_GNSS_POS_UPDATE", Status);break;
		
		#if defined EPSILON_SERIES || defined DETA100_SERIES
		case AID_GNSS_DUAL_ANT_HEADING_UPDATE:
			fdiSetParam("AID_GNSS_DUAL_ANT_HEADING_UPDATE", Status);break;
		#if !defined DETA100_SERIES
		case AID_FFT_HEAVE_ENABLED:
			fdiSetParam("AID_FFT_HEAVE_ENABLED", Status);break;
		#endif
		#endif
		
		case AID_GNSS_TRACK_HEADING_UPDATE:
			fdiSetParam("AID_GNSS_TRACK_HEADING_UPDATE", Status);break;
		case AID_BRO_ALT_UPDATE:
			fdiSetParam("AID_BRO_ALT_UPDATE", Status);break;
		case AID_OPTICFLOW_UPDATE:
			fdiSetParam("AID_OPTICFLOW_UPDATE", Status);break;
		case AID_ZERO_RATE_UPDATE:
			fdiSetParam("AID_ZERO_RATE_UPDATE", Status);break;
		case AID_ZERO_VEL_UPDATE:
			fdiSetParam("AID_ZERO_VEL_UPDATE", Status);break;
		case AID_ZERO_POS_UPDATE:
			fdiSetParam("AID_ZERO_POS_UPDATE", Status);break;
		case AID_ODOMETER_VEL_UPDATE:
			fdiSetParam("AID_ODOMETER_VEL_UPDATE", Status);break;
		case AID_CAR_YZ_ZERO_VEL_NHC_ENABLED:
			fdiSetParam("AID_CAR_YZ_ZERO_VEL_NHC_ENABLED", Status);break;
		case AID_CAR_CENT_ACCEL_NHC_ENABLED:
			fdiSetParam("AID_CAR_CENT_ACCEL_NHC_ENABLED", Status);break;
		case AID_GYO_TRUN_ON_TARE_ENABLED:
			fdiSetParam("AID_GYO_TRUN_ON_TARE_ENABLED", Status);break;
	}
}
int fdiComConfigAIDmag3DMagetic(int Status)
{
	if(Status==Enable)
		{
	fdiComSetConfig();
	fdiComGetAIDmag3DMagetic();	
	fdiComSetAIDmag3DMagetic();	
	fdiSetSave();
	fdiSetReboot();
	USART2_RX_STA = 0;
	HAL_Delay(200);
	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
		}
		if(Status==Disable)
			{
				fdiComSetConfig();
				fdiSetSave();
				fdiSetReboot();
				HAL_Delay(1000);
				USART2_RX_STA = 0;
				HAL_Delay(200);
				HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
				while(huart1.gState != HAL_UART_STATE_READY){};
				int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
			if(res)
				return FDI_NO_ERROR;
			else
				return FDI_ERROR;
		}
}
int	fdiComGetAIDmag3DMagetic(void)
{
	HAL_UART_Transmit_IT(&huart2,"#fparam get AID_MAG_3D_MAGNETIC\r\n",sizeof("#fparam get AID_MAG_3D_MAGNETIC\r\n"));	
	HAL_Delay(1000);
}
int	fdiComSetAIDmag3DMagetic(void)
{
	HAL_UART_Transmit_IT(&huart2,"#fparam set AID_MAG_3D_MAGNETIC 1\r\n",sizeof("#fparam set AID_MAG_3D_MAGNETIC 1\r\n"));	
	HAL_Delay(1000);
}
int	fdiComGetAIDmag2DMagetic(void)
{
	HAL_UART_Transmit_IT(&huart2,"#fparam get AID_MAG_2D_MAGNETIC\r\n",sizeof("#fparam get AID_MAG_2D_MAGNETIC\r\n"));	
	HAL_Delay(1000);
}
int	fdiComSetAIDmag2DMagetic(void)
{
	HAL_UART_Transmit_IT(&huart2,"#fparam get AID_MAG_2D_MAGNETIC 1\r\n",sizeof("#fparam get AID_MAG_2D_MAGNETIC 1\r\n"));	
	HAL_Delay(1000);
}
int fdiComConfigProtocolType(int Status)
{
if(Status==Enable)
		{
	fdiComSetConfig();
	fdiComGetCOMStreamType();
	fdiComSetCOMStreamType();	
	fdiSetSave();
	fdiSetReboot();
	USART2_RX_STA = 0;
	HAL_Delay(200);
	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
	while(huart1.gState != HAL_UART_STATE_READY){};
	int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
	if(res)
		return FDI_NO_ERROR;
	else
		return FDI_ERROR;
	HAL_Delay(100);
		}
		if(Status==Disable)
			{
				fdiComSetConfig();
				fdiSetSave();
				fdiSetReboot();
				HAL_Delay(1000);
				USART2_RX_STA = 0;
				HAL_Delay(200);
				HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
				while(huart1.gState != HAL_UART_STATE_READY){};
				int res = strstr((char*)USART2_RX_BUF , "*#OK") != 0 ? 1 : 0;
			if(res)
				return FDI_NO_ERROR;
			else
				return FDI_ERROR;
		}
}
int	fdiComGetCOMStreamType(void)
{
	HAL_UART_Transmit_IT(&huart2,"#fparam get COMM_STREAM_TYP2 \r\n",sizeof("#fparam get COMM_STREAM_TYP2 \r\n"));	
	HAL_Delay(1000);
}
int	fdiComSetCOMStreamType(void)
{
	HAL_UART_Transmit_IT(&huart2," #fparam set COMM_STREAM_TYP2 5\r\n ",sizeof(" #fparam set COMM_STREAM_TYP2 5\r\n "));	
	HAL_Delay(1000);
}
void	fdiComGetVersionInformation(void)
{
	fdiGetPacket(FDILINK_VERSIONDATA_PACKET_ID);	
}









