#include "includes.hpp"


#include "defines.hpp"
#include "Handle_GSM_Commands.hpp"




void setup() {
  Serial.begin(115200);    // USB serial monitor
  delay(1000);
  Serial.println("Starting GSM AT test...");

  GSM.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX); // Start GSM UART
  delay(2000);

  gsm_setup_sim(true);
  
}

void clean_buffer(){
    while (GSM.available()) {
    GSM.read();
  }
}

void loop() {
   // gsm_setup_sim(true);
   gsm_send_at_command(GSM_MC60_AT_IMEI_CMD);
   char value[64];
   memset(value,0,sizeof(value));
   clean_buffer();
   if (gsm_extract_value_from_response(value, sizeof(value), 3000)) {
    Serial.print("Extracted Value: ");
    Serial.println(value);
  } else {
    Serial.println("No value found");
  }

  delay(2000);  // Repeat after delay

}


//void loop() {
//  // Read data from MC60 and print to Serial Monitor
//  while (GSM.available()) {
//    Serial.write(GSM.read());
//  }
//
//  // Send input from Serial Monitor to GSM
//  while (Serial.available()) {
//    GSM.write(Serial.read());
//  }
//}
