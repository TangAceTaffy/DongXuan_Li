/*
 * road_type.c
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
#include"math.h"
enum_RoadType RoadType;
//用于写死元素顺序
uint8 Elements_Sequence[8];//={0,0,0,0,0,0,0,0,0};//初始化全部赋值为0也就是所有元素都识别的状态
uint8 Elements_Sequence_All[11]={0,1,2,31,13,41,14,5,61,16,7};//所有元素种类
//uint8 Elements_Sequence[8]={1,13,61,7,0,0,0,0};//8个元素
uint8 Elements_Current_Sequence=0;//下个将运行的元素的指针
/*
 *0：所有元素都识别
 *1：三岔
 *2：十字
 *3：小圆环：左环→31 右环→13
 *4：大圆环：左环→41 右环→14
 *5：坡道
 *6：障碍物：左障→61 右障→16
 *7：斑马线
 */
/***************************************************************
* 函数名称：void Roadtype_check(void)
* 功能说明：检测元素类型，如果识别元素便开始执行元素；同时限定元素顺序
* 参数说明：
* 函数返回：
* 修改时间：2024年7月28日
* 备 注：
***************************************************************/
void Roadtype_check(void)
{
    if(Elements_Sequence[Elements_Current_Sequence]==0)
    {
    if(Round.Round_flag==0 && Cross_deal.Cross_flag==0 && Ramp_deal.Ramp_flag==0 && Obstacle.Obstacle_flag==0)//&& Garage_deal.Garage_flag==0 && Fork_deal.Fork_flag==0 && RoadType!=6)//&& start_flag==0)
    {
        Obstacl_Deal();
        Garage_Deal(1,COL/2-1);
        Ramp_Deal();
        Cross_Deal();
        Round_Deal();
    }
    if(Round.Round_flag==0 && Cross_deal.Cross_flag==1 && Ramp_deal.Ramp_flag==0 && RoadType!=Garage)//&& Garage_deal.Garage_flag==0 && Fork_deal.Fork_flag==0 && RoadType!=6)//&& start_flag==0)
    {
        Cross_Deal();
    }
    if(Round.Round_flag==1 && Cross_deal.Cross_flag==0 && Ramp_deal.Ramp_flag==0 && RoadType!=Garage)// Garage_deal.Garage_flag==0 && Fork_deal.Fork_flag==0 && RoadType!=6)//&& start_flag==0)
    {
        Round_Deal();
    }
    if(Ramp_deal.Ramp_flag==1)//防止抖动成别的元素
    {
        Ramp_Deal();
    }
    if(Obstacle.Obstacle_flag==1)//防止抖动成别的元素
    {
        Obstacl_Deal();
    }
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==1)
    {
        Ramp_Deal();
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==31||Elements_Sequence[Elements_Current_Sequence]==13)
    {
        Round_Deal();
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==41||Elements_Sequence[Elements_Current_Sequence]==14)
    {
        Round_Deal();
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==5)
    {
        Ramp_Deal();
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==61||Elements_Sequence[Elements_Current_Sequence]==16)
    {
        Obstacl_Deal();
    }
    else if(Elements_Sequence[Elements_Current_Sequence]==7)
    {
        Garage_Deal(1,COL/2-1);
    }
}
