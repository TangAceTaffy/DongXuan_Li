/*
 * Roundabout.c
 *
 *  Created on: 2022年5月13日
 *      Author: hakuya
 */

#include "zf_common_headfile.h"


//enum_RoadType  RoadType;
Str_Round  Round={0};
RoundTypeDef RoundType;
RoundSizeTypeDef RoundSize;
RoundProcessTypeDef RoundProcess;

unsigned char  Round_row=0;
unsigned char  Round_col=0;
int  Round_num=0;
int  Round_num_1=0;
unsigned char  LeftLoopTemp_R=0,LeftLoopTemp_C=0,Inflection_Temp_x,Inflection_Temp_y;
float  LeftLoopSlope;
float  RightLoopSlope;
float Distance_Leave_Round2;
/***************************************************************
圆环检测

* 函数名称： Round_Detection(Str_Boundary *str,Str_Round *round)
* 功能说明： 圆环检测
* 参数说明：
* 函数返回：void
* 修改时间：
* 备 注：     检测一直开着
*              圆环检测  1、判断一边有下拐点，一边没有下拐点，且拐点位置离结束行不不少于5行 2、拐点侧丢线 3非拐点侧直线
*************************************************************/
void Round_Detection(Str_Boundary *str,Str_Round *round) //圆环
{
       //左环
       //检测到左下拐点，没检测到右下拐点，结束行比拐点远很多
       if(Inflection_point.L_down_point.x!=0&&Inflection_point.R_down_point.x==0&&str->EndLine<Inflection_point.L_down_point.x-5)
       {
          //左下拐点行的上面三行左边丢线
          if(str->LeftEdge[Inflection_point.L_down_point.x-1]==0&&str->LeftEdge[Inflection_point.L_down_point.x-2]==0&&str->LeftEdge[Inflection_point.L_down_point.x-3]==0)
          {
             round->Entrance_count=0;//圆环入口计数清零
             if(Inflection_point.L_down_point.x+5>ROW_END-1)
                Round_row=ROW_END-1;
             else
                Round_row=Inflection_point.L_down_point.x+5;
             for(;Round_row>Inflection_point.L_down_point.x-40&&Round_row>=ROW_START;Round_row--)//从左拐点下面5行到上面10行进行搜索
             {
                if(str->RightEdge[Round_row+1]!=0&&str->RightEdge[Round_row]!=0)
                {
                   //如果右边正常递减，且不丢线     斜率符合要求
                   if(str->RightEdge[Round_row+1]-str->RightEdge[Round_row]>=0 &&str->RightEdge[Round_row+1]-str->RightEdge[Round_row]<=2)
                   {
                      round->Entrance_count++; //圆环入口计数增加
                   }
                }
             }
             //tft180_show_int32(60,120,round->Entrance_count,2);
             if(round->Entrance_count>=25)//min修改，其中有13行满足条件即可判定为圆环
             {
                round->Round_flag=1;
                RoundType=Left_Round;
                RoundProcess=Find_Round;

                RoadType= Round_Road;
                gpio_set_level(BUZZER_PIN, 1);
                //RoundSize=Large_Round;   //待定


//                Garage_Detection(&Boundary,45);
//                if(RoadType==Garage)
//                {
//                    Garage_deal.Garage_time--;
//                    RoadType=else_road;
//                    Garage_deal.Garage_flag=0;
//                    Round.Round_flag=0;
//                }
             }
          }
       }

       //右环
       //检测到右下拐点，没检测到左下拐点，结束行比拐点远很多
       else if(Inflection_point.R_down_point.x!=0&&Inflection_point.L_down_point.x==0&&str->EndLine<Inflection_point.R_down_point.x-5)
       {
          //右下拐点行的上面三行左边丢线
          if(str->RightEdge[Inflection_point.R_down_point.x-1]==0&&str->RightEdge[Inflection_point.R_down_point.x-2]==0&&str->RightEdge[Inflection_point.R_down_point.x-3]==0)
          {
             round->Entrance_count=0;//圆环入口计数清零
             if(Inflection_point.R_down_point.x+5>ROW_END-1)
                Round_row=ROW_END-1;
             else
                Round_row=Inflection_point.R_down_point.x+5;
             for(;Round_row>Inflection_point.R_down_point.x-40&&Round_row>=ROW_START;Round_row--)//从右拐点下面5行到上面10行进行搜索
             {
                if(str->LeftEdge[Round_row+1]!=0 && str->LeftEdge[Round_row]!=0)
                {
                   //如果左边正常递增，且不丢线
                   if(str->LeftEdge[Round_row]-str->LeftEdge[Round_row+1]>=0&&str->LeftEdge[Round_row]-str->LeftEdge[Round_row+1]<=2)
                   {
                      round->Entrance_count++; //圆环入口计数增加
                   }
                }
             }
//             float Round_k=Slope_Calculate(5,45,&Boundary.LeftEdge[0]);
//             float k=(str->LeftEdge[45] - str->LeftEdge[5])  / (float)40;
//             tft180_show_float(60, 60, Round_k, 2, 3);
//             tft180_show_float(60, 80, k, 2, 3);

             //tft180_show_int32(60,120,round->Entrance_count,2);
             if(round->Entrance_count>=33 )//min修改，其中有13行满足条件即可判定为圆环
             {
                round->Round_flag=1;
                RoundType=Right_Round;

                RoadType= Round_Road;
                //RoundSize=Large_Round;
                RoundProcess=Find_Round;
                gpio_set_level(BUZZER_PIN, 1);



//                Garage_Detection(&Boundary,47);
//                if(RoadType==Garage)
//                {
//                    Garage_deal.Garage_time--;
//                    RoadType=else_road;
//                    Garage_deal.Garage_flag=0;
//                    Round.Round_flag=0;
//                }
             }
          }
       }
       //lcd_showint8(100,7, RoundProcess);
      // lcd_showint8(100,6, RoundType);
       //lcd_showint32(100,7, RoundProcess,1);
//       if(black_white(image[40],0,79,Threshold)>=6 || black_white(image[45],0,79,Threshold)>=6)
//       {
//         RoadType=else_road;
//         round->Round_flag=0;
//         RoundProcess=0;
//       }
}
/***************************************************************
圆环处理

* 函数名称： Round_Detection(Str_Boundary *str,Str_Round *round)
* 功能说明： 圆环处理
* 参数说明：
* 函数返回：voiold
* 修改时间：
* 备 注：     检测一直开着
*              圆环检测  1、判断一边有下拐点，一边没有下拐点，且拐点位置离结束行不不少于5行 2、拐点侧丢线 3非拐点侧直线
*************************************************************/
#if 1
float  LeftRoundSlope;
float  RightRoundSlope;
float angke_yaw_round;
uint8 AC_round_data[] = {0xac,0x01};
void Round_Process(Str_Boundary *str,Str_Round *round)
{
    switch(RoundType)
    {
        case Left_Round:
        {
            switch(RoundProcess)
                        {
               /*=========*/case Find_Round://发现圆环=========================================================
                            {



                                //wireless_ch573_send_buff(AC_round_data, sizeof(AC_round_data));
                                //*进入下个阶段的判定---------------------------------------------*/
                                if(str->L_StartLine<40 && str->L_StartLine>30)   //修改参数
                                {
                                    Round_num=0;
                                    for(Round_row=str->L_StartLine;Round_row>=str->L_StartLine-8&&Round_row>=ROW_START+1;Round_row--)   //防止误判     检测换中心岛
                                {
                                    if(str->LeftEdge[Round_row]!=0&&str->LeftEdge[Round_row-1]!=0)
                                    {
                                        Round_num+=str->LeftEdge[Round_row]-str->LeftEdge[Round_row-1] ;
                                    }
                                    else
                                    {
                                        Round_num=0;
                                    }
                                }
                                   // tft180_show_int32(60,80,Round_num,3);
                                if(Round_num<-3)
                                {
                                    Round_num=0;
                                    RoundProcess=Find_Gap;//就认为有缺口
                                 }
                               }
                               //用于区分大小环
                               if(Distance_Leave_Round2==0)
                               {
                                   Distance_Leave_Round2=distance;//防止反复赋值
                               }

                                //发现环阶段补线-----------------------------------------------------
                                for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                                {
                                   if(str->RightEdge[Round_row])
                                   {
                                       char temp_r;
                                       char temp_l;
                                       char track;
                                       temp_r=str->RightEdge[Round_row];
                                       track=Round.Track_Width_forRound[Round_row];
                                       temp_l=temp_r-track-1;
                                       if(temp_l>=79)
                                       {
                                           temp_l=78;

                                       }
                                       if(temp_l<=1)
                                       {
                                           temp_l=1;

                                       }
                                       str->LeftEdge[Round_row]=temp_l;
                                     // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                                   }
                                   else
                                   {
                                      str->LeftEdge[Round_row]=0;
                                   }
                                }
                                break;
                            }

              /*=========*/ case Find_Gap://发现空隙=====================================
                            {
                                //用于区分大小环
                                if(distance-Distance_Leave_Round2>=100)
                                {
                                    RoundSize=Large_Round;
                                }
                                else
                                {
                                    RoundSize=Small_Round;
                                }

                                if(Inflection_point.L_up_point.x!=0 )
                                {
                                     Round_num=0;
                                                                                        // Round_num_1=0;
                                    RoundProcess=Into_Round;
                                    angke_yaw=0;//进环前yaw角初始化为0
                                    angke_yaw_round=0;
                                }

                                //发现gap阶段补线-----------------------------------------------------
                                for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                                                    {
                                                       if(str->RightEdge[Round_row])
                                                       {
                                                           char temp_r;
                                                           char temp_l;
                                                           char track;
                                                           temp_r=str->RightEdge[Round_row];
                                                           track=Round.Track_Width_forRound[Round_row];
                                                           temp_l=temp_r-track-1;
                                                           if(temp_l>=79)
                                                           {
                                                               temp_l=78;

                                                           }
                                                           if(temp_l<=1)
                                                           {
                                                               temp_l=1;

                                                           }
                                                           str->LeftEdge[Round_row]=temp_l;
                                                         // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                                                       }
                                                       else
                                                       {
                                                          str->LeftEdge[Round_row]=0;
                                                       }
                                                    }



                                break;
                            }
                /*=========*/case Into_Round://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
                               // angke_yaw_round=angke_yaw;
//                                if(angke_yaw>20)
//                                {
//                                    RoundProcess=Into_Round2;
//                                }
                                if( angke_yaw>48)
                                {
                                    RoundProcess=In_Round;
                                }

                                //进环阶段阶段补线-----------------------------------------------------
                               uint8 flag;flag=0;
                                for(uint8 h=ROW_END;h>ROW_START;h--)
                                { if(flag==1)break;
                                        for(uint8 i=h;i>ROW_START;i--)
                                        {if(flag==1)break;
                                            for(uint8 j=COL_START;j<40;j++)

                                            {
                                                if(image1[i][j]>=Threshold&&image1[i][j+1]<Threshold)
                                                {
                                                    LeftLoopTemp_R=i;//hang
                                                    LeftLoopTemp_C=j;//lie
                                                    str->EndLine=i;
                                                    flag=1;
                                                    break;
                                                }

                                            }

                                        }

                                }
                                /*进环斜率*/
                                  if (RoundSize==Small_Round)     LeftLoopSlope=1.0;
                                  if (RoundSize==Large_Round)     LeftLoopSlope=0.3;
//                                if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(ROW_END-8-LeftLoopTemp_R);//>0
//                                else LeftLoopSlope=1;
                                                             for(uint8 i=0;i<=ROW_END-1-LeftLoopTemp_R;i++)
                                                             {
                                                                str->RightEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);

                                                                if(str->RightEdge[LeftLoopTemp_R+i]>=78)
                                                                {
                                                                    str->RightEdge[LeftLoopTemp_R+i]=78;
                                                                }
                                                                if(str->RightEdge[LeftLoopTemp_R+i]<=1)
                                                                {
                                                                    str->RightEdge[LeftLoopTemp_R+i]=1;
                                                                }
                                                             // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

                                                                if(str->RightEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
                                                                   break;
                                                             }

                                      break;
                            }
                /*=========*/case Into_Round2://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
                               // angke_yaw_round=angke_yaw;
                                if( angke_yaw>48/2)
                                {
                                    RoundProcess=In_Round;
                                }

                                //进环阶段阶段补线-----------------------------------------------------
                               uint8 flag;flag=0;
                                for(uint8 h=ROW_END;h>ROW_START;h--)
                                { if(flag==1)break;
                                        for(uint8 i=h;i>ROW_START;i--)
                                        {if(flag==1)break;
                                            for(uint8 j=COL_START;j<40;j++)

                                            {
                                                if(image1[i][j]>=Threshold&&image1[i][j+1]<Threshold)
                                                {
                                                    LeftLoopTemp_R=i;//hang
                                                    LeftLoopTemp_C=j;//lie
                                                    str->EndLine=i;
                                                    flag=1;
                                                    break;
                                                }

                                            }

                                        }

                                }
                                /*进环斜率*/
                                                             //LeftLoopSlope=1.8;
                               // if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(ROW_END-7-LeftLoopTemp_R);//>0
                                if (RoundSize==Small_Round)     LeftLoopSlope=1.0;
                                if (RoundSize==Large_Round)     LeftLoopSlope=0.3;
                                                             for(uint8 i=0;i<=ROW_END-1-LeftLoopTemp_R;i++)
                                                             {
                                                                str->RightEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);

                                                                if(str->RightEdge[LeftLoopTemp_R+i]>=78)
                                                                {
                                                                    str->RightEdge[LeftLoopTemp_R+i]=78;
                                                                }
                                                                if(str->RightEdge[LeftLoopTemp_R+i]<=1)
                                                                {
                                                                    str->RightEdge[LeftLoopTemp_R+i]=1;
                                                                }
                                                             // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

                                                                if(str->RightEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
                                                                   break;
                                                             }
                                      break;
                            }
                /*=========*/case In_Round://==========================================================
                            {
                                gpio_set_level(BUZZER_PIN, 0);
                                //*进入下个阶段的判定----------------------------------------*/
                                if(angke_yaw>230 )//&& Inflection_point.R_down_point.x)
                                {
                                    RoundProcess=Out_Round;
                                }
                                //环内阶段阶段补线-----------------------------------------------------

                                    //#无补线操作#//
                                break;
                            }
                /*=========*/case Out_Round://==========================================================
                             {
                                 //*进入下个阶段的判定----------------------------------------*/
                                 if(angke_yaw>325)
                                 {
                                     RoundProcess=Leave_Round;
                                 }
                                 //准备出环阶段阶段补线-----------------------------------------------------
                                 LeftLoopTemp_R=ROW_END-1;
                                 LeftLoopTemp_C=COL_END;
                                 if (RoundSize==Small_Round) LeftLoopSlope=-2.1;//-2.2
                                 if (RoundSize==Large_Round) LeftLoopSlope=-0.8;
//                                 if(Inflection_point.R_down_point.x && Inflection_point.R_down_point.x>24)
//                                 {
//                                     LeftLoopTemp_R=Inflection_point.R_down_point.x;
//                                     LeftLoopTemp_C=Inflection_point.R_down_point.y;
//                                     LeftLoopSlope=-2.9;
//                                 }
                                 for(int8 i=0;i<=LeftLoopTemp_R;i++)
                                 {
                                     str->RightEdge[LeftLoopTemp_R-i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
                                     if(str->RightEdge[LeftLoopTemp_R-i]>=COL_END)
                                     {
                                         str->RightEdge[LeftLoopTemp_R-i]=COL_END;
                                     }
                                     if(str->RightEdge[LeftLoopTemp_R-i]<=COL_START)
                                     {
                                         str->RightEdge[LeftLoopTemp_R-i]=COL_START;
                                     }
                                 }
                                 break;
                             }
                /*=========*/case Leave_Round://==========================================================
                              {
                                  //*进入下个阶段的判定----------------------------------------*/
                                 if(str->L_StartLine>40&&angke_yaw>=360)//修改参数
                                 {
                                       RoundProcess=Leave_Round2;
                                       angke_yaw=0;
                                 }

                                  //出环阶段阶段补线-----------------------------------------------------
                                  for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                                  {
                                     if(str->RightEdge[Round_row])
                                     {
                                         char temp_r;
                                         char temp_l;
                                         char track;
                                         temp_r=str->RightEdge[Round_row];
                                         track=Round.Track_Width_forRound[Round_row];
                                         temp_l=temp_r-track-1;//临时左边线等于右边线的列-道路宽度-1
                                         if(temp_l>=79)
                                         {
                                             temp_l=78;

                                         }
                                         if(temp_l<=1)
                                         {
                                             temp_l=1;

                                         }
                                         str->LeftEdge[Round_row]=temp_l;
//                                       // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                                     }
                                     else
                                     {
                                        str->LeftEdge[Round_row]=0;
                                     }
                                  }

                                  break;
                              }
                /*=========*/case Leave_Round2://==========================================================
                            {

//                                if(Distance_Leave_Round2==0)
//                                {
//                                    Distance_Leave_Round2=distance;//防止反复赋值
//                                }
//                                if(distance-Distance_Leave_Round2>=100)
//                                {
                                    Round.Round_flag=0;
                                    RoundProcess=0;
                                    RoadType= else_road;
                                    Distance_Leave_Round2=0;
//                                }
//                                //出环补线直行
//                                LeftLoopTemp_R=ROW_END-1;
//                                LeftLoopTemp_C=COL_START;
//                                LeftLoopSlope=0.5;
//                                if(Inflection_point.R_down_point.x)
//                                {
//                                  LeftLoopTemp_R=Inflection_point.R_down_point.x;
//                                  LeftLoopTemp_C=Inflection_point.R_down_point.y;
//                                  LeftLoopSlope=0.5;
//                                }
//                                for(int8 i=0;i<=LeftLoopTemp_R;i++)
//                                {
//                                  str->LeftEdge[LeftLoopTemp_R-i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
//                                  if(str->LeftEdge[LeftLoopTemp_R-i]>=COL_END)
//                                  {
//                                     str->LeftEdge[LeftLoopTemp_R-i]=COL_END;
//                                  }
//                                  if(str->LeftEdge[LeftLoopTemp_R-i]<=COL_START)
//                                  {
//                                     str->LeftEdge[LeftLoopTemp_R-i]=COL_START;
//                                  }
//                                }
                                break;
                            }

                        }
            break;
        }
//以下为右环#########################################################################################################################################
//以下为右环#########################################################################################################################################
        case Right_Round:
        {
            switch(RoundProcess)
            {
   /*=========*/case Find_Round://发现圆环=========================================================
                {
                    //*进入下个阶段的判定---------------------------------------------*/
                    if(str->R_StartLine<40 && str->R_StartLine>30 )   //修改参数
                    {
                        Round_num=0;
                        for(Round_row=str->R_StartLine;Round_row>=str->R_StartLine-8&&Round_row>=ROW_START+1;Round_row--)   //防止误判     检测换中心岛
                    {
                        if(str->RightEdge[Round_row]!=0&&str->RightEdge[Round_row-1]!=0)
                        {
                            Round_num+=str->RightEdge[Round_row]-str->RightEdge[Round_row-1] ;
                        }
                        else
                        {
                            Round_num=0;
                        }
                    }
                        //tft180_show_int32(60,80,Round_num,3);
                    if(Round_num>3)
                    {
                        Round_num=0;
                        RoundProcess=Find_Gap;//就认为有缺口
                    }
                   }
                    //用于区分大小环
                    if(Distance_Leave_Round2==0)
                    {
                       Distance_Leave_Round2=distance;//防止反复赋值
                    }
                    //发现环阶段补线-----------------------------------------------------
                    for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                    {
                       if(str->LeftEdge[Round_row])
                       {
                           char temp_r;
                           char temp_l;
                           char track;
                           temp_r=str->LeftEdge[Round_row];
                           track=Round.Track_Width_forRound[Round_row];
                           temp_l=temp_r+track+1;
                           if(temp_l>=79)
                           {
                               temp_l=78;

                           }
                           if(temp_l<=1)
                           {
                               temp_l=1;

                           }
                           str->RightEdge[Round_row]=temp_l;
                         // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                       }
                       else
                       {
                          str->RightEdge[Round_row]=0;
                       }
                    }
                    break;
                }

  /*=========*/ case Find_Gap://发现空隙=====================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
                    //用于区分大小环
                    if(distance-Distance_Leave_Round2>=100)
                    {
                       RoundSize=Large_Round;
                    }
                    else
                    {
                      RoundSize=Small_Round;
                    }
                    if(Inflection_point.R_up_point.x!=0 )
                     {
                         Round_num=0;
                                                                             // Round_num_1=0;
                         RoundProcess=Into_Round;
                         angke_yaw=0;//进环前yaw角初始化为0
                         angke_yaw_round=0;
                     }
                    //发现gap阶段补线-----------------------------------------------------
                    for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                                        {
                                           if(str->LeftEdge[Round_row])
                                           {
                                               char temp_r;
                                               char temp_l;
                                               char track;
                                               temp_r=str->LeftEdge[Round_row];
                                               track=Round.Track_Width_forRound[Round_row];
                                               temp_l=temp_r+track+1;
                                               if(temp_l>=79)
                                               {
                                                   temp_l=78;

                                               }
                                               if(temp_l<=1)
                                               {
                                                   temp_l=1;

                                               }
                                               str->RightEdge[Round_row]=temp_l;
                                             // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                                           }
                                           else
                                           {
                                              str->RightEdge[Round_row]=0;
                                           }
                                        }



                    break;
                }
#if 1
  /*=========*/case Into_Round://==========================================================
               {
                   //*进入下个阶段的判定----------------------------------------*/
                  // angke_yaw_round=angke_yaw;
                   if( angke_yaw<-48)
                   {
                       RoundProcess=In_Round;
                   }

                   //进环阶段阶段补线-----------------------------------------------------
                  uint8 flag;flag=0;
                   for(uint8 h=ROW_END;h>ROW_START;h--)
                   { if(flag==1)break;
                           for(uint8 i=h;i>ROW_START;i--)
                           {if(flag==1)break;
                               for(uint8 j=COL_END;j>40;j--)

                               {
                                   if(image1[i][j]>=Threshold&&image1[i][j-1]<Threshold)
                                   {
                                       LeftLoopTemp_R=i;//hang
                                       LeftLoopTemp_C=j;//lie
                                       str->EndLine=i;
                                       flag=1;
                                       break;
                                   }

                               }

                           }

                       //}
                   }
                   /*进环斜率*/
                   if (RoundSize==Small_Round)     LeftLoopSlope=-1.0;
                   if (RoundSize==Large_Round)     LeftLoopSlope=-0.3;

//                   LeftLoopSlope=-1.8;//*(str->RightEdge[aa1]-aa2)/(aa1-LeftLoopTemp_R);
//                   if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(LeftLoopTemp_R-ROW_END+8);
//                   else LeftLoopSlope=-1.0                                ;
                                                for(uint8 i=0;i<=ROW_END-LeftLoopTemp_R;i++)
                                                {
                                                    int temp_1=0;
                                                   temp_1=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
                                                   if(temp_1>=79)
                                                   {
                                                       temp_1=79;
                                                   }
                                                   if(temp_1<=1)
                                                   {
                                                       temp_1=1;
                                                   }
                                                // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;
                                                   str->LeftEdge[LeftLoopTemp_R+i]=temp_1;

//                                                   if(temp_1>78||LeftLoopTemp_R+i>ROW_END)
//                                                      break;
                                                }
//                                                for(uint8 i=1;i<=LeftLoopTemp_R-ROW_START;i++)
//                                                {
//                                                    str->LeftEdge[LeftLoopTemp_R-i]=(int)(-i*LeftLoopSlope+LeftLoopTemp_C);
//                                                    if(str->LeftEdge[LeftLoopTemp_R-i]>=79)
//                                                    {
//                                                        str->LeftEdge[LeftLoopTemp_R-i]=79;
//                                                    }
//                                                    if(str->LeftEdge[LeftLoopTemp_R-i]<=1)
//                                                    {
//                                                        str->LeftEdge[LeftLoopTemp_R-i]=1;
//                                                    }
//                                                 // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;
//
//                                                    if(str->LeftEdge[LeftLoopTemp_R-i]>78||LeftLoopTemp_R-i>ROW_END)
//                                                       break;
//                                                }


                         break;
               }
    /*=========*/case Into_Round2://==========================================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
                   // angke_yaw_round=angke_yaw;
                    if( angke_yaw<-32)
                    {
                        RoundProcess=In_Round;
                    }

                    //进环阶段阶段补线-----------------------------------------------------
                   uint8 flag;flag=0;
                    for(uint8 h=ROW_END;h>ROW_START;h--)
                    { if(flag==1)break;
                            for(uint8 i=h;i>ROW_START;i--)
                            {if(flag==1)break;
                                for(uint8 j=COL_END;j>40;j--)

                                {
                                    if(image1[i][j]>=Threshold&&image1[i][j-1]<Threshold)
                                    {
                                        LeftLoopTemp_R=i;//hang
                                        LeftLoopTemp_C=j;//lie
                                        str->EndLine=i;
                                        flag=1;
                                        break;
                                    }

                                }

                            }

                        //}
                    }
                    /*进环斜率*/
                    //LeftLoopSlope=-1.8;//*(str->RightEdge[aa1]-aa2)/(aa1-LeftLoopTemp_R);
                    //if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(LeftLoopTemp_R-ROW_END);
                    if (RoundSize==Small_Round) LeftLoopSlope=-1.0;
                    if (RoundSize==Large_Round) LeftLoopSlope=-0.3;
                    for(uint8 i=0;i<=ROW_END-LeftLoopTemp_R;i++)
                    {
                       str->LeftEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
                       if(str->LeftEdge[LeftLoopTemp_R+i]>=79)
                       {
                           str->LeftEdge[LeftLoopTemp_R+i]=79;
                       }
                       if(str->LeftEdge[LeftLoopTemp_R+i]<=1)
                       {
                           str->LeftEdge[LeftLoopTemp_R+i]=1;
                       }
                    // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

                       if(str->LeftEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
                          break;
                    }

                          break;
                }
#endif
    /*=========*/case In_Round://==========================================================
                {
                    gpio_set_level(BUZZER_PIN, 0);
                    //*进入下个阶段的判定----------------------------------------*/
                    if(angke_yaw<-230 && Inflection_point.L_down_point.x)
                    {
                        RoundProcess=Out_Round;
                    }
                    //环内阶段阶段补线-----------------------------------------------------

                        //#无补线操作#//
                    break;
                }
    /*=========*/case Out_Round://==========================================================
                 {
                     //*进入下个阶段的判定----------------------------------------*/
                     if(angke_yaw<-320)
                     {
                         RoundProcess=Leave_Round;
                     }
                     //准备出环阶段阶段补线-----------------------------------------------------
                             LeftLoopTemp_R=ROW_END-1;//行值即在靠近最后一行
                             LeftLoopTemp_C=1;//列值即在靠近第一列
                             if (RoundSize==Small_Round) LeftLoopSlope=2.0;
                             if (RoundSize==Large_Round) LeftLoopSlope=0.8;


//                         if(Inflection_point.L_down_point.x&& Inflection_point.L_down_point.x>24 )//拐点大于25的时候
//                         {
//                            LeftLoopTemp_R=Inflection_point.L_down_point.x;
//                            LeftLoopTemp_C=Inflection_point.L_down_point.y;
//                            LeftLoopSlope=2.2;
//                         }
                                                  for(uint8 i=0;i<=LeftLoopTemp_R;i++)
                                                  {
                                                     str->LeftEdge[LeftLoopTemp_R-i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
                                                     if(str->LeftEdge[LeftLoopTemp_R-i]>=COL_END)
                                                     {
                                                         str->LeftEdge[LeftLoopTemp_R-i]=COL_END;
                                                     }
                                                     if(str->LeftEdge[LeftLoopTemp_R-i]<=COL_START)
                                                     {
                                                         str->LeftEdge[LeftLoopTemp_R-i]=COL_START;
                                                     }
                                                  // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

                                                     if(str->LeftEdge[LeftLoopTemp_R-i]>COL_END-1||LeftLoopTemp_R-i>ROW_END)
                                                        break;
                                                  }
                     break;
                 }
    /*=========*/case Leave_Round://==========================================================
                  {
                      //*进入下个阶段的判定----------------------------------------*/
                     if(str->R_StartLine>40&&angke_yaw<=-350)//修改参数
                     {
                           RoundProcess=Leave_Round2;
                           angke_yaw=0;
                     }


                      //出环阶段阶段补线-----------------------------------------------------
                      for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                      {
                         if(str->LeftEdge[Round_row])
                         {
                             char temp_r;
                             char temp_l;
                             char track;
                             temp_r=str->LeftEdge[Round_row];
                             track=Round.Track_Width_forRound[Round_row];
                             temp_l=temp_r+track+1;
                             if(temp_l>=79)
                             {
                                 temp_l=78;

                             }
                             if(temp_l<=1)
                             {
                                 temp_l=1;

                             }
                             str->RightEdge[Round_row]=temp_l;
                           // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                         }
                         else
                         {
                            str->RightEdge[Round_row]=0;
                         }
                      }

                      break;
                  }
    /*=========*/case Leave_Round2://==========================================================
                {
                    Round.Round_flag=0;
                    RoundProcess=0;
                    RoadType= else_road;
                    Distance_Leave_Round2=0;
                    break;
                }
            }
            break;
        }

    }
}
#endif
void Round_Deal()
{         have_element_flag=0;
          if(Round.Round_flag==0)
          {

             for(Round_row=ROW_END-5;Round_row>=ROW_START+5;Round_row--)
             {
                 Round.Track_Width_forRound[Round_row]=(int)(0.8*Round_row+22.6);//(1.7*Round_row+5.8); //计算  圆环路宽
             }
             Round_Detection(&Boundary,&Round);        //十字检测
          }
          else
          {
              Round_Process(&Boundary,&Round);
              have_element_flag=1;
          }

}
