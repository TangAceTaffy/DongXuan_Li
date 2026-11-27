/*
 * edge_find.h
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"
#ifndef CODE_EDGE_FIND_H_
#define CODE_EDGE_FIND_H_
#define COL_SPACE         2              //间隔点搜索


typedef  struct
{
    unsigned char   RightEdge [ROW/2];//右边界数组
    unsigned char   LeftEdge  [ROW/2];//左边界数组
    unsigned char   MiddleLine[ROW/2];//中线数组
    unsigned char   RightEdge_Copy [ROW/2];//右边界数组
    unsigned char   LeftEdge_Copy  [ROW/2];//左边界数组
    unsigned char   MiddleLine_Copy[ROW/2];//中线数组

       unsigned char   RowLose[ROW/2];//丢线数组 1——不丢线 2——丢右 3——丢左 4——丢线

       unsigned char   AllLose;//左右同时丢线的记录值
       unsigned char   OnlyLeftLose;//只是左边界丢线的记录值
       unsigned char   OnlyRightLose;//只有右边界丢线的记录值
       unsigned char   AllLeftLose;//左边界所有丢线记录值
       unsigned char   AllRightLose;//右边界所有丢线记录值

       unsigned char   track_Width[ROW/2];//赛道宽度


       unsigned char L_StartLine;                //左边沿搜索结束行数置  -1
       unsigned char R_StartLine;                //右边沿搜索结束行数置  -1
       unsigned char StartLine;

       unsigned char L_EndLine;                //左边沿搜索结束行数置  -1
       unsigned char R_EndLine;                //右边沿搜索结束行数置  -1
       unsigned char EndLine;//动态封顶行
       unsigned char LastEndLine;//记录上次封顶行的记录值

       unsigned char Left_Edge_num;
       unsigned char Right_Edge_num;
}Str_Boundary;
typedef struct
{
    uint8 x;
    uint8 y;
} Site_t;
typedef  struct
{
       Site_t  L_down_point;            //左边沿十字下方直角拐点数组（[0]为十字拐点行坐标值，[1]为十字拐点列坐标值）
       Site_t  L_up_point;              //左边沿十字上方直角拐点数组（[0]为十字拐点行坐标值，[1]为十字拐点列坐标值）

       Site_t  R_down_point;            //右边沿十字下方直角拐点数组（[0]为十字拐点行坐标值，[1]为十字拐点列坐标值）
       Site_t  R_up_point;              //右边沿十字上方直角拐点数组（[0]为十字拐点行坐标值，[1]为十字拐点列坐标值）

}Str_Inflection_point;    //拐点结构体

extern int g_threshold_value;//用于差比和判断边线的阈值

extern Str_Boundary          Boundary;
extern Str_Inflection_point  Inflection_point;
//边界丢失数
extern unsigned char L_edge_lose;//左丢线数
extern unsigned char R_edge_lose;//右丢线数
void extract_edge(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END);
int L_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END);
void L_extract_edge_process(Str_Boundary  *str,  unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END);
void R_extract_edge_process(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END);
int R_extract_edge_start(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END);
void R_uppoint(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END,unsigned char Edge_ROW);
void L_uppoint(Str_Boundary  *str, unsigned char Row_START,unsigned char Row_END ,unsigned char Col_START,unsigned char Col_END,unsigned char Edge_ROW);
#endif /* CODE_EDGE_FIND_H_ */
