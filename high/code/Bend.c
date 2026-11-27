/*
 * Bend.c
 *
 *  Created on: Jul 3, 2022
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
Enum_ElseRoadType  ElseRoadType;
/*----------------------------------------------------------------------------------------------------------------
*  @brief   弯直道判断
*  @param
*
*  @return  void
*  @since   v1.0
*  Sample usage:
//-----------------------------------------------------------------------------------------------------------------*/
uint8 search_count;//测试用
void Distinguish(void)
{
    uint8 search_count;
//    uint8 search_row=0;
    uint8 s_flag=0;    //直道标志位
    uint8 c_flag=0;    //弯道标志位
    uint8 c_big_flag=0 ; //大弯标志位
    uint8 s_obstacle_flag=0;    //直道标志位
    if(Boundary.EndLine>ROW_START && Boundary.EndLine<10 && Boundary.MiddleLine[10]>20 && Boundary.MiddleLine[10]<60)//结束行在第10行，中线值在左20右20内,初判断
    {
      search_count=0;
//      search_row=0;
      //从下向上搜，找连续偏差不大的点
      for(uint8 i=30;i>Boundary.EndLine;i--)
      {
            if(ABS(Boundary.MiddleLine[i]-Boundary.MiddleLine[i-1])<=2 )
            {
              search_count++;
            }
              else
              {
//                search_row=i;
                break;
              }
      }
     if(search_count>15)//直道
     {
          c_flag=0;
          s_flag=1;
          s_obstacle_flag=0;
     }
//     else if(search_count>3&&search_count<15)//障碍物直道
//     {
//         c_flag=0;
//         s_flag=0;
//         s_obstacle_flag=1;
//     }
     else//弯道
     {
         c_flag=1;
         s_flag=0;
         s_obstacle_flag=0;
     }

   }


    /*结束行在最后*/
    else if (Boundary.EndLine<=ROW_START && Boundary.MiddleLine[Boundary.EndLine+1]>25&&Boundary.MiddleLine[Boundary.EndLine+1]<55)
      {
        search_count=0;
 //       search_row=0;
        for(uint8 i=30;i>Boundary.EndLine;i--)
        {
          if(ABS( Boundary.MiddleLine[i]-Boundary.MiddleLine[i-1] )<3 )
          {
            search_count++;
          }
          else
          {
//              search_row=i;
             // break;
          }
        }
        if(search_count>27)
        {
            c_flag=0;
            s_flag=1;
            s_obstacle_flag=0;
        }

//        else if(search_count>9&&search_count<27)
//        {
//            c_flag=0;
//            s_flag=0;
//            s_obstacle_flag=1;
//        }

        else
        {
            c_flag=1;
            s_flag=0;
            s_obstacle_flag=0;
        }
      }

    else if(Boundary.EndLine>=15)//没有用到
    {
        if(Boundary.RowLose[Boundary.EndLine+1]==3 &&Boundary.RowLose[Boundary.EndLine+3]==3
                &&Boundary.RowLose[ROW_END-5]==3 &&Boundary.RowLose[ROW_END-7]==3 )
        {
            //c_flag=1;
            c_big_flag=1;
            s_flag=0;
        }
        if(Boundary.RowLose[Boundary.EndLine+1]==2 &&Boundary.RowLose[Boundary.EndLine+3]==2
                &&Boundary.RowLose[ROW_END-5]==2 &&Boundary.RowLose[ROW_END-7]==2 )
        {
            //c_flag=1;
            c_big_flag=1;
            s_flag=0;
        }
    }


    else//结束行靠前
    {
        c_flag=1;
        s_flag=0;
    }


    if(c_flag==1 && s_flag==0 && c_big_flag==0 && s_obstacle_flag==0)
    {
        ElseRoadType=c_road;
    }
    if(c_flag==0 && s_flag==1 && c_big_flag==0 && s_obstacle_flag==0)
    {
        ElseRoadType=s_road;
//        gpio_set_level(BUZZER_PIN, 1);
    }
    if(c_flag==0 && s_flag==0 && c_big_flag==0 && s_obstacle_flag==1)
    {
        ElseRoadType=s_road_obstacle;
    }
    if(c_big_flag==1)//未用到
    {
        ElseRoadType=c_road_big;
    }

}
