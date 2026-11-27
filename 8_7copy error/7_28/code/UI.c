/*
 * UI.c
 *
 *  Created on: 2024年7月28日
 *      Author: icand
 */
#include "zf_common_headfile.h"
//显示一级菜单
void DisplayMain(void)
{
    tft180_show_string(20,  0, "1.SPEED");//速度设置
    tft180_show_string(20, 20, "2.PID");//pid设置
    tft180_show_string(20, 40, "3.FORESEE");//前瞻设置
    tft180_show_string(20, 60, "4.CIRCLE");//圆环设置
    tft180_show_string(20, 80, "5.OTHERS");//其他元素设置
    tft180_show_string(20, 100, "6.START");//启动
//    tft180_show_string(20, 120, "7.STOP");//停止
}
//子界面
//1.SPEED界面
void DisplaySpeed(void)
{
    tft180_show_string(20,  0, "Max:");  tft180_show_int(75, 0,speed_maximum,4);//速度最大值
    tft180_show_string(20, 20, "Min:");  tft180_show_int(75, 20,speed_minimum,4);//速度最小值
    tft180_show_string(20, 40, "KP1:");  tft180_show_float(75, 40,Kp1,2,1); //圆环设置
}
//2.PID界面
void DisplayPID(void)
{
    tft180_show_string(20,  0, "Kp:");    tft180_show_float(65, 0,Kp,1,1);
    tft180_show_string(20, 20, "Kp_p:");  tft180_show_float(65, 20,Kp_p,1,3);
    tft180_show_string(20, 40, "Kd:");    tft180_show_int(65, 40,Kd,2);
    tft180_show_string(20, 60, "Kd_d:");  tft180_show_float(65, 60,Kd_d,1,4);
}
//3.FORSEE界面
void DisplayForsee(void)
{
    tft180_show_string(20,  0, "Else:");    tft180_show_int(65, 0,ElseRoad_Middle_Row,2);
    tft180_show_string(20, 20, "Rnd:");     tft180_show_int(65, 20,Round_Middle_Row,2);
    tft180_show_string(20, 40, "Barr:");    tft180_show_int(65, 40,Barrier_Middle_Row,2);
}
//4.CIRCLE界面
void DisplayCircle(void)
{
//    tft180_show_string(20,  0, "STAMAX:");    tft180_show_int(80, 0,STAT_MAX,2);
//    tft180_show_string(20, 20, "STAMIN:");    tft180_show_int(80, 20,STAT_MIN,2);
    tft180_show_string(20, 40, "Enable:");    tft180_show_int(80, 40,Round_Enable,1);
    tft180_show_string(20, 60, "SPEEDMAX:");  tft180_show_int(90, 60,circle_speed_maximum,3);
    tft180_show_string(20, 80, "SPEEDMIN:");  tft180_show_int(90, 80,circle_speed_minimum,3);
}
//5.OTHERS界面
void DisplayOthers(void)
{
//    tft180_show_string(20,  0, "STAMAX:");    tft180_show_int(80, 0,STAT_MAX,2);
//    tft180_show_string(20, 20, "STAMIN:");    tft180_show_int(80, 20,STAT_MIN,2);
//    tft180_show_string(20, 40, "Enable:");      tft180_show_int(80, 40,Round_Enable,1);
}
//5.START界面
void DisplayStart(void)
{
    tft180_show_string(20,  0, "BRUSHLESS:");    tft180_show_int(100, 0,!Brushless_Stop_flag,1);
    tft180_show_string(20, 20, "BRUSH:");        tft180_show_int(100, 20,!Brush_Stop_flag,1);
}
int16 arrow = 0;//定义光标所在的行，初始化在第一行
void DisplayCursor(void)
{
    tft180_show_string(0,arrow,"->");//在参数前面显示>
}

