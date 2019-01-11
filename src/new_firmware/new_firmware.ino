//mine

#include "phoenix_joints.h"
#include "phoenix_drive.h"

PhoenixJoint joints[NUM_JOINTS] = 
{
  {// Joint 0
    pin_dira : 8,
    pin_dirb : 9,
    pin_pwm : 5,
    direzione : 0,
    velocita : 0
  },
  {// Joint 1
    pin_dira : 10,
    pin_dirb : 11,
    pin_pwm : 6,
    direzione : 0,
    velocita : 0
  },
  {// Joint 2
    pin_dira : 12,
    pin_dirb : 13,
    pin_pwm : 7,
    direzione : 0,
    velocita : 0
  }
};
// drive per pilotare la piattaforma
PhoenixDrive drive;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial initialized...");

  for(int i=0;i<NUM_JOINTS;++i) {
    PhoenixJoint_init(&joints[i]);
  }
  PhoenixDrive_init(&drive, joints);
    
  
}

void loop() 
{

}
