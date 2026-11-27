/*
 * Objective.h
 *
 *  Created on: 2024年4月8日
 *      Author: icand
 */

#ifndef CODE_OBSTACLE_H_
#define CODE_OBSTACLE_H_
typedef enum __ObstacleType
{
  No_Obstacle,
  Left_Obstacle,
  Right_Obstacle
}ObstacleTypeDef;
typedef enum __ObstacleProcess
{
  None_Obstacle,
  Find_Obstacle,
  Cross_Obstacle,
  Leave_Obstacle,
  Out_Obstacle

}ObstacleProcessTypeDef;
typedef  struct
{
       unsigned char Obstacle_flag;//障碍物标志位
       unsigned char Track_Width_forObstacle[ROW_END];//赛道宽度
       uint8 row1, row2;//记录障碍每个阶段边界所在列
       uint8 row1_flag, row2_flag;
       float Obstacle_Check_Point1;
       float Obstacle_Check_Point2;
       int8 Obstacle_Difference;//右边界列号差值
       uint8 temp_count1,temp_count2;
       uint8 temp_count1_print,temp_count2_print;
}Str_Obstacle;    //坡道结构体
////右路障
//extern uint8 Obstacle_Right_Flag;
//extern int8 Obstacle_Right_Difference;
//extern uint8 row1_right,row2_right;//记录每个阶段边界所在列
//extern uint8 row1_right_flag, row1_right_flag;
//extern float Obstacle_Right_Check_Point;
////左路障
//extern uint8 Obstacle_Left_Flag;
//extern int8 Obstacle_Left_Difference;
//extern uint8 row1_left, row2_left;//记录每个阶段边界所在列
//extern uint8 row1_left_flag, row1_left_flag;
//extern float Obstacle_Left_Check_Point;
//void Obstacl_Deal(void);
//void Obstacle_Right_Deal(void);
//void Obstacle_Left_Deal(void);

void Obstacle_Detection(void);
void Obstacl_Deal(void);
extern Str_Obstacle Obstacle;
extern ObstacleProcessTypeDef ObstacleProcess;
extern ObstacleTypeDef ObstacleType;
#endif /* CODE_OBSTACLE_H_ */
