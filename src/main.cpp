#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

#include <ParkMasterDevice.h>
#include <PakMasterDisplay.h>
#include <ParkMasterModbus.h>

// --- Objects ---

byte mac[] = MAC_ADDRESS;

void setup()
{
  Serial.begin(115200);
  pinMode(STATUS_LED, OUTPUT);

  // 3. initialize Modbus
  setupModBus();

  // 1. Initialize OLED
  setupDsiplay();

  // 2. Initialize Ethernet (W5500)
  Ethernet.init(ETH_CS);
  if (Ethernet.begin(mac) == 0)
  {
    display.println("Eth Failed (DHCP)");
  }
  else
  {
    display.print("IP: ");
    display.println(Ethernet.localIP());
  }
  display.display();

  // 3. Initialize Modbus (Hardware Serial 2)
  Serial2.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX);
  node.begin(1, Serial2); // Slave ID 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  delay(2000);
}

void loop()
{

  // Update Display
  displayLoop();

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

  display.setCursor(0, 50);
  display.print("IP: ");
  display.print(Ethernet.localIP());
  display.display();

  delay(1000);
}