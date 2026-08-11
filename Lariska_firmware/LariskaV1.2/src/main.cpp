#include <Arduino.h>
#include "Motor.h"
#include "Dist.h"
#include "ServoDrive.h"
#include "PID.h"
#include "Buzzer.h"

#include "Servo.h"
Servo pitch, yaw;
#define PITCH_PIN  9
#define YAW_PIN    10

#define PITCH_ZERO 66//63
#define YAW_ZERO   75//99

#define PITCH_MAX  83
#define PITCH_MIN  32
#define YAW_MAX    110//110
#define YAW_MIN    32


PID pid(0.2, 0, 0, -128, 127);



void setup() {
  Serial.begin(115200);
  
  motor_init();
  dist_init();
  servo_init();
  motor_set_rpm(150);
  buz_init();

  pitch.attach(PITCH_PIN);
  pitch.write(PITCH_ZERO);
  yaw.attach(YAW_PIN);
  pitch.write(YAW_ZERO);
  int d = 200;
  delay(d);

  yaw.write(YAW_MAX);
  delay(d);
  pitch.write(PITCH_MAX);
  delay(d);

  buz_squeak();
  
  pitch.write(PITCH_ZERO);
  delay(d);
  yaw.write(YAW_ZERO);
  delay(d);
  
  delay(500);
}

void loop() {
  motor_update();
  dist_update();
  
  uint16_t dist = dist_get();
  Serial.println(dist);
  
  if (millis() > 22000) {
      motor_stop();
      for(;;); // TODO: Переделать
  }

  if (dist == 0) {
    // servo_set(-75);
    servo_set(-110);
    pid.reset();
  } else {
    servo_set(pid.compute(350, dist)); 
  }
  
  delay(25);
}
