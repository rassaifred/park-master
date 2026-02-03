#ifndef _PARKMASTERDEVICE_H
#define _PARKMASTERDEVICE_H

#include <Arduino.h>

// --- Pin Definitions ---

#define STATUS_LED 2

void setupDevice()
{

    Serial.println("Starting ParkMaster ...");
    pinMode(STATUS_LED, OUTPUT);
}

#endif // _PARKMASTERDEVICE_H