/*
 * seekfreepower.h
 *
 *  Created on: 2024年7月5日
 *      Author: icand
 */
#ifndef CODE_SEEKFREEPOWER_H_
#define CODE_SEEKFREEPOWER_H_
#define MAX_SPEED 800.0 // 最大速度880
#define MIN_SPEED 800.0  // 最小速度
extern int16 speed_maximum;
extern int16 speed_minimum;
extern int16 circle_speed_maximum;
extern int16 circle_speed_minimum;
extern int16 Findcircle_speed_maximum;
extern int16 Findcircle_speed_minimum;
// 差速输出 = Kp1 * (图像偏差)
extern float diff_output;
extern float Kp1;//差速系数
void calculate_diff_output(float Kp1, int16 error);
// 理想行进速度 = 最大速度 - (最大速度 - 最小速度) * abs(舵机转向值 / 舵机最大转向值)
extern int16 ideal_speed;
void calculate_ideal_speed(int16 max_speed, int16 min_speed, int16 steering_value, int16 max_steering_value);
// 左轮理想速度 = 理想行进速度 + 差速输出
extern float left_ideal_speed;
void calculate_left_wheel_speed(int16 ideal_speed, float diff_output);
// 右轮理想速度 = 理想行进速度 - 差速输出
extern float right_ideal_speed;
void calculate_right_wheel_speed(int16 ideal_speed, float diff_output);
//两个轮子的差速输出
void diff_speed(void);
#endif /* CODE_SEEKFREEPOWER_H_ */
