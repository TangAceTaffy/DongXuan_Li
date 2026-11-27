#include "zf_common_headfile.h"
#include <signal.h>
#include <unistd.h>
void clean(){
    Round.Round_flag=0;
    Cross_deal.Cross_flag=0;
    Obstacle_flag=0;
    Ramp_deal.Ramp_flag=0;
    Brush_Stop_flag=0;
    Brushless_Stop_flag=0;
    Garage_Flag=0;
     gpio_set_level(LED, 0x0);
    
      distance=0;
        left_motor_pid(0);
      right_motor_pid(0);
      pwm_set_duty(pwm_esc_2,200);
}
