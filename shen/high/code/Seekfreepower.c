/*
 * seekfreepower.c
 *
 *  Created on: 2024年7月5日
 *      Author: icand
 */
#include "zf_common_headfile.h"
// 差速输出 = Kp1 * (图像偏差)
float diff_output;
float Kp1=12.6;//差速系数39
void calculate_diff_output(float Kp1, int16 error)
{
    diff_output=Kp1 * error;
}

// 理想行进速度 = 最大速度 - (最大速度 - 最小速度) * abs(舵机转向值 / 舵机最大转向值)
int16 ideal_speed;
void calculate_ideal_speed(int16 max_speed, int16 min_speed, int16 steering_value, int16 max_steering_value)
{
    ideal_speed=max_speed - (max_speed - min_speed) * ABS(steering_value / max_steering_value)*1;//0.9
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
    calculate_diff_output(Kp1,-error);//差速输出
    if(RoundProcess>=Find_Round)
    {
        calculate_ideal_speed(820,800,output,steer_duty_max);
    }
    else
    {
        calculate_ideal_speed(MAX_SPEED,MIN_SPEED,output,steer_duty_max);
    }
    calculate_left_wheel_speed(ideal_speed,diff_output);
    calculate_right_wheel_speed(ideal_speed,diff_output);
    left_motor_pid(left_ideal_speed);
    right_motor_pid(right_ideal_speed);
}
//// 初始化位置式PID
//PositionalPID left_pid;
//PositionalPID right_pid;

//void initialize_pids() {
//    positional_pid_init(&left_pid, 1.0, 0.1, 0.01);
//    positional_pid_init(&right_pid, 1.0, 0.1, 0.01);
//}
//
//// 左轮pwm值 = 速度闭环PID函数(左轮理想速度, 编码器采集的左轮速度)
//double calculate_left_wheel_pwm(double ideal_left_speed, double encoder_left_speed)
//{
//    return positional_pid_calculate(&left_pid, ideal_left_speed, encoder_left_speed);
//}
//
//// 右轮pwm值 = 速度闭环PID函数(右轮理想速度, 编码器采集的右轮速度)
//double calculate_right_wheel_pwm(double ideal_right_speed, double encoder_right_speed)
//{
//    return positional_pid_calculate(&right_pid, ideal_right_speed, encoder_right_speed);
//}
//
//double positional_pid_calculate(PositionalPID *pid, double setpoint, double measured)
//{
//    double error = setpoint - measured;
//    pid->integral += error;
//    double derivative = error - pid->prev_error;
//
//    pid->output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
//
//    // 更新前一次的误差
//    pid->prev_error = error;
//
//    return pid->output;
//}
