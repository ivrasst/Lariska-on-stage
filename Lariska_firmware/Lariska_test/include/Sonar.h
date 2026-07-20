#pragma once

#include <Arduino.h>

#define SONAR_FORW_TRIG 100
#define SONAR_FORW_ECHO 200

#define SONAR_WALL_TRIG 100
#define SONAR_WALL_ECHO 200

int son_f_dist = 0;
int son_w_dist = 0;

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
    int16_t son_f_d = pulseIn(SONAR_FORW_ECHO, HIGH, 7000);
    son_f_dist = son_f_d / 58;

    digitalWrite(SONAR_WALL_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_WALL_TRIG, LOW);
    int16_t son_w_d = pulseIn(SONAR_WALL_ECHO, HIGH, 7000);
    son_w_dist = son_w_d / 58;
}

int son_f_get_dist()
{
    return son_f_dist;
}

int son_w_get_dist()
{
    return son_w_dist;
}


