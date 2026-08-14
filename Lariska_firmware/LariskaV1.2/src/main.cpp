#include <Arduino.h>
#include "Motor.h"
#include "Dist.h"
#include "ServoDrive.h"
#include "PID.h"
#include "Buzzer.h"
#include "States.h"
#include "ADCread.h"


void setup() {
  Serial.begin(115200);
  
  motor_init();
  dist_init();
  servo_init();
  motor_set_rpm(150);
  buz_init();
  adc_init();

  // whait_trigger();

  // to_cheburashka();
  // bow();

  // rotate(36000);

  
}

void loop() {
}
