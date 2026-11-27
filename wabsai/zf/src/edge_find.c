#include <stdio.h>
#include <stdint.h>
#include "zf_common_headfile.h"
#include "image_data.h"

//-------------------------------------------------------------------------------------------------------------------
//  简介:八邻域图像处理

//------------------------------------------------------------------------------------------------------------------


/*
函数名称：int my_abs(int value)
功能说明：求绝对值
参数说明：
函数返回：绝对值
修改时间：2022年9月8日
备    注：
example：  my_abs( x)；
 */
int my_abs(int value)
{
if(value>=0) return value;
else return -value;
}

int16 limit_a_b(int16 x, int a, int b)
{
    if(x<a) x = a;
    if(x>b) x = b;
    return x;
}

/*
函数名称：int16 limit(int16 x, int16 y)
功能说明：求x,y中的最小值
参数说明：
函数返回：返回两值中的最小值
修改时间：2022年9月8日
备    注：
example：  limit( x,  y)
 */
int16 limit1(int16 x, int16 y)
{
	if (x > y)             return y;
	else if (x < -y)       return -y;
	else                return x;
}



/*
函数名称：void get_start_point(uint8 start_row)
功能说明：寻找两个边界的边界点作为八邻域循环的起始点
参数说明：输入任意行数
函数返回：无
修改时间：2022年9月8日
备    注：
example：  get_start_point(image_h-2)
 */
uint8 start_point_l[2] = { 0 };//左边起点的x，y值
uint8 start_point_r[2] = { 0 };//右边起点的x，y值
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0,l_found = 0,r_found = 0;
	//清零
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

		//从中间往左边，先找起点
	for (i = image_w / 2 + 60; i > border_min; i--)
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		// if((difference_sum(image1[start_row][i],image1[start_row][i - 1])>g_threshold_value&&mark_middle_num(image1[start_row][i],image1[start_row][i - 1],Threshold) )|| (image1[start_row][i] > Threshold && image1[start_row][i - 1] == 0))

		{
			// printf("Find left image[%d][%d]\n", start_row,i);
			l_found = 1;
			break;
		}

	}

	for (i = image_w / 2 -60; i < border_max; i++)
	{
		start_point_r[0] = i;//x
		start_point_r[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i + 1] == 0)
		// if((difference_sum(image1[start_row][i],image1[start_row][i + 1])>g_threshold_value&&mark_middle_num(image1[start_row][i],image1[start_row][i + 1],Threshold))|| (image1[start_row][i] > Threshold && image1[start_row][i + 1] == 0))


		{
			// printf("Find right image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if(l_found&&r_found)return 1;
	else {
		//printf("未找到起点\n");
		return 0;
	} 
}

/*
函数名称：void search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

功能说明：八邻域正式开始找右边点的函数，输入参数有点多，调用的时候不要漏了，这个是左右线一次性找完。
参数说明：
break_flag_r			：最多需要循环的次数
(*image)[image_w]		：需要进行找点的图像数组，必须是二值图,填入数组名称即可
					   特别注意，不要拿宏定义名字作为输入参数，否则数据可能无法传递过来
*l_stastic				：统计左边数据，用来输入初始数组成员的序号和取出循环次数
*r_stastic				：统计右边数据，用来输入初始数组成员的序号和取出循环次数
l_start_x				：左边起点横坐标
l_start_y				：左边起点纵坐标
r_start_x				：右边起点横坐标
r_start_y				：右边起点纵坐标
hightest				：循环结束所得到的最高高度
函数返回：无
修改时间：2022年9月25日
备    注：
example：
	search_l_r((uint16)USE_num,image,&data_stastics_l, &data_stastics_r,start_point_l[0],
				start_point_l[1], start_point_r[0], start_point_r[1],&hightest);
 */
#define USE_num	image_h*3	//定义找点的数组成员个数按理说300个点能放下，但是有些特殊情况确实难顶，多定义了一点

 //存放点的x，y坐标
