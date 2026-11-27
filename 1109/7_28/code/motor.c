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
float distance1=0;
float K_P =8;//36   110    12
float K_I =0.5;//1.3    9
float K_D =0.5;//0.9  0.6


int16 speed_actual = 0;
int16 speed_duty_L = 0;
int16 speed_duty_R = 0;
int16 speed_max = 7000;
int16 speed_min = 2000;
//左轮闭环
static float error_L = 0;
static float error_last_L = 0;
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
	error_last_L = error_L;
	if(speed_duty_L>=0)
	{
		speed_duty_L = speed_duty_L>speed_max?speed_max:speed_duty_L;
	}
	else
	{
		speed_duty_L = speed_duty_L<-speed_max?-speed_max:speed_duty_L;

	}
	Moto_L(speed_duty_L);
}
//右轮闭环
static float error_R = 0;
static float error_last_R = 0;
static float error_R_Sum=0;
void right_motor_pid(int16 goal)
{
	speed_actual = (Left_Encoder+Right_Encoder)/2;
	error_R = goal - Right_Encoder;
	error_R_Sum+=error_R;
	//限幅
	if(error_R_Sum>=5000) error_R_Sum=5000;
	speed_duty_R = (int)(K_P*error_R+K_I*error_R_Sum+K_D*(error_R-error_last_R));
	error_last_R = error_R;
	if(speed_duty_R>=speed_max)
	{
		speed_duty_R =speed_duty_R>speed_max?speed_max:speed_duty_R;
	}
	else if(speed_duty_R<speed_min)
	{
	    speed_duty_R =speed_duty_R<-speed_max?-speed_max:speed_duty_R;

	}
	Moto_R(speed_duty_R);
}

//获取编码器的值
void Get_Encoder(void)
{
//读取采集到的编码器脉冲数
    Left_Encoder =encoder_get_count(ENCODER_1);
    Right_Encoder = -1*encoder_get_count(ENCODER_2);
//计数器清零
        encoder_clear_count(TIM2_ENCODER);
        encoder_clear_count(TIM4_ENCODER);
    Average_Encoder = (Left_Encoder + Right_Encoder)*0.5;
//    endarch = 16-(speed_maximum-Average_Encoder)*0.01;//圆环早晚，数字越大越晚

    Sum_Encoder += Average_Encoder;
    distance += (Average_Encoder * 0.0088);

}
void Moto_R(int16 moto1)
{
    if(moto1>=0)
    {
        pwm_set_duty(ATOM1_CH0_P21_2,moto1);
        gpio_set_level(P21_3,1);
    }
    else
    {
        pwm_set_duty(ATOM1_CH0_P21_2,-moto1);
        gpio_set_level(P21_3,0);
    }
}
void Moto_L(int16 moto2)//红左黑右
{
    if(moto2>=0)     //正速
    {
        pwm_set_duty(ATOM1_CH2_P21_4,moto2);
        gpio_set_level(P21_5,1);
    }
    if(moto2<0)
    {
        pwm_set_duty(ATOM1_CH2_P21_4,-moto2);
        gpio_set_level(P21_5,0);
    }
}
