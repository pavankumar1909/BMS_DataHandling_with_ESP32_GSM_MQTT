#ifndef __DEFINES_HPP_
#define __DEFINES_HPP_ 
 //AT COMMANDS

#define MODEM_TX 17  // ESP32 TX to MC60 RX
#define MODEM_RX 16  // ESP32 RX to MC60 TX

/***Network Service Commands***/
//1.Operator Selection
   #define GSM_MC60_AT_COPS_TEST  "AT+COPS=?"      
   #define GSM_MC60_AT_COPS_READ  "AT+COPS?"
   #define GSM_MC60_AT_COPS_WRITE "AT+COPS=0,0"
   
//2.Network Registration Status
   #define GSM_MC60_AT_CREG_TEST  "AT+CREG=?"      
   #define GSM_MC60_AT_CREG_READ  "AT+CREG?"
   #define GSM_MC60_AT_CREG_WRITE "AT+CREG=2"

//3.Signal Quality Report   
   #define GSM_MC60_AT_CSQ_TEST  "AT+CSQ=?"      
   #define GSM_MC60_AT_CSQ_EXEC  "AT+CSQ"

//4.Preferred Operator List
   #define GSM_MC60_AT_CPOL_TEST  "AT+CPOL=?"      
   #define GSM_MC60_AT_CPOL_READ  "AT+CPOL?"
   #define GSM_MC60_AT_CPOL_WRITE "AT+CPOL=I,0,0"  

//5.Read Operator Names
   #define GSM_MC60_AT_COPN_TEST  "AT+COPN=?"      
   #define GSM_MC60_AT_COPN_EXEC  "AT+COPN" 

//6.Get and Set Mobile Operation Band
   #define GSM_MC60_AT_QBANDL_TEST  "AT+QBAND=?"      
   #define GSM_MC60_AT_QBAND_READ  "AT+QBAND?"
   #define GSM_MC60_AT_QBAND_WRITE "AT+QBAND=\"DCS_MODE\"" 

//7.Switch on or off Engineering Mode
   #define GSM_MC60_AT_QENG_TEST  "AT+QENG=?"      
   #define GSM_MC60_AT_QENG_READ  "AT+QENG?"
   #define GSM_MC60_AT_QENG_WRITE "AT+QENG=0,4"

//8.Scan Power of GSM Frequency   
   #define GSM_MC60_AT_QSCANF_TEST  "AT+QSCANF=?"      
   #define GSM_MC60_AT_QSCANF_WRITE "AT+QSCANF=1,9999"   //refer AT+CFUN for detail info

//9.Lock GSM Frequency
   #define GSM_MC60_AT_QLOCKF_TEST  "AT+QLOCKF=?"      
   #define GSM_MC60_AT_QLOCKF_READ  "AT+QLOCKF?"
   #define GSM_MC60_AT_QLOCKF_WRITE "AT+QLOCKF=2,2,1024"

/***GPRS Commands***/
//1. Attach to/Detach from GPRS Service
   #define GSM_MC60_AT_CGATT_TEST  "AT+CGATT=?"      
   #define GSM_MC60_AT_CGATT_READ  "AT+CGATT?"   
   // 1 for Attach and 0 for Dettach to GPRS service
   #define GSM_MC60_AT_CGATT_WRITE "AT+CGATT=1"  
//2.Define PDP Context
   #define GSM_MC60_AT_CGDCONT_TEST  "AT+CGDCONT=?"      
   #define GSM_MC60_AT_CGDCONT_READ  "AT+CGDCONT?"
   //r
   #define GSM_MC60_AT_CGDCONT_WRITE  "AT+CGDCONT=1,\"IP\",\"airteliot.com\""
//3.Quality of Service Profile (Requested)
   #define GSM_MC60_AT_CGQREQ_TEST  "AT+CGQREQ=?"      
   #define GSM_MC60_AT_CGQREQ_READ  "AT+CGQREQ?"
   #define GSM_MC60_AT_CGQREQ_WRITE "AT+CGQREQ=3,0,0,3,0,0"
//4.Quality of Service Profile (Minimum Acceptable)
   #define GSM_MC60_AT_CGQMIN_TEST  "AT+CGQMIN=?"      
   #define GSM_MC60_AT_CGQMIN_READ  "AT+CGQMIN?"
   #define GSM_MC60_AT_CGQMIN_WRITE "AT+CGQMIN=3,0,0,0,0,0"  
//5.PDP Context Activate or Deactivate
   #define GSM_MC60_AT_CGACT_TEST  "AT+CGACT=?"      
   #define GSM_MC60_AT_CGACT_READ  "AT+CGACT?"
   #define GSM_MC60_AT_CGACT_WRITE "AT+CGACT=1,1"
   
#define GSM_MC60_AT_IFC         "AT+IFC=2,2"
#define GSM_MC60_AT_CSQ         "AT+CSQ"
#define GSM_MC60_AT_W           "AT&W"
#define GSM_MC60_AT_CPIN        "AT+CPIN?"
#define GSM_MC60_AT_CGREG       "AT+CGREG?"
#define GSM_MC60_AT_QIMODE      "AT+QIMODE=0"
#define GSM_MC60_AT_QICSGP      "AT+QICSGP=1,\"airteliot.com\""
#define GSM_MC60_AT_QIREGAPP    "AT+QIREGAPP=\"airteliot.com\",\"pavan\",\"123456789\""
#define GSM_MC60_AT_QICSGP_M      "AT+QICSGP?"
#define GSM_MC60_AT_CGDCONT     "AT+CGDCONT=1,\"IP\",\"airteliot.com\""
#define GSM_MC60_AT_CGPADDR     "AT+CGPADDR=1"
#define GSM_MC60_AT_IMEI_CMD    "AT+CGSN"
#define GSM_MC60_AT_CGACT      "AT_CGACT=1,1"
#define GSM_MC60_AT_QILOCIP     "AT+QILOCIP"
#define GSM_MC60_AT_ATV1        "ATV1"
#define GSM_MC60_AT_QIHEAD      "AT+QIHEAD=1"
#define GSM_MC60_AT_QIMUX       "AT+QIMUX=0"
#define GSM_MC60_AT_QIDNSIP     "AT+QIDNSIP=0"
#define GSM_MC60_AT_QISRVC      "AT+QISRVC=1"
#define GSM_MC60_AT_TCP_CONNECT "AT+QIOPEN=\"TCP\",\"85.119.83.194\",1883"


#endif __DEFINES_HPP_
