//mine

#include "phoenix_joints.h"
/**
 * Azzera i valori di direzione e velocita,
 * inizializza i pin di dira, dirb e pwm 
 * sulla piattaforma di Arduino
 **/
void PhoenixJoint_init(PhoenixJoint* j) 
{
  
  
  j->direzione=0;
  j->velocita=0;

  pinMode(j->pin_pwm,OUTPUT);
  digitalWrite(j->pin_pwm,0);

  pinMode(j->pin_dira,OUTPUT);
  digitalWrite(j->pin_dira,0);

  pinMode(j->pin_dirb,OUTPUT);
  digitalWrite(j->pin_dirb,0);
}

/**
 * Imposta direzione e velocita di j (PhoenixJoint)
 * dato il parametro velocita.
 * direzione = segno(velocita) [0 se positivo, 1 se negativo]
 * velocita = modulo(velocita) [0, 255]
 */
void PhoenixJoint_setSpeed(PhoenixJoint* j, int velocita) 
{

  if(velocita>=0)
  //se la velocita è maggiore o uguale a 0 assegno al pwm la velocità senza rotazione
  {
    j->velocita=velocita;
    j->direzione=0;
  }
  else
  //altrimenti assegno al pwm il valore negato della velocità con rotazione
  {
    j->velocita=-velocita;
    j->direzione=1;
  }
  if(velocita>255)
  //se il pwm è maggiore di 255 assegno 255 al pwm
  {
    j->velocita=255;
  }
  
}

/**
 * Comunica alla piattaforma di Arduino,
 * i nuovi stati sui pin dira, dirb e pwma
 * tramite le funzioni di 
 * digitalWrite
 * analogWrite
 */
void PhoenixJoint_handle(PhoenixJoint* j) 
{
  digitalWrite(j->pin_dira, j->direzione);
  digitalWrite(j->pin_dirb, !j->direzione);
  analogWrite(j->pin_pwm, j->velocita);
  if(j->velocita<50)
  {
    analogWrite(j->pin_pwm,0);
  }
}
