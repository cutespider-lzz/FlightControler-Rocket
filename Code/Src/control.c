#include "control.h"

float ControlTime;
const float ControlDt = 0.01f;

SemaphoreHandle_t ControlSemaphore;//控制模块二值信号量
BaseType_t ControlHigherTaskSwitch;

//double Kp_roll=1,Kd_roll=0.2,Kp_pitch=2,Kd_pitch=0.1,Ki_pitch = 1,Kp_yaw=1.5,Kd_yaw=0.1;//姿态控制参数
double Kp_roll=1,Kd_roll=0,Kp_pitch=2,Kd_pitch=0,Ki_pitch = 0,Kp_yaw=1.5,Kd_yaw=0;//姿态控制参数

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
	__HAL_TIM_SET_COUNTER(&htim3,0);
	__HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);
	ControlTime = 0;
	HAL_TIM_Base_Start_IT(&htim3);
}



void ControlStop(void)//飞控结束工作
{
	HAL_TIM_Base_Stop_IT(&htim3);
//	vTaskSuspend(SDWrite_TCB);
//	FileClose();
}


void ServoSet(ServoChannel channel,double angle)//
{
	//漫游者舵机参数
	uint8_t ServoDirection[8] = {1,0,0,0,1,0,0,0};
	int16_t ServoOffset[8] = {0,0,0,-60,0,120,0,0};
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
	roll = AHRSData.Roll*57.3-1.45;
	yaw = AHRSData.Heading*57.3;
	gy = AHRSData.PitchSpeed;
	gx = AHRSData.RollSpeed;
	gz = AHRSData.HeadingSpeed;
//	volatile double pitch = AHRSData.Pitch*57.3;
//	volatile double roll = AHRSData.Roll*57.3;
//	volatile double yaw = AHRSData.Heading*57.3;
//	volatile double gx = AHRSData.PitchSpeed;
//	volatile double gy = AHRSData.RollSpeed;
//	volatile double gz = AHRSData.HeadingSpeed;

	volatile double pitch = AHRSData.Pitch*57.3;
	volatile double roll = AHRSData.Roll*57.3;
	volatile double yaw = AHRSData.Heading*57.3;
	double gx = AHRSData.PitchSpeed;
	double gy = AHRSData.RollSpeed;
	double gz = AHRSData.HeadingSpeed;

	switch(FMUControlMode)
	{
		case FMU_Manual:
		{
			//第一组舵机
			expected_roll = (ReceiverChannel[0]-ReceiverChannelNeutral[0])*0.09;
			expected_pitch = (ReceiverChannel[1]-ReceiverChannelNeutral[1])*0.09;
			expected_yaw = (ReceiverChannel[3]-ReceiverChannelNeutral[3])*0.09;
			servo_roll = expected_roll;//漫游者
			servo_pitch = expected_pitch;
			servo_yaw = expected_yaw;
			ServoSet(ServoChannel_1,servo_roll);
			ServoSet(ServoChannel_5,servo_roll);
			ServoSet(ServoChannel_2,servo_pitch);
			ServoSet(ServoChannel_6,servo_pitch);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,ReceiverChannel[2]);
			ServoSet(ServoChannel_4,servo_yaw);
			ServoSet(ServoChannel_7,servo_yaw);
			break;
		}
		case FMU_Stable:
		{
			//滚转与俯仰角期望值 0.09为45°
			expected_roll = (ReceiverChannel[0]-ReceiverChannelNeutral[0])*0.09;
			expected_pitch = -(ReceiverChannel[1]-ReceiverChannelNeutral[1])*0.06;//输入期望俯仰角
			expected_yaw = (ReceiverChannel[3]-ReceiverChannelNeutral[3])*0.015;
			//计算俯仰角误差积分
			integtal_pitch = integtal_pitch+(expected_pitch-pitch)*ControlDt;
      integtal_pitch = integtal_pitch>10?10:integtal_pitch;
      integtal_pitch = integtal_pitch<-10?-10:integtal_pitch;
			//计算舵机角度
//			servo_roll = Kp_roll*(expected_roll-roll)-Kd_roll*IMUData.tran_gyr_y;
			servo_roll = Kp_roll*(expected_roll-roll)-Kd_roll*gx;//漫游者
			servo_roll = servo_roll>45?45:servo_roll;
			servo_roll = servo_roll<-45?-45:servo_roll;
//			servo_pitch = Kp_pitch*(expected_pitch-pitch)-Kd_pitch*IMUData.tran_gyr_x+Ki_pitch*integtal_pitch;
			servo_pitch = Kp_pitch*(expected_pitch-pitch)-Kd_pitch*gy+Ki_pitch*integtal_pitch;
			servo_pitch = servo_pitch>16?16:servo_pitch;
			servo_pitch = servo_pitch<-16?-16:servo_pitch;
			servo_pitch= -servo_pitch;//机体到舵的转换
			servo_yaw = expected_yaw;
			ServoSet(ServoChannel_1,servo_roll);
			ServoSet(ServoChannel_5,servo_roll);
			ServoSet(ServoChannel_2,servo_pitch);
			ServoSet(ServoChannel_6,servo_pitch);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,ReceiverChannel[2]);
			ServoSet(ServoChannel_4,servo_yaw);
			ServoSet(ServoChannel_7,servo_yaw);
			break;
		}
		case FMU_Height:
		{
			//滚转与俯仰角期望值
			expected_height = expected_height - ((ReceiverChannel[1]-ReceiverChannelNeutral[1]))*3.0/50000.0;
			expected_roll = (ReceiverChannel[0]-ReceiverChannelNeutral[0])*0.09;
			expected_pitch = Kp_height*(expected_height-Geodetic_Position_data.Height)+fabs(roll)*0.3;
			expected_yaw = (ReceiverChannel[3]-ReceiverChannelNeutral[3])*0.015;
			//限制俯仰角上下限
			expected_pitch = expected_pitch>30?30:expected_pitch;
			expected_pitch = expected_pitch<-30?-30:expected_pitch;
			//计算俯仰角误差积分
			integtal_pitch = integtal_pitch+(expected_pitch-pitch)*ControlDt;
      integtal_pitch = integtal_pitch>10?10:integtal_pitch;
      integtal_pitch = integtal_pitch<-10?-10:integtal_pitch;
			//计算舵机角度
//			servo_roll = Kp_roll*(expected_roll-roll)-Kd_roll*IMUData.tran_gyr_y;
			servo_roll = Kp_roll*(expected_roll-roll)-Kd_roll*gx;//漫游者
			servo_roll = servo_roll>30?30:servo_roll;
			servo_roll = servo_roll<-30?-30:servo_roll;
//			servo_pitch = Kp_pitch*(expected_pitch-pitch)-Kd_pitch*IMUData.tran_gyr_x+Ki_pitch*integtal_pitch;
			servo_pitch = Kp_pitch*(expected_pitch-pitch)-Kd_pitch*gy+Ki_pitch*integtal_pitch;
			servo_pitch = -servo_pitch;//机体到舵的转换
			servo_pitch = servo_pitch>16?16:servo_pitch;
			servo_pitch = servo_pitch<-16?-16:servo_pitch;
			servo_yaw = expected_yaw;
			ServoSet(ServoChannel_1,servo_roll);
			ServoSet(ServoChannel_5,servo_roll);
			ServoSet(ServoChannel_2,servo_pitch);
			ServoSet(ServoChannel_6,servo_pitch);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,ReceiverChannel[2]);
			ServoSet(ServoChannel_4,expected_yaw);
			ServoSet(ServoChannel_7,expected_yaw);
			break;
		}
	}
}

