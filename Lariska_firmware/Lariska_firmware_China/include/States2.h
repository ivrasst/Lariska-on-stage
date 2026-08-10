#pragma once
#include <Arduino.h>

#include "ServoMotor.h"
#include "MyServos.h"
#include "Config.h"
#include "Sonar.h"
#include "Sharp.h"

#define SERV_DELAY 200

void st2_to_cheburashka()
{
    Rul.write(RUL_ZERO);
    delay(SERV_DELAY);


    son_tick(1);
    static int dist = son_forw_get_dist();
    while ((dist == 0) || (dist >= 40))
    {
      static uint32_t timer = micros();
      while (micros() - timer < Ts_us)
      ;
      timer = micros();
      
      sm_tick(VEL_T_F);

      son_tick(1);
      dist = son_forw_get_dist();
    }
    sm_off();
}

void sr2_forw(uint32_t timeTurn)
{
    Rul.write(RUL_ZERO);
    delay(SERV_DELAY);

    uint32_t tFoo = millis();
    while (millis() - tFoo < timeTurn)
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();

        sm_tick(VEL_T);
        
    }
    sm_off();
}

void sr2_turnR(uint32_t timeTurn)
{
    Rul.write(RUL_MAX);
    delay(SERV_DELAY);

    uint32_t tFoo = millis();
    while (millis() - tFoo < timeTurn)
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();

        sm_tick(VEL_T);
        
    }
    sm_off();
}

void sr2_turnL(uint32_t timeTurn)
{
    Rul.write(RUL_MIN);
    delay(SERV_DELAY);

    uint32_t tFoo = millis();
    while (millis() - tFoo < timeTurn)
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();

        sm_tick(VEL_T);
        
    }
    sm_off();
}

//====================================    PD    ====================================
void st2_rotate_PD(float kp = 0.45, float kd = 0.0, float velo = 800/*MAX_VEL*/, uint32_t timeTurn = 11000, int ust = 200)
{
    Rul.write(RUL_ZERO);
    delay(SERV_DELAY);
    uint32_t tFoo = millis();
    while (millis() - tFoo < timeTurn)
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();

        int dist = sharpF();
        if(dist < 153) dist = 1;
        // static int distOld = dist;

        int err = (dist - ust);
        static int errOld = err;

        int angle = RUL_ZERO + (err*kp) + ((err - errOld)*kd);
        errOld = err;
        Serial.println(dist);
        Rul.write(angle);
        // delay(SERV_DELAY/2);

        sm_tick(velo);
        
    }
    sm_off();
}

//====================================    LQR    ====================================

void st2_rotate_lqr(float velo = 800/*MAX_VEL*/, uint32_t timeTurn = 11000, float ust = 0.30)
{
    // Rul.write(RUL_ZERO);
    // delay(SERV_DELAY);


    const float L = 0.178;              
    const float l1 = 0.0273;            
    const float l2 = 0.095;            
    const float b = l1 - l2;
    const float target_distance = ust;

    const float R_cylinder = 0.48*0.5;
    const float R_robot = R_cylinder + target_distance;

    const float k1 = 1.45; 
    const float k2 = 0.85;


    uint32_t tFoo = millis();
    while (millis() - tFoo < timeTurn)
    {
        static uint32_t timer = micros();
        while (micros() - timer < Ts_us)
        ;
        timer = micros();

        float distF = sharpF_m();
        float distC = sharpC_m();
        
        Serial.println(String(distF)+ '\t' + String(distC));

        float d1 = distF - target_distance;
        float d2 = distC - target_distance;

        float theta = (d1 - d2) / b;
        float y = d2 - l2 * theta;

        float u_lqr = - (k1 * y + k2 * theta);

        ///
        float u_ff = L / R_robot;

        float u = u_ff + u_lqr;

        float ures = atan(u)* 57.2958;

        int angle = RUL_ZERO + ures;

        Rul.write(angle);
        // delay(SERV_DELAY/2);

        // m_drive(210);
        sm_tick(velo);
        
    }
    sm_off();
}