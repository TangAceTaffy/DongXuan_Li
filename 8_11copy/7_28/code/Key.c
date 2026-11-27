/*
 * Key.c
 *
 *  Created on: 2024年5月16日
 *      Author: icand
 */
#include "zf_common_headfile.h"
uint8 SW1_Last;
uint8 SW2_Last;

void Key_Init(void)
{
    gpio_init(Up, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(Down, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(Enter, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(Back, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入

    gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH1 输入 默认高电平 上拉输入
    gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH2 输入 默认高电平 上拉输入
}


//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

/***************************************************************
* 函数名称：uint8 Get_Key_flag(void)
* 功能说明：通过Get_Key_flag()函数就可以判断哪个按键按下
* 参数说明：
* 函数返回：
* 修改时间：2024年7月28日
* 备 注：
***************************************************************/
uint8 Get_Key_flag(void)//获取按键状态
{
    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;

    //读取当前按键状态
    key1_status = gpio_get_level(Up);
    key2_status = gpio_get_level(Down);
    key3_status = gpio_get_level(Enter);
    key4_status = gpio_get_level(Back);

    //检测到按键按下之后  并放开置位标志位
    if(key1_status && !key1_last_status)    return key1_flag;
    if(key2_status && !key2_last_status)    return key2_flag;
    if(key3_status && !key3_last_status)    return key3_flag;
    if(key4_status && !key4_last_status)    return key4_flag;
    return 0;
}


//void Page_Decide(void)
//{
//    if(!gpio_get_level(SWITCH1)&&!gpio_get_level(SWITCH2))//00
//    {
//        page=1;
//        Brush_Stop_flag =1;
//        Brushless_Stop_flag=1;
//    }
//    else if(!gpio_get_level(SWITCH1)&&gpio_get_level(SWITCH2))//01
//    {
//        page=2;
//
//    }
//    else if(gpio_get_level(SWITCH1)&&!gpio_get_level(SWITCH2))//10
//    {
//        page=3;
//
//    }
//    else if(gpio_get_level(SWITCH1)&&gpio_get_level(SWITCH2))//11
//    {
//        page=4;
//        Brush_Stop_flag =0;
//        Brushless_Stop_flag=0;
//    }
//}
