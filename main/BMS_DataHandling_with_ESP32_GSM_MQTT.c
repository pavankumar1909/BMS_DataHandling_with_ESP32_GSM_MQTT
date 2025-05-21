#include "includes.h"
#include "gsm_uart.h"
#include "defines.h"


void app_main() {
    //char line[BUF_SIZE];
    init_gsm_uart();
    vTaskDelay(pdMS_TO_TICKS(2000));  // Wait for GSM module to power up
    
    
    // gsm_send_cmd(GSM_AT_CMD);  // Test command
    // gsm_read_response();

    // gsm_send_cmd(GSM_AT_SIGNAL_CMD);  // Signal quality
    // gsm_read_response();

    // gsm_send_cmd(GSM_AT_SIMSTAUS_CMD);  // check SIM card status
    // gsm_read_response();

    // gsm_send_cmd(GSM_AT_SIMCARD_NUM_CMD);  // SIM card number
    // gsm_read_response();
    char imei[50]; 
    gsm_send_cmd(GSM_AT_IMEI_CMD);  // get IMEI number
    gsm_imei_response(imei,GSM_AT_IMEI_CMD,sizeof(GSM_AT_IMEI_CMD));
    printf("IMEI: %s\n", imei);
}
   
