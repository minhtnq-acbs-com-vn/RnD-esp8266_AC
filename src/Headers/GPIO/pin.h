#pragma once

#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>

const uint16_t kIrLed = D2;
IRac ac(kIrLed);

const int buttonLoop = D4;
const int buttonTransmit = D3;
const int lightTrigger = 2;