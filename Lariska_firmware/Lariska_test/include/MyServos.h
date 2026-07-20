#pragma once
#include <Arduino.h>
#include "Servo.h"
#include "Config.h"

Servo rul_servo, pitch_servo, yaw_servo;

//== Rul control ==
void rul_init()
{
    rul_servo.attach(RUL_PIN, RUL_MIX, RUL_MAX);
}

void rul_tick(int phi)
{
    rul_servo.write(phi);
}

//== Head control ==
void h_init()
{
    pitch_servo.attach(PITCH_PIN, PITCH_MIX, PITCH_MAX);
    yaw_servo.attach(YAW_PIN, YAW_MIX, YAW_MAX);
}

void h_tick(int pitch_phi, int yaw_phi)
{
    pitch_servo.write(pitch_phi);
    yaw_servo.write(yaw_phi);
}
