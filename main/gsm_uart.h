#ifndef __GSM_UART_H
#define __GSM_UART_H




void init_gsm_uart();
void gsm_send_cmd(const char*);
void gsm_read_response(char *);
bool gsm_extract_value_from_response(char *,int,int) ;
static uint64_t millis();
int gsm_read_line(char *buffer, int max_len, int timeout_ms);

#endif // __GSM_UART_H