//mine
#include "phoenix_line.h"
#include "phoenix_line_internals.h"
#include<math.h>
#define NUM_LINEDETECTORS 6
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



//inizializzo  le due classi PhoenixLineHandler e PhoenixLineDetector
void PhoenixLineHandler_init(PhoenixLineHandler*h, PhoenixLineSensor*s)
{
  h->escape_x=0;
  h->escape_y=0;
  h->escape_flag=0;
  h->escape_ttl=ESCAPE_TTL;
  h->line_sensors=s;
}

void PhoenixLineHandler_reset(PhoenixLineHandler* h)
{
  h->escape_flag=0;
  h->escape_x=0;
  h->escape_y=0;
  h->mask=0;
  h->escape_ttl=ESCAPE_TTL;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
   PhoenixLineSensor_reset(&h->line_sensors[i]);
  }

}


//mask è l'unica parte della funzione che non viene resettata
void PhoenixLineHandler_handle(PhoenixLineHandler* h)
{
  uint8_t a=0;
  for(int j=0;j<NUM_LINEDETECTORS;j++)
  {
    PhoenixLineSensor_handle(&h->line_sensors[j]);
  }
  
if(h->calib_flag==0)
{
  if(h->escape_flag==1)
  {
    h->escape_ttl-=1;
  }
  if(h->escape_ttl==0)
  {
    PhoenixLineHandler_reset(h);
  }
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    if(mask_read(&h->mask,i)==0)
    {
      a=PhoenixLineSensor_getStatus(&h->line_sensors[i]);
      if(a>0)
      {
        mask_setBit(&h->mask,i);
        h->escape_x-=h->line_sensors[i].x;
        h->escape_y-=h->line_sensors[i].y;
        
        h->escape_flag=1;
        h->escape_ttl=ESCAPE_TTL;
      }
      
    }
  }
}
  
}

uint8_t PhoenixLineHandler_getStatus(PhoenixLineHandler* h)
{
  return h->escape_flag;
}

double PhoenixLineHandler_getEscapeX(PhoenixLineHandler* h)
{
  return h->escape_x;
}

double PhoenixLineHandler_getEscapeY(PhoenixLineHandler* h)
{
  return h->escape_y;
}
/**
 * imposta calib_flag pari ad 1, e lancia la funzione 
 * PhoenixLineSensor_startCalib per ogni sensore in line_sensors 
 **/
void PhoenixLineHandler_startCalib(PhoenixLineHandler* h)
{
  h->calib_flag=1;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    PhoenixLineSensor_startCalib(&h->line_sensors[i]);
  }
  
}

/**
 * azzera calib_flag e lancia la funzione PhoenixLineSensor_stopCalib
 * per ogni sensore in line_sensors
 **/
void PhoenixLineHandler_stopCalib(PhoenixLineHandler* h)
{
  h->calib_flag=0;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    PhoenixLineSensor_stopCalib(&h->line_sensors[i]);
  }
}

