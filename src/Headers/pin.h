#ifndef PIN_H
#define PIN_H

#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>

inline uint16_t kIrLed = D2;
inline IRac ac(kIrLed);

inline int buttonLoop = D4;
inline int buttonTransmit = D3;
inline int lightTrigger = 2;

#endif