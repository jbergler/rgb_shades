#include <SPI.h>
#include <Adafruit_BLE_UART.h>

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

// nRF8001 <-> Teensy 3.1
// SCK <-> SCK (pin 14)
// MISO <-> DIN (pin 12)
// MOSI <-> DOUT (pin 11)
// REQ <-> PIN 10
// RDY <-> PIN 2
// RST <-> PIN 9
// GND <-> GND
// VIN <-> 3.3V

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void ble_write(String s) {
  uint8_t sendbuffer[20];
  char sendbuffersize = min(20, s.length());
  s.getBytes(sendbuffer, 20);
  BTLEserial.write(sendbuffer, sendbuffersize);
}

void setup_ble() {
  BTLEserial.setDeviceName("JONAS");
  BTLEserial.begin();
  BTLEserial.setTimeout(25);

  CORE_PIN13_CONFIG = PORT_PCR_MUX(0);
  CORE_PIN14_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
}

void loop_ble() {
  BTLEserial.pollACI();

  aci_evt_opcode_t status = BTLEserial.getState();
  if (status != laststatus) {
  	if (Serial) {
      if (status == ACI_EVT_DEVICE_STARTED) Serial.println(F("* Advertising started"));
      if (status == ACI_EVT_CONNECTED)      Serial.println(F("* Connected"));
      if (status == ACI_EVT_DISCONNECTED)   Serial.println(F("* Disconnected"));
    }
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED && BTLEserial.available()) {
    String input = BTLEserial.readStringUntil('\n');
    String result = process_command(input);
    ble_write(result);
  }
}
