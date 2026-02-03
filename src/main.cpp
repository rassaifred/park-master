#include <Arduino.h>
// Include ParkMaster Modules
#include <ParkMasterDevice.h>
#include <ParkMasterDisplay.h>
#include <ParkMasterPushButton.h>
#include <ParkMasterModbus.h>
#include <ParkMasterEthernet.h>

// Main Setup Function
void setup()
{
  // Initialize Serial for debugging
  Serial.begin(115200);
  Serial.println("Starting ParkMaster ...");  
  // 1. Setup Device
  setupDevice();
  // 2. Setup Push Button
  setupPushButtnon();
  // 3. Setup Modbus
  setupModBus();
  // 4. Setup Display
  setupDsiplay();
  // 5. Setup Ethernet
  setupEthernet();
  // Initial delay
  delay(2000);
}

// Main Loop Function
void loop()
{
  // Update Display
  displayLoop();
  // Update Modbus
  loopModbus();
  // Show Button State
  display.setCursor(0, 25);
  display.print("Btn: "); 
  display.println(isButtonPressed() ? "PRESSED" : "OFF");
  // Show IP Address
  display.print("IP: ");
  display.print(Ethernet.localIP());
  // Refresh Display
  display.display();
  // Small delay
  delay(100);
}