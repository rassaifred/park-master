#ifndef _PARKMASTERDEVICE_H
#define _PARKMASTERDEVICE_H

// --- Pin Definitions ---

#define STATUS_LED      2



void setupDevice()
{
    pinMode(STATUS_LED, OUTPUT);
}

#endif // _PARKMASTERDEVICE_H