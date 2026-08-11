#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"
#include "Dist.h"


#include "PID.h"

#define RUL_PIN    8//*!
#define RUL_MAX    130
#define RUL_MIN    48//37
#define RUL_ZERO   80//83

#define RUL_PIN    8
#define RUL_ZERO   80
#define RUL_LEN   40

Servo servo;
PID pid(1, 0, 0.5, 0, 255);

void servo_init() {
    servo.attach(RUL_PIN);
    servo.write(RUL_ZERO);
}

void servo_set(uint8_t value) {
    uint16_t angle = map(value, 0, 255, RUL_MIN, RUL_MAX);
    
    angle = constrain(angle, (RUL_ZERO - RUL_LEN), (RUL_ZERO + RUL_LEN));

    servo.write(angle);
}

void setup() {
  Serial.begin(115200);
  motor_init(); 
  dist_init();

  servo_init();
  motor_set_rpm(150);
}

void loop() {
  motor_update();
  dist_update();
  
  uint16_t dist = dist_get();
  Serial.println(dist);
    servo_set(pid.compute(400, dist));


  delay(25);
}
