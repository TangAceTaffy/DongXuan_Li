/*
 * motor.h
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#ifndef MOTOR_H_
#define MOTOR_H_
#include "zf_common_headfile.h"

#define MOTOR1_DIR   "/dev/zf_driver_gpio_motor_1"
#define MOTOR1_PWM   "/dev/zf_device_pwm_motor_1"

#define MOTOR2_DIR   "/dev/zf_driver_gpio_motor_2"
#define MOTOR2_PWM   "/dev/zf_device_pwm_motor_2"
#define MOTOR1_PWM_DUTY_MAX    (motor_1_pwm_info.duty_max)
#define MOTOR2_PWM_DUTY_MAX    (motor_2_pwm_info.duty_max)
struct pwm_info motor_1_pwm_info;
struct pwm_info motor_2_pwm_info;
#define ENCODER_1           "/dev/zf_encoder_1"
#define ENCODER_2           "/dev/zf_encoder_2"
//----变量----//
extern int16_t Left_Encoder;
extern int16_t Right_Encoder;
extern float Average_Encoder;  //左右编码器平均值
extern float Sum_Encoder;      //编码器脉冲和
extern float distance;         //车子行走的路程
extern float distance1;
extern float K_P ;
extern float K_I ;
extern float K_D ;
extern int16_t speed_duty_L;
extern int16_t speed_duty_R;


extern double serve_out;
//----变量----//

//----函数----//
void angle_yaw_inte(void);
void Get_Encoder(void);
void Moto_L(int16_t moto1);
void Moto_R(int16_t moto2);
void left_motor_pid(int16_t goal);
void right_motor_pid(int16_t goal);
void Encoder1();
#endif /* MOTOR_H_ */
