#include "phoenix_hbridge.h"
#include "phoenix_status.h"
#include "Arduino.h"

typedef void (*HBridgeFiniFn)(HBridge* bridge);
typedef void (*HBridgeSetSpeedFn)(HBridge* bridge, int16_t speed);

typedef struct HBridgeOps {
  HBridgeFiniFn fini_fn;
  HBridgeSetSpeedFn setSpeed_fn;
} HBridgeOps;

void HBridgeDualDir_fini(HBridge* bridge);
void HBridgeDualDir_setSpeed(HBridge* bridge, int16_t speed);

static HBridgeOps h_bridge_ops[] =
  {
    // dual dir
    {
      .fini_fn=HBridgeDualDir_fini,
      .setSpeed_fn=HBridgeDualDir_setSpeed
    }
  };

/* Dual Dir Mode */
OpStatus HBridgeDualDir_init(HBridge* bridge, int8_t* pins) {
  if(bridge->ops && bridge->ops->fini_fn)
    (*bridge->ops->fini_fn)(bridge);
  
  int8_t *pwm_pin=&pins[0];
  int8_t *dira_pin=&pins[1];
  int8_t *dirb_pin=&pins[2];

  bridge->ops=h_bridge_ops+HBridgeTypeDualDir;
  
  pinMode(*dira_pin, OUTPUT);
  digitalWrite(*dira_pin, 0);
  bridge->params.dualdir.dira_pin=*dira_pin;
  
  pinMode(*dirb_pin, OUTPUT);
  digitalWrite(*dirb_pin, 0);
  bridge->params.dualdir.dirb_pin=*dirb_pin;
  
  pinMode(*pwm_pin, OUTPUT);
  analogWrite(*pwm_pin, 0);
  bridge->params.dualdir.pwm_pin=*pwm_pin;
  
  return Success;
}

void HBridgeDualDir_fini(HBridge* bridge) {
    analogWrite(bridge->params.dualdir.pwm_pin, 0);
    pinMode(bridge->params.dualdir.dira_pin, INPUT_PULLUP);
    pinMode(bridge->params.dualdir.dirb_pin, INPUT_PULLUP);
}
/**
void HBridgeDualDir_setSpeed(HBridge* bridge, int16_t speed) {
  const int8_t pwm_pin = params.dualdir.pwm_pin;
  const int8_t dira_pin = params.dualdir.dira_pin;
  const int8_t dirb_pin = params.dualdir.dirb_pin;

  uint16_t pwm=0;
  uint8_t dir=0;
  if(speed>0) {
    pwm=speed;
    dir=0;
  } else {
    pwm=-speed;
    dir=1;
  }
  if(pwm>255)
    pwm=255;
  digitalWrite(dira_pin, dir);
  digitalWrite(dirb_pin, !dir);

  analogWrite(pwm_pin, pwm);
}

OpStatus HBridge_init(HBridge* bridge, const HBridgeType type, int8_t* pins) {
  switch(type) {
    case HBridgeTypeDualDir:
      return HBridgeDualDir_init(bridge, pins);
    default:
      return -1;
  }
}
**/