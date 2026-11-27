/*
 * motor.c
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#include "zf_common_headfile.h"
#include "motor.h"
#include "math.h"
int16 Left_Encoder = 0;     //左编码器的值
int16 Right_Encoder = 0;    //右编码器的值
float Average_Encoder = 0;  //左右编码器平均值
float Sum_Encoder = 0;      //编码器脉冲和
float distance = 0;         //车子行走的路程
float K_P =8;//36   110    12
float K_I =0.5;//1.3    9
float K_D =0.5;//0.9  0.6
//float d_kp = 6.0;
//float d_kd = 1.5;
//float a_kp = 6.0;
//float a_kd = 2.5;
int16 Right_Duty = 0;
int16 Left_Duty = 0;
int16 mspeed = 20;
int16 Send_Count=0;

////定义差速模型
//#define LDISTANCE 200 //车身的前后轮中心距mm
//#define BORDWIDTH 150 //两后轮中心距mm
//#define A 1.05 //差速的大小系数
//#define K 1.06 //差速预知系数 K越大差速越提前
//#define AK 1   

////差速函数
//#define steering_PWM sevro_ctl
//#define steeringPWM_MID sevro_mid

//float g_Control=0,g_Control_last=0,g_Control_pre=0,casu_weight=0.38;//1.29;//?0.6

//extern uint16 sevro_mid;
//extern uint16 sevro_ctl;


//float k_white_40col=0;
//float casu_weight_base=0.4;
//extern float  white_num_40col_min;
//extern float  white_num_40col_max;
///*********************************************/
//float Get_Dire(uint8 i)
//{
//  g_Control=-(steering_PWM-steeringPWM_MID);
//  
//  float tn=tan(g_Control/54.95*casu_weight); //54.95=70*0.785
//  if(i) //左轮
//  {      
//    return (A*(K-0.5*BORDWIDTH*tn/LDISTANCE*AK));
//    
//   // return 1;
//  }
//  
//  //右轮
//    return (A*(K+0.5*BORDWIDTH*tn/LDISTANCE*AK));
//  //return 0;
//}




////左轮闭环
//int16 error_z = 0;
//int16 last_error_L = 0;
//int16 last_last_error_L = 0;
//void left_motor_pid(int16 goal)
//{
//    error_z = goal - Left_Encoder;
//    Left_Duty+=K_P*(error_z-last_error_L)+K_I*error_z+K_D*(error_z-2*last_error_L+last_last_error_L);
//    last_error_L = error_z;
//    last_last_error_L = last_error_L;
//    Left_Duty = Left_Duty>5000 ? 5000:Left_Duty;
//    Left_Duty = Left_Duty<-5000? -5000:Left_Duty;
//}
////右轮闭环
//int16 error_y = 0;
//int16 last_error_R = 0;
//int16 last_last_error_R = 0;
//void right_motor_pid(int16 goal)
//{
//    static int16 error,last_error=0,last_last_error=0,Goal_speed;
//      lcd_showint16(0,6,error);
//      lcd_showint16(0,7,last_error);
//      lcd_showint16(0,8,last_last_error);
//    Goal_speed = goal;
//    error_y = goal - Right_Encoder;
//    Right_Duty+=K_P*(error_y-last_error_R)+K_I*error_y+K_D*(error_y-2*last_error_R+last_last_error_R);
//    last_error_R = error_y;
//    last_last_error_R = last_error_R;
//    Right_Duty = Right_Duty>5000 ? 5000:Right_Duty;
//    Right_Duty = Right_Duty<-5000 ? -5000:Right_Duty;
//    Moto_R(Right_Duty);
//}
//500
int16 speed_actual = 0;
int16 speed_duty_L = 0;
int16 speed_duty_R = 0;

int16 speed_limit = 9000;
//左轮闭环
static float error_L = 0;
static float error_last_L = 0;
static float error_last_last_L = 0;
static float error_L_Sum=0;

