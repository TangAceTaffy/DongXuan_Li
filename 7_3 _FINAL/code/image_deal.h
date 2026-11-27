/*
 * image_deal.h
 *
 *  Created on: 2022Äê5ÔÂ12ÈÕ
 *      Author: hakuya
 */

#ifndef CODE_IMAGE_DEAL_H_
#define CODE_IMAGE_DEAL_H_

//#define LCDH 50
//#define LCDW 90
//#include "headfile.h"
//#include "common.h"
#include "zf_common_headfile.h"


void halve_image(unsigned char *p_in,unsigned char  *p_out,unsigned char row,unsigned char col);
unsigned char adapt_otsuThreshold(uint8 *image, uint16 col, uint16 row,unsigned char *threshold);
void binarization_processing(unsigned char *p,uint16 row,uint16 col);

extern unsigned char Threshold;
extern uint8 image1[ROW/2][COL/2];



#endif /* CODE_IMAGE_DEAL_H_ */
