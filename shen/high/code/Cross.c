/*
 * Cross.c
 *
 *  Created on: 2022年5月13日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
Str_Cross   Cross_deal;
Enum_CrossType   CrossType;
Enum_CrossProcess  CrossProcess;
Str_RoadEN   REN;
uint8 Cross_num;
uint8 Cross_row;
uint8 Cross_col;
uint8 Cross_Hang = 8;
uint8 Cross_Hang_find = 25;
//Str_Boundary  Boundary;  //边界结构体


/***************************************************************
十字检测

* 函数名称： Cross_Detection()//十字处理
* 功能说明： 十字检测
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：     检测一直开着  十字检测
 *******************************************************************/
#if 1
void Cross_Detection()//十字检测
{
    uint8 temp_lx=0,temp_ly=0;
    temp_lx=Inflection_point.L_down_point.x,temp_ly=Inflection_point.L_down_point.y;
    uint8 temp_rx=0,temp_ry=0;
    temp_rx=Inflection_point.R_down_point.x,temp_ry=Inflection_point.R_down_point.y;

   if(Inflection_point.L_down_point.x>0||Inflection_point.R_down_point.x>0)//左或右下拐点找到
        {
          Cross_num=0;            //清除计数值    空白行连续性计数

          if((image1[temp_lx-1][temp_ly]>Threshold&&image1[temp_lx-2][temp_ly]>Threshold)||(image1[temp_rx-1][temp_ry]>Threshold&&image1[temp_rx-2][temp_ry]>Threshold))
          {
//              tft180_show_string(30, 60, "a");

          for(Cross_row=Boundary.StartLine; Cross_row>ROW_START ; Cross_row-- )     //在搜索到的黑白跳变点后，向上搜索白点，判断是否为干扰点
          {
             if(Boundary.RowLose[Cross_row]==4)//丢线数组 1——不丢线 2——丢右 3——丢左 4——丢线
             {
//                tft180_show_string(30, 60, "b");
                for(Cross_col=Cross_row; Cross_col>Cross_row-Cross_Hang_find&& Cross_row>Cross_Hang_find; Cross_col-- )      /*&&&&&&&&&调参处——最多从第15行开始向上扫15行*/
                {
                   if(Boundary.RowLose[Cross_col]==4)
                   {
//                      tft180_show_string(30, 60, "c");
                      Cross_num++;

                   }
                   else
                   {
                       break;
//                      if( Cross_num>=Cross_Hang)         /*&&&&&&&&&调参处——判定行数*/
//                      {
//                          //Roadtype_judge();
//                          //if(road_type==2)
//                         // {
//                          Cross_deal.Cross_flag=1;//十字flag
//                          CrossProcess=Find_Cross;
//                          RoadType= Cross_Road;
//                          Cross_row=ROW_START;  //清外循环
//                          gpio_set_level(BUZZER_PIN, 1);
//                         break;
//                         // }
//                      }
//                      else
//                      {
//                         Cross_num=0;
//                      }
                   }
                }
             }
          }
        }
       }
   if( Cross_num>=Cross_Hang)
   {
      Cross_deal.Cross_flag=1;//十字flag
      CrossProcess=Find_Cross;
      RoadType= Cross_Road;
      Cross_row=ROW_START;  //清外循环
      gpio_set_level(BUZZER_PIN, 1);
   }
   else
   {
      Cross_num=0;
   }
}
#endif

