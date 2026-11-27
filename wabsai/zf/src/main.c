#include "zf_common_headfile.h"
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <sched.h>

#define KEY_1       "/dev/zf_driver_gpio_key_0"
#define KEY_2       "/dev/zf_driver_gpio_key_1"
#define KEY_3       "/dev/zf_driver_gpio_key_2"
#define KEY_4       "/dev/zf_driver_gpio_key_3"

extern void captureAndUpdateImage();
extern unsigned char* getImageData();
extern void image_deal();
extern void servo_pid();
extern void pit_callback();
extern void Get_Encoder();
extern void motor_speed();




float yaw = 0;
float yaw_now = 0;
float dt = 0.005; // 2ms
float gyro_bias = 0.0;
float gyro=0.0;
float gz;

float yaw_y = 0;
float gy;
int32 gyro_y = 0;
float gyro_bias_y = 0;

// 任务函数定义
void task_a() { 
    // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // printf("Callback time: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);

    image_deal();
//    printf("%f \n",distance);
 }

void task_b() { 
   
    servo_pid();

     // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // printf("Callback time: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
    
}

void task_c() { 
   
    pit_callback();
    gz = imu660ra_gyro_z; // 读取z轴角速度，单位°/s
    yaw += gz * dt;
    yaw_now = yaw-gyro_bias;
    imu660ra_acc_z = yaw_now;
    // printf("%d   \n",imu660ra_acc_x);
    // printf("Yaw = %d\n\n", imu660ra_gyro_y);
//     struct timespec ts;
// clock_gettime(CLOCK_REALTIME, &ts);
// printf("Callback time: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
   
}

void task_d() { 
    Get_Encoder();
    motor_speed();
//      struct timespec ts;
// clock_gettime(CLOCK_REALTIME, &ts);
// printf("Callback time: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
}


// 线程函数模板
void* timer_thread(void* arg) {
    void (*task)(void) = (void (*)(void))arg;
    int interval_ms = 0;


    // 根据任务函数确定周期
    if (task == task_a) interval_ms = 10;
    else if (task == task_b) interval_ms = 5;
    else if (task == task_c) interval_ms = 5;
    else if (task == task_d) interval_ms = 2;
    
    
    
    // 创建定时器
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct itimerspec its = {
        .it_value = { .tv_sec = 0, .tv_nsec = interval_ms * 1000000 },
        .it_interval = { .tv_sec = 0, .tv_nsec = interval_ms * 1000000 }
    };
    timerfd_settime(fd, 0, &its, NULL);

    // 设置线程为实时优先级（需root权限）
    struct sched_param param = { .sched_priority = 90 };
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);

    // 事件循环
    while (1) {
        uint64_t exp;
        read(fd, &exp, sizeof(exp));
        task();  // 执行任务
    }
    return NULL;
}



int main() 
{
    init_and_set_all();
    
    signal(SIGINT, ssleep);
    // pthread_t imageDealThreadHandle;
    // if (pthread_create(&imageDealThreadHandle, NULL, image_deal, NULL) != 0) {
    //     fprintf(stderr, "Failed to create image deal thread!\n");
    //     return -1;
    // }
    pthread_t tid_a, tid_b, tid_c, tid_d;
    pthread_create(&tid_c, NULL, timer_thread, (void*)task_c);
 
   for (int i = 0; i < 4000; i++) {
        gyro_bias += yaw;  // 以Z轴为例
        
    }
    gyro = gyro_bias/4000;
    sleep(1);
    
    pthread_create(&tid_a, NULL, timer_thread, (void*)task_a);
    pthread_create(&tid_b, NULL, timer_thread, (void*)task_b);
   
     pthread_create(&tid_d, NULL, timer_thread, (void*)task_d);

  
    
    while(1)
    {
       
       
    }
    return 0;
}

