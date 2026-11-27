/*
 * edge_find.c
 *
 *  Created on: 2022??5??12??
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
//#include "my_headfile.h"
#define COL_SPACE         2              //?????????
Str_Boundary  Boundary;  //??????
Str_Inflection_point    Inflection_point;   //??????
/*?????????*/
//void L_uppoint(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END,int Edge_ROW);

/*???????*/
int g_threshold_value=45;//?????§Ø????

unsigned char EXTRACT_ROW;//????????
unsigned char EXTRACT_COL;//????????

unsigned char W_num;
unsigned char W_num_row;
unsigned char W_num_col;
unsigned char counting_data;

//unsigned char L_cross_able=0;
//unsigned char R_cross_able=0;

//unsigned char L_Link_num=0;        //???????????????????  0
//unsigned char R_Link_num=0;        //???????????????????  0

//unsigned char Allget_f=0 ;

//???????????§¹???
unsigned char L_edge_last;//???????§¹????
unsigned char R_edge_last;//???????§¹????

//?????????
unsigned char L_edge_in_number;//????????????
unsigned char R_edge_in_number;//????????????

//?????????
unsigned char L_edge_out_number;
unsigned char R_edge_out_number;

//??¾P???
unsigned char L_edge_lose;//??????
unsigned char R_edge_lose;//???????

//?????????¦Ë
int s_L_stop;//????????
int s_R_stop;//????????
//??????¦Ë
 int s_L_get_flag=0;//?????
 int s_R_get_flag=0;//?????

 /*----------------------------------------------------------------------------------------------------------------
 *  @brief   ??????????????
 *  @param
 *
 *
 *
 *  @return  void
 *  @since   v1.0
 *  Sample usage:
 //--------------------------------------------------------------------------------------------------------------*/
 void extract_edge(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)       //???????????????????
 {
//?????------------------------------------------------------------------------------------------------------------
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
 //  L_Row_END=L_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
 //  R_Row_END=R_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
//?????????------------------------------------------------------------------------------------------------------------
   /*????????*/
   for(EXTRACT_ROW=Row_END ; EXTRACT_ROW>Row_START ; EXTRACT_ROW--)
   {
/*??????????????§Ü?????*/
     if(s_L_stop==0 )
     {
       L_extract_edge_process(str, Row_START, Row_END , Col_START, Col_END);
     }
     if(s_R_stop==0 )
     {
       R_extract_edge_process(str, Row_START, Row_END , Col_START, Col_END);
     }

/*??????????????????§Ø?????*/
     if(str->LeftEdge[EXTRACT_ROW]!=0 && str->RightEdge[EXTRACT_ROW]!=0)     //??????§Ò??
      {
         str->RowLose[EXTRACT_ROW] = 1;
      }
      else if(str->LeftEdge[EXTRACT_ROW]!=0 && str->RightEdge[EXTRACT_ROW]==0)//???????
      {
         str->RowLose[EXTRACT_ROW]=2;
      }
      else if(str->LeftEdge[EXTRACT_ROW]==0 && str->RightEdge[EXTRACT_ROW]!=0)//????????
      {
         str->RowLose[EXTRACT_ROW]= 3;
      }
      else if( str->LeftEdge[EXTRACT_ROW]==0&&str->RightEdge[EXTRACT_ROW]==0)//???????   ???????
      {
         str->RowLose[EXTRACT_ROW] = 4;
      }
   }
/*???????§ß?????*/
   //???????????????
   if(str->L_StartLine>str->R_StartLine)
   {
     str->StartLine=str->L_StartLine;

   }
   else
   {
     str->StartLine=str->R_StartLine;
   }
   //??????§³???????
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
 *  @brief   ?????????????
 *  @param   uint8 line[COL/2]

 *  @return  void
 *  @since   v1.0
 *  Sample usage:
 //-----------------------------------------------------------------------------------------------------------------*/
 void L_extract_edge_process(Str_Boundary  *str,  unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
 {

/*?????????????????*/
if(L_edge_lose==0)//???¾P?????0
     {
       /*?????*/
       for(EXTRACT_COL=L_edge_last-(COL_SPACE);EXTRACT_COL+COL_SPACE+1<L_edge_last+10/*????????10*/ && EXTRACT_COL+COL_SPACE+1<Col_END  ;EXTRACT_COL++)
       {

         /*?????????????????????????*/
         if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value
            && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold) )
         {

           break;
         }
         /*???????*/
         if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)
            && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value
              )
         {
              str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE;//-1;//??????

              if(str->RightEdge[EXTRACT_ROW+1]<str->LeftEdge[EXTRACT_ROW]) //??§Ø?  ??????  ?§Ø????????????????????
              {
                  if(str->RightEdge[EXTRACT_ROW+1]!=0&&str->RightEdge[EXTRACT_ROW+2]!=0&&str->RightEdge[EXTRACT_ROW+2]<str->LeftEdge[EXTRACT_ROW]) //?????§Ø?
                  {
                      str->L_EndLine=EXTRACT_ROW;
                      str->R_EndLine=EXTRACT_ROW;
                      s_L_stop=1;
                      s_R_stop=1;
                      return;
                   }
               }

           L_edge_last=EXTRACT_COL+COL_SPACE;//-1;
           L_edge_in_number++;//????????????????
           L_edge_out_number=0;
           L_edge_lose=0;
           break;

         }

       }
