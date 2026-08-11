#include "Dist.h"

#include <Arduino.h>
#include <VL53L0X.h>
#include <AceSorting.h>

#define DIST_ARR_LEN 3
#define DIST_INTERRUPT 2
static void dist_interrupt();

static VL53L0X sensor;
static uint16_t dist_value = 0, dist_last = 0;

static volatile bool dist_data_ready = false;

static uint16_t buff_arr[DIST_ARR_LEN] = {0};
static uint8_t buff_index = 0, zero_counter = 0;

void dist_init() {
  Wire.begin();
  
  pinMode(DIST_INTERRUPT, INPUT_PULLUP);

  Serial.print("INIT: ");
  bool init_ok = sensor.init();
  Serial.println(init_ok);

  if (!init_ok) {
    Serial.println("VL53L0X init failed!");
    return;
  }

  sensor.setTimeout(500);
  sensor.startContinuous();

  attachInterrupt(digitalPinToInterrupt(DIST_INTERRUPT), dist_interrupt, FALLING);
}

void dist_update() {
    if (!dist_data_ready) return;

    dist_data_ready = false;

    uint16_t new_value = sensor.readRangeContinuousMillimeters();   

    if (new_value == 0 || new_value >= 600 || sensor.timeoutOccurred()) {
      zero_counter++;
      if (zero_counter >= DIST_ARR_LEN) {
        memset(buff_arr, 0, sizeof(buff_arr));
        dist_value = 0;
        dist_last = 0;
      }
      return;
    } else {
      zero_counter = 0;
    }

    buff_arr[buff_index] = new_value;
    buff_index = (buff_index + 1) % DIST_ARR_LEN;

    uint16_t temp_arr[DIST_ARR_LEN];
    memcpy(temp_arr, buff_arr, sizeof(buff_arr));
    ace_sorting::shellSortKnuth(temp_arr, DIST_ARR_LEN);
    
    uint16_t median_value = temp_arr[DIST_ARR_LEN / 2];

    constexpr float alpha = 0.9f; 

    if (dist_last == 0) {
        dist_last = median_value;
        dist_value = median_value;
        return;
    }

    dist_value = (uint16_t)(alpha * median_value + (1.0f - alpha) * dist_last);
    dist_last = dist_value;
}

uint16_t dist_get() {
    return dist_value;
}

static void dist_interrupt() {
  dist_data_ready = true;
}