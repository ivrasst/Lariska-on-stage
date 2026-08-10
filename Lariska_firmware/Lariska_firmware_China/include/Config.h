#pragma once

#define Ts_us 2700//3500
#define Ts_s (Ts_us / 1000000.0)

#define VE_LPF_T 0.005

// Servo Motor
// #define SERVO_KP 3.0
// #define SERVO_KI 20.0
float SERVO_KP = 3.0;
float SERVO_KI = 20.0;
#define MAX_VEL 1000//1200 // [ms]
#define VEL_T 450 
#define VEL_T_F 450//450

// Servo
#define RUL_PIN    8//*!
#define RUL_MAX    130
#define RUL_MIN    48//37
#define RUL_ZERO   80//83

#define RUL_MAX_IMP    1836
#define RUL_MIN_IMP    1126
//881

#define PITCH_PIN  9
#define PITCH_MAX  83
#define PITCH_MIN  32
#define PITCH_ZERO 63

#define PITCH_MAX_IMP    1500//1368
#define PITCH_MIN_IMP    835

#define YAW_PIN    10
#define YAW_MAX    180//110
#define YAW_MIN    32
#define YAW_ZERO   99//72

#define YAW_MAX_IMP    1800//1663
#define YAW_MIN_IMP    835

// Rat params
#define RAT_WIDTH 0.09 // [m]
#define RAT_WHEEL_RADIUS 0.09 // [m]

// Rotate params
#define GOAL_DIST 20 // [sm]
#define ROTATE_KP 9.0//5.0
#define ROTATE_KD 0.2//5.0

#define ROTATE_KP_SH 1.0//5.0
#define ROTATE_KD_SH 0.0//5.0


// Squeak
#define ALL_SQUEAK_TIME 3000