#ifndef __CONTROL_H 
#define __CONTROL_H

#include "main.h"
#include "cmsis_os.h"
#include "navigation.h"
#include "receiver.h"

typedef enum
{
	ServoChannel_1 = 0,
	ServoChannel_2,
	ServoChannel_3,
	ServoChannel_4,
	ServoChannel_5,
	ServoChannel_6,
	ServoChannel_7,
	ServoChannel_8,
}ServoChannel;

typedef enum
{
	FMU_Manual,
	FMU_Stable,
	FMU_Height,
	FMU_Path,
	FMU_Return
}FMUControlModeEnum;

extern float ControlTime;
extern const float ControlDt;

extern SemaphoreHandle_t ControlSemaphore;//控制模块二值信号量
extern BaseType_t ControlHigherTaskSwitch;

extern double Kp_roll,Ki_roll,Kd_roll,Kp_pitch,Ki_pitch,Kd_pitch,Kp_yaw,Ki_yaw,Kd_yaw;//姿态控制参数
extern double expected_roll,expected_pitch,expected_yaw,expected_height;//各通道期望值
extern double servo_roll,servo_pitch,servo_yaw;//对应通道角度
extern double integtal_roll,integtal_pitch;//俯仰角误差积分
extern const double	Kp_height;//高度控制率参数
extern FMUControlModeEnum FMUControlMode;//飞控工作模式选择
extern FMUControlModeEnum FMUControlModePrevious;



void ServoSet(ServoChannel channel,double angle);
void ControlInit(void);
void ControlStop(void);
void MYZControl(void);

#endif

