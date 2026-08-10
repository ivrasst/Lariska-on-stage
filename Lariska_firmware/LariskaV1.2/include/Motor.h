#pragma once

#include <stdint.h>

void motor_init();
void motor_update();
void motor_set_rpm(uint16_t rpm);
uint16_t motor_get_rpm();