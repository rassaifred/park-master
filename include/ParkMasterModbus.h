#ifndef _PARKMASTERMODBUS_H
#define _PARKMASTERMODBUS_H
#include <ModbusMaster.h>

#include <ParkMasterDevice.h>
#include <ParkMasterDisplay.h>

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
    // 3. Initialize Modbus (Hardware Serial 2)
    Serial2.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX);
    node.begin(1, Serial2); // Slave ID 1
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
}

void loopModbus()
{
    uint8_t result;
    uint16_t data[2];

    // Example: Read 2 Holding Registers starting at address 0
    result = node.readHoldingRegisters(0, 2);

    display.println("--- MODBUS MASTER ---");

    if (result == node.ku8MBSuccess)
    {
        digitalWrite(STATUS_LED, HIGH);
        display.print("Reg0: ");
        display.println(node.getResponseBuffer(0));
        display.print("Reg1: ");
        display.println(node.getResponseBuffer(1));
    }
    else
    {
        digitalWrite(STATUS_LED, LOW);
        display.print("Error: ");
        display.println(result, HEX);
    }
}

#endif //_PARKMASTERMODBUS_H