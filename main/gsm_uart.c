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

void gsm_read_response() {
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(GSM_UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
    if (len > 0) {
     data[len] = 0;
     ESP_LOGI(TAG, "Received: %s", (char *)data);
    } else {
        ESP_LOGW(TAG, "No response from GSM module");
    }
}

void gsm_imei_response(char *imei,const char* cmd,int cmd_len) {
    uint8_t data[BUF_SIZE],count=0;
    int len = uart_read_bytes(GSM_UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
    if (len > 0) {
        data[len] = 0;
        for(int i=cmd_len,j=0;i<len;i++,j++){
            imei[j]=data[i];
            if(data[i] == '\n'){
                count++;
                if(count == 2){
                    imei[j] = 0; // Null-terminate the string
                    ESP_LOGI(TAG, "IMEI: %s", imei);
                    count=0;   break;
                }
            }
        }
        //imei[j] = 0;
        memset(data, 0, BUF_SIZE);
    } else {
        ESP_LOGW(TAG, "No response from GSM module");
    }
}
