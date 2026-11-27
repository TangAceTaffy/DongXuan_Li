
#include "zf_common_headfile.h"
#include"math.h"

//604 leftmax
//740
int16 error=0,integral=0,delta=0;  //偏差   上次偏差   积分   微分
int16 Now_duty=0;  //位置式pid输出
int16 angle=0;    //舵机占空比输出

static int16 Last_error = 0;
//static float last_angle_i=0;
float T=0.00006;//0.000055
float output;
float Kp=2.0 ;
float Ki = 0;
float Kd = 2.0;
double K_diff = 0;  //过弯差速比
float output_p = 0;
////舵机初始化
//void servo_init(void)
//{
//    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, 728);       //频率为50hz。占空比为7%
//}
//舵机控制主函数
uint8 left_diff_flag = 0;
uint8 right_diff_flag = 0;
//输入参数E为error，EC为err的微分，即本次error-上次error

float kp_m=1.65;//p和d系数的最大值
float kd_m=0.04;
//直入弯1.55，0.04
//
int rule_d[7] = { 10 , 5 , 3 , 2 , 3 , 5 , 10};// { 6 , 5 , 3 , 2 , 3 , 5 , 6};
float Kd_Fuzzy(float EC)//模糊D
{
    float out=0;
    uint8 i=0;
    float degree_left = 0,degree_right = 0;
    uint8 degree_left_index = 0,degree_right_index = 0;
    float DFF[7]={-36,-24,-12,0,12,24,36};//{-45,-30,-15,0,15,30,45};
    float UFF[7];
 
    for(i=0;i<7;i++)
            UFF[i]=kd_m/6*i;
 
    if(EC<DFF[0])
    {
        degree_left = 1;
        degree_right = 0;
        degree_left_index = 0;
    }
    else if (EC>DFF[6]) {
        degree_left = 1;
        degree_right = 0;
        degree_left_index = 6;
    }
    else {
        for(i=0;i<6;i++)
        {
            if(EC>=DFF[i]&&EC<DFF[i+1])
            {
                degree_left = (float)(DFF[i+1] - EC)/(DFF[i+1] - DFF[i]);
                degree_right = 1 - degree_left;
                degree_left_index = i;
                degree_right_index = i+1;
                break;
            }
        }
    }
 
    out = UFF[rule_d[degree_left_index]]*degree_left+UFF[rule_d[degree_right_index]]*degree_right;
 
    return out;
}
float KP_Fuzzy(float E,float EC)//模糊P
{
    int rule_p[7][7]=
    {
        { 6 , 5 , 4 , 4 , 3 , 0 , 0},//-36
        { 6 , 4 , 3 , 3 , 2 , 0 , 0},//-24
        { 4 , 3 , 2 , 1 , 0 , 1 , 2},//-12
        { 2 , 1 , 1 , 0 , 1 , 1 , 2},//0
        { 2 , 1 , 0 , 1 , 2 , 3 , 4},//12
        { 0 , 0 , 2 , 3 , 3 , 4 , 6},//24
        { 0 , 1 , 3 , 4 , 4 , 5 , 6},//36
    };//模糊规则表 P
    uint8 i2;
    /*输入量P语言特征点*/
    float EFF[7]={-36,-24,-12,0,12,24,36};//{-150,-100,-50,0,50,100,150};
    /*输入量D语言特征点*/
    float DFF[7]={-18,-12,-6,0,6,12,18};//{-45,-30,-15,0,15,30,45};
    /*输入量U语言特征点（根据赛道类型选择不同的输出值）*/
    float UFF[7];
      for(i2=0;i2<7;i2++)
         UFF[i2]=kp_m/6*i2;
		/*对kpm进行比例分段*/
    float U=0; 
    float PF[2]={0},DF[2]={0},UF[4]={0};

    int Pn=0,Dn=0,Un[4]={0};
    float t1=0,t2=0,t3=0,t4=0,temp1=0,temp2=0;

    if(E>EFF[0] && E<EFF[6])
    {
        if(E<=EFF[1])
        {
            Pn=-2;
            PF[0]=(EFF[1]-E)/(EFF[1]-EFF[0]);
        }
        else if(E<=EFF[2])
        {
            Pn=-1;
            PF[0]=(EFF[2]-E)/(EFF[2]-EFF[1]);
        }
        else if(E<=EFF[3])
        {
            Pn=0;
            PF[0]=(EFF[3]-E)/(EFF[3]-EFF[2]);
        }
        else if(E<=EFF[4])
        {
            Pn=1;
            PF[0]=(EFF[4]-E)/(EFF[4]-EFF[3]);
        }
        else if(E<=EFF[5])
        {
            Pn=2;
            PF[0]=(EFF[5]-E)/(EFF[5]-EFF[4]);
        }
        else if(E<=EFF[6])
        {
            Pn=3;
            PF[0]=(EFF[6]-E)/(EFF[6]-EFF[5]);
        }
    }
 
    else if(E<=EFF[0])
    {
        Pn=-2;
        PF[0]=1;
    }
    else if(E>=EFF[6])
    {
        Pn=3;
        PF[0]=0;
    }
 
    PF[1]=1-PF[0];
 
 
    if(EC>DFF[0]&&EC<DFF[6])
    {
        if(EC<=DFF[1])
        {
            Dn=-2;
            DF[0]=(DFF[1]-EC)/(DFF[1]-DFF[0]);
        }
        else if(EC<=DFF[2])
        {
            Dn=-1;
            DF[0]=(DFF[2]-EC)/(DFF[2]-DFF[1]);
        }
        else if(EC<=DFF[3])
        {
            Dn=0;
            DF[0]=(DFF[3]-EC)/(DFF[3]-DFF[2]);
        }
        else if(EC<=DFF[4])
        {
            Dn=1;
            DF[0]=(DFF[4]-EC)/(DFF[4]-DFF[3]);
        }
        else if(EC<=DFF[5])
        {
            Dn=2;
            DF[0]=(DFF[5]-EC)/(DFF[5]-DFF[4]);
        }
        else if(EC<=DFF[6])
        {
            Dn=3;
            DF[0]=(DFF[6]-EC)/(DFF[6]-DFF[5]);
        }
    }
    
    else if (EC<=DFF[0])
    {
        Dn=-2;
        DF[0]=1;
    }
    else if(EC>=DFF[6])
    {
        Dn=3;
        DF[0]=0;
    }
 
    DF[1]=1-DF[0];
 

    Un[0]=rule_p[Pn+2][Dn+2];
    Un[1]=rule_p[Pn+3][Dn+2];
    Un[2]=rule_p[Pn+2][Dn+3];
    Un[3]=rule_p[Pn+3][Dn+3];
 
    if(PF[0]<=DF[0])    
        UF[0]=PF[0];                  
    else
        UF[0]=DF[0];
    if(PF[1]<=DF[0])
        UF[1]=PF[1];
    else
        UF[1]=DF[0];
    if(PF[0]<=DF[1])
        UF[2]=PF[0];
    else
        UF[2]=DF[1];
    if(PF[1]<=DF[1])
        UF[3]=PF[1];
    else
        UF[3]=DF[1];

    if(Un[0]==Un[1])
    {
        if(UF[0]>UF[1])
            UF[1]=0;
        else
            UF[0]=0;
    }
    if(Un[0]==Un[2])
    {
        if(UF[0]>UF[2])
            UF[2]=0;
        else
            UF[0]=0;
    }
    if(Un[0]==Un[3])
    {
        if(UF[0]>UF[3])
            UF[3]=0;
        else
            UF[0]=0;
    }
    if(Un[1]==Un[2])
    {
        if(UF[1]>UF[2])
            UF[2]=0;
        else
            UF[1]=0;
    }
    if(Un[1]==Un[3])
    {
        if(UF[1]>UF[3])
            UF[3]=0;
        else
            UF[1]=0;
    }
    if(Un[2]==Un[3])
    {
        if(UF[2]>UF[3])
            UF[3]=0;
        else
            UF[2]=0;
    }
    t1=UF[0]*UFF[Un[0]];
    t2=UF[1]*UFF[Un[1]];
    t3=UF[2]*UFF[Un[2]];
    t4=UF[3]*UFF[Un[3]];
    temp1=t1+t2+t3+t4;
    temp2=UF[0]+UF[1]+UF[2]+UF[3];
//    if(temp2!=0)
//        U=temp1/temp2;
//    else {
//        U=0;
//    }
    temp1=PF[0]*UFF[Un[0]]+PF[1]*UFF[Un[1]]+PF[0]*UFF[Un[2]]+PF[1]*UFF[Un[3]]+DF[0]*UFF[Un[0]]+DF[0]*UFF[Un[1]]+DF[1]*UFF[Un[2]]+DF[0]*UFF[Un[3]];
    U=temp1;
    return U;
}

