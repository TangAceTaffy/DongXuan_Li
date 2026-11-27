/*
 * midline_process.c
 *
 *  Created on: 2022
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
int16  position;
int L_recover_row=0;//左恢复行
int R_recover_row=0;//右恢复行
int ExtractCenterline_1()
{
    //tft180_show_int32(60,100,1,6);//陀螺仪
  if(Boundary.LeftEdge[ROW_END]!=0 && Boundary.RightEdge[ROW_END]!=0)     //左右都有边界
  {
    Boundary.MiddleLine[ROW_END] =(Boundary.LeftEdge[ROW_END] +Boundary.RightEdge[ROW_END])/2;//左加右除以2

  }
  else if(Boundary.LeftEdge[ROW_END]!=0 && Boundary.RightEdge[ROW_END]==0)//find left
  {
    Boundary.RightEdge[ROW_END]=COL_END;//右定义最右边
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//左加右除以2

  }
  else if( Boundary.LeftEdge[ROW_END]==0 && Boundary.RightEdge[ROW_END]!=0)//find right
  {
    Boundary.LeftEdge[ROW_END]=0;//左定义0
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//左加右除以2

  }
  else if( Boundary.LeftEdge[ROW_END]==0 &&Boundary.RightEdge[ROW_END]==0)//两边丢线   d待处理
  {
    Boundary.LeftEdge[ROW_END]=0;
    Boundary.RightEdge[ROW_END]=COL_END;
    Boundary.MiddleLine[ROW_END]=(Boundary.LeftEdge[ROW_END] + Boundary.RightEdge[ROW_END])/2;//取屏幕正中间
  }

  //// 从第二行开始搜索

  for(int i=ROW_END-1;i>=ROW_START;i--)
  {
   if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //左右都有边界
    {
          Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])/2;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
        if(Boundary.LeftEdge[i+1]!=0) //拟合中线
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

         if(Boundary.RightEdge[i+1]!=0) //拟合中线
           {
            // Boundary.MiddleLine[i]=Boundary.RightEdge[i] + Boundary.MiddleLine[i+1]-Boundary.RightEdge[i+1];
             int temp_r1=Boundary.RightEdge[i+1];//临时有符号变量防止中线溢出
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
    else if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//两边丢线   d待处理
   {

            Boundary.MiddleLine[i]=Boundary.MiddleLine[i+1];

    }
  }
  return  0;
}

/*得出左边恢复行下面的中线，主要靠右边向左边补线*/
void ExtractCenterline_L()
{
    //tft180_show_int32(60,100,2,6);//陀螺仪
  /* 定义恢复行的 实际赛道宽度与直道赛道宽度的比值 */
  float temp=(float)(Boundary.RightEdge[L_recover_row]-Boundary.LeftEdge[L_recover_row])/(float)Boundary.track_Width[L_recover_row];

  /* 得出左边恢复行下面的中线，主要靠右边向左边补线 */
  for(int i=L_recover_row;i<=ROW_END;i++)
  {
    if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//两边丢线   d待处理
    {
          Boundary.MiddleLine[i]=Boundary.MiddleLine[i-1] ;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]!=0)//左边丢线   用右边补
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
    else if(Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]!=0)//左右都有取中值
    {
          Boundary.MiddleLine[i] =(Boundary.LeftEdge[i] + Boundary.RightEdge[i])>>1;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
  }
  /*出左边恢复行上面的中线*/
  for(int i=L_recover_row;i>=ROW_START;i--)
  {
    if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //左右都有边界
    {
          Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])>>1;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
          if(Boundary.LeftEdge[i+1]!=0) //拟合中线
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
        //tft180_show_int32(60,60,2,6);//陀螺仪

          if(Boundary.RightEdge[i+1]!=0) //拟合中线
          {
              int temp_r1=Boundary.RightEdge[i+1];//临时有符号变量防止中线溢出
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
    else if( Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]==0)//两边丢线   d待处理
    {
        //tft180_show_int32(60,60,3,6);//陀螺仪
          Boundary.MiddleLine[i]=Boundary.MiddleLine[i+1] ;
          if(Boundary.MiddleLine[i]>(COL_END+1)-2)
          {
              Boundary.MiddleLine[i]=(COL_END+1)-2;
          }

    }
  }

}
/*得出右边恢复行下面的中线，主要靠左边向右边补线*/
void ExtractCenterline_R()
{
    //tft180_show_int32(60,100,3,6);//陀螺仪
  /* 定义恢复行的 实际赛道宽度与直道赛道宽度的比值 */
  float temp=(float)(Boundary.RightEdge[R_recover_row]-Boundary.LeftEdge[R_recover_row])/(float)Boundary.track_Width[R_recover_row];

  for(int i=R_recover_row;i<=ROW_END;i++)
  {
    if( Boundary.LeftEdge[i]==0&&Boundary.RightEdge[i]==0)//两边丢线   d待处理
    {

            Boundary.MiddleLine[i]=Boundary.MiddleLine[i-1] ;

      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if( Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]==0)//丢右
    {
      Boundary.MiddleLine[i]  = Boundary.LeftEdge[i]+(int)((float)Boundary.track_Width[i]*temp)/2;
      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if(Boundary.LeftEdge[i]!=0&&Boundary.RightEdge[i]!=0)//都不丢
    {
       Boundary.MiddleLine[i] =(Boundary.LeftEdge[i] + Boundary.RightEdge[i])>>1;
       if(Boundary.MiddleLine[i]>(COL_END+1)-2)
       {
           Boundary.MiddleLine[i]=(COL_END+1)-2;
       }
    }
  }
   /*得出右边恢复行上面的中线*/
  for(int i=R_recover_row;i>=ROW_START;i--)
  {
    if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]!=0)     //左右都有边界
    {
      Boundary.MiddleLine[i]=(Boundary.LeftEdge[i]+Boundary.RightEdge[i])>>1;
      if(Boundary.MiddleLine[i]>(COL_END+1)-2)
      {
          Boundary.MiddleLine[i]=(COL_END+1)-2;
      }

    }
    else if(Boundary.LeftEdge[i]!=0 && Boundary.RightEdge[i]==0)//find left
    {
      if(Boundary.LeftEdge[i+1]!=0) //拟合中线
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

      if(Boundary.RightEdge[i+1]!=0) //拟合中线
      {
          int temp_r1=Boundary.RightEdge[i+1];//临时有符号变量防止中线溢出
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
    else if( Boundary.LeftEdge[i]==0 && Boundary.RightEdge[i]==0)//两边丢线   d待处理
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
    //tft180_show_int32(60,100,3,6);//陀螺仪
       uint8 i;
       L_recover_row=0;//左恢复行
       R_recover_row=0;//右恢复行


       /*计算路宽*/
       for(i=ROW_END;i>0 ;i--)
       {
          str->track_Width[i]=(int)(i*Width_P+24.6); //计算  路宽
       }


       /*通过判断左右起始行来判断恢复行*///谁靠上选谁
       if(str->L_StartLine<str->R_StartLine)
       {
         L_recover_row=str->L_StartLine;

       }
       else
       {
         R_recover_row=str->R_StartLine;
       }


       /*从左恢复行向上扫判断是否为干扰点*/
       if(L_recover_row && str->LeftEdge[L_recover_row] && str->RightEdge[L_recover_row])
       {
         int temp_count=0;//计数
         for(i=L_recover_row;i>ROW_START && i>L_recover_row-7;i--)
         {
           if(str->LeftEdge[i] && str->RightEdge[i])//两边都有边界计数加1
           {
            temp_count++;
           }
         }
         if(temp_count>4)//上面有三个边界判定为恢复点,此时从该点开始扫线
         {
           ExtractCenterline_L();
         }
         else
         {
           ExtractCenterline_1();
         }
       }

       /*从右恢复行向上扫判断是否为干扰点*/
       else if(R_recover_row && str->LeftEdge[R_recover_row] && str->RightEdge[R_recover_row])
       {
         int temp_count=0;//计数
         for(i=R_recover_row;i>ROW_START && i>R_recover_row-7;i--)
         {
           if(str->LeftEdge[i] && str->RightEdge[i])//两边都有边界计数加1
           {
             temp_count++;
           }
         }
         if(temp_count>4)//上面有三个边界判定为恢复点,此时从该点开始扫线
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

       for(i=ROW_END;i>str->EndLine;i--)  //顶端延伸
       {
          aaaa+=str->MiddleLine[i]-str->MiddleLine[i+1];

       }
       aaaa=aaaa>>2;//相当于除4
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
     //*(Boundary.EndLine/20+0.9);    //计算偏差



       return  0;
}
int Middle_Row;
int ElseRoad_Middle_Row=22;//20
int Round_Middle_Row=20;//30
int Barrier_Middle_Row=20;
void error_get(void)
{
	      float sum2;
          float cha_mid;
          cha_mid=0;
          if(RoundProcess>=Find_Round)//处理圆环时的前瞻
          {
              Middle_Row=Round_Middle_Row;//20
          }
          else if(RoadType==Barrier)//处理障碍的时候的前瞻
          {
              Middle_Row=Barrier_Middle_Row;
          }
          else//除特殊处理之外的前瞻
          {
              Middle_Row=ElseRoad_Middle_Row;
          }
          for(int i=Middle_Row;i<Middle_Row+3;i++)//取了三行的误差
          {
              cha_mid+=(COL_END+1)/2-Boundary.MiddleLine[i];//求和
          }
          position=cha_mid/3;//求均值
}
