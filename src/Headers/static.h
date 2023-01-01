#ifndef STATIC_H
#define STATIC_H

#include <Arduino.h>

#include "client.h"
#include "topic.h"
#include "packet.h"
#include "pin.h"

void setLight(String state);
void publishConfirm(String type);

#endif