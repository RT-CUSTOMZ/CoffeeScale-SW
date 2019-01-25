#include "ets_sys.h"
#include "osapi.h"

 #include <lwip/ip_addr.h>

#include "user_interface.h"

#include "espconn.h"

// Abruf mit:
// avahi-browse _iot._tcp -rvc

static struct mdns_info info;
ICACHE_FLASH_ATTR
void user_mdns_config()
{
    static char host_name[20];
    
    uint8_t mac[6];
    wifi_get_macaddr(STATION_IF,mac);

    os_sprintf(host_name,"coffee-scale-%02x%02x%02x",mac[3],mac[4],mac[5]);

	wifi_set_broadcast_if(STATIONAP_MODE);
	struct ip_info ipconfig;

	wifi_get_ip_info(STATION_IF, &ipconfig);
	info.host_name = host_name;
	info.ipAddr = ipconfig.ip.addr; //ESP8266 station IP
	info.server_name = "iot";
	info.server_port = 80;
	info.txt_data[0] = "type=coffee-scale";
	info.txt_data[1] = "";
	info.txt_data[2] = "";
	espconn_mdns_init(&info);
}