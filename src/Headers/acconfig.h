#ifndef ACCONFIG_H
#define ACCONFIG_H

#include <EEPROM.h>
#include <IRac.h>
#include <IRutils.h>
#include "pin.h"
#include "static.h"

inline boolean acPower = false;

inline decode_type_t chosenBrand[] = {
    MITSUBISHI,
    MITSUBISHI_AC,
    DAIKIN,
    TOSHIBA_AC,
    PANASONIC,
    PANASONIC_AC,
};

inline decode_type_t lastDecode = UNKNOWN;

inline int romSize = sizeof(decode_type_t);
inline int romAddress = 0;

void setupAC();
void checkAC();
void configAC(bool option);
void readButtonTransmit();
void readButtonLoop();

#endif