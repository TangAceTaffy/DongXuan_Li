/*
 * Zebra.c
 *
 *  Created on: 2024年4月5日
 *      Author: icand
 */
#include "zf_common_headfile.h"
float Garage_Flag=0;
float Garage_Check_Point=0;
void Garage_Deal(unsigned char Col_START,unsigned char Col_END) //入库判断
{
    uint8 flag_count = 0;
    uint8 row, col;
    if(distance>=1000)//车子开过一段距离后再识别斑马线为了防止起点经过斑马线停止
    {
        for(row = 26; row >= 25; row--)     //扫描两行获取跳变点数量原26-25
        {
           for(col = COL_START; col < COL_END - 1; col++)
           {
               if(difference_sum(image1[row][col],image1[row][col+COL_SPACE])>=g_threshold_value &&
                  mark_middle_num(image1[row][col],image1[row][col+COL_SPACE],Threshold))
               {
                   flag_count++;
               }
           }
        }
        if(flag_count >= 10||RoadType==Garage)       //原本14 判断对应跳变点数量,加个RoadType==Garage是为了防止过了车库后flag_count不满足了,且编码器未积分到goal
            {
                RoadType = Garage;
                gpio_set_level(BUZZER_PIN, 1);
                if(Garage_Check_Point==0)
                {
                    Garage_Check_Point=distance;//防止反复赋
                }
                if(distance-Garage_Check_Point>=30)//保证整个车通过斑马线
                {
                    Garage_Flag=1;
                    gpio_set_level(BUZZER_PIN, 0);
                    //return 1;
                }

            }
    }

}
/***************************************************************
出界保护
* 函数名称：void protect(void)
* 功能说明：检测第45行的像素点只要黑色像素点大于71个，就停止车辆
* 参数说明：
* 函数返回：void uint8 threshold
* 修改时间：2018年3月7日
* 备 注：
***************************************************************/
//出界保护
int SUM=0;
void protect(void)
{
    unsigned char sum;
    uint8 row, col;
    row=45;
    sum=0;
    for(col=0;col<COL_END - 1;col++)
    {
        if(image1[row][col]<=Threshold)
            sum++;
    }
    SUM=sum;
    if(SUM>=71)
    {
        Garage_Flag=1;
    }
    return;
}
