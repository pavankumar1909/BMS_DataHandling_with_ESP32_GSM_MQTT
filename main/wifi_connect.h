#ifndef __WIFI_CONNECT_H__
#define __WIFI_CONNECT_H__


static void wifi_event_handler(void *,esp_event_base_t,int32_t, void *) ;
void wifi_connect();
void wifi_init_sta();


#endif // __WIFI_CONNECT_H__