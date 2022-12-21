#pragma once

// Setup MQTT
const char *mqttServer = "192.168.68.101";
const char *mqttUsername = "pi4";
const char *mqttPassword = "qwertasdfg";
const int port = 1885;

const char *mqttClientID = String(ESP.getChipId()).c_str();