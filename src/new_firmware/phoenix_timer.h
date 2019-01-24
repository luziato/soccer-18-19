//mine

#include <Arduino.h>
#include <avr/io.h>

// struttura temporanea Timer (Vi devo spiegare questa cosa a voce)
struct Timer;

// Altra cosa da spiegarvi a voce
typedef void (*TimerFn)(void*);
/**
 * Utilizza TIMER5 per inviare un interrupt
 * ogni millisecondo
 **/
void Timer_init(void);

/**
 * Crea una nuova istanza di Timer con duration_ms,
 * stop_flag pari ad 1, fn pari a timer_fn
 * e args pari a timer_args
 * Nel file .cpp è già presente un array di Timer(s)
 * Per controllare quale posizione è già stata allocata
 * devi controllare la maschera (timers_mask).
 * Se il bit i-esimo della maschera e' pari a 0
 * allora la cella i-esima dell'array è vuota.
 * Inoltre imposta la variabile timer_num pari ad i
 * Una volta riempita la struttura, ricordati di impostare
 * il bit i-esimo della maschera ad 1
 **/
struct Timer* Timer_create(uint16_t duration_ms,
                           TimerFn timer_fn,
                           void* timer_args);

/**
 * Azzera il bit t->timer_num esimo della
 * maschera timers_mask 
 **/
void Timer_destroy(struct Timer*);

/**
 * Imposta a 0 la variabile stop_flag di t
 **/
void Timer_start(struct Timer*);

/**
 * Imposta a 1 la variabile stop_flag di t
 **/
void Timer_stop(struct Timer*);





