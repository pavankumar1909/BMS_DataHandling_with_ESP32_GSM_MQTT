#include "includes.h"

#include "defines.h"

#include "gsm_uart.h"
#include "wifi_connect.h"

char MQTT_TOPIC[20];

void app_main() {
    //char line[BUF_SIZE];
    init_gsm_uart();
    vTaskDelay(pdMS_TO_TICKS(2000));  // Wait for GSM module to power up
     char cmd_response[100];
     gsm_send_cmd(GSM_AT_IMEI_CMD);  // get IMEI number
     if (gsm_extract_value_from_response(cmd_response, sizeof(cmd_response), 3000)) {
        printf("IEMI value: %s\n", cmd_response);
        strcpy(MQTT_TOPIC, cmd_response);
        printf("MQTT_TOPIC: %s\n", MQTT_TOPIC);
    } 
     else{
        printf("Failed to extract value\n");}

    wifi_init_sta();    

    //  gsm_send_cmd(GSM_AT_CMD);  // Test command
    //  gsm_read_response(cmd_response);
    //  printf("Command Response: %s\n", cmd_response);
    //  gsm_send_cmd(GSM_AT_SIGNAL_CMD);  // Signal quality
    //  gsm_read_response(cmd_response);
    //  printf("Command Response: %s\n", cmd_response);
   

    // gsm_send_cmd(GSM_AT_SIMSTAUS_CMD);  // check SIM card status
    // gsm_read_response(cmd_response);
    // printf("Command Response: %s\n", cmd_response);
    // gsm_send_cmd(GSM_AT_SIMCARD_NUM_CMD);  // SIM card number
    // gsm_read_response(cmd_response);
    // printf("Command Response: %s\n", cmd_response);

   
    


}
   
