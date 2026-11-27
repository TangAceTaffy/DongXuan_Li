/*
 * seekfreepower.c
 *
 *  Created on: 2024年7月5日
 *      Author: icand
 */
#include "zf_common_headfile.h"
#include "math.h"
// 差速输出 = Kp1 * (图像偏差)
float diff_output;
float Kp1=5;//差速系数3.3
float Str_Kp1=1.5;
float Els_Kp1=4;//6.2
float KD_d =0.05;//0.05
float Kp_p1=0.0;
int16_t speed_maximum =700;//900

// int16_t circle_speed_maximum = 300;
// int16_t circle_speed_minimum = 300;

static int16_t averagespeed[5] = {80, 80, 80, 80, 80};

extern int defineSR;



void calculate_diff_output(float Kp1, int16_t error1)
{
    diff_output=Kp1 * error1+Kp_p1 * error1 * Float_ABS(error1)-KD_d*imu660ra_gyro_z;
}

// 理想行进速度 = 最大速度 - (最大速度 - 最小速度) * abs(舵机转向值 / 舵机最大转向值)
int16_t ideal_speed;
void calculate_ideal_speed(int16_t max_speed)
{
    ideal_speed=max_speed;
}

// 左轮理想速度 = 理想行进速度 + 差速输出
float left_ideal_speed;
void calculate_left_wheel_speed(int16_t ideal_speed, float diff_output)
{
    left_ideal_speed=ideal_speed + diff_output;
}

// 右轮理想速度 = 理想行进速度 - 差速输出
float right_ideal_speed;
void calculate_right_wheel_speed(int16_t ideal_speed, float diff_output)
{
    right_ideal_speed=ideal_speed - diff_output;
}
//两个轮子的差速输出
void diff_speed(void)
{
   if(defineSR == 0) Kp1=Els_Kp1;
   if(defineSR == 1) Kp1=Str_Kp1;//直道p
  
   if(RoundProcess>Find_Round&&RoundProcess<Leave_Round) Kp1=5;//R80:5.5
    calculate_diff_output(Kp1,-error1);//差速输出


//    calculate_ideal_speed(speed_maximum);
    if(defineSR == 1)
    {

        calculate_ideal_speed(speed_maximum);
    }
    if(defineSR == 0)
    {

        calculate_ideal_speed(500);//700
    }
   
     if(defineSR == 2)
    {

        calculate_ideal_speed(400);//600
      
       
        
    }
   if(CrossProcess>=Find_Cross&&CrossProcess<Out_Cross){
    calculate_ideal_speed(500);//650
   }
   if((RoundProcess>=Find_Round&&RoundProcess<Leave_Round)){
    calculate_ideal_speed(500);//R80:800
   }
   if(RoadType==Ramp)//处理障碍的时候的前瞻
          {
              calculate_ideal_speed(500);//600
          }

  
    calculate_left_wheel_speed(ideal_speed,diff_output);
    calculate_right_wheel_speed(ideal_speed,diff_output);

    // left_ideal_speed = 400;
    // right_ideal_speed = 400;
   

    left_motor_pid(left_ideal_speed);
    right_motor_pid(right_ideal_speed);
}
