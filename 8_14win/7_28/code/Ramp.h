/*
 * Ramp.h
 *
 *  Created on: 2024年4月20日
 *      Author: icand
 */

#ifndef CODE_RAMP_H_
#define CODE_RAMP_H_

typedef  struct
{
       unsigned char Ramp_flag;      //坡道标志位
}Str_Ramp;    //坡道结构体

typedef enum
{
       Find_Ramp,
       Out_Ramp
}Enum_RampProcess;
extern float Ramp_Distance;
extern Str_Ramp   Ramp_deal;
void Ramp_Detection(void);
void Ramp_Process(void);
void Ramp_Deal(void);
#endif /* CODE_RAMP_H_ */
