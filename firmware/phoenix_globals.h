/**
 * phoenix_globals.h
 */
#pragma once

#include "phoenix_common.h"
#include "phoenix_pins.h"
#include "phoenix_line.h"
#include "phoenix_line_internals.h"
#include "Adafruit_ADS1015.h"

extern Adafruit_ADS1015 line_adc[NUM_LINEADC];
extern PhoenixLineDetector line_sensors[NUM_LINEDETECTORS];
extern PhoenixLineHandler line_handler;

