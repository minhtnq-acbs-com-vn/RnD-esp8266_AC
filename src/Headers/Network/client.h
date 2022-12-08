#pragma once
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

// Init wifi and mqtt
WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;