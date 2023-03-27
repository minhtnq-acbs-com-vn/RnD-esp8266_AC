#ifndef API_H
#define API_H

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "client.h"
#include "mqtt.h"
#include "packet.h"
#include "pin.h"
#include "topic.h"

inline const String userID = "640ee59066f4b889269ff405";
inline const String systemKey = "4tiNh!B&*$^78PTKqp*v";
inline const String apiHost = "https://rndaedss.ddns.net/api/v1/device";
inline const String roomName = "room1";
inline const String deviceModule = "AC";
inline const String deviceFunc[] = {"AC", "LightTrigger"};
inline const String deviceName = String(ESP.getChipId());
inline const String apiQuery = apiHost + "/" + deviceName;

void sentDeviceInfo();
String getDeviceInfo();
void setupDeviceConfig();
void setupPacketConfig(DynamicJsonDocument doc);
void setupPin(DynamicJsonDocument doc);
void printChanges(String option);

#endif