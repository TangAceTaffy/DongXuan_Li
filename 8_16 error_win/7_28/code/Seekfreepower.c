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
float Kp1=10;//差速系数39
int16 speed_maximum = 600;//800
int16 speed_minimum = 600;
int16 circle_speed_maximum = 600;
int16 circle_speed_minimum = 600;

static int16 averagespeed[5] = {600, 600, 600, 600, 600};
static int as = 0;
int16 sumspeed = 0;
double averagespeed1;
void calculate_diff_output(float Kp1, int16 error)
{
    diff_output=Kp1 * error;
}

// 理想行进速度 = 最大速度 - (最大速度 - 最小速度) * abs(舵机转向值 / 舵机最大转向值)
int16 ideal_speed;
void calculate_ideal_speed(int16 max_speed, int16 min_speed, int16 steering_value, int16 max_steering_value)
{
    ideal_speed=max_speed - (max_speed - min_speed) * ABS(steering_value / max_steering_value)*3;//0.9
}

// 左轮理想速度 = 理想行进速度 + 差速输出
float left_ideal_speed;
void calculate_left_wheel_speed(int16 ideal_speed, float diff_output)
{
    left_ideal_speed=ideal_speed + diff_output;
}

// 右轮理想速度 = 理想行进速度 - 差速输出
float right_ideal_speed;
void calculate_right_wheel_speed(int16 ideal_speed, float diff_output)
{
    right_ideal_speed=ideal_speed - diff_output;
}
//两个轮子的差速输出
void diff_speed(void)
{
    as = (as + 1) % 5;
    calculate_diff_output(Kp1,-error);//差速输出

    if(RoundProcess>=Find_Round)
    {
        calculate_ideal_speed(circle_speed_maximum,circle_speed_minimum,output,steer_duty_max);
    }
    else
    {
//        calculate_ideal_speed(MAX_SPEED,MIN_SPEED,output,steer_duty_max);
        calculate_ideal_speed(speed_maximum,speed_minimum,output,steer_duty_max);
    }
    averagespeed[as] = ideal_speed;
    sumspeed = 0;
    for(int i = 0; i < 5; i++)
    {
        sumspeed += averagespeed[i];
    }
    averagespeed1 = sumspeed / 5;
    ideal_speed = averagespeed1;

//    if(ideal_speed<600){
//        ideal_speed=600;
//    }

    calculate_left_wheel_speed(ideal_speed,diff_output);
    calculate_right_wheel_speed(ideal_speed,diff_output);

//    left_ideal_speed = 1000;
//    right_ideal_speed = 1000;

    left_motor_pid(left_ideal_speed);
    right_motor_pid(right_ideal_speed);
}
