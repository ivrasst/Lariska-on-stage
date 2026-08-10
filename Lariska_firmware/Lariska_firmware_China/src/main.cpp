#include <Arduino.h>
#include <argviz.h>

#include "VelEst.h"
#include "Motor.h"
#include "Encoder.h"
#include "ServoMotor.h"
#include "Sonar.h"
#include "test.h"
#include "MyServos.h"
#include "Buzzer.h"
#include "States.h"
#include "States2.h"
#include "Screens.h"
#include "Sharp.h"
#include "St3.h"



void scenario();

void setup() {
  Serial.begin(115200);
  ve_init();
  m_init();
  enc_init();
  servo_init();
  son_init();
  buz_init();
  stPD_init();
  // son_tick(0);
  // static int pred = son_wall_get_dist();
  // while (pred == 0 || pred >= 25)
  // {
  //   son_tick(0);
  //   pred = son_wall_get_dist();
  // }

  // while (analogRead(A3) < 300);


  // scenario();  

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
  st_pd();
  // st2_rotate_PD();
  // st2_rotate_lqr();
  // Serial.println(String(analogRead(A3))+ '\t' + String(analogRead(A0)));
  
  // servo_test();
  // Serial.println(String(sharpF_m()) + " "+ String(sharpF()) + '\t' + String(sharpC_m()) + " "+ String(sharpC()));
}



void scenario()
{
  st_to_cheburashka();
  Serial.println("S");
  st_R_turn(250);
  delay(150);
  // st_forward(250);
  st_forward(300);
  
  st_forward(1000);
  st_L_turn(450);
  delay(150);
  st_forward(700);
  st_beep();


  delay(1000);//*/

  // st_L_turn(400);
  // delay(150);
  // st_forward(500);
  st_rot();
}