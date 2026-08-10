#include "Motor.h"

#include <Arduino.h>
#include "PID.h"



#define M_TICKS 375
#define M_PIN_INA 5
#define M_PIN_INB 4
#define M_PIN_PWM 6
#define M_ENC_INT 2
#define M_ENC_DIR 3

static PID pid(1.5, 1, 0, 0, 350);
static void motor_interrupt();
static void motor_pwm(int16_t pwm);

static float enc_timer = 0, enc_period = 0, enc_count = 0;
static float rpm_set = 0, rpm_last = 0;

void motor_init() {
    pid.reset();

    pinMode(M_PIN_INA, OUTPUT);
    pinMode(M_PIN_INB, OUTPUT);
    pinMode(M_PIN_PWM, OUTPUT);
    pinMode(M_ENC_DIR, INPUT);
    pinMode(M_ENC_INT, INPUT);

    attachInterrupt(digitalPinToInterrupt(M_ENC_INT), motor_interrupt, RISING);
}

void motor_update() {
    // float rpm_set_local = rpm_set;
    // if (rpm_set_local < 20) rpm_set_local = 20;
    // float kp = 0.03 * rpm_set_local + 0.7;
    // float ki = 0.02 * rpm_set_local + 0.8;
    // pid.set(kp, ki, 0);

    float real = motor_get_rpm();
    float res = pid.compute(rpm_set, real);
    Serial.print(real);
    Serial.print(",");
    Serial.println(res);


    motor_pwm(res);


    if (micros() - enc_timer > 10000) {
        rpm_last = 0;
        return;
    }

    float rpm = (1000000 / enc_period) / M_TICKS * 60;
    rpm_last = rpm;
}

void motor_set_rpm(uint16_t rpm) {
    rpm_set = rpm;
}

uint16_t motor_get_rpm() {
    return rpm_last;
}

static void motor_pwm(int16_t pwm) {
    int dir = pwm > 0;
    pwm = constrain(pwm, 0, 255);
    digitalWrite(M_PIN_INA, dir);
    digitalWrite(M_PIN_INB, !dir);
    analogWrite(M_PIN_PWM, pwm);
}

static void motor_interrupt() {
    uint32_t now = micros();
    enc_period = now - enc_timer;
    enc_timer = now;

    if (digitalRead(M_ENC_DIR))
        enc_count++;
    else
        enc_count--;
}