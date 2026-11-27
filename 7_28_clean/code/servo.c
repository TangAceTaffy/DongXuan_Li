
#include "zf_common_headfile.h"
#include"math.h"
int16 error=0,integral=0,delta=0;  //偏差   上次偏差   积分   微分
int16 angle=0;    //舵机占空比输出

static int16 Last_error = 0;
float output;

float Kp=2.0 ;//大了比较切内弯
float Ki = 0;//未用到
float Kd = 2.0;//抑制抖动和预判弯道的效果
float Kd_d;//就是抑制抖动和抑制转向
float Kp_p;//大了大弯道和连续弯道转的更好
void servo_pid()
{
       error = position;		
       //输入参数E为error，EC为err的微分，即本次error-上次error
	   float E=0,EC=0;
       E  = position;
       EC = position - Last_error;
       Kp=2.00;
       Kp_p=0.100;//0.100
       Kd=0;//28 35
       Kd_d=0.0110;
       output = (Kp*E+Kp_p*E*ABS(E)+Kd*EC-Kd_d*imu660ra_gyro_z);//计算输出0.001
       angle = steeringPWM_MID + output;//舵机角度计算   右转弯output为负数
       angle = angle > angle_max ? angle_max:angle;
       angle = angle < angle_min ? angle_min:angle;
       pwm_set_duty(SERVO_MOTOR_PWM, angle);
       Last_error = error;//储存error的微分
}
