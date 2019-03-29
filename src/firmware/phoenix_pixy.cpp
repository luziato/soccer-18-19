//mine
/**
 * phoenix_pixy.h
 **/
#include "phoenix_pixy.h"
#include "utils.h"
#include <Arduino.h>
#include <Pixy2.h>
#define BALL_SIG 1
#define BALL_RELIABLE_CTR 5
Pixy2 _pixy;
/*typedef struct 
{
  uint8_t ball_detection;
  uint16_t ball_x;
  uint16_t ball_y;
  uint16_t ball_w;
  uint16_t ball_h;
}PhoenixCamera;
*/

/**
 * Inizializza p (PhoenixCamera*) azzerando i valori
 * ball_detection, ball_x, ball_y, ball_w e ball_h
 * In oltre è necessario inizializzare 
 * l'oggetto pixy (Pixy) tramite il metodo pixy.init()
 **/
void PhoenixCamera_init(PhoenixCamera* p)
{
  _pixy.init();
  p->ball_detection=0;
  p->ball_x=0;
  p->ball_y=0;
  p->ball_w=0;
  p->ball_h=0;
  return;
}

/**
 * Interroga il modulo pixy, richiedendo il numero di blocchi
 * visti.
 * I passi necessari sono questi:
 * 1) Imposta ball_detection pari a 0
 * 2) Richiede numero di blocchi visti (pixy.getBlocks())
 * 3) Se almeno un blocco è stato rilevato, bisogna controllare
 *    se uno dei blocchi ha la stessa "signature" della palla
 *    (salvata in BALL_SIG) allora bisogna incrementare
 *    la variabile ball_detection;
 *    La variabile in questione deve essere limitata all'intervallo
 *    (0, BALL_RELIABLE_CTR)
 * 4) Una volta trovata la palla, scaricare i seguenti valori
 *    dalla pixy:
 *    - x (coordinata x del blocco)
 *    - y (coordinata y del blocco)
 *    - w (larghezza del blocco [width])
 *    - h (altezza x del blocco [height])
 * 5) Se non viene rilevato nessun blocco oppure non viene rilevata
 *    la palla, decrementare la variabile ball_detection
 **/
void PhoenixCamera_handle(PhoenixCamera* p)
{
  p->ball_detection=0;
  int a=_pixy.ccc.getBlocks();
    for(int i=0;i<a;i++)
    {
    
      if(_pixy.ccc.blocks[i].m_signature==BALL_SIG)
      {
        if(_pixy.ccc.blocks[i].m_age>BALL_RELIABLE_AGE)
        {
          p->ball_detection=1;
          p->ball_h=_pixy.ccc.blocks[i].m_height;
          p->ball_w=_pixy.ccc.blocks[i].m_width;
          p->ball_x=_pixy.ccc.blocks[i].m_x;
          p->ball_y=_pixy.ccc.blocks[i].m_y;

          p->errore=((int)p->ball_x-160);
          p->errore = cconstraint(p->errore,180,-180);
          //ERRORE PROPORZIONALE
          //quanto è grande l'errore
          double e_p=p->errore*p->kp;
          //ERRORE DERIVATIVO
          // calcola l'errore nel tempo
          double e_d=((p->errore-p->errore_prec)*p->idt)*p->kd;
          //ERRORE INTERGRALE
          //errori che aumentano nel tempo
          p->sum_i+=p->ki*p->errore*p->dt;

          p->sum_i=clamp(p->sum_i,p->max_i);
          p->output_pid=e_p+e_d+p->sum_i;
          // dobbiamo limitare l'output
          p->output_pid=clamp(p->output_pid,p->max_output);

          p->errore_prec=p->errore;
        }      
      }
    }
}

/**
 * Restituisce il valore ball_detection
 **/
uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p)
{
  return p->ball_detection;
}

/**
 * Restituisce il valore ball_x
 **/
uint16_t PhoenixCamera_getBallX(PhoenixCamera* p)
{
  return p->ball_x;
}

/**
 * Restituisce il valore ball_y
 **/
uint16_t PhoenixCamera_getBallY(PhoenixCamera* p)
{
  return p->ball_y;
}

/**
 * Restituisce il valore ball_w
 **/
uint16_t PhoenixCamera_getBallW(PhoenixCamera* p)
{
  return p->ball_w;
}

/**
 * Restituisce il valore ball_h
 **/
uint16_t PhoenixCamera_getBallH(PhoenixCamera* p)
{
  return p->ball_h;
}

void PhoenixCamera_print(PhoenixCamera*p)
{
  Serial.print("[x attuale= ");
  Serial.print(p->ball_x);
  Serial.print("\t");
  Serial.print("output pid= ");
  Serial.print(p->output_pid);
  Serial.print("\t");  
  Serial.print("errore= ");
  Serial.print(p->errore);
  Serial.print("]");
  Serial.println();
}