uint16 points_l[(uint16)USE_num][2] = { {  0 } };//左线
uint16 points_r[(uint16)USE_num][2] = { {  0 } };//右线
uint16 dir_r[(uint16)USE_num] = { 0 };//用来存储右边生长方向
uint16 dir_l[(uint16)USE_num] = { 0 };//用来存储左边生长方向
uint16 data_stastics_l = 0;//统计左边找到点的个数
uint16 data_stastics_r = 0;//统计右边找到点的个数
uint8 hightest = 0;//最高点
uint8 hight = 0;
void search_l_r(uint16 break_flag, uint8(*image)[image_w], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest)
{

	uint8 i = 0, j = 0;

	//左边变量
	uint8 search_filds_l[8][2] = { {  0 } };
	uint8 index_l = 0;
	uint8 temp_l[8][2] = { {  0 } };
	uint8 center_point_l[2] = {  0 };
	uint16 l_data_statics;//统计左边
	//定义八个邻域
	static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//这个是顺时针

	//右边变量
	uint8 search_filds_r[8][2] = { {  0 } };
	uint8 center_point_r[2] = { 0 };//中心坐标点
	uint8 index_r = 0;//索引下标
	uint8 temp_r[8][2] = { {  0 } };
	uint16 r_data_statics;//统计右边
	//定义八个邻域
	static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//这个是逆时针

	l_data_statics = *l_stastic;//统计找到了多少个点，方便后续把点全部画出来
	r_data_statics = *r_stastic;//统计找到了多少个点，方便后续把点全部画出来

	//第一次更新坐标点  将找到的起点值传进来
	center_point_l[0] = l_start_x;//x
	center_point_l[1] = l_start_y;//y
	center_point_r[0] = r_start_x;//x
	center_point_r[1] = r_start_y;//y

		//开启邻域循环
	while (break_flag--)
	{

		//左边
		for (i = 0; i < 8; i++)//传递8F坐标
		{
			search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
			search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
		}
		//中心坐标点填充到已经找到的点内
		points_l[l_data_statics][0] = center_point_l[0];//x
		points_l[l_data_statics][1] = center_point_l[1];//y
		l_data_statics++;//索引加一

		//右边
		for (i = 0; i < 8; i++)//传递8F坐标
		{
			search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
			search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
		}
		//中心坐标点填充到已经找到的点内
		points_r[r_data_statics][0] = center_point_r[0];//x
		points_r[r_data_statics][1] = center_point_r[1];//y

		index_l = 0;//先清零，后使用
		for (i = 0; i < 8; i++)
		{
			temp_l[i][0] = 0;//先清零，后使用
			temp_l[i][1] = 0;//先清零，后使用
		}

		//左边判断
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0
				&& image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
	// 		if((difference_sum(image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]],image[search_filds_l[i][1]][search_filds_l[i][0]])>g_threshold_value
	// 		&&mark_middle_num(image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]],image[search_filds_l[i][1]][search_filds_l[i][0]],Threshold) )||
	// (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0&& image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] > Threshold))



			{
				temp_l[index_l][0] = search_filds_l[(i)][0];
				temp_l[index_l][1] = search_filds_l[(i)][1];
				index_l++;
				dir_l[l_data_statics - 1] = (i);//记录生长方向
			}

			if (index_l)
			{
				//更新坐标点
				center_point_l[0] = temp_l[0][0];//x
				center_point_l[1] = temp_l[0][1];//y
				for (j = 0; j < index_l; j++)
				{
					if (center_point_l[1] > temp_l[j][1])
					{
						center_point_l[0] = temp_l[j][0];//x
						center_point_l[1] = temp_l[j][1];//y
					}
				}
			}

		}
		if ((points_r[r_data_statics][0]== points_r[r_data_statics-1][0]&& points_r[r_data_statics][0] == points_r[r_data_statics - 2][0]
			&& points_r[r_data_statics][1] == points_r[r_data_statics - 1][1] && points_r[r_data_statics][1] == points_r[r_data_statics - 2][1])
			||(points_l[l_data_statics-1][0] == points_l[l_data_statics - 2][0] && points_l[l_data_statics-1][0] == points_l[l_data_statics - 3][0]
				&& points_l[l_data_statics-1][1] == points_l[l_data_statics - 2][1] && points_l[l_data_statics-1][1] == points_l[l_data_statics - 3][1]))
		{
			//printf("三次进入同一个点，退出\n");
			break;
		}
		if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
			&& my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
			)
		{
			//printf("\n左右相遇退出\n");	
			*hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;//取出最高点
			hight=*hightest;
			// printf("\n%d",*hightest);
			break;
		}
		if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
		{
			
			continue;//如果左边比右边高了，左边等待右边
		}
		if (dir_l[l_data_statics - 1] == 7
			&& (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))//左边比右边高且已经向下生长了
		{
			//printf("\n左边开始向下了，等待右边，等待中... \n");
			center_point_l[0] = points_l[l_data_statics - 1][0];//x
			center_point_l[1] = points_l[l_data_statics - 1][1];//y
			l_data_statics--;
		}
		r_data_statics++;//索引加一

		index_r = 0;//先清零，后使用
		for (i = 0; i < 8; i++)
		{
			temp_r[i][0] = 0;//先清零，后使用
			temp_r[i][1] = 0;//先清零，后使用
		}

		//右边判断
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
				&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)

		// 		if((difference_sum(image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]],image[search_filds_r[i][1]][search_filds_r[i][0]])>g_threshold_value
		// 	&&mark_middle_num(image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]],image[search_filds_r[i][1]][search_filds_r[i][0]],Threshold)  )||
	    // (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] > Threshold))



			{
				temp_r[index_r][0] = search_filds_r[(i)][0];
				temp_r[index_r][1] = search_filds_r[(i)][1];
				index_r++;//索引加一
				dir_r[r_data_statics - 1] = (i);//记录生长方向
				//printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
			}
			if (index_r)
			{

				//更新坐标点
				center_point_r[0] = temp_r[0][0];//x
				center_point_r[1] = temp_r[0][1];//y
				for (j = 0; j < index_r; j++)
				{
					if (center_point_r[1] > temp_r[j][1])
					{
						center_point_r[0] = temp_r[j][0];//x
						center_point_r[1] = temp_r[j][1];//y
					}
				}

			}
		}


	}


	//取出循环次数
	*l_stastic = l_data_statics;
	*r_stastic = r_data_statics;

}
/*
函数名称：void get_left(uint16 total_L)
功能说明：从八邻域边界里提取需要的边线
参数说明：
total_L	：找到的点的总数
函数返回：无
修改时间：2022年9月25日
备    注：
example： get_left(data_stastics_l );
 */
