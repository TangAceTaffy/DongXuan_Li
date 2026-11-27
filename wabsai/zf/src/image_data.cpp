
#include "image_data.h"
#include "edge_find.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>



// 图像数据的全局数组
unsigned char image1[120][160] = {}; // 图像大小可以根据实际需求调整

// 互斥锁，确保对 image1 的访问是线程安全的
std::mutex imageMutex;

// 获取图像数据的函数
unsigned char* getImageData() {
    std::lock_guard<std::mutex> lock(imageMutex);
    return &image1[0][0];
}



// 使用OpenCV来获取图像并更新 image1
class VideoCaptureThread {
    public:
        VideoCaptureThread(int device = 0) : cap(device, cv::CAP_V4L2) {
            if (!cap.isOpened()) {
                std::cerr << "Failed to open camera!" << std::endl;
                return;
            }
    
            // 设置摄像头参数
            cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G')); // MJPG编码
            // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', '8', ' ', ' '));
            
            cap.set(cv::CAP_PROP_FRAME_WIDTH, 160);   // 宽度160像素
            cap.set(cv::CAP_PROP_FRAME_HEIGHT, 120);  // 高度120像素
            cap.set(cv::CAP_PROP_FPS, 100);           // 帧率120FPS
            cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 3);    // 1=手动曝光，3=自动曝光（部分摄像头）
            //  cap.set(cv::CAP_PROP_EXPOSURE, 100)  ; // 手动设置曝光值（可选）
            cap.set(cv::CAP_PROP_BUFFERSIZE, 4); 
            
    
        }
    
       
    
        // 直接读取摄像头帧（无队列）
        bool getFrame(cv::Mat &frame) {
            std::unique_lock<std::mutex> lock(frameMutex);
            return cap.read(frame); // 直接从硬件读取
        }
    
    private:
        cv::VideoCapture cap;
        std::mutex frameMutex; // 保护摄像头读取操作（多线程安全）
    };
    
    // 全局实例化
    VideoCaptureThread videoCaptureThread;
    

    /*变量声明*/
#define UPDATE_INTERVAL 5  // 每5帧更新一次阈值
#define ROI_SCALE 2       // 中央1/ROI_SCALE 区域
#define white_pixel 255
#define black_pixel 0
#define GrayScale 256
u_int8_t image_threshold = 127;         // 初始阈值
u_int8_t frame_count = 0;
u_int8_t original_image[image_h][image_w];
u_int8_t image_thereshold;//图像分割阈值
u_int8_t otsu_roi_buffer[(image_h) * (image_w)];
//------------------------------------------------------------------------------------------------------------------
//  @brief      获得一副灰度图像
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------
//  @brief     动态阈值
unsigned char adapt_otsuThreshold(u_int8_t *image, u_int16_t col, u_int16_t row,unsigned char *threshold)   //注意计算阈值的一定要是原图像
{
       #define GrayScale 256
       u_int16_t width = col;
       u_int16_t height = row;
       int pixelCount[GrayScale];
       float pixelPro[GrayScale];
       int i, j, pixelSum = width * height/4;
       //uint8 threshold = 0;
       u_int8_t* data = image;  //指向像素数据的指针
       for (i = 0; i < GrayScale; i++)
       {
          pixelCount[i] = 0;
          pixelPro[i] = 0;
       }

       u_int32_t gray_sum=0;
       //统计灰度级中每个像素在整幅图像中的个数
       for (i = 0; i < height; i+=2)
       {
          for (j = 0; j < width; j+=2)
          {
             pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
             gray_sum+=(int)data[i * width + j];       //灰度值总和
          }
       }

       //计算每个像素值的点在整幅图像中的比例

       for (i = 0; i < GrayScale; i++)
       {
          pixelPro[i] = (float)pixelCount[i] / pixelSum;

       }

       //遍历灰度级[0,255]
       float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;



       w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
       for (j = 0; j < GrayScale; j++)
       {

          w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
          u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

          w1=1-w0;
          u1tmp=gray_sum/pixelSum-u0tmp;

          u0 = u0tmp / w0;              //背景平均灰度
          u1 = u1tmp / w1;              //前景平均灰度
          u = u0tmp + u1tmp;            //全局平均灰度
          deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
          if (deltaTmp > deltaMax)
          {
             deltaMax = deltaTmp;
             *threshold = j;
          }
          if (deltaTmp < deltaMax)
          {
             *threshold+=0;
             break;
          }
       }
       return *threshold;
}

// 图像处理函数
u_int8_t bin_image[image_h][image_w];//图像数组
void turn_to_bin(void)
{
  u_int8_t i,j;
 image_thereshold = adapt_otsuThreshold(image1[0], image_w, image_h,&Threshold);
  for(i = 0;i<image_h;i++)
  {
      for(j = 0;j<image_w;j++)
      {
          if(image1[i][j]>image_thereshold)bin_image[i][j] = white_pixel;
          else bin_image[i][j] = black_pixel;
      }
  }
}

void image_filter_opencv(cv::Mat& bin_image) {
    // 定义核（3x3 矩形，对应你的 8 邻域）
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // 膨胀（填补黑点周围的白点）
    cv::dilate(bin_image, bin_image, kernel);

    // 腐蚀（移除白点周围的黑点）
    cv::erode(bin_image, bin_image, kernel);

    // 或者直接使用开运算（先腐蚀后膨胀）或闭运算（先膨胀后腐蚀）
    // cv::morphologyEx(bin_image, bin_image, cv::MORPH_OPEN, kernel);
    // cv::morphologyEx(bin_image, bin_image, cv::MORPH_CLOSE, kernel);
}

void processImage() {
   


        cv::Mat frame;
        if (videoCaptureThread.getFrame(frame)) {
            
            cv::Mat grayImage;
            cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);

           
            
               
          
        cv::Rect roiRect(10, 28, 135, 77);//0，28，160，92

        cv::Mat roi = grayImage(roiRect);
        
        
        cv::Mat resizedRoi;
        cv::resize(roi, resizedRoi, cv::Size(160, 120), 0, 0, cv::INTER_AREA);
        
        // 拷贝数据到全局数组
       
       
        
          
             cv::Mat cvBinImage(120, 160, CV_8UC1); // 包装成 cv::Mat（不拷贝数据）
            
          
            image_thereshold = adapt_otsuThreshold(image1[0], image_w, image_h,&Threshold);
            cv::threshold(resizedRoi, cvBinImage, image_thereshold, 255, cv::THRESH_BINARY);
             image_filter_opencv(cvBinImage);
             std::lock_guard<std::mutex> lock(imageMutex);
            memcpy(&bin_image[0][0], cvBinImage.data, 120 * 160 * sizeof(u_int8_t));
            
              memcpy(&image1[0][0], resizedRoi.data, 160*120*sizeof(uchar));
    
    
}
    else {
        std::cerr << "Image size is not 160x120!" << std::endl;
    }

    //              struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // printf("Callback time: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
                
            
        
    
        

    
}
