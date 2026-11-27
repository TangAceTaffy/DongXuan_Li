//注：roadtype显示的是特殊元素类型，elseroad（只用到了c_road→弯道和→s_road直道）显示的是正常闭环的时候的直弯道
#include "zf_common_headfile.h"
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
//----元素识别主函数----//   返回标志位
//各元素标志位
uint8 have_element_flag = 0;
//比赛用
uint8 Brush_Stop_flag=0;//可以进行上位机控制的标志位
uint8 Brushless_Stop_flag=0;

void motor_speed()
{
    if ((Brush_Stop_flag == 0&&Brushless_Stop_flag==0)&&Garage_Flag==0) //动的&&并非识别到斑马线要停车
    {
        diff_speed();
//        Moto_L(3000);
//        Moto_R(3000);

        pwm_set_duty(ATOM0_CH5_P02_5, 800);
        pwm_set_duty(ATOM0_CH4_P02_4, 800);
    }
    else if ((Brush_Stop_flag == 1&&Brushless_Stop_flag==1)||Garage_Flag==1)//不动,Garage_Flag==1是为了当roadtype不再是garage后不会再次启动电机
    {
//        left_motor_pid(0);
//        right_motor_pid(0);
        Moto_L(0);
        Moto_R(0);
        pwm_set_duty(ATOM0_CH5_P02_5, 200);
        pwm_set_duty(ATOM0_CH4_P02_4, 200);
    }
    else if(Brush_Stop_flag == 1&&Brushless_Stop_flag==0)
    {
        pwm_set_duty(ATOM0_CH5_P02_5, 800);
        pwm_set_duty(ATOM0_CH4_P02_4, 800);
    }
//    left_motor_pid(700);
//    right_motor_pid(700);
//    diff_speed();
}

