#ifndef CLIENT_H
#define CLIENT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>

inline WiFiClientSecure secureClient;
inline WiFiClient espClient;
inline PubSubClient client(espClient);
inline WiFiManager wifiManager;

#endif