//接收按键值，并更新arrow
void UI_ContentKey(void)
{
    uint8 key = Get_Key_flag();//获取按键值
    if(key == key1_flag)//向上 up
    {
        tft180_show_string(0,arrow,"  ");  //需要将当前行的光标隐藏，不然当arrow更新之后，出现两行显示光标
        arrow-=20;//向上移动，arrow减小
    }
    if(key == key2_flag)//向下 down
    {
        tft180_show_string(0,arrow,"  ");
        arrow+=20;//和up同理
    }
    if(key == key3_flag)//进入子页面  enter
    {
        tft180_clear();//需要将当前显示清屏，用于显示子界面
        pagenum = pagenumdown();//进入子界面
        arrow = 0;
    }
    if(key == key4_flag)//返回上一个页面 back
    {
        tft180_clear();//需要将当前显示清屏，用于返回上一个页面
        pagenum = pagenumup();//返回上个界面
        arrow = 0;
    }
    if(arrow < 0)
    {
        arrow = 120;//意思是：当按下up键，光标一直向上移动，当运动到第一行即arrow=0，
    }             //再按下up时，光标直接跳到最后一行，arrow = 120
    else if(arrow >120)
    {
        arrow = 0;
    }
}
unsigned char pagenum=0;
void UI_Content(void)
{
//    tft180_clear();//在显示新一级菜单时，需要清屏
    // 根据pagenum去显示菜单
    switch(pagenum)
    {
        case 0://显示主菜单
        {
            DisplayMain();
        }break;
        case 1://
        {
            DisplaySpeed();
        }break;
        case 2://
        {
            DisplayPID();
        }break;
        case 3://
        {
            DisplayForsee();
        }break;
        case 4://
        {
            DisplayCircle();
        }break;
        case 5://显示元素参数
        {
            DisplayOthers();
        }break;
        case 6://
        {
            DisplayStart();
        }break;
//        case 7://
//        {
//            DisplayBarrierPara();
//        }break;
//        case 8://
//        {
//            DisplayPodaoPara();
//        }break;
        default://其他非法情况
        {
            DisplayMain();
        }break;
    }
}

//返回上一级菜单
uint8 pagenumup(void)
{
    switch(pagenum)
    {
        case 0://在一级菜单
            return 0;
        case 1://在一级菜单
            return 0;
        case 2://在一级菜单
            return 0;
        case 3://在一级菜单
            return 0;
        case 4://在一级菜单
            return 0;
        case 5://在一级菜单
            return 0;
        //这里解释一下，当在二级菜单ID=6时，返回的上一级是ID=5
//        //详情参考：十八届智能车负压电磁组（五）：UI设计
//        //
//        case 6://在二级菜单
//            return 5;
//        case 7://在二级菜单
//            return 5;
//        case 8://在二级菜单
//            return 5;

        default:
            return 0;
    }
}

//进入下一级菜单
//需要判断当前ID：知道在那一页，有些什么参数
//还需要判断光标所在行：知道要进入哪一个变量里面
uint8 pagenumdown(void)
{
    switch(pagenum)
    {
        case 0://在主界面
        {
            switch(arrow)//判断在第几行
            {
                case 0://在第0行---->对应着参数LeftMotorPara
                {
                    return 1;//进入DisplaySpeed
                }
                case 20: return 2;//对应DisplayPID
                case 40: return 3;//对应DisplayForsee
                case 60: return 4;//对应DisplayCircle
                case 80: return 5;//对应DisplayOthers
                case 100: return 6;
                case 120: return 7;
            }
        }break;
        case 1://在LeftMotorPara界面
        {
            return 1;//返回当前界面
            //在该界面下没有下一级，就直接break;
        }break;
        case 2: return 2;break;//在RightMotorPara界面
        case 3: return 3;break;//ServoPara界面
        case 4: return 4;break;//IMUPara界面
        case 5://ElemnetPara界面
        {
            switch(arrow)
            {
                case 0: return 6;//对应Ring
                case 1: return 7;//对应Barrier
                case 2: return 8;//对应podao
                default : return 5;//返回当前界面
            }
        }break;

        default:break;
    }
}

float mul = 1;//倍率（粗调或细调）

