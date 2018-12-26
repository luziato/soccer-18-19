/**
 * phoenix_line.h
 */
#pragma once
#include <Arduino.h>
#include "phoenix_line_internals.h"
#include "phoenix_status.h"

#define ESCAPE_TTL 2000

typedef struct {
  PhoenixLineDetector* ld;
  uint16_t mask; 
  
  double border_x;
  double border_y;
  uint8_t escape_flag;
  uint16_t escape_direction[3];
  
  int16_t escape_ttl;
} PhoenixLineHandler;

void PhoenixLineHandler_init(PhoenixLineHandler*,
                            PhoenixLineDetector*);

OpStatus PhoenixLineHandler_handle(PhoenixLineHandler*);

void PhoenixLineHandler_reset(PhoenixLineHandler*);