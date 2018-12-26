/**
 * phoenix_line_internals.cpp
 */

#include "phoenix_line_internals.h"
#include "phoenix_globals.h"
#include <math.h>

void PhoenixLineDetector_init(PhoenixLineDetector* d) {
  d->x = cos(degreesToRadians(d->index));
  d->y = sin(degreesToRadians(d->index));
  line_adc[d->adc_addr].begin();
}

OpStatus PhoenixLineDetector_handle(PhoenixLineDetector* d) {
  d->reading=line_adc[d->adc_addr].readADC_SingleEnded(d->adc_idx);
  if(d->reading==0)
    return UnknownType;
  
  if(d->reading > d->threshold)
    d->detected = 1;
  return Success;
}

void PhoenixLineDetector_reset(PhoenixLineDetector* d) {
  d->detected=0;
}