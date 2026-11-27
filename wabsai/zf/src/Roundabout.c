//圆环过程
//1 发现圆环 打直
//2 入环  打死一个转角
//3 环内巡线
//4 出环  打死一个转角
//5 离开圆环 打直
#include "zf_common_headfile.h"
#include <math.h>
Str_Round  Round={0};
RoundTypeDef RoundType;
RoundSizeTypeDef RoundSize;
RoundProcessTypeDef RoundProcess;
unsigned char  Round_row=0;
unsigned char  Round_col=0;
int  Round_num=0;
int  Round_num_1=0;
int  Round_num_2=0;
unsigned char  LeftLoopTemp_R=0,LeftLoopTemp_C=0,Inflection_Temp_x,Inflection_Temp_y;
float  LeftLoopSlope;
float  RightLoopSlope;
float Distance_In_Round=0;
float Round_acc_z;
int Round_Leftroud_num=0;
int Round_Rightroud_num=0;
float  LeftRoundSlope;
float  RightRoundSlope;
int32 angke_yaw_round;
int32 angke_yaw_round1;
int Round_Left_num=0;
int16 LSTAT_MAX=25;
int16 LSTAT_MIN=20;
int16 RSTAT_MAX=25;
int16 RSTAT_MIN=20;
int R_flag;
int r_round_lose,l_round_lose,r_round_lose_flag,l_round_lose_flag;
int L_round_angke=-5400;
int R_round_angke=5000;
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
void Round_Detection(Str_Round *round) //圆环
{
     //左环
       //检测到左下拐点，没检测到右下拐点，结束行比拐点远很多
       if(L_down_point_x>15&&L_down_point_x<80&&r_lose_num<10&&R_down_point_x<3&&R_up_point_x<3)
       {
        // printf("L \n");
        //检测右边线斜率
        // if(abs(l_border[L_down_point_x+1]-l_border[L_down_point_x+24])>5&&abs(l_border[L_down_point_x+8]-l_border[L_down_point_x+30])>5){
       
       
            // printf("L1 \n");
          //左下拐点行的上面三行左边丢线
          if(l_border[L_down_point_x-7]<4&&l_border[L_down_point_x-5]<4&&l_border[L_down_point_x-6]<4)
          {
        //    printf("L2 \n");
             round->Entrance_count=0;//圆环入口计数清零
             if(L_down_point_x+5>ROW_END-1)
                Round_row=ROW_END-1;
             else
                Round_row=L_down_point_x+5;
             for(;Round_row>L_down_point_x-15&&Round_row>=ROW_START;Round_row--)//从左拐点下面5行到上面10行进行搜索
             {
                
              
                   //如果右边正常递减，且不丢线     斜率符合要求
                   float K1_RightEdge;
                   float K2_RightEdge;
                  
                   K1_RightEdge = (float)(r_border[4]-r_border[9])/5.0;
                   K2_RightEdge = (float)(r_border[18]-r_border[30])/12.0;
                //    printf("%f %f \n",K1_RightEdge,K2_RightEdge);

                 
                   if(Float_ABS(K1_RightEdge-K2_RightEdge)<=0.1)//&&ABS(K3_RightEdge-K2_RightEdge)<=0.5
                   {
                    
                      round->Entrance_count++; //圆环入口计数增加
                   }
                
             
             if(round->Entrance_count>=6)//min修改，其中有13行满足条件即可判定为圆环 && distance>=1000
             {
                // printf("l3 \n");
                round->Round_flag=1;
                RoundType=Left_Round;
                RoundProcess=Find_Round;
               angke_yaw_round=0;
                RoadType= Round_Road;
                
                Distance_In_Round=0;
                
                // gpio_set_level(LED, 0x1);
                break;
             }
            // }
        }
    }
    
          }
       

       //右环
       //检测到右下拐点，没检测到左下拐点，结束行比拐点远很多
      
       if(R_down_point_x>15&&R_down_point_x<80&&l_lose_num<10&&L_down_point_x<3&&L_up_point_x<3)
       {
    //   printf("R1 \n");
      
        // if(abs(r_border[R_down_point_x+1]-r_border[R_down_point_x+24])>5&&abs(r_border[R_down_point_x+8]-r_border[R_down_point_x+30])>5){
            // printf("R12 \n");
          
 
          //右下拐点行的上面三行左边丢线
          if(r_border[R_down_point_x-7]>image_w-4&&r_border[R_down_point_x-5]>image_w-4&&r_border[R_down_point_x-6]>image_w-4)
          {
         
            // printf("R2 \n");
             round->Entrance_count=0;//圆环入口计数清零
             if(R_down_point_x+5>ROW_END-1)
                Round_row=ROW_END-1;
             else
                Round_row=R_down_point_x+5;
             for(;Round_row>R_down_point_x-15&&Round_row>=ROW_START;Round_row--)//从右拐点下面5行到上面10行进行搜索
             {
               
                   
                   //如果左边正常递增，且不丢线
                   float K1_LeftEdge;
                   float K2_LeftEdge;
                  
                   
                   K1_LeftEdge = (float)(l_border[4]-l_border[9])/5.0;
                   K2_LeftEdge = (float)(l_border[18]-l_border[30])/12.0;
                //    printf("%f %f \n",K1_LeftEdge,K2_LeftEdge);
                   
                   if(Float_ABS(K1_LeftEdge-K2_LeftEdge)<=0.1)
                   {
                   
                      round->Entrance_count++; //圆环入口计数增加
                   }
                
             
             if(round->Entrance_count>=6 )//min修改，其中有13行满足条件即可判定为圆环
             {
                // printf("r3 \n");
               
             angke_yaw_round=0;
                  round->Round_flag=1;
                Distance_In_Round=0;
                RoundType=Right_Round;
                RoundProcess=Find_Round;
                RoadType= Round_Road;
               
               

               

                
                // gpio_set_level(LED, 0x1);
                break;
             }
            }
        // }
        
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

void Round_Process(Str_Round *round)
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
                          
                                if(Distance_In_Round==0)
                                {
                                    Distance_In_Round=distance;//防止反复赋值
                                }
                                
                               
                             
                                //发现环阶段补线-----------------------------------------------------
                               
                                  
                                        Round_Leftroud_num=2;
                                         gpio_set_level(LED, 0x1);
                                    
                          for(int i=data_stastics_l-15;i>31;i--){
                          
                                if((dir_l[i]==3&&dir_l[i+8]==2&&dir_l[i-30]==5&&distance-Distance_In_Round>300)) {
                                    Round_Left_num++;
                                    angke_yaw_round1+=imu660ra_acc_z;
                                    // printf("%d \n",imu660ra_acc_z);
                                    //  printf("%d\n\n",angke_yaw_round1);
                                }
                                   
                                   
                                    if(Round_Left_num>5){
                                        // printf("L4 \n");
                                        // printf("%d\n",angke_yaw_round1);
                                          angke_yaw_round1=angke_yaw_round1/Round_Left_num;
                                        // printf("%d \n",imu660ra_acc_z-angke_yaw_round1);
                                        // printf("%d \n",imu660ra_acc_z);
                                        // printf("%d \n \n",angke_yaw_round1);
                                          Distance_In_Round=0;
                                           Round_Leftroud_num=0;
                                        Round_Rightroud_num=2;
                                        RoundProcess=Find_Gap;
                                        Round_Left_num=0;
                                       
                                        
                                        
                                        break;
                                    }
                              
                               
                                
                               
                             }
                             break;
                            }

              /*=========*/ case Find_Gap://发现空隙=====================================
                            {
                                // printf("L2 \n");
                                //*进入下个阶段的判定----------------------------------------*/
                                 if(Distance_In_Round==0)
                                {
                                    Distance_In_Round=distance;//防止反复赋值
                                }
                                // *无计可施里程计
                                if(distance-Distance_In_Round>=2)
                                {
                                    Round_num=0;
                                    RoundProcess=Into_Round;
                                    
                                   
                                }
                               
                                 break;
                            }
                /*=========*/case Into_Round://==========================================================
                            {
                                //*进入下个阶段的判定----------------------------------------*/
                            //   printf("L3 \n");
                                if( imu660ra_acc_z-angke_yaw_round1<-1000)
                                {
                                    // printf("%d \n",imu660ra_acc_z-angke_yaw_round1);
                                    RoundProcess=In_Round;
                                  
                                    
                                }

                          
                               
                                      break;
                            }
               
                /*=========*/case In_Round://==========================================================
                            {
                                Round_Leftroud_num=0;
                                //*进入下个阶段的判定----------------------------------------*/
                                if(imu660ra_acc_z-angke_yaw_round1<-2000 )//&& R_down_point_x)
                                {
                                      gpio_set_level(LED, 0x0);
                                    // printf("%d \n",imu660ra_acc_z-angke_yaw_round1);
                                    RoundProcess=Out_Round;
                                  

                                    
                                }
                                //环内阶段阶段补线-----------------------------------------------------

                                    //#无补线操作#//
                                break;
                            }
                /*=========*/case Out_Round://==========================================================
                             {
                                 //*进入下个阶段的判定----------------------------------------*/
                                 if(imu660ra_acc_z-angke_yaw_round1<L_round_angke)
                                 {
                                    // printf("%d \n",imu660ra_acc_z-angke_yaw_round1);
                                    Distance_In_Round=0;
                                     RoundProcess=Leave_Round;
                                     gpio_set_level(LED, 0x1);
                                     Round_Rightroud_num=0;
                                     
                                    
                                 }
                                 //准备出环阶段阶段补线-----------------------------------------------------
                                //  for(int8 i=0;i<=ROW_END;i++)
                                //  {
                                //      r_border[ROW_END-i]=(int)(COL_END+i*(-1.2))-15;
                                //      l_border[ROW_END-i]=1;
                                //      if(r_border[ROW_END-i]>=COL_END)
                                //      {
                                //          r_border[ROW_END-i]=COL_END;
                                //      }
                                //      if(r_border[ROW_END-i]<=1)
                                //      {
                                //          r_border[ROW_END-i]=1;
                                //      }

                                //  }
                                 break;
                             }
                /*=========*/case Leave_Round://==========================================================
                              {
                                if(Distance_In_Round==0)
                                {
                                Distance_In_Round=distance;
                                }
                                 Round_Leftroud_num=2;
                                  //*进入下个阶段的判定----------------------------------------*/
                                 if(distance-Distance_In_Round>1000)//R80:2500
                                 {
                                    Round.Round_flag=0;
                                    RoadType= else_road;
                                       angke_yaw_round1=0;
                                       Round_Leftroud_num=0;
                                       gpio_set_level(LED, 0x0);
                                 }


                                

                                  break;
                              }
                /*=========*/case Leave_Round2://==========================================================
                            {
                                if(distance-Distance_In_Round>=45)
                                {
                                Round.Round_flag=0;
                                RoadType= else_road;
                                }
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
                             
                    if(Distance_In_Round==0)
                                {
                                    
                                    Distance_In_Round=distance;//防止反复赋值
                                }
                    //发现环阶段补线-----------------------------------------------------
                
                            Round_Rightroud_num=2;
                        
                          gpio_set_level(LED, 0x1);
                          for(int i=data_stastics_r-15;i>31;i--){
                          
                                if((dir_r[i]==3&&dir_r[i+8]==2&&dir_r[i-30]==5&&distance-Distance_In_Round>300)) {
                                    Round_Left_num++;
                                    angke_yaw_round+=imu660ra_acc_z;
                                     
                                    //  printf("R4 \n");
                                    //    printf("%d \n",imu660ra_acc_z);
                                    //  printf("%d\n\n",angke_yaw_round);
                                }
                    
                  if(Round_Left_num>5){
                    // printf("%d\n",angke_yaw_round);
                                            angke_yaw_round=angke_yaw_round/Round_Left_num;
                                        // printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                                        // printf("%d \n",imu660ra_acc_z);
                                        // printf("%d \n \n",angke_yaw_round);
                   
                                      
                                     
                                          Distance_In_Round=0;
                                          Round_Rightroud_num=0;
                                        Round_Leftroud_num=2;
                                        RoundProcess=Find_Gap;
                                        Round_Left_num=0;
                                        
                                        
                                    }
                    
                                }
                    
                    break;
                }


                /*=========*/ case Find_Gap://发现空隙=====================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
                    if(Distance_In_Round==0)
                    {
                        Distance_In_Round=distance;//防止反复赋值
                    }
                    // *无计可施里程计
                    if(distance-Distance_In_Round>=2)//可有可无
                    {
                        //  printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                        Round_num=0;
                        RoundProcess=Into_Round;
                        
                        
                        
                    }
                
                    break;
                }
                /*=========*/case Into_Round://==========================================================
                {
                    //*进入下个阶段的判定----------------------------------------*/
               
                    if( imu660ra_acc_z-angke_yaw_round>1000)
                    {
                        //  printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                        RoundProcess=In_Round;
                        
                    }
                  

                   
                        break;
                }

                /*=========*/case In_Round://==========================================================
                {
                    
                 gpio_set_level(LED, 0x0);
                    //*进入下个阶段的判定----------------------------------------*/
                    if(imu660ra_acc_z-angke_yaw_round>1200 )
                    {
                        //  printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                        RoundProcess=Out_Round;
                    }
                    //环内阶段阶段补线-----------------------------------------------------

                        //#无补线操作#//
                    break;
                }
                /*=========*/case Out_Round://==========================================================
                {
                    // int out_round_num;
                    // //*进入下个阶段的判定----------------------------------------*/
                    // out_round_num=0;
                //    for(int i =5;i<60;i++){
                //     if(l_border[i]<l_border[i+1]) {
                //         out_round_num++;
                //         // printf("%d\n",out_round_num);
                //         if(out_round_num>5) break;
                //     }
                //     if(l_border[i]>l_border[i+1]){
                //         r_round_lose_flag++;
                //     }
                //    }
                   
                    if(imu660ra_acc_z-angke_yaw_round>R_round_angke) //l_lose_num<2
                    {
                        //  printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                        Distance_In_Round=0;
                        RoundProcess=Leave_Round;
                        Round_Leftroud_num=0;
                        
                        gpio_set_level(LED, 0x1);
                    }
                    //准备出环阶段阶段补线-----------------------------------------------------
                   
                    break;
                }
                /*=========*/case Leave_Round://==========================================================
                {
                 
                    if(Distance_In_Round==0)
                    {
                        //  printf("%d \n",imu660ra_acc_z-angke_yaw_round);
                    Distance_In_Round=distance;
                    }
                     Round_Rightroud_num=2;
                    //*进入下个阶段的判定----------------------------------------*/
                    if(distance-Distance_In_Round>1000)//R80:2500
                    {
                        Round.Round_flag=0;
                        RoadType= else_road;
                        Round_Rightroud_num=0;
                        angke_yaw_round=0;
                        gpio_set_level(LED, 0x0);
                    }


                    //出环阶段阶段补线-----------------------------------------------------
                 
                    break;
                }
                /*=========*/case Leave_Round2://==========================================================
                {
                    if(distance-Distance_In_Round>=45)
                    {
                    Round.Round_flag=0;
                    RoadType= else_road;

                   
                    }
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
           
             Round_Detection(&Round);        //圆环检测
            
          }
          else
          {
            
              Round_Process(&Round);
          }
    }
}
