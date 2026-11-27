/*
 * edge_find.c
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
#define COL_SPACE         2              //间隔点搜索
Str_Boundary  Boundary;  //边界结构体
Str_Inflection_point    Inflection_point;   //拐点结构体
/*临时变量*/
int g_threshold_value=45;//差比和判断阈值

unsigned char EXTRACT_ROW;//当前提取行
unsigned char EXTRACT_COL;//当前提取列

unsigned char W_num;
unsigned char W_num_row;
unsigned char W_num_col;
unsigned char counting_data;

//储存上一个有效边界
unsigned char L_edge_last;//上一个有效左边界
unsigned char R_edge_last;//上一个有效右边界

//内倾连续值
unsigned char L_edge_in_number;//左内倾连续数
unsigned char R_edge_in_number;//右内倾连续数

//外倾连续值
unsigned char L_edge_out_number;
unsigned char R_edge_out_number;

//边界丢失数
unsigned char L_edge_lose;//左丢线数
unsigned char R_edge_lose;//右丢线数

//搜索停止标志位
int s_L_stop;//左停止搜线
int s_R_stop;//右停止搜线
//得线标志位
 int s_L_get_flag=0;//左得线
 int s_R_get_flag=0;//右得线

 /*----------------------------------------------------------------------------------------------------------------
 *  @brief   图像边界提取主函数
 *  @param
 *
 *
 *
 *  @return  void
 *  @since   v1.0
 *  Sample usage:
 //--------------------------------------------------------------------------------------------------------------*/
 void extract_edge(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)       //此函数为边沿提取主函数
 {
//初始化------------------------------------------------------------------------------------------------------------
   memset(str->LeftEdge, 0,sizeof(str->LeftEdge));
   memset(str->RightEdge,0,sizeof(str->RightEdge));
   memset(str->RowLose,0,sizeof(str->RowLose));
   memset(str->MiddleLine,0,sizeof(str->MiddleLine));
   L_edge_in_number=0;
   R_edge_in_number=0;

   L_edge_last=0;
   R_edge_last=0;

   L_edge_lose=1;
   R_edge_lose=1;

   L_edge_out_number=0;
   R_edge_out_number=0;

   str->L_StartLine=0;
   str->R_StartLine=0;
   str->StartLine=0;

   str->L_EndLine=0;
   str->R_EndLine=0;
   str->EndLine=0;
   s_L_stop=0;
   s_R_stop=0;
   s_L_get_flag=0;
   s_R_get_flag=0;

   Inflection_point.R_up_point.x=0;
   Inflection_point.R_up_point.y=0;
   Inflection_point.R_down_point.x=0;
   Inflection_point.R_down_point.y=0;

   Inflection_point.L_up_point.x=0;
   Inflection_point.L_up_point.y=0;
   Inflection_point.L_down_point.x=0;
   Inflection_point.L_down_point.y=0;
//初始化结束------------------------------------------------------------------------------------------------------------
   /*扫描主循环*/
   for(EXTRACT_ROW=Row_END ; EXTRACT_ROW>Row_START ; EXTRACT_ROW--)
   {
/*当行数到达起始行后开始扫描*/
     if(s_L_stop==0 )
     {
       L_extract_edge_process(str, Row_START, Row_END , Col_START, Col_END);
     }
     if(s_R_stop==0 )
     {
       R_extract_edge_process(str, Row_START, Row_END , Col_START, Col_END);
     }

/*每行左右边界确定后进行判断边界状态*/
     if(str->LeftEdge[EXTRACT_ROW]!=0 && str->RightEdge[EXTRACT_ROW]!=0)     //左右都有边界
      {
         str->RowLose[EXTRACT_ROW] = 1;
      }
      else if(str->LeftEdge[EXTRACT_ROW]!=0 && str->RightEdge[EXTRACT_ROW]==0)//找到左丢右
      {
         str->RowLose[EXTRACT_ROW]=2;
      }
      else if(str->LeftEdge[EXTRACT_ROW]==0 && str->RightEdge[EXTRACT_ROW]!=0)//找到右丢左
      {
         str->RowLose[EXTRACT_ROW]= 3;
      }
      else if( str->LeftEdge[EXTRACT_ROW]==0&&str->RightEdge[EXTRACT_ROW]==0)//两边丢线   等待处理
      {
         str->RowLose[EXTRACT_ROW] = 4;
      }
   }
/*选择起始行结束行*/
   //取第一个最大的起始行
   if(str->L_StartLine>str->R_StartLine)
   {
     str->StartLine=str->L_StartLine;

   }
   else
   {
     str->StartLine=str->R_StartLine;
   }
   //取一个最小的结束行
   if(str->L_EndLine<str->R_EndLine)
   {
     str->EndLine=str->L_EndLine;

   }
   else
   {
     str->EndLine=str->R_EndLine;
   }
 }
 /*----------------------------------------------------------------------------------------------------------------
 *  @brief   左边线连续搜索
 *  @param   uint8 line[COL/2]

 *  @return  void
 *  @since   v1.0
 *  Sample usage:
 //-----------------------------------------------------------------------------------------------------------------*/
 void L_extract_edge_process(Str_Boundary  *str,  unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
 {

     /*连续的话，用跟综巡线*/
     if(L_edge_lose==0)//左边界丢线数为0
     {
       /*向右扫*/
       for(EXTRACT_COL=L_edge_last-(COL_SPACE);EXTRACT_COL+COL_SPACE+1<L_edge_last+10/*向右最多扫10*/ && EXTRACT_COL+COL_SPACE+1<Col_END  ;EXTRACT_COL++)
       {

         /*扫到右边界说明右问题，结束向右扫*/
         if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value
            && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold) )
         {

           break;
         }
         /*扫到左边界*/
         if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)
            && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value
              )
         {
              str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE;//-1;//储存边界

              if(str->RightEdge[EXTRACT_ROW+1]<str->LeftEdge[EXTRACT_ROW]) //预判断  节省时间  判断左边搜到但是在右边界右边
              {
                  if(str->RightEdge[EXTRACT_ROW+1]!=0&&str->RightEdge[EXTRACT_ROW+2]!=0&&str->RightEdge[EXTRACT_ROW+2]<str->LeftEdge[EXTRACT_ROW]) //最终判断
                  {
                      str->L_EndLine=EXTRACT_ROW;
                      str->R_EndLine=EXTRACT_ROW;
                      s_L_stop=1;
                      s_R_stop=1;
                      return;
                   }
               }
           L_edge_last=EXTRACT_COL+COL_SPACE;//-1;
           L_edge_in_number++;//记录内倾边线连续度
           L_edge_out_number=0;
           L_edge_lose=0;
           break;
         }
       }
