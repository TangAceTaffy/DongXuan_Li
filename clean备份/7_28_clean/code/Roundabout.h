/*
 * Roundabout.h
 *
 *  Created on: 2022年5月13日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"

#ifndef CODE_ROUNDABOUT_H_
#define CODE_ROUNDABOUT_H_


typedef enum __RoundType
{
  Left_Round=1,
  Right_Round
}RoundTypeDef;


typedef enum __RoundSize
{
  Small_Round=1,
//  Middle_Round,               //中环不考虑了
  Large_Round

}RoundSizeTypeDef;

typedef enum __RoundProcess
{
  Round_Not_Found=0,
  Find_Round,
  Find_Gap,
  Into_Round,
  Into_Round2,
  In_Round,
  Out_Round,
  Leave_Round,
  Leave_Round2

}RoundProcessTypeDef;

typedef  struct
{
       unsigned char Round_flag;     //圆环标志位
       unsigned char Round_flag_able; //圆环标志位使能

       unsigned char Entrance_count;

       unsigned char Track_Width_forRound[ROW_END];//赛道宽度

}Str_Round;    //圆环结构体
extern RoundTypeDef RoundType;
extern Str_Round  Round;
extern RoundSizeTypeDef  RoundSize;
extern RoundProcessTypeDef RoundProcess;
void Round_Deal();//十字检测
extern float Distance_In_Round;
extern float Distance_Leave_Round2;
extern int  Round_num;
extern int check_point;
extern float Distance_In_Round;
#endif /* CODE_ROUNDABOUT_H_ */
