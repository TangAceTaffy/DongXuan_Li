/*
 * motor.h
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#ifndef MOTOR_H_
#define MOTOR_H_
#include "zf_common_headfile.h"
//----变量----//
extern int16 Left_Encoder ;
extern int16 Right_Encoder ;
extern float Average_Encoder;  //左右编码器平均值
extern float Sum_Encoder;      //编码器脉冲和
extern float distance;         //车子行走的路程
extern int16 Right_Duty;
extern int16 Left_Duty;
extern float K_P ;
extern float K_I ;
extern float K_D ;
//extern int16 error_z;
//extern int16 last_error_L;
//extern int16 error_last_last_L;
//extern int16 error_y;
//extern int16 last_error_R;
//extern int16 error_last_last_R;
extern int gyro_out;
extern int16 mspeed;
extern int16 Send_Count;
extern uint8 Differential_coefficient_flag;
extern int16 speed_duty_L;
extern int16 speed_duty_R;
extern double serve_out;
//----变量----//
//----函数----//
void angle_yaw_inte(void);
void Get_Encoder(void);
void Moto_L(int16 moto1);
void Moto_R(int16 moto2);
void set_pwm(int16 moto1,int16 moto2);
void left_motor_pid(int16 goal);
void right_motor_pid(int16 goal);
void dir_angle(int16 position);
void set_pwm_dir(int gyro_out);
void Speed_Differential_calculation(int temSpeed);
void Speed_Differential_akm_calculation(int temSpeed);
void Changable_Speed(int Max_Speed,int Min_Speed);
//----函数----//
#endif /* MOTOR_H_ */
