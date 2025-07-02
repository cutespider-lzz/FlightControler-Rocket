#include "control.h"
#include <math.h> 
#include "taskinit.h"

float ControlTime;
const float ControlDt = 0.01;

 
SemaphoreHandle_t ControlSemaphore;//控制模块二值信号量
BaseType_t ControlHigherTaskSwitch;

double Kp_roll=1,Kd_roll=0.2,Kp_pitch=2,Kd_pitch=0.1,Ki_pitch = 1,Kp_yaw=1.5,Kd_yaw=0.1;//姿态控制参数




///////////////////////2025/6.29start
double a_x,a_y,a_z;
double Kx1,Kx2,Kz1,Kz2,Kz3,Ky1,Ky2,Ky3,Kdc,Kydc;
double Ky_seek=3,Kz_seek=3;//比例导引率的K
double dservo_pitch,dservo_yaw,dgz,dgy,gz=0,gy=0;
double rou=1.17,V,V2,Q,g = 9.8;//西安的密度
double Ncy,Ny,Ncz,Nz;//指令过载和实际
double theta,psi,dtheta,dpsi;//定义弹道倾角和弹道偏角
double x,y,z,dx,dy,dz,xt=212,yt=0,zt=0,dxt=0,dyt=0,dzt=0;
double xr,yr,zr,Vrx,Vry,Vrz,dqgamma,dqlambda,r;
double Q_sample[6] = {14905.8000000000,13593.9883193053,10989.4013774509,9655.79019220484,3611.48649906317,1403.77471486764};//速度递减
double Kz1_sample[6] = {0.014902219037634,0.014070112039108,0.011820685724419,0.010192988309790,-0.012510685943559,-0.070230653720901};//动压正相关
double Kz2_sample[6] = {67.980028630672170,71.846636265750860,84.743776691322380,97.421037488305560,-65.017151859481220,-3.906321148451361};
double Kz3_sample[6] = {-0.073933754626083,-0.078436663810936,-0.090433487094310,-0.099085094883749,-0.248241327266784,-2.054362661488793};//动压正相关
double Ky1_sample[6] = {0.014902219037634,0.014070112039108,0.011820685724419,0.010192988309790,-0.012510685943559,-0.070230653720901};//动压正相关
double Ky2_sample[6] = {67.980028630672170,71.846636265750860,84.743776691322380,97.421037488305560,-65.017151859481220,-3.906321148451361};
double Ky3_sample[6] = {-0.073933754626083,-0.078436663810936,-0.090433487094310,-0.099085094883749,-0.248241327266784,-2.054362661488793};//动压正相关
double Kx1_sample[6] = {-0.024268090412232,-0.025367203980571,-0.028089290670664,-0.029878487991067,-0.047398332746910,-0.072392092009083};//动压正相关
double Kx2_sample[6] = {-5.496404707182840,-5.517173627413768,-5.569263603626163,-5.604020735260854,-5.968338299584944,-6.581527941884852};//动压正相关
double servo_roll=0,servo_pitch=0,servo_yaw=0,servo_pitchtest,servo_yawtest;//对应通道角度
double servo_1,servo_2,servo_3,servo_4;//对应通道角度

double linear_interp(double x[], double y[], int n, double xi) {
    if (xi >= x[0]) return y[0];
    if (xi <= x[n-1]) return y[n-1];
    
    for (int i = 0; i < n-1; i++) {
        if (xi <= x[i] && xi >= x[i+1]) {
            double slope = (y[i+1] - y[i]) / (x[i+1] - x[i]);
            return y[i] + slope * (xi - x[i]);
        }
    }
    return 0; // 默认返回
}

///////////////////////2025/6.29end

double expected_roll,expected_pitch,expected_yaw,expected_height;//各通道期望值
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
    ControlTime += 0.01f;  // 对应100ms间隔
    xSemaphoreGiveFromISR(ControlSemaphore, &ControlHigherTaskSwitch);
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

	double gz_prev;
	double gy_prev;

