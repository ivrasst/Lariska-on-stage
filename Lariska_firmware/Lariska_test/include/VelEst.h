#pragma once
#include "Config.h"

float ve_w_est = 0;
float ve_w_est_f = 0;

void ve_init()
{
}

void ve_tick(float phi)
{
    static float phi_old = phi;
    float dphi = phi - phi_old;
    ve_w_est = dphi / Ts_s;
    phi_old = phi;

    static float I = 0;
    float e = ve_w_est - ve_w_est_f;
    float s = e / VE_LPF_T;
    I += s * Ts_s;
    ve_w_est_f = I;
}

float ve_get_w_est_f()
{
    return ve_w_est_f;
}

