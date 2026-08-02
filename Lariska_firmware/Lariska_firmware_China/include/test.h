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
    rul.setTargetDeg(test_phi_rul);
    pitch.setTargetDeg(test_phi_pitch);
    yaw.setTargetDeg(test_phi_yaw);
}