/*
 * Key.h
 *
 *  Created on: 2024年5月16日
 *      Author: icand
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_
#define Up                       (P22_3)//KEY1
#define Down                     (P22_2)//KEY2
#define Enter                    (P22_1)//KEY3
#define Back                     (P22_0)//KEY4

#define SWITCH1                 (P33_13)
#define SWITCH2                 (P33_12)
extern uint8 SW1_Last;
extern uint8 SW2_Last;
//开关标志位
typedef enum
{
    key1_flag = 1,
    key2_flag = 2,
    key3_flag = 3,
    key4_flag = 4
};

uint8 Get_Key_flag(void);
void Key_Init(void);

//void Page_Decide(void);

#endif /* CODE_KEY_H_ */