/*????????????*/
       if(str->LeftEdge[EXTRACT_ROW]!=0)
       {
         return;
       }
/*????????????íà???????????????(???????????????¡¤?????)----------------------------------------------------------------------------------*/
       else
       {
         // ?????????3???????????????????????????
         if(L_edge_in_number>=3  )//????????????????????????????????????????????????¡À??
         {
           int temp=0;//??????????
           temp=0;
           /*???????,????????????*/
           for(int E_ROW=EXTRACT_ROW+1;E_ROW<EXTRACT_ROW+L_edge_in_number && E_ROW<EXTRACT_ROW+10 && E_ROW<ROW_END;E_ROW++)
           {

             if( str->LeftEdge[E_ROW]-str->LeftEdge[E_ROW+1]>2)//?????-????§³?2??????
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
         /*?????????????§Ø??????*/
         if(EXTRACT_ROW<5 && EXTRACT_ROW>Row_START )//???5?????????????????????????
         {
           str->L_EndLine=EXTRACT_ROW;
           str->R_EndLine=EXTRACT_ROW;
           s_L_stop=1;
           s_R_stop=1;
           return;
         }
         L_edge_in_number=0;//?????
         //L_edge_out_number=0;
       }

/*????????§µ?????-------------------------------------------------------------------------------------------------------*/
       if(L_edge_last>Col_END)//??????????
       {
           L_edge_last=str->LeftEdge[EXTRACT_ROW+1];
       }
       for(EXTRACT_COL=L_edge_last+(COL_SPACE);EXTRACT_COL-COL_SPACE-1>L_edge_last-20 && EXTRACT_COL-COL_SPACE-1>Col_START  ;EXTRACT_COL--)
       {
         if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
            && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value)
         {
           str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE;//??????
           L_edge_last=EXTRACT_COL-COL_SPACE;
           L_edge_out_number++;
           L_edge_lose=0;
           if(Inflection_point.L_up_point.x==0 && Inflection_point.L_down_point.x==0 && str->LeftEdge[EXTRACT_ROW+1]>6 && str->LeftEdge[EXTRACT_ROW+1]<COL_END-8 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //????§Ø??????¦¶??
              {
                 Inflection_point.L_down_point.x=EXTRACT_ROW+1;                           //?›¥?????????¡¤????????????
                 Inflection_point.L_down_point.y=str->LeftEdge[EXTRACT_ROW+1];                //?›¥?????????¡¤????????????
              }
           break;
         }
       }

        /*??????????????????*/
       if(str->LeftEdge[EXTRACT_ROW]==0)
       {
         L_edge_lose++  ;   //????????1
         if(Inflection_point.L_up_point.x==0 && Inflection_point.L_down_point.x==0 && str->LeftEdge[EXTRACT_ROW+1]>6&& EXTRACT_ROW>10 && str->LeftEdge[EXTRACT_ROW+1]<COL_END-8&& EXTRACT_ROW<=Row_END-3 )      //????§Ø??????¦¶??
              {
                 for( char W_num_row=EXTRACT_ROW+1 ; W_num_row<=EXTRACT_ROW+5 ; W_num_row++ )  //????8????????
                 {
                    if( str->LeftEdge[W_num_row]-str->LeftEdge[W_num_row+1]>=0 )
                    {
                       Inflection_point.L_down_point.x=W_num_row;               //?›¥???????????
                       Inflection_point.L_down_point.y=str->LeftEdge[W_num_row];        //?›¥???????????
                       break;
                    }
                 }
              }

          /*??????3???????????????????*/
         if(EXTRACT_ROW<ROW/4 && L_edge_last<COL/4 && L_edge_out_number>2)//?????????????
         {
           int temp=0;
          /*???????????¡À??*/
           for(EXTRACT_COL=L_edge_last; EXTRACT_COL>Col_START && EXTRACT_COL>L_edge_last-10 ;EXTRACT_COL--)//
           {

             if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW+3][EXTRACT_COL])>=g_threshold_value)
             {
               temp++;
               if(temp>3)//???3???¡À??????????????????
               {
                 str->L_EndLine=EXTRACT_ROW;
                 s_L_stop=1;
                 return;
               }
             }
           }
         }
          /*??????????????????????*/
         if(EXTRACT_ROW<Row_START+5 && L_edge_last<Col_START+5 && L_edge_out_number>1)
         {

             str->L_EndLine=EXTRACT_ROW;
             return;

         }
         L_edge_out_number=0;
       }

     }
     /*????????????*/
