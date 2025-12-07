#include "timer.h"

const int SEGMENT_CODES[10] = { // 0-9 segment codes
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90};

void updateTimer(volatile Timer *t) // Update 7-segment display with current timer value // Wilmer Zetterström
{
    *DISPLAY_ADDR(5) = 0xFF;
    *DISPLAY_ADDR(4) = 0xFF;
    *DISPLAY_ADDR(3) = SEGMENT_CODES[t->minutes / 10]; // Tens of minutes
    *DISPLAY_ADDR(2) = SEGMENT_CODES[t->minutes % 10] & 0x7F; // Ones of minutes and Colon ON
    *DISPLAY_ADDR(1) = SEGMENT_CODES[t->seconds / 10]; // Tens of seconds
    *DISPLAY_ADDR(0) = SEGMENT_CODES[t->seconds % 10]; // Ones of seconds
}

void tick(volatile Timer *t, int increment) // Increment or decrement timer by specified seconds // Wilmer Zetterström
{
    int total_seconds = t->minutes * 60 + t->seconds + increment; // Convert to total seconds
    if (total_seconds < 0) total_seconds = 0; // Prevent negative time
    t->minutes = total_seconds / 60; // Update minutes
    t->seconds = total_seconds % 60; // Update seconds
}

void startTimer() // Start the hardware timer // Wilmer Zetterström
{
    int period_ms = 3000000; // 3,000,000 cycles for 100ms at 30MHz

    TIMER_PERIODL = period_ms & 0xFFFF; // Set timer period low
    TIMER_PERIODH = (period_ms >> 16) & 0xFFFF; // Set timer period high
    TIMER_CONTROL = 0x7; // START | CONT | ITO
}

void stopTimer() // Stop the hardware timer // Wilmer Zetterström  
{
    TIMER_CONTROL = 0x0; // Stop timer
}

int check_timer_done(volatile Timer *t) // Check if the counter has reached zero // Wilmer Zetterström
{
    if (t->minutes == 0 && t->seconds == 0) {
        stopTimer();
        return 1; // Timer done
    }
    return 0; // Timer not done
}