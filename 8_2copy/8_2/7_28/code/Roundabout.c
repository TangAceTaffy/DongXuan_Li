//圆环过程
//1 发现圆环 打直
//2 入环  打死一个转角
//3 环内巡线
//4 出环  打死一个转角
//5 离开圆环 打直
#include "zf_common_headfile.h"
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
             if(round->Entrance_count>=25)//min修改，其中有13行满足条件即可判定为圆环 && distance>=1000
             {
                round->Round_flag=1;
                RoundType=Left_Round;
                RoundProcess=Find_Round;

                RoadType= Round_Road;
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
             if(round->Entrance_count>=33 )//min修改，其中有13行满足条件即可判定为圆环
             {
                round->Round_flag=1;
                RoundType=Right_Round;

                RoadType= Round_Road;
                RoundProcess=Find_Round;
             }
          }
       }
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
int Arc_Col=0;//弧顶坐标
int Arc_Row=0;//弧顶坐标
int Arc_Distance=0;
int16 STAT_MAX=40;
int16 STAT_MIN=30;
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
                                //*进入下个阶段的判定---------------------------------------------*/
                                gpio_set_level(BUZZER_PIN, 1);
                                if(Distance_In_Round==0)
                                {
                                    Distance_In_Round=distance;//防止反复赋值
                                }
                                //*无计可施里程计
//                                if(distance-Distance_In_Round>=70)
//                                {
                                if(str->L_StartLine<STAT_MAX && str->L_StartLine>STAT_MIN)   //修改参数
                                {
                                    Round_num=0;
                                    for(Round_row=str->L_StartLine;Round_row>=str->L_StartLine-8&&Round_row>=ROW_START+1;Round_row--)   //防止误判     检测换中心岛
                                {
                                    if(str->LeftEdge[Round_row]!=0&&str->LeftEdge[Round_row-1]!=0)
                                    {
                                        Round_num+=str->LeftEdge[Round_row]-str->LeftEdge[Round_row-1];//内倾
                                    }
                                    else
                                    {
                                        Round_num=0;
                                    }
                                }

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
                                if(Arc_Row>=35)
                                {
                                    RoundProcess=Into_Round;
                                    angke_yaw=0;//进环前yaw角初始化为0
                                    angke_yaw_round=0;
                                }
                                for(int i=40;i>=30;i--)//调参数
                                {
                                       if(str->LeftEdge[i]-str->LeftEdge[i-5]>0&&str->LeftEdge[i]-str->LeftEdge[i+5]>0)//寻找弧顶
                                       {
                                           Arc_Row=i;
                                           Arc_Col=str->LeftEdge[i];
                                           Arc_Distance=str->RightEdge[Arc_Row]-str->LeftEdge[Arc_Row];//弧顶到右边界距离
                                       }
                                }
//                                if(Inflection_point.L_up_point.x!=0 )
//                                {
//                                   Round_num=0;
//                                   RoundProcess=Into_Round;
//                                   angke_yaw=0;//进环前yaw角初始化为0
//                                   angke_yaw_round=0;
//                                }
//


                                //发现gap阶段补线-----------------------------------------------------
//                                for(Round_row=ROW_END;Round_row>=ROW_START;Round_row--)
//                                {
//                                   if(str->RightEdge[Round_row])
//                                   {
//                                       char temp_r;
//                                       char temp_l;
//                                       char track;
//                                       temp_r=str->RightEdge[Round_row];
//                                       track=Round.Track_Width_forRound[Round_row];
//                                       temp_l=temp_r-track-1;
//                                       if(temp_l>=79)
//                                       {
//                                           temp_l=78;
//
//                                       }
//                                       if(temp_l<=1)
//                                       {
//                                           temp_l=1;
//
//                                       }
//                                       str->LeftEdge[Round_row]=temp_l;
//                                     // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
//                                   }
//                                   else
//                                   {
//                                      str->LeftEdge[Round_row]=0;
//                                   }
//                                }
                                break;
                            }
                /*=========*/case Into_Round://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
                                gpio_set_level(BUZZER_PIN, 0);
                                if( angke_yaw>48)
                                {
                                    Arc_Col=0;
                                    Arc_Row=0;
                                    RoundProcess=In_Round;
                                    Arc_Distance=0;

                                }
                               for(int i=ROW_END;i>=ROW_START;i--)
                               {

                                      char temp_r;
                                      char temp_l;
                                      temp_l=str->LeftEdge[i];
                                      temp_r=temp_l+Arc_Distance;
                                      if(temp_l>=79)
                                      {
                                          temp_l=78;

                                      }
                                      if(temp_l<=1)
                                      {
                                          temp_l=1;
                                      }
                                      str->RightEdge[i]=temp_r;
                                    // str->LeftEdge[Round_row]=str->RightEdge[Round_row]-str->track_Width[Round_row];//左边界等于右边界减半宽
                               }



//                                //进环阶段阶段补线-----------------------------------------------------
//                               uint8 flag;flag=0;
//                                for(uint8 h=ROW_END;h>ROW_START;h--)
//                                { if(flag==1)break;
//                                        for(uint8 i=h;i>ROW_START;i--)
//                                        {if(flag==1)break;
//                                            for(uint8 j=COL_START;j<40;j++)
//                                            {
//                                                if(image1[i][j]>=Threshold&&image1[i][j+1]<Threshold)
//                                                {
//                                                    LeftLoopTemp_R=i;//hang
//                                                    LeftLoopTemp_C=j;//lie
//                                                    str->EndLine=i;
//                                                    flag=1;
//                                                    break;
//                                                }
//                                            }
//
//                                        }
//                                }
//                                /*进环斜率*/
//                                if(flag==1) LeftLoopSlope=LeftLoopTemp_C/(float)(ROW_END-8-LeftLoopTemp_R);//>0
//                                else LeftLoopSlope=2.2;
//                                for(uint8 i=0;i<=ROW_END-1-LeftLoopTemp_R;i++)
//                                {
//                                    str->RightEdge[LeftLoopTemp_R+i]=(int)(i*LeftLoopSlope+LeftLoopTemp_C);
//
//                                    if(str->RightEdge[LeftLoopTemp_R+i]>=78)
//                                    {
//                                        str->RightEdge[LeftLoopTemp_R+i]=78;
//                                    }
//                                    if(str->RightEdge[LeftLoopTemp_R+i]<=1)
//                                    {
//                                        str->RightEdge[LeftLoopTemp_R+i]=1;
//                                    }
//                                    if(str->RightEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
//                                       break;
//                                }
                                      break;
                            }
                //不知道什么时候会进Into_Round2
                /*=========*/case Into_Round2://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
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
                    //*进入下个阶段的判定---------------------------------------------*/
                    if(Distance_In_Round==0)
                    {
                        Distance_In_Round=distance;//防止反复赋值
                    }
                    //*无计可施里程计
//                    if(distance-Distance_In_Round>=70)
//                    {

                    if(str->R_StartLine<STAT_MAX && str->R_StartLine>STAT_MIN )   //修改参数
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
                   }
                   /*进环斜率*/
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
                       str->LeftEdge[LeftLoopTemp_R+i]=temp_1;
                   }
                         break;
               }
    /*=========*/case Into_Round2://==========================================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
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
                       if(str->LeftEdge[LeftLoopTemp_R+i]>78||LeftLoopTemp_R+i>ROW_END)
                       break;
                    }
                          break;
                }
#endif
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
unsigned char Round_Enable=1;
void Round_Deal()
{
    if(Round_Enable)
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
}
