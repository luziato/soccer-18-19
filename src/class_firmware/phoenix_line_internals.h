//mine
#pragma once
#include <Arduino.h>
#include "Adafruit_ADS1015.h"



typedef struct {
  uint16_t soglia;  
  uint8_t rilevato; 
  uint16_t valore_letto;
  
  uint8_t adc_addr;
  uint8_t adc_idx;
} PhoenixLineDetector;

void PhoenixLineDetector_init(PhoenixLineDetector*);
                              
OpStatus PhoenixLineDetector_handle(PhoenixLineDetector*);

void PhoenixLineDetector_reset(PhoenixLineDetector*);
