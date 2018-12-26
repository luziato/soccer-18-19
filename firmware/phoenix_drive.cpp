#include "phoenix_drive.h"

static double imatrix[NUM_MOTORS][NUM_MOTORS] =
  {
    {0.33, -0.33, 0.57},
    {0.33, -0.33, -0.57},
    {0.33, 0.66, 0}
  };

HolonomicDrive::HolonomicDrive() {}

void HolonomicDrive::init(Joint* joints, JointParams* params,
            JointControl* control) {
  this->joints=joints;
  this->params=params;
  this->control=control;
  
  int i;
  for(i=0;i<NUM_MOTORS;++i) {
    joints[i].init(params->pins);
  }
}

void HolonomicDrive::move(double x, double y, double theta) {
  int r,j;
  double comp_vec[3] = {theta, x, y};
  double speed=0;
  // calculate joints speeds through the inverse kinematics matrix
  // it's just a matrix product between the inverse matrix and movement components vector
  for(r=0;r<NUM_MOTORS;++r) {
    for(j=0;j<NUM_MOTORS;++j) {
      speed+=imatrix[r][j]*comp_vec[j];
    }
    control[r].speed=(int16_t)speed;
    speed=0;
  }
}

void HolonomicDrive::handle() {
  int i;
  for(i=0;i<NUM_MOTORS;++i) {
    joints[i].setSpeed(control[i].speed);
    joints[i].handle();
  }
}
