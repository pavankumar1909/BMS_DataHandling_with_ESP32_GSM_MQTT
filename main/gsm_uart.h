#ifndef __GSM_UART_H
#define __GSM_UART_H




void init_gsm_uart();
void gsm_send_cmd(const char*);
void gsm_read_response();
void gsm_imei_response(char *,const char*,int);



#endif // __GSM_UART_H