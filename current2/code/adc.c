/*电磁的目前整体没有用到，只是别的地方用到了该源文件的变量，不加的话会其他的一直报错
 * adc.c
 *
 *  Created on: Aug 4, 2022
 *      Author: zhang
 */
#include "zf_common_headfile.h"
#include "adc.h"
uint32  adc_date[7];                //储存电感采集值    4个电感
uint16  Left_Adc=0,Right_Adc=0,Left_Xie_Adc=0,Right_Xie_Adc=0,Middle_Adc=0,Zuo_Qian_Adc=0,You_Qian_Adc=0;//电感值
uint32  adc_max[7]= {3220,3220,3220,3220,3220,3220,3220};              //最大值
uint32  adc_min[7]= {0,0,0,0,0,0,0};              //最小值  (给定一个需要)
int16  position,Cha=0,He=0,Sum,He_X;
int16  Cha_H=0,Cha_X=0;
int16  Error_L,Error_R;  //左右电感的相对偏差值，用于元素判断条件，已放大100倍
void read_adc(void)
{
//  AD_Date_Fitier();
    normalize_date();
//   adc_date[0] =  adc_mean_filter(ADC_P01,10);//左横
//   adc_date[1] =  adc_mean_filter(ADC_P05,10);//右横
//   adc_date[2] =  adc_mean_filter(ADC_P00,10);//左斜
//   adc_date[3] =  adc_mean_filter(ADC_P06,10);//右斜
//
//  Left_Adc = adc_date[0];//左电感最终值
//  Right_Adc = adc_date[1];//右电感最终值
//  Left_Xie_Adc = adc_date[2];//左斜电感最终值
//  Right_Xie_Adc = adc_date[3];//右斜电感最终值
}
/****************电感采集**************************
函数：void AD_Date_Fitier()
功能：对电感采值进行冒泡排序滑动滤波
参数：无
说明：12bit  4096  adc_mean_filter(ADC_P00,10);//采集10次 然后返回平均值
返回值：无
日期： 2022-3-19    14：26
修改日期： 2022-3-19    14：26
作者：  */
//void AD_Date_Fitier(void)
//{
//    uint8 i;
//    int16 filter_buf_L[FILTER_N];  //左横电感储存数组
//    int16 filter_buf_LC[FILTER_N]; //左斜电感储存数组//    int16 filter_buf_R[FILTER_N];  //右横电感储存数组
//    int16 filter_buf_RC[FILTER_N];  //右斜电感储存数组
//    int16 filter_buf_MID[FILTER_N];  //右斜电感储存数组
//    for(i = 0; i <FILTER_N; i++)//采值
//    {
////        filter_buf_L[i]  =  adc_mean_filter(ADC_IN7_A7,ADC_8BIT,10);//左横
////        filter_buf_R[i]  =  adc_mean_filter(ADC_IN9_B1,ADC_8BIT,10);//右横
////        filter_buf_LC[i] =  adc_mean_filter(ADC_IN10_C0,ADC_8BIT,3);//中
////        filter_buf_RC[i] =  adc_mean_filter(ADC_IN11_C1,ADC_8BIT,3);//左斜
////        filter_buf_MID[i] =  adc_mean_filter(ADC_IN12_C2,ADC_8BIT,3);//右斜
//    }
//    adc_date[0]= I_Median_Average_Filter(filter_buf_L);//左
//    adc_date[1] =I_Median_Average_Filter(filter_buf_R);//右
//    adc_date[2] = I_Median_Average_Filter(filter_buf_LC);//左斜
//    adc_date[3] = I_Median_Average_Filter(filter_buf_RC);//右斜
//    adc_date[4] = I_Median_Average_Filter(filter_buf_MID);
//}
/*****************归一化处理***********************
函数：void  normalize_date()
功能：采集电感值，进行归一化缩小，
参数：  无
说明：  在该函数中调用电感采集函数，在使用中需调用求最大值函数和该函数。
返回值：无
日期： 2021-1-13    晚23:40
修改日期： 2021-3-22    晚22:00
作者：      */
uint16 except_mid = 0;
void  normalize_date(void)
{
    int32 ADC_DATE[7]= {0}; //这个数据类型必须是有符号的
    int16  i;
//    adc_date[0] =  adc_mean_filter_convert(ADC1_CH11_C1,10);//左横 c1
//    adc_date[1] =  adc_mean_filter_convert(ADC1_CH12_C2,10);//左斜 c2
//    adc_date[2] =  adc_mean_filter_convert(ADC1_CH13_C3,10);//中c3
//    adc_date[3] =  adc_mean_filter_convert(ADC1_CH6_A6,10);//右斜 A6
//		adc_date[4] =  adc_mean_filter_convert(ADC1_CH7_A7,10);//右A7
//		adc_date[5] =  adc_mean_filter_convert(ADC1_CH5_A5,10);
//		adc_date[6] =  adc_mean_filter_convert(ADC1_CH4_A4,10);
    for(i=0; i<7; i++)           //归一化处理
    {
        ADC_DATE[i]= ((adc_date[i]-adc_min[i])*100/(adc_max[i]-adc_min[i]));         //adc_max[i] 最小值默认为0
        if(ADC_DATE[i]<=0)
        {
            ADC_DATE[i]=0;
        }
        else if(ADC_DATE[i]>=100)
        {
            ADC_DATE[i]=100;
        }
        adc_date[i]=ADC_DATE[i];
    }
//    Left_Adc = adc_date[4];//左电感最终值
//    Left_Xie_Adc = adc_date[3];//左斜电感最终值
//    Middle_Adc = adc_date[2];//中电感最终值
//    Right_Xie_Adc = adc_date[1];//右斜电感最终值
//    Right_Adc = adc_date[0];//右电感最终值
//	  Zuo_Qian_Adc=adc_date[5];
//		You_Qian_Adc=adc_date[6];

    except_mid = Left_Adc+Right_Adc+Right_Xie_Adc+Left_Xie_Adc;

//    else
//    {
        position =50*(Left_Adc-Right_Adc)/(Left_Adc+Right_Adc); //Cha_BI_He_Cha(Left_Adc,Right_Adc,Left_Xie_Adc,Right_Xie_Adc,0.85,0.15,7);
//        Error_L = XiangDui_Error(Left_Adc,Right_Adc,100);
//        Error_R = XiangDui_Error(Right_Adc,Left_Adc,100);
  //  }
//  delay_ms(5);
}
/*****************差比和***********************
函数： float Cha_BI_He(float Date_1,float Date_2,int16 X)
参数：  float Date_1--第一个数据  float Date_2--第二个数据  int16 X--左移位数
说明：  无
返回值：无
日期：2022-3-19
最后修改时间：2022-3-19
作者：      */
int16 Cha_BI_He(uint16 Date_1,uint16 Date_2,uint16 X)
{
    int16 Resault;
    Cha =  (int16)((Date_1 - Date_2));   //差
    He =   Date_1 + Date_2;   //和
    Resault = (Cha<<X/(He+1)) ; //差比和
    return   Resault;
}
/*****************差比和差***********************
函数： int16 Cha_BI_He_Cha(uint16 Date_1,uint16 Date_2,uint16 Date_3,uint16 Date_4,float a,float b,uint16 X)
参数：  float Date_1--左横电感  float Date_2--右横电感
        float Date_3--左斜电感  float Date_4--右斜电感
        float a--横电感加权系数  float b-- 斜电感加权系数   int16 X--左移位数
说明：  无
返回值：Resault
日期：2022-3-28
最后修改时间：2022-3-28
作者：       */
int16 Cha_BI_He_Cha(uint16 Date_1,uint16 Date_2,uint16 Date_3,uint16 Date_4,float a,float b,uint16 X)
{
    int16 Resault;
    int16 FengZ,FengM;
    Cha_H =  (int16)((Date_1 - Date_2));   //横电感差
    Cha_X =  (int16)((Date_3 - Date_4));   //斜电感差
    He =   Date_1 + Date_2;   //横电感和
    Sum = Date_1 + Date_2 + Date_3 + Date_4;  //所有电感之和
    He_X = Date_3 + Date_4; //斜电感和
    FengZ = a*Cha_H+b*Cha_X;
    FengM = a*He+b*myabs(Cha_X);
    Resault = ((FengZ<<X)/(FengM+1)); //差比和差
    return   Resault;
}
////////去除极值求平均
int16 I_Median_Average_Filter(int16 *DATE)
{
    uint8 i;
    int16 max,min;  //定义极值以及和
    int16 sum = 0;
    max = DATE[0];
    min = DATE[0];
    for(i=0; i<sizeof(DATE); i++)
    {
        if(max<DATE[i])
        {
            max = DATE[i];
        }
        if(min>DATE[i])
        {
            min = DATE[i];
        }
        sum += DATE[i];
    }
    sum =(sum-max-min)/(sizeof(DATE)-2);    //>>3
    return sum;
}
/****************电感采集**************************
函数：void ADC_MAX_Collect(void)
功能：均值滤波
参数：  无
说明：  调用库函数    adc_mean_filter(ADC_P00,5);
返回值：无
日期： 2022-3-19    14：26
修改日期：2022-3-19    14：26
作者：    */
void ADC_MAX_Collect(void)
{
    int i,j;
    for(i = 600; i>0; i--)
    {
//        adc_date[0] = adc_mean_filter_convert(ADC1_CH11_C1,5);//采集5次 然后返回平均值
//        adc_date[1] = adc_mean_filter_convert(ADC1_CH12_C2,5);//采集5次 然后返回平均值
//        adc_date[2] = adc_mean_filter_convert(ADC1_CH13_C3,5);//采集5次 然后返回平均值
//        adc_date[3] = adc_mean_filter_convert(ADC1_CH6_A6,5);//采集5次 然后返回平均值
//        adc_date[4] = adc_mean_filter_convert(ADC1_CH7_A7,5);//采集5次 然后返回平均值
//			  adc_date[4] = adc_mean_filter_convert(ADC1_CH4_A4,5);//采集5次 然后返回平均值
//			  adc_date[4] = adc_mean_filter_convert(ADC1_CH5_A5,5);//采集5次 然后返回平均值
        for(j=0; j<2; j++) //两个横电感
        {
            if(adc_date[j]>=adc_max[j])
            {
                adc_max[j]=adc_date[j];
            }
            //  if(adc_date[j]<=adc_min[j])
            // adc_min[j]=adc_date[j];
            //delay_ms(2);//延时采集
        }
    }
}
void Adv_init(void)
{
//    adc_init(ADC1_CH11_C1, ADC_12BIT);
//		adc_init(ADC1_CH12_C2, ADC_12BIT);
//		adc_init(ADC1_CH13_C3, ADC_12BIT);
//		adc_init(ADC1_CH6_A6, ADC_12BIT);
//		adc_init(ADC1_CH7_A7, ADC_12BIT);
//	  adc_init(ADC1_CH5_A5, ADC_12BIT);
//	  adc_init(ADC1_CH4_A4, ADC_12BIT);
 
}
int16 XiangDui_Error(uint16 Date_1,uint16 Date_2,int16 X)
{
    int16 Resault,Average;
    Average = (Date_1 + Date_2)*0.5;   //求两数平均
    Resault = ((myabs(Average - Date_1))*X)/Average;
    return   Resault;
}

int myabs(int num)
{
    int value = 0;
    if (num < 0)
    {
        value = -num;
    }
    else
    {
        value = num;
    }
    return value;
}
