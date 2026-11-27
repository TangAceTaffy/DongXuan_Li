/*
 * Obstacle.c
 *
 *  Created on: 2024年4月8日
 *      Author: icand
 */
#include "zf_common_headfile.h"
ObstacleTypeDef ObstacleType;
ObstacleProcessTypeDef ObstacleProcess;
Str_Obstacle Obstacle;
unsigned char  Obstacle_LeftLoopTemp_R=0,Obstacle_LeftLoopTemp_C=0;
unsigned char  Obstacle_RightLoopTemp_R=0,Obstacle_RightLoopTemp_C=0;
float  Obstacle_LeftLoopSlope;
float  Obstacle_RightLoopSlope;
unsigned char  Obstacle_row=0;
unsigned char  Obstacle_col=0;
void Obstacle_Detection(void)
{
    if(RoadType==else_road && Boundary.StartLine==ROW_END && Boundary.EndLine==0)//进入判断条件→位于直道且不是弯道（左右截止在第0行）
    {
        //障碍物阶段一：逐行扫描左边界发现列差两次变大，记录当前行
      if(Elements_Sequence[Elements_Current_Sequence]==16||Elements_Sequence[Elements_Current_Sequence]==0)
      {
        if(Obstacle.row1_flag==0 )//右障碍物判断
        {
            for(uint8 i = ROW_END-10; i >= ROW_START+10; i--)//第一个跳变点，范围可以调前瞻
            {
              if(Boundary.RowLose[i]==1)
              {
                Obstacle.Obstacle_Difference=Boundary.RightEdge[i]-Boundary.RightEdge[i-2];
                if(Obstacle.Obstacle_Difference>=10 && Boundary.RightEdge[i-3]>2&&
                        Boundary.RightEdge[i-2]>2 &&Boundary.RightEdge[i-1]>2&&Boundary.RightEdge[i]>2
                        &&Boundary.RightEdge[i+1]>2&&Boundary.RightEdge[i+2]>2&&Boundary.RightEdge[i+3]>2)//固定row1
                {
                    Obstacle.row1=i;
                    Obstacle.row1_flag=1;
                }
              }
              else
              {
                  break;
              }
            }
        }
        if(Obstacle.row1_flag==1&&Obstacle.Obstacle_flag==0&&ObstacleProcess==None_Obstacle)
               {
                   for(uint8 i = Obstacle.row1-3; i >= Obstacle.row1-3-7; i--)//第一个跳变点所在行前八行开始向上扫第二个跳变点
                   {
                       Obstacle.Obstacle_Difference=ABS(Boundary.RightEdge[i-2]-Boundary.RightEdge[i]);
                       if(Obstacle.Obstacle_Difference>=5||Boundary.RightEdge[i]<60)//||image1[i][col]>=Threshold)//砖头内部差很小
                       {
                         Obstacle.row1_flag=0;
                       }
                       for(uint8 j = Obstacle.row1+5; j>ROW_START+5; j--)//检测另一边线直线
                       {
                           if(Boundary.LeftEdge[j-2]-Boundary.LeftEdge[j]>0)//另一边内倾直线
                           {
                               Obstacle.temp_count1++;
                           }
                       }
                       Obstacle.temp_count1_print=Obstacle.temp_count1;
                       if(Obstacle.temp_count1>=15)//减小可以加前瞻
                       {
                           Obstacle.Obstacle_flag=1;//发现路障
                           RoadType=Barrier;
                           ObstacleProcess=Find_Obstacle;
                           ObstacleType=Right_Obstacle;
                           Obstacle.temp_count1=0;
                       }
                       else
                       {
                           Obstacle.temp_count1=0;
                       }
                   }
               }
      }
      if(Elements_Sequence[Elements_Current_Sequence]==61||Elements_Sequence[Elements_Current_Sequence]==0)
      {
        if(Obstacle.row1_flag==0)//左障碍物判断
               {
                   for(uint8 i = ROW_END-10; i >= ROW_START+10; i--)//第一个跳变点ROW_END-10
                   {
                     if(Boundary.RowLose[i]==1)
                     {
                       Obstacle.Obstacle_Difference=Boundary.LeftEdge[i-2]-Boundary.LeftEdge[i];
                       if(Obstacle.Obstacle_Difference>=5 && Boundary.LeftEdge[i-3]<48&&//防止丢线
                               Boundary.LeftEdge[i-2]<48 &&Boundary.LeftEdge[i-1]<48&&Boundary.LeftEdge[i]<48
                               &&Boundary.LeftEdge[i+1]<48&&Boundary.LeftEdge[i+2]<48&&Boundary.LeftEdge[i+3]<48)//固定row1
                       {
                           Obstacle.row1=i;
                           Obstacle.row1_flag=1;
                       }
                     }
                     else
                     {
                         break;
                     }
                   }
               }

        if(Obstacle.row1_flag==1&&Obstacle.Obstacle_flag==0&&ObstacleProcess==None_Obstacle)
               {
                   for(uint8 i = Obstacle.row1-3; i >= Obstacle.row1-3-7; i--)//第一个跳变点所在行前八行开始向上扫第二个跳变点
                   {
                       Obstacle.Obstacle_Difference=ABS(Boundary.LeftEdge[i-2]-Boundary.LeftEdge[i]);
                       if(Obstacle.Obstacle_Difference>=5||Boundary.LeftEdge[i]>20)//||image1[i][col]>=Threshold)//砖头内部差很小
                       {
                         Obstacle.row1_flag=0;
                       }
                       for(uint8 j = Obstacle.row1+5; j>ROW_START+5; j--)//检测另一边线直线
                       {
                           if(Boundary.RightEdge[j]-Boundary.RightEdge[j-2]>0)//另一边内倾直线
                           {
                               Obstacle.temp_count1++;
                           }
                       }
                       Obstacle.temp_count1_print=Obstacle.temp_count1;
                       if(Obstacle.temp_count1>=15)
                       {
                           Obstacle.Obstacle_flag=1;//发现路障
                           RoadType=Barrier;
                           ObstacleProcess=Find_Obstacle;
                           ObstacleType=Left_Obstacle;
                           Obstacle.temp_count1=0;
                       }
                       else
                       {
                           Obstacle.temp_count1=0;
                       }
                   }
               }
      }

        //障碍物阶段二：判断砖头左右→右障碍物：下面中线所在列大于上面中线所在列
//        if(Obstacle.Obstacle_flag&&ObstacleType==Right_Obstacle)
//        {
//            for(uint8 i = Obstacle.row1-3; i>= Obstacle.row1-6; i--)//加强判断减少别的元素误识别,扫了4行
//            {
//                for(uint8 j = Boundary.RightEdge [i]; j<= Boundary.RightEdge [i]+5; j++)//砖头的6列
//                {
//                    if(image1[i][j]>Threshold)//砖头区域有是黑色就加加
//                    {
//                        Obstacle.temp_count2++;
//                    }
//                }
//            }
//            Obstacle.temp_count2_print=Obstacle.temp_count2;
//            if(Obstacle.temp_count2>=6)
//            {
//                RoadType=Barrier;
//                Obstacle.temp_count2=0;
//            }
//            else
//            {
//                Obstacle.temp_count2=0;
//            }
//
//        }
//        else if(Obstacle.Obstacle_flag&&ObstacleType==Left_Obstacle)
//        {
//            for(uint8 i = Obstacle.row1-3; i>= Obstacle.row1-6; i--)//加强判断减少别的元素误识别,扫了4行
//            {
//                for(uint8 j = Boundary.LeftEdge [i]; j>= Boundary.LeftEdge [i]-5; j--)//砖头的6列
//                {
//                    if(image1[i][j]>Threshold)//砖头区域有一个不是黑色就退出
//                    {
//                        Obstacle.temp_count2++;
//                    }
//                }
//            }
//            Obstacle.temp_count2_print=Obstacle.temp_count2;
//            if(Obstacle.temp_count2>=6)
//            {
//                RoadType=Barrier;
//                Obstacle.temp_count2=0;
//            }
//            else
//            {
//                Obstacle.temp_count2=0;
//            }
//
//        }

    }
}
void Obstacle_Process(Str_Boundary *str)
{
    if(RoadType==Barrier)
    {
        switch(ObstacleType)
               {
       //右障碍物
                  case No_Obstacle:
                  {
                      break;
                  }
                  case Right_Obstacle:
                  {
                      switch(ObstacleProcess)
                      {
                          case Find_Obstacle:
                          {
                              gpio_set_level(BUZZER_PIN, 1);
                              ObstacleProcess=Cross_Obstacle;
                              break;
                          }
                          case Cross_Obstacle:
                          {
                              if(Obstacle.Obstacle_Check_Point1==0)Obstacle.Obstacle_Check_Point1=distance;
                              if(distance-Obstacle.Obstacle_Check_Point1>=30)
                              {
                                 ObstacleProcess=Leave_Obstacle;
                              }
                              for(Obstacle_row=ROW_END;Obstacle_row>=ROW_START;Obstacle_row--)
                              {
                                  if(str->LeftEdge[Obstacle_row])
                                  {
                                      char temp_r;
                                      char temp_l;
                                      char track;
                                      temp_l=str->LeftEdge[Obstacle_row];
                                      track= Obstacle.Track_Width_forObstacle[Obstacle_row];
                                      temp_r=temp_l+track-30;
                                      if(temp_r>=79)temp_r=78;
                                      if(temp_r<=1)temp_r=1;
                                      str->RightEdge[Obstacle_row]=temp_r;
                                  }
                              }

                              break;
                          }
                          case Leave_Obstacle:
                          {
                              if(Obstacle.Obstacle_Check_Point2==0)Obstacle.Obstacle_Check_Point2=distance;
                              if(distance-Obstacle.Obstacle_Check_Point2>=50)
                              {
                                  ObstacleProcess=Out_Obstacle;
                              }
                              break;
                          }
                          case Out_Obstacle:
                          {
                              Obstacle.Obstacle_flag=0;
                              Obstacle.Obstacle_Check_Point1=0;
                              Obstacle.Obstacle_Check_Point2=0;
                              Obstacle.row1_flag=0;Obstacle.row2_flag=0;
                              Obstacle.row1=0;Obstacle.row2=0;
                              gpio_set_level(BUZZER_PIN, 0);
                              ObstacleProcess=No_Obstacle;
                              RoadType=else_road;
                              Elements_Current_Sequence++;
                              break;
                          }
                      }
                      break;
                  }
       //左障碍物
                  case Left_Obstacle:
                  {
                      switch(ObstacleProcess)
                      {
                          case Find_Obstacle:
                          {
                              gpio_set_level(BUZZER_PIN, 1);
                              ObstacleProcess=Cross_Obstacle;
                              break;
                          }
                          case Cross_Obstacle:
                          {
                              if(Obstacle.Obstacle_Check_Point1==0)Obstacle.Obstacle_Check_Point1=distance;
                              if(distance-Obstacle.Obstacle_Check_Point1>=30)
                              {
                                  ObstacleProcess=Leave_Obstacle;
                              }
                              for(Obstacle_row=ROW_END;Obstacle_row>=ROW_START;Obstacle_row--)
                              {
                                  if(str->RightEdge[Obstacle_row])
                                  {
                                      char temp_l;
                                      char temp_r;
                                      char track;
                                      temp_r=str->RightEdge[Obstacle_row];
                                      track=Obstacle.Track_Width_forObstacle[Obstacle_row];
                                      temp_l=temp_r-track+30;
                                      if(temp_l>=79)temp_l=78;
                                      if(temp_l<=1)temp_l=1;
                                      str->LeftEdge[Obstacle_row]=temp_l;
                                  }
                              }
                              break;
                         }
                         case Leave_Obstacle://防止识别到下角点成圆环了
                         {
                             if(Obstacle.Obstacle_Check_Point2==0)Obstacle.Obstacle_Check_Point2=distance;
                             if(distance-Obstacle.Obstacle_Check_Point2>=50)
                             {
                                 ObstacleProcess=Out_Obstacle;
                             }

                             break;
                         }
                         case Out_Obstacle:
                         {
                             Obstacle.Obstacle_flag=0;
                             Obstacle.Obstacle_Check_Point1=0;
                             Obstacle.Obstacle_Check_Point2=0;
                             Obstacle.row1_flag=0;Obstacle.row2_flag=0;
                             Obstacle.row1=0;Obstacle.row2=0;
                             gpio_set_level(BUZZER_PIN, 0);
                             ObstacleType=No_Obstacle;
                             RoadType=else_road;
                             Elements_Current_Sequence++;
                             break;
                         }

                  }
               }
           }
    }

}
void Obstacl_Deal(void)
{         have_element_flag=0;
          if(Obstacle.Obstacle_flag==0)
          {
             Obstacle_Detection();
          }
          else
          {
              for(Obstacle_row=ROW_END-5;Obstacle_row>=ROW_START+5;Obstacle_row--)
              {
                 Obstacle.Track_Width_forObstacle[Obstacle_row]=(int)(0.8*Obstacle_row+22.6);//(1.7*Round_row+5.8); //计算  圆环路宽
              }
              Obstacle_Process(&Boundary);
              have_element_flag=1;
          }

}
