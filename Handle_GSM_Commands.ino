#include"Handle_GSM_Commands.hpp"

void gsm_send_at_command(char *cmd)
{
  GSM.println(cmd);
}

bool gsm_extract_value_from_response(char *out_str, int out_len, int timeout_ms) 
{
  char line[200];
  unsigned long total_time = 0;
  const unsigned long per_line_timeout = 500;

  while (total_time < (unsigned long)timeout_ms) {
    int len = gsm_read_line(line, sizeof(line), per_line_timeout);
    total_time += per_line_timeout;

    if (len <= 0) continue;

    // Skip command echo or control responses
    if (strstr(line, "AT") || strcmp(line, "OK") == 0 || strcmp(line, "ERROR") == 0)
    {
//      if(strcmp(line, "OK") == 0)
//      {
//        Serial.println("OK");
//      }
        Serial.println(line);
      continue;
    }
    
    strcpy(out_str,line);
    out_str[strlen(line)]='\0';
//    Serial.println("here");
    Serial.println(line);
//    // Case 1: Value inside double quotes
//    char *start = strchr(line, '"');
//    if (start) {
//     // Serial.println(line);
//      start++; // Move past opening quote
//      char *end = strchr(start, '"');
//      if (end) {
//        int copy_len = end - start;
//        if (copy_len >= out_len) copy_len = out_len - 1;
//        strncpy(out_str, start, copy_len);
//        out_str[copy_len] = '\0';
//        return true;
//      }
//    }
//
//    // Case 2: Value after colon without quotes
//    char *colon = strchr(line, ':');
//    if (colon) {
//      Serial.println(colon);
//      colon++; // Move past colon
//      while (*colon == ' ') colon++; // Skip spaces
//
//      int i = 0;
//      while (colon[i] && !isspace((unsigned char)colon[i]) && i < out_len - 1) {
//        out_str[i] = colon[i];
//        i++;
//      }
//      out_str[i] = '\0';
//
//      if (i > 0) return true;
//    }
//
//    // Case 3: Whole line is the value (alphanumeric, no colon/quotes)
//    if (strlen(line) > 0 && strlen(line) < out_len) {
//     // Serial.println(line);
//      strcpy(out_str, line);
//      return true;
//    }
  }

  return false;
}

int gsm_read_line(char *buffer, int max_len, int timeout_ms) {
  int index = 0;
  unsigned long start_time = millis();
  memset(buffer,0,sizeof(buffer));
  while ((millis() - start_time) < (unsigned long)timeout_ms && index < max_len - 1) {
    if (GSM.available()) {
      char c = GSM.read();
      if (c == '\n') {
        break;
      } else if (c == '\r') {
        continue;
      } else {
        buffer[index++] = c;
      }
    }
  }

  buffer[index] = '\0';
  return index;
}
void read_response(char *buffer, int max_len,int timeout_ms)
{
  int index = 0;
  unsigned long start_time = millis();
  memset(buffer,0,sizeof(buffer));
  while ((millis() - start_time) < (unsigned long)timeout_ms && index < max_len - 1) {
    if (GSM.available()) {
      char c = GSM.read();
        buffer[index++] = c;
        //Serial.print(buffer[index]);
    }
  }
  
  buffer[index] = '\0';
}
void clean_buffer(){
    while (GSM.available()) {
    GSM.read();
  }
}
char value[500];
//
//bool sendMQTTConnect(const char* clientID, const char* username, const char* password){
//  // Open TCP connection first before calling this
//  GSM.println("AT+QISEND");
//  delay(1000);
//  if (!GSM.find(">")) {
//    Serial.println("No prompt from QISEND");
//    return false;
//  }
//
//  // Step 1: Build MQTT CONNECT packet
//
//  byte fixedHeader[] = {
//    0x10, // CONNECT packet
//    0x00  // Remaining length to fill later
//  };
//
//  byte variableHeader[] = {
//    0x00, 0x04, 'M', 'Q', 'T', 'T',  // Protocol name
//    0x04,        // Protocol level = 4 (MQTT 3.1.1)
//    0xC2,        // Connect flags: User+Pass+CleanSession
//    0x00, 0x3C   // Keep alive = 60s
//  };
//
//  // Prepare payload
//  int payloadLen = 0;
//  byte payload[200];
//
//  auto appendString = [&](const char* str) {
//    int len = strlen(str);
//    payload[payloadLen++] = len >> 8;
//    payload[payloadLen++] = len & 0xFF;
//    for (int i = 0; i < len; i++) {
//      payload[payloadLen++] = str[i];
//    }
//  };
//
//  appendString(clientID);
//  appendString(username);
//  appendString(password);
//
//  // Total remaining length
//  byte remainingLen = sizeof(variableHeader) + payloadLen;
//  fixedHeader[1] = remainingLen;
//
//  // Step 2: Send packets
//  GSM.write(fixedHeader, 2);
//  GSM.write(variableHeader, sizeof(variableHeader));
//  GSM.write(payload, payloadLen);
//
//  // Step 3: End with Ctrl+Z
//  GSM.write(0x1A);
//  delay(1000);
//
//  // Optional: Read response from broker
//  while (GSM.available()) {
//    Serial.write(GSM.read());
//  }
//
//  return true;
//}

