#ifndef MQTT_H
#define MQTT_H

#include "client.h"
#include "topic.h"
#include "packet.h"
#include "static.h"
#include "acconfig.h"

// Setup MQTT
inline const char *mqttServer = "test.mosquitto.org";
inline const char *mqttUsername = "pi";
inline const char *mqttPassword = "qwertasdfg";
inline int port = 1883;

inline const char *mqttClientID = String(ESP.getChipId()).c_str();

void setupMQTTConnection();
void callback(char *topic, byte *message, unsigned int length);
void mqttReconnect();

#endif