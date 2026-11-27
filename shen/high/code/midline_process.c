/*
 * midline_process.c
 *
 *  Created on: 2022锟斤拷5锟斤拷12锟斤拷
 *      Author: hakuya
 */
#include "zf_common_headfile.h"

/***************************************************************
锟斤拷锟斤拷

* 锟斤拷锟斤拷锟斤拷锟狡ｏ拷
* 锟斤拷锟斤拷说锟斤拷锟斤拷  temp
* 锟斤拷锟斤拷说锟斤拷锟斤拷
* 锟斤拷锟斤拷锟斤拷锟截ｏ拷voiold
* 锟睫革拷时锟戒：
* 锟斤拷 注锟斤拷
**************************************************************/
//uint8 track_Theoretical_width[ROW]={
//6       ,  8    ,  10   ,  12   ,  14   ,
//16    ,  18   ,  20   ,  22   ,  24   ,
//26    ,  28   ,  30   ,  32   ,  34   ,
//36    ,  38   ,  40   ,  41   ,  43   ,
//45    ,  47   ,  49   ,  51   ,  52   ,
//54    ,  56   ,  58   ,  60   ,  62   ,
//64    ,  66   ,  68   ,  70   ,  71   ,
//73    ,  75   ,  77   ,  79   ,  81   ,
//83    ,  85   ,  87   ,  89   ,  91   ,
//93    ,  95   ,  97   ,  98   ,  100  ,
//101   ,  103  ,  105  ,  107  ,  109  ,
//111   ,  113  ,  114  ,  115  ,  117  ,
//119   ,  121  ,  123  ,  125  ,  127  ,
//128   ,  129  ,  131  ,  133  ,  135  ,
//137   ,  138  ,  139  ,  140  ,  142  ,
//144   ,  146  ,  148  ,  150  ,  152
//};
//float mid_k[ROW_END]={0};

//uint8 CenterBlack[ROW/2]={0};
//float Deviation=0;//偏锟斤拷
//uint8  Mline_end =0 ;
//float Camera_CenterError ;
//float slope_coefficient ;
int L_recover_row=0;//锟斤拷指锟斤拷锟�
int R_recover_row=0;//锟揭恢革拷锟斤拷
//float Getrouteoffset2(unsigned char start,unsigned char end,float midpos)
//{
//  unsigned char i=0;
//  //unsigned char iCount=0;
//  float  Black_Sum=0;
//  float weightSum = 0;
//  float TemError = 0.0;
// if(end<ROW_START)
// {
//   end=ROW_START+2;
// }
//  if(start<end)
//  {
//    return TemError;
//  }
//  else
//  {
//
//     for(i=start; i>end;i--)
//     {
//        Black_Sum += (midpos-Boundary.MiddleLine[i]);
//        weightSum += 1;
//     }
//     TemError =Black_Sum/weightSum;
//
//     if(TemError > 32)
//     {
//        TemError =32;
//     }
//     if(TemError < -32)
//     {
//        TemError = -32;
//     }
//     return TemError;
//  }
//}



