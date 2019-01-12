//mine
#include "phoenix_line.h"
#include "phoenix-line-internals.h"
#include<math.h>
// Funzioni utili per lavorare con la maschera.
//mask_read ti dice se il bit in posizione index è 0 o 1
uint8_t mask_read(uint16_t* mask, uint8_t index) 
{
  return *mask & (0x1<<index);
}
//mask_setBit imposta il bit in posizione index a 1
void mask_setBit(uint16_t* mask, uint8_t index) 
{
  *mask |= (0x1<<index); 
}
//mask_clearBit imposta il bit in posizione index a 0
void mask_clearBit(uint16_t* mask, uint8_t index) 
{
  *mask &= ~(0x1<<index);
}


/*
//aggiorno la direzione di fuga
Static void PhoenixLineHandler_updateEDir(PhoenixLineHandler*h)
{
  h->escape_directon[0]=-h->border_x;//x
  h->escape_directon[1]=-h->border_y;//y
  h->escape_directon[2]=-0;//rotation
}*/


//inizializzo  le due classi PhoenixLineHandler e PhoenixLineDetector
void PhoenixLineHandler_init(PhoenixLineHandler*h, PhoenixLineSensor*s)
{
  h->escape_x=0;
  h->escape_y=0;
  h->ecsape_flag=0;
  h->escape_ttl=ESCAPE_TTL;
  h->line_sensors->s;
}


//mask è l'unica parte della funzione che non viene resettata
void PhoenixLineHandler_handle(PhoenixLineHandler* h)
{
  uint8_t a=0;
  h->line_sensors->PhoenixLineHandler_handle;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {

    if( mask_read(mask,i)==0)
    {
      a=h->line_sensors[i]->PhoenixLineSensor_getStatus(line_sensors);
      (if a>0)
      {
        mask_setBit(mask,i);
        h->escape_x+=h->line_sensors[i].x;
        h->escape_y+=h->line_sensors[i].y;
        
        h->ecsape_flag=1;
        h->escape_ttl=ESCAPE_TTL;
      }
      if(h->ecsape_flag==1)
      {
        h->escape_ttl-=1;
      }
      if(h->escape_ttl==0)
      {
        h->PhoenixLineHandler_reset;
      }
    }
  }
}

uint8_t PhoenixLineHandler_getStatus(PhoenixLineHandler* h)
{
  return h->ecsape_flag;
}

double PhoenixLineHandler_getEscapeX(PhoenixLineHandler* h)
{
  return h->escape_x;
}

double PhoenixLineHandler_getEscapeY(PhoenixLineHandler* h)
{
  return h->escape_y;
}

void PhoenixLineHandler_reset(PhoenixLineHandler* h)
{
  h->escape_flag=0;
  h->escape_x=0;
  h->escape_y=0;
  h->mask=0;

  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
   h->line_sensors[i]->PhoenixLineHandler_reset(h->line_sensors);
  }

}