uint8 l_border[image_h];//左线数组
uint8 r_border[image_h];//右线数组
uint8 center_line[image_h];//中线数组
int r_lose_num;
int l_lose_num;
int r_lose_low_num;
int l_lose_low_num;
void get_left(uint16 total_L)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	//初始化
	for (i = 0;i<image_h;i++)
	{
		l_border[i] = border_min;
	}
	h = image_h - 2;
	//左边
	l_lose_num=60;
	l_lose_low_num=60;
	for (j = 0; j < total_L; j++)
	{
		
		if (points_l[j][1] == h)
		{
			l_border[h] = points_l[j][0]+1;
			// printf("%d \n",l_border[h]);
			if(l_border[h]>3&&h<60&&h>4) l_lose_num--;
			if(l_border[h]>3&&h>60&&h<110) l_lose_low_num--;
		}
		else continue; //每行只取一个点，没到下一行就不记录
		h--;
		if (h == 0) 
		{
			break;//到最后一行退出
		}
	}
		
}
/*
函数名称：void get_right(uint16 total_R)
功能说明：从八邻域边界里提取需要的边线
参数说明：
total_R  ：找到的点的总数
函数返回：无
修改时间：2022年9月25日
备    注：
example：get_right(data_stastics_r);
 */
void get_right(uint16 total_R)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	for (i = 0; i < image_h; i++)
	{
		r_border[i] = border_max;//右边线初始化放到最右边，左边线放到最左边，这样八邻域闭合区域外的中线就会在中间，不会干扰得到的数据
	}
	h = image_h - 2;
	//右边
	r_lose_num=60;
	r_lose_low_num=60;
	for (j = 0; j < total_R; j++)
	{
		if (points_r[j][1] == h)
		{
			r_border[h] = points_r[j][0] - 1;
			if(r_border[h]<image_w-4&&h<60&&h>4) r_lose_num--;
			if(r_border[h]<image_w-4&&h>60&&h<110) r_lose_low_num--;
		
		}
		else continue;//每行只取一个点，没到下一行就不记录
		h--;
		if (h == 0)break;//到最后一行退出
	}
			
}

