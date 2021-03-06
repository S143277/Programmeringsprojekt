#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "30010_io.h"
#include "ansi.h"
#include "controller.h"

struct interrupt_t{
    volatile int16_t h, m, s, hs;
};

struct interrupt_t t;

void init_timer(uint16_t priority);
void time(struct interrupt_t *t);
void TIM2_IRQHandler(void);
void init_stopwatch();
void stopwatch_joystick( uint8_t *ss, uint8_t *push);



#endif /* TIMER_H_INCLUDED */
