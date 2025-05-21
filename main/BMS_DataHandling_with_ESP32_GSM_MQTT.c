#include "includes.h"
#include "gsm_uart.h"



void app_main() {
    init_gsm_uart();
    vTaskDelay(pdMS_TO_TICKS(2000));  // Wait for GSM module to power up
    
    
    gsm_send_cmd("AT");  // Test command
    gsm_read_response();

    gsm_send_cmd("AT+CSQ");  // Signal quality
    gsm_read_response();

    gsm_send_cmd("AT+CPIN?");  // check SIM card status
    gsm_read_response();

    gsm_send_cmd("AT+CCID");  // SIM card number
    gsm_read_response();

    gsm_send_cmd("AT+CGSN");  // get IMEI number
    gsm_read_response();
   
}
