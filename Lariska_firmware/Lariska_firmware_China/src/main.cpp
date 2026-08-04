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




void scenario();

void setup() {
  Serial.begin(115200);
  ve_init();
  m_init();
  enc_init();
  servo_init();
  son_init();
  buz_init();

  // while (rul.getTargetDeg() < 80 || rul.getTargetDeg() > 86)
  // {  
  //   static uint32_t timer = micros();
  //   while (micros() - timer < Ts_us)
  //   ;
  //   rul.setTargetDeg(83);
  //   servo_tick();
  // }
  
  scenario();  

  /*argviz_init(Serial);
  argviz_registerScreen(0, enc_buz_vel);
  argviz_registerScreen(1, servo);
  argviz_registerScreen(2, sonars);
  argviz_registerScreen(3, motor);
  argviz_start();//*/
  //-------------------

  
}

void loop() {
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
  ;
  timer = micros();
  // son_tick();
  // Serial.print("son_forw_get_dist()  :  ");
  
  // Serial.println(son_forw_get_dist());
  // Serial.println(a);
  // st_rotate();
  // st_tick();
    
    // son_tick(1);

  sm_test();
  // servo_test();
}




// ====    ====

void scenario()
{
  // Move to Cheburashka part
  son_tick(1);
  static int dist = son_forw_get_dist();
  while ((dist == 0) || (dist >= 40))
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();

    rul.setTargetDeg(RUL_MIN);
    rul.tick();
    st_forw();
    
    st_tick();
    

    son_tick(1);
    dist = son_forw_get_dist();
  }
  sm_off();
//*/
  uint32_t time_turn = millis();
  while (millis() - time_turn <= 700)
  {
    rul.setTarget(RUL_MAX_IMP);
    rul.tick();
  }

  // time_turn = millis();
  // while (millis() - time_turn <= 700)
  // {
  //   rul.setTarget(RUL_MIN_IMP);
  //   rul.tick();
  // }

  // TURN L
  time_turn = millis();
  while (millis() - time_turn <= 500)/*430*/
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();
    // st_forw();
    sm_tick(450);
    rul.setTarget(RUL_MAX_IMP);
    rul.tick();
    
    // st_tick();
  }
  sm_off();

  // FORW
  time_turn = millis();
  while (millis() - time_turn <= 1000)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();
  
    sm_tick(450);
    rul.setTargetDeg(RUL_ZERO);
    rul.tick();
    
    // st_tick();
  }
  sm_off();

  // TURN R

  time_turn = millis();
  while (millis() - time_turn <= 300)/*430*/
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();
    
    sm_tick(450);
    rul.setTarget(RUL_MIN_IMP);
    rul.tick();
    
    // st_tick();
  }
  sm_off();

  
  /*//////////////////////////////////////////////
  // Bow part
  const int de = 700;
  uint32_t time_bow = millis();
  while (millis() - time_bow <= de)
  {
    yaw.setTarget(YAW_MAX_IMP);
    yaw.tick();
  }
  
  
  time_bow = millis();
  while (millis() - time_bow <= de)
  {
    pitch.setTarget(PITCH_MAX_IMP);
    pitch.tick();
  }
  // delay(200);
  
  for(int i = 0; i < 3; i++){
    buz_state(1);
    delay(500);
    buz_state(0);
    delay(500);
  }
  
  yaw.setTargetDeg(YAW_ZERO);
  delay(200);
  pitch.setTargetDeg(PITCH_ZERO);
  delay(200);
//*/

  // Rotate part
  uint32_t time_rot = millis();
  while (millis() - time_rot < 11000)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();

    st_rotate();
    st_tick();
    
    // son_tick(1);
  }
  sm_off();
//*/
}