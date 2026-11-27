/*
 * function.h
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */

#ifndef CODE_FUNCTION_H_
#define CODE_FUNCTION_H_
#include "zf_common_headfile.h"

//----------超声波变量-------------//
//#define SPLIT_ULTRASONIC_UART       UART_8
//#define SPLIT_ULTRASONIC_BAUD       115200
//#define SPLIT_ULTRASONIC_RX         UART8_TX_E14        // 有来有去的 UART-RX 引脚 要接在单片机 TX 上
//#define SPLIT_ULTRASONIC_TX         UART8_RX_E15        // 有来有去的 UART-TX 引脚 要接在单片机 RX 上

//#define SEND_PORT_PIN               D10                 // 设置对应端口 有去模块发送 这里其实可以不用控制
//extern uint8 distance;
//extern uint8 I_dist;
//extern uint8 close_flag;
//extern uint8 far_flag;
//extern uint8 K_dist;
//----------超声波变量-------------//

//----------陀螺仪变量-------------//
//extern float angke_yaw;//z
//extern float angke_pitch;//x
//extern float angke_roll;//y
//extern uint16_t yaw_find_flag;
//----------陀螺仪变量-------------//

// void angke_yaw_get(void);
 //void angke_pitch_get(void);
 //void angke_roll_get(void);
 int difference_sum(unsigned char a,unsigned char b );
 int mark_middle_num(int num1,int num2,int middle);
 void int8_range_protect(unsigned char data[],uint8 start,uint8 end);
 void CommonRectificate(unsigned char data[],unsigned char begin,unsigned char end);
 float Slope_Calculate(uint8 begin,uint8 end,uint8 *p);
 int32 int_range_protect( int32  duty, int32  min, int32  max ); //限幅保护
 float float_range_protect( float duty, float min, float max );
 int ABS(int a);
 float Float_ABS(float a);
 int32 limit_max(int32,int32);
 int32 limit_min(int32,int32);
 extern float angke_yaw;//z
 extern float angke_pitch;//x
 extern float angke_roll;//y
 extern uint16_t yaw_find_flag;
 void angke_yaw_get(void);
 extern double gyro_offset_x, gyro_offset_y, gyro_offset_z;
 void calibrate_gyro(void);
// void uart_handler (void);
 //void u32_to_u8(uint32 data32, uint8 data8[]);
 //void distance_buzzer(void);
 //void inspect_distance(void);
 //uint8 pre_kal(uint8 data);
 //void load_in_data(uint8 data);
 //void vertify_distance(uint8 data);

#endif /* CODE_FUNCTION_H_ */
