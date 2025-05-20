void sendATCommand(String cmd)
{
  GSM.println(cmd);
}


void setup_sim(bool check)
{
  bool success = false;
  int i=0;
  if(check)
  {

     sendATCommand(AT_CSQ);
     delay(100); 
     /*to query the SIM status and network registration status*/
     sendATCommand(AT_CPIN);
     delay(100);
     sendATCommand(AT_CGREG);
     delay(500); 

     /*select TCPIP Stack mode*/
     sendATCommand(AT_QIMODE);
     delay(500); 
     
     /*set APN*/
     sendATCommand(AT_QICSGP);
     delay(500); 
     
     /* Start TCPIP task*/
     sendATCommand(AT_QIREGAPP);
     delay(500);

     /*Check the current connecting mode*/
     sendATCommand(AT_QICSGP);
     delay(500);

     /* The current connecting mode is GPRS connecting mode */
     /*Activate GPRS context*/
     sendATCommand(AT_QIACT);
     delay(500);

     /* Get the local IP address */
     sendATCommand(AT_QILOCIP);
     delay(500);

     /* Use ATV1 to set the response format */
     sendATCommand(AT_ATV1);
     delay(500);

     /* Use AT+QIHEAD=1 to add the header information when receive data */
     sendATCommand(AT_QIHEAD);
     delay(500);

     sendATCommand(AT_QIMUX);
     delay(500);

     /* Use AT+QIDNSIP=0 to use the IP address to establish TCP/UDP session, while AT+QIDNSIP=1 is use the domain name to establish TCP/UDP session */
     sendATCommand(AT_QIDNSIP);
     delay(500);

      sendATCommand(AT_TCP_CONNECT);
     delay(500);
     
  }
}
