/*
 * Cross.h
 *
 *  Created on: 2022年5月13日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
#ifndef CODE_CROSS_H_
#define CODE_CROSS_H_


typedef  struct
{
       unsigned char Cross_flag;      //十字标志位
       unsigned char Cross_flag_able; //十字标志位使能

       char Track_Width_forCross[ROW_END];//赛道宽度

       unsigned char addR_flag ;
       unsigned char addL_flag ;

       unsigned char Entrance_count;
       unsigned char Gap_count;

}Str_Cross;    //圆环结构体
typedef enum
{
       Cross_Not_Found=0,
       Find_Cross,
       In_Cross,
       Out_Cross
}Enum_CrossProcess;
typedef enum
{
       Cro_else ,
       Cro_LeftLean,     //十字左倾标志位
       Cro_RightLean,    //十字右倾标志位
       Cro_ZHENG        //正十字志位
}Enum_CrossType;
typedef  struct
{
       unsigned char EN_Break_RoadType;   //断路使能标志位
       unsigned char EN_Barrier;         //障碍使能标志位
       unsigned char EN_Ramp ;         //坡道使能标志位
       unsigned char EN_Round;     //圆环使能标志位
       unsigned char EN_Cross;      //十字使能标志位


}Str_RoadEN;    //圆环结构体
extern uint8_t Cross_num;
extern Str_Cross   Cross_deal;
extern Enum_CrossType  CrossType;
extern Enum_CrossProcess  CrossProcess;
extern  Str_RoadEN   REN;
void Cross_Deal();//十字检测
extern void Cross_Detection();//十字检测
extern int flag_1;
#endif /* CODE_CROSS_H_ */
