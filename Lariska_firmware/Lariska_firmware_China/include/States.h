#pragma once
#include "ServoMotor.h"
#include "MyServos.h"
#include "Config.h"
#include "Sonar.h"
#include <AceSorting.h>

#include "Sharp.h"

int pitch_phi = PITCH_ZERO;
int yaw_phi = YAW_ZERO;
int rul_phi = RUL_ZERO;
float vel = 0.0;

const int UST = 245;

void st_tick()
{
    rul.setTargetDeg(rul_phi);
    sm_tick(vel);
    pitch.setTargetDeg(pitch_phi);
    yaw.setTargetDeg(yaw_phi);
    servo_tick();
}

void st_forw()
{
    pitch_phi = PITCH_ZERO;
    yaw_phi = YAW_ZERO;
    rul_phi = RUL_ZERO;
    vel = VEL_T_F;
}



void st_rotate()
{
    // const int len = 5;
    // static int Dists[len] = {GOAL_DIST};
    // int Dists_sort[len] = {};
    // static int index = 0;
    







    // static int distOld = GOAL_DIST;
    // son_tick(0);
    // int dist = son_wall_get_dist();
    // static uint32_t rul_time = millis();
    
    // if(dist == 0){
    //     if(distOld < GOAL_DIST && (millis() - rul_time < 250))
    //         dist = GOAL_DIST * 0.5;
    //     else{
    //         dist = GOAL_DIST * 1.5;
    //         rul_time = millis();
    //     }
    // }










    // if(dist != 0) Dists[index] = dist;
    // index++;
    // if(index >= len) index = 0;

    // for(int i = 0; i < 10; i++)
    //     Dists_sort[i] = Dists[i];

    // ace_sorting::insertionSort(Dists_sort, len);
    
    // int med = Dists_sort[len/2+1];
       


    //// if(dist == 0){
    ////     if(distOld > GOAL_DIST)
    ////         dist = GOAL_DIST * 1.5;
          
    //// }

    
    int dist = sharpF();
    static int distOld = dist;
    // int err = (GOAL_DIST - dist);
    // int err = (GOAL_DIST - med);


    int err = (dist - UST);
    static int errOld = err;

    // rul_phi = RUL_ZERO + 8 + ( (err * ROTATE_KP)+((err - errOld)*ROTATE_KD) );
    rul_phi = RUL_ZERO + ( (err * ROTATE_KP_SH)+((err - errOld)*ROTATE_KD_SH) );
    Serial.println(rul_phi);
    vel = MAX_VEL;
    

    distOld = dist;
    // distOld = med;
}

void st_to_cheburashka()
{
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
}

void st_rot(uint32_t gTime = 11000)
{
  uint32_t time_rot = millis();
  while (millis() - time_rot < gTime)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();

    st_rotate();
    st_tick();

  }
  sm_off();
}


void st_beep(int gTime = 500)
{
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
      delay(gTime);
      buz_state(0);
      delay(gTime);
    }
    yaw.setTargetDeg(YAW_ZERO);
    delay(200);
    pitch.setTargetDeg(PITCH_ZERO);
    delay(200);
    // time_bow = millis();
    // while (millis() - time_bow <= de)
    // {
    //       yaw.setTargetDeg(YAW_ZERO);
    //       yaw.tick();
    // }
    // time_bow = millis();
    // while (millis() - time_bow <= de)
    // {
    //       pitch.setTargetDeg(PITCH_ZERO);
    //       pitch.tick();
    // }
}

void st_L_turn(int gTime)
{
  static uint32_t time_turn = millis();
  time_turn = millis();
  while (millis() - time_turn <= gTime/*300*//*500*/)/*430*/
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
    ;
    timer = micros();
    
    sm_tick(VEL_T);
    rul.setTarget(RUL_MIN_IMP);
    rul.tick();
  }
  sm_off();
}

void st_R_turn(int ti)
{
    Serial.println("R");
    static uint32_t time_turn = millis();
    time_turn = millis();
    while (millis() - time_turn <= ti/*300*//*500*/)/*430*/
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();
        
        sm_tick(VEL_T);
        rul.setTarget(RUL_MAX_IMP);
        rul.tick();
    }
    sm_off();
}

void st_forward(int gTime)
{ 
    Serial.println("F");
    uint32_t time_turn = millis();
    while (millis() - time_turn <= gTime)
    {
      static uint32_t timer = micros();
      while (micros() - timer < Ts_us)
      ;
      timer = micros();
    
      sm_tick(VEL_T);
      rul.tick();
      rul.setTargetDeg(RUL_ZERO);
      // st_tick();
    }
    time_turn = millis();
    sm_off();
}