/*
 * Fuzzy.c
 *
 *  Created on: 2022年5月6日
 *      Author: dell
 */

#include "zf_common_headfile.h"
#define H_Min   2





MH      MHstruct;
MH      MHstructFastCar = {
//	        {1.8 ,2.0,2.2,2.6,3.2,3.8,4.3 } ,//舵机P值表R
//        {1.8 2.0,2.2,2.6,3.2,3.8,4.3 } ,//舵机P值表L
        {1.8 ,2.0,2.2,2.4,3.0,3.2,3.6 },//舵机P值表R{1.8 ,2.0,2.2,2.4,3.0,3.2,3.6 }
        {1.8 ,2.0,2.2,2.4,3.0,3.2,3.6 } ,//舵机P值表L{1.8 ,2.0,2.2,2.4,3.0,3.2,3.6 }
        //{1.8 ,2.0,2.2,2.4,2.8,3.2,3.4 }
        //{1.8 ,2.0,2.2,2.4,2.8,3.2,3.4 }
//        {0.8 ,1.0,1.2,2.2,2.8,3.3,3.R5 } ,//舵机P值表R
//        {0.8 ,1.0,1.2,2.2,2.8,3.3,3.5 } ,//舵机P值表L

  //模糊表|-*-纵轴：反向可视距离递增-*-|-*-横轴：中值偏差变化递增-*-|
   {
    {
      {//L-IN
              { 0, 1, 2, 3, },
              { 1, 2, 3, 4, },
              { 3, 4, 5, 6, },
              { 5, 6, 6, 6, }
      }
    },

    {
      {//R-IN
              { 0, 1, 2, 3, },
              { 1, 2, 3, 4, },
              { 3, 4, 5, 6, },
              { 5, 6, 6, 6, }
      }
    },

    {
      {//L-OUT
              { 0, 1, 2, 3, },
              { 1, 2, 3, 4, },
              { 3, 4, 5, 6, },
              { 5, 6, 6, 6, }
      }
    },

    {
      {//R-OUT
              { 0, 1, 2, 3, },
              { 1, 2, 3, 4, },
              { 3, 4, 5, 6, },
              { 5, 6, 6, 6, }
      }
    }
   },

  //电机P值表
  { 2.0, 2.3 ,2.6, 3.0, 3.3, 3.8, 4.3 },
  //电机I值表
  { 10, 16.625, 21.25, 32.5, 55, 77.5, 100 },
  //{ 10, 16.625, 21.25, 32.5, 55, 77.5, 100 }{ 50, 59.375, 68.75, 87.5, 125, 162.5, 200 },

  //电机模糊表
  //模糊表|-*-纵轴：反向可视距离递增-*-|-*-横轴：脉冲偏差变化递增-*-|
  {
    {
      {//ADD-IN
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }
    },

    {
      {//SUB-IN
        { 0, 1, 2, 4, },
        { 1, 3, 5, 6, },
        { 3, 5, 6, 6, },
        { 5, 6, 6, 6, }
      }
    },

    {
      {//ADD-OUT
        { 0, 1, 2, 4, },
        { 1, 3, 5, 6, },
        { 3, 5, 6, 6, },
        { 5, 6, 6, 6, }
      }
    },

    {
      {//SUB-OUT
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }
    },
  }
};

/************************************************************************
函数名：模糊表初始化
************************************************************************/
void InitMH(void) {
  MHstruct = MHstructFastCar;
  MHstruct.f_SizeOfViewE = 35; //有效偏差
  MHstruct.f_SizeOfViewH = 28; //有效可视距离
}

