#pragma once
#include "ServoMotor.h"
#include "MyServos.h"
#include "Config.h"
#include "Sonar.h"
#include <AceSorting.h>

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
    // const int len = 5;
    // static int Dists[len] = {GOAL_DIST};
    // int Dists_sort[len] = {};
    // static int index = 0;
    
    static int distOld = GOAL_DIST;
    son_tick(0);
    int dist = son_wall_get_dist();
    static uint32_t rul_time = millis();
    
    if(dist == 0){
        if(distOld < GOAL_DIST && (millis() - rul_time < 250))
            dist = GOAL_DIST * 0.5;
        else{
            dist = GOAL_DIST * 1.5;
            rul_time = millis();
        }
    }

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

    int err = (GOAL_DIST - dist);
    // int err = (GOAL_DIST - med);
    static int errOld = err;

    rul_phi = RUL_ZERO + 8 + ( (err * ROTATE_KP)+((err - errOld)*ROTATE_KD) );
    
    vel = 1200;//MAX_VEL;
    

    distOld = dist;
    // distOld = med;
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


