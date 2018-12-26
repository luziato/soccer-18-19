//mine
#pragma once
#include "phoenix_line_internals.h"
#include "phoenix_globals.h"
#include <math.h>
#include <Adafruit_ADS1015.h> 

void PhoenixLineDetector_init(PhoenixLineDetector* d) 
{
  d->rilevato = 0;
  d->valore_letto = 0;
  d->soglia = 0;
  line_adc[d->adc_addr].begin();//inserisco i valori nel metodo begin() di adc
}

//OpStatus ritorna success 
OpStatus PhoenixLineDetector_handle(PhoenixLineDetector* d) 
{
  d->valore_letto=line_adc[d->adc_addr].readADC_SingleEnded(d->adc_idx);
  if(d->valore_letto > d->soglia)
  {
	  d->rilevato = 1;
  }
  return Success;
}

void PhoenixLineDetector_reset(PhoenixLineDetector* d) 
{
  d->rilevato=0;
  d->valore_letto=0;
}
