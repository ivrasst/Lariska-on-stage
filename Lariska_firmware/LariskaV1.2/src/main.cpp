#include <Arduino.h>
#include "Motor.h"
#include "Dist.h"
#include "ServoDrive.h"
#include "PID.h"

PID pid(0.2, 0, 0, -128, 127);

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
  
  if (millis() > 11000) {
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
