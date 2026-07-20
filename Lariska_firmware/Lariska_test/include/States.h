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
    rul_tick(rul_phi);
    sm_tick(vel);
    h_tick(pitch_phi, yaw_phi);
}

void st_forw()
{
    pitch_phi = PITCH_ZERO;
    yaw_phi = YAW_ZERO;
    rul_phi = RUL_ZERO;
    vel = MAX_VEL;
}

void st_rotate()
{
    pitch_phi = PITCH_ZERO;
    yaw_phi = YAW_ZERO;
    son_tick();
    rul_phi = (GOAL_DIST - son_wall_get_dist()) * ROTATE_KP;
    vel = MAX_VEL;
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
// #define START_TURNING_SON_DIST 1 //[]
// #define END_TURNING_TIME 10 // [ms]
// #define TURNING_SERV_ANG 10 // [deg]
/*
int forw()
{
    int phi = RUL_ZERO;
    float forw_dist_m = 0;
    float rot_radius_m = 0;
    int rot_n = 1.5;
    float f_rad = 2*M_PI * (forw_dist_m / (2*M_PI*RAT_WHEEL_RADIUS));
    float r_rad =  2*M_PI * ((2*M_PI*rot_radius_m)*rot_n / (2*M_PI*RAT_WHEEL_RADIUS));
    
    static float start_rot_phi = 0;
    
    if(( son_f_get_dist() > START_TURNING_SON_DIST ) && ( son_f_get_dist() != 0 ))
    {
        phi = RUL_ZERO;
    }
    else
    {
        static uint32_t time_turn = millis();
        if(millis() - time_turn < END_TURNING_TIME)
        {
            phi = TURNING_SERV_ANG;
        }
        else
        {
            
        }
    }

}
*/