void servo_pid()
{
//    if (annulus_status==3 ) //|| annulus_status==4) //正常巡线过程
//    {
       error = position;		
	     
			float E=0,EC=0; 
       E  = position;
       EC = position - Last_error;
//固定pid
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//    if(ElseRoadType==1||Cross_deal.Cross_flag==1)
//	  {
//			kp_m=3.80;//p和d系数的最大值4.10
//            kd_m=2.25;//0.54
//			Kp=1.9;
//			Kd=0.6;//1.2
//	  }
//    else if(Obstacle.Obstacle_flag==1)
//     {
//        kp_m=7.05;//p和d系数的最大值 4.95 7.05
//        kd_m=2.04;//1.94
//        Kp=3;
//        Kd=3;
//     }
//		else
//		{
//			kp_m=4.95;//p和d系数的最大值 4.95  5.05
//            kd_m=2.09;//1.94
//			Kp=2.5;
//			Kd=1.7;
//		}
///////////////////////////////////////////////////////////////////////////////////////////////////////\
//模糊p
///////////////////////////////////////////////////////////////////////////////////////////////////////
//	  kp_m=8;//p和d系数的最大值2.25 2.95
//      kd_m=3.5;
      //Kp = KP_Fuzzy(E,EC);//模糊p查找
     // Kd = Kd_Fuzzy(EC) ;//模糊d查找
			//Kp=5.4;
    if(RoundSize==Large_Round&&RoundProcess<=In_Round&&Round.Round_flag==1)
	  {
        Kp=1.5;
        Kd=10;//0.3
	  }
    else
	  {
		DuoJi_GetP((float*)&Kp, (uint16)(Boundary.EndLine),E);  //国科的经典的模糊控制
//		    Kp=KP_Fuzzy(E,EC);
//		    Kd=Kd_Fuzzy(EC);
        Kd=50;//0.3
	  }
       //Kd=2.46;
			 //Kd=2.56;
			 //Kp=2.6;
			 //Kd=1.46;
//		   DuoJi_GetP((float*)&Kp, (uint16)(Boundary.EndLine),E);  //经典的模糊控制
		   //Kp=FUZZY_P(E,EC);

           output = (Kp*E+Kd*(EC)+1.0*((imu660ra_gyro_z+10.5-gyro_offset_z)*-0.00012480f));//计算输出
           angle = steeringPWM_MID + output;//舵机角度计算   右转弯output为负数
           angle = angle > angle_max ? angle_max:angle;
           angle = angle < angle_min ? angle_min:angle;
           pwm_set_duty(SERVO_MOTOR_PWM, angle);
           Last_error = error;//储存error的微分
			 //last_angle_i=angle_i;
}


#define steering_PWM sevro_ctl

#define LDISTANCE 200 //????????? mm
#define BORDWIDTH 150 //??????     mm
#define A 0.78//1.05 //???????
#define K 1.06//1.06 //???????  K???????
#define AK 1   
float g_Control=0,g_Control_last=0,g_Control_pre=0,casu_weight=0.38;//1.29;//?0.6

extern uint16 sevro_mid;
//extern uint16 sevro_ctl;


float k_white_40col=0;
float casu_weight_base=0.4;
extern uint8 white_num_40col;
extern float  white_num_40col_min;
extern float  white_num_40col_max;
float Get_Dire(uint8 i)
{
  g_Control=(angle-steeringPWM_MID);
  if(g_Control>25 ||g_Control<-25)
	{
  float tn=tan(g_Control/54.95*casu_weight); //54.95=70*0.785
  if(i) ///??
  {      
    return (A*(K-0.5*BORDWIDTH*tn/LDISTANCE*AK));//左
    
   // return 1;
  }
  //??
	else
	{
    return (A*(K+0.5*BORDWIDTH*tn/LDISTANCE*AK));//右
	}
}
  //return 0;
}