//定义膨胀和腐蚀的阈值区间
#define threshold_max	255*5//此参数可根据自己的需求调节
#define threshold_min	255*2//此参数可根据自己的需求调节
void image_filter(uint8(*image1)[image_w])//形态学滤波，简单来说就是膨胀和腐蚀的思想
{
	uint16 i, j;
	uint32 num = 0;


	for (i = 1; i < image_h - 1; i++)
	{
		for (j = 1; j < (image_w - 1); j++)
		{
			//统计八个方向的像素值
			num =
				image1[i - 1][j - 1] + image1[i - 1][j] + image1[i - 1][j + 1]
				+ image1[i][j - 1] + image1[i][j + 1]
				+ image1[i + 1][j - 1] + image1[i + 1][j] + image1[i + 1][j + 1];


			if (num >= threshold_max && image1[i][j] ==0)
			{

				image1[i][j] = 255;//白  可以搞成宏定义，方便更改

			}
			if (num <= threshold_min && image1[i][j] ==255)
			{

				image1[i][j] = 0;//黑

			}

		}
	}

}


/*
函数名称：void middle_line()
功能说明：找中线
参数说明：

函数返回：无
修改时间：2022年9月25日
备    注：
example：middle_line();
 */
void middle_line(){
	uint8_t i;
  int Left_Round_A;
 

  if(Round_Leftroud_num==2||Round_Rightroud_num==2||Round_Leftroud_num==1||Round_Rightroud_num==1){
	if(Round_Leftroud_num==2){//靠右边补中线
    for(i=0;i<40;i++){
      Left_Round_A=r_border[i]-20;
      if(Left_Round_A>=image_w-2)
      {
        Left_Round_A=image_w-2;

      }
      if(Left_Round_A<=1)
      {
        Left_Round_A=1;

      }
      center_line[i]=Left_Round_A;
      
    }
    return 0;
  }
  if(Round_Rightroud_num==2){//靠左边补中线
    for(i=0;i<40;i++){
      Left_Round_A=l_border[i]+20;
      if(Left_Round_A>=image_w-2)
      {
        Left_Round_A=image_w-2;

      }
      if(Left_Round_A<=1)
      {
        Left_Round_A=1;

      }
      center_line[i]=Left_Round_A;
    }
    return 0;
  }
  if(Round_Leftroud_num==1){//靠右边补中线
    for(i=0;i<50;i++){
      Left_Round_A=r_border[i]-10;
      if(Left_Round_A>=image_w-2)
      {
        Left_Round_A=image_w-2;

      }
      if(Left_Round_A<=1)
      {
        Left_Round_A=1;

      }
      center_line[i]=Left_Round_A;
      
    }
    return 0;
  }
  if(Round_Rightroud_num==1){//靠左边补中线
    for(i=0;i<50;i++){
      Left_Round_A=l_border[i]+10;
      if(Left_Round_A>=image_w-2)
      {
        Left_Round_A=image_w-2;

      }
      if(Left_Round_A<=1)
      {
        Left_Round_A=1;

      }
      center_line[i]=Left_Round_A;
	  
    }
    return 0;
  }
}
  else {
	for(int i=image_h-2;i>0;i--){
		if(l_border[i]>4||r_border[i]<image_w-4){
			center_line[i]=(l_border[i]+r_border[i])/2;
		}
		else{
			
			center_line[i]=(center_line[i+4]+center_line[i+5]+center_line[i+1]+center_line[i+2]+center_line[i+3])/5;
		
			
		}
		if(i>40){
			center_line[i]=(l_border[i]+r_border[i])/2;
		}

	}
}
Round_Leftroud_num=0;
  Round_Rightroud_num=0;
}




