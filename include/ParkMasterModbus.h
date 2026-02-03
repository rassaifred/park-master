#ifndef _PARKMASTERMODBUS_H
#define _PARKMASTERMODBUS_H
#include <ModbusMaster.h>

// --- Pin Definitions ---
#define RS485_RX 16
#define RS485_TX 17
#define RS485_RE_DE 4

// --- Objects ---

ModbusMaster node;

// Callback for Modbus Flow Control
void preTransmission() { digitalWrite(RS485_RE_DE, HIGH); }
void postTransmission() { digitalWrite(RS485_RE_DE, LOW); }

void setupModBus()
{
    // 3. Initialize Modbus
    pinMode(RS485_RE_DE, OUTPUT);
    digitalWrite(RS485_RE_DE, LOW);
}

#endif //_PARKMASTERMODBUS_H