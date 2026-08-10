#pragma once
#include <Arduino.h>
#include "Servo.h"
#include "ServoSmooth.h"
#include "Config.h"

#define RUL_SERVO_GY false

ServoSmooth rul, pitch, yaw;
Servo Rul;


void servo_init()
{

    if(RUL_SERVO_GY){
        rul.attach(RUL_PIN, RUL_MIN_IMP, RUL_MAX_IMP, RUL_ZERO);    
        rul.setSpeed(400/*160*/);
        rul.setAccel(0.7/*0.6*/);
    }
    else
        rul.detach();
    Rul.attach(RUL_PIN, RUL_MIN_IMP, RUL_MAX_IMP);    

    pitch.attach(PITCH_PIN, PITCH_MIN_IMP, PITCH_MAX_IMP, PITCH_ZERO);
    pitch.setSpeed(130);
    pitch.setAccel(0.3);

    yaw.attach(YAW_PIN, YAW_MIN_IMP, YAW_MAX_IMP, YAW_ZERO);
    // yaw.setSpeed(130);
    // yaw.setAccel(0.3);
    yaw.setSpeed(70);
    yaw.setAccel(0.1);
}

void servo_tick()
{
    rul.tickManual();
    pitch.tickManual();
    yaw.tickManual();
}

/*
rul 37 85 130
p   32 63 83
y   32 72 110
*/
////////////////////////////////////