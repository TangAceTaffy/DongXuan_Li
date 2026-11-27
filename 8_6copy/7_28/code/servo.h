#ifndef _SERVO_H
#define _SERVO_H
#define steeringPWM_MID 700
#define angle_max  780//最左时的占空比
#define angle_min  620//最右时的占空比
#define steer_duty_max 80//最大占空比之差
#define PI 3.15159265
#define DEC (PI/180)
void servo_pid();
extern int16 angle;    //舵机占空比输出
extern float output;
extern int16 error;
extern int16 delta;
extern float Kp;
extern float Kd;
extern float Kd_d;
extern float Kp_p;
#endif
