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
    Serial.println("here");
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

char value[500];
void gsm_setup_sim(bool check)
{
  if(check)
  {
    //  print_cmd("AT+COPS=?",11000);
    
    gsm_send_at_command("AT+COPS=?");
    gsm_extract_value_from_response(value,sizeof(value),11000);  // Read data from MC60 and print to Serial Monitor
    Serial.println(value);
  }
  
}
