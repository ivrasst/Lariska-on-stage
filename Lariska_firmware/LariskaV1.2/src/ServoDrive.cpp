#include "ServoDrive.h"

#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 8
#define SERVO_ZERO 85
#define SERVO_LEN_HALF 17
#define SERVO_LEN (SERVO_LEN_HALF * 2)

#define PITCH_PIN  9
#define YAW_PIN    10
#define PITCH_ZERO 66
#define YAW_ZERO   75
#define PITCH_MAX  83
#define PITCH_MIN  32
#define YAW_MAX    110
#define YAW_MIN    32

static Servo servo, pitch, yaw;

void servo_init() {
  servo.attach(SERVO_PIN);
  servo.write(SERVO_ZERO);

  pitch.attach(PITCH_PIN);
  pitch.write(PITCH_ZERO);

  yaw.attach(YAW_PIN);
  pitch.write(YAW_ZERO);
}

void servo_set(int8_t value) {
  int min_angle = SERVO_ZERO - SERVO_LEN;
  int max_angle = SERVO_ZERO + SERVO_LEN;

  int angle = map(value, -128, 127, min_angle, max_angle);
  angle = constrain(angle, min_angle, max_angle);

  servo.write(angle);
}
void servo_set_zero()
{
  servo.write(SERVO_ZERO);
}


void pitch_set(int8_t angle)
{
  angle = constrain(angle, PITCH_MIN, PITCH_MAX);
  pitch.write(angle);
}
void yaw_set(int8_t angle)
{
  angle = constrain(angle, YAW_MIN, YAW_MAX);
  yaw.write(angle);
}

void pitch_set_max()
{
  pitch.write(PITCH_MAX);
}
void yaw_set_max()
{
  yaw.write(YAW_MAX);
}

void pitch_set_zero()
{
  pitch.write(PITCH_ZERO);
}
void yaw_set_zero()
{
  yaw.write(YAW_ZERO);
}