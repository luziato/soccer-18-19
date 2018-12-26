//mine
#include "phoenix_drive.h"

static double imatrix[NUM_MOTORS][NUM_MOTORS]
//matrice
  {
    {0.33, -0.33, 0.57},
    {0.33, -0.33, -0.57},
    {0.33, 0.66, 0}
  };

HolonomicDrive::HolonomicDrive()
{
  //costruttore si lascia vuoto
}


void HolonomicDrive::init(Joint* joints, JointParams* params, JointControl* control)
//inizializza del programma vecchio
{
  this->joints=joints;//pwm,dira,dirb
  this->params=params;//x,y,pins[3]
  this->control=control;//speed, mode

  for(int i=0;i<NUM_MOTORS;i++)
  {
    joints[i].init(params->pins);
    //minizializza dira. dirb e pwm
  }
}


void HolonomicDrive::move(double x, double y, double theta)
//move del programma vecchio
{
  double speed=0;
  double comp_vec[3] = {theta, x, y};
  //theta rotazione?

  for(int r=0;r<NUM_MOTORS;r++)
  {
    for(int j=0;j<NUM_MOTORS;j++)
    {
      speed = speed + imatrix[r][j]*comp_vec[j];
      //calcola la velocità di joints->speed la matrice con la matrice in alto e il vettore {theta, x, y}
    }
    control[r].speed=(int16_t)speed;
    speed=0;
    //control è un array di struct JointControl
    //ogni elemento dell'array è riferito ad un motore
    //ogni elemento ha un parametro speed
  }
}


void HolonomicDrive::handle()
//elabora nel programma vecchio
{

  for(int i=0;i<NUM_MOTORS;i++)
  {
    joints[i].setSpeed(control[i].speed);
    //assegrno allo speed di Joint->setSpeed, JointControl->speed
    joints[i].handle();
  }
}
