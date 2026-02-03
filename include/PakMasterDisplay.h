#ifndef _PARKMASTERDISPLAY_H
#define _PARKMASTERDISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Pin Definitions ---
#define SDA_PIN 21
#define SCL_PIN 22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 1. Initialize OLED
void setupDsiplay()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("OLED failed"));
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Initializing...");
    display.display();
}

void displayLoop()
{
    // Placeholder for any display updates needed in the main loop
    display.clearDisplay();
    display.setCursor(0, 0);
}

#endif // _PARKMASTERDISPLAY_H