void MYZControl(void)
{

	gz_prev = gz;
	gy_prev = gy;
	
	pitch = AHRSData.Pitch*57.3;
	roll = AHRSData.Roll*57.3;
	yaw = AHRSData.Heading*57.3;
	
	gx = AHRSData.RollSpeed;
	gz = AHRSData.HeadingSpeed;
	gy = AHRSData.PitchSpeed;
	

	dgz = (gz - gz_prev) / 0.01;
	dgy = (gy - gy_prev) / 0.01;

	
	
	a_x = INSGPSData.BodyAcceleration_X;
	a_y = -INSGPSData.BodyAcceleration_Z;
	a_z = INSGPSData.BodyAcceleration_Y;
	


	Ny = a_y/g;//有侧滑角和攻角产生的误差,可能有问题，需要的是速度系下的过载
	Nz = a_z/g;
	

	//北东地坐标系直接对应-z,x,-y
	
	V2 = INSGPSData.Velocity_Down*INSGPSData.Velocity_Down+INSGPSData.Velocity_East*INSGPSData.Velocity_East+INSGPSData.Velocity_North*INSGPSData.Velocity_North;
//	V = sqrt(V2);
	Q = 0.5*rou*V2;
	
//	x = INSGPSData.Location_East;//东
//	y = -INSGPSData.Location_Down;//天
//	z = -INSGPSData.Location_North;//南
//	dx = INSGPSData.Velocity_East;
//	dy = -INSGPSData.Velocity_Down;
//	dz = -INSGPSData.Velocity_North;
/////////////////////////////////////////////////////测试用——start
	x = 0;//东
	y = 260;//天
	z = 0;//南
	dx = 46;
	dy = 0;
	dz = 0;
	V = sqrt(dx*dx+dy*dy+dz*dz);
	Ny=-0.5844;
	Nz=0;
	gz = 0;
	dgz = 0;
	gy = 0;
	dgy = 0;
/////////////////////////////////////////////////////测试用——end
	theta=atanf(dy/dx);//弧度制

	xr=xt-x; yr=yt-y; zr=zt-z;
	Vrx=dxt-dx; Vry=dyt-dy; Vrz=dzt-dz;
	
	//计算视线角速度
	dqgamma=((xr*xr+zr*zr)*Vry-yr*(xr*Vrx+zr*Vrz))/((xr*xr+yr*yr+zr*zr)*sqrt(xr*xr+zr*zr));
	dqlambda=(zr*Vrx-xr*Vrz)/(xr*xr+zr*zr);
	r = sqrt(xr*xr+yr*yr+zr*zr);
	
	Ncy=Ky_seek*dqgamma*V/g+cosf(theta);
  Ncz=-Kz_seek*dqlambda*V*cosf(theta)/g;
	
	//cal_roll
	Kx1 = linear_interp(Q_sample,Kx1_sample,6,Q);
	Kx2 = linear_interp(Q_sample,Kx2_sample,6,Q);
	servo_roll = Kx1*(Kx2*(roll/57.3)-gx);
	servo_roll = servo_roll>45/57.3?45/57.3:servo_roll;
	servo_roll = servo_roll<-45/57.3?-45/57.3:servo_roll;

	//cal_pitch
	Kz1 = linear_interp(Q_sample,Kz1_sample,6,Q);//原有yz轴和仿真的不一样，我自己转化的，建议确认正负
	Kz2 = linear_interp(Q_sample,Kz2_sample,6,Q);
	Kz3 = linear_interp(Q_sample,Kz3_sample,6,Q);
	Kdc = 1+g/(Kz3*V);
	dservo_pitch = Kz1*Kz2*Kz3*(Kdc*Ncy-Ny)-Kz1*Kz2*gz-Kz1*dgz;
	servo_pitch = servo_pitch + dservo_pitch*ControlDt;
	servo_pitch = servo_pitch;
	servo_pitchtest = servo_pitch;
	servo_pitch = servo_pitch>16/57.3?16/57.3:servo_pitch;
	servo_pitch = servo_pitch<-16/57.3?-16/57.3:servo_pitch;
	
	
	
	
	//call_pew
	Ky1 = linear_interp(Q_sample,Ky1_sample,6,Q);
	Ky2 = linear_interp(Q_sample,Ky2_sample,6,Q);
	Ky3 = linear_interp(Q_sample,Ky3_sample,6,Q);
	Kydc = 1-g/(Ky3*V)*cosf(theta);
	dservo_yaw = Ky1*Ky2*Ky3*(Kydc*Ncz-Nz)-Ky1*Ky2*gy-Ky1*dgy;
	servo_yaw = servo_yaw + dservo_yaw*ControlDt;
	servo_yaw = servo_yaw;
	servo_yawtest = servo_yaw;
	servo_yaw = servo_yaw>16/57.3?16/57.3:servo_yaw;
	servo_yaw = servo_yaw<-16/57.3?-16/57.3:servo_yaw;
	
	
/////////////////////////////////////////////////////测试用——start	

	
	servo_pitch = 0;
	servo_yaw = 0;
//	servo_roll = 0;
///////////////////////////////////////////////////测试用——end
	servo_1 = (servo_roll+servo_yaw)*57.3;
	servo_2 = (servo_roll+servo_pitch)*57.3;
	servo_3 = (servo_roll+servo_yaw)*57.3;
	servo_4 = (servo_roll-servo_pitch)*57.3;

	ServoSet(ServoChannel_1,servo_1);
	ServoSet(ServoChannel_2,servo_2);
	ServoSet(ServoChannel_3,servo_3);
	ServoSet(ServoChannel_4,servo_4);

	
}
