#include "FDILink.h"
#include "string.h"
#include "main.h"
#include "fdilink_decode.h"
#include "FDI_config.h"
//----------------------------------------------------------------------//
//				          - FDI_LINK Function file                     -//
//----------------------------------------------------------------------//
extern uint8_t CRC8_Table(uint8_t* p, uint8_t counter);
extern uint16_t CRC16_Table(uint8_t* p, uint8_t counter);



//extern void fdiDecodeBuffer(int PACKET_ID,void* buf);
#ifndef FDI_ASSERT
#define FDI_ASSERT(x)
#endif
/**
  * @brief Reset the FDILink error status.
  * @param[in] FDILink Pointer to the FDILink status structure.
  */
void fdiErrorOccurred(FDILink_Status_t* FDILink)
{
	FDILink->RxStatus = FDILink_Frame_Start;
}
/**
  * @brief Insert a value into the FDILink buffer.
  * @param[in] FDILink Pointer to the FDILink status structure.
  * @param[in] value Value to be inserted.
  */
void fdiInsertBuffer(FDILink_Status_t* FDILink, uint8_t value)
{
	if (FDILink->RxDataLeft <= 0)
	{
		fdiErrorOccurred(FDILink);
		return;
	}
	if (FDILink->RxStatus != FDILink_Frame_Data)
	{
		fdiErrorOccurred(FDILink);
		return;
	}
	FDILink->Buffer[FDILink->BufferIndex++] = value;  //将元素放入队列尾部
	if (FDILink->BufferIndex >= 256)
	{
		fdiErrorOccurred(FDILink);
		return;
	}
	FDILink->RxDataLeft--;
}

/**
  * @brief Reset the struct.
  * @param[in] FDILink Pointer to the FDILink status structure.
	*	@return void.
  */
void fdiResetAll(FDILink_Status_t* FDILink)
{
	FDILink->RxStatus = FDILink_Frame_Start;
	FDILink->RxDataLeft = 0;
	FDILink->RxType = 0;
	FDILink->BufferIndex = 0;
	FDILink->TxNumber = 0;
}

/**
  * @brief Handle the running data received in the FDILink communication.
  * @param[in] FDILink Pointer to the FDILink status structure.
  * @param[in] value Received value.
	*	@return 0 for success, -3 if invalid RxStatus, -1 for error, 1 for complete frame received.
  */
int fdiRuningReceiveData(FDILink_Status_t* FDILink, uint8_t value)
{
	if (FDILink->RxStatus < FDILink_Frame_Start || FDILink->RxStatus > FDILink_Frame_End)
	{
		fdiErrorOccurred(FDILink);
		return -3;
	}
	FDILink->FDILink_Frame_Buffer[FDILink->RxStatus] = value;
	switch (FDILink->RxStatus)
	{
		case FDILink_Frame_Start:
			fdiResetAll(FDILink);
			if (value == FDILink_Connect_Flag)
			{
				return 0;
			}
			if (value != FDILink_STX_Flag)
			{
				fdiErrorOccurred(FDILink);
				return -1;
			}
			FDILink->RxStatus = FDILink_Frame_CMD;
			break;
		case FDILink_Frame_CMD:
			FDILink->RxType = value;
			FDILink->RxStatus = FDILink_Frame_Length;
			break;
		case FDILink_Frame_Length:
			FDILink->RxDataLeft = value;
			FDILink->RxStatus = FDILink_Frame_SerialNumber;
			break;
		case FDILink_Frame_SerialNumber:
			FDILink->RxNumber = value;
			FDILink->RxStatus = FDILink_Frame_CRC8;
			break;
		case FDILink_Frame_CRC8:
			FDILink->CRC8_Verify = value;
			if (CRC8_Table(FDILink->FDILink_Frame_Buffer, FDILink_Frame_CRC8) != FDILink->CRC8_Verify)
			{
				fdiErrorOccurred(FDILink);
				return -1;
			}
			if(FDILink->RxDataLeft == 0)
			{
				FDILink->RxStatus = FDILink_Frame_Start;
				return 1;
			}
			FDILink->RxStatus = FDILink_Frame_CRC16H;
			break;
		case FDILink_Frame_CRC16H:
			FDILink->CRC16_Verify = value;
			FDILink->RxStatus = FDILink_Frame_CRC16L;
			break;
		case FDILink_Frame_CRC16L:
			FDILink->CRC16_Verify = (FDILink->CRC16_Verify << 8) | value;
			FDILink->RxStatus = FDILink_Frame_Data;
			break;
		case FDILink_Frame_Data:
			if (FDILink->RxDataLeft)
			{
				fdiInsertBuffer(FDILink,value);
				if (FDILink->RxDataLeft == 0)
				{
					FDILink->RxStatus = FDILink_Frame_End;
				}
				break;
			}
			else
			{
				FDILink->RxStatus = FDILink_Frame_End;
			}

		case FDILink_Frame_End:
		{
			if (value != FDILink_EDX_Flag)
			{
				fdiErrorOccurred(FDILink);
				return -1;
			}
			uint16_t CRC16 = CRC16_Table(FDILink->Buffer, FDILink->BufferIndex);
			if (CRC16 != FDILink->CRC16_Verify)
			{
				fdiErrorOccurred(FDILink);
				return -1;
			}
			FDILink->RxStatus = FDILink_Frame_Start;
			return 1;
		}
		default:
			fdiErrorOccurred(FDILink);
			return -1;
	}
	return 0;
}