void left_motor_pid(int16 goal)
{
    //output = ( Kp*E+Kd*(EC) );//计算输出
	speed_actual = (Left_Encoder+Right_Encoder)/2;
	error_L = goal - Left_Encoder;
	error_L_Sum+=error_L;
	//限幅
	if(error_L_Sum>=5000) error_L_Sum=5000;
	speed_duty_L = (int)(K_P*error_L+K_I*error_L_Sum+K_D*(error_L-error_last_L));
	//error_last_last_L = error_last_L;
	error_last_L = error_L;
	if(speed_duty_L>=0)
	{
		speed_duty_L = speed_duty_L>speed_limit?speed_limit:speed_duty_L;
	}
	else
	{
		speed_duty_L = speed_duty_L<-speed_limit?-speed_limit:speed_duty_L;
	}
	Moto_L(speed_duty_L);
}
//右轮闭环
static float error_R = 0;
static float error_last_R = 0;
static float error_last_last_R = 0;
static float error_R_Sum=0;
void right_motor_pid(int16 goal)
{
	speed_actual = (Left_Encoder+Right_Encoder)/2;
	error_R = goal - Right_Encoder;
	error_R_Sum+=error_R;
	//限幅
	if(error_R_Sum>=5000) error_R_Sum=5000;
	speed_duty_R = (int)(K_P*error_R+K_I*error_R_Sum+K_D*(error_R-error_last_R));
	//error_last_last_R = error_last_R;
	error_last_R = error_R;
	if(speed_duty_R>=0)
	{
		speed_duty_R = speed_duty_R>speed_limit?speed_limit:speed_duty_R;
	}
	else
	{
		speed_duty_R = speed_duty_R<-speed_limit?-speed_limit:speed_duty_R;
	}
	Moto_R(speed_duty_R);
}

//static int16 dir_err_last = 0;
//int16 dir_out = 0;
//int16 gyro_real = 0;
//int16 gyro_expect = 0;
//int16 gyro_err = 0;
//static int16 gyro_err_last = 0;
//int gyro_out = 0;
//void dir_angle(int16 position)
//{
//    gyro_expect = d_kp * position + d_kd * dir_err_last;
//    dir_err_last = position;
//    icm20602_gyro_z = 0.5*icm20602_gyro_z;
//    if(icm20602_gyro_z>=0)
//    {
//        gyro_real = icm20602_gyro_z > 1?icm20602_gyro_z:0;
//    }
//    if(icm20602_gyro_z<0)
//    {
//        gyro_real = icm20602_gyro_z < -1?icm20602_gyro_z:0;
//    }
//    gyro_err = -gyro_expect - gyro_real;
//    gyro_out = a_kp * gyro_err + a_kd * gyro_err_last;
//    gyro_out = gyro_out>10000 ? 10000:gyro_out;
//    gyro_out = gyro_out<-10000 ? -10000:gyro_out;
//    gyro_err_last = gyro_err;
//    set_pwm_dir(gyro_out);
//}



//void set_pwm_dir(int gyro_out)
//{
//    if(gyro_out>=0)
//    {
//        pwm_set_duty(TIM5_PWM_CH4_A3,gyro_out);
//        pwm_set_duty(TIM5_PWM_CH1_A0,gyro_out);
//
//    }
//    if(gyro_out<0)
//    {
//        pwm_set_duty(TIM5_PWM_CH3_A2,-gyro_out);
//        pwm_set_duty(TIM5_PWM_CH2_A1,-gyro_out);
//    }
//}








