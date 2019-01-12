//mine
#pragma once
#include <Arduino.h>
#include "phoenix_line_internals.h"
#include "phoenix_status.h"

#define ESCAPE_TTL 2000

uint8_t mask_read(uint16_t* mask, uint8_t index);
void mask_setBit(uint16_t* mask, uint8_t index);
void mask_clearBit(uint16_t* mask, uint8_t index);

typedef struct 
{
  PhoenixLineSensor* line_sensors;
  uint16_t mask=0;

  uint8_t escape_flag;
  double escape_x;
  double escape_y;

  uint8_t calib_flag;
  uint16_t escape_ttl;
} PhoenixLineHandler;

void PhoenixLineHandler_init(PhoenixLineHandler* h, PhoenixLineSensor* s);

void PhoenixLineHandler_handle(PhoenixLineHandler* h);

uint8_t PhoenixLineHandler_getStatus(PhoenixLineHandler* h);

double PhoenixLineHandler_getEscapeX(PhoenixLineHandler* h);

double PhoenixLineHandler_getEscapeY(PhoenixLineHandler* h);

void PhoenixLineHandler_reset(PhoenixLineHandler* h);