/***************************************************************
十字处理

* 函数名称：Cross_Process()//十字处理
* 功能说明： 十字处理
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：与其他芯片不同，需要给补线做出保护，不然超出图像范围就容易卡死单片机
*******************************************************************/
void Cross_Process()//十字处理
{
       uint8 SC_MUN=5;
       float  LeftCrossSlope;
       float  RightCrossSlope;
       switch(CrossProcess)
       {
        case Find_Cross:
          {
             //判断进入下一阶段
            if(Inflection_point.L_down_point.x==0&&Inflection_point.R_down_point.x==0)
            {
                CrossProcess=In_Cross;
            }
            if(Boundary.StartLine<30)//&&调参处
            {
                CrossProcess=In_Cross;
            }


              Cross_num=0;            //清除计数值    空白行连续性计数
              for(Cross_row=Boundary.StartLine; Cross_row>ROW_START ; Cross_row-- )     //在搜索到的黑白跳变点后，向上搜索白点，判断是否为干扰点
              {
                 if(Boundary.RowLose[Cross_row]==4)
                 {
                    Cross_num++;
                    if( Cross_num>Cross_Hang)
                    {
                       break;
                    }
                 }
              }
              if( Cross_num<Cross_Hang-2)
              {
                 CrossProcess=In_Cross;
              }


#if 1
             if(Inflection_point.L_down_point.x>0&&Inflection_point.R_down_point.x>0)  //开始补线    常规补线     左右下拐点全找到
             {
                if(Inflection_point.L_up_point.x!=0&&Inflection_point.R_up_point.x!=0)//左右上下拐点全找到
                {
                   CommonRectificate(&Boundary.LeftEdge[0],Inflection_point.L_up_point.x,Inflection_point.L_down_point.x+1);
                   CommonRectificate(&Boundary.RightEdge[0],Inflection_point.R_up_point.x,Inflection_point.R_down_point.x+1);
                }
                else if(Inflection_point.L_up_point.x!=0&&Inflection_point.R_up_point.x==0)//左上找到，右上没找到
                {
                   if(Inflection_point.L_up_point.y>Inflection_point.L_down_point.y)
                   {
                      CommonRectificate(&Boundary.LeftEdge[0],Inflection_point.L_up_point.x-1,Inflection_point.L_down_point.x+1);
                      for(Cross_row=Inflection_point.L_up_point.x-1;Cross_row<=Inflection_point.L_down_point.x+1;Cross_row++)
                      {
                         Boundary.RightEdge[Cross_row] = Boundary.LeftEdge[Cross_row]+ Cross_deal.Track_Width_forCross[Cross_row] ;
                         if ( Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                               }

                      }
                   }
                }
                else if(Inflection_point.L_up_point.x==0&&Inflection_point.R_up_point.x!=0)//右上找到左上没找到
                {
                   if(Inflection_point.R_up_point.y<Inflection_point.R_down_point.y)//右上在右下左侧
                   {
                      CommonRectificate(&Boundary.RightEdge[0],Inflection_point.R_up_point.x-1,Inflection_point.R_down_point.x+1);
                      for(Cross_row=Inflection_point.R_up_point.x-1;Cross_row<=Inflection_point.R_down_point.x+1;Cross_row++)
                      {
                        // Boundary.LeftEdge[Cross_row] = Boundary.RightEdge[Cross_row]- Cross_deal.Track_Width_forCross[Cross_row] ;
                         char temp_r;
                         char temp_l;
                         temp_r=Boundary.RightEdge[Cross_row];
                         temp_l=temp_r-Cross_deal.Track_Width_forCross[Cross_row] ;
                         if(temp_l<=0)
                         {
                             temp_l=1;

                         }
                         if (temp_l>(COL_END+1)-2)
                             {
                                 temp_l=(COL_END+1)-2;
                               }
                         Boundary.LeftEdge[Cross_row] =temp_l;

                      }
                   }
                }
                else
                {
                   if(Boundary.L_StartLine>Inflection_point.L_down_point.x+SC_MUN) //至少10个
                   {
                      // Cross.addL_flag=1;
                      LeftCrossSlope= Slope_Calculate(Inflection_point.L_down_point.x+1,Boundary.L_StartLine,&Boundary.LeftEdge[0]) ;
                      for(Cross_row=Inflection_point.L_down_point.x;Cross_row>ROW_START;Cross_row--)
                      {
                         Boundary.LeftEdge[Cross_row]=(int)((Cross_row-Inflection_point.L_down_point.x)*LeftCrossSlope+Inflection_point.L_down_point.y);
                         if ( Boundary.LeftEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.LeftEdge[Cross_row]=(COL_END+1)-2;
                             }

                         Boundary.RightEdge[Cross_row] = Boundary.LeftEdge[Cross_row]+ Cross_deal.Track_Width_forCross[Cross_row] ;
                         if ( Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                            }

                      }
                   }
                   else if(Boundary.R_StartLine>Inflection_point.R_down_point.x+SC_MUN)
                   {
                      // Cross.addR_flag=1;
                      RightCrossSlope=Slope_Calculate(Inflection_point.R_down_point.x+1,Boundary.R_StartLine,&Boundary.RightEdge[0]) ;

                      for(Cross_row=Inflection_point.R_down_point.x;Cross_row>ROW_START;Cross_row--)
                      {
                         Boundary.RightEdge[Cross_row]=(int)((Cross_row-Inflection_point.R_down_point.x)*RightCrossSlope+Inflection_point.R_down_point.y);
                         if ( Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                             }
                         char temp_r;
                         char temp_l;
                         temp_r=Boundary.RightEdge[Cross_row];
                         temp_l=temp_r-Cross_deal.Track_Width_forCross[Cross_row] ;
                         if(temp_l<=0)
                         {
                             temp_l=1;

                         }
                         if (temp_l>(COL_END+1)-2)
                             {
                                 temp_l=(COL_END+1)-2;
                               }
                         Boundary.LeftEdge[Cross_row] =temp_l;

                      }
                   }

                }
             }


             else if(Inflection_point.L_down_point.x>0&&Inflection_point.R_down_point.x==0)  //开始补线    常规补线
             {
                if(Inflection_point.L_up_point.x!=0)
                {
                   CommonRectificate(&Boundary.LeftEdge[0],Inflection_point.L_up_point.x,Inflection_point.L_down_point.x+1);
                   for(Cross_row=Inflection_point.L_up_point.x;Cross_row<=Inflection_point.L_down_point.x+1;Cross_row++)
                   {
                      Boundary.RightEdge[Cross_row] = Boundary.LeftEdge[Cross_row]+ Cross_deal.Track_Width_forCross[Cross_row] ;
                      if ( Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                          {
                              Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                            }

                   }
                }
                else
                {
                   if(Boundary.L_StartLine>Inflection_point.L_down_point.x+SC_MUN) //至少10个
                   {
                      // Cross.addL_flag=1;
                      LeftCrossSlope= Slope_Calculate(Inflection_point.L_down_point.x+1,Boundary.L_StartLine,&Boundary.LeftEdge[0]) ;

                      for(Cross_row=Inflection_point.L_down_point.x;Cross_row>ROW_START;Cross_row--)
                      {
                         Boundary.LeftEdge[Cross_row]=(int)((Cross_row-Inflection_point.L_down_point.x)*LeftCrossSlope+Inflection_point.L_down_point.y);
                         if ( Boundary.LeftEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.LeftEdge[Cross_row]=(COL_END+1)-2;
                               }



                         Boundary.RightEdge[Cross_row] = Boundary.LeftEdge[Cross_row]+ Cross_deal.Track_Width_forCross[Cross_row] ;
                         if ( Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                             {
                                 Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                               }

                      }
                   }
                }
             }


             else if(Inflection_point.L_down_point.x==0&&Inflection_point.R_down_point.x>0)  //开始补线    常规补线
             {
                if(Inflection_point.R_up_point.x!=0)
                {
                   CommonRectificate(&Boundary.RightEdge[0],Inflection_point.R_up_point.x,Inflection_point.R_down_point.x+1);

                   for(Cross_row=Inflection_point.R_up_point.x;Cross_row<=Inflection_point.R_down_point.x;Cross_row++)
                   {
                     // Boundary.LeftEdge[Cross_row] = Boundary.RightEdge[Cross_row]- Cross_deal.Track_Width_forCross[Cross_row] ;
                      char temp_r;
                      char temp_l;
                      temp_r=Boundary.RightEdge[Cross_row];
                      temp_l=temp_r-Cross_deal.Track_Width_forCross[Cross_row] ;
                      if(temp_l<=0)
                      {
                          temp_l=1;

                      }
                      if (temp_l>(COL_END+1)-2)
                          {
                              temp_l=(COL_END+1)-2;
                            }
                      Boundary.LeftEdge[Cross_row] =temp_l;

                   }
                }
                else
                {
                   if(Boundary.R_StartLine>Inflection_point.R_down_point.x+SC_MUN)
                   {
                      // Cross.addR_flag=1;
                    RightCrossSlope=Slope_Calculate(Inflection_point.R_down_point.x+1,Boundary.R_StartLine,&Boundary.RightEdge[0]) ;

                      for(Cross_row=Inflection_point.R_down_point.x;Cross_row>ROW_START;Cross_row--)
                      {
                       Boundary.RightEdge[Cross_row]=(int)((Cross_row-Inflection_point.R_down_point.x)*RightCrossSlope+Inflection_point.R_down_point.y);
                       if(Boundary.RightEdge[Cross_row]>(COL_END+1)-2)
                       {

                           Boundary.RightEdge[Cross_row]=(COL_END+1)-2;
                       }

                        //Boundary.LeftEdge[Cross_row] = Boundary.RightEdge[Cross_row]- Cross_deal.Track_Width_forCross[Cross_row] ;
                        char temp_r;
                        char temp_l;
                        temp_r=Boundary.RightEdge[Cross_row];
                        temp_l=temp_r-Cross_deal.Track_Width_forCross[Cross_row] ;
                        if(temp_l<=0)
                        {
                            temp_l=1;

                        }
                        if (temp_l>(COL_END+1)-2)
                            {
                                temp_l=(COL_END+1)-2;
                             }
                        Boundary.LeftEdge[Cross_row] =temp_l;

                      }
                   }

                }
             }
#endif
             break;
          }
        case In_Cross:
          {
              if(Boundary.StartLine>35)//&&调参处
              {
              CrossProcess=Out_Cross;
              }
             break;
          }

        case  Out_Cross :
          {
              Cross_deal.Cross_flag=0;//十字flag
              RoadType= else_road;
              gpio_set_level(BUZZER_PIN, 0);
              Obstacle.Obstacle_flag=0;
             break;
          }
        default:
          {
             break;
          }
       }

}
/***************************************************************
十字处理

* 函数名称： Cross_Detection()//十字处理
* 功能说明： 十字处理外部调用
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：
*******************************************************************/
void Cross_Deal()//十字检测
{

          if(Cross_deal.Cross_flag==0)
          {
              have_element_flag=0;
             for(Cross_row=ROW_END-5;Cross_row>=ROW_START+5;Cross_row--)
             {
                 Cross_deal.Track_Width_forCross[Cross_row]=(int)(0.8*Cross_row+22.6); //计算  圆环路宽
             }
             Cross_Detection();        //十字检测
          }
          else
          {
             Cross_Process();
             have_element_flag=1;
          }

}



