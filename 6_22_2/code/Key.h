/*
 * Key.h
 *
 *  Created on: 2024年5月16日
 *      Author: icand
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_
#define KEY1                    (P22_3)
#define KEY2                    (P22_2)
#define KEY3                    (P22_1)
#define KEY4                    (P22_0)

#define SWITCH1                 (P33_13)
#define SWITCH2                 (P33_12)
extern int16 key_S_value,key_H_value,key_ok_value;
extern int16 LCD_page,LCD_item,LCD_sum,LCD_sum_max,LCD_sum_min,LCD_page_max,LCD_item_max,LCD_page_min,LCD_item_min;
extern int16 page,arrow_row,arrow_col;//控制菜单的俩变量
extern int16 page_last;//
void key(void);
void Page_Decide(void);
void key_action(void);
void LCD_value(void);
void LCD_show(void);
#endif /* CODE_KEY_H_ */
