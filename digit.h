#ifndef DIGIT_H
#define DIGIT_H

#include "timer.h"

//EXTERNS
extern Timer timerTimeSet;
extern Timer timerSoundDigit;

//FUNCTIONS
void reset_time_set();
static void send_new_time();
static void add_digit(const int digit);
void is_digit(const int key);

#endif
