/*
 * Zebra.h
 *
 *  Created on: 2024年4月5日
 *      Author: icand
 */

#ifndef CODE_ZEBRA_H_
#define CODE_ZEBRA_H_
//uint8 Garage_Deal(unsigned char Col_START,unsigned char Col_END) //入库判断
void Garage_Deal(unsigned char Col_START,unsigned char Col_END);
extern float Garage_Flag;
extern float Garage_Check_Point;
extern int SUM;
void protect(void);


#endif /* CODE_ZEBRA_H_ */