//从国科的代码中移植过来的
/************************************************************************
函数名：获取舵机P值
功能：通过反向可视距离和中值偏差得出不同P值
参数：i32p_P------舵机P指针
      i16_ViewH---Offline
      i16_ViewE---中值偏差
************************************************************************/
void DuoJi_GetP(float *i32p_P, int16 i16_ViewH, int16 i16_ViewE)
{
  MHstruct.i16_ViewH = i16_ViewH;

  float VH = f_Get_H_approximation(i16_ViewH - H_Min);
  float VE = f_Get_E_approximation(i16_ViewE, MHstruct.f_SizeOfViewE);
  float X2Y = 0;
  float X1Y = 0;
  float Y2X = 0;
  float Y1X = 0;

  int8 VH1 = (int)VH;
  if (VH1 > VH) {
    VH--;
  }
  int8 VH2 = VH1 + 1;

  int8 VE1 = (int)VE;
  if (VE1 > VE) {
    VE1--;
  }
  int8 VE2 = VE1 + 1;

  if (VH1 > 3) {
    VH1 = 3;
  }

  if (VH2 > 3) {
    VH2 = 3;
  }

  if (VE1 > 3) {
    VE1 = 3;
  }

  if (VE2 > 3) {
    VE2 = 3;
  }

  X2Y = (MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE2] -
         MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE1]) *
            (VE - VE1) +
        MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE1];

  X1Y = (MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH2][VE2] -
         MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH2][VE1]) *
            (VE - VE1) +
        MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH2][VE1];

  Y2X = (MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH2][VE1] -
         MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE1]) *
            (VH - VH1) +
        MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE1];

  Y1X = (MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH2][VE2] -
         MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE2]) *
            (VH - VH1) +
        MHstruct.mt_Duoji[MHstruct.ui8_IOLR].ui8_Table[VH1][VE2];

  float P_approximation = (X2Y + X1Y + Y2X + Y1X) / 4.0;

  int8 P1 = (int)P_approximation;
  if (P1 > P_approximation) {
    P1--;
  }
  int8 P2 = P1 + 1;
    //当前值小于舵机中值→右偏应该向左打
    if (i16_ViewE < 0) {

  *i32p_P = (MHstruct.f_DuoJiP_TableL[P2] - MHstruct.f_DuoJiP_TableL[P1])*(P_approximation - P1) +MHstruct.f_DuoJiP_TableL[P1];
    }
    else
    {
  *i32p_P = (MHstruct.f_DuoJiP_TableR[P2] - MHstruct.f_DuoJiP_TableR[P1])*(P_approximation - P1) + MHstruct.f_DuoJiP_TableR[P1];
    }

}

/************************************************************************
函数名：获取横轴似坐标
功能：获取get_p()函数所需变量
接口：无
调用：通过get_p()被动调用
************************************************************************/
float f_Get_H_approximation(short i16_ViewH) {
  float H_approximation;

  if (i16_ViewH < 0) {
    i16_ViewH = 0;
  }

  H_approximation = i16_ViewH * 3 / MHstruct.f_SizeOfViewH;

  return H_approximation;
}

/************************************************************************
函数名：获取纵轴近似坐标
功能：获取get_p()函数所需变量
接口：无
调用：通过get_p()被动调用
************************************************************************/
float f_Get_E_approximation(short i16_E, float f_E_Size) {
  float E_approximation;

  if (i16_E < 0) {
    i16_E = -i16_E;
  }

  E_approximation = i16_E * 3 / f_E_Size;

  return E_approximation;
}


//定义误差的语言值
#define ENB -45//最小值
#define ENM -30
#define ENS -15
#define EZO 0
#define EPS 15
#define EPM 30
#define EPB 45 //最大值

//定义误差的变化量的语言值
#define ECNB -30
#define ECNM -20
#define ECNS -10
#define ECZO 0
#define ECPS 10
#define ECPM 20
#define ECPB 30

//定义P的语言值
#define PNB 6    //8
#define PNM 3   //6
#define PNS 1  //2.5
#define PZO 0
#define PPS 1
#define PPM 3
#define PPB 6

//定义I的语言值
#define INB 1
#define INM 1
#define INS 1
#define IZO 1
#define IPS 1
#define IPM 1
#define IPB 1

//定义D的语言值
#define DNB 1
#define DNM 1
#define DNS 1
#define DZO 1
#define DPS 1
#define DPM 1
#define DPB 1


int fuzzy_e[7]={ENB,ENM,ENS,EZO,EPS,EPM,EPB};  //误差的模糊规则表
int fuzzy_ec[7]={ECNB,ECNM,ECNS,ECZO,ECPS,ECPM,ECPB};  //误差变化量的模糊规则表

float fuzzy_p[7][7]={                                   //p的模糊规则表
                 {PPB,PPB,PPB,PPB,PPM,PZO,PZO},
                 {PPB,PPB,PPB,PPM,PPM,PZO,PZO},
                 {PPB,PPM,PPM,PPS,PZO,PNS,PNM},
                 {PPM,PPM,PPS,PZO,PNS,PNM,PNM},
                 {PPM,PPS,PZO,PNS,PNM,PNM,PNB},
                 {PZO,PZO,PNM,PNM,PNB,PNB,PNB},
                 {PZO,PZO,PNM,PNB,PNB,PNB,PNB}
};

