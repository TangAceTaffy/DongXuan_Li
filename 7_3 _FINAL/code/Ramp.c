/*
 * Ramp.c
 *
 *  Created on: 2024年4月20日
 *      Author: icand
 */
#include "zf_common_headfile.h"
Str_Ramp   Ramp_deal;
Enum_RampProcess RampProcess;
float Ramp_Distance;
void Ramp_Detection(void)
{

    if (angke_roll <- 10)
    {
        Ramp_deal.Ramp_flag=1;//十字flag
        RampProcess=Find_Ramp;
        RoadType = Ramp;
        Ramp_Distance = distance;
        gpio_set_level(BUZZER_PIN, 1);
    }

}
void Ramp_Process(void)
{
    switch(RampProcess)
    {
        case Find_Ramp:
        {
//            //标志位清0
//            Round.Round_flag=0;
//            Cross_deal.Cross_flag=0;
            if (distance-Ramp_Distance >= 100)
            {
                RampProcess=Out_Ramp;
            }
            break;
        }
        case Out_Ramp:
        {
            Ramp_Distance = 0;
            angke_roll = 0;
            Ramp_deal.Ramp_flag=0;//十字flag
            Round.Round_flag=0;
            Cross_deal.Cross_flag=0;
            Obstacle.Obstacle_flag=0;
            RoadType= else_road;
            Elements_Current_Sequence++;
            gpio_set_level(BUZZER_PIN, 0);
            break;
        }
        default:
        {
            break;
        }
    }

}



/***************************************************************
坡道处理

* 函数名称： Cross_Detection()//十字处理
* 功能说明： 十字处理外部调用
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：
*******************************************************************/
void Ramp_Deal(void)//十字检测
{

   if(Ramp_deal.Ramp_flag==0)
   {
       have_element_flag=0;
       Ramp_Detection();        //十字检测
   }
   else
   {
       Ramp_Process();
       have_element_flag=1;
   }

}
