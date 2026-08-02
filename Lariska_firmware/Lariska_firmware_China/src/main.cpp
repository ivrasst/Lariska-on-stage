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

  // Move to Cheburashka part
  son_tick(1);
  while (son_forw_get_dist() >= 23 && son_forw_get_dist() != 0)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();

    st_forw();
    st_tick();
    

    son_tick(1);
  }
  sm_off();

  // Bow part
  yaw.setTargetDeg(YAW_MAX);
  delay(200);
  pitch.setTargetDeg(PITCH_MAX);
  delay(200);
  
  for(int i = 0; i < 3; i++){
    buz_state(1);
    delay(150);
    buz_state(0);
    delay(150);
  }
  
  yaw.setTargetDeg(YAW_ZERO);
  delay(200);
  pitch.setTargetDeg(PITCH_ZERO);
  delay(200);

  // Rotate part
  uint32_t time_rot = millis();
  while (millis() - time_rot < 10000)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();

    st_rotate();
    st_tick();
    
    son_tick(1);
  }
  sm_off();

  
}



void loop() {
  // static uint32_t timer = micros();
  // while (micros() - timer < Ts_us)
  // ;
  // timer = micros();

  // servo_test();
}