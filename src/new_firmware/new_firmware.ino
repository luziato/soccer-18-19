//mine
#pragma once
#include <Arduino.h>
#include "phoenix_joints.h"
#include "phoenix_drive.h"
#include "phoenix_params.h"
#include "phoenix_timer.h"

PhoenixJoint joints[NUM_JOINTS] = 
{
  {// Joint 0
    pin_dira : 24,
    pin_dirb : 25,
    pin_pwm : 7,
    direzione : 0,
    velocita : 0
  },
  {// Joint 1
    pin_dira : 32,
    pin_dirb : 33,
    pin_pwm : 8,
    direzione : 0,
    velocita : 0
  },
  {// Joint 2
    pin_dira : 36,
    pin_dirb : 37,
    pin_pwm : 6,
    direzione : 0,
    velocita : 0
  }
};
// drive per pilotare la piattaforma
PhoenixDrive drive;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Serial initialized...");

  for(int i=0;i<NUM_JOINTS;++i) 
  {
    PhoenixJoint_init(&joints[i]);
  }
  PhoenixDrive_init(&drive, joints);
  
  
  struct Timer* timer_ptr=Timer_create(100, &testTimerFn, 0);
  Timer_start(timer_ptr);
  Timer_init();
}

long unsigned int counter=0;

void testTimerFn() {
  Serial.println(counter);
  counter=0;
}

void loop() 
{
  
  counter++;
  /**for(int i=0;i<3;i++)
  {
    
    Serial.println("la i è: "+ i);
    PhoenixJoint_setSpeed(&joints[i],100);
    PhoenixJoint_handle(&joints[i]);
    Serial.println(joints[i].velocita);
    Serial.println(joints[i].direzione);
    delay(1000);
    PhoenixJoint_setSpeed(&joints[i],-100);
    PhoenixJoint_handle(&joints[i]);
    Serial.println("la velotcità è: "+ joints[i].velocita);
    Serial.println("la direzione è: "+ joints[i].direzione);
    delay(1000);
    PhoenixJoint_setSpeed(&joints[i],0);
    PhoenixJoint_handle(&joints[i]);
    Serial.println("la velotcità è: "+ joints[i].velocita);
    Serial.println("la direzione è: "+ joints[i].direzione);
    delay(1000);
  }
 **/
}
