//mine

#include "phoenix_imu.h"

/**
 * Inizializza la struttura m (PhoenixImu*) tramite la seguente procedura:
 * azzera heading_attuale, heading_target, heading_offset, errore, errore_pid
 * Inizializza imu (BNO055*) nel seguente modo:
 * 1) imposta imu->i2c_addr uguale a BNO055_I2C_ADDR
 * 2) imposta imu->op uguale a NDOF
 * 3) lancia la funzione BNO055_init(m->imu)
 * 4) Se la funzione restituisce un valore diverso da 0
 *    allora bloccare l'inizializzazione e ritornare -1
 **/
uint8_t PhoenixImu_init(PhoenixImu* m) 
{
  m->heading_attuale=0;
  m->heading_target=0;
  m->heading_offset=0;
  m->errore=0;
  m->errore_pid=0;
  m->imu->i2c_addr=BNO055_I2C_ADDR;
  m->imu->op=NDOF;
  if(!BNO055_init(m->imu))
  {
    return -1;
  }
  else
  {
    
    BNO055_init(m->imu);
    //BNO055_init(BNO055* b)
  }
  return 0;
}

/**
 * Esegue la funzione BNO055_handle(m->imu) per aggiornare
 * lo stato della periferica, sucessivamente assegna ad
 * heading_attuale, il valore di eul_heading di imu (accedi ad imu per
 * recuperare il valore).
 *
 * Successivamente calcola:
 * 1) errore pari a heading_target - (heading_attuale-heading_offset)
 * 2) errore_pid : ANCORA NON LO POTETE FARE
 *
 *
 * Piccola considerazione:
 * Se il modulo BNO055 ha una frequenza di risposta di 
 * 100 Hz (10mS) e in un secondo il loop viene eseguito circa
 * 30.000-35.000 volte (35 kHz o 28uS a loop), è conveniente
 * chiamare continuamente PhoenixImu_handle ? oppure
 * è più conveniente chiamarla solo ogni 10mS attraverso
 * un timer ? :) Nella prossima puntata...
 **/
double clamp(double v, double m)
{
 if(v>m)//se supera il massimo ritorna il massimo
 {
   return m;
 }
 if(v<-m)
 {
   return -m;
 }
 return v;
}
void PhoenixImu_handle(PhoenixImu* m) 
{
  BNO055_handle(m->imu);
  //m->imu->BNO055_handle();
  m->heading_attuale=m->imu->eul_heading;  
  m->errore=m->heading_target-(m->heading_attuale-m->heading_offset);
 
  //PID
  //ERRORE PROPORZIONALE
  //quanto è grande l'errore
  double e_p=m->errore*m->kp;


  //ERRORE DERIVATIVO
  // calcola l'errore nel tempo
  double e_d=((m->errore-m->errore_prec)*m->idt)*m->kd;

  //ERRORE INTERGRALE
  //errori che aumentano nel tempo
  m->sum_i+=m->ki*m->errore*m->dt;
  /*
  divergenza dell'integrale:rischiamo che sum_i diventi enorme
  gli impostiamo un limite
  un valore massimo e un valore minimo
  per controllare questo faccio clamp
  */
  m->sum_i=clamp(m->sum_i,m->max_i);
 
  m->output_pid=e_p+e_d+m->sum_i;
 // dobbiamo limitare l'output
  m->output_pid=clamp(m->output_pid,m->max_output)

  m->errore_prec=m->errore;
}

/**
 * Imposta heading_offset pari ad os
 **/
void PhoenixImu_setOffset(PhoenixImu* m, double os) 
{
  m->heading_offset=os;//settiamo l'heading offset 
}

/**
 * Imposta heading_target pari a t
 **/
void PhoenixImu_setTarget(PhoenixImu* m, double t) 
{
  m->heading_target=t;//settiamo l'heading target a dove voglio andare a finire
}

