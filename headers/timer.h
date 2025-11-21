#ifndef TIMER_H
#define TIMER_H

#include "dtekv-lib.h"

#define TIMER_STATUS (*(volatile int *)0x04000020) // Timer status register
#define TIMER_CONTROL (*(volatile int *)0x04000024) // Timer control register
#define TIMER_PERIODL (*(volatile int *)0x04000028) // Timer period low register
#define TIMER_PERIODH (*(volatile int *)0x0400002C) // Timer period high register

#define DISPLAY_ADDR(n) ((volatile int *)(0x04000050 + (n) * 0x10)) // 7-segment display addresses

typedef struct { // Timer structure
    int minutes;
    int seconds;
} Timer;

void updateTimer(volatile Timer* t);
void tick(volatile Timer* t, int increment);
void startTimer();
void stopTimer();
void getTimer(volatile Timer* t);
int check_timer_done(volatile Timer* t);

#endif