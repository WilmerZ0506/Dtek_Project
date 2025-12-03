#ifndef INTERRUPT_H
#define INTERRUPT_H

#define BTN_ADDR (*(volatile int *)0x040000d0) // Button address
#define BTN_INTERRUPTMASK (*(volatile int *)0x040000d8) // Button interrupt mask
#define BTN_EDGE (*(volatile int *)0x040000dc) // Button edge register

#include "dtekv-lib.h"
#include "timer.h"
#include "boss.h"
#include "game.h"

void handle_interrupt(unsigned cause);

#endif