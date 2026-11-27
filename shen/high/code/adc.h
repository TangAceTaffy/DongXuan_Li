/*电磁的目前整体没有用到，只是别的地方用到了该源文件的变量，不加的话会其他的一直报错
 * adc.h
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#ifndef ADC_H_
#define ADC_H_
#include "zf_common_headfile.h"
extern uint32  adc_date[7];                //储存电感采集值    5个电感
extern uint32  adc_max[7];               //最大值
extern  uint32  adc_min[7];               //最小值  (给定一个需要)
extern uint16  Left_Adc,Right_Adc,Left_Xie_Adc,Right_Xie_Adc,Middle_Adc,Zuo_Qian_Adc,You_Qian_Adc;//电感值
extern int16  position,Cha,He,Sum,He_X;
extern int16  Cha_H,Cha_X;
extern int16  Error_L,Error_R;
extern uint16 except_mid;
void read_adc(void);
void Adv_init(void);
void  AD_Date_Fitier(void);
void  normalize_date(void);
void  ADC_MAX_Collect(void);
int myabs(int num);
int16 Cha_BI_He(uint16 Date_1,uint16 Date_2,uint16 X);
int16 Cha_BI_He_Cha(uint16 Date_1,uint16 Date_2,uint16 Date_3,uint16 Date_4,float a,float b,uint16 X);
int16 I_Median_Average_Filter(int16 *DATE);
int16 XiangDui_Error(uint16 Date_1,uint16 Date_2,int16 X);
#endif /* ADC_H_ */
