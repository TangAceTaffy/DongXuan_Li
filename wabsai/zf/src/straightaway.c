#include "zf_common_headfile.h"
int16  front_dot = 4;
int16  front_dot1 = 8;
int16  front_dot2 = 10;
int16  front_dot3 = 20;
int16  front_dot4 = 30;
int16  front_dot5 = 40;
int16  front_dot6 = 50;
int16  front_dot7 = 60;

          
int define_straight(){
    int K =0;

    float k1;
    float k2;
     float k3;
    float k4;
    float k5;
    float k6;
  
  
    k1=Float_ABS(center_line[front_dot]-center_line[front_dot3])/16.0;
    k2=Float_ABS(center_line[front_dot1]-center_line[front_dot3])/12.0;
     k3=Float_ABS(center_line[front_dot2]-center_line[front_dot4])/20.0;
    k4=Float_ABS(center_line[front_dot3]-center_line[front_dot5])/20.0;
    k5=Float_ABS(center_line[front_dot4]-center_line[front_dot6])/20.0;
    k6=Float_ABS(center_line[front_dot5]-center_line[front_dot7])/20.0;
    // printf("%f \n",k1);
    //  printf("%f \n",k2);
    //   printf("%f \n",k3);
    //    printf("%f \n",k4);
    //     printf("%f \n",k5);
    //      printf("%f \n",k6);
    //      printf("%f %f %f %f \n",k1-k3,k2-k4,k3-k5,k4-k6);

  


//    printf("r=%d\n",r_lose_num);
//    printf("l=%d\n",l_lose_num);
    
   
    int s = 1;
      
    if(Float_ABS(k1-k3)<0.21&&Float_ABS(k2-k4)<0.21&&Float_ABS(k3-k5)<0.21&&Float_ABS(k4-k6)<0.21&&(r_lose_num<10||l_lose_num<10)){
        s = 1;
        gpio_set_level(LED, 0x0);
    }
    else{
        s = 0;
     
        gpio_set_level(LED, 0x1);
    }
  if(angle>angle_max-10||angle<angle_min+10) s=2;

    return s;
}
int speed_straight(){
    int s =0;
    if(Average_Encoder>speed_maximum-100) s=0;
    else s=1;
    return s;
}
