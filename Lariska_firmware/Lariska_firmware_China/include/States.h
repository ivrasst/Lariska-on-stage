#pragma once
#include "ServoMotor.h"
#include "MyServos.h"
#include "Config.h"
#include "Sonar.h"

int pitch_phi = PITCH_ZERO;
int yaw_phi = YAW_ZERO;
int rul_phi = RUL_ZERO;
float vel = 0.0;

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
    vel = 450;
}

void st_rotate()
{
    son_tick(0);
    int dist = son_wall_get_dist();
    int fd = son_forw_get_dist();
    
    if(dist == 0)
        dist = GOAL_DIST * 1.5;
    if (fd <= 23 && fd != 0)
        dist = GOAL_DIST * 0.6;

    int err = (GOAL_DIST - dist);
    static int errOld = err;

    rul_phi = 100 + ( (err * ROTATE_KP)+((err - errOld)*ROTATE_KD) );
    
    vel = 2000;//MAX_VEL;
}

void st_stop_bow()
{
    static uint32_t time_bow = millis();
    if(time_bow <= 500)
    {
        pitch_phi = PITCH_ZERO;
        yaw_phi = YAW_MAX;
    }
    else if (time_bow <= 1000)
    {
        pitch_phi = PITCH_MAX;
        yaw_phi = YAW_MAX;
    }
    else if (time_bow <= 1500)
    {
        pitch_phi = PITCH_ZERO;
        yaw_phi = YAW_MAX;
    }
    else if (time_bow <= 2000)
    {
        pitch_phi = PITCH_ZERO;
        yaw_phi = YAW_ZERO;
    }
    rul_phi = RUL_ZERO;
    vel = 0.0;
}


