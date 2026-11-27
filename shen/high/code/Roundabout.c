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
float Distance_In_Round;
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
             if(round->Entrance_count>=25)//min修改，其中有13行满足条件即可判定为圆环 && distance>=1000
             {
                round->Round_flag=1;
                RoundType=Left_Round;
                RoundProcess=Find_Round;

                RoadType= Round_Road;
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
                                gpio_set_level(BUZZER_PIN, 1);
                                if(Distance_In_Round==0)
                                {
                                    Distance_In_Round=distance;//防止反复赋值
                                }
//                                if(distance-Distance_In_Round>=70)
//                                {
                                if(str->L_StartLine<30 && str->L_StartLine>20)   //修改参数
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
                                    Distance_In_Round=0;
                                 }
                               }
//                                }
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
                                //*进入下个阶段的判定----------------------------------------*/
                              //  if(str->L_StartLine==ROW_END)//前几行不丢线了
                              //  {
                              //      Round_num=0;
                              //      Round_num_1=0;
                              //      for(Round_row=ROW_END-3;Round_row>=ROW_START;Round_row--)//从最下往上找十行
                              //      {
                              //          if(str->LeftEdge[Round_row]==0)
                              //          {
                              //              if(Round_row>=15)//调参，从第几行开始计数
                              //              {
                              //                  for(Round_col=Round_row;Round_col>=ROW_START;Round_col--)
                              //                  {

                              //                      if(str->LeftEdge[Round_row]==0)
                              //                      {
                              //                          Round_num++;
                              //                      }
                              //                      else
                              //                      {
                              //                          break;
                              //                      }
                              //                  }
                              //                  if(Round_num>=8 )//调参，行数
                              //                  {
                              //                      Round_num=0;
                              //                      // Round_num_1=0;
                              //                      RoundProcess=Into_Round;

                              //                      angke_yaw=0;//进环前yaw角初始化为0
                              //                      angke_yaw_round=0;
                              //                      break;
                              //                  }
                              //              }
                              //          }

                              //      }
                              //  }


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
                                gpio_set_level(BUZZER_PIN, 0);
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
                                                             //LeftLoopSlope=1.8;
                                if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(ROW_END-8-LeftLoopTemp_R);//>0
                                else LeftLoopSlope=2.2;
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

//                                                             LeftLoopSlope=-1.2;//LeftLoopTemp_C/(float)(ROW_END-LeftLoopTemp_R);//>0
//                                                                                          for(uint8 i=ROW_END;i>=0;i--)
//                                                                                          {
//                                                                                             str->RightEdge[i]=(int)((ROW_END-i)*LeftLoopSlope+COL_END);
//
//                                                                                             if(str->RightEdge[i]>=79)
//                                                                                             {
//                                                                                                 str->RightEdge[i]=79;
//                                                                                             }
//                                                                                             if(str->RightEdge[i]<=1)
//                                                                                             {
//                                                                                                 str->RightEdge[i]=1;
//                                                                                             }
//                                                                                          // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;
//
//                                                                                           //  if(str->RightEdge[i]>78||LeftLoopTemp_R+i>ROW_END)
//                                                                                          //      break;
//                                                                                          }

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
                                LeftLoopSlope=2.4;
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

//                                                             LeftLoopSlope=-1.2;//LeftLoopTemp_C/(float)(ROW_END-LeftLoopTemp_R);//>0
//                                                                                          for(uint8 i=ROW_END;i>=0;i--)
//                                                                                          {
//                                                                                             str->RightEdge[i]=(int)((ROW_END-i)*LeftLoopSlope+COL_END);
//
//                                                                                             if(str->RightEdge[i]>=79)
//                                                                                             {
//                                                                                                 str->RightEdge[i]=79;
//                                                                                             }
//                                                                                             if(str->RightEdge[i]<=1)
//                                                                                             {
//                                                                                                 str->RightEdge[i]=1;
//                                                                                             }
//                                                                                          // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;
//
//                                                                                           //  if(str->RightEdge[i]>78||LeftLoopTemp_R+i>ROW_END)
//                                                                                          //      break;
//                                                                                          }

                                      break;
                            }
                /*=========*/case In_Round://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
                                if(angke_yaw>225 )//&& Inflection_point.R_down_point.x)
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
                                 if(angke_yaw>300)
                                 {
                                     RoundProcess=Leave_Round;
                                 }
                                 //准备出环阶段阶段补线-----------------------------------------------------
                                                                 for(int8 i=0;i<=ROW_END;i++)
                                                              {
                                                                 str->RightEdge[ROW_END-i]=(int)(COL_END+i*(-2.3));
                                                                 str->LeftEdge[ROW_END-i]=1;
                                                                 if(str->RightEdge[ROW_END-i]>=COL_END)
                                                                 {
                                                                     str->RightEdge[ROW_END-i]=COL_END;
                                                                 }
                                                                 if(str->RightEdge[ROW_END-i]<=1)
                                                                 {
                                                                     str->RightEdge[ROW_END-i]=1;
                                                                 }
                                                                                                                             }
//                                 LeftLoopTemp_R=ROW_END;
//                                 LeftLoopTemp_C=COL_END;
//                                 LeftLoopSlope=-1.8;
//                                 //str->EndLine=15;//



////                                     if(Inflection_point.R_down_point.x && Inflection_point.R_down_point.x>25)
////                                     {
////                                        LeftLoopTemp_R=Inflection_point.R_down_point.x+5;
////                                        LeftLoopTemp_C=Inflection_point.R_down_point.y;
////                                        LeftLoopSlope=-2.2;
////                                     }
////                                                                         else
////                                                                         {
////                                                                               LeftLoopTemp_R=ROW_END-5;
////                                        LeftLoopTemp_C=COL_END;
////                                        LeftLoopSlope=-2.2;
////                                                            //           }



