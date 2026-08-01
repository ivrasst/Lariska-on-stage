#include <Arduino.h>
#include <argviz.h>

// #include "VoltageSens.h"
#include "VelEst.h"
#include "Motor.h"
#include "Encoder.h"
#include "ServoMotor.h"
#include "Sonar.h"
#include "test.h"
#include "MyServos.h"
#include "Buzzer.h"
#include "States.h"

#include "Screens.h"

void setup() {
  Serial.begin(115200);
  ve_init();
  m_init();
  enc_init();
  servo_init();
  son_init();
  buz_init();
  
  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_registerScreen(1, servo);
  argviz_registerScreen(2, sonars);
  argviz_start();
  
}

void loop() {
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
  ;
  timer = micros();
  
  
  

  st_rotate();
  st_tick();
  
  // servo_test();
  servo_tick();
}