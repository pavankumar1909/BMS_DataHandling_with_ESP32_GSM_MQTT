#ifndef __DEFINES_HPP_
#define __DEFINES_HPP_ 
 //AT COMMANDS
#define AT_IEMI        "AT+GSN" 

#define AT_CSQ         "AT+CSQ"
#define AT_W           "AT&W"
#define AT_CPIN        "AT+CPIN?"
#define AT_CGREG       "AT+CGREG?"
#define AT_QIMODE      "AT+QIMODE=0"
#define AT_QICSGP      "AT+QICSGP=1,\"airteliot.com\""
#define AT_QIREGAPP    "AT+QIREGAPP"
#define AT_QICSGP      "AT+QICSGP?"
#define AT_QIACT       "AT+QIACT"
#define AT_QILOCIP     "AT+QILOCIP"
#define AT_ATV1        "ATV1"
#define AT_QIHEAD      "AT+QIHEAD=1"
#define AT_QIMUX       "AT+QIMUX"
#define AT_QIDNSIP     "AT+QIDNSIP=0"
#define AT_TCP_CONNECT "AT+QIOPEN=1,\"TCP\",\"85.119.83.194\",1883"
#endif __DEFINES_HPP_
