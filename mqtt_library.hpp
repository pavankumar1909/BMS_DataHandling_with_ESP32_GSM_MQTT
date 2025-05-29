#ifndef __MQTT_LIBRARY_HPP__
#define __MQTT_LIBRARY_HPP__

bool mqtt_connect(char *,char *,char*,char*);
bool mqtt_connect(char *);
void send_publish_packet(const char *topic_name,const char *message);

#endif __MQTT_LIBRARY_HPP__
