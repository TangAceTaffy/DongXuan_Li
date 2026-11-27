#include "zf_common_headfile.h"

Str_Cross Cross_deal;
Enum_CrossType CrossType;
Enum_CrossProcess CrossProcess;
Str_RoadEN REN;
uint8_t Cross_num;
uint8_t Cross_row;
uint8_t Cross_col;
uint8_t Cross_Hang = 3;
uint8_t Cross_Hang_find = 15;
float Cross_Distance = 0;
int cross_end = 1;
uint8_t temp_lx = 0, temp_ly = 0;
uint8_t temp_rx = 0, temp_ry = 0;
/***************************************************************
十字检测

* 函数名称： Cross_Detection()//十字处理
* 功能说明： 十字检测
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：     检测一直开着  十字检测
 *******************************************************************/

void Cross_Detection() // 十字检测
{

   temp_lx = L_down_point_x - 3, temp_ly = L_down_point_y + 2;

   temp_rx = R_down_point_x - 3, temp_ry = R_down_point_y - 2;

   if (L_down_point_x > 5 && R_down_point_x > 5 &&
       abs(L_down_point_x - R_down_point_x) <= 10 &&
       (L_down_point_y - R_down_point_y) < -8)
   {
      // printf("C01\n");
      CrossType = Cro_ZHENG;
      // Cross_num=0;
      if ((bin_image[temp_lx - 1][temp_ly] > Threshold && bin_image[temp_lx - 2][temp_ly] > Threshold) && (bin_image[temp_rx - 1][temp_ry] > Threshold && bin_image[temp_rx - 2][temp_ry] > Threshold))
      {
         // printf("C02\n");
         if (min(temp_lx, temp_rx) == temp_lx)
            Cross_row = temp_lx - 2;
         else
            Cross_row = temp_rx - 2;
         if (Cross_row > image_w - 2)
            Cross_row = image_w - 2;
         cross_end = min(temp_lx, temp_rx) - 15;
         if (cross_end < 1)
            cross_end = ROW_START;
         for (; Cross_row >= cross_end; Cross_row--)
         {

            if (((l_border[Cross_row] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 1] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 2] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 3] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 4] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 5] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 6] >= image_w - 4) ||
                 (l_border[Cross_row] < 4 && r_border[Cross_row + 7] >= image_w - 4) ||
                 (l_border[Cross_row + 1] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 2] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 3] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 4] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 5] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 6] < 4 && r_border[Cross_row] >= image_w - 4) ||
                 (l_border[Cross_row + 7] < 4 && r_border[Cross_row] >= image_w - 4)) ||
                ((l_border[Cross_row] < 4 && r_border[Cross_row] - r_border[Cross_row - 1] >= 4) ||
                 (l_border[Cross_row] - l_border[Cross_row - 1] >= 4 && r_border[Cross_row] >= image_w - 4)))
            {

               Cross_num++;
            }
            // else
            //    {

            //       break;
            //    }
         }
      }
   }

   else if (L_down_point_x > 5 && R_down_point_x > 5 &&
            (R_down_point_x - L_down_point_x) > 10 &&
            (L_down_point_y - R_down_point_y) < -40)
   {
      // printf("C11\n");
      CrossType = Cro_RightLean;
      if ((image1[temp_lx - 1][temp_ly] > Threshold && image1[temp_lx - 2][temp_ly] > Threshold) && (image1[temp_rx - 1][temp_ry] > Threshold && image1[temp_rx - 2][temp_ry] > Threshold))
      {
         // printf("C12\n");
         float Cross_R_k1, Cross_R_k2;
         Cross_R_k1 = (float)(l_border[temp_lx - 1] - l_border[temp_lx - 3]) / 2;
         Cross_R_k2 = (float)(l_border[temp_lx - 2] - l_border[temp_lx - 4]) / 2;
         for (int i = 0; i <= 8; i++)
         {
            cross_end = temp_rx - 1 - i;
            if (cross_end < 1)
               cross_end = 1;
            if ( // abs(Cross_R_k1-Cross_R_k2)<0.3 &&
                l_border[temp_lx] - l_border[temp_lx - 1 - i] >= 0 &&
                r_border[cross_end] >= image_w - 4 &&
                abs(r_border[temp_rx + i + 4] - r_border[temp_rx + 4]) <= 5)
            { // 左下拐点往上几行斜率几乎相同；右下拐点往上丢线；右下拐点往下几行边界垂直
               Cross_num++;
            }
            // else
            // {
            //    break;
            // }
         }
      }
   }

   else if (L_down_point_x > 5 && R_down_point_x > 5 &&
            (L_down_point_x - R_down_point_x) > 10 &&
            (L_down_point_y - R_down_point_y) < -40)
   {
      // printf("C21\n");
      CrossType = Cro_LeftLean;
      if ((image1[temp_lx - 1][temp_ly] > Threshold && image1[temp_lx - 2][temp_ly] > Threshold) && (image1[temp_rx - 1][temp_ry] > Threshold && image1[temp_rx - 2][temp_ry] > Threshold))
      {

         // printf("C22\n");

         for (int i = 0; i <= 8; i++)
         {
            cross_end = temp_lx - 1 - i;
            if (cross_end < 1)
               cross_end = 1;
            if ( // abs(Cross_L_k1-Cross_L_k2)<0.3 &&
                r_border[temp_rx - 1 - i] - r_border[temp_rx] > 0 &&
                l_border[cross_end] <= 4 &&
                abs(l_border[temp_lx + i + 4] - l_border[temp_lx + 4]) <= 5)
            { // 右下拐点往上几行斜率几乎相同；左下拐点往上丢线；左下拐点往下几行边界垂直
               // printf("C23\n");
               Cross_num++;
            }
            // else
            // {
            //    break;
            // }
         }
      }
   }

   else
      CrossType = Cro_else;

   if (Cross_num >= Cross_Hang)
   {
      // printf("Ly=%d  Ry=%d\nLx=%d  Rx=%d\n\n",temp_ly,temp_ry,temp_lx,temp_rx);
      Cross_deal.Cross_flag = 1; // 十字flag
      CrossProcess = Find_Cross;
      RoadType = Cross_Road;
      Cross_row = ROW_START; // 清外循环
      Cross_Distance = 0;
      Cross_num = 0;

      gpio_set_level(LED, 0x1);
   }
   else
   {
      Cross_num = 0;
   }
}

