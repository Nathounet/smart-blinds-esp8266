#include <Arduino.h>
#include "actuator.h"

void reset_one(const int pinToReset, Timer *timerToReset)
{
  digitalWrite(pinToReset, HIGH);
  timerToReset->reset_timer();
}

void reset_all()
{
  reset_up();
  reset_down();
  reset_sound_A();
  reset_sound_digit();
}

void actuate_one(Timer *timerToCheck, void (*resetFunc)(), int pinToSet, Timer *timerToStart)
{
  if (timerToCheck->is_timer_running() == true)
  {
    resetFunc();
  }
  digitalWrite(pinToSet, LOW);
  timerToStart->start_timer();
}
