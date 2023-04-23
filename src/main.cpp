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
  delay(500);
  
  digitalWrite(lightTrigger, HIGH);
  pinMode(lightTrigger, OUTPUT);
  pinMode(buttonLoop, INPUT_PULLUP);
  pinMode(buttonTransmit, INPUT_PULLUP);
  setupAC();
  EEPROM.begin(romSize);
  EEPROM.get(romAddress, lastDecode);

  // Init wifi and mqtt
  wifiConnect();
  setupMQTTConnection();
  sentDeviceInfo();
  setupDeviceConfig();
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