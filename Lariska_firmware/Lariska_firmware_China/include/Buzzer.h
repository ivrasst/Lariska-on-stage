#pragma once
#include <Arduino.h>
#include "Config.h"
#define BUZ_PIN A1

void buz_init()
{
    pinMode(BUZ_PIN, OUTPUT);
    digitalWrite(BUZ_PIN, LOW);
}

void buz_state(bool buz_state)
{
    digitalWrite(BUZ_PIN, buz_state);
}

bool buz_squeak()
{
    static uint32_t sq_time = millis();
    uint32_t dtime = millis() - sq_time;
    if(dtime > ALL_SQUEAK_TIME)
    {
        if(dtime > (ALL_SQUEAK_TIME/6))
            buz_state(HIGH);
        if(dtime > 2*(ALL_SQUEAK_TIME/6))
            buz_state(LOW);
        if(dtime > 3*(ALL_SQUEAK_TIME/6))
            buz_state(HIGH);
        if(dtime > 4*(ALL_SQUEAK_TIME/6))
            buz_state(LOW);
        if(dtime > 5*(ALL_SQUEAK_TIME/6))
            buz_state(HIGH);
        if(dtime > 6*(ALL_SQUEAK_TIME/6))
            buz_state(LOW);
        return 1;
    }
    else
    {
        return 0;
    }
}