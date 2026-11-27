/*
 * road_type.h
 *
 *  Created on: 2022年5月12日
 *      Author: hakuya
 */
#include "zf_common_headfile.h"

#ifndef CODE_ROAD_TYPE_H_
#define CODE_ROAD_TYPE_H_
typedef enum
{
       else_road,
       Fork_Road,
       Cross_Road,
       Round_Road,
       Ramp,          //坡道
       Barrier,      //障碍物
       Garage,
       Start

} enum_RoadType;
extern  enum_RoadType  RoadType;
extern uint8 Elements_Sequence_All[11];
extern uint8 Elements_Sequence[8];
extern uint8 Elements_Current_Sequence;
void Roadtype_check(void);
#endif /* CODE_ROAD_TYPE_H_ */