//                                    // else
//                                    // {
//                                    //     LeftLoopTemp_R=39;
//                                  //       LeftLoopTemp_C=79;
//                                   //      LeftLoopSlope=-2.3;
//                                   //  }
//                                                              for(uint8 i=0;i<=LeftLoopTemp_R;i++)
//                                                              {
//                                                                 str->RightEdge[LeftLoopTemp_R-i]=(int)(LeftLoopTemp_C+i*LeftLoopSlope);
//                                                                 str->LeftEdge[LeftLoopTemp_R-i]=1;
//                                                                 if(str->RightEdge[LeftLoopTemp_R-i]>=COL_END)
//                                                                 {
//                                                                     str->RightEdge[LeftLoopTemp_R-i]=COL_END;
//                                                                 }
//                                                                 if(str->RightEdge[LeftLoopTemp_R-i]<=1)
//                                                                 {
//                                                                     str->RightEdge[LeftLoopTemp_R-i]=1;
//                                                                 }
//                                                              // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

//                                                                 if(str->RightEdge[LeftLoopTemp_R-i]>COL_END-1||LeftLoopTemp_R-i>ROW_END-1)
//                                                                    break;
//                                                              }
                                 break;
                             }
                /*=========*/case Leave_Round://==========================================================
                              {
                                  //*进入下个阶段的判定----------------------------------------*/
                                 if(str->L_StartLine>40)//修改参数
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
                /*=========*/case Leave_Round2://==========================================================
                            {
                                Round.Round_flag=0;
                                RoadType= else_road;

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
                    //wireless_ch573_send_buff(AC_round_data, sizeof(AC_round_data));

                    //*进入下个阶段的判定---------------------------------------------*/
                    if(Distance_In_Round==0)
                    {
                        Distance_In_Round=distance;//防止反复赋值
                    }
//                    if(distance-Distance_In_Round>=70)
//                    {

                    if(str->R_StartLine<30 && str->R_StartLine>20 )   //修改参数
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
                        Distance_In_Round=0;
                     }
                   }
