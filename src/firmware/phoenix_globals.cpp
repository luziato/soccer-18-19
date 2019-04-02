/**
 * phoenix_globals.cpp
 **/

#include "phoenix_globals.h"

/*
*                         *
**********STEORA***********
*                         *
PhoenixJoint joints[NUM_JOINTS] = 
{
  //senso orario
  //dietro: joint 0  
  //destra: joint 1
  //sinistra: joint 2
  {
  // Joint 0 
  pin_dira : 23,
  pin_dirb : 28,
  pin_pwm : 3,
  direzione : 0,
  velocita : 0
  },
  {
  // Joint 1 
  pin_dira : 22,
  pin_dirb : 27,
  pin_pwm : 2,
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
  x : 39.00,
  y : 67.5499,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A0
  },
  {// Sensore 1
  x : 84.051,
  y : -22.2011,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A1
  },
  {// Sensore 2
  x : 61.6838,
  y : -61.2470,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A2
  },
  {// Sensore 3
  x : -61.2579,
  y : -61.6668,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A3
  },
  {// Sensore 4
  x : -83.8843,
  y : -22.7760,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A4
  },
  {// Sensore 5
  x : -39.00,
  y : 67.5499,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A5
  } 
};
PhoenixLineHandler line_handler;

BNO055 dev_bno055;
PhoenixImu imu = 
{
  imu : &dev_bno055,
  heading_attuale:0,
  heading_target:0,
  heading_offset:0,
  errore:0,
  output_pid:0,
  max_output:180,
  ki:80,
  kp:3,
  kd:0.005,
  errore_prec:0,
  dt:0.001,
  idt:1000,
  sum_i:0,
  max_i:180,
};

PhoenixCamera camera=
{
  ball_detection:0,
  ball_x:0,
  ball_y:0,
  ball_w:0,
  ball_h:0,
  ki:0,
  kp:1.5,
  kd:0,
  output_pid:0,
  max_output:180,
  errore:0,
  errore_prec:0,
  dt:0.02,
  idt:50.0,
  sum_i:0,
  max_i:180,
};
*/












/*
*                         *
**********YATILI***********
*                         *
*/
PhoenixJoint joints[NUM_JOINTS] = 
{
  //senso orario
  //dietro: joint 0  
  //destra: joint 1
  //sinistra: joint 2
  {
  // Joint 0 
  pin_dira : 23,
  pin_dirb : 28,
  pin_pwm : 3,
  direzione : 0,
  velocita : 0
  },
  {
  // Joint 1 
  pin_dira : 22,
  pin_dirb : 27,
  pin_pwm : 2,
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
  x : 0.5,
  y : 0.866,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A0
  },
  {// Sensore 1
  x : 0.98,
  y : -0.173,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A1
  },
  {// Sensore 2
  x : 0.642,
  y : -0.766,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A2
  },
  {// Sensore 3
  x : -0.642,
  y : -0.766,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A3
  },
  {// Sensore 4
  x : -0.984,
  y : 0.17,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A4
  },
  {// Sensore 5
  x : -0.5,
  y : 0.866,
  soglia : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  pin_reading: A5
  } 
};
PhoenixLineHandler line_handler;

BNO055 dev_bno055;
PhoenixImu imu = 
{
  imu : &dev_bno055,
  heading_attuale:0,
  heading_target:0,
  heading_offset:0,
  errore:0,
  output_pid:0,
  max_output:180,
  ki:122.5,
  kp:3,
  kd:0.00055,
  errore_prec:0,
  dt:0.001,
  idt:1000,
  sum_i:0,
  max_i:180,
};

PhoenixCamera camera=
{
  ball_detection:0,
  ball_x:0,
  ball_y:0,
  ball_w:0,
  ball_h:0,
  ki:0.07,
  kp:1.5,
  kd:0.07,
  output_pid:0,
  max_output:180,
  errore:0,
  errore_prec:0,
  dt:0.02,
  idt:50.0,
  sum_i:0,
  max_i:180,
};


