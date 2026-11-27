/*
 * midline_process.h
 *
 *  Created on: 2022Äê5ÔÂ12ÈÕ
 *      Author: hakuya
 */

#ifndef CODE_MIDLINE_PROCESS_H_
#define CODE_MIDLINE_PROCESS_H_
#include "zf_common_headfile.h"
#define  Width_P 0.9

//extern uint16 cha_mid;
//float Getrouteoffset2(unsigned char start,unsigned char end,float midpos);

void ExtractCenterline_R();
void ExtractCenterline_L();
int ExtractCenterline_1();
int ExtractCenterline(Str_Boundary *str);
extern int Middle_Row;
extern int ElseRoad_Middle_Row;
extern int Round_Middle_Row;
extern int Barrier_Middle_Row;
extern int16  position;
extern int16  position2;
void error_get(void);
void MY_midline_process(Str_Boundary  *str);
#endif /* CODE_MIDLINE_PROCESS_H_ */
