/*!
 *	\file		FDI_send.h
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

#ifndef __FDI_SEND_H
#define __FDI_SEND_H

void fdiUsart2UserSentInstruction(void);
void fdiDecodeBuffer(int PACKET_ID,void* buf);
void fdiComInterfaceDisplay(void);
void fdiSendSLAM1Datapacke(void);															//发送外部SLAM1数据包
int fdiSendExternalData(int type, void* buffer, int length);	//发送外部数据包
#endif

