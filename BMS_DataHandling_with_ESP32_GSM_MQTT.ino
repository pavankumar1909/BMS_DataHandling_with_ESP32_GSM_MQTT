#include <HardwareSerial.h>
#include "defines.hpp"
#include "Handle_GSM_Commands.hpp"

#define MODEM_TX 17  // ESP32 TX to MC60 RX
#define MODEM_RX 16  // ESP32 RX to MC60 TX

HardwareSerial GSM(1); // Use UART1

void setup() {
  Serial.begin(115200);    // USB serial monitor
  delay(1000);
  Serial.println("Starting GSM AT test...");

  GSM.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX); // Start GSM UART
  delay(2000);

  GSM.println("AT"); // Send test command

  setup_sim(HIGH);
}

void loop() {
  // Read data from MC60 and print to Serial Monitor
  while (GSM.available()) {
    Serial.write(GSM.read());
  }

  // Send input from Serial Monitor to GSM
  while (Serial.available()) {
    GSM.write(Serial.read());
  }
}