else// ???????????§Þ????????
     {
       L_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
     }



 }
 /*----------------------------------------------------------------------------------------------------------------
  *  @brief   ????????????
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //-----------------------------------------------------------------------------------------------------------------*/
  int L_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
    /*?????¾P???????§Ö?????????*/
    if(str->RightEdge[EXTRACT_ROW+1]>Col_START)
    {
        /*???????§µ?????????*/
        for(EXTRACT_COL=Col_START;EXTRACT_COL+COL_SPACE+1<str->RightEdge[EXTRACT_ROW+1];EXTRACT_COL++)//??????????????????????????????????
        {
          /*??????????????????*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value&& mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))
          {
            break;
          }
          /*???????*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value
             && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))
          {
            str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE-1;//???????§Õ???
            L_edge_last=EXTRACT_COL;

            /*????¦Å????*/
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
        /*???????§µ?????????*/
        for(EXTRACT_COL=Col_START;EXTRACT_COL+COL_SPACE+1<Col_END;EXTRACT_COL++)//??????????????????????????????????
        {
          /*??????????????????*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value
              && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold))

          {
            break;
          }
          /*???????*/
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)&& difference_sum(image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
          {
            str->LeftEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE-1;//???????§Õ???
            L_edge_last=EXTRACT_COL+COL_SPACE-1;

            if(s_L_get_flag==0)
            {
              str->L_StartLine=EXTRACT_ROW;

            }
             break;
          }
        }
    }
    /*??????¾P?????????*/
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
      s_L_get_flag=1;//????????1
      L_edge_lose=0;
    }
     /*??????????????*/
    else
    {
      /* ????*/
      L_edge_lose++;
      L_edge_out_number=0;
      L_edge_in_number=0;
    }
    return 0;
  }
  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   ???????????
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------*/
  int R_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
    /* ????????????  */
    if(str->LeftEdge[EXTRACT_ROW+1]>Col_START)
    {
      for(EXTRACT_COL=Col_END;EXTRACT_COL-COL_SPACE-1>str->LeftEdge[EXTRACT_ROW+1];EXTRACT_COL--)
      {
        /*??????????????????*/
        if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
           && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))
        {
          break;
        }
        /*???????*/
        if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
          && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
        {
          str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE+1;//???????§Õ???
          R_edge_last=EXTRACT_COL-COL_SPACE+1;

           /*????????*/
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
        /*??????????????????*/
        if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
           && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))

        {
          break;
        }
        /*???????*/
        if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold)
           && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
        {
          str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE+1;//???????§Õ???
          R_edge_last=EXTRACT_COL-COL_SPACE+1;

          if(s_R_get_flag==0)
          {
            str->R_StartLine=EXTRACT_ROW;

          }
           break;
        }
      }
    }
    /*??????¾P?????????*/
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
      s_R_get_flag=1;//????????1
      R_edge_lose=0;//???????0

    }
     /*??????????????*/
    else
    {
      /* ????*/
      R_edge_lose++;
      R_edge_out_number=0;
      R_edge_in_number=0;
    }

    return 0;

  }
  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   ????????????
  *  @param   uint8 line[COL/2]

  *  @return  void
  *  @since   v1.0
  *  Sample usage:
  //--------------------------------------------------------------------------------------------------*/
  void R_extract_edge_process(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END)
  {
      /*?????????????????*/
      if(R_edge_lose==0)
      {
        for(EXTRACT_COL=R_edge_last+(COL_SPACE);EXTRACT_COL-COL_SPACE-1>R_edge_last-20 && EXTRACT_COL-COL_SPACE-1>Col_START  ;EXTRACT_COL--)
        {
          /*?????????????????????????*/
          if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE])>=g_threshold_value
             && mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold))
          {

            break;
          }
          /*???????*/
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],Threshold )
             && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL-COL_SPACE],image1[EXTRACT_ROW][EXTRACT_COL])>=g_threshold_value)
          {
            str->RightEdge[EXTRACT_ROW]=EXTRACT_COL-COL_SPACE;//??????
            if(str->LeftEdge[EXTRACT_ROW+1]>str->RightEdge[EXTRACT_ROW])     //??§Ø?  ??????  ?§Ø????????????????????
            {
              if(str->LeftEdge[EXTRACT_ROW+1]!=0&&str->LeftEdge[EXTRACT_ROW+2]!=0&&str->LeftEdge[EXTRACT_ROW+2]>str->RightEdge[EXTRACT_ROW]) //?????§Ø?
              {
                str->L_EndLine=EXTRACT_ROW;
                str->R_EndLine=EXTRACT_ROW;
                s_L_stop=1;
                s_R_stop=1;

              }
            }
            R_edge_last=EXTRACT_COL-COL_SPACE;
            R_edge_in_number++;//????????????
            R_edge_lose=0;
            break;
          }

        }
         /*????????????*/
        if(str->RightEdge[EXTRACT_ROW]!=0)//???????????????????
        {
          return;
        }
        /*????????????íà???????????????*/
        else
        {
           /*?????????3???????????????????????????*/
          if(R_edge_in_number>=3 )//????????????????????????????????????????????????¡À??
          {
            int temp=0;//??????????
            temp=0;
            /*???????*/
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
          /*?????????????§Ø??????*/
          else if(EXTRACT_ROW<Row_START+5 && EXTRACT_ROW>Row_START )
          {
            str->L_EndLine=EXTRACT_ROW;
            str->R_EndLine=EXTRACT_ROW;
            s_L_stop=1;
            s_R_stop=1;
            return;
          }

          R_edge_in_number=0;//?????
        }
        /*????????§µ?????*/
        if(L_edge_last-(COL_SPACE)<Col_START)//??????????
        {
          L_edge_last=Col_START;
        }
        for(EXTRACT_COL=R_edge_last-(COL_SPACE);EXTRACT_COL+COL_SPACE+1<R_edge_last+20 && EXTRACT_COL+COL_SPACE+1<Col_END  ;EXTRACT_COL++)
        {
          if(mark_middle_num(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE],Threshold)
             && difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW][EXTRACT_COL+COL_SPACE])>=g_threshold_value)
          {
            str->RightEdge[EXTRACT_ROW]=EXTRACT_COL+COL_SPACE;//??????
            R_edge_last=EXTRACT_COL+COL_SPACE;
             R_edge_out_number++;
            R_edge_lose=0;
            if(Inflection_point.R_up_point.x==0 && Inflection_point.R_down_point.x==0 && str->RightEdge[EXTRACT_ROW+1]<COL_END-8 && str->RightEdge[EXTRACT_ROW+1]>COL_START+50 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //????§Ø??????¦¶??
               {
                  Inflection_point.R_down_point.x=EXTRACT_ROW+1;                           //?›¥?????????¡¤????????????
                  Inflection_point.R_down_point.y=str->RightEdge[EXTRACT_ROW+1];                //?›¥?????????¡¤????????????
               }
            break;


          }
        }
         /*??????????????????*/
        if(str->RightEdge[EXTRACT_ROW]==0)
        {
          R_edge_lose++  ;   //????????1
          if(Inflection_point.R_up_point.x==0 && Inflection_point.R_down_point.x==0 && str->RightEdge[EXTRACT_ROW+1]<COL_END-8 && EXTRACT_ROW>10 && EXTRACT_ROW<=Row_END-3 )      //????§Ø??????¦¶??
             {
                Inflection_point.R_down_point.x=EXTRACT_ROW+1;                           //?›¥?????????¡¤????????????
                Inflection_point.R_down_point.y=str->RightEdge[EXTRACT_ROW+1];                //?›¥?????????¡¤????????????
             }
          /*??????3???????????????????*/
          if(EXTRACT_ROW<ROW/4 && R_edge_last>COL/4 && R_edge_out_number>2)//????????????????????????
          {
            int temp=0;
            /*???????????¡À??*/

            for(EXTRACT_COL=R_edge_last; EXTRACT_COL<Col_END && EXTRACT_COL<R_edge_last+5 ;EXTRACT_COL++)//???????¡À??
            {

              if(difference_sum(image1[EXTRACT_ROW][EXTRACT_COL],image1[EXTRACT_ROW+3][EXTRACT_COL])>=g_threshold_value)
              {
                temp++;
                if(temp>3)//???3???¡À??????????????????
                {
                  str->R_EndLine=EXTRACT_ROW;
                  s_R_stop=1;
                  return;
                }

              }

            }
             /*????????????????????*/
          if(EXTRACT_ROW<Row_START+10 && R_edge_last>Col_END-5 && R_edge_out_number>1)
          {

              str->R_EndLine=EXTRACT_ROW;
              return;

          }
             R_edge_out_number=0;
          }
        }

      }
      else// ???????????§Þ????????
      {

        R_extract_edge_start(str, Row_START, Row_END , Col_START, Col_END);
      }
  }


  /*----------------------------------------------------------------------------------------------------------------
  *  @brief   ?????????
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

      for(Row=Edge_ROW;Row>Edge_ROW-10 && Row>ROW_START+1;Row--)//????§á???????10??
      {
        for(Col=COL_START+2;Col<COL_END-14;Col++)//???????
        {
          if(difference_sum(image1[Row][Col+COL_SPACE],image1[Row][Col])>=g_threshold_value)//????????
          {
            if( ABS(Col+COL_SPACE-C1)<=3&& Col+COL_SPACE>=C1)//??????§Ó??§³??3?????C????
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
  *  @brief   ?????????
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

      for(Row=Edge_ROW;Row>Edge_ROW-10 && Row>ROW_START+1;Row--)//????§á???????10??
      {
        for(Col=Col_END-2;Col>15;Col--)//???????
        {
          if(difference_sum(image1[Row][Col-COL_SPACE],image1[Row][Col])>=g_threshold_value)//????????
          {
            if( ABS(Col-COL_SPACE-C1)<=3&& Col-COL_SPACE<=C1)//??????§Ó??§³??3?????C????
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


