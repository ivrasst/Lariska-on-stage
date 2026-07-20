#pragma once

#define Ts_us 2000
#define Ts_s (Ts_us / 1000000.0)

#define VE_LPF_T 0.005

#define SERVO_KP 3.0
#define SERVO_KI 20.0

// Servo Motor
#define MAX_VEL 3 // [ms]

// Servo
#define RUL_PIN    20//*!
#define RUL_MAX    180
#define RUL_MIX    0
#define RUL_ZERO   0

#define PITCH_PIN  21
#define PITCH_MAX  180
#define PITCH_MIX  0
#define PITCH_ZERO 0

#define YAW_PIN    22
#define YAW_MAX    180
#define YAW_MIX    0
#define YAW_ZERO   0

// Rat params
#define RAT_WIDTH 0.09 // [m]
#define RAT_WHEEL_RADIUS 0.09 // [m]