#include "includes.hpp"

#include "defines.hpp"
#include "Handle_GSM_Commands.hpp"
#include "mqtt_library.hpp"



void setup() {
  Serial.begin(115200);    // USB serial monitor
  delay(1000);
  Serial.println("Starting GSM AT test...");

  GSM.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX); // Start GSM UART
  delay(2000);

  gsm_setup_sim(true);
 
}



char buffer[150];
void loop() 
{
  if(GSM.available()) 
  {
    Serial.println("in loop");
     // Optional: Wait for server response
     int i=0;
    for(;GSM.available();i++) 
    {
       buffer[i]=GSM.read();
       Serial.print(buffer[i]);
      
    }
    buffer[i]='\0';
    const char*substr="pavandevice/progress";
//    Serial.println(strlen(buffer));
//    Serial.println();

    //given string sequence after 10 characters because at 8,9  positions receiving escape characters
    char * check=strstr(buffer+10,substr); 
    
    if(check)
    {
      Serial.println("true");
      check+=strlen("pavandevice/progress");
      Serial.println(check);
      // Serial.println(msg);
    }
    memset(buffer,0,sizeof(buffer));
//    for(int j=0;p;j++) 
//    {
//       Serial.print(p[j]);
//    }
    
  }
//    String line = GSM.readStringUntil('\n');
//    line=line.substring(10);
////    Serial.println("line: ");
////    Serial.println(line);
//    const char *searchStr = "pavandevice/progress";
//    int index = line.indexOf(searchStr);
//
//  if (index != -1) 
//  {
//    // Move past the "pavandevice/progress" part
//    int startIndex = index + strlen(searchStr);
//    String msg = line.substring(startIndex);
//    Serial.print("Extracted message: ");
//    Serial.println(msg);
//  } 
//  else {
//    Serial.println("Substring not found.");
//  }
//
//  }
  delay(1000);
}
