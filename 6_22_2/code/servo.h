#ifndef _SERVO_H
#define _SERVO_H
#define steeringPWM_MID 736
#define angle_max  800//zuo
#define angle_min  666//you
#define PI 3.15159265
#define DEC (PI/180)
//sbit Buzz = P7^7;
//sbit Hall = P1^0;
void servo_init(void);
void servo_pid();
float Get_Dire(uint8 i);
extern int16 angle;    //舵机占空比输出
extern int16 Now_duty;
extern double K_diff ;  //过弯差速比
extern float output;
extern int16 error;
extern int16 delta;
extern float Kp;
extern float Kd;
extern float output_p;

extern uint8 left_diff_flag;
extern uint8 right_diff_flag;
#endif
