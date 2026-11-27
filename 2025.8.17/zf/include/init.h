#ifndef INIT_H
#define INIT_H
#include "zf_common_headfile.h"
#define LED "/dev/zf_driver_gpio_beep"
extern uint8_t ALLSTART;
extern uint8_t data;
void init_and_set_all(void);
extern unsigned char   track_Width[ROW];
#endif /* INIT_H */
