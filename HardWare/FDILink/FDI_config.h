/*!
 *	\file		FDI_config.h
 *  \author		FDISYSTEMS 
 *	\date		05 February 2023
 *
 *	\brief		Contains main FDILink methods.
 *
 *	\section CodeCopyright Copyright Notice 
 *	Copyright (C) 2018-2023, FDISYSTEMS  . All rights reserved.
 *	
 *	This source code is intended for use only by FDISYSTEMS and
 *	those that have explicit written permission to use it from
 *	FDISYSTEMS.
 *	
 *	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 *	PARTICULAR PURPOSE.
 */

/*!
 *	\mainpage FDISYSTEMS Communication library documentation
 *	Welcome to the FDILink library documentation.<br>
 *	This documentation describes all functions implemented in the FDILink library.
 */
#ifndef __FDI_CONFIG_H
#define __FDI_CONFIG_H
#include "FDILink.h"

void fdiResetAll(FDILink_Status_t* FDILink);				//全部回到原始状态
void fdiComGetVersionInformation(void);							//获取固件信息

int fdiComSetConfig(void);															//准备进入配置模式						
int fdiEnterSetConfig(void);														//进入配置模式
int fdiSetDeconfig(void);																	//退出配置模式
int fdiSetReboot(void);																		//重启设备
int fdiSetReset(void);																		//恢复出厂设置
int fdiSetSave(void);																			//保存配置
int fdiComSetConfigAxis(char* flip, int rot);							//设置设备的安装方向
int fdiComSetConfigAnteHeadbias(int angle);									//配置双天线航向偏角
int fdiComSetConfigAnteBaseline(int length);									//配置双天线之间的基线长度
int fdiSetParam(char* paramName, float paramValue);				//配置参数
int fdiComSetConfigBaud(int COM, int BAUD);								//配置设备数据口的波特率
int fdiComSetConfigType(int COM, int Type);								//配置设备数据口的功能
int fdiComSetConfigUserDefine(int type, float num);				//配置USER_DEFINE数据
int fdiComSetConfigGPIOs(int GPIO, int Fun);							//配置GPIOs功能
int fdiComSetConfigAID(int AID, int Status);							//配置AID开关
int fdiComSetConfigAnteArm(int x, int y, int z);							//配置GNSS主天线到IMU杆臂的坐标
int fdiComSetConfigImucailed(int num);										//配置调平，校准陀螺仪、加表的零偏
int fdiComSetConfigPacketSentMsg(char* msg, int freq);				//配置发送的数据包内容及频率
int fdiComSetDgnss(int DGNSS, char* paramValue);//配置GNSS设置参数
int fdiComConfigAIDmag3DMagetic(int Status);
int	fdiComGetAIDmag3DMagetic(void);
int	fdiComSetAIDmag3DMagetic(void);

#endif
