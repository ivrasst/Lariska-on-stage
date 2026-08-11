#pragma once

class PID {
public:
    PID() = default;
    PID(float kp, float ki, float kd, float out_min, float out_max)
        : Kp(kp), Ki(ki), Kd(kd), out_min(out_min), out_max(out_max)
        , integrator(0), prev_error(0) {}

    float compute(float setpoint, float process_value);
    void set(float kp, float ki, float kd) {
        Kp = kp;
        Ki = ki;
        Kd = kd;
    }
    void reset();
    float Kp = 0;
    float Ki = 0;
    float Kd = 0;
private:

    float out_min = 0;
    float out_max = 0;
    float integrator = 0;
    float prev_error = 0;
};