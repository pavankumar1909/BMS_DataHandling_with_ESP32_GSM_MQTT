#ifndef __DEFINES_HPP_
#define __DEFINES_HPP_ 
 //AT COMMANDS

#define MODEM_TX 17  // ESP32 TX to MC60 RX
#define MODEM_RX 16  // ESP32 RX to MC60 TX

#define GSM_MC60_AT_CSQ         "AT+CSQ"
#define GSM_MC60_AT_W           "AT&W"
#define GSM_MC60_AT_CPIN        "AT+CPIN?"
#define GSM_MC60_AT_CGREG       "AT+CGREG?"
#define GSM_MC60_AT_QIMODE      "AT+QIMODE=0"
#define GSM_MC60_AT_QICSGP      "AT+QICSGP=1,\"airteliot.com\""
#define GSM_MC60_AT_QIREGAPP    "AT+QIREGAPP"
#define GSM_MC60_AT_QICSGP      "AT+QICSGP?"
#define GSM_MC60_AT_IMEI_CMD    "AT+CGSN"
#define GSM_MC60_AT_QIACT       "AT+QIACT"
#define GSM_MC60_AT_QILOCIP     "AT+QILOCIP"
#define GSM_MC60_AT_ATV1        "ATV1"
#define GSM_MC60_AT_QIHEAD      "AT+QIHEAD=1"
#define GSM_MC60_AT_QIMUX       "AT+QIMUX"
#define GSM_MC60_AT_QIDNSIP     "AT+QIDNSIP=0"
#define GSM_MC60_AT_TCP_CONNECT "AT+QIOPEN=\"TCP\",\"85.119.83.194\",1883"


#endif __DEFINES_HPP_
