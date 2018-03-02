#include <Arduino.h>
#include "digit.h"
#include "actuator.h"
#include "mqtt.h"
#include "remote.h"

//LOCALS
String newTime = String("s");

void reset_time_set()
{
  newTime= "s";
  timerTimeSet.reset_timer();
}

static void send_new_time()
{
  save_time(newTime);
  reset_time_set();
}

static void add_digit(const int newDigit)
{
  sound_digit();

  if (newTime.length() < 5)
  {
    newTime += newDigit;
    Serial.print("add_digit len:"); ////DEL_ME
    Serial.print(newTime.length()); ////DEL_ME
    Serial.print(" new-time:"); ////DEL_ME
    Serial.println(newTime); ////DEL_ME
    if (newTime.length() == 5)
    {
      send_new_time();
    }
  }
}

void is_digit(const int key)
{
  switch (key)
  {
    case KEYES_KEY_1:
      add_digit(1);
      break;

    case KEYES_KEY_2:
      add_digit(2);
      break;

    case KEYES_KEY_3:
      add_digit(3);
      break;

    case KEYES_KEY_4:
      add_digit(4);
      break;

    case KEYES_KEY_5:
      add_digit(5);
      break;

    case KEYES_KEY_6:
      add_digit(6);
      break;

    case KEYES_KEY_7:
      add_digit(7);
      break;

    case KEYES_KEY_8:
      add_digit(8);
      break;

    case KEYES_KEY_9:
      add_digit(9);
      break;

    case KEYES_KEY_0:
      add_digit(0);
      break;

    default:
      Serial.print("Other value (digit timer RUNNING): "); ////DEL_ME
      Serial.println(key, HEX); ////DEL_ME
      // Other frame code received
      break;
  }
}
