#pragma once
int Phi = 45;
float goal_w = 0.0;
int test_phi_rul = RUL_ZERO;
int test_phi_pitch = PITCH_ZERO;
int test_phi_yaw = YAW_ZERO;
#include "Screens.h"
#include"MyServos.h"

void servo_test()
{
    // rul.setTargetDeg(test_phi_rul);
    Rul.write(test_phi_rul);
    pitch.setTargetDeg(test_phi_pitch);
    yaw.setTargetDeg(test_phi_yaw);
}

void sm_test()
{
    sm_tick(goal_w);
}

void start_test()
{
    // Servo
    rul.setTargetDeg(RUL_MIN);
    delay(250);
    rul.setTargetDeg(RUL_ZERO);
    delay(250);
    rul.setTargetDeg(RUL_MAX);
    delay(250);
    rul.setTargetDeg(RUL_ZERO);
    delay(250);

    yaw.setTargetDeg(YAW_MAX);
    delay(250);
    pitch.setTargetDeg(PITCH_MAX);
    delay(250);
    pitch.setTargetDeg(PITCH_ZERO);
    delay(250);
    yaw.setTargetDeg(YAW_ZERO);
    delay(250);

    // Motor
    uint32_t t = millis();
    while (millis() - t <= 500)
    {
        if(millis() - t <= 250)
        {
            sm_tick(MAX_VEL);
        }
        else if(millis() - t < 500)
        {
            sm_tick(-MAX_VEL);
        }
        else
            sm_tick(0);
    }
    
}