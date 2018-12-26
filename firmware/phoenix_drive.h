#pragma once
#include "Arduino.h"
#include "phoenix_joint.h"


typedef struct {
  double x_comp;
  double y_comp;
  uint8_t pins[3];
} JointParams;

typedef struct {
  int16_t speed;
  uint8_t mode;
} JointControl;


class HolonomicDrive {
  Joint* joints;
  JointParams* params;
  JointControl* control;
  
  public:
  HolonomicDrive();
  void init(Joint* joints, JointParams* params,
            JointControl* control);
  void move(double x, double y, double theta);
  void handle();
};