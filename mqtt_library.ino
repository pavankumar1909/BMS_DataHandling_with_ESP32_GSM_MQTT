#include"mqtt_library.hpp"

bool mqtt_connect(const char *client_id,const char *username,const char *password)
{
    int client_id_length= strlen(client_id);
    int username_length = strlen(username);
    int password_length = strlen(password);
    int RL = 10 ;    //len =10 is fixed
    RL+= client_id_length + 2;      //client_id _ength+2 bytes for fixing client_id_length
    RL+= username_length  + 2;      //username_length +2 bytes for fixing username_length
    RL+= password_length  + 2;      //password_length +2 bytes for fixing password_length
    int total_packet_length = RL+2;
    char buffer[total_packet_length];     //buffer to store connect packet data
    char Fixed_header[]={
                            0x10,                   // protocol type
                            RL,                     //Remaining_length (length of control packet excluding 0x10 & RL)
                            0x00,0x04,              // protocol length   [depends protocol type length varies]
                            'M','Q','T','T',        //protocol type
                            0x04,                   //protocol level (represents protocol version)
                            0xC2,                   //connection_flag
                            0x00,0x2C               //keep alive for 60 seconds
                        };
    int buffer_index=0; 
    //for storing fixed_header into buffer
    while(buffer_index<sizeof(Fixed_header))
    {
       buffer[buffer_index]=Fixed_header[buffer_index];
       buffer_index++;
    }
    
    //for storing client_id into buffer
    buffer[buffer_index++]=0x00;
    buffer[buffer_index++]= client_id_length;
    
    for(int j=0;client_id_length!=0;)
    {
      buffer[buffer_index++]=client_id[j++];
      client_id_length--;
    }
    
    //for storing username into buffer
    buffer[buffer_index++]=0x00;
    buffer[buffer_index++]=username_length;
    for(int j=0;username_length!=0;)
    {
     buffer[buffer_index++]=username[j++];
     username_length--;    
    }
    
    //for storing password into buffer
    buffer[buffer_index++]=0x00;
    buffer[buffer_index++]=password_length;
    for(int j=0;password_length!=0;)
    {
     buffer[buffer_index++]=password[j++];
     password_length--;
    }                    
    for(int i=0;i<sizeof(buffer);i++)
    {
      Serial.print(buffer[i]);                    
    }
    Serial.println();

     
    Serial.println("Sending MQTT connect..");

    GSM.println("AT+QISEND\r\n");
    delay(1000);
    // Send MQTT CONNECT packet over TCP
    GSM.write(buffer,sizeof(buffer));
    GSM.write(0x1A); // Ctrl+Z to end
    delay(1000);

     // Optional: Wait for server response
    while(GSM.available()) 
    {
    Serial.write(GSM.read());
    }
    
    return 1;
}

bool mqtt_connect(const char *client_id)
{
    int client_id_length= strlen(client_id);
    int RL = 10 ;    //len =10 is fixed
    RL+= client_id_length + 2;      //client_id _ength+2 bytes for fixing client_id_length
    int total_packet_length = RL+2;
    char buffer[total_packet_length];     //buffer to store connect packet data
    char Fixed_header[]={
                            0x10,                   // protocol type
                            RL,                     //Remaining_length (length of control packet excluding 0x10 & RL)
                            0x00,0x04,              // protocol length   [depends protocol type length varies]
                            'M','Q','T','T',        //protocol type
                            0x04,                   //protocol level (represents protocol version)
                            0xC2,                   //connection_flag
                            0x00,0xfC               //keep alive for _ _ seconds
                        };
    int buffer_index=0; 
    
    //for storing fixed_header into buffer
    while(buffer_index<sizeof(Fixed_header)/sizeof(char))
    {
       buffer[buffer_index]=Fixed_header[buffer_index];
       buffer_index++;
    }
    
    //for storing client_id into buffer
    buffer[buffer_index++]=0x00;
    buffer[buffer_index++]= client_id_length;
    
    for(int j=0;client_id_length!=0;)
    {
      buffer[buffer_index++]=client_id[j++];
      client_id_length--;
    }
//     
//    for(int i=0;i<sizeof(buffer);i++)
//    {
//      Serial.print(buffer[i]);                    
//    }
//    Serial.println();
//    for(int i=0;i<sizeof(buffer);i++)
//    {
//      Serial.print(i);
//      Serial.print(":");
//      Serial.print(buffer[i],HEX);  
//      Serial.print(", ");                  
//    }
//    Serial.println();
//    delay(500);
    
    Serial.println("Sending MQTT connect..");

    GSM.println("AT+QISEND\r\n");
    delay(1000);
    // Send MQTT CONNECT packet over TCP
    GSM.write(buffer,sizeof(buffer));
    GSM.write(0x1A); // Ctrl+Z to end
    delay(1000);

     // Optional: Wait for server response
    while(GSM.available()) 
    {
    Serial.write(GSM.read());
    }

    return 1;
}