float fuzzy_i[7][7]={                                   //p的模糊规则表
                 {IPB,IPB,IPB,IPB,IPM,IZO,IZO},
                 {IPB,IPB,IPB,IPM,IPM,IZO,IZO},
                 {IPB,IPM,IPM,IPS,IZO,INS,INM},
                 {IPM,IPM,IPS,IZO,INS,INM,INM},
                 {IPM,IPS,IZO,INS,INM,INM,INB},
                 {IZO,IZO,INM,INM,INB,INB,INB},
                 {IZO,IZO,INM,INB,INB,INB,INB}
};

float fuzzy_d[7][7]={                                   //p的模糊规则表
                 {DPB,DPB,DPB,DPB,DPM,DZO,DZO},
                 {DPB,DPB,DPB,DPM,DPM,DZO,DZO},
                 {DPB,DPM,DPM,DPS,DZO,DNS,DNM},
                 {DPM,DPM,DPS,DZO,DNS,DNM,DNM},
                 {DPM,DPS,DZO,DNS,DNM,DNM,DNB},
                 {DZO,DZO,DNM,DNM,DNB,DNB,DNB},
                 {DZO,DZO,DNM,DNB,DNB,DNB,DNB}
};

float fuzz_err[7]={0};  //储存误差对应的隶属度(小于1)
float fuzz_errc[7]={0}; //储存误差变化量对应的隶属度（小于1）
int ERR,ERRC;           //用来在解模糊时确立在规则表中的位置