bool mqttConnect(const char* clientID) {
  Serial.println("Sending MQTT CONNECT packet...");

  GSM.println("AT+QISEND");
  delay(1000);

//  if (!GSM.find(">")) {
//    Serial.println("No prompt after AT+QISEND");
//    return false;
//  }

  byte packet[128];
  int index = 0;

  // Fixed header
  packet[index++] = 0x10; // MQTT CONNECT packet type
  // Remaining length placeholder; to be filled later

  int vh_start = index;

  // Variable header
  packet[index++] = 0x00; packet[index++] = 0x04; // Length of "MQTT"
  packet[index++] = 'M'; packet[index++] = 'Q'; packet[index++] = 'T'; packet[index++] = 'T';
  packet[index++] = 0x04; // Protocol Level
  packet[index++] = 0x02; // Connect Flags: clean session only
  packet[index++] = 0x00; packet[index++] = 0x3C; // Keep Alive: 60 seconds

  // Payload: Client ID
  int clientIDLen = strlen(clientID);
  packet[index++] = (clientIDLen >> 8) & 0xFF;
  packet[index++] = clientIDLen & 0xFF;
  memcpy(&packet[index], clientID, clientIDLen);
  index += clientIDLen;

  // Now, compute remaining length
  int remainingLength = index - vh_start;

  // Insert remaining length at packet[1]
  packet[1] = remainingLength;

  // Send MQTT CONNECT packet over TCP
  GSM.write(packet, index);
  GSM.write(0x1A); // Ctrl+Z to end
  delay(1000);

  // Optional: Wait for server response
  while (GSM.available()) {
    Serial.write(GSM.read());
  }

  return true;
}
bool mqttPublish(const char* topic, const char* message) {
  Serial.println("Sending MQTT PUBLISH packet...");

  GSM.println("AT+QISEND");
  delay(500);
//
//  if (!modem.find(">")) {
//    Serial.println("No prompt after AT+QISEND");
//    return false;
//  }

  byte packet[256];
  int index = 0;

  // --- Fixed Header ---
  packet[index++] = 0x30; // PUBLISH packet with QoS 0, DUP 0, Retain 0
  // We'll fill Remaining Length later

  int start_rl = index;

  // --- Variable Header (Topic Name) ---
  int topicLen = strlen(topic);
  packet[index++] = (topicLen >> 8) & 0xFF;
  packet[index++] = topicLen & 0xFF;
  memcpy(&packet[index], topic, topicLen);
  index += topicLen;

  // --- Payload (Message) ---
  int msgLen = strlen(message);
  memcpy(&packet[index], message, msgLen);
  index += msgLen;

  // --- Remaining Length ---
  int remainingLength = index - start_rl;

  // Insert Remaining Length at packet[1] using MQTT variable length encoding
  // (Supports messages < 127 bytes)
  if (remainingLength < 128) {
    packet[1] = remainingLength;
  } else {
    // For longer messages, more encoding needed (can be added if needed)
    Serial.println("Message too long!");
    return false;
  }

  // --- Send Packet ---
  GSM.write(packet, index);
  GSM.write(0x1A); // Ctrl+Z to end AT+QISEND input
  delay(1000);

  while (GSM.available()) {
    Serial.write(GSM.read());
  }

  return true;
}

