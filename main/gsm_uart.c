#include "includes.h"
#include "gsm_uart.h"
#include "defines.h"

static const char *TAG = "GSM_UART";

void init_gsm_uart() {
    const uart_config_t uart_config = {
        .baud_rate = BAUDRATE_115200,  // Make sure this matches your GSM module
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(GSM_UART_NUM, &uart_config);
    uart_set_pin(GSM_UART_NUM, GSM_TXD_PIN, GSM_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(GSM_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
}


void gsm_send_cmd(const char* cmd) {
    uart_write_bytes(GSM_UART_NUM, cmd, strlen(cmd));
    uart_write_bytes(GSM_UART_NUM, "\r\n", 2);
}

void gsm_read_response(char *cmd_response) {
    memset(cmd_response, 0, sizeof(cmd_response));
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(GSM_UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
    if (len > 0) {
     data[len] = 0;
     memcpy(cmd_response, data, len);
     cmd_response[len] = 0; // Null-terminate the string
     ESP_LOGI(TAG, "Received: \n%s", (char *)data);
    } 
        else {
        ESP_LOGW(TAG, "No response from GSM module");
    }
}


bool gsm_extract_value_from_response(char *out_str, int out_len, int timeout_ms) {
    char line[128];
    int total_time = 0;
    int per_line_timeout = 500;

    while (total_time < timeout_ms) {
        int len = gsm_read_line(line, sizeof(line), per_line_timeout);
        total_time += per_line_timeout;

        if (len <= 0) continue;

        // Skip command echo or control responses
        if (strstr(line, "AT") || strcmp(line, "OK") == 0 || strcmp(line, "ERROR") == 0)
            continue;

        // Case 1: Value inside double quotes
        char *start = strchr(line, '"');
        if (start) {
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
            colon++; // Move past colon
            while (*colon == ' ') colon++; // Skip spaces

            // Copy alphanumeric string (stop at newline or null)
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

        //Case 4: Only OK 
        if (strcmp(line, "OK") == 0 ) {
            //ESP_LOGI(TAG, "Received: %s", line);
            return true;
        }

        // Case 5: Only ERROR
        if (strcmp(line, "ERROR") == 0 ) {
           // ESP_LOGI(TAG, "Received: %s", line);
            return false; 
        }
    }

    return false;
}
// Helper to get current time in milliseconds
static uint64_t millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Reads a line from GSM UART until \n or timeout
int gsm_read_line(char *buffer, int max_len, int timeout_ms) {
    int index = 0;
    uint8_t byte;
    uint64_t start_time = millis();

    while ((millis() - start_time) < timeout_ms && index < max_len - 1) {
        int len = uart_read_bytes(GSM_UART_NUM, &byte, 1, 20 / portTICK_PERIOD_MS);
        if (len > 0) {
            if (byte == '\n') {
                break; // End of line
            } else if (byte == '\r') {
                continue; // Skip carriage return
            } else {
                buffer[index++] = byte;
            }
        }
    }

    buffer[index] = '\0';  // Null-terminate
    return index;
}