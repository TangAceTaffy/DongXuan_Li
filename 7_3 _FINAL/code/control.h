#ifndef _MOTOR_H_
#define _MOTOR_H_
#define Normal_speed  40       //正常赛道速度
#define Fork_speed     20       //三岔内速度
#define Annulus_speed  20       //圆环内速度
#define House_speed    0         //出入库速度
#define Hall_Pin	P46
//----变量----//
extern uint8 para1;
//各元素标志位
extern uint8 Fork_Flag;
extern uint8 in_fork_status;
extern uint8 Ramp_Flag;
extern uint8 Left_Big_annulus_status;
extern uint8 Left_Small_annulus_status;
extern uint8 Right_Big_annulus_status;
extern uint8 Right_Small_annulus_status;
extern uint8 have_element_flag;
extern float angle_i;
//三岔内标志位
extern uint8 Fork_num;//还是1？
extern uint8 fork_turn_left_flag;
extern uint8 fork_turn_right_flag;
extern uint8 exit_ban;
extern uint8 Fork_ban;
//圆环内标志位
extern uint8 big_annulus_series[6];
extern uint8 left_annulus_series[6];
extern uint8 annulus_count;
extern uint8 annulus_status;
extern uint8 annulus_turn_left_small_flag;
extern uint8 annulus_turn_left_big_flag;
extern uint8 annulus_turn_right_big_flag;
extern uint8 annulus_turn_right_small_flag;
//强制越界保护
extern uint8 force_left_flag;
extern uint8 force_right_flag;
//电机控制
extern uint8 Brush_Stop_flag;
extern uint8 Brushless_Stop_flag;
extern uint8 acc_flag;
extern uint8 slo_flag;
//----变量----//
extern uint8 hall_flag;
extern uint8 hall_count;
//extern uint8 roadtype_ban;
//typedef enum
//{
//       s_road,
//       c_road,
//       Cross_Road,
//       Round_Road,
//       Ramp,          
//       Garage,
//       Start

//} enum_RoadType;
//typedef enum
//{
//	left_c,
//	right_c
//} enum_c_road;
//extern enum_c_road c_road_type;
//extern enum_RoadType  RoadType;
//----函数----//
void angle_yaw_inte(void);
void angle_pitch_inte(void);
void angular_speed_calc(void);
void motor_speed(void);
void display(void);
//int myabs(int16 a);
void BUZZ_ON(void);
//----函数----//
//void roadtype_check(void);

#endif
