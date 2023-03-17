#ifndef MQTT_H
#define MQTT_H

#include "client.h"
#include "topic.h"
#include "packet.h"
#include "static.h"
#include "acconfig.h"
#include "api.h"

// Setup MQTT
inline const char *mqttServer = "rndaedss.ddns.net";
inline const char *mqttUsername = "aws";
inline const char *mqttPassword = "Rnd_AEDSS2023";
inline int port = 1883;

inline const char *mqttClientID = String(ESP.getChipId()).c_str();

void setupMQTTConnection();
void callback(char *topic, byte *message, unsigned int length);
void requestFilter(String request);
void mqttReconnect();

#endif