/*检测是否扫到边界*/
       if(str->LeftEdge[EXTRACT_ROW]!=0)
       {
         return;
       }
/*向右没有找到边界，检测是否为边界结束点(正常巡线不会运行下方程序)----------------------------------------------------------------------------------*/
       else
       {
         // 连续度大于3，上一个边界点在右上，可能为右弯
         if(L_edge_in_number>=3  )//当在图像上端丢失内倾边界时可能是弯道，在这一行向下扫，检测下边界
         {
           int temp=0;//找到的边界点数
           temp=0;
           /*向前找边界,搜索所有内倾*/
           for(int E_ROW=EXTRACT_ROW+1;E_ROW<EXTRACT_ROW+L_edge_in_number && E_ROW<EXTRACT_ROW+10 && E_ROW<ROW_END;E_ROW++)
           {

             if( str->LeftEdge[E_ROW]-str->LeftEdge[E_ROW+1]>2)//上一行-下一行》2，内倾
             {
               temp++;
             }
             if(temp>3)
             {
               str->L_EndLine=EXTRACT_ROW;
               str->R_EndLine=EXTRACT_ROW;
               s_L_stop=1;
               s_R_stop=1;
               return;
             }

           }
         }
         /*在右上角，可以判定为结束*/
         if(EXTRACT_ROW<5 && EXTRACT_ROW>Row_START )//最后5行没必要提取了可能已经到赛道外
         {
           str->L_EndLine=EXTRACT_ROW;
           str->R_EndLine=EXTRACT_ROW;
           s_L_stop=1;
           s_R_stop=1;
           return;
         }
         L_edge_in_number=0;//内倾丢失
         //L_edge_out_number=0;
       }
