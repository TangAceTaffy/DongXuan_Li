/*
 * Key.c
 *
 *  Created on: 2024年5月16日
 *      Author: icand
 */
#include "zf_common_headfile.h"
int16 key_S_value=0,key_H_value=0,key_ok_value=0;
int16 LCD_page=1,LCD_item=1,LCD_item_last=1,LCD_sum=0,LCD_sum_max=255,LCD_sum_min=-255,LCD_page_max=3,LCD_item_max=8,LCD_page_min=1,LCD_item_min=1;
int16 page=1,arrow_row=0,arrow_col=0;//控制菜单的俩变量
int16 page_last;//
uint8 SW1_Last;
uint8 SW2_Last;

void Key_Init(void)
{
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入

    gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH1 输入 默认高电平 上拉输入
    gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH2 输入 默认高电平 上拉输入
}
void Page_Decide(void)
{
    if(!gpio_get_level(SWITCH1)&&!gpio_get_level(SWITCH2))//00
    {
        page=1;
    }
    else if(!gpio_get_level(SWITCH1)&&gpio_get_level(SWITCH2))//01
    {
        page=2;
    }
    else if(gpio_get_level(SWITCH1)&&!gpio_get_level(SWITCH2))//10
    {
        page=3;
    }
    else if(gpio_get_level(SWITCH1)&&gpio_get_level(SWITCH2))//11
    {
        page=4;
    }
}
void key_action(void)
{
    Page_Decide();//每页按键作用不同
    switch (page)
    {
        case 1:
        {
            break;
        }
        case 2:
        {
            if(gpio_get_level(KEY1)==0)
            {
               system_delay_ms(300);
               arrow_row=arrow_row+20;
               tft180_clear();
            }
            if(gpio_get_level(KEY2)==0)
            {
               system_delay_ms(300);
               arrow_row=arrow_row-20;
               tft180_clear();
            }
            if((arrow_row<0)) arrow_row=80;
            else if((arrow_row>80))arrow_row=0;

            if(gpio_get_level(KEY3)==0)
            {

                system_delay_ms(300);
                Elements_Sequence[arrow_row/20]=Elements_Sequence_All[arrow_col++];
                tft180_clear();
            }
            if(gpio_get_level(KEY4)==0)
            {
                system_delay_ms(300);
                Elements_Sequence[arrow_row/20]=Elements_Sequence_All[arrow_col--];
                tft180_clear();
            }
            if((arrow_col<0)) arrow_col=11;
            else if((arrow_col>11))arrow_col=0;
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }

    }
//拨码开关变化要清屏
    if(SW1_Last!=gpio_get_level(SWITCH1))
    {
        tft180_clear();
    }
    SW1_Last=gpio_get_level(SWITCH1);


    if(SW2_Last!=gpio_get_level(SWITCH2))
    {
        tft180_clear();
    }
    SW2_Last=gpio_get_level(SWITCH2);
}

