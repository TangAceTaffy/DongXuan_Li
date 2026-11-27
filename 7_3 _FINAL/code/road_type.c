/*
 * road_type.c
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
#include"math.h"
enum_RoadType RoadType;
uint8 Elements_Sequence[8];//={0,0,0,0,0,0,0,0,0};//初始化
uint8 Elements_Sequence_All[11]={0,1,2,31,13,41,14,5,61,16,7};
//uint8 Elements_Sequence[8]={1,13,61,7,0,0,0,0};//8个元素
uint8 Elements_Current_Sequence=0;//将运行元素的指针

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
//uint16 long_l,long_r,long_m;
//uint16 mid_point_x,mid_point_y;
////-------------------------------------------------------------------------------------------------------------------
////  @brief
////  @param
////  @param
////  @return
////  @since
////  Sample usage:
////  @note
////-------------------------------------------------------------------------------------------------------------------
//void Roadtype_judge(void)//十字三岔加强判断
//{
//    long_l=40;long_r=40;long_m=40;
//    mid_point_x=0;mid_point_y=0;

//    if(Inflection_point.R_down_point.x!=0 && Inflection_point.L_down_point.x!=0)
//    {
//        for(int i=Inflection_point.L_down_point.x ; i>=3 ; i--)
//        {
//            if(difference_sum(image[i][Inflection_point.L_down_point.y],image[i-2][Inflection_point.L_down_point.y])>=g_threshold_value
//            && mark_middle_num(image[i][Inflection_point.L_down_point.y],image[i-2][Inflection_point.L_down_point.y],Threshold))
//            {
//                long_l=Inflection_point.L_down_point.x-i;break;
//            }
//        }
//        for(int i=Inflection_point.R_down_point.x ; i>=3 ; i--)
//        {
//            if(difference_sum(image[i][Inflection_point.R_down_point.y],image[i-2][Inflection_point.R_down_point.y])>=g_threshold_value
//            && mark_middle_num(image[i][Inflection_point.R_down_point.y],image[i-2][Inflection_point.R_down_point.y],Threshold))
//            {
//                long_r=Inflection_point.R_down_point.x-i;break;
//            }
//        }
//        mid_point_y=(Inflection_point.R_down_point.y+Inflection_point.L_down_point.y)/2;
//        mid_point_x=(Inflection_point.R_down_point.x+Inflection_point.L_down_point.x)/2;
//        for(int i=mid_point_x ; i>=3 ; i--)
//        {
//            if(difference_sum(image[i][mid_point_y],image[i-2][mid_point_y])>=g_threshold_value
//            && mark_middle_num(image[i][mid_point_y],image[i-2][mid_point_y],Threshold))
//            {
//                 long_m=mid_point_x-i;break;
//             }
//        }

//        //if( long_m- (long_l+long_r)/2 >=5) {road_type=2;}//road_type_flag=1;
//        //if( (long_l+long_r)/2- long_m >=5) {road_type=1;}//road_type_flag=1;
//        if( long_m>long_l||long_m>long_r) {road_type=2;}//road_type_flag=1;
//        if( long_l>long_m||long_r>long_m) {road_type=1;}//road_type_flag=1;
//        //lcd_showint16(0,7,road_type);
//        //lcd_showint16(50,5,long_r);
//        //lcd_showint16(50,6,long_l);
//        //lcd_showint16(50,7,long_m);
//    }
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief
//  @param
//  @param
//  @return
//  @since
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
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
