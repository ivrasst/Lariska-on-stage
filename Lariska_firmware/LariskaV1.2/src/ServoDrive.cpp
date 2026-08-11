#include "ServoDrive.h"

#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 8
#define SERVO_ZERO 85
#define SERVO_LEN_HALF 17
#define SERVO_LEN (SERVO_LEN_HALF * 2)

static Servo servo;

void servo_init() {
  servo.attach(SERVO_PIN);
  servo.write(SERVO_ZERO);
}

void servo_set(int8_t value) {
  int min_angle = SERVO_ZERO - SERVO_LEN;
  int max_angle = SERVO_ZERO + SERVO_LEN;

  int angle = map(value, -128, 127, min_angle, max_angle);
  angle = constrain(angle, min_angle, max_angle);

  servo.write(angle);
}
