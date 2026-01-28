#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ModbusMaster.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Pin Definitions ---
#define ETH_CS          5
#define RS485_RX        16
#define RS485_TX        17
#define RS485_RE_DE     4
#define STATUS_LED      2
#define SDA_PIN         21
#define SCL_PIN         22

// --- Objects ---
Adafruit_SSD1306 display(128, 64, &Wire, -1);
ModbusMaster node;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Callback for Modbus Flow Control
void preTransmission()  { digitalWrite(RS485_RE_DE, HIGH); }
void postTransmission() { digitalWrite(RS485_RE_DE, LOW);  }

void setup() {
  Serial.begin(115200);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(RS485_RE_DE, OUTPUT);
  digitalWrite(RS485_RE_DE, LOW);

  // 1. Initialize OLED
  Wire.begin(SDA_PIN, SCL_PIN);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Initializing...");
  display.display();

  // 2. Initialize Ethernet (W5500)
  Ethernet.init(ETH_CS);
  if (Ethernet.begin(mac) == 0) {
    display.println("Eth Failed (DHCP)");
  } else {
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

void loop() {
  uint8_t result;
  uint16_t data[2];

  // Example: Read 2 Holding Registers starting at address 0
  result = node.readHoldingRegisters(0, 2);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("--- MODBUS MASTER ---");

  if (result == node.ku8MBSuccess) {
    digitalWrite(STATUS_LED, HIGH);
    display.print("Reg0: "); display.println(node.getResponseBuffer(0));
    display.print("Reg1: "); display.println(node.getResponseBuffer(1));
  } else {
    digitalWrite(STATUS_LED, LOW);
    display.print("Error: "); display.println(result, HEX);
  }

  display.setCursor(0, 50);
  display.print("IP: "); display.print(Ethernet.localIP());
  display.display();

  delay(1000);
}