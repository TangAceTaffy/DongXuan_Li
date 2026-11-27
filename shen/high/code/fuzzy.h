/*
 * Fuzzy.h
 *
 *  Created on: 2022年5月6日
 *      Author: dell
 */

#ifndef FUZZY_H_
#define FUZZY_H_



typedef struct {
  //基础模糊表
  uint8         ui8_Table[4][4];
} MH_Table;


typedef struct {
  //舵机P值表L
  float         f_DuoJiP_TableL[7];
  //舵机P值表R
  float         f_DuoJiP_TableR[7];//没用  就用一个  没必要用两个舵机表 麻烦
  //舵机模糊表
  MH_Table      mt_Duoji[4];//总共四个4*4的数组
    //电机P值表
  float         f_DianJiP_Table[7];   //没用
  //电机I值表
  float         f_DianJiI_Table[7];   //没用
  //电机模糊表
  MH_Table      mt_DianJi[4];            //没用
  //出入弯标志
  uint8         ui8_IO;              //没用
  //左右出入弯标志
  uint8         ui8_IOLR;            //没用
  //出入弯加减速标志
  uint8         ui8_IOAS;          //没用
  //反向可视距离变化范围
  float         f_SizeOfViewH;      //图像视野  由摄像头的角度决定
  //中值偏差变化范围
  float         f_SizeOfViewE;
    //脉冲偏差变化范围                          //没用看不懂
  float         f_SizeOfPulseE;
  //上次反向可视距离                                //和OFFLINE一个意思
  short         i16_ViewH;
  //
} MH;
float f_Get_E_approximation(short i16_E, float f_E_Size);
float f_Get_H_approximation(short i16_ViewH);
void DuoJi_GetP(float *i32p_P, short i16_ViewH, short i16_ViewE);
void InitMH(void);
void Data_Settings(void);
float FUZZY_P(int err,int errc);
float FUZZY_I(int err,int errc);
float FUZZY_D(int err,int errc);


extern MH      MHstruct;
extern MH      MHstructFastCar;



#endif /* FUZZY_H_ */
