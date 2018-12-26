/**
 * phoenix_hbridge.h
 * Functions and classes to handle hbridges
 * onboard of Phoenix-class robots
 */

#pragma once
#include <Arduino.h>
#include "phoenix_status.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum {
    HBridgeTypeDualDir=0
  } HBridgeType;


  struct HBridgeOps;
  typedef struct {
    struct HBridgeOps* ops;
    union {
      struct {
        uint8_t pwm_pin;
        uint8_t dira_pin;
        uint8_t dirb_pin;
      } dualdir;
    } params;  
  } HBridge;

  OpStatus HBridge_setSpeed(HBridge* bridge, int16_t speed);
  /**
   * type=dual_dir :  pins[0]=pwm, pins[1]=dir_a, pins[2]=dir_b;
   * @returns 0 on success, <0 on failure
   */
  OpStatus HBridge_init(HBridge* bridge, const HBridgeType type, int8_t* pins);
#ifdef __cplusplus
}
#endif