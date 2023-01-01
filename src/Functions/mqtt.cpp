#include "../Headers/mqtt.h"

void setupMQTTConnection()
{
    client.setServer(mqttServer, port);
    client.setCallback(callback);
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.println(topic);
  String strMsg;
  for (uint32_t i = 0; i < length; i++)
  {
    strMsg += (char)message[i];
  }
  Serial.println(strMsg);
  //***Insert code here to control other devices***
  if (strMsg == serverRequestACOn)
  {
    configAC(true);
    publishConfirm("ac");
  }
  else if (strMsg == serverRequestACOff)
  {
    configAC(false);
    publishConfirm("ac");
  }
  else if (strMsg == serverRequestLightOn)
  {
    setLight("on");
    publishConfirm("light");
  }
  else if (strMsg == serverRequestLightOff)
  {
    setLight("off");
    publishConfirm("light");
  }
}

void mqttReconnect()
{
  while (!client.connected())
  {
    Serial.println("Attemping MQTT connection...");
    if (client.connect(mqttClientID, mqttUsername, mqttPassword))
    {
      Serial.println("Connected");

      //***Subscribe all topic you need***
      client.subscribe(topicACServer);
    }
    else
    {
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}