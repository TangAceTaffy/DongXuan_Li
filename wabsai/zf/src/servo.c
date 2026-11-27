
#include "zf_common_headfile.h"
#include"math.h"
struct pwm_info servo_pwm_info;
// 定义驱动路劲，该路劲由设备树生成


// 定义主板上舵机频率  请务必注意范围 50-300
// 如果要修改，需要直接修改设备树。
#define SERVO_MOTOR_FREQ            (servo_pwm_info.freq)                       

// 在设备树中，默认设置的10000。如果要修改，需要直接修改设备树。
#define PWM_DUTY_MAX                (servo_pwm_info.duty_max)      

// 定义主板上舵机活动范围 角度                                                     
                
int16_t error1=0,integral=0,delta=0,error2=0;  //偏差   上次偏差   积分   微分
int32_t angle=0;    //舵机占空比输出

static int16_t Last_error1 = 0;
static int16_t lasterror;//存储5位error值，使得判断过程更长
static int16_t lastservo[5];
static int Ls = 0;
static int Le = 0;

float output;

float Kp=3.3;
float Stright_Kp=1.5 ;//大了比较切内弯4
float Else_Kp=2.8;
float Kp_p=0.0    ;//大了大弯道和连续弯道转的更好0.01
float Kd = 0.01;//抑制抖动和预判弯道的效果0.1    
float Kd_d=0.016;//0.016
// float Str_Kd_d=0.014;//就是抑0制抖动和抑制转向0.014

// float Else_Kd_d=0.008;

float Round_Kp = 0;
int error_sum;
//float Ki;//未用到
int gyro;

void servo_pid()
{
       if(defineSR == 0){
               Kp=Else_Kp;
       }
       if(defineSR == 1){
               Kp=Stright_Kp;//直道p 
               
       }
       if(RoundProcess>=Find_Round&&RoundProcess<Into_Round) Kp=2;//R80:3
     

       error1 = position;
 
     


    
      

       //输入参数E为error，EC为err的微分，即本次error-上次error
	float E=0,EC=0;
       E  = error1;
       EC = error1 - lasterror;//position - Last_error;
       gyro=imu660ra_gyro_z;

       // if(RoundProcess>=Find_Round&&RoundProcess<Leave_Round) Kp_p=Round_Kp;
//        if(imu660ra_gyro_z>2000) gyro=2000;
//        if(imu660ra_gyro_z<-2000) gyro=-2000;


       output = ((Kp*E+Kp_p*E*ABS(E)+Kd*EC)+Kd_d*gyro);//计算输出0.001
       angle = steeringPWM_MID + output;//舵机角度计算   右转弯output为负数
       angle = angle > angle_max ? angle_max:angle;
       angle = angle < angle_min ? angle_min:angle;
       pwm_set_duty(SERVO_MOTOR1_PWM, angle);
       lasterror = error1;//储存error的微分  Last_error = error
    
       
}
