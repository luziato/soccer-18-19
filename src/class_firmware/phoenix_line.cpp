//mine
#include "phoenix_line.h"
#include "phoenix-line-internals.h"
#include<math.h>


//aggiorno la direzione di fuga
Static void PhoenixLineHandler_updateEDir(PhoenixLineHandler*h)
{
  h->escape_directon[0]=-h->border_x;//x
  h->escape_directon[1]=-h->border_y;//y
  h->escape_directon[2]=-0;//rotation
}
//inizializzo  le due classi PhoenixLineHandler e PhoenixLineDetector
void PhoenixLineHandler_init(PhoenixLineHandler*h, PhoneixLineDetector*ld)
{
  h->ld=ld;
  h->ecsape_flag=0;
  for(int i=0;i<3;i++)
  {
    h->ecape_direction[i]=0;
  }
}

//opstatus ritorna un intero
//Success se trova una linea quindi ritorna 0
//mask è l'unica parte della funzione che non viene resettata
OpStatus PhoenixLineHandler_handle(PhoneixLineHandler*h)
{
  h->border_x=0;
  h->border_y=0;
  //interroga tutti i sensori e aggiorna tutti i detector
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    if(PhoenixLineHandler_handle(&h->ld[i])<0)return UnknownType;
    for(int i=0;i<NUM_LINEDETECTORS;i++)
    {
      //scorro il byte di i posizioni il >>
      if(h->mask>>i & 0x01==0)
      {
        if(h->ld[i].detected)
        {
          h->mask|=0x1<<i;
          h->border_x+=h->ld[i].x;
          h->border_y+=h->ld[i].y;
          PhoenixLineHandler_updateEDir(h);
        }
      }
    }
    return Success;
  }
}



void PhoenixLineHandler_reset(phoenixLineHandler*h)
{
  h->ecsape_flag=0;
  h->mask=0;
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    h->ecsape_direction[i]=0;
  }
  for(int i=0;i<NUM_LINEDETECTORS;i++)
  {
    PhoenixLineHandler_reset(&h->ld[i])
  }

}
