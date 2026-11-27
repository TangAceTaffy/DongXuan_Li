#include "zf_common_headfile.h"
//显示函数



void display(void)
{

     key_action();
     Page_Decide();
     switch(page)
     {
         case 1://第一页
         {
             tft180_displayimage03x((mt9v03x_image[0]), COL/2, ROW/2);  //图像显示 w:80h:50
             int i;
             int l;
             int r;
             int b;
             for(i=0;i< ROW/2;i++)
             {
                 r=Boundary.RightEdge[i];
                 l=Boundary.LeftEdge[i];
                 b=Boundary.MiddleLine[i];
                 tft180_draw_point(b,i,RGB565_BLACK);
                 tft180_draw_point(r,i,RGB565_BLUE);
                 tft180_draw_point(l,i,RGB565_BLUE);
                 tft180_draw_point(b+1,i,RGB565_BLACK);
                 tft180_draw_point(r+1,i,RGB565_BLUE);
                 tft180_draw_point(l+1,i,RGB565_BLUE);
             }
             if(Obstacle.row1)
             {
                 for(int i=Obstacle.row1-2;i<Obstacle.row1+2;i++)
                 {
                         tft180_draw_point(Boundary.RightEdge[Obstacle.row1],i,RGB565_PURPLE);
                         tft180_draw_point(Boundary.RightEdge[Obstacle.row1]+1,i,RGB565_PURPLE);
                 }
             }
                 if(Inflection_point.L_down_point.x)
                 {
                     for(int i=Inflection_point.L_down_point.x-3;i<Inflection_point.L_down_point.x+4;i++)
                     {
                         tft180_draw_point(Inflection_point.L_down_point.y,i,RGB565_RED);
                         tft180_draw_point(Inflection_point.L_down_point.y+1,i,RGB565_RED);
                     }
                 }
                 if(Inflection_point.L_up_point.x)
                 {
                     for(int i=Inflection_point.L_up_point.x-3;i<Inflection_point.L_up_point.x+4;i++)
                     {
                         tft180_draw_point(Inflection_point.L_up_point.y,i,RGB565_YELLOW);
                         tft180_draw_point(Inflection_point.L_up_point.y+1,i,RGB565_YELLOW);
                     }
                 }
                 if(Inflection_point.R_down_point.x)
                 {
                     for(int i=Inflection_point.R_down_point.x-3;i<Inflection_point.R_down_point.x+4;i++)
                     {
                         tft180_draw_point(Inflection_point.R_down_point.y,i,RGB565_RED);
                         tft180_draw_point(Inflection_point.R_down_point.y+1,i,RGB565_RED);
                     }
                 }
                 if(Inflection_point.R_up_point.x)
                 {
                     for(int i=Inflection_point.R_up_point.x-3;i<Inflection_point.R_up_point.x+4;i++)
                     {
                         tft180_draw_point(Inflection_point.R_up_point.y,i,RGB565_YELLOW);
                         tft180_draw_point(Inflection_point.R_up_point.y+1,i,RGB565_YELLOW);
                     }
                 }
                 for(uint8 h=0; h<COL_END ; h++)
                 {
                     tft180_draw_point(h,Boundary.EndLine,RGB565_BLACK);
                 }
                     tft180_show_string(0, 50, "Roadtype:");
                     tft180_show_int(70, 50,RoadType,1);

                     tft180_show_string(0, 70, "Sequence:");
                     tft180_show_int(0, 90,Elements_Sequence[0],2);
                     tft180_show_int(20, 90,Elements_Sequence[1],2);
                     tft180_show_int(40, 90,Elements_Sequence[2],2);
                     tft180_show_int(60, 90,Elements_Sequence[3],2);
                     tft180_show_int(80, 90,Elements_Sequence[4],2);

                     tft180_show_string(0, 110, "Next:");
                     tft180_show_int(70, 110,Elements_Sequence[Elements_Current_Sequence],2);

//                     tft180_show_string(0, 125, "Distance:");
//                     tft180_show_int(0,125,RoundProcess,1);
                     //tft180_show_int(30,125,check_point,2);
//                     tft180_show_int(60,125,angke_yaw,3);

                     tft180_show_int(60, 125,SUM,3);

//                     tft180_show_int(60, 125,Distance_In_Round,3);
//                     tft180_show_int(60,125,angke_yaw,3);
                     //tft180_show_int(60,125angke_yaw,Kd,2);
                     //tft180_show_int(0, 140,Distance_Leave_Round2,4);
             break;
         }
         case 2:
         {
             tft180_show_string(0,arrow_row,"->");
             tft180_show_int(20, 0,Elements_Sequence[0],2);
             tft180_show_int(20, 20,Elements_Sequence[1],2);
             tft180_show_int(20, 40,Elements_Sequence[2],2);
             tft180_show_int(20, 60,Elements_Sequence[3],2);
             tft180_show_int(20, 80,Elements_Sequence[4],2);
             break;
         }
         case 3:
         {

             break;
         }
         case 4:
         {

             break;
         }
     }


//     tft180_show_int(60, 135, angke_yaw, 3);
//     tft180_show_int(0,100,error,3);//left + right -
//	 tft180_show_int(60, 100, Left_Encoder, 3);//左编码器显示
//   tft180_show_int(60, 120, Right_Encoder, 3);//右编码器显示

//	 tft180_show_int(0, 60,RoadType, 1);
//   tft180_show_int(0, 60,Boundary.MiddleLine[ROW_END-2],3);
//   tft180_show_int(60, 60,Boundary.MiddleLine[ROW_END],3);
//   tft180_show_int(90, 60, ABS(Boundary.MiddleLine[ROW_END]-Boundary.MiddleLine[ROW_END-2]), 3);
//   tft180_show_int(0, 80, Round.Round_flag,1);
//   tft180_show_int(30, 80,Cross_deal.Cross_flag,1);
//     tft180_show_int(60, 80,RoundProcess,1);
//    // tft180_show_int(0, 60,RoadType,1);





//




//     tft180_show_int(0, 60,Elements_Sequence[Elements_Current_Sequence],2);

//     tft180_show_int(60, 60,Obstacle.temp_count1_print,2);
//     tft180_show_int(90, 60,Obstacle.temp_count2_print,1);
//     tft180_show_int(40, 60, Boundary.StartLine,2);
//	 tft180_show_int(90, 60,Ramp_Distance, 3);
//	 //tft180_show_float(30, 60,Kp, 2, 2);
//	 tft180_show_int(0, 60, Boundary.Right_Edge_num, 3);

//	 tft180_show_int(30, 60, Boundary.L_EndLine, 3);
//     tft180_show_int(30, 60, Boundary.RowLose[15-2], 1);
//	 tft180_show_int(60, 60, Cross_num, 2);
//	 tft180_show_int(30, 60, R_edge_lose, 3);
//	 tft180_show_int(0, 60,row1_right_flag, 1);
//	 tft180_show_int(20, 60,row2_right_flag,1);

//	 tft180_show_int(40, 60,row1_left_flag, 1);
//	 tft180_show_int(60, 60,row2_left_flag, 1);
//	 tft180_show_float(40, 60,Kp, 2, 2);
//	 tft180_show_int(60, 100,ElseRoadType,1);
//	 tft180_show_int(0, 120,Boundary.RowLose[25],1);
//	 tft180_show_int(60, 100,RoundProcess, 1);
//	 tft180_show_int(60, 120,Distance_Leave_Round2, 3);

//	 tft180_show_int(90, 60,Obstacle_Mid, 3);
	 //tft180_show_int(68, 90,Obstacle_Check_Point, 3);
//	 tft180_show_int(68, 60,distance-Obstacle_Check_Point, 3);
//	 tft180_show_int(60, 60,row1_flag, 3);
   
	//以下为扫线显示，拐点显示


}
