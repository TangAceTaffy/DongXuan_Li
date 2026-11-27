#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "zf_common_headfile.h"



 int difference_sum(unsigned char a,unsigned char bs );
 int mark_middle_num(int num1,int num2,int middle);
 void int8_range_protect(unsigned char data[],uint8_t start,uint8_t end);
 void CommonRectificate(unsigned char data[],unsigned char begin,unsigned char end);
 
 int32_t int_range_protect( int32_t  duty, int32_t  min, int32_t  max ); //ÏÞ·ù±£»¤
 float float_range_protect( float duty, float min, float max );
 int ABS(int a);
 float Float_ABS(float a);
 int32_t limit_max(int32_t,int32_t);
 int32_t limit_min(int32_t,int32_t);
 #endif /* FUNCTION_H_ */
