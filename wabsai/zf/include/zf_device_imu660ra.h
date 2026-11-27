#ifndef _zf_device_imu660ra_h
#define _zf_device_imu660ra_h


#include "zf_common_typedef.h"

extern int32 imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;  
extern int32 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;
extern int32 last_imu660ra_acc_y;
extern int32 imu_z;
void imu660ra_get_acc(void);
void imu660ra_get_gyro(void);
void pit_callback();

extern float yaw_now;
#endif
