/*
 * Obstacle.c
 *
 *  Created on: 2024?那4??8??
 *      Author: icand
 */
#include "zf_common_headfile.h"
ObstacleTypeDef ObstacleType;
int Obstacle_flag=0;
int Distance_In_Cross;

void Obstacle_Detection(void)
{
    int i=1;
    int Obstacle_num=0;
    Obstacle_flag=0;
    if(RoadType==else_road && hight<=4)
    {
        // printf("111 \n\n");
        if(r_lose_num<10 && R_up_point_y>3 && L_up_point_y<3 && L_down_point_y<3 && r_border[R_up_point_x+4]-r_border[R_up_point_x-4]>15 &&
        ABS(r_border[R_up_point_x-9]-r_border[R_up_point_x-4])<4 && r_border[R_up_point_x+4]<image_w-20 && r_border[R_up_point_x-4]<image_w-20)
        {//????～?
        // printf("222 \n\n");
            i=1;
            Obstacle_num=0;
            for(;i<9;i++)
            {
                if(ABS(r_border[R_up_point_x-i-2]-r_border[R_up_point_x-1-i-2])<4 && r_border[R_up_point_x-i]<image_w-20 && r_border[R_up_point_x-i-1]<image_w-20 && ABS(r_border[R_up_point_x+1+i]-r_border[R_up_point_x+1+i+2])<4)
                {
                    
        // printf("333 \n\n");
                    Obstacle_num++;
                }
                if(Obstacle_num>5)
                {
                    // Garage_Flag=1;      //???車??


                    Obstacle_flag=1;
                    Distance_In_Cross=0;
                    printf("O1 \n");
                    break;

                }
            }
        }
        if(l_lose_num<10 && L_up_point_y>3 && R_up_point_y<3 && R_down_point_y<3 && l_border[L_up_point_x+4]-l_border[L_up_point_x-4]<-15 &&
        ABS(l_border[L_up_point_x-4]-l_border[L_up_point_x-9])<4 && l_border[L_up_point_x-4]>20 && l_border[L_up_point_x+4]>20)
        {//℅車??～?
        // printf("222 \n\n");
            i=1;
            Obstacle_num=0;
            for(;i<9;i++)
            {
                if(ABS(l_border[L_up_point_x-i-2]-l_border[L_up_point_x-1-i-2])<4 && l_border[L_up_point_x-i]>20 && l_border[L_up_point_x-i-1]>20 && ABS(l_border[L_up_point_x+1+i]-l_border[L_up_point_x+i+1+2])<4)
                {
        // printf("333 \n\n");
                    Obstacle_num++;
                }
                if(Obstacle_num>5)
                {
                    // Garage_Flag=1;      //???車??


                    Obstacle_flag=2;
                    Distance_In_Cross=0;
                    printf("O2 \n");
                    break;

                }
            }
        }
    }
}

void Obstacl_Deal(){
    if(Obstacle_flag==0){
        Obstacle_Detection();
    }
    if(Obstacle_flag==1){
        Round_Rightroud_num=1;
        gpio_set_level(LED, 0x1);
         if(Distance_In_Cross==0)
                    {
                        Distance_In_Cross=distance;//﹞???﹞???????
                    }
        if(distance-Distance_In_Cross>500){
            Round_Rightroud_num=0;
            Obstacle_flag=0;
            gpio_set_level(LED, 0x0);
        }

    }
    if(Obstacle_flag==2){
        Round_Leftroud_num=1;
        gpio_set_level(LED, 0x1);
         if(Distance_In_Cross==0)
                    {
                        Distance_In_Cross=distance;//﹞???﹞???????
                    }
        if(distance-Distance_In_Cross>500){
            Round_Leftroud_num=0;
            Obstacle_flag=0;
            gpio_set_level(LED, 0x0);
        }

    }

}