//                    }
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
//
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
                                                //LeftLoopSlope=-1.8;//*(str->RightEdge[aa1]-aa2)/(aa1-LeftLoopTemp_R);
                   if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(LeftLoopTemp_R-ROW_END+8);
                   else LeftLoopSlope=-2.2;
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
                    LeftLoopSlope=-2.4;
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
//    case Into_Round://进环    关键 分两步
//                    {
//               // lcd_showint8(110,6, 2);
//                       /*进环的补线处理*/
//                     if(!Inflection_point.R_down_point.x&&!Inflection_point.R_up_point.x&&str->RightEdge[ROW_END-5])//&&str->LeftEdge[ROW-4])
//                     // if(Inflection_point.L_up_point.x==0&&Inflection_point.L_down_point.x&&str->LeftEdge[ROW_END-3])
//    //                  if(Inflection_point.L_up_point.x&&(left_ad>=220||right_ad>200)&&!str->LeftEdge[ROW_END-1])
//                     {
//
//                          RoundProcess=Into_Round2;
//                        }
//
//                      else
//                       {      //获取补线点信息
//                          if(Inflection_point.R_down_point.x>5) //记录上一次拐点存在的信息
//                          {
//                             Inflection_Temp_x=Inflection_point.R_down_point.x;
//                             Inflection_Temp_y=Inflection_point.R_down_point.y;
//                          }
//                          //得到信息后，开始补线
//                          for(uint8 i=Inflection_Temp_x;i>2;i--)
//                          {
//                             if(image[i][Inflection_Temp_y]<=Threshold&&image[i-1][Inflection_Temp_y]>Threshold)
//                             {
//                                LeftLoopTemp_R=i-1;
//                                str->EndLine=i-1;
//                                break;
//                             }
//                          }
//                          for(uint8 i=Inflection_Temp_y;i<75;i++)
//                          {
//                             if((image[LeftLoopTemp_R-1][i+1]<=Threshold)&&(image[LeftLoopTemp_R-1][i]>Threshold))
//                             {
//                                LeftLoopTemp_C=i;
//
//                                break;
//                             }
//                          }
//
//                          /*进环斜率*/
//                          LeftLoopSlope=-1.3;//*(str->RightEdge[aa1]-aa2)/(aa1-LeftLoopTemp_R);
//
//                          for(uint8 i=0;i<=48;i++)
//                          {
//                             str->LeftEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
//
//                           str->LeftEdge[LeftLoopTemp_R+i]=int_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;
//
//                             if(str->LeftEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
//                                break;
//                          }
//                       }
//
//                       for(uint8 i=str->EndLine;i<ROW_END;i++)
//                       {
//                          for(uint8 j=1;j<=79;j++)
//                          {
//                             if(image[i][j]>=Threshold&&image[i][j+1]<Threshold)
//                             {
//                                if(str->LeftEdge[i]>j+1)
//                                       str->LeftEdge[i]=j+1;
//                                break;
//                             }
//                          }
//                       }
//                       break;
//                    }
//                  case Into_Round2://进环    关键 4
//                    {
//                //  lcd_showint8(110,6, 3);
//                       /*判断是否进入环岛*/
//                       if(angke_yaw>=40)//&&str->L_StartLine==0&& RoundSize==Small_Round)      //定距离一段
//                       {
//                          RoundProcess=In_Round;
//                          Inflection_Temp_x=0;
//                          Inflection_Temp_y=0;
//                          //lcd_showint8(80,5, 4);
//                       }
//
//    #if 1                                 //补线
//                       for(uint8 i=str->EndLine;i<=ROW_END;i++)
//                       {
//                          for(uint8 j=1;j<=75;j++)
//                          {
//                             if(image[i][j]<=Threshold&&image[i][j+1]>Threshold&&image[i][j+2]>Threshold&&image[i][j+3]>Threshold)
//                            //if (difference_sum(image[i][j],image[i][j-COL_SPACE])>=g_threshold_value)
//                             {
//                                if(str->LeftEdge[i]>j+1)
//                                       str->LeftEdge[i]=j+1;
//
//                                break;
//                             }
//                          }
//                       }
//
//
//                       /*进环斜率*/
//                       LeftLoopSlope=-2.0;
//                       for(uint8 i=ROW_END;i>ROW_START;i--)
//                       {
//                         //  lcd_showint8(80,5, 5);
//                          if(str->LeftEdge[i]!=0)
//                             str->LeftEdge[i]=str->LeftEdge[i]<(int)(LeftLoopSlope*i+5)?str->LeftEdge[i]:(int)(LeftLoopSlope*i+5);
//                          else
//                             str->LeftEdge[i]=(int)(LeftLoopSlope*i+5);
//                          if(str->LeftEdge[i]>79)
//                             str->LeftEdge[i]=0;
//                       }
//                       for(uint8 i=49;i>str->EndLine&&i>ROW_START+2;i--)
//                       {
//                           //lcd_showint8(80,5, 6);
//                          if(image[i][10]>=Threshold&&image[i-1][10]<Threshold&&image[i-2][10]<Threshold)
//                          //if (difference_sum(image[i-2][10],image[i][10])>=g_threshold_value)
//                          {
//                             for(uint8 j=i;j>str->EndLine&&j>ROW_START;j--)
//                             {
//                                str->RightEdge[j]=0;
//                             }
//                             str->EndLine=i-1;        //改变endline
//                             break;
//                          }
//                          if(str->RightEdge[i]>30)
//                          {
//                             str->RightEdge[i]=0;   //限幅
//                          }
//                       }
//    #endif
//                       break;
//                    }
    /*=========*/case In_Round://==========================================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
                    if(angke_yaw<-240 && Inflection_point.L_down_point.x)
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
                     if(angke_yaw<-340)
                     {
                         RoundProcess=Leave_Round;
                     }
                     //准备出环阶段阶段补线-----------------------------------------------------
                             LeftLoopTemp_R=ROW_END-1;
                             LeftLoopTemp_C=1;
                             LeftLoopSlope=2.1;


                         if(Inflection_point.L_down_point.x && Inflection_point.L_down_point.x>25 )
                         {
                            LeftLoopTemp_R=Inflection_point.L_down_point.x;
                            LeftLoopTemp_C=Inflection_point.L_down_point.y;
                            LeftLoopSlope=2.3;
                         }
                                                  for(uint8 i=0;i<=LeftLoopTemp_R;i++)
                                                  {
                                                     str->LeftEdge[LeftLoopTemp_R-i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
                                                     if(str->LeftEdge[LeftLoopTemp_R-i]>=79)
                                                     {
                                                         str->LeftEdge[LeftLoopTemp_R-i]=79;
                                                     }
                                                     if(str->LeftEdge[LeftLoopTemp_R-i]<=1)
                                                     {
                                                         str->LeftEdge[LeftLoopTemp_R-i]=1;
                                                     }
                                                  // str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,79) ;

                                                     if(str->LeftEdge[LeftLoopTemp_R-i]>78||LeftLoopTemp_R-i>ROW_END)
                                                        break;
                                                  }
                     break;
                 }
    /*=========*/case Leave_Round://==========================================================
                  {
                      //*进入下个阶段的判定----------------------------------------*/
                     if(str->R_StartLine>40)//修改参数
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
                    RoadType= else_road;
                    break;
                }
            }
            break;
        }

    }
}
#endif
#if 0
void Round_Process(Str_Boundary *str,Str_Round *round,Str_Inflection_point *point)
{
    float  LeftLoopSlope;
    float  RightLoopSlope;

    uint8  Round_num=0;
       switch(RoundType)
       {
        case Left_Round:  //左环
          {
             switch(RoundProcess)
             {
              case Find_Round://发现圆环
                {
                   // lcd_showint8(80,3, 1);

                   //*进入下个阶段的判定*/
                   if(str->L_StartLine<25)   //da待改进
                   {
                      Round_num=0;
                      for(Round_row=str->L_StartLine;Round_row>=str->L_StartLine-4&&Round_row>=ROW_START+1;Round_row--)   //防止误判     检测环中心岛
                      {
                         if(str->LeftEdge[Round_row]!=0)
                         {
                            Round_num+=str->LeftEdge[Round_row]-str->LeftEdge[Round_row+1] ;
                         }
                         else
                         {
                            Round_num=0;
                         }
                      }
                      if(Round_num>10)
                      {
                         Round_num=0;
                         RoundProcess=Find_Gap;//就认为有缺口
                         //lcd_showint8(80,1, 1);
                      }
                   }
                   //*入环的补线*/
                   for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                   {
                      if(str->RightEdge[Round_row])
                      {
                          char temp_r;
                          char temp_l;
                          char track;
                          temp_r=str->RightEdge[Round_row];
                          track=Boundary.track_Width[Round_row];
                          temp_l=temp_r-track;
                          if(temp_l>=89)
                          {
                              temp_l=88;

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
              case Find_Gap://发现圆环中心
                {
                  //  lcd_showint8(110,4, 0);
                   /*下一阶段的判定*/
                   //底部三行左边界都不丢线
                 // if(str->LeftEdge[ROW_END-2]&&str->LeftEdge[ROW_END-1]&&str->LeftEdge[ROW_END-3])//&&str->LeftEdge[ROW_END-2]
                   if(Inflection_point.L_up_point.x&&Inflection_point.L_down_point.x&&(Inflection_point.L_down_point.x-Inflection_point.L_up_point.x)<15)
                    {
//                        if(str->LeftEdge[point->L_up_point.x-1]!=0&&str->LeftEdge[point->L_up_point.x-2]!=0&&str->LeftEdge[point->L_up_point.x-1]<=34&&str->LeftEdge[point->L_up_point.x-2]<=34)
//                       {
//                         if(str->LeftEdge[point->L_up_point.x-1]<str->LeftEdge[point->L_up_point.x-2])
//                        {

                             RoundProcess=Into_Round;
//                        }
//
//                       }

                    }
                   /*左补线*/
                   for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                   {
                      if(str->RightEdge[Round_row])
                      {
 //                       str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                          char temp_r;
                          char temp_l;
                          char track;
                          temp_r=str->RightEdge[Round_row];
                          track=Boundary.track_Width[Round_row];
                          temp_l=temp_r-track;
                          if(temp_l>=89)
                          {
                              temp_l=88;

                          }
                          if(temp_l<=1)
                          {
                              temp_l=1;

                          }
                          str->LeftEdge[Round_row]=temp_l;
                      }
                      else
                      {
                         str->LeftEdge[Round_row]=0;
                      }
                   }
                   break;
                }
              case Into_Round://进环    关键 分两步
                {
                 // lcd_showint8(110,4, 1);
                   /*进环的补线处理*/
                  //if(str->LeftEdge[ROW_END-3]==0&&str->LeftEdge[ROW_END-2]==0)//&&str->LeftEdge[ROW-4])
                if( Inflection_point.L_up_point.x&&Inflection_point.L_down_point.x==0&&str->LeftEdge[ROW_END-3]==0)
                {

                       RoundProcess=Into_Round2;
                }

                  else
                   {      //获取补线点信息
                      if(point->L_down_point.x>5) //记录上一次拐点存在的信息
                      {
                         Inflection_Temp_x=point->L_down_point.x;
                         Inflection_Temp_y=point->L_down_point.y;
                      }
                      //得到信息后，开始补线
                      for(uint8 i=Inflection_Temp_x;i>2;i--)
                      {
                         if(image[i][Inflection_Temp_y]>=Threshold&&image[i-1][Inflection_Temp_y]<Threshold)
                         {
                            LeftLoopTemp_R=i-1;
                            str->EndLine=i-1;
                            break;
                         }
                      }
                      for(uint8 i=Inflection_Temp_y;i<75;i++)
                      {
                         if((image[LeftLoopTemp_R-1][i+1]>=Threshold)&&(image[LeftLoopTemp_R-1][i]<Threshold))
                         {
                            LeftLoopTemp_C=i;

                            break;
                         }
                      }

                      /*进环斜率*/
                      LeftLoopSlope=1.8;//*(str->RightEdge[aa1]-aa2)/(aa1-LeftLoopTemp_R);

                      for(uint8 i=0;i<=28;i++)
                      {
                         str->RightEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);

                       str->RightEdge[LeftLoopTemp_R+i]=int8_range_protect(str->RightEdge[LeftLoopTemp_R+i],1,79) ;

                         if(str->RightEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
                            break;
                      }
                   }

                   for(uint8 i=str->EndLine;i<ROW_END;i++)
                   {
                      for(uint8 j=1;j<=89;j++)
                      {
                         if(image[i][j]>=Threshold&&image[i][j+1]<Threshold)
                         {
                            if(str->RightEdge[i]>j+1)
                                   str->RightEdge[i]=j+1;
                            break;
                         }
                      }
                   }
                   break;
                }
              case Into_Round2://进环    关键 4
                {
                lcd_showint8(110,4, 2);
                   /*判断是否进入环岛*/
                   if(angke_yaw>=40)//&&str->L_StartLine==0&& RoundSize==Small_Round)      //定距离一段
                   {
                      RoundProcess=In_Round;
                      Inflection_Temp_x=0;
                      Inflection_Temp_y=0;
                      //lcd_showint8(80,5, 4);
                   }

#if 1                                 //补线
                   for(uint8 i=str->EndLine;i<=ROW_END;i++)
                   {
                      for(uint8 j=1;j<=89;j++)
                      {
                         if(image[i][j]>=Threshold&&image[i][j+1]<Threshold&&image[i][j+2]<Threshold&&image[i][j+3]<Threshold)
                        //if (difference_sum(image[i][j],image[i][j-COL_SPACE])>=g_threshold_value)
                         {
                            if(str->RightEdge[i]>j+1)
                                   str->RightEdge[i]=j+1;

                            break;
                         }
                      }
                   }


                   /*进环斜率*/
                   LeftLoopSlope=1.9;
                   for(uint8 i=ROW_END;i>ROW_START;i--)
                   {
                     //  lcd_showint8(80,5, 5);
                      if(str->RightEdge[i]!=0)
                         str->RightEdge[i]=str->RightEdge[i]<(int)(LeftLoopSlope*i+5)?str->RightEdge[i]:(int)(LeftLoopSlope*i+5);
                      else
                         str->RightEdge[i]=(int)(LeftLoopSlope*i+5);
                      if(str->RightEdge[i]>89)
                         str->RightEdge[i]=0;
                   }
                   for(uint8 i=29;i>str->EndLine&&i>ROW_START+2;i--)
                   {
                       //lcd_showint8(80,5, 6);
                      if(image[i][10]>=Threshold&&image[i-1][10]<Threshold&&image[i-2][10]<Threshold)
                      //if (difference_sum(image[i-2][10],image[i][10])>=g_threshold_value)
                      {
                         for(uint8 j=i;j>str->EndLine&&j>ROW_START;j--)
                         {
                            str->LeftEdge[j]=0;
                         }
                         str->EndLine=i-1;        //改变endline
                         break;
                      }
                      if(str->LeftEdge[i]>30)
                      {
                         str->LeftEdge[i]=0;   //限幅
                      }
                   }
#endif
                   break;
                }
              case In_Round://在环内    5
                {
                lcd_showint8(110,4, 3);
                angke_yaw = 0;
                   //记录上一次拐点存在的信息
                   if(point->R_down_point.x&&image[point->R_down_point.x][point->R_down_point.y-2]>=Threshold&&image[point->R_down_point.x][point->R_down_point.y-3]>=Threshold&&image[point->R_down_point.x-1][point->R_down_point.y]>=Threshold&&image[point->R_down_point.x-2][point->R_down_point.y]>=Threshold)
                   {
                      Inflection_Temp_x=point->R_down_point.x;
                      Inflection_Temp_y =point->R_down_point.y;
                      //判断下一阶段
                      if(point->R_down_point.x>5)
                      {
                         uint8 hang_num=0;            //清除白块计数值 8
                         for(Round_row=point->R_down_point.x-1; Round_row>=point->R_down_point.x-6&&Round_row>ROW_START ; Round_row-- )     //在搜索到的黑白跳变点后，向上搜索白点，判断是否为干扰点
                         {
                            if(str->RowLose[Round_row]==4)
                            {
                                   hang_num++;
                            }
                         }
                         if( hang_num>2|| point->R_down_point.x>15||Inflection_point.R_down_point.y>30)
                         {
                            RoundProcess=Out_Round;
                           // lcd_showint8(110,4, 4);
                         }
                      }
                   }

                   if(Inflection_Temp_x>0)
                   {
                      //补线
                      LeftLoopSlope=2.0;
                      for(uint8 i=Inflection_Temp_x+1;i>ROW_START;i--)
                      {

                         str->RightEdge[i]=(int)((i-Inflection_Temp_x)*LeftLoopSlope+Inflection_Temp_y);    //fuhao
                         if (str->RightEdge[i]<COL_START)
                         {
                            str->EndLine =i;
                            break;
                         }
                      }
                      //str->StartLine=ROW_END;
                      //memset(str->LeftEdge, 0,sizeof(str->LeftEdge) );   //z左线清空
                   }
                   for(uint8 i=29;i>str->EndLine;i--)    //消除左线误搜索
                   {
                      if(str->LeftEdge[i]>30)
                      {
                         str->LeftEdge[i]=0;
                      }
                   }
                   break;
                }

              case Out_Round://出环   6
                {
                   lcd_showint8(110,4, 4);
                   LeftLoopSlope=2.1;
                   for(uint8 i=29;i>5;i--)//取小值
                   {
                      if(str->RightEdge[i]!=0)
                         str->RightEdge[i]=str->RightEdge[i]<(unsigned char)(LeftLoopSlope*i+7)?str->RightEdge[i]:(unsigned char)(LeftLoopSlope*i+7);
                      else
                         str->RightEdge[i]=(unsigned char)(LeftLoopSlope*i+7);
                      if(str->RightEdge[i]>89)
                         str->RightEdge[i]=0;
                   }
//                 str->StartLine=ROW_END;
//                 memset(str->LeftEdge, 0,sizeof(str->LeftEdge) );
//
                   if(angke_yaw>120)   //下一阶段标志
                   {
                      RoundProcess=Leave_Round;
                   }
                   for(uint8 i=29;i>str->EndLine;i--)    //消除左线误搜索
                   {
                      if(str->LeftEdge[i]>35)
                      {
                         str->LeftEdge[i]=0;
                      }
                      if(i<29&&i>ROW_START)
                      {
                         if(str->LeftEdge[i]!=0&&str->LeftEdge[i-1]==0&&str->LeftEdge[i+1]==0)
                            str->LeftEdge[i]=0;
                      }
                   }
                   /*下一阶段的判定*/

                   break;
                }
              case Leave_Round://离开圆环
                {
                    lcd_showint8(110,4, 5);
                   Round_num=0;
                   for(Round_row=str->R_StartLine;Round_row>str->EndLine+1&&Round_row>ROW_START+10;Round_row--)
                   {
                      if(str->RightEdge[Round_row]==0)
                      {
                        Round_num++;
                      }
                   }
                   if(Round_num<3&&((str->R_StartLine-str->EndLine)>22||str->RightEdge[str->EndLine]>18))  //30需要调  huo 判断斜率
                   {
                      RoundProcess=Leave_Round2;//暂定
                   }
                   else
                   {
                      LeftLoopSlope=2.5;
                      for(uint8 i=29;i>5;i--)
                      {
                         if(str->RightEdge[i]!=0)
                            str->RightEdge[i]=str->RightEdge[i]<(unsigned char)(LeftLoopSlope*i+5)?str->RightEdge[i]:(unsigned char)(LeftLoopSlope*i+5);
                         else
                            str->RightEdge[i]=(unsigned char)(LeftLoopSlope*i+5);
                         if(str->RightEdge[i]>89)
                            str->RightEdge[i]=0;
                      }

                      for(uint8 i=29;i>str->EndLine;i--)    //消除左线误搜索
                      {
                         if(str->LeftEdge[i]>40)
                         {
                            str->LeftEdge[i]=0;
                         }
                         if(i<29&&i>ROW_START)
                         {
                            if(str->LeftEdge[i]!=0&&str->LeftEdge[i-1]==0&&str->LeftEdge[i+1]==0)
                                   str->LeftEdge[i]=0;
                         }
                      }
                   }
                   break;
                }
              case Leave_Round2://离开圆环 7
                {
                   //可以拉长视野
                  lcd_showint8(110,4, 6);
                   for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                   {
                      if(str->RightEdge[Round_row])
                      {
                       //  str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                          //if(str->RightEdge[Round_row])
                         char temp_r;
                         char temp_l;
                         char track;
                         temp_r=str->RightEdge[Round_row];
                         track=str->track_Width[Round_row]+2.8;
                         temp_l=temp_r-track;
                         if(temp_l>=89)
                         {
                             temp_l=88;

                         }
                         if(temp_l<=1)
                         {
                             temp_l=1;

                         }
                         str->LeftEdge[Round_row]=temp_l;
                      }
                      else
                      {
                         str->LeftEdge[Round_row]=0;
                      }
                   }

                   if (Lost_num<=2)
                   {

                if(str->L_StartLine&&str->R_StartLine&&str->L_StartLine==29&&str->R_StartLine==29&&Inflection_point.L_down_point.x==0&&Inflection_point.L_up_point.x==0)
                   {
                      lcd_showint8(110,4, 7);
                      RoundProcess=Round_Not_Found;//暂定
                      round->Round_flag=0;
                      RoadType= else_road;
                   }

                   }
                   break;
                }
              default:
                {
                   break;
                }
             }
             break;
          }

          //右环
        case Right_Round:
            {
               switch(RoundProcess)
               {
                case Find_Round://发现圆环
                  {
                     /*进入下个阶段的判定*/
                     //如果左右起始行之差大于5，缺口计数为0，左边界底部四行丢线//保证右边界的斜率在一定范围，以防斜入圆环误判，参数待定
                     if(str->R_StartLine<25)   //da待改进
                     {
                        Round_num=0;
                        for(Round_row=str->R_StartLine;Round_row>=str->R_StartLine-4&&Round_row>=ROW_START+1;Round_row--)   //防止误判     检测换中心岛
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
                        if(Round_num>5)
                        {
                            Round_num=0;
                           RoundProcess=Find_Gap;//就认为有缺口
                        }
                     }


                     /*入环的补线*/
//                     for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
//                     {
//                        if(str->RightEdge[Round_row]==0)
//                        {
//
//                            char temp_r;
//                            char temp_l;
//                            char track;
//                            temp_l=str->LeftEdge[Round_row];
//                            track=Boundary.track_Width[Round_row];
//                            temp_r=temp_l+track;
//                            if(temp_r>=89)
//                            {
//                                temp_r=88;
//
//                            }
//                            if(temp_r<=1)
//                            {
//                                temp_r=1;
//
//                            }
//                            str->RightEdge[Round_row]=temp_r;
//
//                           //str->RightEdge[Round_row]=str->LeftEdge[Round_row]+round->Track_Width_forRound[Round_row];//左边界等于右边界减半宽
//                        }
//                        else
//                        {
//                           str->RightEdge[Round_row]=0;
//                        }
//                    }
                     break;
                  }
                case Find_Gap://发现圆环中心
                  {
                      lcd_showint8(110,1, 1);
                     /*下一阶段的判定*/
                     //底部三行左边界都不丢线
                  //   if(str->RightEdge[ROW_END]&&str->RightEdge[ROW_END-1]&&str->RightEdge[ROW_END-2])//&&str->LeftEdge[ROW-4])
                   if(Inflection_point.R_up_point.x&&Inflection_point.R_down_point.x&&(Inflection_point.R_down_point.x-Inflection_point.R_up_point.x)<15)
                     {
                        RoundProcess=Into_Round;
                     }
                     /*右补线*/
                     for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
                     {
                        if(str->LeftEdge[Round_row])
                        {

                            char temp_r;
                            char temp_l;
                            char track;
                            temp_l=str->LeftEdge[Round_row];
                            track=Boundary.track_Width[Round_row]*1.5;
                            temp_r=temp_l+track;
                            if(temp_r>=89)
                            {
                                temp_r=88;

                            }
                            if(temp_r<=1)
                            {
                                temp_r=1;

                            }
                            str->RightEdge[Round_row]=temp_r;
                          // str->RightEdge[Round_row]=str->LeftEdge[Round_row]+round->Track_Width_forRound[Round_row];//左边界等于右边界减半宽
                        }
                        else
                        {
                           str->RightEdge[Round_row]=0;
                        }
                     }
                     break;
                  }
                case Into_Round://进环  3
                  {
                      lcd_showint8(110,1, 2);
                     /*进环的补线处理*/
                     //获取补线点信息
                   //  if(str->RightEdge[39]&&str->RightEdge[38])//&&str->LeftEdge[ROW-4])
                      if(Inflection_point.R_up_point.x&&Inflection_point.R_down_point.x==0&&str->RightEdge[ROW_END-3]==0)
                     {
                        if(Inflection_point.R_down_point.x>5) //记录上一次拐点存在的信息
                        {
                           Inflection_Temp_x=Inflection_point.R_down_point.x;
                           Inflection_Temp_y=Inflection_point.R_down_point.y;
                        }
                        //得到信息后，开始补线
                        for(uint8 i=Inflection_Temp_x;i>2;i--)//拐点向上搜索白黑跳变，记录
                        {
                           if(image[i][Inflection_Temp_y]>=Threshold&&image[i-1][Inflection_Temp_y]<Threshold&&image[i-2][Inflection_Temp_y]<Threshold)
                           {
                              LeftLoopTemp_R=i-1;
                              str->EndLine=i-1;
                              break;
                           }
                        }
                        for(uint8 i=Inflection_Temp_y;i>10;i--)//拐点向左搜索黑白跳变
                        {
                           if(image[LeftLoopTemp_R-1][i-2]>=Threshold&&image[LeftLoopTemp_R-1][i-1]>=Threshold&&image[LeftLoopTemp_R-1][i]<Threshold)
                           {
                              LeftLoopTemp_C=i;
                              break;
                           }
                        }
                        /*进环斜率*/
                        LeftLoopSlope=-2.0;

                        for(uint8 i=0;i<=89;i++)
                        {
                           str->LeftEdge[LeftLoopTemp_R+i]=(int)(LeftLoopTemp_C+i*LeftLoopSlope);
                          str->LeftEdge[LeftLoopTemp_R+i]=int8_range_protect(str->LeftEdge[LeftLoopTemp_R+i],1,89) ;
                           if(str->LeftEdge[LeftLoopTemp_R+i]<2||LeftLoopTemp_R+i>ROW_END)
                              break;
                        }
//                        uint8 round_temp_col = 0;
//                        uint8 round_temp_row = 0;
//                        for(uint8 row=59;row>ROW_START;row--)//岔路点识别
//                        {
//                          for(uint8 col=5;col<COL_END-5;col++)//取跳变点行数最靠前的点
//                            {
//                                if( image[row][col]>=Threshold&&image[row-1][col]<Threshold&&image[row-2][col]<Threshold)
//                                {
//                                   if(row>round_temp_row)
//                                    {
//                                      round_temp_row=row;
//                                      round_temp_col=col;
//
//
//                                       break;
//                                    }
//
//                                }
//                            }
//                       }
//                       if(round_temp_row)
//                       {
//                         for (uint8 i = 59; i >round_temp_row-5; i--)
//                       {
//                         Boundary.RightEdge[i] = 89;
//                           Boundary.LeftEdge[i]=Boundary.RightEdge[i]-Boundary.track_Width[i];
////                           char temp_t=Boundary.track_Width[i];//临时有符号变量防止中线溢出
////                           char temp_l;
////                           temp_l=temp_col-temp_t/2;
////                          if(temp_l>=80)
////                          {
////                              temp_l=79;
////                          }
////                          if (temp_l<=0)
////                          {
////                              temp_l=1;
////                          }
////                          Boundary.LeftEdge[i]=0;
////                          Boundary.RightEdge[i]=temp_col+Boundary.track_Width[i]/4;
//                      }
//                     }
                     }
                     else
                     {
                        RoundProcess=Into_Round2;
                     }

                     for(uint8 i=str->EndLine;i<=39;i++)
                     {
                        for(uint8 j=COL_END;j>=COL_START+4;j--)
                        {
                           if(image[i][j]<Threshold&&image[i][j+1]>=Threshold&&image[i][j-1]<Threshold)
                           {
                              if(str->LeftEdge[i]<j)
                              {
                                     str->LeftEdge[i]=j;
                              }
                              break;
                           }
                        }
                     }
                     break;
                  }
                case Into_Round2://进环 4
                  {
                      lcd_showint8(110,1, 3);
                     /*判断是否进入环岛*/
                     if(angke_yaw<=-40)//&&str->L_StartLine==0&& RoundSize==Small_Round)      //定距离一段
                     {

                        RoundProcess=In_Round;
                        Inflection_Temp_x=0;
                        Inflection_Temp_y=0;
                     }
                     /*进环的补线处理*/
                     for(uint8 i=str->EndLine;i<=29;i++)
                     {
                        for(uint8 j=COL_END;j>=COL_START+4;j--)
                        {
                           if(image[i][j]<Threshold&&image[i][j+1]>=Threshold&&image[i][j-1]<Threshold)
                           {
                              if(str->LeftEdge[i]<j)
                              {
                                     str->LeftEdge[i]=j;
                              }
                              break;
                           }
                        }
                     }
                     //补线
                     /*进环斜率*/
                     LeftLoopSlope=-2.0;
                     for(uint8 i=29;i>5;i--)
                     {
                        if(str->LeftEdge[i]!=0)
                           str->LeftEdge[i]=str->LeftEdge[i]>(int)(LeftLoopSlope*i+75)?str->LeftEdge[i]:(int)(LeftLoopSlope*i+75);
                        else
                           str->LeftEdge[i]=(int)(LeftLoopSlope*i+75);
                        if(str->LeftEdge[i]<COL_START)
                           str->LeftEdge[i]=0;
                     }
                     for(uint8 i=29;i>str->EndLine&&i>ROW_START+3;i--)
                     {
                        if(image[i][70]>=Threshold&&image[i-1][70]<Threshold&&image[i-2][70]<Threshold)
                        {
                           for(uint8 j=i;j>str->EndLine;j--)
                           {
                              str->RightEdge[j]=0;
                           }
                           str->EndLine=i-1;
                           break;
                        }
                        if(str->RightEdge[i]<89)
                        {
                           str->RightEdge[i]=0;   //限幅
                        }
                     }
                   break;
                  }
                case In_Round://在环内  5
                  {

                      lcd_showint8(110,1, 4);
                     if(Inflection_point.L_down_point.x&&image[Inflection_point.L_down_point.x][Inflection_point.L_down_point.y+2]>=Threshold&&image[Inflection_point.L_down_point.x][Inflection_point.L_down_point.y+3]>=Threshold&&image[Inflection_point.L_down_point.x-1][Inflection_point.L_down_point.y]>=Threshold)
                     {
                        Inflection_Temp_x=Inflection_point.L_down_point.x;
                        Inflection_Temp_y=Inflection_point.L_down_point.y;
                        if(Inflection_point.L_down_point.x>5)
                        {
                           uint8 hang_num=0;            //清除白块计数值                 8
                           for(Round_row=Inflection_point.L_down_point.x-1; Round_row>=Inflection_point.L_down_point.x-6&&Round_row>ROW_START ; Round_row-- )     //在搜索到的黑白跳变点后，向上搜索白点，判断是否为干扰点
                           {
                              if(str->RowLose[Round_row]==4)
                              {
                                     hang_num++;
                              }
                           }
                           if(angle_z<-230)//hang_num>2|| Inflection_point.L_down_point.x>15||(Inflection_point.L_down_point.y<30&&Inflection_point.L_down_point.y!=0)
                           {
                              RoundProcess=Out_Round;
                           }
                        }
                     }


                     if(Inflection_Temp_x>0)
                     {
                        //补线
                        LeftLoopSlope=2.0;

                        for(int i=Inflection_Temp_x+1;i>ROW_START;i--)
                        {
                           str->LeftEdge[i]=str->LeftEdge[i+1]+2;
                           //str->LeftEdge[i]=(int)((Inflection_Temp_x-i)*LeftLoopSlope+Inflection_Temp_y);    //这个式子you  bug
                           if (str->LeftEdge[i]>COL_END)
                           {
                              str->EndLine =i;
                              break;
                           }
                        }
                        // str->StartLine=ROW_END;
                     }
                     for(uint8 i=29;i>str->EndLine;i--)    //消除右线误搜索
                     {
                        if(str->RightEdge[i]<50)
                        {
                           str->RightEdge[i]=0;
                        }
                     }

                     break;
                  }
                case Out_Round://出环
                  {
                      lcd_showint8(110,1, 5);
                      LeftLoopSlope=-2.0;
                     for(int i=29;i>5;i--)
                     {
                        if(str->LeftEdge[i])
                           str->LeftEdge[i]=str->LeftEdge[i]>(int)(LeftLoopSlope*i+75)?str->LeftEdge[i]:(int)(LeftLoopSlope*i+75);
                        else
                           str->LeftEdge[i]=(int)(LeftLoopSlope*i+75);
                        if(str->LeftEdge[i]<COL_START)
                           str->LeftEdge[i]=0;
                     }
                     //str->StartLine=ROW_END;


                     if(angle_z<-330)   //下一阶段标志
                      {
                        RoundProcess=Leave_Round;
                      }


                     for(uint8 i=29;i>str->EndLine;i--)    //消除右线误搜索
                     {
                        if(str->RightEdge[i]<50)
                        {
                           str->RightEdge[i]=0;
                        }
                         if(i<39&&i>ROW_START)
                        {
                           if(str->RightEdge[i]!=0&&str->RightEdge[i-1]==0&&str->RightEdge[i+1]==0)
                              str->RightEdge[i]=0;
                        }
                     }
                     break;
                  }
                case Leave_Round://离开圆环
                  {
                      lcd_showint8(110,1, 6);
                      Round_num=0;
                     for(Round_row=str->L_StartLine;Round_row>str->EndLine+1&&Round_row>ROW_START+10;Round_row--)
                     {
                        if(str->LeftEdge[Round_row]==0)
                        {
                          Round_num++;
                        }
                     }
                     if(Round_num<3&&((str->L_StartLine-str->EndLine)>22||str->LeftEdge[str->EndLine]<65))  //30需要调
                     {
                        RoundProcess=Leave_Round2;//暂定
                     }
                     else
                     {
                        LeftLoopSlope=-2.0;
                        for(int i=59;i>5;i--)
                        {
                           if(str->LeftEdge[i])
                              str->LeftEdge[i]=str->LeftEdge[i]>(int)(LeftLoopSlope*i+75)?str->LeftEdge[i]:(int)(LeftLoopSlope*i+75);
                           else
                              str->LeftEdge[i]=(int)(LeftLoopSlope*i+75);
                           if(str->LeftEdge[i]<COL_START)
                              str->LeftEdge[i]=0;
                        }
                        for(uint8 i=59;i>str->EndLine;i--)    //消除右线误搜索
                        {
                           if(str->RightEdge[i]<50)
                           {
                              str->RightEdge[i]=0;
                           }
                           if(i<59&&i>ROW_START)
                           {
                              if(str->RightEdge[i]!=0&&str->RightEdge[i-1]==0&&str->RightEdge[i+1]==0)
                                     str->RightEdge[i]=0;
                           }
                        }
                     }

                     if(str->R_StartLine>40)//修改参数
                                          {
                                                RoundProcess=Leave_Round2;
                                                angke_yaw=0;
                                          }
                     break;
                  }

                  case Leave_Round2://离开圆环
                  {
//
//                      for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
//                     {
//                        if(str->LeftEdge[Round_row])
//                        {
//                            char temp_r;
//                            char temp_l;
//                            char track;
//                            temp_l=str->LeftEdge[Round_row];
//                            track=str->track_Width[Round_row]+2.8;
//                            temp_r=temp_l+track;
//                            if(temp_r>=89)
//                            {
//                                temp_r=88;
//
//                            }
//                            if(temp_r<=1)
//                            {
//                                temp_r=1;
//
//                            }
//                            str->RightEdge[Round_row]=temp_r;
//                          // str->RightEdge[Round_row]=str->LeftEdge[Round_row]+round->Track_Width_forRound[Round_row];//左边界等于右边界减半宽
//                        }
//                        else
//                        {
//                           str->RightEdge[Round_row]=0;
//                        }
//                     }
                     /*离开圆环的补线处理*/
//                 if(Rost_num<=2)
//                  {
//                   if(str->L_StartLine&&str->R_StartLine&&str->L_StartLine==29&&str->R_StartLine==29&&Inflection_point.R_down_point.x==0&&Inflection_point.R_up_point.x==0)
 //                     {
//                       lcd_showint8(110,1, 7);
                        RoundProcess=Round_Not_Found;//暂定
                        round->Round_flag=0;
                        //RoadType= else_road;
//                     }

 //                }
                 break;
                  }
                default:
                  {
                     break;
                  }
               }
               break;
            }
          default:
            {
               break;
            }
//
       }


 }

int8 int8_range_protect( int8  duty, int8  min, int8 max ) //限幅保护
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
#endif
void Round_Deal()
{
          if(Round.Round_flag==0)
          {
             for(Round_row=ROW_END-5;Round_row>=ROW_START+5;Round_row--)
             {
                 Round.Track_Width_forRound[Round_row]=(int)(0.8*Round_row+22.6);//(1.7*Round_row+5.8); //计算  圆环路宽
             }
             Round_Detection(&Boundary,&Round);        //圆环检测
          }
          else
          {
              Round_Process(&Boundary,&Round);
          }

}
