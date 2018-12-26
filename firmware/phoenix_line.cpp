/**
 * phoenix_line.cpp
 */

#include "phoenix_line.h"
#include "phoenix_line_internals.h"
#include <math.h>

//TODO: Implementare timer x reset automatico dell'handler

static void PhoenixLineHandler_updateEDir(PhoenixLineHandler* h) {
  h->escape_direction[0] = -h->border_x;
  h->escape_direction[1] = -h->border_y;
  h->escape_direction[2] = 0;
}

void PhoenixLineHandler_init(PhoenixLineHandler* h,
                            PhoenixLineDetector* ld) {
  h->ld=ld;
  h->escape_flag=0;
  for(int i=0;i<3;++i)
    h->escape_direction[i] = 0;
}

OpStatus PhoenixLineHandler_handle(PhoenixLineHandler* h) {
  h->border_x=0;
  h->border_y=0;
  // query all the sensors and update the detector's state
  for(int i=0;i<NUM_LINEDETECTORS;++i)
    if(PhoenixLineDetector_handle(&h->ld[i])<0) return UnknownType;

  for(int i=0;i<NUM_LINEDETECTORS;++i) {
    // check if line detector has already detected a line 
    if( (h->mask>>i & 0x01) == 0) {
      if(h->ld[i].detected) {
        // If a new detector, detects a line,
        // update the mask, compute the new direction vector
        // and reset the escape_ttl
        h->mask |= 0x1<<i;
        h->border_x+=h->ld[i].x;
        h->border_y+=h->ld[i].y;
        PhoenixLineHandler_updateEDir(h);
      }
    }
  }
  return Success;
}

void PhoenixLineHandler_reset(PhoenixLineHandler* h) {
  h->escape_flag=0;
  h->mask=0;
  for(int i=0;i<3;++i)
    h->escape_direction[i]=0;
  for(int i=0;i<NUM_LINEDETECTORS;++i)
    PhoenixLineDetector_reset(&h->ld[i]);
}