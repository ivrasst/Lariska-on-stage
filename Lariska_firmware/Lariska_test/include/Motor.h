#pragma once

#include <Arduino.h>

#define M_INA_PIN 10 //*!
#define M_INB_PIN 11
#define M_PWM_PIN 12

void m_init()
{
    pinMode(M_INA_PIN, OUTPUT);
    pinMode(M_INB_PIN, OUTPUT); 
}

void m_drive(float pwm)
{
    int dir = pwm > 0;
    pwm = constrain(pwm, 0, 255);
    digitalWrite(M_INA_PIN, dir);
    digitalWrite(M_INB_PIN, !dir);
    analogWrite(M_PWM_PIN, pwm);
}