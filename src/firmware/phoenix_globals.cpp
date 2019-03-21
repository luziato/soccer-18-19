/**
 * phoenix_globals.cpp
 **/

#include "phoenix_globals.h"

PhoenixJoint joints[NUM_JOINTS] = 
{
  //senso orario
  //destra: joint 0  
  //dietro: joint 1
  //sinistra: joint 2
  {
  // Joint 0 
  pin_dira : 22,
  pin_dirb : 27,
  pin_pwm : 2,
  direzione : 0,
  velocita : 0
  },
  {
  // Joint 1 
  pin_dira : 23,
  pin_dirb : 28,
  pin_pwm : 3,
  direzione : 0,
  velocita : 0
  },
  {
  // Joint 2 
  pin_dira : 24,
  pin_dirb : 29,
  pin_pwm : 4,
  direzione : 0,
  velocita : 0
  }
};


PhoenixDrive drive;

PhoenixLineSensor line_sensors[NUM_LINE_SENSORS] = 
{
  {// Sensore 0
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: 0
  },
  {// Sensore 1
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: 0
  },
  {// Sensore 2
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: 0
  },
  {// Sensore 3
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: 0
  },
  {// Sensore 4
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: 0
  }
};
PhoenixLineHandler line_handler;

BNO055 dev_bno055;
PhoenixImu imu;
