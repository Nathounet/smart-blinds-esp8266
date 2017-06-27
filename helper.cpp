#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "helper.h"
#include "digit.h"
#include "remote.h"

//LOCALS
const char* wifiSSID      = "FRITZ!Box 7490";
const char* wifiPassword  = "98236153252703264592";
const int timerToUpdateNumber = 7;
void (*timerToUpdateList[timerToUpdateNumber])() =
{
  update_up,
  update_down,
  update_time_set,
  update_sound_A,
  update_sound_digit,
  update_mqqt_con,
  update_mqtt_tx
};

void setup_wifi()
{
  WiFi.begin(wifiSSID, wifiPassword); // Connect to the WiFi
  // Wait until the connection has been confirmed before continuing
  digitalWrite(LED_BUILTIN, LOW); //Turn error led on
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup_pins()
{
  pinMode(pinUP, OUTPUT);
  pinMode(pinDOWN, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinDIGIT, OUTPUT);

  digitalWrite(pinUP, HIGH);
  digitalWrite(pinDOWN, HIGH);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinDIGIT, HIGH);

  // Error state
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void update_one_timer(Timer *timerToUpdate, void (*callbackFunc)())
{
  if (timerToUpdate->is_timer_running() == true)
  {
    timerToUpdate->increment_timer();
    if (timerToUpdate->is_timer_reached() == true)
    {
      callbackFunc();
    }
  }
}

void update_all_timer()
{
  for(int i = 0; i < timerToUpdateNumber; ++i)
  {
    timerToUpdateList[i]();
  }
}

void read_IR_frame(const int key)
{
  switch (key) {
    case KEYES_KEY_OK:
    case SAMSUNG_KEY_OK_1:
    case SAMSUNG_KEY_OK_2:
      reset_all();
      break;

    case KEYES_KEY_UP:
      up();
      break;

    case KEYES_KEY_DOWN:
      down();
      break;

    case KEYES_KEY_STAR:
    case KEYES_KEY_HASH:
      timerTimeSet.start_timer();
      break;

    case SAMSUNG_KEY_A_1:
    case SAMSUNG_KEY_A_2:
      sound_A();
      break;

    case SAMSUNG_KEY_UP_1:
    case SAMSUNG_KEY_UP_2:
      if (timerSoundA.is_timer_running() == true)
      {
        up();
      }
      break;

    case SAMSUNG_KEY_DOWN_1:
    case SAMSUNG_KEY_DOWN_2:
      if (timerSoundA.is_timer_running() == true)
      {
        down();
      }
      break;

    default:
      if (timerTimeSet.is_timer_running() == true)
      {
        is_digit(key);
      }
      else
      {
        Serial.print("Other value (digit timer NOT running): "); ////DEL_ME
        Serial.println(key, HEX); ////DEL_ME
      }
      break;
  }
}
