#ifndef EDGE_FIND_H
#include "zf_common_headfile.h"

#define USE_num	image_h*3

#include "image_data.h"





 




//宏定义
#define image_h	120//图像高度
#define image_w	160//图像宽度

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//跳过的点数
#define border_max	image_w-2 //边界最大值
#define border_min	1	//边界最小值	
extern uint8 original_image[image_h][image_w];


extern void image_process(void); 
extern uint8 l_border[image_h];//左线数组
extern uint8 r_border[image_h];//右线数组
extern uint8 center_line[image_h];//中线数组
extern uint8 Threshold;
extern uint16 dir_r[(uint16)USE_num];//用来存储右边生长方向
extern uint16 dir_l[(uint16)USE_num];//用来存储左边生长方向
extern int L_down_point_x;
extern int R_down_point_x;
extern int L_down_point_y;
extern int R_down_point_y;
extern int L_up_point_x;
extern int R_up_point_x;
extern int L_up_point_y;
extern int R_up_point_y;
extern unsigned char image0[image_h][image_w];
extern int position;

extern uint16 data_stastics_l;//统计左边找到点的个数
extern uint16 data_stastics_r;//统计右边找到点的个数

extern uint16 points_l[USE_num][2]; 
extern uint16 points_r[USE_num][2];
extern void middle_line();
extern uint8 hight;
extern int r_lose_num;
extern int l_lose_num;
extern int r_lose_low_num;
extern int l_lose_low_num;

extern int ElseRoad_Middle_Row;
extern int StrightRoad_Middle_Row;


extern int Round_Middle_Row;
extern int Barrier_Middle_Row;

#endif 

