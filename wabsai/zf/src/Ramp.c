/*
 * Ramp.c
 *
 *  Created on: 2024年4月20日
 *      Author: icand
 */
#include "zf_common_headfile.h"
Str_Ramp Ramp_deal;
Enum_RampProcess RampProcess;
float Ramp_Distance = 0;
int Ramp_flag = 0;
int Ramp_num = 0;
void Ramp_Detection(void)
{
    // if (Ramp_flag == 0 && imu660ra_gyro_y > 2000 )
    // {

    //     printf("Ramp12 %d   ", imu660ra_acc_x);
    //     printf("Ramp11 %d \n", imu660ra_gyro_y);
    //     if (Ramp_flag == 0)
    //         Ramp_Distance = distance;
    //     Ramp_flag = 1;
    // }
    // if (Ramp_flag == 1 && abs(imu660ra_acc_x) > 700 && defineSR != 2 && abs(imu660ra_acc_x) < 2500 && imu660ra_gyro_y > 1000)
    // {
    //     Ramp_Distance = distance;
    //     Ramp_deal.Ramp_flag = 1; // 十字flag
    //     RampProcess = Find_Ramp;
    //     RoadType = Ramp;
    //     gpio_set_level(LED, 0x1);
    //     printf("Ramp22 %d   ", imu660ra_acc_x);
    //     printf("Ramp21 %d \n", imu660ra_gyro_y);
    //     Ramp_flag = 0;
    // }
    // if (distance - Ramp_Distance >= 500 && imu660ra_gyro_y < 1500 && abs(imu660ra_acc_x) < 500 && Ramp_flag == 1)
    // {

    //     printf("Ramp32 %d   ", imu660ra_acc_x);
    //     Ramp_flag = 0;
    //     printf("Ramp out\n");
    // }

    if (Ramp_flag == 0)
    {
        Ramp_num = 0;
        for (int i = 1; i <= 26; i += 2)
        {
            if ((abs(r_border[i + 4] - r_border[i]) < 2 || abs(l_border[i] - l_border[i + 4]) < 2) && r_lose_num < 10 && l_lose_num < 10 &&
                (r_border[40 + i + 4] - r_border[40 + i] >= 2 || l_border[40 + i] - l_border[40 + i + 4] >= 2) && r_border[i] < 150 && l_border[i] > 10)
            {
                Ramp_num++;
                if (Ramp_num > 5)
                {
                    Ramp_flag = 1;
                    Ramp_Distance = distance;
                    Ramp_num = 0;
                    // printf("Ramp1\n");
                    break;
                }
            }
        }
    }
    // else
    //     printf("imu660ra_gyro_y %d \n\n", imu660ra_gyro_y);

    if (Ramp_flag == 1 && abs(imu660ra_gyro_y) > 2400)          //           || abs(imu660ra_acc_x > 700)
    {
        Ramp_Distance = distance;
        Ramp_deal.Ramp_flag = 1; // 十字flag
        RampProcess = Find_Ramp;
        RoadType = Ramp;
        gpio_set_level(LED, 0x1);
        printf("Into_Ramp gyro=%d  acc=%d\n", imu660ra_gyro_y,imu660ra_acc_x);
        Ramp_flag = 0;
    }
    if (distance - Ramp_Distance >= 1600 && Ramp_flag == 1)
    {

        // printf("Ramp32 %d   ", imu660ra_acc_x);
        Ramp_flag = 0;
        // printf("Ramp out\n");
    }
}
void Ramp_Process(void)
{
    switch (RampProcess)
    {
    case Find_Ramp:
    {

        // for (int i = 0; i < 50; i++)
        // {
        //     r_border[i] = 150;
        //     l_border[i] = 10;
        // }

        if (distance - Ramp_Distance >= 400)
        {
            RampProcess = Out_Ramp;
        }
        break;
    }
    case Out_Ramp:
    {
        if (distance - Ramp_Distance >= 400)
        {
            RampProcess = Leave_Ramp;
        }
        break;
    }
    case Leave_Ramp:
    {
        Ramp_deal.Ramp_flag = 0; // 十字flag
        Round.Round_flag = 0;

        Obstacle_flag = 0;
        RoadType = else_road;
        Elements_Current_Sequence++;
        gpio_set_level(LED, 0x0);

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
void Ramp_Deal(void) // 十字检测
{

    if (Ramp_deal.Ramp_flag == 0 && (distance - Ramp_Distance >= 800))
    {
        have_element_flag = 0;
        Ramp_Detection(); // 十字检测
    }
    else
    {
        Ramp_Process();
        have_element_flag = 1;
    }
}
