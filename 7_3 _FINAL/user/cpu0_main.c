/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/


#include "zf_common_headfile.h"
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

    init_and_set_all();//初始化

    while(1)
    {
        if(mt9v03x_finish_flag)                                                                                      //摄像头图像传输到显示屏
        {
            halve_image(mt9v03x_image[0],image1[0],ROW,COL);//图像压缩
            adapt_otsuThreshold(mt9v03x_image[0], ROW, COL, &Threshold);//获取阈值
            mt9v03x_finish_flag = 0;
        }
        //顺序不好乱改
        extract_edge(&Boundary,0 ,ROW/2-1,1,COL/2-1);//边缘提取
        Roadtype_check();//实际是deal→detect+process
        ExtractCenterline(&Boundary);//中线提取
        Distinguish();//直弯道识别
        error_get();//获取偏差error
        //servo_pid();

        display();//下位机显示

       //上位机发送指令——0：停车 1：启动！
        wireless_uart_read_buffer(&data, 1);//下位机读取一位串口数据
        if(data==0)
        {
            Brush_Stop_flag= 1;
            Brushless_Stop_flag= 1;
            //gpio_toggle_level(BUZZER_PIN);//蜂鸣器操作未知
            wireless_uart_send_string("\r\nALL_STOP");//上位机显示当前状态
        }
        else if(data==1)
        {
            Brush_Stop_flag= 1;
            Brushless_Stop_flag=0;
            //gpio_toggle_level(BUZZER_PIN);//蜂鸣器操作未知
            wireless_uart_send_string("\r\nBRUSHLESS_START");//上位机显示当前状态
        }
        else if(data==2)
        {
            Brush_Stop_flag= 0;
            Brushless_Stop_flag=0;
            wireless_uart_send_string("\r\nALL_START");//上位机显示当前状态
        }
        //模拟示波器
//        seekfree_assistant_oscilloscope_data.data[0] = Left_Encoder;
//        seekfree_assistant_oscilloscope_data.data[1] = Right_Encoder;
//        seekfree_assistant_oscilloscope_data.data[2] = 700;
////        seekfree_assistant_oscilloscope_data.data[3] = ;
////        seekfree_assistant_oscilloscope_data.data[4] = ;
////        seekfree_assistant_oscilloscope_data.data[5] = ;
////        seekfree_assistant_oscilloscope_data.data[6] = ;
//        seekfree_assistant_oscilloscope_data.channel_num = 3;
//        seekfree_assistant_oscilloscope_send(&seekfree_assistant_oscilloscope_data);
    }
}