/*
函数名称：void image_draw_rectan(uint8(*image)[image_w])
功能说明：给图像画一个黑框
参数说明：uint8(*image)[image_w]	图像首地址
函数返回：无
修改时间：2022年9月8日
备    注：
example： image_draw_rectan(bin_image);
 */
void image_draw_rectan(uint8(*image)[image_w])
{

	uint8 i = 0;
	for (i = 0; i < image_h; i++)
	{
		image[i][0] = 0;
		image[i][1] = 0;
		image[i][image_w - 1] = 0;
		image[i][image_w - 2] = 0;

	}
	for (i = 0; i < image_w; i++)
	{
		image[0][i] = 0;
		image[1][i] = 0;
		//image[image_h-1][i] = 0;

	}
}

/*
函数名称：void Inflection_point(void)
功能说明：拐点函数
参数说明：无
函数返回：无
修改时间：2022年9月8日
备    注：
example： Inflection_point();
 */
int L_down_point_x=0;
int R_down_point_x=0;
int L_down_point_y=0;
int R_down_point_y=0;

int R_up_point_x=0;
int R_up_point_y=0;
int L_up_point_x=0;
int L_up_point_y=0;
void Inflection_point(void){
	R_down_point_x=0;
	R_down_point_y=0;
	L_down_point_x=0;
	L_down_point_y=0;

	R_up_point_x=0;
	R_up_point_y=0;
	L_up_point_x=0;
	L_up_point_y=0;
	int dir_l_down_flag=0;
	int dir_r_down_flag=0;
	int dir_l_up_flag=0;
	int dir_r_up_flag=0;
  for(int i =20;points_l[i][1]>3;i++){
	    int K_dir_l_down=0;
		int K_dir_l_up=0;
		K_dir_l_down=round((float)((dir_l[i-3]+dir_l[i-2]+dir_l[i-6]+dir_l[i-4]+dir_l[i-5])/5));
		K_dir_l_up=round((float)((dir_l[i+4]+dir_l[i+6]+dir_l[i+3]+dir_l[i+2]+dir_l[i+5])/5));
//寻找下拐点
    if(((K_dir_l_up==2&&K_dir_l_down==4)||(K_dir_l_up==2&&K_dir_l_down==5))&&dir_l_down_flag==0){
      dir_l_down_flag+=1;
      L_down_point_y=points_l[i][0];
      L_down_point_x=points_l[i][1];
	  
    
    }
//寻找上拐点
	if(((K_dir_l_up==4&&K_dir_l_down==6)||(K_dir_l_up==5&&K_dir_l_down==6))&&dir_l_up_flag==0){
    dir_l_up_flag+=1;
      L_up_point_y=points_l[i][0];
      L_up_point_x=points_l[i][1];
	//   printf("%d %d %d %d %d %d %d \n",dir_r[i-5],dir_r[i-3],dir_r[i],dir_r[i+3],dir_r[i+5],points_r[i][0],points_r[i][1]);
	// 	printf("\n");
    // printf("a \n");
    }
	
}
	for(int i =20;points_r[i][1]>3;i++){
		int K_dir_r_down=0;
		int K_dir_r_up=0;
		K_dir_r_down=round((float)((dir_r[i-3]+dir_r[i-2]+dir_r[i-6]+dir_r[i-4]+dir_r[i-5])/5));
		K_dir_r_up=round((float)((dir_r[i+4]+dir_r[i+6]+dir_r[i+2]+dir_r[i+3]+dir_r[i+5])/5));
//寻找下拐点
    
    if(((K_dir_r_up==2&&K_dir_r_down==4)||(K_dir_r_up==2&&K_dir_r_down==5))&&dir_r_down_flag==0){
        dir_r_down_flag+=1;
        R_down_point_y=points_r[i][0];
        R_down_point_x=points_r[i][1];
		// printf("%d %d %d \n",dir_r[i],points_r[i][0],points_r[i][1]);
		// printf("\n");
		
//寻找上拐点
    }
	if(((K_dir_r_up==4&&K_dir_r_down==6)||(K_dir_r_up==5&&K_dir_r_down==6))&&dir_r_up_flag==0){
    dir_r_up_flag+=1;
      R_up_point_y=points_r[i][0];
      R_up_point_x=points_r[i][1];
	//   printf("%d %d %d %d %d %d %d \n",dir_r[i-5],dir_r[i-3],dir_r[i],dir_r[i+3],dir_r[i+5],points_r[i][0],points_r[i][1]);
	// 	printf("\n");
    }
	
  }
  //判断下角点不在上焦点上面
}