/****************************************************************
十字处理

* 函数名称：Cross_Process()//十字处理
* 功能说明： 十字处理
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：与其他芯片不同，需要给补线做出保护，不然超出图像范围就容易卡死单片机
*******************************************************************/
int Cross_last_point_R = 0;
int Cross_last_point_L = 0;

void Cross_Process() // 十字处理
{
   uint8_t SC_MUN = 5;
   float LeftCrossSlope;
   float RightCrossSlope;
   int flag_1;

   switch (CrossProcess)
   {
   case Find_Cross:
   {

      Round_Leftroud_num = 0;
      Round_Rightroud_num = 0;

      if (Cross_Distance == 0)
         Cross_Distance = distance;
      Cross_num = 0;
      if (R_down_point_y > 40 && L_down_point_y > 3 && L_down_point_y < 120 && L_down_point_x > 12 && R_down_point_x > 12 && ABS(L_down_point_x - R_down_point_x) < 25)
      { // 找到左右下角点并且没有左右上角点
         printf("c3 \n");
         Cross_last_point_R = R_down_point_y;
         Cross_last_point_L = L_down_point_y;

         Round_Leftroud_num = 0;
         Round_Rightroud_num = 0;
         if (R_down_point_y - L_down_point_y != 0 && R_down_point_x - L_down_point_x != 0)
         {

            float Cross_Slope;
            Cross_Slope = (float)(R_down_point_x - L_down_point_x) / (R_down_point_y - L_down_point_y);

            float Cross_Vertical_Slope;
            Cross_Vertical_Slope = (float)(-1 / Cross_Slope);

            for (int i = max(L_down_point_x, R_down_point_x); i > 0; i--)
            {
               int Right_Cross_Slope = (float)(R_down_point_x - i) * Cross_Slope + R_down_point_y;
               if (Right_Cross_Slope < 4)
               {
                  Right_Cross_Slope = 4;
               }
               if (Right_Cross_Slope > image_w - 4)
               {
                  Right_Cross_Slope = image_w - 4;
               }
               if (i < R_down_point_x)
                  r_border[i] = Right_Cross_Slope;

               int Left_Cross_Slope = (float)(L_down_point_x - i) * Cross_Slope + L_down_point_y;
               if (Left_Cross_Slope < 4)
               {
                  Left_Cross_Slope = 4;
               }
               if (Left_Cross_Slope > image_w - 4)
               {
                  Left_Cross_Slope = image_w - 4;
               }
               if (i < L_down_point_x)
                  l_border[i] = Left_Cross_Slope;
            }
            for(int i=min(L_down_point_x, R_down_point_x);i<40;i++){
              l_border[i]=L_down_point_y;
              r_border[i]=R_down_point_y;

            }
         }
         else
         {

            for (int i = min(L_down_point_x, R_down_point_x); i > 5; i--)
            {

               r_border[i] = R_down_point_y;

               l_border[i] = L_down_point_y;
            }
         }
      }
      else
      {
         // printf("C4 \n");
         // if (L_up_point_y > 3 && L_up_point_y < 120)
         // { // 只有左上
         //    // printf("c34 \n");
         //    for (int i = 0; i < 80; i++)
         //    {
         //       l_border[i] = L_up_point_y;
         //       r_border[i] = L_up_point_y + 60;
         //    }
         //    Round_Leftroud_num = 0;
         //    Round_Rightroud_num = 0;
         // }
         // if (R_up_point_y > 40 && R_down_point_y < 3)
         // { // 只有右上
         //    // printf("c35 \n");
         //    for (int i = 0; i < 80; i++)
         //    {
         //       r_border[i] = R_up_point_y;
         //       l_border[i] = R_up_point_y - 60;
         //    }
         //    Round_Leftroud_num = 0;
         //    Round_Rightroud_num = 0;
         // }
         // if (L_up_point_y > 3 && L_up_point_y < 120 && R_up_point_y > 40 && (L_down_point_y < 4 || R_down_point_y < 4 || R_down_point_x < R_up_point_x || L_down_point_x < L_up_point_x))
         // { // 左右上都有
         //    printf("c33 \n");
         //    for (int i = 0; i < 80; i++)
         //    {
         //       l_border[i] = L_up_point_y;
         //       r_border[i] = R_up_point_y;

         //       Round_Leftroud_num = 0;
         //       Round_Rightroud_num = 0;
         //    }
         // }
         // if (L_down_point_y > 10 && L_down_point_y < 80 && L_up_point_y < 80 && L_up_point_x >= 10 && L_up_point_x < L_down_point_x) // 找到左下角点并且有左上角点
         // {
         //    printf("c31 \n");
         //    for (int i = L_up_point_x; i < L_down_point_x; i++)
         //    {
         //       float K = (float)(L_down_point_y - L_up_point_y) / (L_down_point_x - L_up_point_x);
         //       l_border[i] = (int)(L_up_point_y + (i - L_up_point_x) * K);

         //       Round_Rightroud_num = 2;
         //       Round_Leftroud_num = 0;
         //    }
         // }
         // if (R_down_point_y > 80 && R_up_point_y > 80 && R_up_point_x >= 10 && R_up_point_x < R_down_point_x) // 找到右下角点并且有右上角点
         // {
         //    printf("c32 \n");
         //    for (int i = R_up_point_x; i < R_down_point_x; i++)
         //    {
         //       float K = (float)(R_down_point_y - R_up_point_y) / (R_down_point_x - R_up_point_x);

         //       r_border[i] = (int)(R_up_point_y + (i - R_up_point_x) * K);

         //       Round_Leftroud_num = 2;
         //       Round_Rightroud_num = 0;
         //    }
         // }
         // if (R_down_point_y > 3 && L_down_point_x < 20 && (R_up_point_x < 4 || R_up_point_x > R_down_point_x) && R_down_point_x < 100 && R_down_point_x > 20 && R_down_point_x > L_up_point_x)
         // { // 只有右下
         //    printf("C12 \n");
         //    float K = (float)(r_border[R_down_point_x + 5] - r_border[R_down_point_x + 15]) / 10.0;

         //    for (int i = R_down_point_x; i > 0; i--)
         //    {
         //       r_border[i] = (R_down_point_y - round((i - R_down_point_x) * K));
         //    }

         //    Round_Leftroud_num = 2;
         //    Round_Rightroud_num = 0;
         // }
         // if (L_down_point_y > 3 && R_down_point_x < 20 && (L_up_point_x < 4 || L_up_point_x > L_down_point_x) && L_down_point_x < 100 && L_down_point_x > 20 && L_down_point_x > R_up_point_x)
         // { // 只有左下
         //    printf("C13 \n");
         //    float K = (float)(l_border[L_down_point_x + 5] - l_border[L_down_point_x + 15]) / 10.0;

         //    for (int i = L_down_point_x; i > 0; i--)
         //    {
         //       l_border[i] = (L_down_point_y - round((i - L_down_point_x) * K));
         //    }

         //    Round_Rightroud_num = 2;
         //    Round_Leftroud_num = 0;
         // }
         // 补丁
         if (r_lose_num > l_lose_num+10)
         {
          Round_Rightroud_num=2;
         }
         if (l_lose_num > r_lose_num+10)
         {
         Round_Leftroud_num=2;
         }
         else {
            Round_Leftroud_num==0;
            Round_Rightroud_num==0;
         }
         flag_1 = 0;
      }

      if ((distance - Cross_Distance) > 800) // 600
      {                                      // 判断出十字
         CrossProcess = In_Cross;
         Cross_Distance == 0;
         Round_Leftroud_num=0;
         Round_Rightroud_num=0;

         gpio_set_level(LED, 0x0);
      }
      flag_1 = 0;
      break;
   }

   case In_Cross:
   {

      if (Cross_Distance == 0)
         Cross_Distance = distance;

      if ((distance - Cross_Distance) > 10)
      {
         CrossProcess = Out_Cross;

         // gpio_set_level(LED, 0x1);
      }
      break;
   }

   case Out_Cross:
   {

      Round_Leftroud_num = 0;
      Round_Rightroud_num = 0;

      Cross_deal.Cross_flag = 0; // 十字flag
      RoadType = else_road;

      Obstacle_flag = 0;

      gpio_set_level(LED, 0x0);
      break;
   }
   default:
   {
      break;
   }
   }
}
/***************************************************************
十字处理

* 函数名称： Cross_Detection()//十字处理
* 功能说明： 十字处理外部调用
* 参数说明：
* 函数返回： void
* 修改时间：
* 备 注：
*******************************************************************/
void Cross_Deal() // 十字检测
{
   if (Cross_deal.Cross_flag == 0)
   {
      have_element_flag = 0;

      Cross_Detection(); // 十字检测
   }
   else
   {
      Cross_Process();

      have_element_flag = 1;
   }
}
