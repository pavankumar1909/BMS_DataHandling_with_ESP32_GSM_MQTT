#ifndef __GSM_UART_H
#define __GSM_UART_H



#define GSM_UART_NUM UART_NUM_1
#define BUF_SIZE 1024

#define GSM_TXD_PIN (17)
#define GSM_RXD_PIN (16)
#define BAUDRATE_115200 115200

void init_gsm_uart();
void gsm_send_cmd(const char*);
void gsm_read_response();
void gsm_send_cmd(const char*);


#endif // __GSM_UART_H