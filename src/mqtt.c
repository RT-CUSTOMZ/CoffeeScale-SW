#include "lwip/apps/mqtt.h"
#include "mqtt/mqtt.h"
#include "stdio.h"

#include "driver/uart.h"

#include "http11/http11_parser.h"
#include "http_server.h"
#include "json_state.h"
#include "http_path_lookup.h"

extern json_state_t ip_json_state;

static mqtt_client_t * mqtt_client;

static MQTT_config* config;

void static mqtt_connect(void);

static void mqtt_request_cb(void *arg, err_t err)
{

}

static json_state_t * json_state;

static void ICACHE_FLASH_ATTR
mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
	err_t err;
	char buffer[100];

	switch (status) {
	case MQTT_CONNECT_ACCEPTED:
		// snprintf(buffer, sizeof(buffer),"blup %s", "bla");
		err = mqtt_publish(
			mqtt_client,
			config->will_topic,
			"online",
			6,      // strlen("online")
			0,      //qos
			1,      // retain
			mqtt_request_cb,
			NULL);

		char topic[100];
		os_sprintf(topic, "%s/%s/ip",
			config->base_topic,
			config->conn_id);

		const char *json_string = ip_json_state.get_json(NULL);

		err = mqtt_publish(
			mqtt_client,
			topic,
			json_string,
			strlen(json_string),
			0,      //qos
			1,      // retain
			mqtt_request_cb,
			NULL);
		break;

	case MQTT_CONNECT_DISCONNECTED:
	case MQTT_CONNECT_TIMEOUT:
		mqtt_connect();
		break;

	default:
		break;
	}

}

static void ICACHE_FLASH_ATTR
mqtt_dns_lookup_cb(const char *name, struct ip_addr *ipaddr, void *arg)
{
	struct mqtt_connect_client_info_t mqtt_connect_client_info = {
		.client_id	= config->conn_id,
		.client_user	= config->user,
		.client_pass	= config->password,
		.keep_alive	= 60,
		.will_topic	= config->will_topic,
		.will_msg	= "offline",
		.will_qos	= 0,
		.will_retain	= 1,
	};

	err_t err;

	if ((ipaddr) && (ipaddr->addr)) {
		err = mqtt_client_connect(
			mqtt_client,
			ipaddr,
			MQTT_PORT,
			mqtt_connection_cb,
			NULL,
			&mqtt_connect_client_info);
	}else{

	}
}

void static mqtt_connect(void)
{
	err_t err;

	struct ip_addr host;

	// IP4_ADDR(&host, 192, 168, 123, 62);

	err = dns_gethostbyname(
		config->uri,
		&host,
		mqtt_dns_lookup_cb,
		mqtt_client);

	switch (err) {
	case ERR_OK:
		// numeric or cached, returned in resolved
		mqtt_dns_lookup_cb(config->uri, &host, mqtt_client);
		break;
	case ERR_INPROGRESS:
		// need to ask, will return data via callback
		break;
	default:
		// bad arguments in function call
		break;
	}
}

void mqtt_init(MQTT_config *new_config)
{
	mqtt_client = mqtt_client_new();
	config = new_config;

	mqtt_connect();
}

void MQTT_publish(mqtt_client_t *client, const char* subtopic, char* data, uint32_t data_len) {
	(void) client; //not used at the moment

	if(0 == mqtt_client_is_connected(mqtt_client) )
		return;

	err_t err;
	char topic[100];

	os_sprintf(topic, "%s/%s/%s",
		config->base_topic,
		config->conn_id,
		subtopic);

	err = mqtt_publish(
		mqtt_client,
		topic,
		data,
		data_len,
		0,      //qos
		0,      // retain
		mqtt_request_cb,
		NULL);
}