unsigned char image0[image_h][image_w]={};

/*
函数名称：void image_process(void)
功能说明：最终处理函数
参数说明：无
函数返回：无
修改时间：2022年9月8日
备    注：
example： image_process();
 */
void image_process(void)
{
uint16 i;
uint8 hightest = 0;//定义一个最高行，tip：这里的最高指的是y值的最小
/*这是离线调试用的*/

// turn_to_bin();
/*提取赛道边界*/
// image_filter(bin_image);//滤波
image_draw_rectan(bin_image);//预处理
//清零
data_stastics_l = 0;
data_stastics_r = 0;
if (get_start_point(image_h - 2))//找到起点了，再执行八领域，没找到就一直找
{
	
	search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);
	// search_l_r((uint16)USE_num, image1, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);
	
	// 从爬取的边界线内提取边线 ， 这个才是最终有用的边线
	get_left(data_stastics_l);
	get_right(data_stastics_r);
	Inflection_point();
	
	//处理函数放这里，不要放到if外面去了，不要放到if外面去了，不要放到if外面去了，重要的事说三遍

}
 
}

//****************************************************************道路中线error值****************************************************************
int ElseRoad_Middle_Row;
int StrightRoad_Middle_Row;
int Middle_Row=14;//16


int position=0;
int Round_Middle_Row=20;//R80:20

int Cross_Row=10;
int Barrier_Middle_Row=10;
int Ramp_Middle_Row=40;
void error_get(void)
{
	      float sum2;
          float cha_mid;
          Middle_Row=20;
          cha_mid=0;
      
          if(RoundProcess>=Into_Round&&RoundProcess<Leave_Round&&RoadType == Round_Road)//处理圆环时的前瞻
          {
			// printf("0000909898898989898989898989898989898989 \n");
              Middle_Row=Round_Middle_Row;//20
             
          }
		  else if(CrossProcess>=Find_Cross&&CrossProcess<Out_Cross&&RoadType == Cross_Road)//处理圆环时的前瞻
          {
			// printf("ccccccccccccccccccc \n");
              Middle_Row=Cross_Row;
		
             
          }
          else if(RoadType==Barrier)//处理障碍的时候的前瞻
          {
              Middle_Row=Barrier_Middle_Row;  
          }
		   else if(RampProcess >= Find_Ramp && RampProcess < Out_Ramp && RoadType == Ramp)//处理障碍的时候的前瞻
          {
			// printf("r_row\n");
              Middle_Row=Ramp_Middle_Row;
          }
        
          for(int i=Middle_Row;i<Middle_Row+13;i+=4)//取了三行的误差
          {
              cha_mid+=(COL_END)/2-center_line[i];//求和
          }

         

        


          position=cha_mid/3;//求均值
                  



}





/*

这里是起点（0.0）***************——>*************x值最大
************************************************************
************************************************************
************************************************************
************************************************************
******************假如这是一副图像*************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
y值最大*******************************************(188.180)

*/


