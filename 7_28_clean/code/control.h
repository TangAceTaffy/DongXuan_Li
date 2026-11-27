#ifndef _MOTOR_H_
#define _MOTOR_H_
//各元素标志位
extern uint8 have_element_flag;
extern float angle_i;
//电机控制
extern uint8 Brush_Stop_flag;
extern uint8 Brushless_Stop_flag;
//----函数----//
void angle_yaw_inte(void);
void angle_pitch_inte(void);
void angular_speed_calc(void);
void motor_speed(void);
void display(void);
#endif
