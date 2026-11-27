#ifndef MIDLINE_PROCESS_H_
#define MIDLINE_PROCESS_H_

#define  Width_P 1.5
#include "zf_common_headfile.h"

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
extern int16_t  position;
extern int16_t  position2;
void error_get(void);
void MY_midline_process(Str_Boundary  *str);
#endif /* MIDLINE_PROCESS_H_ */