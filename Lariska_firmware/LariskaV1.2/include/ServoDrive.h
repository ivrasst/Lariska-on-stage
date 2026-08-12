#pragma once

#include <stdint.h>


void servo_init();
void servo_set(int8_t value);
void servo_set_zero();

void pitch_set(int8_t value);
void yaw_set(int8_t value);

void pitch_set_max();
void yaw_set_max();
void pitch_set_zero();
void yaw_set_zero();