int ExtractCenterline_1()
{
    //tft180_show_int32(60,100,1,6);//锟斤拷锟斤拷锟斤拷
  if(Boundary.LeftEdge[ROW_END]!=0 && Boundary.RightEdge[ROW_END]!=0)     //锟斤拷锟揭讹拷锟叫边斤拷
  {
    Boundary.MiddleLine[ROW_END] =(Boundary.LeftEdge[ROW_END] +Boundary.RightEdge[ROW_END])/2;//锟斤拷锟斤拷页锟斤拷锟�2

  }
  else if(Boundary.LeftEdge[ROW_END]!=0 && Boundary.RightEdge[ROW_END]==0)//find left
  {
    Boundary.RightEdge[ROW_END]=COL_END;//锟揭讹拷锟斤拷锟斤拷锟揭憋拷
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//锟斤拷锟斤拷页锟斤拷锟�2

  }
  else if( Boundary.LeftEdge[ROW_END]==0 && Boundary.RightEdge[ROW_END]!=0)//find right
  {
    Boundary.LeftEdge[ROW_END]=0;//锟斤拷锟斤拷0
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//锟斤拷锟斤拷页锟斤拷锟�2

  }
  else if( Boundary.LeftEdge[ROW_END]==0 &&Boundary.RightEdge[ROW_END]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
  {
    Boundary.LeftEdge[ROW_END]=0;
    Boundary.RightEdge[ROW_END]=COL_END;
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//取锟斤拷幕锟斤拷锟叫硷拷
  }

  //// 锟接第讹拷锟叫匡拷始锟斤拷锟斤拷

  for(int i=ROW_END-1;i>=ROW_START;i--)
  {
   if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //锟斤拷锟揭讹拷锟叫边斤拷
    {
          Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])/2;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
        if(Boundary.LeftEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
         {
           Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + Boundary.MiddleLine[i+1]-Boundary.LeftEdge[i+1];
                     if(Boundary.MiddleLine[i]>(COL_END+1)-2)
                     {
                         Boundary.MiddleLine[i]=(COL_END+1)-2;
                     }
          }
       else
           {
                Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + Boundary.track_Width[i]/2;
                if(Boundary.MiddleLine[i]>(COL_END+1)-2)
                {
                    Boundary.MiddleLine[i]=(COL_END+1)-2;
                }
          }
    }
    else if(Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]!=0)//find right
    {

         if(Boundary.RightEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
           {
            // Boundary.MiddleLine[i]=Boundary.RightEdge[i] + Boundary.MiddleLine[i+1]-Boundary.RightEdge[i+1];
             int temp_r1=Boundary.RightEdge[i+1];//锟斤拷时锟叫凤拷锟脚憋拷锟斤拷锟斤拷止锟斤拷锟斤拷锟斤拷锟�
             int temp_m1=Boundary.MiddleLine[i+1];
             int temp_r=Boundary.RightEdge[i];
             int temp_m;
             temp_m=temp_r-ABS(temp_r1-temp_m1);
             //if(temp_m<=0) temp_m=1;
             if(temp_m>(COL_END+1)-2)
             {
                 temp_m=(COL_END+1)-2;
             }
             if (temp_m<=0)
             {
                 temp_m=1;
            }
           Boundary.MiddleLine[i]=temp_m;

           }
       else
         {
            Boundary.MiddleLine[i]  = Boundary.RightEdge[i] - Boundary.track_Width[i]/2;
            if(Boundary.MiddleLine[i]>(COL_END+1)-2)
            {
                Boundary.MiddleLine[i]=(COL_END+1)-2;
            }


          }

   }
    else if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
   {

            Boundary.MiddleLine[i]=Boundary.MiddleLine[i+1];

    }
  }
  return  0;
}

