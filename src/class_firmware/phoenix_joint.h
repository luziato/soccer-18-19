//mine
#include <Arduino.h>
#include "phoenix_globals.h"
#include "phoenix_status"

class Joint //creo una nuova classe Joint
{
private: //creo delle variabili private
  uint8_t*pins[3];
  unit8_t pin_pwm;
  unit8_t pin_dira;
  unit8_t pin_dirb;
  uint8_t* pins;
  int16_t speed;
public://dichiaro le varie funzioni che implementerò nel file cpp
  void Joint::init(uint8_t* pins);
  void Joint::setSpeed(int16_t speed);
  void Joint::handle();
};
