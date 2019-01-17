//mine
#include "phoenix_line.h"
#include "phoenix_line_internals.h"
#include<math.h>
#define NUM_LINEDETECTORS 16
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

  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
   PhoenixLineSensor_reset(&h->line_sensors[i]);
  }

}


//mask è l'unica parte della funzione che non viene resettata
void PhoenixLineHandler_handle(PhoenixLineHandler* h)
{
  uint8_t a=0;
  PhoenixLineSensor_handle;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {

    if(mask_read(&h->mask,i)==0)
    {
      a=PhoenixLineSensor_getStatus(&h->line_sensors[i]);
      if(a>0)
      {
        mask_setBit(&h->mask,i);
        h->escape_x+=h->line_sensors[i].x;
        h->escape_y+=h->line_sensors[i].y;
        
        h->escape_flag=1;
        h->escape_ttl=ESCAPE_TTL;
      }
      if(h->escape_flag==1)
      {
        h->escape_ttl-=1;
      }
      if(h->escape_ttl==0)
      {
        PhoenixLineHandler_reset(h);
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