float FUZZY_P(int err,int errc)  //形参为两电感的差 ,电感差的变化量
{
    float P;
    //求误差对应的隶属度
    if(err>EPB || err<ENB)
    {
        P = DNB;
        return P;
    }
    else if(err>=ENB&&err<=ENM)
    {
        fuzz_err[0]=1.00*(err-ENM)/(ENB-ENM);fuzz_err[1]=1.00*(ENB-err)/(ENB-ENM);ERR=0;
    }
    else if(err>=ENM&&err<=ENS)
    {
        fuzz_err[1]=1.00*(err-ENS)/(ENM-ENS);fuzz_err[2]=1.00*(ENM-err)/(ENM-ENS);ERR=1;
    }
    else if(err>=ENS&&err<=EZO)
    {
        fuzz_err[2]=1.00*(err-EZO)/(ENS-EZO);fuzz_err[3]=1.00*(ENS-err)/(ENS-EZO);ERR=2;
    }
    else if(err>=EZO&&err<=EPS)
    {
        fuzz_err[3]=1.00*(err-EPS)/(EZO-EPS);fuzz_err[4]=1.00*(EZO-err)/(EZO-EPS);ERR=3;
    }
    else if(err>=EPS&&err<=EPM)
    {
        fuzz_err[4]=1.00*(err-EPM)/(EPS-EPM);fuzz_err[5]=1.00*(EPS-err)/(EPS-EPM);ERR=4;
    }
    else if(err>=EPM&&err<=EPB)
    {
        fuzz_err[5]=1.00*(err-EPB)/(EPM-EPB);fuzz_err[6]=1.00*(EPM-err)/(EPM-EPB);ERR=5;
    }

    //求误差变化量对应的隶属度
    if(errc>=ECNB&&errc<=ECNM)
    {
        fuzz_errc[0]=1.00*(errc-ECNM)/(ECNB-ECNM);fuzz_errc[1]=1.00*(ECNB-errc)/(ECNB-ECNM);ERRC=0;
    }
    else if(errc>=ECNM&&errc<=ECNS)
    {
        fuzz_errc[1]=1.00*(errc-ECNS)/(ECNM-ECNS);fuzz_errc[2]=1.00*(ECNM-errc)/(ECNM-ECNS);ERRC=1;
    }
    else if(errc>=ECNS&&errc<=ECZO)
    {
        fuzz_errc[2]=1.00*(errc-ECZO)/(ECNS-ECZO);fuzz_errc[3]=1.00*(ECNS-errc)/(ECNS-ECZO);ERRC=2;
    }
    else if(errc>=ECZO&&errc<=ECPS)
    {
        fuzz_errc[3]=1.00*(errc-ECPS)/(ECZO-ECPS);fuzz_errc[4]=1.00*(ECZO-errc)/(ECZO-ECPS);ERRC=3;
    }
    else if(errc>=ECPS&&errc<=ECPM)
    {
        fuzz_errc[4]=1.00*(errc-ECPM)/(ECPS-ECPM);fuzz_errc[5]=1.00*(ECPS-errc)/(ECPS-ECPM);ERRC=4;
    }
    else if(errc>=ECPM&&errc<=ECPB)
    {
        fuzz_errc[5]=1.00*(errc-ECPB)/(ECPM-ECPB);fuzz_errc[6]=1.00*(ECPM-errc)/(ECPM-ECPB);ERRC=5;
    }

    //解模糊
    P = fuzzy_p[ERR][ERRC]*fuzz_err[ERR]*fuzz_errc[ERRC]
       +fuzzy_p[ERR][ERRC+1]*fuzz_err[ERR]*fuzz_errc[ERRC+1]
       +fuzzy_p[ERR+1][ERRC]*fuzz_err[ERR+1]*fuzz_errc[ERRC]
       +fuzzy_p[ERR+1][ERRC+1]*fuzz_err[ERR+1]*fuzz_errc[ERRC+1];
    return  P;
}
float FUZZY_I(int err,int errc)  //形参为两电感的差 ,电感差的变化量
{
    float I;
    //求误差对应的隶属度
    if(err>EPB || err<ENB)
    {
        I = INB;
        return I;
    }
    else if(err>=ENB&&err<=ENM)
    {
        fuzz_err[0]=1.00*(err-ENM)/(ENB-ENM);fuzz_err[1]=1.00*(ENB-err)/(ENB-ENM);ERR=0;
    }
    else if(err>=ENM&&err<=ENS)
    {
        fuzz_err[1]=1.00*(err-ENS)/(ENM-ENS);fuzz_err[2]=1.00*(ENM-err)/(ENM-ENS);ERR=1;
    }
    else if(err>=ENS&&err<=EZO)
    {
        fuzz_err[2]=1.00*(err-EZO)/(ENS-EZO);fuzz_err[3]=1.00*(ENS-err)/(ENS-EZO);ERR=2;
    }
    else if(err>=EZO&&err<=EPS)
    {
        fuzz_err[3]=1.00*(err-EPS)/(EZO-EPS);fuzz_err[4]=1.00*(EZO-err)/(EZO-EPS);ERR=3;
    }
    else if(err>=EPS&&err<=EPM)
    {
        fuzz_err[4]=1.00*(err-EPM)/(EPS-EPM);fuzz_err[5]=1.00*(EPS-err)/(EPS-EPM);ERR=4;
    }
    else if(err>=EPM&&err<=EPB)
    {
        fuzz_err[5]=1.00*(err-EPB)/(EPM-EPB);fuzz_err[6]=1.00*(EPM-err)/(EPM-EPB);ERR=5;
    }

    //求误差变化量对应的隶属度
    if(errc>=ECNB&&errc<=ECNM)
    {
        fuzz_errc[0]=1.00*(errc-ECNM)/(ECNB-ECNM);fuzz_errc[1]=1.00*(ECNB-errc)/(ECNB-ECNM);ERRC=0;
    }
    else if(errc>=ECNM&&errc<=ECNS)
    {
        fuzz_errc[1]=1.00*(errc-ECNS)/(ECNM-ECNS);fuzz_errc[2]=1.00*(ECNM-errc)/(ECNM-ECNS);ERRC=1;
    }
    else if(errc>=ECNS&&errc<=ECZO)
    {
        fuzz_errc[2]=1.00*(errc-ECZO)/(ECNS-ECZO);fuzz_errc[3]=1.00*(ECNS-errc)/(ECNS-ECZO);ERRC=2;
    }
    else if(errc>=ECZO&&errc<=ECPS)
    {
        fuzz_errc[3]=1.00*(errc-ECPS)/(ECZO-ECPS);fuzz_errc[4]=1.00*(ECZO-errc)/(ECZO-ECPS);ERRC=3;
    }
    else if(errc>=ECPS&&errc<=ECPM)
    {
        fuzz_errc[4]=1.00*(errc-ECPM)/(ECPS-ECPM);fuzz_errc[5]=1.00*(ECPS-errc)/(ECPS-ECPM);ERRC=4;
    }
    else if(errc>=ECPM&&errc<=ECPB)
    {
        fuzz_errc[5]=1.00*(errc-ECPB)/(ECPM-ECPB);fuzz_errc[6]=1.00*(ECPM-errc)/(ECPM-ECPB);ERRC=5;
    }

    //解模糊
    I = fuzzy_i[ERR][ERRC]*fuzz_err[ERR]*fuzz_errc[ERRC]
       +fuzzy_i[ERR][ERRC+1]*fuzz_err[ERR]*fuzz_errc[ERRC+1]
       +fuzzy_i[ERR+1][ERRC]*fuzz_err[ERR+1]*fuzz_errc[ERRC]
       +fuzzy_i[ERR+1][ERRC+1]*fuzz_err[ERR+1]*fuzz_errc[ERRC+1];
    return  I;
}
float FUZZY_D(int err,int errc)  //形参为两电感的差 ,电感差的变化量
{
    float D;
    //求误差对应的隶属度
    if(err>EPB || err<ENB)
    {
        D = DNB;
        return D;
    }
    else if(err>=ENB&&err<=ENM)
    {
        fuzz_err[0]=1.00*(err-ENM)/(ENB-ENM);fuzz_err[1]=1.00*(ENB-err)/(ENB-ENM);ERR=0;
    }
    else if(err>=ENM&&err<=ENS)
    {
        fuzz_err[1]=1.00*(err-ENS)/(ENM-ENS);fuzz_err[2]=1.00*(ENM-err)/(ENM-ENS);ERR=1;
    }
    else if(err>=ENS&&err<=EZO)
    {
        fuzz_err[2]=1.00*(err-EZO)/(ENS-EZO);fuzz_err[3]=1.00*(ENS-err)/(ENS-EZO);ERR=2;
    }
    else if(err>=EZO&&err<=EPS)
    {
        fuzz_err[3]=1.00*(err-EPS)/(EZO-EPS);fuzz_err[4]=1.00*(EZO-err)/(EZO-EPS);ERR=3;
    }
    else if(err>=EPS&&err<=EPM)
    {
        fuzz_err[4]=1.00*(err-EPM)/(EPS-EPM);fuzz_err[5]=1.00*(EPS-err)/(EPS-EPM);ERR=4;
    }
    else if(err>=EPM&&err<=EPB)
    {
        fuzz_err[5]=1.00*(err-EPB)/(EPM-EPB);fuzz_err[6]=1.00*(EPM-err)/(EPM-EPB);ERR=5;
    }

    //求误差变化量对应的隶属度
    if(errc>=ECNB&&errc<=ECNM)
    {
        fuzz_errc[0]=1.00*(errc-ECNM)/(ECNB-ECNM);fuzz_errc[1]=1.00*(ECNB-errc)/(ECNB-ECNM);ERRC=0;
    }
    else if(errc>=ECNM&&errc<=ECNS)
    {
        fuzz_errc[1]=1.00*(errc-ECNS)/(ECNM-ECNS);fuzz_errc[2]=1.00*(ECNM-errc)/(ECNM-ECNS);ERRC=1;
    }
    else if(errc>=ECNS&&errc<=ECZO)
    {
        fuzz_errc[2]=1.00*(errc-ECZO)/(ECNS-ECZO);fuzz_errc[3]=1.00*(ECNS-errc)/(ECNS-ECZO);ERRC=2;
    }
    else if(errc>=ECZO&&errc<=ECPS)
    {
        fuzz_errc[3]=1.00*(errc-ECPS)/(ECZO-ECPS);fuzz_errc[4]=1.00*(ECZO-errc)/(ECZO-ECPS);ERRC=3;
    }
    else if(errc>=ECPS&&errc<=ECPM)
    {
        fuzz_errc[4]=1.00*(errc-ECPM)/(ECPS-ECPM);fuzz_errc[5]=1.00*(ECPS-errc)/(ECPS-ECPM);ERRC=4;
    }
    else if(errc>=ECPM&&errc<=ECPB)
    {
        fuzz_errc[5]=1.00*(errc-ECPB)/(ECPM-ECPB);fuzz_errc[6]=1.00*(ECPM-errc)/(ECPM-ECPB);ERRC=5;
    }

    //解模糊
    D = fuzzy_d[ERR][ERRC]*fuzz_err[ERR]*fuzz_errc[ERRC]
       +fuzzy_d[ERR][ERRC+1]*fuzz_err[ERR]*fuzz_errc[ERRC+1]
       +fuzzy_d[ERR+1][ERRC]*fuzz_err[ERR+1]*fuzz_errc[ERRC]
       +fuzzy_d[ERR+1][ERRC+1]*fuzz_err[ERR+1]*fuzz_errc[ERRC+1];
    return  D;
}
