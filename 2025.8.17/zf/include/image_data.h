#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H
#include "edge_find.h"
#ifdef __cplusplus


extern "C" {
#endif

// 定义一个全局变量，C代码可以访问
extern unsigned char image1[120][160]; // 假设图像大小是 160x120
extern u_int8_t bin_image[image_h][image_w];//图像数组
// 定义函数来获取图像数据
unsigned char* getImageData();
extern void captureAndUpdateImage();
unsigned char adapt_otsuThreshold(u_int8_t *image, u_int16_t col, u_int16_t row,unsigned char *threshold);
extern void camera_open();
extern void processImage();
#ifdef __cplusplus
}
#endif

#endif // IMAGE_DATA_H