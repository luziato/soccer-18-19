#pragma once
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum {
    JointDisabled=0,
    JointPWM=1,
    JointPID=2
  } JointMode;
  /**
  typedef struct {
    uint16_t encoder_position;
    int16_t encoder_speed;
    int16_t desired_speed;
    int16_t pwm;
    int16_t sensed_current;
    uint8_t mode;
  } JointInfo;

  typedef struct {
    int16_t kp, ki, kd;
    int16_t max_i;
    int16_t min_pwm, max_pwm;

    int16_t max_speed;
    int16_t slope;
    uint8_t h_bridge_type;
    int8_t h_bridge_pins[3];
  } JointParams;

  typedef struct {
    int16_t speed;
    uint8_t mode;
  } JointControl;
  **/
#ifdef __cplusplus
}
#endif