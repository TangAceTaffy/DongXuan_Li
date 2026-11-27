#ifndef _SERVO_H
#define _SERVO_H
#include "zf_common_headfile.h"
#define SERVO_MOTOR1_PWM            "/dev/zf_device_pwm_servo"
#define pwm_esc_2            "/dev/zf_device_pwm_esc_2"
#define steeringPWM_MID 780//138000*2
#define angle_max  855//156000*2//最左时的占空比
#define angle_min  705//120000*2//最右时的占空比
 


#define PI 3.15159265
#define DEC (PI/180)
void servo_pid();
extern int32_t angle;    //舵机占空比输出
extern float output;
extern int16_t error1;
extern int16_t error2;
extern int16_t delta;
extern float Kp;
extern float Kd;
extern float Kd_d;
extern float Kp_p;
extern float Stright_Kp;
extern float Else_Kp;
#endif
