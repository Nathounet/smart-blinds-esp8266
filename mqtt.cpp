#include "mqtt.h"
#include "actuator.h"

//LOCALS
const char* mqttServer     = "192.168.178.21";
const char* clientID       = "Smart-Blinds";
const char* mqttUsername   = "smart-blinds";
const char* mqttPassword   = "wakemeupbeforeyougogo";
const char* mqttAlarmIn    = "trigger-alarm";
const char* mqttAlarmOut   = "trigger-alarm_ACK";
const char* mqttTimeSetIn  = "set-alarm-time_ACK";
const char* mqttTimeSetOut = "set-alarm-time";
char alarmTime[6];

void setup_mqtt()
{
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(on_message);
  reconnect();
}

void on_message(char* topic, byte* payload, unsigned int payloadSize)
{
  Serial.print("receiving "); ////DEL_ME
  Serial.println((char)(payload[0])); ////DEL_ME
  // alarm trigger received
  if ((char)payload[0] == '1')
  {
    mqttClient.publish(mqttAlarmOut, "2"); // ack
    up();
  }

  // ack for set time received
  else if ((char)payload[0] == '2')
  {
    timerMqttTx.reset_timer(); // stop sending loop
  }
}

void reconnect()
{
  //TODO return needed ?
  Serial.print(" reconnect"); ////DEL_ME
  if (mqttClient.connect(clientID, mqttUsername, mqttPassword))
  {
    mqttClient.publish(mqttAlarmOut, "0"); // signal that is ready to receive
    mqttClient.subscribe(mqttAlarmIn);     // open an 'input topic' for alarm trigger
    mqttClient.publish(mqttTimeSetOut, "0");  // signal that is ready to receive
    mqttClient.subscribe(mqttTimeSetIn);      // open an 'input topic' for new time set ack
    timerMqttCon.reset_timer();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(" ->success"); ////DEL_ME
  }
  else
  {
    timerMqttCon.start_timer();
    digitalWrite(LED_BUILTIN, LOW); //Turn error led on
    Serial.println(" ->failure"); ////DEL_ME
  }
}

void save_time(String newTime)
{
  newTime.toCharArray(alarmTime, 6) ; // string to char*
  send_time();
}

void send_time()
{
  Serial.print("sending:"); ////DEL_ME
  Serial.print(alarmTime); ////DEL_ME
  timerMqttTx.start_timer();
  if(mqttClient.publish(mqttTimeSetOut, alarmTime))
  {
    Serial.println(":sent correctly"); ////DEL_ME
  }
  else
  {
    Serial.println(":pb while sending"); ////DEL_ME
    reconnect();
  }
}
