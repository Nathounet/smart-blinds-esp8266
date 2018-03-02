#ifndef HELPER_H
#define HELPER_H

#include "timer.h"
#include "actuator.h"
#include "mqtt.h"
#include "digit.h"

//EXTERNS
extern WiFiClient wifiClient;
extern Timer timerUP;
extern Timer timerDOWN;
extern Timer timerTimeSet;
extern Timer timerSoundA;
extern Timer timerSoundDigit;
extern Timer timerMqttCon;
extern Timer timerMqttTx;

//FUNCTIONS
void setup_wifi();
void setup_pins();
void is_mqtt_connected();
void publish_loop();
static void update_one_timer(Timer *timerToUpdate, void (*callbackFunc)());
void update_all_timer();
void read_IR_frame(const int key);

//INLINES
inline void update_up()          { update_one_timer(&timerUP, reset_up); }
inline void update_down()        { update_one_timer(&timerDOWN, reset_down); }
inline void update_time_set()    { update_one_timer(&timerTimeSet, reset_time_set); }
inline void update_sound_A()     { update_one_timer(&timerSoundA, reset_sound_A); }
inline void update_sound_digit() { update_one_timer(&timerSoundDigit, reset_sound_digit); }
inline void update_mqqt_con()    { update_one_timer(&timerMqttCon, reconnect); }
inline void update_mqtt_tx()     { update_one_timer(&timerMqttTx, send_time); }

#endif
