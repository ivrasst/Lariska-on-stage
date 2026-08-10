#include <Arduino.h>
#include "Motor.h"



void setup() {
  Serial.begin(115200);
  motor_init(); 
  motor_set_rpm(200);
  
}

void loop() {
  motor_update();
  delay(25);
}
