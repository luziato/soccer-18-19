//mine

#define phoenixglobal_h
#define NUM_MOTORS 3
#include <Arduino.h>
#include "phoenixjoint.h"
#include "phoenixdrive.h"

JointDati dati [NUM_MOTORS]=
{
  //dato[0]
  {
    .x_comp=0,
    .y_comp=0,
    .pins{7,1,3}
  },
  //dato[1]
  {
    .x_comp=0,
    .y_comp=0,
    .pins{9,2,4}
  },
  //dato[2]
  {
    .x_comp=0,
    .y_comp=0,
    .pins{8,5,6}
  }
};

Joint joints[NUM_MOTORS];

/*
*joints[0]={.pin_pwm=dati[0].pins[0],.pin_dira=dati[0].pins[1],.pin_dirb=dati[0].pins[2]};
*joints[1]={.pin_pwm=dati[1].pins[0],.pin_dira=dati[1].pins[1],.pin_dirb=dati[1].pins[2]};
*joints[2]={.pin_pwm=dati[2].pins[0],.pin_dira=dati[2].pins[1],.pin_dirb=dati[2].pins[2]};
*/
JointControl control[NUM_MOTORS]=
{
  //control[0]
  {
    .speed=0,
    .mode=0
  }
  //control[1]
  {
    .speed=0,
    .mode=0
  }
  //control[2]
  {
    .speed=0,
    .mode=0
  }
};
