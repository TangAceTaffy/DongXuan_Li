/*
 * UI.h
 *
 *  Created on: 2024Äê7ÔÂ28ÈÕ
 *      Author: icand
 */

#ifndef CODE_UI_H_
#define CODE_UI_H_
void DisplayMain(void);
void DisplaySpeed(void);
void DisplayPID(void);
void DisplayForsee(void);
void DisplayCircle(void);
void DisplayOthers(void);
void DisplayStart(void);
void DisplayCursor(void);
void UI_ContentKey(void);
extern unsigned char pagenum;
void UI_Content(void);
uint8 pagenumup(void);
uint8 pagenumdown(void);
void UI_Datapage();
void UI_DatapageKey();
void UI(void);
#endif /* CODE_UI_H_ */
