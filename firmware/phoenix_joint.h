#pragma once

#include <Arduino.h>
#include "phoenix_globals.h"
#include "phoenix_status.h"

class Joint {
  uint8_t _pin_pwm;
  uint8_t _pin_dira;
  uint8_t _pin_dirb;
  
  uint8_t _pwm;
  uint8_t _dir;

  public:
  Joint();
  /**
   * pins[0] -> pwm
   * pins[1] -> dira
   * pins[2] -> dirb
   */
  void init(uint8_t* pins);
  void setSpeed(int16_t speed);
  void handle();
};