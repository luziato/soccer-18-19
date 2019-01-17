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
  d->misura=analogRead(d->pin_reading);
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
}

void PhoenixLineSensor_startCalib(PhoenixLineSensor* d)
{
  d->calibra_flag=1;
}

void PhoenixLineSensor_stopCalib(PhoenixLineSensor* d)
{
  d->calibra_flag=0;
  d->soglia=(d->misura_max+d->misura_min)/2;
  d->misura_max=0;
  d->misura_min=1023;
}

uint8_t PhoenixLineSensor_getStatus(PhoenixLineSensor* d)
{
  return d->detect_flag;
}

void PhoenixLineSensor_reset(PhoenixLineSensor* d) 
{
  d->detect_flag=0;
  d->misura=0;
}
