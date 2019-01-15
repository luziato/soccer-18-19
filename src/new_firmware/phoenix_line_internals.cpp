//mine
#pragma once
#include "phoenix_line_internals.h"
//#include "phoenix_globals.h"
#include <math.h>


void PhoenixLineSensor_init(PhoenixLineSensor* d) 
{
  d->detect_flag=0;
  d->calibra_flag=0;
  d->misura=0;
  d->misura_min=0;
  d->misura_max=0;
  d->soglia=0;

}


void PhoenixLineSensor_handle(PhoenixLineSensor* d) 
{
  if(d->calibra_flag==true)
  {
    if(d->misura>d->misura_max)
    {
      d->misura_max=d->misura;
    }
    if(d->misura<d->misura_min)
    {
      d->misura_min=d->misura;
    }
  }

  if(d->misura > d->soglia)
  {
	  d->detect_flag = 1;
  }
  return Success;
}

void PhoenixLineSensor_startCalib(PhoenixLineSensor* d)
{
l->calibra_flag=1;
}

void PhoenixLineSensor_stopCalib(PhoenixLineSensor* d)
{
l->calibra_flag=0;
soglia=(d->misura_max+d->misura_min)/2;
d->misura_max=0;
d->misura_min=0;
}

uint8_t PhoenixLineSensor_getStatus(PhoenixLineSensor* d)
{
  return d->detected->flag;
}

void PhoenixLineSensor_reset(PhoenixLineSensor* d) 
{
  d->detect_flag=0;
  d->misura=0;
}
