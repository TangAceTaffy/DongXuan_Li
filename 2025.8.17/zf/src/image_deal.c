#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include "zf_common_headfile.h"
#include "image_data.h"

extern void captureAndUpdateImage();  // 声明 C++ 函数
extern unsigned char image1[120][160]; // 声明为二维数组

extern int getiamge1;
int defineSR;
int speedSR;
unsigned char Threshold=110;
int g_threshold_value=35;//差比和判断阈值
int otsu_flag = 1;

void image_deal(){


    
      processImage();

      unsigned char* data = getImageData();  // 获取图像数据
        
    
      
        
        protect();

        image_process();
if(distance>=1600){
        Roadtype_check();
}
        middle_line();
        

        defineSR=define_straight();
        speedSR=speed_straight();

        error_get();
      
// //****************************************************************//屏幕中显示图像****************************************************************
        //   ips200_show_gray_image(0,0,image1,160,120);
        

       
        // int b;
        // int l;
        // int r;
        // for (int i = 0; i < 120; ++i) {
           
        //     for (int j = 0; j < 160; ++j) {
        //         r=r_border[i];
        //         l=l_border[i];
        //         b=center_line[i];
        //         image0[i][b]=1;
        //         image0[i][l]=2;
        //         image0[i][r]=3;
        //         ips200_draw_point(b,i,RGB565_GREEN);
        //         ips200_draw_point(r,i,RGB565_BLUE);
        //         ips200_draw_point(l,i,RGB565_RED);
        //         ips200_draw_point(b+1,i,RGB565_GREEN);
        //         ips200_draw_point(r+1,i,RGB565_BLUE);
        //         ips200_draw_point(l+1,i,RGB565_RED);
            
	// 			if(i==L_down_point_x) image0[i][L_down_point_y]=4;
	// 			if(i==R_down_point_x) image0[i][R_down_point_y]=5;
	// 			if(i==L_up_point_x) image0[i][L_up_point_y]=6;
	// 			if(i==R_up_point_x) image0[i][R_up_point_y]=7; 
        //       if(image0[i][j]==0) printf("..");
	// 		  if(image0[i][j]==1) printf("1");
	// 		  if(image0[i][j]==2) printf("2");
	// 		  if(image0[i][j]==3) printf("3");
	// 		  if(image0[i][j]==4) printf("4");
	// 		  if(image0[i][j]==5) printf("5");
	// 		  if(image0[i][j]==6) printf("6");
	// 		  if(image0[i][j]==7) printf("7");
        // //    printf("%d ",bin_image[i][j]);
             
        //   }
        //   printf("\n");
        //  }
        // memset(image0, 0, sizeof(image0));
	// 	  	printf("\n");

// // //****************************************************************//显示图像元素识别****************************************************************     
      
// //               ips200_show_int(200, 120,RoundProcess , 6);
              // ips200_show_int(200, 120,CrossProcess , 6);
//             //  ips200_show_float(200,150,distance,6,2);
          
// // //             //  ips200_show_int(200,80,Round_num,3);

// // // // printf("Lx=%d  Rx=%d\nLy=%d  Ry=%d\n",Inflection_point.L_down_point.y,Inflection_point.R_down_point.y,Inflection_point.L_down_point.x,Inflection_point.R_down_point.x);


      // int rtype = 0;
      // switch(RoadType){
      //    case else_road:ips200_show_string(0,11*16,"else_road");break;
      //    case Fork_Road:ips200_show_string(0,11*16,"Fork_Road");break;
      //    case Cross_Road:ips200_show_string(0,11*16,"Cross_Road");break;
      //    case Round_Road:ips200_show_string(0,11*16,"Round_Road");break;
      //    case Ramp:ips200_show_string(0,11*16,"Ramp");break;          //坡道
      //    case Barrier:ips200_show_string(0,11*16,"Barrier");break;      //障碍物
      //    case Garage:ips200_show_string(0,11*16,"Garage");break;
      //    case Start:ips200_show_string(0,11*16,"Start");break;
      // }
     

// 打印角点
                     // if(L_down_point_x)
                     //   {
                     //   for(int i=L_down_point_x-3;i<L_down_point_x+4;i++)
                     //      {
                     //       ips200_draw_point(L_down_point_y,i,RGB565_CYAN);
                     //       ips200_draw_point(L_down_point_y+1,i,RGB565_CYAN);
                     //      }
                     //  }
                     //  if(L_up_point_x)
                     //  {
                     //      for(int i=L_up_point_x-3;i<L_up_point_x+4;i++)
                     //      {
                     //       ips200_draw_point(L_up_point_y,i,RGB565_PINK);
                     //       ips200_draw_point(L_up_point_y+1,i,RGB565_PINK);
                     //      }
                     //  }
                     //  if(R_down_point_x)
                     //  {
                     //      for(int i=R_down_point_x-3;i<R_down_point_x+4;i++)
                     //      {
                     //       ips200_draw_point(R_down_point_y,i,RGB565_PURPLE);
                     //       ips200_draw_point(R_down_point_y+1,i,RGB565_PURPLE);
                     //      }
                     //  }
                     //  if(R_up_point_x)
                     //  {
                     //      for(int i=R_up_point_x-3;i<R_up_point_x+4;i++)
                     //      {
                     //       ips200_draw_point(R_up_point_y,i,RGB565_YELLOW);
                     //       ips200_draw_point(R_up_point_y+1,i,RGB565_YELLOW);
                     //      }
                     //  }



      
 

}