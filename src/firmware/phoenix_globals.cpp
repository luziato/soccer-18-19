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
  {
    x : 0,
    y : 0,
    //pos rispetto alla circonferenza
    // tutto a destra x1;y0
    // sen y e cos per x
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
  {
    x : 0,
    y : 0,
    //pos rispetto alla circonferenza
    // tutto a destra x1;y0
    // sen y e cos per x
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


