/**
 * phoenix_line_internals.h
 */
#pragma once
#include <Arduino.h>
#include "phoenix_common.h"
#include "phoenix_status.h"
#include "Adafruit_ADS1015.h"



typedef struct {
  uint16_t index;  // index of triggered element
  uint8_t detected; // detected flag
  double x;
  double y;
  uint16_t threshold;
  uint16_t reading;
  
  uint8_t adc_addr;
  uint8_t adc_idx;
} PhoenixLineDetector;

void PhoenixLineDetector_init(PhoenixLineDetector*);
                              
OpStatus PhoenixLineDetector_handle(PhoenixLineDetector*);

void PhoenixLineDetector_reset(PhoenixLineDetector*);
