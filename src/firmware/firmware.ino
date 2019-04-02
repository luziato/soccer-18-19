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
#include "phoenix_pixy.h"
#include "phoenix_eeprom.h"
#include "utils.h"
struct Timer* test1;
bool cal=true;
//funzione caliba
/*
e start calib
faccio giraare il robot su se stesso
nel frattempo lancio phonix line handler,
fermo il robot e fermo la calibrazione,
dopodichè lancio store line sensor (sulla eeprom)
*/
//se non caliobro
/* carico i dati dalla emprom
load line sensor*/
void calibrazioneON()
{
  int start=millis(),attuale;
  PhoenixLineHandler_startCalib(&line_handler);
  while(attuale-start<(10000))
  {
    PhoenixDrive_setSpeed(&drive, 0, 0, 1);
    PhoenixDrive_handle(&drive);
    PhoenixLineHandler_handle(&line_handler);
    attuale=millis();
  }
    PhoenixDrive_setSpeed(&drive, 0, 0, 0);
    PhoenixDrive_handle(&drive);
    PhoenixLineHandler_stopCalib(&line_handler);
    PhoenixEeprom_storeLineSensor();
}

void calibrazioneOFF()
{
  PhoenixEeprom_loadLineSensor();
}

void setup() 
{
  
  cli();
  Serial.begin(9600);
  Serial.println("Serial initialized...");

  for(int i=0;i<NUM_JOINTS;++i) 
  {
    PhoenixJoint_init(&joints[i]);
  }
  Serial.println("Joints initialized...");
  PhoenixDrive_init(&drive, joints);
  Serial.println("Drive initialized...");

  for(int i=0;i<NUM_LINE_SENSORS;++i) 
  {
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

  //imu init
  
  if(!PhoenixImu_init(&imu)==0)
   {
    Serial.println("IMU initialized...");
    PhoenixImu_handle(&imu);
    PhoenixImu_setOffset(&imu,imu.heading_attuale);
   }
   else
   {
     Serial.println("IMU insn't initialized...");
   }

  //pixy
  PhoenixCamera_init(&camera);
  Serial.println("Pixy initialized...");
  //eeprom
  PhoenixEeprom_init();

  //calibrazione
  if(cal==true)
 {
   Serial.println("in calibrazione...");
   calibrazioneON();
   cal=false;
   Serial.println("calibrazione finita.");
 }
 else
 {
   calibrazioneOFF();
   Serial.println("Prendo i dati dalla eeprom");
 }
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
void testA_BFn()
{

  PhoenixJoint_setSpeed(&joints[0],255);
  PhoenixJoint_handle(&joints[0]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[0],-255);
  PhoenixJoint_handle(&joints[0]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[0],0);
  PhoenixJoint_handle(&joints[0]);
  delay(1000);

  PhoenixJoint_setSpeed(&joints[1],255);
  PhoenixJoint_handle(&joints[1]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[1],-255);
  PhoenixJoint_handle(&joints[1]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[1],0);
  PhoenixJoint_handle(&joints[1]);
  delay(1000);

  PhoenixJoint_setSpeed(&joints[2],255);
  PhoenixJoint_handle(&joints[2]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[2],-255);
  PhoenixJoint_handle(&joints[2]);
  delay(1000);
  PhoenixJoint_setSpeed(&joints[2],0);
  PhoenixJoint_handle(&joints[2]);
  delay(1000);

}
void testDriveFn()
{

  PhoenixDrive_setSpeed(&drive, 0, 1, 0);
  //(motore,x,y,rotazione)
  PhoenixDrive_handle(&drive);
}
void testTimerFn() 
{
  Serial.println(idle_time);
  idle_time=0;
}

void SteoraPlayFn() 
{
  //se vedo la palla mi allineo 
  //altrimenti torno indietro verso la porta
  //se sono allineato allora tiro avanti
  double x=0;
  double y=0;
  double t=0;
//handle
PhoenixCamera_handle(&camera);
PhoenixImu_handle(&imu);
if(PhoenixCamera_getBallStatus(&camera)==1)
{
  //traiettoria
  x=-sin(degToRad(imu.errore));
  y=1-cos(degToRad(imu.errore));
  t=-camera.output_pid/180;
  if(abs(x)<0.5)
  {
    y=1;
  }  
}
else
{
  t=-imu.output_pid/180;
  y=-0.5;
}

PhoenixDrive_setSpeed(&drive, x, y, t);
PhoenixDrive_handle(&drive);
}

void YatiliPlayFn() 
{
  //se vedo la palla mi allineo 
  //altrimenti torno indietro verso la porta
  //se sono allineato allora tiro avanti
  double x=0;
  double y=0;
  double t=0;
  int y_prec=0;
  double time;//tempo in cui è stata vista l'ultima volta la palla
//handle
PhoenixCamera_handle(&camera);
PhoenixImu_handle(&imu);
if(PhoenixCamera_getBallStatus(&camera)==1)
{
  //traiettoria
  x=-sin(degToRad(imu.errore));
  y=1-cos(degToRad(imu.errore));
  t=-camera.output_pid/180;
  if(abs(x)<0.5)
  {
    y=1;
  }
  y_prec=camera.ball_y;//ultima ball_y rilevata
}
else if((millis()-time)<(5500))
{
 //mi giro verso l'ultimo outpud_pid
 t=-camera.output_pid/180;
 //y
 //se la y<180 non ho la palletta
 //se la y>180 ho la palletta
 //più la palletta si allontana più y è piccolo
 if(y_prec<180)
 {
  y=1;
 }
}
else
{
  t=-imu.output_pid/180;
  y=-0.5;
}

PhoenixDrive_setSpeed(&drive, x, y, t);
PhoenixDrive_handle(&drive);
}
void fnFollowBall()
{
  double x=0;
  double y=0;
  double t=0;
  int x_prec=0;
  int y_prec=0;
  double time;//tempo in cui è stata vista l'ultima volta la palla
  PhoenixCamera_handle(&camera);
  PhoenixImu_handle(&imu);
 if(PhoenixCamera_getBallStatus(&camera)==1)
  {
    t=millis();
    //traiettoria
    x=-sin(degToRad(imu.errore));
    //y=1-cos(degToRad(imu.errore));
    t=-camera.output_pid/180;
    if(abs(x)<0.5)
    {
      y=1;
    }  
    x_prec=camera.ball_x;//ultima ball_x rilevata
    y_prec=camera.ball_y;//ultima ball_y rilevata
  }
  else if((millis()-time)<(5500))
  {
    //x
    if(x_prec>0.5)
    {
      t=1;
      //se la x precedente è positivo si gira verso destra
      x=1;
      //nel caso del potriere si deve spostare verso destra
    }
    if(x_prec<-0.5)
    {
      t=-1;
      //se la x precedente è negativa si gira verso sinistra
      x=-1;
      //nel caso del portiere si deve spostare verso sinistra
    }

    //y
    //se la y<180 non ho la palletta
    //se la y>180 ho la palletta
    //più la palletta si allontana più y è piccolo
    if(y_prec<175)
    {
      y=1;
      y=0;
    }
    
  }
  else
  {
    //vado indietro
    x=0;
    y=-1;
    t=0;
  }
  PhoenixDrive_setSpeed(&drive,x,y,t);
  PhoenixDrive_handle(&drive);

}


void loop() 
{
 idle_time++;
 PhoenixImu_handle(&imu);
 PhoenixCamera_handle(&camera);
 //PhoenixLineSensor_handle(&line_sensors);
 PhoenixLineHandler_handle(&line_handler);
 //PhoenixCamera_print(&camera);
 YatiliPlayFn();
 //PhoenixImu_print(&imu);
 //SteoraPlayFn() ;
 //fnFollowBall();
  //non so se mettere while o if
  //spena utilizza un if proverò con quello
  if(PhoenixLineHandler_getStatus==1)
  {
    /*PhoenixLineSensor_handle(&line_sensors);*/
    PhoenixLineHandler_handle(&line_handler);
    PhoenixDrive_setSpeed(&drive,PhoenixLineHandler_getEscapeX(&line_handler),PhoenixLineHandler_getEscapeY(&line_handler),0);
    PhoenixDrive_handle(&drive);
    
  }
  for(int i=0;i<6;i++)
  {
    Serial.print(" stato: ");
    Serial.print(PhoenixLineSensor_getStatus(&line_sensors[i]));
    Serial.print(" misura: ");
    Serial.print(line_sensors[i].misura);
    Serial.print("  soglia: ");
    Serial.print(line_sensors[i].soglia);
    Serial.print("\t");    
  }
  Serial.println("");  
  
}
