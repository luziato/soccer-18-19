#include "phoenix_joint.h"

Joint::Joint() {}

void Joint::init(uint8_t* pins) {
  uint8_t* pin_pwm = &pins[0];
  uint8_t* pin_dira = &pins[1];
  uint8_t* pin_dirb = &pins[2];

  pinMode(*pin_pwm, OUTPUT);
  analogWrite(*pin_pwm, 0);

  pinMode(*pin_dira, OUTPUT);
  digitalWrite(*pin_dira, 0);

  pinMode(*pin_dirb, OUTPUT);
  digitalWrite(*pin_dirb, 0);

  this->_pin_pwm = *pin_pwm;
  this->_pin_dira = *pin_dira;
  this->_pin_dirb = *pin_dirb;
}

void Joint::setSpeed(int16_t speed) {
  uint16_t pwm=0;
  uint8_t dir=0;

  if(speed>=0) {
    pwm=speed;
    dir=0;
  } else {
    pwm=-speed;
    dir=1;
  }
  if(pwm>255)
    pwm=255;
  
  this->_pwm=pwm;
  this->_dir=dir;
} 

void Joint::handle() {
  digitalWrite(_pin_dira, _dir);
  digitalWrite(_pin_dirb, !_dir);
  analogWrite(_pin_pwm, _pwm);
}