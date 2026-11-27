#include "zf_common_headfile.h"
#include "init.h"
uint8 ALLSTART=0;
//用于无线串口通信
uint8 data=0;
void init_and_set_all(void)
{
      ALLSTART=0;
//TFT初始化
      tft180_init();                                        //TFT初始化
      tft180_clear ();                                      //TFT清屏
      tft180_show_string(0, 0, "init_START.");              //TFT显示初始化开始
//摄像头初始化
      mt9v03x_init();                                     //摄像头初始化
      tft180_show_string(0, 0, "mt9v03x_init ok.");       //摄像头初始化完成标志位
//示波器初始化
      seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
//无刷电机初始化
//      pwm_init(ATOM0_CH5_P02_5, 100, 1100);//0%占空比关闭状态
//      pwm_init(ATOM0_CH4_P02_4, 100, 1100);//0%占空比关闭状态

//电机初始化
      pwm_init(ATOM1_CH2_P21_4, 10000, 0);                          //0%占空比关闭状态
      gpio_init(P21_5, GPO,GPIO_HIGH, GPO_PUSH_PULL);               //上拉正转
      pwm_init(ATOM1_CH0_P21_2, 10000, 0);                          //0%占空比关闭状态
      gpio_init(P21_3, GPO, GPIO_HIGH, GPO_PUSH_PULL);              //上拉正转
      pwm_init(ATOM1_CH1_P33_9, 50, steeringPWM_MID);               //舵机初始化 736中值 666最右 800最左
//编码器初始化    定义在zf_driver_encoder_h
       encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);                  //编码器初始化
       encoder_quad_init(ENCODER_2, ENCODER_2_A, ENCODER_2_B);//正交编码器
//      encoder_dir_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);//方向编码器
       //下面为中断初始化，每20ms一次，在isr.c中找IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)，若改动中断须重新调参
//陀螺仪初始化
      imu660ra_init();
      calibrate_gyro();//去除零飘
//无线初始化
//      bluetooth_ch9141_init ();
//      wireless_uart_init();
//蜂鸣器初始化
       gpio_init(BUZZER_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
//电磁初始化
      //Adv_init();
//计时器初始化
      pit_ms_init(CCU60_CH0, 2);
      pit_ms_init(CCU60_CH1, 4);
      pit_ms_init(CCU61_CH1, 20);
      pit_ms_init(CCU61_CH0,1000);
//模糊表初始化
//        InitMH();
//无线串口初始化
      wireless_uart_init();

//按键初始化
      Key_Init();
//初始化结束
      tft180_show_string(0, 0, "init_FINISH.");             //初始化完成标志
      system_delay_ms(2000);                                 //等待上电
      tft180_clear();
      ALLSTART=1;
}
