/*********************************************************************************************************************
* LS2K0300 Opensourec Library 即（LS2K0300 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是LS2K0300 开源库的一部分
*
* LS2K0300 开源库 是免费软件
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
* 文件名称          zf_common_typedef
* 公司名称          成都逐飞科技有限公司
* 适用平台          LS2K0300
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者           备注
* 2025-02-27        大W            first version
********************************************************************************************************************/

#ifndef _zf_common_headfile_h_
#define _zf_common_headfile_h_
// #define Threshold (1)
#define COL                (160)
#define ROW                (120)
#define COL_START               (1)
#define COL_END                 COL-1
#define ROW_START               (1)
#define ROW_END                 ROW-1

extern int z_acc;
extern int tof_flag;

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sched.h>

//===================================================芯片 SDK 底层===================================================

//===================================================芯片 SDK 底层===================================================

//====================================================开源库公共层====================================================

#include "zf_common_font.h"
#include "zf_common_function.h"
#include "function.h"

#include "zf_common_typedef.h"
//====================================================开源库公共层====================================================

//===================================================芯片外设驱动层===================================================

#include "zf_driver_delay.h"

#include "zf_driver_gpio.h"
#include "zf_driver_file.h"
#include "zf_driver_encoder.h"
#include "zf_driver_pwm.h"


//===================================================芯片外设驱动层===================================================

//===================================================外接设备驱动层===================================================
#include "zf_device_ips200_fb.h"
#include "zf_device_imu_core.h"
#include "zf_device_imu660ra.h"
#include "zf_device_imu660rb.h"
#include "zf_device_imu963ra.h"




//===================================================外接设备驱动层===================================================


#include "Compilers.h"
#include "control.h"
#include "Cross.h"
#include "edge_find.h"
#include "Ifx_Cfg.h"
#include "Ifx_Types.h"
#include "image_data.h"
#include "image_deal.h"
#include "init.h"
#include "button.h"
#include "motor.h"
#include "Obstacle.h"
#include "Platform_Types.h"
#include "Ramp.h"
#include "register.h"
#include "road_type.h"
#include "Roundabout.h"
#include "Seekfreepower.h"
#include "servo.h"
#include "Zebra.h"
#include "straightaway.h"
#include "clean.h"
//===================================================应用组件层===================================================
// #include "seekfree_assistant.h"
// #include "seekfree_assistant_interface.h"
//===================================================应用组件层===================================================
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
//===================================================用户自定义文件===================================================

//===================================================用户自定义文件===================================================




#endif

