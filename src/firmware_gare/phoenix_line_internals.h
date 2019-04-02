//mine
#pragma once
#include <Arduino.h>




typedef struct 
{
  double x; // componente x del vettore associato al sensore
  double y; // componente y del vettore associato al sensore
  uint16_t soglia;// soglia riconoscimento linea
  uint16_t misura;// misura attuale del sensore
  uint16_t misura_min;// x Calibrazione: Lettura di valore minimo
  uint16_t misura_max;// x Calibrazione: Lettura di valore massimo
  uint8_t detect_flag;// flag di rilevazione linea ( 1 : linea rilevata )
  uint8_t calibra_flag;// x Calibrazione: flag di calibrazione
  uint8_t pin_reading;// Pin relativo al sensore
} PhoenixLineSensor;


void PhoenixLineSensor_init(PhoenixLineSensor* d);
                              
void PhoenixLineSensor_handle(PhoenixLineSensor* d);

void PhoenixLineSensor_startCalib(PhoenixLineSensor* d);

void PhoenixLineSensor_stopCalib(PhoenixLineSensor* d);

uint8_t PhoenixLineSensor_getStatus(PhoenixLineSensor* d);

void PhoenixLineSensor_reset(PhoenixLineSensor* d);
