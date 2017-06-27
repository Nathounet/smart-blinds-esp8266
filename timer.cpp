#include <Arduino.h>
#include "timer.h"

Timer::Timer(int maxTimer):
  duration(maxTimer)
{
  startTime = 0;
  currentTime = 0;
}

void Timer::start_timer()
{
  startTime = millis();
  currentTime = millis();
}

void Timer::reset_timer()
{
  startTime = 0;
  currentTime = 0;
}

void Timer::increment_timer()
{
  currentTime = millis();
}

bool Timer::is_timer_reached()
{
  if (currentTime >= duration + startTime)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Timer::is_timer_running()
{
  if (currentTime > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