/*向右搜不行，向左-------------------------------------------------------------------------------------------------------*/
       if(L_edge_last>Col_END)//防止数组越界
       {
           L_edge_last=str->LeftEdge[EXTRACT_ROW+1];
       }
       for(EXTRACT_COL=L_edge_last+(COL_SPACE);EXTRACT_COL-COL_SPACE-1>L_edge_last-20 && EXTRACT_COL-COL_SPACE-1>Col_START  ;EXTRACT_COL--)
       {
         if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
            && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value)
         {
           str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE;//储存边界
           L_edge_last=EXTRACT_COL-COL_SPACE;
           L_edge_out_number++;
           L_edge_lose=0;
           if(Inflection_point.L_up_point.x==0 && Inflection_point.L_down_point.x==0 && str->LeftEdge[EXTRACT_ROW+1]>6 && str->LeftEdge[EXTRACT_ROW+1]<COL_END-8 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //当要判断的点在范围内
              {
                 Inflection_point.L_down_point.x=EXTRACT_ROW+1;                           //存储左边沿十字下方直角拐点行坐标
                 Inflection_point.L_down_point.y=str->LeftEdge[EXTRACT_ROW+1];                //存储左边沿十字下方直角拐点列坐标
              }
           break;
         }
       }
        /*向左也搜不到，有问题*/
       if(str->LeftEdge[EXTRACT_ROW]==0)
       {
         L_edge_lose++  ;   //丢失标志加1
         if(Inflection_point.L_up_point.x==0 && Inflection_point.L_down_point.x==0 && str->LeftEdge[EXTRACT_ROW+1]>6&& EXTRACT_ROW>10 && str->LeftEdge[EXTRACT_ROW+1]<COL_END-8&& EXTRACT_ROW<=Row_END-3 )      //当要判断的点在范围内
              {
                 for( char W_num_row=EXTRACT_ROW+1 ; W_num_row<=EXTRACT_ROW+5 ; W_num_row++ )  //检测前8行内倾数
                 {
                    if( str->LeftEdge[W_num_row]-str->LeftEdge[W_num_row+1]>=0 )
                    {
                       Inflection_point.L_down_point.x=W_num_row;               //存储十字拐点行坐标
                       Inflection_point.L_down_point.y=str->LeftEdge[W_num_row];        //存储十字拐点列坐标
                       break;
                    }
                 }
              }
          /*当连续3点外倾丢失，并且在左上*/
         if(EXTRACT_ROW<ROW/4 && L_edge_last<COL/4 && L_edge_out_number>2)//在图像左上角丢线
         {
           int temp=0;
          /*向左搜，检测下边界*/
           for(EXTRACT_COL=L_edge_last; EXTRACT_COL>Col_START && EXTRACT_COL>L_edge_last-10 ;EXTRACT_COL--)//
           {

             if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW+3][EXTRACT_COL])>=g_threshold_value)
             {
               temp++;
               if(temp>3)//找到3个下边界点就可以结束左边界搜索
               {
                 str->L_EndLine=EXTRACT_ROW;
                 s_L_stop=1;
                 return;
               }
             }
           }
         }
          /*在离左边界很近，出问题，结束*/
         if(EXTRACT_ROW<Row_START+5 && L_edge_last<Col_START+5 && L_edge_out_number>1)
         {

             str->L_EndLine=EXTRACT_ROW;
             return;
         }
         L_edge_out_number=0;
       }

     }
     /*上一次没搜到边界*/
