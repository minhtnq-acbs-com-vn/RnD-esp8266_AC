#ifndef PACKET_H
#define PACKET_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "pin.h"
#include "topic.h"
#include "api.h"

// Setup string
inline String serverRequestACOn = "requestACOn";
inline String serverRequestACOff = "requestACOff";
inline String deviceACConfirmed = "deviceACConfirmed";

inline String serverRequestLightOn = "requestLightOn";
inline String serverRequestLightOff = "requestLightOff";
inline String deviceLightConfirmed = "deviceLightConfirmed";
inline String requestAPI = "requestAPI";

inline String ack[] = {deviceACConfirmed, deviceLightConfirmed};
inline String ackKey[] = {"ac", "light"};
inline String request[] = {serverRequestACOn, serverRequestACOff, serverRequestLightOn, serverRequestLightOff, requestAPI};
inline String requestKey[] = {"acOn", "acOff", "lightOn", "lightOff", "api"};

String packToJson();

#endif