void send_subcribe_packet(const char *topic_name)
{
  int topic_name_length = strlen(topic_name);
  int RL = 5 + topic_name_length;  
      
  int total_packet_length= RL +2;   //2 for fixed header

  char buffer[total_packet_length];
    
  int i=0;
  buffer[i++] = 0x82;
  buffer[i++] = RL ;
  buffer[i++] = 0x00;
  buffer[i++] = 0x0a;
  buffer[i++] = 0x00;
  buffer[i++] = topic_name_length;
  int j=0;
  while(topic_name_length!=0)
  {
     buffer[i++]= topic_name[j];
     j++;
     topic_name_length--;
  }
  buffer[i]=0x01;
   Serial.println("Sending MQTT SUBSCRIBE..");

    GSM.println("AT+QISEND\r\n");
    delay(1000);
    // Send MQTT CONNECT packet over TCP
    GSM.write(buffer,sizeof(buffer));
    GSM.write(0x1A); // Ctrl+Z to end
    delay(1000);

    // Optional: Wait for server response
    while(GSM.available()) 
    {
    Serial.write(GSM.read());
    }

}

void send_publish_packet(const char *topic_name,const char *message)
{
    
    int topic_name_length = strlen(topic_name);
    Serial.print("top_len");
    Serial.println(topic_name_length);
    int message_length    = strlen(message);
    Serial.print("msg_len: ");
    Serial.println(message_length);
    int RL = 2 + topic_name_length + message_length;  // 2 fixed for control packet type and RL
      
    int total_packet_length= RL +2;   //2 for fixed header

    unsigned char buffer[total_packet_length]; 
    unsigned char Fixed_header[]={
                           0x30,    //control packet type
                           RL      //Remaining length of packet    
                        };

     int buffer_index=0;
  
     //storing Fixed header into buffer  
     while(buffer_index<sizeof(Fixed_header)/sizeof(unsigned char))
     {
       buffer[buffer_index]=Fixed_header[buffer_index];
       buffer_index++;
     }
  
     //storing topic name into buffer
     buffer[buffer_index++] = 0x00;
     buffer[buffer_index++] = topic_name_length;
     for(int j=0;topic_name_length!=0;)
     {
      buffer[buffer_index++]=topic_name[j++];
      topic_name_length--;    
     }
 
     for(int j=0;message_length!=0;)
     {
      buffer[buffer_index++]=message[j++];
       message_length--;   
     }
     buffer[buffer_index++]=0;
     buffer[buffer_index++]=0x10;
     
     Serial.println("Sending MQTT PUBLISH..");

     GSM.println("AT+QISEND\r\n");
     delay(1000);
     // Send MQTT CONNECT packet over TCP
     GSM.write(buffer,sizeof(buffer));
     GSM.write(0x1A); // Ctrl+Z to end
     delay(1000);

     // Optional: Wait for server response
    while(GSM.available()) 
    {
    Serial.write(GSM.read());
    }

  

}