else// 丢线时进入从中间向两边扫
     {
       L_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
     }
 }
 /*----------------------------------------------------------------------------------------------------------------
  *  @brief   丢线搜索函数
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //-----------------------------------------------------------------------------------------------------------------*/
  int L_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
    /*当左边界丢失后，上一行的右边界正常*/
    if(str->RightEdge[EXTRACT_ROW+1]>Col_START)
    {
        /*扫描起始行，从左向右*/
        for(EXTRACT_COL=Col_START;EXTRACT_COL+COL_SPACE+1<str->RightEdge[EXTRACT_ROW+1];EXTRACT_COL++)//开始后左线从左向右扫，如果扫到右边界停止扫描
        {
          /*扫到右边界就结束本行扫描*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value&& mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))
          {
            break;
          }
          /*扫到左边界*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value
             && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))
          {
            str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE-1;//找到起始行储存
            L_edge_last=EXTRACT_COL;

            /*第一次得到线*/
            if(s_L_get_flag==0)
            {
              str->L_StartLine=EXTRACT_ROW;

            }
            break;
          }
        }

    }
    else
    {
        /*扫描起始行，从左向右*/
        for(EXTRACT_COL=Col_START;EXTRACT_COL+COL_SPACE+1<Col_END;EXTRACT_COL++)//开始后左线从左向右扫，如果扫到右边界停止扫描
        {
          /*扫到右边界就结束本行扫描*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value
              && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))

          {
            break;
          }
          /*扫到左边界*/
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)&& difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
          {
            str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE-1;//找到起始行储存
            L_edge_last=EXTRACT_COL+COL_SPACE-1;

            if(s_L_get_flag==0)
            {
              str->L_StartLine=EXTRACT_ROW;

            }
             break;
          }
        }
    }
    /*如果左边界丢线又找到了*/
    if(str->LeftEdge[EXTRACT_ROW]!=0)
    {
 if (Inflection_point.L_down_point.x==0)
 {
     if( L_edge_lose>5 && str->LeftEdge[EXTRACT_ROW]>(COL_START-1)+5 && Inflection_point.L_up_point.x==0&&EXTRACT_ROW<(ROW_END+1)/2)
     {
         //L_uppoint_1(str, EXTRACT_ROW, Row_END , str->LeftEdge[EXTRACT_ROW], Col_END);
        L_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
     if( s_L_get_flag==0 && str->LeftEdge[EXTRACT_ROW]>(COL_START-1)+5 && Inflection_point.L_up_point.x==0&&EXTRACT_ROW<(ROW_END+1)/3)
      {
          //L_uppoint_1(str, EXTRACT_ROW, Row_END , str->LeftEdge[EXTRACT_ROW], Col_END);
         L_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);

      }
 }
 else
 {
     if( L_edge_lose>5 && str->LeftEdge[EXTRACT_ROW]>(COL_START-1)+5 && Inflection_point.L_up_point.x==0&&EXTRACT_ROW>5)
     {
         //L_uppoint_1(str, EXTRACT_ROW, Row_END , str->LeftEdge[EXTRACT_ROW], Col_END);
        L_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
     if( s_L_get_flag==0 && str->LeftEdge[EXTRACT_ROW]>(COL_START-1)+5 && Inflection_point.L_up_point.x==0&&EXTRACT_ROW<(ROW_END+1)-5)
      {
          //L_uppoint_1(str, EXTRACT_ROW, Row_END , str->LeftEdge[EXTRACT_ROW], Col_END);
         L_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);

      }
 }
      s_L_get_flag=1;//获得线标志为1
      L_edge_lose=0;
    }
     /*如果左边界继续丢线*/
    else
    {
      /* 丢边*/
      L_edge_lose++;
      L_edge_out_number=0;
      L_edge_in_number=0;
    }
    return 0;
  }
  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   右边界起始函数
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------*/
  int R_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
    /* 如果上一行左边界  */
    if(str->LeftEdge[EXTRACT_ROW+1]>Col_START)
    {
      for(EXTRACT_COL=Col_END;EXTRACT_COL-COL_SPACE-1>str->LeftEdge[EXTRACT_ROW+1];EXTRACT_COL--)
      {
        /*扫到左边界就结束本行扫描*/
        if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
           && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))
        {
          break;
        }
        /*扫到右边界*/
        if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
          && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
        {
          str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE+1;//找到起始行储存
          R_edge_last=EXTRACT_COL-COL_SPACE+1;

           /*记录起始行*/
          if(s_R_get_flag==0)
          {
            str->R_StartLine=EXTRACT_ROW;

          }
          break;

        }
      }
    }
    else
    {
      for(EXTRACT_COL=Col_END;EXTRACT_COL-COL_SPACE-1>Col_START;EXTRACT_COL--)
      {
        /*扫到左边界就结束本行扫描*/
        if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
           && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))

        {
          break;
        }
        /*扫到右边界*/
        if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
           && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
        {
          str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE+1;//找到起始行储存
          R_edge_last=EXTRACT_COL-COL_SPACE+1;

          if(s_R_get_flag==0)
          {
            str->R_StartLine=EXTRACT_ROW;

          }
           break;
        }
      }
    }
    /*如果右边界丢线又找到了*/
    if(str->RightEdge[EXTRACT_ROW]!=0)
    {
 if (Inflection_point.R_down_point.x==0)
 {

     if( R_edge_lose>5 && str->RightEdge[EXTRACT_ROW]<(COL_END+1)-5 && Inflection_point.R_up_point.x==0&&EXTRACT_ROW<(ROW_END+1)/2)
     {
        R_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
     if( s_R_get_flag==0 && str->RightEdge[EXTRACT_ROW]<(COL_END+1)-5 && Inflection_point.R_up_point.x==0&&EXTRACT_ROW<(ROW_END+1)/3)
     {
         R_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
 }
 else
 {
     if( R_edge_lose>5 && str->RightEdge[EXTRACT_ROW]<(COL_END+1)-5 && Inflection_point.R_up_point.x==0&&EXTRACT_ROW>5)
     {
        R_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
     if( s_R_get_flag==0 && str->RightEdge[EXTRACT_ROW]<(COL_END+1)-5 && Inflection_point.R_up_point.x==0&&EXTRACT_ROW<ROW_END-5)
     {
         R_uppoint(str, Row_START, Row_END , Col_START, Col_END,EXTRACT_ROW);
     }
 }
      s_R_get_flag=1;//获得线标志为1
      R_edge_lose=0;//丢失标志为0

    }
     /*如果右边界继续丢线*/
    else
    {
      /* 丢边*/
      R_edge_lose++;
      R_edge_out_number=0;
      R_edge_in_number=0;
    }

    return 0;

  }
  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   右边界连续函数
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------*/
  void R_extract_edge_process(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
      /*连续的话，用跟综巡线*/
      if(R_edge_lose==0)
      {
        for(EXTRACT_COL=R_edge_last+(COL_SPACE);EXTRACT_COL-COL_SPACE-1>R_edge_last-20 && EXTRACT_COL-COL_SPACE-1>Col_START  ;EXTRACT_COL--)
        {
          /*扫到左边界说明有问题，结束向左扫*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
             && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))
          {

            break;
          }
          /*扫到右边界*/
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold )
             && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
          {
            str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE;//储存边界
            if(str->LeftEdge[EXTRACT_ROW+1]>str->RightEdge[EXTRACT_ROW])     //预判断  节省时间  判断左边搜到但是在右边界右边
            {
              if(str->LeftEdge[EXTRACT_ROW+1]!=0&&str->LeftEdge[EXTRACT_ROW+2]!=0&&str->LeftEdge[EXTRACT_ROW+2]>str->RightEdge[EXTRACT_ROW]) //最终判断
              {
                str->L_EndLine=EXTRACT_ROW;
                str->R_EndLine=EXTRACT_ROW;
                s_L_stop=1;
                s_R_stop=1;

              }
            }
            R_edge_last=EXTRACT_COL-COL_SPACE;
            R_edge_in_number++;//检测边线连续度
            R_edge_lose=0;
            break;
          }

        }
         /*检测是否扫到边界*/
        if(str->RightEdge[EXTRACT_ROW]!=0)//向右扫得到边界后，结束本行
        {
          return;
        }
        /*向左没有找到边界，检测是否为边界结束点*/
        else
        {
           /*连续度大于3，上一个边界点在左上，可能为左弯*/
          if(R_edge_in_number>=3 )//当在图像上端丢失内倾边界时可能是弯道，在这一行向下扫，检测下边界
          {
            int temp=0;//找到的边界点数
            temp=0;
            /*向前找边界*/
            for(int E_ROW=EXTRACT_ROW+1;E_ROW<EXTRACT_ROW+R_edge_in_number && E_ROW<EXTRACT_ROW+5 && E_ROW<ROW_END;E_ROW++)
            {
              if(str->RightEdge[E_ROW+1]-str->RightEdge[E_ROW]>2)
              {
                temp++;
              }
              if(temp>3)
              {
                str->L_EndLine=EXTRACT_ROW;
                str->R_EndLine=EXTRACT_ROW;
                s_L_stop=1;
                s_R_stop=1;
                return;
              }
            }
          }
          /*在左上角，可以判定为结束*/
          else if(EXTRACT_ROW<Row_START+5 && EXTRACT_ROW>Row_START )
          {
            str->L_EndLine=EXTRACT_ROW;
            str->R_EndLine=EXTRACT_ROW;
            s_L_stop=1;
            s_R_stop=1;
            return;
          }

          R_edge_in_number=0;//内倾丢失
        }
        /*向左搜不行，向右*/
        if(L_edge_last-(COL_SPACE)<Col_START)//防止数组越界
        {
          L_edge_last=Col_START;
        }
        for(EXTRACT_COL=R_edge_last-(COL_SPACE);EXTRACT_COL+COL_SPACE+1<R_edge_last+20 && EXTRACT_COL+COL_SPACE+1<Col_END  ;EXTRACT_COL++)
        {
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)
             && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value)
          {
            str->RightEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE;//储存边界
            R_edge_last=EXTRACT_COL+COL_SPACE;
             R_edge_out_number++;
            R_edge_lose=0;
            if(Inflection_point.R_up_point.x==0 && Inflection_point.R_down_point.x==0 && str->RightEdge[EXTRACT_ROW+1]<COL_END-8 && str->RightEdge[EXTRACT_ROW+1]>COL_START+50 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //当要判断的点在范围内
               {
                  Inflection_point.R_down_point.x=EXTRACT_ROW+1;                           //存储左边沿十字下方直角拐点行坐标
                  Inflection_point.R_down_point.y=str->RightEdge[EXTRACT_ROW+1];                //存储左边沿十字下方直角拐点列坐标
               }
            break;


          }
        }
         /*向右也搜不到，有问题*/
        if(str->RightEdge[EXTRACT_ROW]==0)
        {
          R_edge_lose++  ;   //丢失标志加1
          if(Inflection_point.R_up_point.x==0 && Inflection_point.R_down_point.x==0 && str->RightEdge[EXTRACT_ROW+1]<COL_END-8 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //当要判断的点在范围内
             {
                Inflection_point.R_down_point.x=EXTRACT_ROW+1;                           //存储左边沿十字下方直角拐点行坐标
                Inflection_point.R_down_point.y=str->RightEdge[EXTRACT_ROW+1];                //存储左边沿十字下方直角拐点列坐标
             }
          /*当连续3点外倾丢失，并且在右上*/
          if(EXTRACT_ROW<ROW/4 && R_edge_last>COL/4 && R_edge_out_number>2)//在图像右上角丢线，可能是右弯
          {
            int temp=0;
            /*向右搜，检测下边界*/

            for(EXTRACT_COL=R_edge_last; EXTRACT_COL<Col_END && EXTRACT_COL<R_edge_last+5 ;EXTRACT_COL++)//向右搜下边界
            {

              if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW+3][EXTRACT_COL])>=g_threshold_value)
              {
                temp++;
                if(temp>3)//找到3个下边界点就可以结束右边界搜索
                {
                  str->R_EndLine=EXTRACT_ROW;
                  s_R_stop=1;
                  return;
                }

              }

            }
             /*离右边界很近，出问题，结束*/
          if(EXTRACT_ROW<Row_START+10 && R_edge_last>Col_END-5 && R_edge_out_number>1)
          {

              str->R_EndLine=EXTRACT_ROW;
              return;

          }
             R_edge_out_number=0;
          }
        }

      }
      else// 丢线时进入从中间向两边扫
      {

        R_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
      }
  }


  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   检测左上拐点
  *  @param   im[ROW/2][COL/2]

  *               EDGE *L_E

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //-----------------------------------------------------------------------------------------------------------------*/

  void L_uppoint(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END,unsigned char Edge_ROW)
  {
    int Col;
    //uint8 N_P=0;
    int C1=0;
    int Row=Edge_ROW;

      for(Row=Edge_ROW;Row>Edge_ROW-10 && Row>ROW_START+1;Row--)//从本行开始向上扫10行
      {
        for(Col=COL_START+2;Col<COL_END-14;Col++)//初始值固定
        {
          if(difference_sum(image1[Row][Col+COL_SPACE],image1[Row][Col])>=g_threshold_value)//检测到跳变点
          {
            if( ABS(Col+COL_SPACE-C1)<=3&& Col+COL_SPACE>=C1)//如果两列差值小于3，说明C为拐点
            {
              Inflection_point.L_up_point.x=Row;
              Inflection_point.L_up_point.y=C1;
              return;
             }
            C1=Col+COL_SPACE;
            break;

        }
      }
   }
  }
  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   检测右上拐点
  *  @param   im[ROW/2][COL/2]

  *               EDGE *L_E

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //-----------------------------------------------------------------------------------------------------------------*/

  void R_uppoint(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END,unsigned char Edge_ROW)
  {
    int Col;
    //uint8 N_P=0;
    int C1=0;

    int Row=Edge_ROW;

      for(Row=Edge_ROW;Row>Edge_ROW-10 && Row>ROW_START+1;Row--)//从本行开始向上扫10行
      {
        for(Col=Col_END-2;Col>15;Col--)//初始值固定
        {
          if(difference_sum(image1[Row][Col-COL_SPACE],image1[Row][Col])>=g_threshold_value)//检测到跳变点
          {
            if( ABS(Col-COL_SPACE-C1)<=3&& Col-COL_SPACE<=C1)//如果两列差值小于3，说明C为拐点
            {
              Inflection_point.R_up_point.x=Row;
              Inflection_point.R_up_point.y=C1;
              return;
             }
            C1=Col-COL_SPACE;
            break;

        }
      }
   }
  }


