#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "timer.h"

//EXTERNS
extern const int pinIR;
extern const int pinUP;
extern const int pinDOWN;
extern const int pinA;
extern const int pinDIGIT;
extern Timer timerUP;
extern Timer timerDOWN;
extern Timer timerSoundA;
extern Timer timerSoundDigit;

//FUNCTIONS
void reset_one(const int pinToReset, Timer *timerToReset);
void reset_all();
void actuate_one(Timer *timerToCheck, void (*resetFunc)(), int pinToSet, Timer *timerToStart);

//INLINES
inline void reset_up()          { reset_one(pinUP, &timerUP); }
inline void reset_down()        { reset_one(pinDOWN, &timerDOWN); }
inline void reset_sound_A()     { reset_one(pinA, &timerSoundA); }
inline void reset_sound_digit() { reset_one(pinDIGIT, &timerSoundDigit); }
inline void up()          { actuate_one(&timerDOWN, reset_down, pinUP, &timerUP); }
inline void down()        { actuate_one(&timerUP, reset_up, pinDOWN, &timerDOWN); }
inline void sound_A()     { actuate_one(&timerSoundA, reset_sound_A, pinA, &timerSoundA); }
inline void sound_digit() { actuate_one(&timerSoundDigit, reset_sound_digit, pinDIGIT, &timerSoundDigit); }

#endif
