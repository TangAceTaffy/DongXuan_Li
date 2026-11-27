#include <stdio.h>
#include <stdint.h>
#include "zf_common_headfile.h"

/*----------------------------------------------------------------------------------------------------------------
*  @brief   差比和函数
*  @param
*
*
*
*  @return
*  @since
*  Sample usage:
//--------------------------------------------------------------------------------------------------------------*/
int difference_sum(unsigned char a,unsigned char b )
{
 if(a+b==0)
 {
   return 0;
 }
  return (a-b)*300/(a+b);
}
/*----------------------------------------------------------------------------------------------------------------
*  @brief   和函数
*  @param
*
*
*
*  @return
*  @since
*  Sample usage:
//--------------------------------------------------------------------------------------------------------------*/

int sum(unsigned char a,unsigned char b)
{
    return a+b;
}



/*----------------------------------------------------------------------------------------------------------------
*  @brief   阈值比较函数
*  @param
*
*
*
*  @return
*  @since
*  Sample usage:
//--------------------------------------------------------------------------------------------------------------*/
int mark_middle_num(int num1,int num2,int middle)
{
  if(num1<=num2 && num1<=middle && num2>=middle)
  {
    return 1;
  }
  else if(num2<num1 && num1>middle && num2<middle)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void int8_range_protect(unsigned char data[],uint8_t start,uint8_t end)
{
    uint8_t i;
    for(i=0;i<39;i++)
    {
        if(data[i]<start)
        {
            data[i]=start;
        }
        if(data[i]>end)
        {
             data[i]=end;
         }

    }
}

/******************************************************************************
 *
//最小二乘法拟合斜率
******************************************************************************/

/******************************************************************************
 *
//曲线拟合   CommonRectificate(&P_LeftBlack[0],startPos-1,endPos+1);
******************************************************************************/
void CommonRectificate(unsigned char data[],unsigned char begin,unsigned char end)
{
       unsigned char MidPos = 0;
       if (end > 80-1)
       {
          end = 80-1;
       }
       if (begin == end)
       {
          data[begin] = (data[begin-1]+data[begin+1])>>1;
         // BlackLineData[begin] =  LeftBlack[begin] + (RightBlack[begin]-LeftBlack[begin])/2;
       }
       else if(begin < end)
       {
          MidPos = (begin+end)>>1;
          data[MidPos] = (data[begin]+data[end])>>1;
          //BlackLineData[MidPos] =  LeftBlack[MidPos] + (RightBlack[MidPos]-LeftBlack[MidPos])/2;
          if (begin+1 < MidPos)
          {
             CommonRectificate(data,begin,MidPos);
          }
          if (MidPos+1 < end)
          {
             CommonRectificate(data,MidPos,end);
          }
       }
}
/*----------------------------------------------------------------------------------------------------------------
 *  @brief
 *  @param
 *
 *
 *
 *  @return
 *  @since
 *  Sample usage:
 //--------------------------------------------------------------------------------------------------------------*/
int32_t int_range_protect( int32_t  duty, int32_t  min, int32_t  max ) //限幅保护
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
//-------------------------------------------------------------------------//
/******** 限幅保护 *********/
float float_range_protect( float duty, float min, float max ) //限幅保护
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
//-------------------------------------------------------------------------//
/******** 限幅保护 *********/
int ABS(int a)
{
  if(a<0)
  {
      return -a;

  }
  else
   {
      return a;
   }

}

float Float_ABS(float a)
{
   if(a<0)
   {
       return -a;

   }
   else
    {
       return a;
    }
}
int32_t limit_max(int32_t a,int32_t b){//最大值限幅
   if(a>b)return b;
   else return a;
}
int32_t limit_min(int32_t a,int32_t b){//最小值限幅
   if(a<b)return b;
   else return a;
}