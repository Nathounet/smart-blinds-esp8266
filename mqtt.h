#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include "timer.h"

//EXTERNS
extern PubSubClient mqttClient;
extern Timer timerMqttTx;
extern Timer timerMqttCon;

//FUNCTIONS
void setup_mqtt();
void on_message(char* topic, byte* payload, unsigned int length);
void reconnect();
void save_time(String newTime);
void send_time();

#endif
