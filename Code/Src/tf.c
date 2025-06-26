#include "tf.h"

BYTE work[_MAX_SS];
FRESULT TFRet;
uint8_t TFWriteBuff[512];

void TFInit(void)
{
	TFRet = f_mount(&SDFatFS,SDPath,1);
	if(TFRet != FR_OK)
	{
		switch(TFRet)
		{
			case FR_NO_FILESYSTEM:
				TFRet = f_mkfs(SDPath,FM_FAT32,0,work,_MAX_SS);
				if(TFRet==FR_OK) 
				{
					TFRet = f_mount(&SDFatFS,SDPath,1);
					if(TFRet == FR_OK) ;
					else
					{
						while(1) ;
					}
				}
				break;
			default:
				while(1) ;
		}
	}
	else if(retSD == FR_OK) 
	{
		f_open(&SDFile,"TF test.txt",FA_WRITE|FA_OPEN_APPEND);
		f_printf(&SDFile,"TF write test!\n");
		f_close(&SDFile);
	}
}

void TFWrite(void)
{
	
}

