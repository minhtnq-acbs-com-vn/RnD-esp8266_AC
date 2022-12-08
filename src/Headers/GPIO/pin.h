#pragma once

#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>
#include <EEPROM.h>

const uint16_t kIrLed = D2;
IRac ac(kIrLed);

const int buttonLoop = D4;
const int buttonTransmit = D3;
boolean acPower = false;

decode_type_t chosenBrand[] = {
    MITSUBISHI,
    MITSUBISHI_AC,
    DAIKIN,
    TOSHIBA_AC,
    PANASONIC,
    PANASONIC_AC,
};
decode_type_t lastDecode = UNKNOWN;

const int romSize = sizeof(decode_type_t);
const int romAddress = 0;