#include "IR.h"

#include <AceSorting.h>
#define IR_ARR_LEN 3
#define IR_K_VES 0.75

static uint16_t ir_dist = 0, ir_dist_old = 0;

static uint16_t ir_buff_arr[IR_ARR_LEN] = {0};
static uint8_t ir_buff_index = 0;

void ir_update()
{
  uint16_t new_value = analogRead(A4);
  ir_buff_arr[ir_buff_index] = new_value;
  ir_buff_index = (ir_buff_index + 1) % IR_ARR_LEN;

  uint16_t temp_arr[IR_ARR_LEN];
  memcpy(temp_arr, ir_buff_arr, sizeof(ir_buff_arr));
  ace_sorting::shellSortKnuth(temp_arr, IR_ARR_LEN);
    
  uint16_t median_value = temp_arr[IR_ARR_LEN / 2];

  ir_dist = (uint16_t)(IR_K_VES * median_value + (1.0f - IR_K_VES) * ir_dist_old);
  ir_dist_old = ir_dist;
}

uint16_t ir_get()
{
  return ir_dist;
}