/**
  * @brief Check the data length in the FDILink buffer.
  * @param[in]  FDILink Pointer to the FDILink status structure.
  * @param[in]  len Expected data length.
	*	@return 0 for success, -1 for error.
  */
int fdiCheckBata(FDILink_Status_t* FDILink, uint8_t len)
{
	if (FDILink->BufferIndex != len)
	{
		fdiErrorOccurred(FDILink);
		return -1;
	}
	return 0;
}
/**
  * @brief Apply the effect based on the received FDILink data.
  * @param[in] FDILink Pointer to the FDILink status structure.
  */
void fdiEffectFeature(FDILink_Status_t* FDILink)
{
	fdiDecodeBuffer(FDILink->RxType,FDILink->Buffer);
}
/**
  * @brief Send a FDI link frame.
  * @param[in] type Frame type.
  * @param[in] len Length of the data buffer.	(0-255)
	* @param[in] type Frame type.
	* @param[in] FDILink Pointer to the FDILink status structure.
	*	@param[in] buf Pointer to the data buffer.
	* @return Number of bytes sent.
  */

int fdiComProtocolSend(FDILink_Status_t* FDILink, uint8_t type, uint8_t * buf, int len)
{
	uint8_t buffer[256];
	FDI_ASSERT(len < 248);
	buffer[FDILink_Frame_Start] = FDILink_STX_Flag;
	buffer[FDILink_Frame_CMD] = type;
	buffer[FDILink_Frame_Length] = len;
	buffer[FDILink_Frame_SerialNumber] = FDILink->TxNumber++;
	uint8_t CRC8 = CRC8_Table(buffer, FDILink_Frame_CRC8);
	buffer[FDILink_Frame_CRC8] = CRC8;
	if(len == 0)
	{
		//没有CRC16校验和结束符
		return Serial_Send(buffer,FDILink_Frame_CRC8 + 1);
	}
	else
	{
		uint8_t* buf_data = buffer + FDILink_Frame_Data;
		memcpy(buf_data,buf,len);
		uint16_t CRC16 = CRC16_Table(buf_data, len);
		buffer[FDILink_Frame_CRC16H] = (CRC16 >> 8);
		buffer[FDILink_Frame_CRC16L] = (CRC16 & 0xff);
		buffer[FDILink_Frame_End + len - 1] = FDILink_EDX_Flag;
		return Serial_Send(buffer,FDILink_Frame_End + len);
	}
}

/**
  * @brief Pack the data into the FDILink buffer for transmission.
  * @param[out] buffer Pointer to the buffer to store the packed data.
	* @param[in] FDILink Pointer to the FDILink status structure.
  * @param[in] len Length of the data buffer.	(0-255)
	* @param[in] type Data type.
	* @param[in] buf Pointer to the data buffer.
	*	@param[in] len Length of the data buffer.
	* @return Length of the packed data 
  */
