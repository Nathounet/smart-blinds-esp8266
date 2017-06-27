#include <IRremoteESP8266.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "helper.h"
#include "actuator.h"
#include "mqtt.h"
#include "remote.h"
#include "timer.h"

// PINS
const int pinIR    = 14; // D5 on ESP8266 NodeMCU
const int pinUP    = 12; // D6
const int pinDOWN  = 13; // D7
const int pinA     = 4;  // D2 use as sound acknowledgement for key A
const int pinDIGIT = 5;  // D1 use as sound acknowledgement for new digit

// VARIABLES
Timer timerUP(17000);
Timer timerDOWN(15500);
Timer timerTimeSet(10000);
Timer timerSoundA(3000);
Timer timerSoundDigit(100);
Timer timerMqttCon(10000); // timer for MQTT reconnection
Timer timerMqttTx(2000);  // timer for re-publish new time while no ack

IRrecv irRecv(pinIR);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
decode_results irFrame;

// SETUP
void setup()
{
  Serial.begin(9600); //DEBUG ////DEL_ME
  irRecv.enableIRIn();
  setup_pins();
  setup_wifi();
  setup_mqtt();
}

// LOOP
void loop()
{
  // Detect deconnection while trying to listen on input channel
  if (!mqttClient.loop())
  {
    if(timerMqttCon.is_timer_running() == false)
    {
      timerMqttCon.start_timer();
    }
  }

  update_all_timer();

  if (irRecv.decode(&irFrame))
  {
    read_IR_frame(irFrame.value & 0xFFFF);
    delay(100);
    irRecv.resume(); // Receive the next value
  }
}
