#ifndef __Handle_GSM_Commands_HPP_
#define __Handle_GSM_Commands_HPP_


void gsm_setup_sim(bool);
void gsm_send_at_command(String);
bool gsm_extract_value_from_response(char *, int, int);
int gsm_read_line(char *, int, int );

HardwareSerial GSM(1); // Use UART1

#endif //Handle_GSM_Commands
