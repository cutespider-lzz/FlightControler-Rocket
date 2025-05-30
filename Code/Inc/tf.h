#ifndef __TF_H
#define __TF_H

#include "fatfs.h"

extern BYTE work[];
extern FRESULT TFRet;
extern uint8_t TFWriteBuff[];


void TFInit(void);//TF卡初始化函数
void TFWrite(void);//TF卡写入函数

#endif
