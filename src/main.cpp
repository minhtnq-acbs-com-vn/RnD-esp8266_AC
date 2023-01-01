#include <Arduino.h>

#include "Headers/mqtt.h"
#include "Headers/static.h"
#include "Headers/wificustom.h"
#include "Headers/acconfig.h"

void setup()
{
  // Init Serial console
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");

  // Init wifi and mqtt
  wifiConnect();
  setupMQTTConnection();

  pinMode(buttonLoop, INPUT);
  pinMode(buttonTransmit, INPUT);
  delay(200);
  setupAC();
  EEPROM.begin(romSize);
  EEPROM.get(romAddress, lastDecode);
  pinMode(lightTrigger, OUTPUT);
}

void loop()
{
  if (!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  readButtonLoop();
  readButtonTransmit();
  wifiCheck();
}