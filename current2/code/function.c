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
///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：超声波测距
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/


//uint16 ranging_counter = 0;                             // 测距数据
//uint8 ranging_flage = 0x00;                             // 测距状态

//uint8 receipt_data;
//uint8 dat[3];
//uint8 num;
//uint8 distance = 0;

//void uart_handler (void)
//{
//    uart_query_byte(SPLIT_ULTRASONIC_UART, &receipt_data);
//    dat[num] = receipt_data;
//    if(dat[0] != 0xa5)  num = 0;                                                    //检查第一个数据是否为0xa5
//    else                num++;

//    if(num == 3)                                                                    //接收完成 开始处理数据
//    {
//        num = 0;
//        ranging_counter = dat[1]<<8 | dat[2];                                       //得到超声波模块测出的距离
//        ranging_flage = 0x01;
//    }
//    distance = ranging_counter / 10;

//}

///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：32位转为8位
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/

//void u32_to_u8(uint32 data32, uint8 data8[])
//{
//    data8[0] = data32 >> 24;
//    data8[1] = (data32 >> 16) & 0xff;
//    data8[2] = (data32 >> 8) & 0xff;
//    data8[3] = data32 & 0xff;
//}

/////*----------------------------------------------------------------------------------------------------------------
////  *  @brief：距离蜂鸣器
////  *  @param
////  *
////  *
////  *
////  *  @return
////  *  @since
////  *  Sample usage:
////  //--------------------------------------------------------------------------------------------------------------*/
////void distance_buzzer(void)
////{
////    if (distance <= 80 && distance >= 0)
////    {
////        gpio_set_level(BEEP_PIN,1);
////    }
////    else
////    {
////        gpio_set_level(BEEP_PIN,0);
////    }
////}

///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：距离蜂鸣器
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/
//uint8 close_flag = 0;
//void distance_buzzer(void)
//{
//    if (close_flag == 1)
//    {
//        gpio_set_level(BEEP_PIN,1);
//    }
//    else
//    {
//        gpio_set_level(BEEP_PIN,0);
//    }
//}
///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：减少测距噪声
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/
//uint8 Dist[] = {168, 0};
//uint8 I_dist = 0;
//uint8 first_in_flag = 0;
//void inspect_distance(void)
//{
//   // uint8 valid_flag = 0;

////    if (first_in_flag <= 5)
////    {
////        first_in_flag++;
////        Dist[0] = distance;
////    }
// //   else{
//           Dist[1] = distance;
//        if ( ABS(Dist[0] - Dist[1]) >= 20 )
//        {
//            //valid_flag = 0;
//            I_dist = Dist[0];

//        }
//        else
//        {
//            Dist[0] = Dist[1];
//            I_dist = Dist[0];

//        }


//            if (I_dist<= 120 && I_dist >= 0)
//            {
//                close_flag = 1;
//            }
//            else
//            {
//                close_flag = 0;
//            }

//   // }

//}
///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：滤波前的预处理，将比平均值小于20的数滤掉
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/

//uint8 pre_dat[] = {0, 0, 0};

//uint8 pre_kal(uint8 data)
//{
//    uint8 i = 0;
//    uint16 sum = 0;
//    uint8 avg = 0;
//    uint8 dis = 0;
//    dis = distance;
//    for (i = 0; i < 3; i++)
//    {
//        sum = pre_dat[i] + sum;
//    }
//    avg = sum / 3;
//    tft180_show_uint16(30, 100, avg);
//    tft180_show_uint16(30, 120, sum);

//    if (data <= avg - 20)
//    {
//        return avg;
//    }
//    else
//    {
//        return dis;
//    }
//}
///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：将这个值存入数组留待下一次判断
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/

//void load_in_data(uint8 data)
//{
//    uint8 i = 0;
//    for (i = 0; i < 2; i++)
//    {
//        pre_dat[i] = pre_dat[i+1];
//    }
//    pre_dat[2] = data;
//}
///*----------------------------------------------------------------------------------------------------------------
//  *  @brief：扫线方式滤波
//  *  @param
//  *
//  *
//  *
//  *  @return
//  *  @since
//  *  Sample usage:
//  //--------------------------------------------------------------------------------------------------------------*/
//uint8 close_num = 0;
//uint8 far_num = 0;
//uint8 far_flag = 0;
//void vertify_distance(uint8 data)
//{
//    uint8 dis = data;

//    if (dis <= 90)      //小于80，太近了，减速
//    {
//        close_num++;
//        far_num = 0;
//    }
//    else if (dis >= 100 && dis <= 120) //在100和120之间，太远了，加速
//    {
//        far_num++;
//        close_num = 0;
//    }
//    else
//    {
//        close_num = 0;
//        far_num =0;
//    }


//    if (close_num >= 240)   //防止溢出
//    {
//        close_num = 8;
//    }
//    if (far_num >= 240)     //防止溢出
//    {
//        far_num = 8;
//    }

//    if (close_num >= 8)     //符合太近要求
//    {
//        close_flag = 1;
//    }
//    else if (far_num >= 8)  //符合太远要求
//    {
//        far_flag = 1;
//    }
//    else
//    {
//        close_flag =0;
//        far_flag = 0;
//    }
//}


 /*----------------------------------------------------------------------------------------------------------------
  *  @brief   ???yaw???
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
