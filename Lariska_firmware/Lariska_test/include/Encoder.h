#pragma once
#include <Arduino.h>

#define ENC_INT_PIN 2
#define ENC_DIR_PIN 3

#define ENC_DIR 1

#define ENC_TICK_TO_RAD (374/360.0)

float enc_phi = 0.0;
volatile int enc_counter = 0;
volatile int32_t enc_t = 0;

void enc_interruupt() {
  if (digitalRead(3)) enc_counter += ENC_DIR;
  else enc_counter -= ENC_DIR;
}

void enc_init() {
  pinMode(3, 0);
  attachInterrupt(0, enc_interruupt, 3);
}

void enc_tick()
{
    noInterrupts();
    int c = enc_counter;
    enc_counter = 0;
    interrupts();
    enc_phi += ENC_TICK_TO_RAD * c;
    enc_t += c;
}

float enc_get_phi()
{
    return enc_phi;
}

int enc_get_tick_s()
{
    noInterrupts();
    int ret = enc_counter;
    interrupts();
    return ret;
}



////////////////////////////////////////////

// int8_t enc_tt[4][4] = {0};

// void enc_interrupt()
// {
//     int B = digitalRead(ENC_DIR_PIN);
//     int CA = digitalRead(ENC_INT_PIN);
//     int A = CA ^ B;
//     int AB = A << 1 | B;
//     static int old_AB = AB;

//     enc_counter += enc_tt[old_AB][AB];
//     old_AB = AB;
// }

// void enc_init()
// {
//     pinMode(ENC_INT_PIN, INPUT);
//     pinMode(ENC_DIR_PIN, INPUT);

//     enc_tt[0b00][0b01] = ENC_DIR;
//     enc_tt[0b01][0b11] = ENC_DIR;
//     enc_tt[0b11][0b10] = ENC_DIR;
//     enc_tt[0b10][0b00] = ENC_DIR;

//     enc_tt[0b00][0b10] = -ENC_DIR;
//     enc_tt[0b10][0b11] = -ENC_DIR;
//     enc_tt[0b11][0b01] = -ENC_DIR;
//     enc_tt[0b01][0b00] = -ENC_DIR;

//     attachInterrupt(digitalPinToInterrupt(ENC_INT_PIN), enc_interrupt, CHANGE);    
// }

// int enc_get_tick_s()
// {
//     noInterrupts();
//     int ret = enc_counter;
//     interrupts();
//     return ret;
// }

// void enc_tick()
// {
//     noInterrupts();
//     int c = enc_counter;
//     enc_counter = 0;
//     interrupts();
//     enc_phi += ENC_TICK_TO_RAD * c  ;
// }

// float enc_get_phi()
// {
//     return enc_phi;
// }
