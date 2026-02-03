#ifndef PARK_MASTER_PUSH_BUTTON_H
#define PARK_MASTER_PUSH_BUTTON_H

#include <Arduino.h>

// --- Pin Definitions ---
#define BUTTON_PIN     15

void setupPushButtnon()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Active Low
}

bool isButtonPressed()
{
    return digitalRead(BUTTON_PIN) == LOW; // Active Low // bool btnState = digitalRead(BUTTON_PIN); // Active Low
}

#endif // PARK_MASTER_PUSH_BUTTON_H