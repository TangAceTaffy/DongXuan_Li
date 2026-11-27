//control()可以改直道→速度闭环：left_motor_pid(500)right_motor_pid(500)和弯道速度→差速：Speed_Differential_calculation(400)以及各类元素速度
//注：roadtype显示的是特殊元素类型，elseroad（只用到了c_road→弯道和→s_road直道）显示的是正常闭环的时候的直弯道
#include "zf_common_headfile.h"
//enum_c_road c_road_type;
//----陀螺仪水平积分----//
float angle_i = 0;
void angle_yaw_inte(void)
{
    angle_i += (float)((icm20602_gyro_z-6.5)*-0.0001210);
}

//----陀螺仪垂直积分----//
float angle_v = 0;
void angle_pitch_inte(void)
{
		angle_v += (float)((icm20602_gyro_y-10)*0.0001210);
}

//----角加速度计算----//
float angular_speed = 0;
void angular_speed_calc(void)
{
    angular_speed = ((float)((icm20602_gyro_z-5.3)*0.0001210))/0.002;
}

uint8 para1 = 45;//圆环中电感值
//----元素识别主函数----//   返回标志位
//各元素标志位
uint8 Fork_Flag = 0;
uint8 in_fork_status = 0;
uint8 Left_Big_annulus_status = 0;
uint8 Left_Small_annulus_status = 0;
uint8 Right_Big_annulus_status = 0;
uint8 Right_Small_annulus_status = 0;
uint8 Ramp_Flag = 0;
uint8 have_element_flag = 0;
//三岔内标志位（未用）
uint8 Fork_num = 1;//------------------------1左2右---------------------//
uint8 fork_turn_left_flag = 0;
uint8 fork_turn_right_flag = 0;
uint8 exit_ban = 0; //刚入三岔，避免立刻退出
static uint8 Fork_count = 0;
//圆环内标志位
uint8 big_annulus_series[6]= {0,0,0,0,0,0};//------------------------1大0小---------------------//
uint8 left_annulus_series[6]= {0,0,0,0,0,0};//------------------------1左0右---------------------//
static uint8 annulus_ban = 0;
uint8 Fork_ban = 0;

uint8 annulus_count = 0;
uint8 annulus_status = 0;
uint8 annulus_turn_left_small_flag = 0;
uint8 annulus_turn_left_big_flag = 0;
uint8 annulus_turn_right_big_flag = 0;
uint8 annulus_turn_right_small_flag = 0;

static float find_distance = 0;//环内走过的距离数据点
static float in_distance = 0;
static float out_distance = 0;
static float leave_distance = 0;
//坡道（未用到）
static float Ramp_distance = 0;
static float outramp_distance = 0;
//计数
static float out_twice_distance = 0;
static uint8 motor_stop_flag = 0;
static uint8 the_end_flag = 0;
uint8 hall_flag = 0;
uint8 hall_count = 0;
//强制越界保护
uint8 force_left_flag = 0;
uint8 force_right_flag = 0;
//------------------写死元素顺序---------------//
static uint8 element_order[4] = {1,1,1,1};//---------个数要确定，环为1，三岔为0--------//
static uint8 element_count = 0;
static uint8 element_ban = 0;
//圆环过程
//1 发现圆环 打直
//2 入环	打死一个转角
//3 环内巡线
//4 出环 	打死一个转角
//5 离开圆环 打直

//调车用
//uint8 Brush_Stop_flag=1;//可以进行上位机控制的标志位
//uint8 Brushless_Stop_flag=1;

//比赛用
uint8 Brush_Stop_flag=1;//可以进行上位机控制的标志位
uint8 Brushless_Stop_flag=1;

uint8 acc_flag = 0;
uint8 slo_flag = 0;

void motor_speed()
{
    if ((Brush_Stop_flag == 0&&Brushless_Stop_flag==0)&&Garage_Flag==0) //动的&&并非识别到斑马线要停车
    {
        diff_speed();
        pwm_set_duty(ATOM0_CH5_P02_5, 1500);
        pwm_set_duty(ATOM0_CH4_P02_4, 1500);
    }
    else if ((Brush_Stop_flag == 1&&Brushless_Stop_flag==1)||Garage_Flag==1)//不动,Garage_Flag==1是为了当roadtype不再是garage后不会再次启动电机
    {
                left_motor_pid(0);
                right_motor_pid(0);
                pwm_set_duty(ATOM0_CH5_P02_5, 1000);
                pwm_set_duty(ATOM0_CH4_P02_4, 1000);
    }
    else if(Brush_Stop_flag == 1&&Brushless_Stop_flag==0)
    {
        pwm_set_duty(ATOM0_CH5_P02_5, 1500);
        pwm_set_duty(ATOM0_CH4_P02_4, 1500);
    }

//    Changable_Speed(700);
//    left_motor_pid(0);
//    right_motor_pid(0);
}

