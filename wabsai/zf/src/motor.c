/*
 * motor.c
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#include "zf_common_headfile.h"
#include "math.h"
int16_t Left_Encoder = 0;     //左编码器的值
int16_t Right_Encoder = 0;    //右编码器的值
float Average_Encoder = 0;  //左右编码器平均值
float Sum_Encoder = 0;      //编码器脉冲和
float distance = 0;         //车子行走的路程
float distance1=0;
float K_P =10;//14
float K_I =6;//2
float K_D =0;//2.4



int16_t speed_actual = 0;
int16_t speed_duty_L = 0;
int16_t speed_duty_R = 0;

int16_t speed_max = 10000;	//10000
int16_t speed_min = -10000;	
//左轮闭环
static float error_L = 0;
static float error_last_L = 0;
static float error_L_Sum=0;
void left_motor_pid(int16_t goal)
{
    //output = ( Kp*E+Kd*(EC) );//计算输出
	speed_actual = (Left_Encoder+Right_Encoder)/2;
	error_L = goal - Left_Encoder;
	error_L_Sum+=error_L;
	//限幅
	if(error_L_Sum>=3000) {
		error_L_Sum=3000;
		// printf("\n99999999999999\n99999999999999999\n999999999999999\n999999999999\n9999999999999999\n9999999999999999999\n999999999999999999\n99999999999999999\n999999999999999\n");
	}
	speed_duty_L = (int)(K_P*error_L+K_I*error_L_Sum+K_D*(error_L-error_last_L));
	error_last_L = error_L;

	// if(Left_Encoder>400){
	// for(int i=400;i<=Left_Encoder;i+=2){
	// 	if(i>goal-2 && i<goal+2)
	// 		printf("I");
	// 	else
	// 		printf(" ");
	// }}
	// printf("%d\n",Left_Encoder);


	if(speed_duty_L>=speed_max)
	{
		speed_duty_L = speed_max;//speed_duty_L>speed_max?speed_max:speed_duty_L;
	}
	else if(speed_duty_L<speed_min)
	{
		speed_duty_L = speed_min;//speed_duty_L<-speed_max?-speed_max:speed_duty_L;

	}
	// printf("Left_Encoder= %hd    speed_duty_L= %hd    error_L= %f\n",Left_Encoder,speed_duty_L,error_L);

	Moto_L(speed_duty_L);
}
//右轮闭环
static float error_R = 0;
static float error_last_R = 0;
static float error_R_Sum=0;
void right_motor_pid(int16_t goal)
{
	speed_actual = (Left_Encoder+Right_Encoder)/2;
	error_R = goal - Right_Encoder;
	error_R_Sum+=error_R;
	//限幅
	if(error_R_Sum>=3000) {
		error_R_Sum=3000;
		// printf("\nR99999999999999\nR99999999999999999\nR999999999999999\nR999999999999\nR9999999999999999\nR9999999999999999999\nR999999999999999999\nR99999999999999999\nR999999999999999\n");
	}
	speed_duty_R = (int)(K_P*error_R+K_I*error_R_Sum+K_D*(error_R-error_last_R));
	error_last_R = error_R;

	// printf("Right_Encoder= %hd    speed_duty_R= %hd    error_R= %f",Right_Encoder,speed_duty_R,error_R);
	// printf("\n\n");
	
	// if(Right_Encoder>100){
	// for(int i=100;i<=Right_Encoder;i+=4){
	// 	if(i>goal-4 && i<goal+4)
	// 		printf("I");
	// 	else
	// 		printf(" ");
	// }}
	// printf("%d\n",Right_Encoder);

	if(speed_duty_R>=speed_max)
	{
		speed_duty_R =speed_max;
	}
	else if(speed_duty_R<speed_min)
	{
	    speed_duty_R =speed_min;

	}
	Moto_R(speed_duty_R);
}



//获取编码器的值
void Get_Encoder(void)
{
// 读取采集到的编码器脉冲数
    Left_Encoder =-encoder_get_count(ENCODER_1);
    Right_Encoder =encoder_get_count(ENCODER_2);
//计数器清零
        //encoder_clear_count(TIM2_ENCODER);
        //encoder_clear_count(TIM4_ENCODER);
    Average_Encoder = (Left_Encoder + Right_Encoder)*0.5;
//    endarch = 16-(speed_maximum-Average_Encoder)*0.01;//圆环早晚，数字越大越晚

    Sum_Encoder += Average_Encoder;
    distance += (Average_Encoder * 0.01);

}
void Moto_R(int16_t moto1)
{
    if(moto1>=0)
    {
		pwm_set_duty(MOTOR1_PWM,moto1);
        gpio_set_level(MOTOR1_DIR,1);
    }
    else
    {
        pwm_set_duty(MOTOR1_PWM,-moto1);
        gpio_set_level(MOTOR1_DIR,0);
    }
}
void Moto_L(int16_t moto2)//红左黑右
{
    if(moto2>=0)     //正速
    {
        pwm_set_duty(MOTOR2_PWM,moto2);
        gpio_set_level(MOTOR2_DIR,1);
    }
    if(moto2<0)
    {
        pwm_set_duty(MOTOR2_PWM,-moto2);
        gpio_set_level(MOTOR2_DIR,0);
    }
}
