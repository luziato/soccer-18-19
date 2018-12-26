//mine
#include "phoenix_globals.h"

Adafruit_ADS1015 line_adc[4] 
{  //dichiaro i sensori di linea 
    Adafruit_ADS1015(0),
    Adafruit_ADS1015(1),
    Adafruit_ADS1015(2),
    Adafruit_ADS1015(3)
};

PhoenixLineDetector line_sensors[NUM_LINEDETECTORS] = 
{
  { // 0
    index : 0,
    detected : 0,
    x : 0,
    y : 0,
    threshold : 0,
    reading : 0,
    adc_addr : 0,
    adc_idx : 0
  },
  { // 1
    index : 1,
    detected : 0,
    x : 0,
    y : 0,
    threshold : 0,
    reading : 0,
    adc_addr : 0,
    adc_idx : 0
  }
};

PhoenixLineHandler line_handler = 
{
  ld : line_sensors,
  mask : 0x0,
  border_x : 0,
  border_y : 0,
  escape_flag : 0,
  escape_direction : {0, 0, 0},
  escape_ttl : ESCAPE_TTL
};
