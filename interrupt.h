#ifndef INTERRUPT_H
#define INTERRUPT_H

#define BTN_ADDR (*(volatile int *)0x040000d0) // Button address
#define BTN_INTERRUPTMASK (*(volatile int *)0x040000d8) // Button interrupt mask
#define BTN_EDGE (*(volatile int *)0x040000dc) // Button edge register

extern volatile int button_pressed;

void handle_interrupt(unsigned cause);

#endif