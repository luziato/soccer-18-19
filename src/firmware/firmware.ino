/**
   
   firmware.ino

-----------------------------------------------------

   Copyright 2018 Emanuele Giacomini
   
   Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
   
       http://www.apache.org/licenses/LICENSE-2.0
   
   Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and limitations under the License.
**/

#include "phoenix_params.h"
#include "phoenix_globals.h"
#include "phoenix_joints.h"
#include "phoenix_drive.h"
#include "phoenix_line_internals.h"
#include "phoenix_line.h"
#include "phoenix_imu.h"
#include "phoenix_timer.h"

struct Timer* test1;

void setup() 
{
  cli();
  Serial.begin(9600);
  Serial.println("Serial initialized...");

  for(int i=0;i<NUM_JOINTS;++i) {
    PhoenixJoint_init(&joints[i]);
  }
  Serial.println("Joints initialized...");
  PhoenixDrive_init(&drive, joints);
  Serial.println("Drive initialized...");

  for(int i=0;i<NUM_LINE_SENSORS;++i) {
    Serial.println("ok: " + i);
    PhoenixLineSensor_init(&line_sensors[i]);
  }
  
  Serial.println("Line Sensors initialized...");
  PhoenixLineHandler_init(&line_handler, line_sensors);
  Serial.println("Line Handler initialized...");

//  Timer_init();
  test1 = Timer_create(100, &testTimerFn, 0);
  struct Timer* test_joint_timer=Timer_create(1000, &testJointsFn, 0);
  Timer_start(test1);
  Timer_start(test_joint_timer);
  Serial.println("Timer initialized...");
  sei();
}

volatile uint16_t idle_time=0;
volatile uint8_t test_joint_fn_state=0;
volatile uint8_t test_joint_fn_joint_idx=0;

void testJointsFn() 
{
  switch(test_joint_fn_state) 
  {
  case 0:
    PhoenixJoint_setSpeed(&joints[test_joint_fn_joint_idx%3], 255);
    PhoenixJoint_handle(&joints[test_joint_fn_joint_idx%3]);
    break;
  case 1:
    PhoenixJoint_setSpeed(&joints[test_joint_fn_joint_idx%3], -255);
    PhoenixJoint_handle(&joints[test_joint_fn_joint_idx%3]);
    break;
  case 3:
    PhoenixJoint_setSpeed(&joints[test_joint_fn_joint_idx%3], 0);
    PhoenixJoint_handle(&joints[test_joint_fn_joint_idx%3]);
    test_joint_fn_joint_idx++;
    break;
  }
  test_joint_fn_state++;
  if(test_joint_fn_state>3)
    test_joint_fn_state=0;
}

void testTimerFn() 
{
  Serial.println(idle_time);
  idle_time=0;
}

void loop() 
{
  idle_time++;
  Serial.println("sono nel loop");
  PhoenixDrive_setSpeed(&drive, 0, 1, 0);
  //il primo valore è la y
  //il secondo è la rotazione
  //il terzo è la x
  PhoenixDrive_handle(&drive);
}