/*锟矫筹拷锟斤拷呋指锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷要锟斤拷锟揭憋拷锟斤拷锟斤拷卟锟斤拷锟�*/
void ExtractCenterline_L()
{
    //tft180_show_int32(60,100,2,6);//锟斤拷锟斤拷锟斤拷
  /* 锟斤拷锟斤拷指锟斤拷械锟� 实锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷直锟斤拷锟斤拷锟斤拷锟斤拷锟饺的憋拷值 */
  float temp=(float)(Boundary.RightEdge[L_recover_row]-Boundary.LeftEdge[L_recover_row])/(float)Boundary.track_Width[L_recover_row];

  /* 锟矫筹拷锟斤拷呋指锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷要锟斤拷锟揭憋拷锟斤拷锟斤拷卟锟斤拷锟� */
  for(int i=L_recover_row;i<=ROW_END;i++)
  {
    if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
    {
          Boundary.MiddleLine[i]=Boundary.MiddleLine[i-1] ;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]!=0)//锟斤拷叨锟斤拷锟�   锟斤拷锟揭边诧拷
    {
        int temp_m;
         temp_m  = Boundary.RightEdge[i] - (int)((float)Boundary.track_Width[i]*temp)/2;
         if(temp_m>(COL_END+1)-2)
         {
             temp_m=(COL_END+1)-2;
         }
         if(temp_m<=1)
         {
             temp_m=1;
         }
         Boundary.MiddleLine[i]=temp_m;

    }
    else if(Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]!=0)//锟斤拷锟揭讹拷锟斤拷取锟斤拷值
    {
          Boundary.MiddleLine[i] =(Boundary.LeftEdge[i] + Boundary.RightEdge[i])>>1;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
  }
  /*锟斤拷锟斤拷呋指锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷*/
  for(int i=L_recover_row;i>=ROW_START;i--)
  {
    if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //锟斤拷锟揭讹拷锟叫边斤拷
    {
          Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])>>1;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
          if(Boundary.LeftEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
          {
            Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + Boundary.MiddleLine[i+1]-Boundary.LeftEdge[i+1];
            if(Boundary.MiddleLine[i]>(COL_END+1)-2)
            {
                Boundary.MiddleLine[i]=(COL_END+1)-2;
            }

          }
          else
          {
            Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + (int)((float)Boundary.track_Width[i]*temp)/2;
            if(Boundary.MiddleLine[i]>(COL_END+1)-2)
            {
                Boundary.MiddleLine[i]=(COL_END+1)-2;
            }

          }
    }
    else if(Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]!=0)//find right
    {
        //tft180_show_int32(60,60,2,6);//锟斤拷锟斤拷锟斤拷

          if(Boundary.RightEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
          {
              int temp_r1=Boundary.RightEdge[i+1];//锟斤拷时锟叫凤拷锟脚憋拷锟斤拷锟斤拷止锟斤拷锟斤拷锟斤拷锟�
              int temp_m1=Boundary.MiddleLine[i+1];
              int temp_r=Boundary.RightEdge[i];
              int temp_m;
              temp_m=temp_r-ABS(temp_r1-temp_m1);
              if(temp_m<=0) temp_m=0;
              if(temp_m>(COL_END+1)-2)
              {
                  temp_m=(COL_END+1)-2;
              }
              if (temp_m<=0)
              {
                  temp_m=1;
             }
            Boundary.MiddleLine[i]=temp_m;
            //if()
          }
          else
          {
            Boundary.MiddleLine[i]  = Boundary.RightEdge[i] - (int)((float)Boundary.track_Width[i]*temp)/2;
            if(Boundary.MiddleLine[i]>(COL_END+1)-2)
            {
                Boundary.MiddleLine[i]=(COL_END+1)-2;
            }
            if(Boundary.MiddleLine[i]<= COL_START)
             {
                 Boundary.MiddleLine[i]=1;
             }
          }

    }
    else if( Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
    {
        //tft180_show_int32(60,60,3,6);//锟斤拷锟斤拷锟斤拷
          Boundary.MiddleLine[i]=Boundary.MiddleLine[i+1] ;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
  }

}
/*锟矫筹拷锟揭边恢革拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷撸锟斤拷锟揭拷锟斤拷锟斤拷锟斤拷锟揭边诧拷锟斤拷*/
void ExtractCenterline_R()
{
    //tft180_show_int32(60,100,3,6);//锟斤拷锟斤拷锟斤拷
  /* 锟斤拷锟斤拷指锟斤拷械锟� 实锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷直锟斤拷锟斤拷锟斤拷锟斤拷锟饺的憋拷值 */
  float temp=(float)(Boundary.RightEdge[R_recover_row]-Boundary.LeftEdge[R_recover_row])/(float)Boundary.track_Width[R_recover_row];

  for(int i=R_recover_row;i<=ROW_END;i++)
  {
    if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
    {

            Boundary.MiddleLine[i]=Boundary.MiddleLine[i-1] ;

      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if( Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]==0)//锟斤拷锟斤拷
    {
      Boundary.MiddleLine[i]  = Boundary.LeftEdge[i]+(int)((float)Boundary.track_Width[i]*temp)/2;
      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if(Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]!=0)//锟斤拷锟斤拷锟斤拷
    {
       Boundary.MiddleLine[i] =(Boundary.LeftEdge[i] + Boundary.RightEdge[i])>>1;
       if(Boundary.MiddleLine[i]>(COL_END+1)-2)
       {
           Boundary.MiddleLine[i]=(COL_END+1)-2;
       }
    }
  }
   /*锟矫筹拷锟揭边恢革拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�*/
  for(int i=R_recover_row;i>=ROW_START;i--)
  {
    if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //锟斤拷锟揭讹拷锟叫边斤拷
    {
      Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])>>1;
      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
      if(Boundary.LeftEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
      {
        Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + Boundary.MiddleLine[i+1]-Boundary.LeftEdge[i+1];
        if(Boundary.MiddleLine[i]>(COL_END+1)-2)
        {
            Boundary.MiddleLine[i]=(COL_END+1)-2;
        }
      }
      else
      {
        Boundary.MiddleLine[i]=Boundary.LeftEdge[i] + (int)((float)Boundary.track_Width[i]*temp)/2;
        if(Boundary.MiddleLine[i]>(COL_END+1)-2)
        {
            Boundary.MiddleLine[i]=(COL_END+1)-2;
        }

      }
    }
    else if(Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]!=0)//find right
    {

      if(Boundary.RightEdge[i+1]!=0) //锟斤拷锟斤拷锟斤拷锟�
      {
          int temp_r1=Boundary.RightEdge[i+1];//锟斤拷时锟叫凤拷锟脚憋拷锟斤拷锟斤拷止锟斤拷锟斤拷锟斤拷锟�
          int temp_m1=Boundary.MiddleLine[i+1];
          int temp_r=Boundary.RightEdge[i];
          int temp_m;
          temp_m=temp_r-ABS(temp_r1-temp_m1);

          //if(temp_m<=0) temp_m=0;
          if(temp_m>(COL_END+1)-2)
          {
              temp_m=(COL_END+1)-2;
          }
          if (temp_m<=0)
          {
              temp_m=1;
         }
        Boundary.MiddleLine[i]=temp_m;
      }
      else
      {
       Boundary.MiddleLine[i]  = Boundary.RightEdge[i] - (int)((float)Boundary.track_Width[i]*temp)/2;
       if(Boundary.MiddleLine[i]>(COL_END+1)-2)
       {
           Boundary.MiddleLine[i]=(COL_END+1)-2;
       }
      }

    }
    else if( Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]==0)//锟斤拷锟竭讹拷锟斤拷   d锟斤拷锟斤拷锟斤拷
    {
      Boundary.MiddleLine[i]=Boundary.MiddleLine[i+1] ;
      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }
    }
  }
}
int ExtractCenterline(Str_Boundary  *str)
{
    //tft180_show_int32(60,100,3,6);//锟斤拷锟斤拷锟斤拷
       uint8 i;
       L_recover_row=0;//锟斤拷指锟斤拷锟�
       R_recover_row=0;//锟揭恢革拷锟斤拷


       /*锟斤拷锟斤拷路锟斤拷*/
       for(i=ROW_END;i>0 ;i--)
       {
          str->track_Width[i]=(int)(i*Width_P+24.6); //锟斤拷锟斤拷  路锟斤拷
       }


       /*通锟斤拷锟叫讹拷锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷锟叫断恢革拷锟斤拷*///谁锟斤拷锟斤拷选谁
       if(str->L_StartLine<str->R_StartLine)
       {
         L_recover_row=str->L_StartLine;

       }
       else
       {
         R_recover_row=str->R_StartLine;
       }


       /*锟斤拷锟斤拷指锟斤拷锟斤拷锟斤拷锟缴拷卸锟斤拷欠锟轿拷锟斤拷诺锟�*/
       if(L_recover_row && str->LeftEdge[L_recover_row] && str->RightEdge[L_recover_row])
       {
         int temp_count=0;//锟斤拷锟斤拷
         for(i=L_recover_row;i>ROW_START && i>L_recover_row-7;i--)
         {
           if(str->LeftEdge[i] && str->RightEdge[i])//锟斤拷锟竭讹拷锟叫边斤拷锟斤拷锟斤拷锟�1
           {
            temp_count++;
           }
         }
         if(temp_count>4)//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟叫讹拷为锟街革拷锟斤拷,锟斤拷时锟接该点开始扫锟斤拷
         {
           ExtractCenterline_L();
         }
         else
         {
           ExtractCenterline_1();
         }
       }

       /*锟斤拷锟揭恢革拷锟斤拷锟斤拷锟斤拷扫锟叫讹拷锟角凤拷为锟斤拷锟脚碉拷*/
       else if(R_recover_row && str->LeftEdge[R_recover_row] && str->RightEdge[R_recover_row])
       {
         int temp_count=0;//锟斤拷锟斤拷
         for(i=R_recover_row;i>ROW_START && i>R_recover_row-7;i--)
         {
           if(str->LeftEdge[i] && str->RightEdge[i])//锟斤拷锟竭讹拷锟叫边斤拷锟斤拷锟斤拷锟�1
           {
             temp_count++;
           }
         }
         if(temp_count>4)//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟叫讹拷为锟街革拷锟斤拷,锟斤拷时锟接该点开始扫锟斤拷
         {
           ExtractCenterline_R();
         }
         else
         {
           ExtractCenterline_1();
         }
       }


       else
       {
         ExtractCenterline_1();
       }

       int aaaa=0;;
       int kkkk=0;

       for(i=ROW_END;i>str->EndLine;i--)  //锟斤拷锟斤拷锟斤拷锟斤拷
       {
          aaaa+=str->MiddleLine[i]-str->MiddleLine[i+1];

       }
       aaaa=aaaa>>2;//锟洁当锟节筹拷4
       if(aaaa>=-5&&aaaa<=5)
       {
          kkkk=0;
       }
       else if(aaaa<-5)
       {
          kkkk=-1 ;
       }
       else if(aaaa>5)
       {
          kkkk=1;
       }


       for(i=str->EndLine;i>=ROW_START;i--)
       {
          str->MiddleLine[i]=str->MiddleLine[i+1]+kkkk;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
              {
                  Boundary.MiddleLine[i]=(COL_END+1)-2;
              }

       }
     //*(Boundary.EndLine/20+0.9);    //锟斤拷锟斤拷偏锟斤拷



       return  0;
}

int Middle_Row;
void error_get(void)
{
	      float sum2;
          float cha_mid;
          cha_mid=0;
          if(RoundProcess>=Find_Round)
          {
              Middle_Row=20;//20
          }
          else if(RoadType==Barrier)
          {
              Middle_Row=15;
          }
          else
          {
              Middle_Row=13;
          }
          for(int i=Middle_Row;i<Middle_Row+3;i++)//????
          {
              cha_mid+=(COL_END+1)/2-Boundary.MiddleLine[i] ;  //?????????
          }
          position=cha_mid/3;//???????




}