//显示具体的参数
void UI_Datapage()
{
    uint8 x = 20,y = 60;
    switch(pagenum)
    {
        case 0:break;//在ID为0的界面没有需要修改的参数
        case 1://
        {
            switch(arrow)
            {
                case 0://MAX
                {
                    tft180_show_string(x,0,"MAX");
                    tft180_show_int(y,30,speed_maximum,4);
                }break;
                case 20://MIN
                {
                    tft180_show_string(x,0,"MIN");
                    tft180_show_int(y,30,speed_minimum,4);
                }break;
                case 40://KP1
                {
                    tft180_show_string(x,0,"KP1");
                    tft180_show_float(y,30,Kp1,2,1);
                }break;
                default:break;
            }
            tft180_show_float(60,60,mul,3,3);//显示倍率
        }break;

        case 2://对应PID
        {
            switch(arrow)
            {
                case 0://kp
                {
                    tft180_show_string(x,0,"Kp");
                    tft180_show_float(y,30,Kp,1,2);
                }break;
                case 20://kp_p
                {
                    tft180_show_string(x,0,"Kp_p");
                    tft180_show_float(y,30,Kp_p,1,3);
                }break;
                case 40://kd
                {
                    tft180_show_string(x,0,"Kd");
                    tft180_show_int(y,30,Kd,2);
                }break;
                case 60://kd_d
                {
                    tft180_show_string(x,0,"Kd_d");
                    tft180_show_float(y,30,Kd_d,1,3);
                }break;
                default:break;
            }
            tft180_show_float(60,60,mul,3,3);//显示倍率
        }break;
        case 3://对应Foresee
        {
            switch(arrow)
            {
                case 0://Else
                {
                    tft180_show_string(x,0,"Else");
                    tft180_show_int(y,30,ElseRoad_Middle_Row,2);
                }break;
                case 20://Rnd
                {
                    tft180_show_string(x,0,"Rnd");
                    tft180_show_int(y,30,Round_Middle_Row,2);
                }break;
                case 40://Barr
                {
                    tft180_show_string(x,0,"Barr");
                    tft180_show_int(y,30,Barrier_Middle_Row,2);
                }break;
                default:break;
            }
            tft180_show_float(60,60,mul,3,3);//显示倍率
        }break;
        case 4://对应Circle
        {
            switch(arrow)
            {
//                case 0://对应STAT_MAX
//                {
//                    tft180_show_string(x,0,"STAMAX");
//                    tft180_show_int(y,30,STAT_MAX,2);
//                }break;
//                case 20://对应STAT_MIN
//                {
//                    tft180_show_string(x,0,"STAMIN");
//                    tft180_show_int(y,30,STAT_MIN,2);
//                }break;
                case 40://对应Enable
                {
                    tft180_show_string(x,0,"Enable");
                    tft180_show_int(y,30,Round_Enable,1);
                }break;
                case 60://对应SPEED_MAX
                {
                    tft180_show_string(x,0,"SPEEDMAX");
                    tft180_show_int(y,30,Round_Enable,3);
                }break;
                case 80://对应SPEED_MIN
                {
                    tft180_show_string(x,0,"SPEEDMIN");
                    tft180_show_int(y,30,Round_Enable,3);
                }break;
                default:break;
            }
            tft180_show_float(60,60,mul,3,3);//显示倍率
        }break;
        case 5:break;//对应Others
        case 6:
        {
            switch(arrow)
            {
                case 0:
                {
                    tft180_show_string(x,0,"BRUSHLESS");
                    tft180_show_int(y,30,!Brushless_Stop_flag,1);
                }break;
                case 20://对应AngleTh
                {
                    tft180_show_string(x,0,"BRUSH");
                    tft180_show_int(y,30,!Brush_Stop_flag,1);
                }break;
                default:break;
            }
//            tft180_show_float(60,60,mul,3,3);//显示倍率
        }break;
//        case 7://对应BarrierPara
//        {
//            //自行添加变量
//
//        }break;
//        case 8://对应podaoPara
//        {
//            //自行添加变量
//        }break;

        default:break;
    }
}
uint8 datapage = 0;//0：显示ID对应的函数，1：修改arrow对应的参数