int fdiComBufferTrans(uint8_t* buffer, FDILink_Status_t* FDILink, uint8_t type, void* buf, int len)
{
	FDI_ASSERT(len < 248);
	buffer[FDILink_Frame_Start] = FDILink_STX_Flag;
	buffer[FDILink_Frame_CMD] = type;
	buffer[FDILink_Frame_Length] = len;
	buffer[FDILink_Frame_SerialNumber] = FDILink->TxNumber++;
	uint8_t CRC8 = CRC8_Table(buffer, FDILink_Frame_CRC8);
	buffer[FDILink_Frame_CRC8] = CRC8;

	uint8_t* buf_data = buffer + FDILink_Frame_Data;
	//memcpy(buf_data,buf,len);
	for(int i = 0;i < len;i++)
	{
		buf_data[i] = ((uint8_t*)buf)[i];
	}
	uint16_t CRC16 = CRC16_Table(buf_data, len);
	buffer[FDILink_Frame_CRC16H] = (CRC16 >> 8);
	buffer[FDILink_Frame_CRC16L] = (CRC16 & 0xff);
	buffer[FDILink_Frame_End + len - 1] = FDILink_EDX_Flag;
	return FDILink_Frame_End + len;
}
/**
  * @brief Pack the data into a FDI link frame.
  * @param[out] buffer Pointer to the output buffer.
  * @param[in] FDILink Pointer to the FDILink status structure.
	* @param[in] type Frame type.
	* @param[in] buf Pointer to the data buffer.
	*	@param[in] len Length of the data buffer.
	* @return  Size of the packed frame.
  */
static inline int fdiPackRecelveData(FDILink_Status_t* FDILink, uint8_t value)
{
	FDI_ASSERT(FDILink->BootStatus == FDILink_Status_Running);
	uint8_t result = fdiRuningReceiveData(FDILink, value);
	if (result == 1)
	{
		fdiEffectFeature(FDILink);
	}
	return result;
}
/**
  * @brief Initialize the FDILink status structure.
	* @return return 0 (always).
  */
int fdiComProtocolInit(FDILink_Status_t* FDILink)
{
	FDILink->BufferIndex = 0;
	FDILink->BootStatus = FDILink_Status_Running;
	FDILink->RxStatus = FDILink_Frame_Start;
	for (int i = 0; i < 256; i++)
	{
		FDILink->Buffer[i] = 0;
	}
	return 0;
}
/**
  * @brief Receive data into the FDILink buffer.
  * @param[in] FDILink Pointer to the FDILink status structure.
	* @param[in] buf Pointer to the received data buffer.
	*	@param[in] len Length of the received data buffer.
	* @return return 0 (always).
  */

int fdiComProtocolReceive(FDILink_Status_t* FDILink, uint8_t * buf, int len)
{
	for(int i = 0;i < len;i++)
	{
		fdiPackRecelveData(FDILink, buf[i]);
	}
	return 0;
}


//static FDILink_Status_t _FDILink;
uint8_t p_buff[256];



/*!
 *  请求数据帧并解析，ID为要请求的数据帧ID编号。系统会返回当前时刻对应数据输出，如果该帧被设置为固定频率输出，则会持续输出。
 *  使用此指令会自动解析要获得的数据至构建好的结构体中，fdiDecodeBuffer中配置了部分数据包，用户可自行添加需要解析的数据包
 *	Request and analysis data frame.
 *	\param[out]	None
 *	\param[in]	ID - the data frame ID number to be requested.
 *	\return		FDI_NO_ERROR if we have entered configuration mode.
 */
int fdiGetPacket(uint8_t ID)
{
	
//	uint8_t buffer[4];
//	buffer[0] = ID;
//	buffer[1] = 0;
//	buffer[2] = 0;
//	buffer[3] = 0;
//	fdiComBufferTrans(p_buff, &_FDILink, 0xA0, buffer, sizeof(buffer));
//	for(int i =0;i<150;i++)
//	{
//		//请求ID发送
//			HAL_Delay(10);
//			HAL_UART_Transmit_IT(&huart1, p_buff, 12);
//		//接收ID数据
//		fdiComProtocolReceive(&_FDILink, USART2_RX_BUF, USART2_RX_STA);
//	}
//	return FDI_NO_ERROR;
}


/*!
 *  查询设备的安装方向
 *	Query the installation direction of the equipment.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have gotten the info.
 */
int fdiComGetAxis(void)
{
//	HAL_UART_Transmit_IT(&huart1,"#faxis\r\n",sizeof("#faxis\r\n"));
//	HAL_Delay(1000);
//	HAL_UART_Transmit_IT(&huart2,"#faxis\r\n",sizeof("#faxis\r\n"));
//	USART2_RX_STA = 0;
//	HAL_Delay(100);

//	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
//	while(huart1.gState != HAL_UART_STATE_READY){};
//	return FDI_NO_ERROR;
//	HAL_Delay(100);
}



