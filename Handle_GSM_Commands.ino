void gsm_send_at_command(char *cmd)
{
  GSM.println(cmd);
}

bool gsm_extract_value_from_response(char *out_str, int out_len, int timeout_ms) {
  char line[128];
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

    // Case 1: Value inside double quotes
    char *start = strchr(line, '"');
    if (start) {
      Serial.println(line);
      start++; // Move past opening quote
      char *end = strchr(start, '"');
      if (end) {
        int copy_len = end - start;
        if (copy_len >= out_len) copy_len = out_len - 1;
        strncpy(out_str, start, copy_len);
        out_str[copy_len] = '\0';
        return true;
      }
    }

    // Case 2: Value after colon without quotes
    char *colon = strchr(line, ':');
    if (colon) {
      Serial.println(line);
      colon++; // Move past colon
      while (*colon == ' ') colon++; // Skip spaces

      int i = 0;
      while (colon[i] && !isspace((unsigned char)colon[i]) && i < out_len - 1) {
        out_str[i] = colon[i];
        i++;
      }
      out_str[i] = '\0';

      if (i > 0) return true;
    }

    // Case 3: Whole line is the value (alphanumeric, no colon/quotes)
    if (strlen(line) > 0 && strlen(line) < out_len) {
      strcpy(out_str, line);
      return true;
    }
  }

  return false;
}

int gsm_read_line(char *buffer, int max_len, int timeout_ms) {
  int index = 0;
  unsigned long start_time = millis();

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

char value[64];
void gsm_setup_sim(bool check)
{
  if(check)
  {
    gsm_send_at_command(GSM_MC60_AT_TCP_CONNECT);
  
 
      // Read data from MC60 and print to Serial Monitor
    gsm_extract_value_from_response(value,sizeof(64),2000);
    delay(1000);
  }

  
}

//void gsm_setup_sim(bool check)
//{
//  bool success = false;
//  int i=0;
//  if(check)
//  {
//
//     sendATCommand(AT_CSQ);
//     delay(100); 
//     
//     /*to query the SIM status and network registration status*/
//     sendATCommand(AT_CPIN);
//     delay(100);
//     
//       gsm_send_at_command(GSM_AT_IMEI_CMD);
//       delay(500); 
//
//     /*select TCPIP Stack mode*/
//     sendATCommand(AT_QIMODE);
//     delay(500); 
//     
//     /*set APN*/
//     sendATCommand(AT_QICSGP);
//     delay(500); 
//     
//     /* Start TCPIP task*/
//     sendATCommand(AT_QIREGAPP);
//     delay(500);
//
//     /*Check the current connecting mode*/
//     sendATCommand(AT_QICSGP);
//     delay(500);
//
//     /* The current connecting mode is GPRS connecting mode */
//     /*Activate GPRS context*/
//     sendATCommand(AT_QIACT);
//     delay(500);
//
//     /* Get the local IP address */
//     sendATCommand(AT_QILOCIP);
//     delay(500);
//
//     /* Use ATV1 to set the response format */
//     sendATCommand(AT_ATV1);
//     delay(500);
//
//     /* Use AT+QIHEAD=1 to add the header information when receive data */
//     sendATCommand(AT_QIHEAD);
//     delay(500);
//
//     sendATCommand(AT_QIMUX);
//     delay(500);
//
//     /* Use AT+QIDNSIP=0 to use the IP address to establish TCP/UDP session, while AT+QIDNSIP=1 is use the domain name to establish TCP/UDP session */
//     sendATCommand(AT_QIDNSIP);
//     delay(500);
//
//      sendATCommand(AT_TCP_CONNECT);
//     delay(500);
//     
//  }
//
//}
