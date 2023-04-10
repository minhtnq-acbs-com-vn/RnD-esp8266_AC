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
  
  digitalWrite(lightTrigger, HIGH);
  pinMode(lightTrigger, OUTPUT);
  pinMode(buttonLoop, INPUT_PULLUP);
  pinMode(buttonTransmit, INPUT_PULLUP);

  // Init wifi and mqtt
  wifiConnect();
  setupMQTTConnection();
  delay(500);
  sentDeviceInfo();
  delay(500);
  setupDeviceConfig();
  delay(200);
  setupAC();
  EEPROM.begin(romSize);
  EEPROM.get(romAddress, lastDecode);
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