/*!
 *  查询双天线航向与载体前向夹角（主天线到从天线为基线矢量正方向，从IMU正上方看去，顺时针为天线航向偏角的正方向）
 *	Query the included angle between dual antenna heading and carrier forward.
 *	\param[out]	None
 *	\param[in]	None
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComGetAnte(void)
{
//	HAL_UART_Transmit_IT(&huart1,"#fante\r\n",sizeof("#fante\r\n"));
//	HAL_Delay(1000);
//	HAL_UART_Transmit_IT(&huart2,"#fante\r\n",sizeof("#fante\r\n"));
//	USART2_RX_STA = 0;
//	HAL_Delay(100);

//	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
//	while(huart1.gState != HAL_UART_STATE_READY){};
//	return FDI_NO_ERROR;
//	HAL_Delay(100);
}


/*!
 *  读取GNSS设置参数，paramName为需要获取的参数名称
 *	Read parameters.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiGetDgnss(int DGNSS)
{
//	char* paramName;
//	memset(paramName, 0, strlen(paramName));
//	switch(DGNSS)
//	{
//		case QXWZ_DSK_KEY:
//			memcpy(paramName, "QXWZ_DSK_KEY", strlen("QXWZ_DSK_KEY"));break;
//		case QXWZ_DSK_SECRET:
//			memcpy(paramName, "QXWZ_DSK_SECRET", strlen("QXWZ_DSK_SECRET"));break;
//		case QXWZ_DEV_ID:
//			memcpy(paramName, "QXWZ_DEV_ID", strlen("QXWZ_DEV_ID"));break;
//		case QXWZ_DEV_TYPE:
//			memcpy(paramName, "QXWZ_DEV_TYPE", strlen("QXWZ_DEV_TYPE"));break;
//		case NTRIP_SVR_DOMAIN:
//			memcpy(paramName, "NTRIP_SVR_DOMAIN", strlen("NTRIP_SVR_DOMAIN"));break;
//		case NTRIP_SVR_PORT:
//			memcpy(paramName, "NTRIP_SVR_PORT", strlen("NTRIP_SVR_PORT"));break;
//		case NTRIP_ACCOUNT:
//			memcpy(paramName, "NTRIP_ACCOUNT", strlen("NTRIP_ACCOUNT"));break;
//		case NTRIP_PASSWORD:
//			memcpy(paramName, "NTRIP_PASSWORD", strlen("NTRIP_PASSWORD"));break;
//		case NTRIP_MOUNT:
//			memcpy(paramName, "NTRIP_MOUNT", strlen("NTRIP_MOUNT"));break;
//		case BASE_STATION_SOURCE:
//			memcpy(paramName, "BASE_STATION_SOURCE", strlen("BASE_STATION_SOURCE"));break;
//		case USR_AUTHEMTICATION:
//			memcpy(paramName, "USR_AUTHEMTICATION", strlen("USR_AUTHEMTICATION"));break;
//		case NET_INFO_IMEI:
//			memcpy(paramName, "NET_INFO_IMEI", strlen("NET_INFO_IMEI"));break;
//		case NET_INFO_CCID:
//			memcpy(paramName, "NET_INFO_CCID", strlen("NET_INFO_CCID"));break;
//	}
//	char send_buff[128];
//	sprintf(send_buff, "#fdgnss get %s\r\n", paramName);
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
//	HAL_Delay(1000);
//	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
//	USART2_RX_STA = 0;
//	HAL_Delay(100);

//	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
//	while(huart1.gState != HAL_UART_STATE_READY){};
//	return FDI_NO_ERROR;
//	HAL_Delay(100);
}



/*!
 *  读取参数，paramName为需要获取的参数名称
 *	Read parameters.
 *	\param[out]	None
 *	\param[in]	paramName - Parameter name to be obtained.
 *	\return		FDI_NO_ERROR if we have set the param.
 */
int fdiComGetParam(char* paramName)
{
//	char send_buff[128];
//	sprintf(send_buff, "#fparam get %s\r\n", paramName);
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)send_buff,strlen(send_buff));
//	HAL_Delay(1000);
//	HAL_UART_Transmit_IT(&huart2,(uint8_t*)send_buff,strlen(send_buff));
//	USART2_RX_STA = 0;
//	HAL_Delay(100);

//	HAL_UART_Transmit_IT(&huart1,USART2_RX_BUF,USART2_RX_STA);
//	while(huart1.gState != HAL_UART_STATE_READY){};
//	return FDI_NO_ERROR;
//	HAL_Delay(100);
}