//更改参数
void UI_DatapageKey()
{
    uint8 key = Get_Key_flag();
    if(key == key1_flag)//   +
    {
        switch(pagenum)//判断在哪一页
        {
            case 1:
            {
                switch(arrow)//哪一行
                {
                    case 0:speed_maximum += mul;break;
                    case 20:speed_minimum += mul;break;
                    case 40:Kp1 += mul;break;
                    default:break;
                }
            }break;
            case 2:
            {
                switch(arrow)
                {
                    case 0:Kp += mul;break;
                    case 20:Kp_p += mul;break;
                    case 40:Kd += mul;break;
                    case 60:Kd_d += mul;break;
                    default:break;
                }
            }break;
            case 3:
            {
                switch(arrow)
                {
                    case 0:ElseRoad_Middle_Row += mul;break;
                    case 20:Round_Middle_Row += mul;break;
                    case 40:Barrier_Middle_Row += mul;break;
                    default:break;
                }
            }break;
            case 4:
            {
                switch(arrow)
                {
//                    case 0:STAT_MAX += mul;break;
//                    case 20:STAT_MIN += mul;break;
                    case 40:Round_Enable += mul;break;
                    case 60:circle_speed_maximum += mul;break;
                    case 80:circle_speed_minimum += mul;break;
                    default:break;
                }
            }break;
           case 6:
           {
               switch(arrow)
               {
                   case 0:Brushless_Stop_flag =Brushless_Stop_flag^1;break;
                   case 20:Brush_Stop_flag =Brush_Stop_flag^1;break;
                   default:break;
               }
           }break;
            default:break;
        }
    }
    if(key == key2_flag)// -
     {
        switch(pagenum)//判断在哪一页
        {
            case 1:
            {
                switch(arrow)//哪一行
                {
                    case 0:speed_maximum -= mul;break;
                    case 20:speed_minimum -= mul;break;
                    case 40:Kp1 -= mul;break;
                    default:break;
                }
            }break;
            case 2:
            {
                switch(arrow)
                {
                    case 0:Kp -= mul;break;
                    case 20:Kp_p -= mul;break;
                    case 40:Kd -= mul;break;
                    case 60:Kd_d -= mul;break;
                    default:break;
                }
            }break;
            case 3:
            {
                switch(arrow)
                {
                    case 0:ElseRoad_Middle_Row -= mul;break;
                    case 20:Round_Middle_Row -= mul;break;
                    case 40:Barrier_Middle_Row -= mul;break;
                    default:break;
                }
            }break;
            case 4:
            {
                switch(arrow)
                {
//                    case 0:STAT_MAX -= mul;break;
//                    case 20:STAT_MIN -= mul;break;
                    case 40:Round_Enable -= mul;break;
                    case 60:circle_speed_maximum -= mul;break;
                    case 80:circle_speed_minimum -= mul;break;
                    default:break;
                }
            }break;

            default:break;
        }
    }
    if(key == key3_flag)//更改倍率
    {
        mul/= 10;
    }
    if(key == key4_flag)// 确认更改参数
    {
        mul*= 10;
    }
    if(mul>=1000)
    {
        mul=0.001;
    }
    else if(mul<0.001)
    {
        mul=100;
    }
//    if(key == key5_flag)
//    {
//        datapage = 0;
//    }

}
void UI(void)
{
    if(!gpio_get_level(SWITCH1)&&!gpio_get_level(SWITCH2))
    {
        UI_Content();//显示ID对应的函数
        UI_ContentKey();//更新ID
    }
    else if(!gpio_get_level(SWITCH1)&&gpio_get_level(SWITCH2))
    {
        UI_Datapage();  //数据页
        UI_DatapageKey();   //数据按键处理
    }
    DisplayCursor();//光标显示
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
