#pragma once

#include "Config.h"
#include "Encoder.h"
#include "Motor.h"
#include "VelEst.h"

float sm_pi(float err)
{
    static float I = 0;

    float up = err * SERVO_KP;
    float ui = I;
    float u = up + ui;

    I += err * SERVO_KI * Ts_s;

    return u;
}

void sm_tick(float w0)
{
    enc_tick();
    ve_tick(enc_get_phi());
    float w = ve_get_w_est_f();
    float err = w0 - w;
    float u = sm_pi(err);
    m_drive(u);
}

void sm_off()
{
    m_drive(0);
}
