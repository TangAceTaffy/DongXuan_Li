
#include "zf_common_headfile.h"
#include"math.h"
int16 error=0,integral=0,delta=0,error2=0;  //偏差   上次偏差   积分   微分
int16 angle=0;    //舵机占空比输出

static int16 Last_error = 0;
static int16 lasterror[5];//存储5位error值，使得判断过程更长
static int16 lastservo[5];
static int Ls = 0;
static int Le = 0;

float output;

float Kp=4.0 ;//大了比较切内弯4
float Kp_p=0;//大了大弯道和连续弯道转的更好
float Kd = 0.2;//抑制抖动和预判弯道的效果0.1
float Kd_d=0.01;//就是抑制抖动和抑制转向0.01
//float Ki;//未用到


void servo_pid()
{
       Le = (Le + 1) % 5;
       Ls = (Ls + 1) % 5;

       error = position;
       error2 = position2;//车头往左负 舵机左边大
       lastservo[Ls] = error;
       if(ABS(error2)>30){

           error=error2;
       }


       //输入参数E为error，EC为err的微分，即本次error-上次error
	   float E=0,EC=0;
       E  = error;
       EC = error - lasterror[Le];//position - Last_error;
//       Kp=4.00;
//       Kp_p=0.100;//0.100
//       Kd=60;//28 35
//       Kd_d=0.0160;
       output = (Kp*E+Kp_p*E*ABS(E)+Kd*EC*ABS(EC)-Kd_d*imu660ra_gyro_z);//计算输出0.001
       angle = steeringPWM_MID + output;//舵机角度计算   右转弯output为负数
       angle = angle > angle_max ? angle_max:angle;
       angle = angle < angle_min ? angle_min:angle;


       pwm_set_duty(SERVO_MOTOR_PWM, angle);
       lasterror[Le] = error;//储存error的微分  Last_error = error
}
