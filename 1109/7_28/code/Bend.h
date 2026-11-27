/*
 * Bend.h
 *
 *  Created on: Jul 3, 2022
 *      Author: hakuya
 */
#include "zf_common_headfile.h"

#ifndef BEND_H_
#define BEND_H_

typedef enum
{
       s_road =1,
       c_road,
       s_bend_big,
       s_bend_small,
       c_road_big,
       s_road_obstacle
}Enum_ElseRoadType;
extern  Enum_ElseRoadType  ElseRoadType;
void Distinguish(void);
#endif /* BEND_H_ */
