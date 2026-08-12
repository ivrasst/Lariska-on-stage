#include "Sonar.h"

#define SONAR_FORW_TRIG 11
#define SONAR_FORW_ECHO 7

uint16_t son_dist = 0;

void son_init()
{
    pinMode(SONAR_FORW_TRIG, OUTPUT);
    pinMode(SONAR_FORW_ECHO, INPUT);
}

void son_update()
{
    digitalWrite(SONAR_FORW_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_FORW_TRIG, LOW);
    son_dist = (pulseIn(SONAR_FORW_ECHO, HIGH, 3000))/58;
}

uint16_t son_get()
{
    return son_dist;
}