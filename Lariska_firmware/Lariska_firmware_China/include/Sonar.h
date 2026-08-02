#pragma once

#include <Arduino.h>

#define SONAR_FORW_TRIG 11
#define SONAR_FORW_ECHO 7

#define SONAR_WALL_TRIG 13
#define SONAR_WALL_ECHO 12

int son_forw_dist = 0;
int son_wall_dist = 0;

void son_init()
{
    pinMode(SONAR_FORW_TRIG, OUTPUT);
    pinMode(SONAR_FORW_ECHO, INPUT);

    pinMode(SONAR_WALL_TRIG, OUTPUT);
    pinMode(SONAR_WALL_ECHO, INPUT);
}

void son_tick()
{
    digitalWrite(SONAR_FORW_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_FORW_TRIG, LOW);
    int16_t son_forw_d = pulseIn(SONAR_FORW_ECHO, HIGH, 11000);
    son_forw_dist = son_forw_d / 58;

    digitalWrite(SONAR_WALL_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_WALL_TRIG, LOW);
    int16_t son_wall_d = pulseIn(SONAR_WALL_ECHO, HIGH, 8000);
    son_wall_dist = son_wall_d / 58;
}


/// @brief 
/// @param choose_son=0 Wall  
/// @param choose_son=1 Forw
void son_tick(bool choose_son)
{
    if(choose_son)
    {
        digitalWrite(SONAR_FORW_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(SONAR_FORW_TRIG, LOW);
        int16_t son_forw_d = pulseIn(SONAR_FORW_ECHO, HIGH, 11000);
        son_forw_dist = son_forw_d / 58;
    }
    else if(!choose_son)
    {
        digitalWrite(SONAR_WALL_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(SONAR_WALL_TRIG, LOW);
        int16_t son_wall_d = pulseIn(SONAR_WALL_ECHO, HIGH, 8000);
        son_wall_dist = son_wall_d / 58;
    }
}

int son_forw_get_dist()
{
    return son_forw_dist;
}

int son_wall_get_dist()
{
    return son_wall_dist;
}


