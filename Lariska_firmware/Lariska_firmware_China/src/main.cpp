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

void move_to_Cheburashka();

void setup() {
  Serial.begin(115200);
  ve_init();
  m_init();
  enc_init();
  servo_init();
  son_init();
  buz_init();
  
  argviz_init(Serial);
  argviz_registerScreen(0, enc_buz_vel);
  argviz_registerScreen(1, servo);
  argviz_registerScreen(2, sonars);
  argviz_start();
  //-------------------


  son_tick(1);
  while (son_forw_get_dist() > 23){
    move_to_Cheburashka();
    son_tick(1);
  }
}

void move_to_Cheburashka()
{
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
  ;
  timer = micros();

  st_rotate();
  st_tick();
  
  // servo_test();
  servo_tick();
}

void loop() {
  // static uint32_t timer = micros();
  // while (micros() - timer < Ts_us)
  // ;
  // timer = micros();
}