void gsm_setup_sim(bool check)
{
    //AT+CFUN=1         // Full functionality
    //AT+CPIN?          // Ensure SIM is ready
    //AT+CSQ            // Check signal strength
    //AT+CGREG?         // Ensure registered
   
  if(check)
  {
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIDEACT");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

     clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+CMEE=2");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    gsm_send_at_command("AT+CFUN=1");
    read_response(value,sizeof(value),1000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

    clean_buffer();
    gsm_send_at_command("AT+CPIN?");
    read_response(value,sizeof(value),1000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    gsm_send_at_command("AT+CSQ");
    read_response(value,sizeof(value),1000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+CGREG?");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

    clean_buffer();
    gsm_send_at_command("AT+CGREG=1");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
 
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIMUX=0");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
     
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QICSGP=1,\"airteliot.com\"");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIREGAPP");
    read_response(value,sizeof(value),3000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value); 

    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QICSGP?");
    read_response(value,sizeof(value),3000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIACT");
    read_response(value,sizeof(value),3000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);   //AT+CGPADDR=<cid>
       
//     clean_buffer();
//    memset(value,0,sizeof(value));
//    gsm_send_at_command("AT+QIACT?");
//    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
//    Serial.println(value);

      clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QILOCIP");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

   
      clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("ATV1"); 
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

    
     clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIHEAD=1");
    gsm_extract_value_from_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

     clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIDNSIP=1");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
//     clean_buffer();
//    memset(value,0,sizeof(value));
//    gsm_send_at_command("AT+QIOPEN=\"TCP\",\"test.mosquitto.org\",1883");
//    read_response(value,sizeof(value),10000);  // Read data from MC60 and print to Serial Monitor
//    Serial.println(value);

    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QIOPEN=\"TCP\",\"sytiqhub.in\",1883");
    read_response(value,sizeof(value),10000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

    

     clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QMTOPEN=0,\"sytiqhub.in\",1883");
    read_response(value,sizeof(value),5000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

     clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QISTAT=0");
    read_response(value,sizeof(value),1000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
    
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QMTCONN=0,\"pavankumar\",\"test1\",\"Aabbccdd@1234\"");
    read_response(value,sizeof(value),5000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);

    
    clean_buffer();
    memset(value,0,sizeof(value));
    gsm_send_at_command("AT+QMTPUB=0,0,0,0,\"pavandevice/progress\"");
//    
//    
    delay(1000);
    
    
    publish_msg("pavankumar");
    read_response(value,sizeof(value),2000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
  
  
}

  
//    mqtt_connect("pavankumar","test1","Aabbccdd@1234");
//    delay(1000);
//    send_publish_packet("pavandevice/progress", "AT+COMMANDS from MC60!");
//  mqttPublish
}

void publish_msg(char *msg)
{
    Serial.println("Sending MQTT publish..");
    // Send MQTT CONNECT packet over TCP
    GSM.write(msg,10);
    delay(500);
    GSM.write(0x1A); // Ctrl+Z to end
    delay(500);

     // Optional: Wait for server response
    while(GSM.available()) 
    {
    Serial.write(GSM.read());
    }
}

 
