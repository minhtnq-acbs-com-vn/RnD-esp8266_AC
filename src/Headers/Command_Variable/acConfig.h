#pragma once

#include <EEPROM.h>
#include <IRac.h>
#include <IRutils.h>

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