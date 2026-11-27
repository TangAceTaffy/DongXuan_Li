/*
 * function.c
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"

/*----------------------------------------------------------------------------------------------------------------
*  @brief   差比和函数
*  @param
*
*
*
*  @return
*  @since
*  Sample usage:
//--------------------------------------------------------------------------------------------------------------*/
 int difference_sum(unsigned char a,unsigned char b )
 {
  if(a+b==0)
  {
    return 0;
  }
   return (a-b)*300/(a+b);
 }
 /*----------------------------------------------------------------------------------------------------------------
 *  @brief   阈值比较函数
 *  @param
 *
 *
 *
 *  @return
 *  @since
 *  Sample usage:
 //--------------------------------------------------------------------------------------------------------------*/
 int mark_middle_num(int num1,int num2,int middle)
 {
   if(num1<=num2 && num1<=middle && num2>=middle)
   {
     return 1;
   }
   else if(num2<num1 && num1>middle && num2<middle)
   {
     return 1;
   }
   else
   {
     return 0;
   }
 }

 void int8_range_protect(unsigned char data[],uint8 start,uint8 end)
 {
     uint8 i;
     for(i=0;i<39;i++)
     {
         if(data[i]<start)
         {
             data[i]=start;
         }
         if(data[i]>end)
         {
              data[i]=end;
          }

     }
 }

 /******************************************************************************
  *
 //最小二乘法拟合斜率
 ******************************************************************************/
 float Slope_Calculate(uint8 begin,uint8 end,uint8 *p)
 {
  float xsum=0,ysum=0,xysum=0,x2sum=0;
   uint8 i=0;
   float result=0;
   static float resultlast;
   p=p+begin;
   for(i=begin;i<end;i++)
   {
       xsum+=i;
       ysum+=*p;
       xysum+=i*(*p);
       x2sum+=i*i;
       p=p+1;
   }
  if((end-begin)*x2sum-xsum*xsum) //判断除数是否为零
  {
    result=((end-begin)*xysum-xsum*ysum)/((end-begin)*x2sum-xsum*xsum);
    resultlast=result;
  }
  else
  {
   result=resultlast;
  }
  return result;
 }
 /******************************************************************************
  *
 //曲线拟合   CommonRectificate(&P_LeftBlack[0],startPos-1,endPos+1);
 ******************************************************************************/
 void CommonRectificate(unsigned char data[],unsigned char begin,unsigned char end)
 {
        unsigned char MidPos = 0;
        if (end > 80-1)
        {
           end = 80-1;
        }
        if (begin == end)
        {
           data[begin] = (data[begin-1]+data[begin+1])>>1;
          // BlackLineData[begin] =  LeftBlack[begin] + (RightBlack[begin]-LeftBlack[begin])/2;
        }
        else if(begin < end)
        {
           MidPos = (begin+end)>>1;
           data[MidPos] = (data[begin]+data[end])>>1;
           //BlackLineData[MidPos] =  LeftBlack[MidPos] + (RightBlack[MidPos]-LeftBlack[MidPos])/2;
           if (begin+1 < MidPos)
           {
              CommonRectificate(data,begin,MidPos);
           }
           if (MidPos+1 < end)
           {
              CommonRectificate(data,MidPos,end);
           }
        }
 }
 /*----------------------------------------------------------------------------------------------------------------
  *  @brief
  *  @param
  *
  *
  *
  *  @return
  *  @since
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------------------*/
 int32 int_range_protect( int32  duty, int32  min, int32  max ) //限幅保护
 {
     if( duty > max )
     {
         return max;
     }
     else if( duty <= min )
     {
         return min;
     }
     else
     {
         return duty;
     }
 }
 //-------------------------------------------------------------------------//
 /******** 限幅保护 *********/
 float float_range_protect( float duty, float min, float max ) //限幅保护
 {
     if( duty > max )
     {
         return max;
     }
     else if( duty <= min )
     {
         return min;
     }
     else
     {
         return duty;
     }
 }
 //-------------------------------------------------------------------------//
 /******** 限幅保护 *********/
int ABS(int a)
 {
   if(a<0)
   {
       return -a;

   }
   else
    {
       return a;
    }

 }

float Float_ABS(float a)
{
    if(a<0)
    {
        return -a;

    }
    else
     {
        return a;
     }
}
int32 limit_max(int32 a,int32 b){//最大值限幅
    if(a>b)return b;
    else return a;
}
int32 limit_min(int32 a,int32 b){//最小值限幅
    if(a<b)return b;
    else return a;
}
 /*----------------------------------------------------------------------------------------------------------------
  *  @brief   获取角速度后换算成角度
  *  @param
  *
  *
  *
  *  @return
  *  @since
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------------------*/
 float angke_yaw;//z
 float angke_pitch;//x
 float angke_roll;//y
 uint16 yaw_find_flag=0;
 void angke_yaw_get(void)
 {
  angke_yaw-= (imu660ra_gyro_z+10.5-gyro_offset_z)*-0.00012480f;
 }

 void angke_pitch_get(void)
 {
  angke_pitch+= (imu660ra_gyro_x+9.5-gyro_offset_x)*0.00012480f;
 }

 void angke_roll_get(void)
 {
  angke_roll+= (imu660ra_gyro_y-9-gyro_offset_y)*0.00012480f;
 }
 /*----------------------------------------------------------------------------------------------------------------
  *  @brief   零飘偏差值计算（放初始化）
  *  @param   calibrate_gyro

  *  @return  void
  *  @since   v1.0
  *  comments on a form:传参：三轴陀螺仪的零飘偏差值
  //-----------------------------------------------------------------------------------------------------------------*/
 double gyro_offset_x, gyro_offset_y, gyro_offset_z;
 void calibrate_gyro(void)
 {
     //读取陀螺仪数值并求平均值
     double total_x = 0.0, total_y = 0.0, total_z = 0.0;
     int num_samples = 100;
     for (int i = 0; i < num_samples; i++) {
         imu660ra_get_gyro();
         total_x += imu660ra_gyro_x;
         total_y += imu660ra_gyro_y;
         total_z += imu660ra_gyro_z;
     }
     gyro_offset_x = total_x / num_samples;
     gyro_offset_y = total_y / num_samples;
     gyro_offset_z = total_z / num_samples;
 }
