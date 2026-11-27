#include "zf_common_headfile.h"
#include "init.h"
uint8_t ALLSTART=0;
//用于无线串口通信
uint8_t data=0;
unsigned char   track_Width[ROW];
void init_and_set_all(void)
{
      ALLSTART=0;
      //无刷电机初始化
      // pwm88 = PWM_GTIM_Create(88, 0b11, 2, 10000, 0);    //88通道2
      // PWM_GTIM_enable(pwm88);

      // pwm89 = PWM_GTIM_Create(89, 0b11, 3, 10000, 0);    //89通道3
      // PWM_GTIM_enable(pwm89);

      //电机初始化
      
      // gpio_set_level(MOTOR1_DIR, 1);                                    
      // pwm_set_duty(MOTOR1_PWM, 0);      

      // gpio_set_level(MOTOR2_DIR, 1);                                  
      // pwm_set_duty(MOTOR2_PWM, 0); 

      //舵机初始化

      ips200_init("/dev/fb0");
      pwm_set_duty(SERVO_MOTOR1_PWM,steeringPWM_MID);
  






      gpio_set_level(LED, 0x0);
       
     

      //编码器初始化
      
      
      
      for(int Round_row=ROW_END;Round_row>=ROW_START+5;Round_row--)
      {
          Round.Track_Width_forRound[Round_row]=(int)(0.8*Round_row+24);//(1.7*Round_row+5.8); //计算  圆环路宽
      }

      for(int i=ROW_END;i>0 ;i--)
      {
            track_Width[i]=(int)(i*0.9+24); //计算  路宽
      }

      ALLSTART=1;
}
