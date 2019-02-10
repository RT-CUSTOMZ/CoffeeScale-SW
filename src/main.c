/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/1/1, v1.0 create this file.
 *******************************************************************************/
#include "ets_sys.h"
#include "osapi.h"

 #include <lwip/ip_addr.h>

#include "user_interface.h"

#include "artnet/artnet.h"
#include "driver/uart.h"

#include "echo.h"
#include "sntp.h"
#include "config.h"

//mdns
#include "espconn.h"

#include "serial.h"

#include <mqtt/mqtt.h>

MQTT_config mqtt_config = {
  .enabled = true,
  .uri = "mqtt.fh.guelland.eu",
  .user = NULL,
  .password = NULL,
  .base_topic = "coffee_scale",
};

//wifi led


static void wifi_led_init(void) {
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,FUNC_GPIO14);
	gpio_output_set(0, BIT14, BIT14, 0);  // 5 low
}

static void wifi_led_connected(void) {
	gpio_output_set(BIT14, 0, BIT14, 0);  // 14 high led off
}

static void wifi_led_disconnected(void) {
	gpio_output_set(0, BIT14, BIT14, 0);   // 14 low led on
}

//

#include "HX711.h"

static void new_value_callback(int value, void *obj) {
	os_printf("HX711 value: %d\n", (value - 7200000) / 256);

	static char *json_buff[100];
	os_sprintf(json_buff, "{ \"rawValue\": %d }", value);
	MQTT_publish(obj, "value", json_buff, strlen(json_buff) );
}

HX711 hx711 = {
	.new_value_callback = new_value_callback,
	.new_value_callback_obj = NULL,
};

static void ICACHE_FLASH_ATTR
wifi_checker(uint8 reset_flag)
{
	enum dhcp_status status = (enum dhcp_status)wifi_station_get_connect_status();

	switch (status) {
	case STATION_IDLE:
	case STATION_CONNECTING:
	case STATION_GOT_IP:
		wifi_set_opmode_current(STATION_MODE);
		break;

	case STATION_WRONG_PASSWORD:
	case STATION_NO_AP_FOUND:
	case STATION_CONNECT_FAIL:
		wifi_set_opmode_current(STATIONAP_MODE);
		break;
	}
}

static void wifi_checker_init()
{

	static os_timer_t client_timer;

	os_timer_disarm(&client_timer);
	os_timer_setfn(&client_timer, (os_timer_func_t*)wifi_checker, NULL);
	os_timer_arm(&client_timer, 1000, 1);
}

////////////////////////////////////////////////////////////////////////////////

static uint16_t wifi_timeout = 0;

void ICACHE_FLASH_ATTR
wifi_handle_event_cb(System_Event_t *evt)
{
	os_printf("event %x\n", evt->event);
	switch (evt->event) {
	case EVENT_STAMODE_CONNECTED:
		os_printf("connect to ssid %s, channel %d\n",
			  evt->event_info.connected.ssid,
			  evt->event_info.connected.channel);
		break;
	case EVENT_STAMODE_DISCONNECTED:
		os_printf("disconnect from ssid %s, reason %d\n",
			  evt->event_info.disconnected.ssid,
			  evt->event_info.disconnected.reason);
			  wifi_led_disconnected();
		wifi_set_opmode_current(STATIONAP_MODE);
		break;
	case EVENT_STAMODE_AUTHMODE_CHANGE:
		os_printf("mode: %d -> %d\n",
			  evt->event_info.auth_change.old_mode,
			  evt->event_info.auth_change.new_mode);
		break;
	case EVENT_STAMODE_GOT_IP:
		os_printf("ip:" IPSTR ",mask:" IPSTR ",gw:" IPSTR,
			  IP2STR(&evt->event_info.got_ip.ip),
			  IP2STR(&evt->event_info.got_ip.mask),
			  IP2STR(&evt->event_info.got_ip.gw));
		os_printf("\n");
		wifi_set_opmode_current(STATION_MODE);
    {
      static char client_id[20];
      uint8_t mac[6];
      wifi_get_macaddr(STATION_IF,mac);

      os_sprintf(client_id,"ESP-%02x:%02x:%02x",mac[3],mac[4],mac[5]);
      mqtt_config.conn_id = client_id;

      static char will_topic[100];
      os_sprintf(will_topic, "%s/%s/status",
        mqtt_config.base_topic,
        mqtt_config.conn_id);
      mqtt_config.will_topic = will_topic;

		wifi_led_connected();
      mqtt_init(&mqtt_config);
		HX711_init(&hx711);
    }
		user_mdns_config();
		break;
	case EVENT_SOFTAPMODE_STACONNECTED:
		os_printf("station: " MACSTR "join, AID = %d\n",
			  MAC2STR(evt->event_info.sta_connected.mac),
			  evt->event_info.sta_connected.aid);
		break;
	case EVENT_SOFTAPMODE_STADISCONNECTED:
		os_printf("station: " MACSTR "leave, AID = %d\n",
			  MAC2STR(evt->event_info.sta_disconnected.mac),
			  evt->event_info.sta_disconnected.aid);
		break;
	case EVENT_SOFTAPMODE_PROBEREQRECVED:

		break;
	default:
		break;
	}
}

extern void http_server_init(void);
extern void uart_server_server_init(void);


static inline ICACHE_FLASH_ATTR void wifi_init(const char * ap_mode_ssid)
{
	static struct softap_config config;

	if(strlen(ap_mode_ssid) > sizeof(config.ssid)){
		//report error
		return;
	}

	memset(&config, 0, sizeof(config));
	// os_sprintf(config.ssid, "LED Cube");
	strncpy(config.ssid, ap_mode_ssid, sizeof(config.ssid) );
	config.ssid_len = strlen(ap_mode_ssid);
	config.channel = 1;
	config.authmode = AUTH_OPEN;
	config.max_connection = 4;
	config.beacon_interval = 100;
	wifi_softap_set_config_current(&config);

	struct ip_info info;
	wifi_softap_dhcps_stop();
	IP4_ADDR(&info.ip, 10, 42, 23, 1);
	IP4_ADDR(&info.gw, 10, 42, 23, 1);
	IP4_ADDR(&info.netmask, 255, 255, 255, 0);
	wifi_set_ip_info(SOFTAP_IF, &info);

	struct dhcps_lease dhcp_lease;
	const char* start_ip = "10.42.23.100";
	const char* end_ip = "10.42.23.105";
	dhcp_lease.start_ip.addr = ipaddr_addr(start_ip);
	dhcp_lease.end_ip.addr = ipaddr_addr(end_ip);
	wifi_softap_set_dhcps_lease(&dhcp_lease);

	wifi_softap_dhcps_start();

	wifi_set_event_handler_cb(wifi_handle_event_cb);

	wifi_set_sleep_type(NONE_SLEEP_T);


	wifi_set_opmode_current(STATIONAP_MODE);
}

static uint32_t transmittCallback(uint8_t ** dataPtr, void * userptr)
{
  return 0;
}

void button_init(void);

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR user_init(void)
{
	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	//system_set_os_print(0);
	os_printf("SDK version:%s\n", system_get_sdk_version());

	wifi_led_init();

  	wifi_init("coffee_scale");

	http_server_init();

  	config_load();

  	button_init();
}