void key(void)
{
    //按键检测
    //at24c02_write_bytes(100,write_buf,8);
    if(KEY1==0)//up
    {
        system_delay_ms(20);
        if(KEY1==0)
        {
            key_S_value+=1;

        }
        while(KEY1==0);
        LCD_value();
    }
    else if(KEY2==0)//down
    {
        system_delay_ms(20);
        if(KEY2==0)
        {
            key_S_value-=1;

        }
        while(KEY2==0);
        LCD_value();
    }
    else if(KEY3==0)//right
    {
        system_delay_ms(20);
        if(KEY3==0)
        {
            key_H_value+=1;

        }
        while(KEY3==0);
        LCD_value();
    }
    else if(KEY4==0)//left
    {
        system_delay_ms(20);
        if(KEY4==0)
        {
            key_H_value-=1;

        }
        while(KEY4==0);
        LCD_value();
    }
//    else if(k5==0)
//    {
//        delay_ms(500);
//        if(k5==0)//exit
//        {
//            key_ok_value-=1;
//            ips114_clear(BLACK);
//            LCD_item_last=1;
//            LCD_item=LCD_item_last;
//        }
//        else//ok
//        {
//            key_ok_value+=1;
//            ips114_clear(BLACK);
//      LCD_item_last=LCD_item;
//            LCD_item=1;
//        }
//        while(k5==0);
//        LCD_value();
//    }
}
void LCD_value(void)
{
    LCD_page+=key_ok_value;
    key_ok_value=0;
    LCD_item+=key_S_value;
    key_S_value=0;
    LCD_sum+=key_H_value;
    key_H_value=0;
  LCD_page=limit_max(LCD_page,LCD_page_max);
    LCD_page=limit_min(LCD_page,LCD_page_min);
    LCD_item=limit_max(LCD_item,LCD_item_max);
    LCD_item=limit_min(LCD_item,LCD_item_min);
    LCD_sum=limit_max(LCD_sum,LCD_sum_max);
    LCD_sum=limit_min(LCD_sum,LCD_sum_min);
    LCD_show();
}
void LCD_show()
{//屏幕UI显示
//  ips114_clear(BLACK);
//    if(LCD_page==1)
//    {
//        ips114_showstr(10,0,"Link Start!");
//        ips114_showstr(10,1,"adc_show");
//        ips114_showstr(10,2,"value_set");
//        ips114_showstr(10,3,"check the score");
//        ips114_showstr(10,4,"guiyi mode");
//        switch(LCD_item)
//        {
//            case 1:ips114_showstr_now(10,0,"Link Start!");break;
//            case 2:ips114_showstr_now(10,1,"adc_show");break;
//            case 3:ips114_showstr_now(10,2,"value_set");break;
//            case 4:ips114_showstr_now(10,3,"check the score");break;
//            case 5:ips114_showstr_now(10,4,"guiyi mode");break;
//        }
//    }
//    else if(LCD_page==2)
//    {
//        if(LCD_item_last==1)
//        {
//            if(kk4==0)
//            {carstop=0;}
//            else
//            {
//                if(kk2==0)
//                    ku=1;
//                carstop=1;
//            }
//
//
//        }
//        else if(LCD_item_last==2)
//        {
//            ips114_showstr(60,0,"Initial value");
//            for(ii=0;ii<=6;ii++)
//                ips114_showint8(ii*30,1,adc_result[ii]);
//            ips114_showstr(70,3,"Guiyi value");
//            for(ii=0;ii<=6;ii++)
//                ips114_showint8(ii*30,4,ad_least[ii]);
//            ips114_showstr(90,6,"ad_pwm");
//            ips114_showint16(88,7,ad_pwm);
//            delay_ms(100);
//        }
//        else if(LCD_item_last==3)
//        {
//            ips114_showstr(10,0,"ad_P");
//            ips114_showint16(100,0,ad_P);
//            ips114_showstr(10,1,"ad_D");
//            ips114_showint16(100,1,ad_D);
//            ips114_showstr(10,2,"dir_P");
//            ips114_showint16(100,2,dir_P);
//            ips114_showstr(10,3,"sp_I");
//            ips114_showint16(100,3,sp_I);
//            ips114_showstr(10,4,"dis_P");
//            ips114_showint16(100,4,dis_P);
//            ips114_showstr(10,5,"speed_set");
//            ips114_showint16(100,5,speed_set);
//            ips114_showstr(10,6,"speed_weight");
//            ips114_showint16(100,6,speed_weight);
//            ips114_showstr(10,7,"steer_max");
//            ips114_showint16(100,7,steer_max);
//            if(LCD_item==1)
//            {
//                ips114_showstr_now(10,0,"ad_P");
//                ad_P=ad_P+LCD_sum;
//                write_buf[0] = ad_P;
//                at24c02_write_byte(0, write_buf[0]);
//                ips114_showint16_now(100,0,ad_P);
//                LCD_sum=0;
//            }
//            if(LCD_item==2)
//            {
//                ips114_showstr_now(10,1,"ad_D");
//                ad_D=ad_D+LCD_sum*2;
//                write_buf[1] = ad_D;
//                at24c02_write_byte(10, write_buf[1]);
//                ips114_showint16_now(100,1,ad_D);
//                LCD_sum=0;
//            }
//            if(LCD_item==3)
//            {
//                ips114_showstr_now(10,2,"dir_P");
//                dir_P=dir_P+LCD_sum;
//                write_buf[2] = dir_P;
//                at24c02_write_byte(20,write_buf[2]);
//                ips114_showint16_now(100,2,dir_P);
//                LCD_sum=0;
//            }
//            if(LCD_item==4)
//            {
//                ips114_showstr_now(10,3,"sp_I");
//                sp_I=sp_I+LCD_sum;
//                write_buf[3] = sp_I;
//                at24c02_write_byte(30, write_buf[3]);
//                ips114_showint16_now(100,3,sp_I);
//                LCD_sum=0;
//            }
//            if(LCD_item==5)
//            {
//                ips114_showstr_now(10,4,"dis_P");
//                dis_P=dis_P+LCD_sum;
//                write_buf[4] = dis_P;
//                at24c02_write_byte(40, write_buf[4]);
//                ips114_showint16_now(100,4,dis_P);
//                LCD_sum=0;
//            }
//            if(LCD_item==6)
//            {
//                ips114_showstr_now(10,5,"speed_set");
//                speed_set=speed_set+LCD_sum*5;
//                write_buf[5] = speed_set;
//                at24c02_write_byte(50,write_buf[5]);
//                ips114_showint16_now(100,5,speed_set);
//                LCD_sum=0;
//            }
//            if(LCD_item==7)
//            {
//                ips114_showstr_now(10,6,"speed_weight");
//                speed_weight=speed_weight+LCD_sum;
//                write_buf[6] = speed_weight;
//                at24c02_write_byte(60, write_buf[6]);
//                ips114_showint16_now(100,6,speed_weight);
//                LCD_sum=0;
//            }
//            if(LCD_item==8)
//            {
//                ips114_showstr_now(10,7,"steer_max");
//                steer_max=steer_max+LCD_sum*10;
//                write_buf[7] = steer_max;
//                at24c02_write_byte(70, write_buf[7]);
//                ips114_showint16_now(100,7,steer_max);
//                LCD_sum=0;
//            }
//        }
//        else if(LCD_item_last==4)
//        {
//            ips114_showstr(50,0,"SHANHUN THE FIRST");
//            ips114_showstr(50,1,"Group:Triple_cars");
//            ips114_showfloat(90,3,(js-6)/10.0,2,1);
//            ips114_showstr(150,3,"s");
//            ips114_showfloat(90,5,s_pwm*0.01,3,1);
//            ips114_showstr(150,5,"m");
//            ips114_showstr(40,7,"Mission Accomplished!");
//            delay_ms(100);
//        }
//        else if(LCD_item_last==5)
//        {
//            ips114_showstr(10,0,"guiyi mode");
//            guiyi_get();
//        }
//    }
//    key();
}
