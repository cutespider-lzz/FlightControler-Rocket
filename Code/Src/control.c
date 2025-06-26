#include "control.h"

float ControlTime;
const float ControlDt = 0.01;

SemaphoreHandle_t ControlSemaphore;//控制模块二值信号量
BaseType_t ControlHigherTaskSwitch;

double Kp_roll=1,Kd_roll=0.2,Kp_pitch=2,Kd_pitch=0.1,Ki_pitch = 1,Kp_yaw=1.5,Kd_yaw=0.1;//姿态控制参数
//double Kp_roll=1,Kd_roll=0,Kp_pitch=2,Kd_pitch=0,Ki_pitch = 0,Kp_yaw=1.5,Kd_yaw=0;//姿态控制参数

double expected_roll,expected_pitch,expected_yaw,expected_height;//各通道期望值
double servo_roll,servo_pitch,servo_yaw;//对应通道角度
double integtal_roll,integtal_pitch;//俯仰角误差积分
const double	Kp_height=3;//高度控制率参数
FMUControlModeEnum FMUControlMode = FMU_Manual;//飞控工作模式选择
FMUControlModeEnum FMUControlModePrevious = FMU_Manual;

double pitch,roll,yaw,gx,gy,gz;
//	volatile double roll = AHRSData.Roll*57.3;
//	volatile double yaw = AHRSData.Heading*57.3;
//	volatile double gx = AHRSData.PitchSpeed;
//	volatile double gy = AHRSData.RollSpeed;
//	volatile double , = AHRSData.HeadingSpeed;

void ControlInit(void)//飞控开始工作
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
  __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim3);
}


void ControlStop(void)//飞控结束工作
{
	HAL_TIM_Base_Stop_IT(&htim3);
//	vTaskSuspend(SDWrite_TCB);
//	FileClose();
}


void ControlUpdata(void) {
    ControlTime += ControlDt;
    
    // 无论ControlTime的值如何，都触发信号量
    static uint8_t counter = 0;
    if (++counter >= 5) {  // 5 * 2ms = 10ms
        counter = 0;
        xSemaphoreGiveFromISR(ControlSemaphore, &ControlHigherTaskSwitch);
        portYIELD_FROM_ISR(ControlHigherTaskSwitch);
    }
}



void ServoSet(ServoChannel channel,double angle)//
{
	//漫游者舵机参数
	uint8_t ServoDirection[8] = {1,0,0,0,1,0,0,0};
	int16_t ServoOffset[8] = {0,100,0,-150,0,120,0,0};
	int16_t angle_int16;
	switch(channel)
	{
		case ServoChannel_1:
			if(ServoDirection[ServoChannel_1]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_1];
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,angle_int16);
			break;
		case ServoChannel_2:
			if(ServoDirection[ServoChannel_2]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_2];
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,angle_int16);
			break;
		case ServoChannel_3:
			if(ServoDirection[ServoChannel_3]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_3];
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,angle_int16);
			break;
		case ServoChannel_4:
			if(ServoDirection[ServoChannel_4]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_4];
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,angle_int16);
			break;
		case ServoChannel_5:
			if(ServoDirection[ServoChannel_5]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_5];
			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,angle_int16);
			break;
		case ServoChannel_6:
			if(ServoDirection[ServoChannel_6]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_6];
			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,angle_int16);
			break;
		case ServoChannel_7:
			if(ServoDirection[ServoChannel_7]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_7];
			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,angle_int16);
			break;
		case ServoChannel_8:
			if(ServoDirection[ServoChannel_8]) angle = -angle;
			angle_int16 = angle*11.1+1500+ServoOffset[ServoChannel_8];
			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,angle_int16);
			break;
	}
}



void MYZControl(void)
{
	pitch = AHRSData.Pitch*57.3;
	roll = AHRSData.Roll*57.3;
	yaw = AHRSData.Heading*57.3;
	gy = AHRSData.PitchSpeed;
	gx = AHRSData.RollSpeed;
	gz = AHRSData.HeadingSpeed;


			servo_roll = Kp_roll*roll;
			servo_roll = servo_roll>30?30:servo_roll;
			servo_roll = servo_roll<-30?-30:servo_roll;
			ServoSet(ServoChannel_1,servo_roll);
			ServoSet(ServoChannel_2,servo_roll);
			ServoSet(ServoChannel_3,servo_roll);
			ServoSet(ServoChannel_4,servo_roll);
	
}
