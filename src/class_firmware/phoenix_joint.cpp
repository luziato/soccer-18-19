//mine
#include "phoenix_joint.h"
Joint::Joint()
{
  //cotruttore si lascia vuoto
}
  void Joint::init(uint8_t* pins)
  //inizializza del programma vecchio
  {     //inizializzo i puntatori con il relativo posto nell'array
        uint8_t*pin_pwm=&pins[0];
        uint8_t*pin_dira=&pins[1];
        uint8_t*pin_dirb=&pins[2];


      //inizializzo i pin ad output e 0
      pinmode(pin_pwm,OUTPUT);
      analogWrite(*pin_pwm,0);

      pinmode(pin_dira,OUTPUT);
      analogWrite(*pin_pwm,0);

      pinmode(pin_dirb,OUTPUT);
      analogWrite(*pin_pwm,0);

      this->_pin_pwm=pin_pwm;
      this->_pin_dira=pin_dira;
      this->_pin_dirb=pin_dirb;
  }


 void Joint::setSpeed(int16_t speed)
 //setVel nel programma vecchio
 //quello che noi facevamo con il modulo qui gli invertiamo direttamente i valori
  {
      //inizializzo pwm e direzione a 0
      unint8_t pwm=0;
      unint8_t dir=0;
      if(speed>=0)
      //se la velocita è maggiore o uguale a 0 assegno al pwm la velocità senza rotazione
      {
        pwm=speed;
        dir=0;
      }
      else
      //altrimenti assegno al pwm il valore negato della velocità con rotazione
      {
        pwm=-speed;
        dir=1;
      }
      if(pwm>255)
      //se il pwm è maggiore di 255 assegno 255 al pwm
      {
        pwm=255;
      }

      this->_pwm=pwm;
      this->_dir=dir;
  }


  void Joint::handle()
  //elabora nel programma vecchio
  {
    digitalWrite(_pin_dira, _dir);
    digitalWrite(_pin_dirb, !_dir);
    analogWrite(_pin_pwm, _pwm);
  }
