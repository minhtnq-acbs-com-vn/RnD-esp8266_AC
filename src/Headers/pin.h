#ifndef PIN_H
#define PIN_H

#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>

inline uint16_t kIrLed = D2;
inline IRac ac(kIrLed);

inline int buttonTransmit = D4;
inline int buttonLoop = D5;
inline int lightTrigger = 2;

inline int pin[] = {kIrLed, buttonTransmit, buttonLoop, lightTrigger};
inline String pinKey[] = {"ac", "buttonTransmit", "buttonLoop", "lightTrigger"};

#endif