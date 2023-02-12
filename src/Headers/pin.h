#ifndef PIN_H
#define PIN_H

#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>

inline uint16_t kIrLed = D2;
inline uint16_t kIrLed2 = D3;
inline IRac ac(kIrLed);
inline IRac ac2(kIrLed2);

inline int buttonTransmit = D4;
inline int buttonLoop = D5;
inline int lightTrigger = 2;

inline int pin[] = {kIrLed, kIrLed2, buttonTransmit, buttonLoop, lightTrigger};
inline String pinKey[] = {"ac1", "ac2", "buttonTransmit", "buttonLoop", "lightTrigger"};

#endif