#pragma once
#include "MyServos.h"
#include "Buzzer.h"
#include "Sonar.h"
#include "VelEst.h"

bool buz_st = 0;
SCREEN(sonars, 
       {
          ROW("Wall : %d", int(son_wall_get_dist()))
          // ROW("Enc tick : %d", int(enc_t))
          ROW("Forw : %d", int(son_forw_get_dist()))
       })
SCREEN(enc_buz_vel, 
       {
          ROW("Enc phi: %d", int(enc_phi))
          // ROW("Enc tick : %d", int(enc_t))
          CLICK_ROW([](CLICK_STATE state)
                  {
                     switch (state)
                     {
                     case CLICK_DOWN:
                       buz_st = !buz_st;
                       buz_state(buz_st);
                       break;
                     default:
                       break;
                     } },
                  "Buz_state: %s", String(buz_st).c_str())
          CLICK_ROW([](CLICK_STATE state)
                  {
                     switch (state)
                     {
                     case CLICK_LEFT:
                       goal_w-= 10;
                       break;
                     case CLICK_RIGHT:
                       goal_w+= 10;
                       break;
                     case CLICK_DOWN:
                       goal_w = 0.0;
                       break;
                     default:
                       break;
                     } },
                  "goal_w: %s", String(goal_w).c_str())

       })

SCREEN(servo, 
       {
          CLICK_ROW([](CLICK_STATE state)
                  {
                     switch (state)
                     {
                     case CLICK_LEFT:
                       test_phi_rul -= 1 ;
                       break;
                     case CLICK_RIGHT:
                       test_phi_rul += 1;
                       break;
                     case CLICK_DOWN:
                       test_phi_rul = RUL_ZERO;
                       break;
                     default:
                       break;
                     } },
                  "phi_rul: %s", String(test_phi_rul).c_str())
          CLICK_ROW([](CLICK_STATE state)
                  {
                     switch (state)
                     {
                     case CLICK_LEFT:
                       test_phi_pitch -= 1 ;
                       break;
                     case CLICK_RIGHT:
                       test_phi_pitch += 1;
                       break;
                     case CLICK_DOWN:
                       test_phi_pitch = PITCH_ZERO;
                       break;
                     default:
                       break;
                     } },
                  "phi_pitch: %s", String(test_phi_pitch).c_str())
          CLICK_ROW([](CLICK_STATE state)
                  {
                     switch (state)
                     {
                     case CLICK_LEFT:
                       test_phi_yaw -= 1 ;
                       break;
                     case CLICK_RIGHT:
                       test_phi_yaw += 1;
                       break;
                     case CLICK_DOWN:
                       test_phi_yaw = YAW_ZERO;
                       break;
                     default:
                       break;
                     } },
                  "phi_yaw: %s", String(test_phi_yaw).c_str())
          ROW("Rul_imp: %d", int(rul.getCurrent()))
          ROW("Pitch_imp: %d", int(pitch.getCurrent()))
          ROW("Yaw_imp: %d", int(yaw.getCurrent()))
       })
SCREEN(motor, 
       {
          ROW("Real_vel: %d", int(ve_get_w_est_f()))
          
          CLICK_ROW([](CLICK_STATE state)
                  {
                    switch (state)
                     {
                     case CLICK_LEFT:
                       goal_w -= 100 ;
                       break;
                     case CLICK_RIGHT:
                       goal_w += 100;
                       break;
                     case CLICK_DOWN:
                       goal_w = 0;
                       break;
                     default:
                       break;
                     }},
                  "goal_w: %s", String(goal_w).c_str())
          CLICK_ROW([](CLICK_STATE state)
                  {
                    switch (state)
                     {
                     case CLICK_LEFT:
                       SERVO_KP -= 0.1 ;
                       break;
                     case CLICK_RIGHT:
                       SERVO_KP += 0.1;
                       break;
                     case CLICK_DOWN:
                       SERVO_KP = 3.0;
                       break;
                     default:
                       break;
                     }},
                  "KP: %s", String(SERVO_KP).c_str())
          CLICK_ROW([](CLICK_STATE state)
                  {
                    switch (state)
                     {
                     case CLICK_LEFT:
                       SERVO_KI -= 0.1 ;
                       break;
                     case CLICK_RIGHT:
                       SERVO_KI += 0.1;
                       break;
                     case CLICK_DOWN:
                       SERVO_KI = 20.0;
                       break;
                     default:
                       break;
                     }},
                  "KI: %s", String(SERVO_KI).c_str())
          })