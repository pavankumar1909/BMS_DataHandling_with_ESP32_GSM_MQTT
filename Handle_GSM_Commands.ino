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

/*
         
  sendATCommand("AT+CMGF=?");    
  delay(1000);
  sendATCommand("AT+CMGF?");    
  delay(1000);
  sendATCommand("AT+CREG?");    
  delay(1000);
  sendATCommand("AT+CMGF=1");    
  delay(1000);
  sendATCommand("AT+CMGS=\"+918638235546\"");    
  delay(1000);
  sendATCommand("AT+CMGF=1");    
  delay(2000);
  sendATCommand("This is my SMS message");*/
  
    sendATCommand("AT+GSN");
    delay(100);
    
    sendATCommand("AT+QIACT");
    delay(100);
    
    sendATCommand(AT_CSQ);
    delay(200);

    sendATCommand(AT_CGACT);
    delay(2000);

    sendATCommand(AT_CGPADDR);
    delay(2000);
 }
}