//获取编码器的值
void Get_Encoder(void)
{
//读取采集到的编码器脉冲数
    Left_Encoder =encoder_get_count(ENCODER_1);
    Right_Encoder = -1*encoder_get_count(ENCODER_2);
//计数器清零
    //    encoder_clear_count(ENCODER_1);
    //    encoder_clear_count(ENCODER_2);
        encoder_clear_count(TIM2_ENCODER);
        encoder_clear_count(TIM4_ENCODER);
    Average_Encoder = (Left_Encoder + Right_Encoder)*0.5;
    Sum_Encoder += Average_Encoder;
    distance += (Average_Encoder * 0.0088);
    if(distance == 100)
    {
        mspeed = 0;
    }
}
void Moto_R(int16 moto1)
{
    if(moto1>=0)
    {
//        gpio_set_level(A2, 0);
//        pwm_set_duty(TIM5_PWM_CH4_A3,moto1);
        pwm_set_duty(ATOM1_CH0_P21_2,moto1);
        gpio_set_level(P21_3,1);
    }
    else
    {
//        gpio_set_level(A2, 1);
//        pwm_set_duty(TIM5_PWM_CH4_A3,-moto1);
        pwm_set_duty(ATOM1_CH0_P21_2,-moto1);
        gpio_set_level(P21_3,0);
    }
}
void Moto_L(int16 moto2)//红左黑右
{
    if(moto2>=0)     //正速
    {
//        gpio_set_level(A0, 0);
//        pwm_set_duty(TIM5_PWM_CH2_A1,moto2);
        pwm_set_duty(ATOM1_CH2_P21_4,moto2);
        gpio_set_level(P21_5,1);
    }
    if(moto2<0)
    {
//        gpio_set_level(A0, 1);
//        pwm_set_duty(TIM5_PWM_CH2_A1,-moto2);
        pwm_set_duty(ATOM1_CH2_P21_4,-moto2);
        gpio_set_level(P21_5,0);
    }
}
void set_pwm(int16 moto1,int16 moto2)
{
    Moto_L(moto1);
    Moto_R(moto2);
}

/****************************************
               ????
****************************************/
void Speed_Differential_akm_calculation(int temSpeed)
{
	float left_akm=Get_Dire(1);
	float right_acm=Get_Dire(0);
	left_motor_pid(left_akm*temSpeed);
	right_motor_pid(right_acm*temSpeed);
}
uint8 Differential_coefficient_flag=0;
double serve_out;
void Speed_Differential_calculation(int temSpeed)//??????????
{
       float  C_left_speed=0.0,C_right_speed=0.0;//???????
       float  Differential_coefficient=0;  //????
       serve_out= angle-steeringPWM_MID;
       if(serve_out>25||serve_out<-25)
       {
          Differential_coefficient=0.5;//原来：0.068 0.088 0.5 0.36
          Differential_coefficient_flag++;
       }
       else if(serve_out<20||serve_out>-20)

       {
         Differential_coefficient=0;
         Differential_coefficient_flag=0;
       }
//
       else
       {
          Differential_coefficient=0.000*serve_out;
          Differential_coefficient_flag=0;
       }

       if(serve_out>= 0)//弯道速度
       {
          C_left_speed  =1.0* temSpeed  *  (1.0-Differential_coefficient);    //????<1
          C_right_speed =1.0* temSpeed  *  (1.0+Differential_coefficient);    //????>1
       }
       else if(serve_out< 0)
       {
          C_left_speed  =1.0* temSpeed  *  (1.0+Differential_coefficient);       /////////
          C_right_speed =1.0* temSpeed  *  (1.0-Differential_coefficient);       //////////
       }
       //Closed_Loop(C_left_speed,C_right_speed);
		left_motor_pid(C_left_speed);
		right_motor_pid(C_right_speed);
}
//变速运动
void Changable_Speed(int Max_Speed,int Min_Speed)
{
    //理想速度=最大速度-(最大速度-最小速度)*abs(转角值/最大转角值);
    int Real_Speed;
    Real_Speed=Max_Speed-(Max_Speed-Min_Speed)*ABS((steeringPWM_MID-angle)/(steeringPWM_MID-angle_min));
    right_motor_pid(Real_Speed);
    left_motor_pid(Real_Speed);
}
