/*
 * function.h
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */

#ifndef CODE_FUNCTION_H_
#define CODE_FUNCTION_H_
#include "zf_common_headfile.h"


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
#endif /* CODE_FUNCTION_H_ */
