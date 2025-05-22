#ifndef __DEFINES_H
#define __DEFINES_H


#define GSM_UART_NUM UART_NUM_1
#define BUF_SIZE 1024

#define GSM_TXD_PIN (17)
#define GSM_RXD_PIN (16)
#define BAUDRATE_115200 115200

#define GSM_AT_CMD              "AT"
#define GSM_AT_SIMSTAUS_CMD     "AT+CPIN?"
#define GSM_AT_SIGNAL_CMD       "AT+CSQ"
#define GSM_AT_IMEI_CMD         "AT+CGSN"
#define GSM_AT_SIMCARD_NUM_CMD  "AT+CCID"

#define WIFI_SSID      "Galaxy A3075C4"   
#define WIFI_PASS      "99999999"  
#define WIFI_CONNECTED_BIT BIT0
#define MAX_RETRY       5


#endif // __DEFINES_H