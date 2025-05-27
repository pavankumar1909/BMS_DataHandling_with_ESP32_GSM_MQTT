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



void loop()
{
//  Serial.println("in loop");
//  delay(500);
}

//char val[200];
//void loop() {
 // gsm_setup_sim(true);
//  gsm_send_at_command("AT+COPS=?");
//  gsm_extract_value_from_response(val,sizeof(val),11000);
//}
