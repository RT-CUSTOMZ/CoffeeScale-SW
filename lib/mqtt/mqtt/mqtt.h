#ifndef MQTT_H
#define MQTT_H
//#include "stdint.h"
#include "os_type.h"

typedef struct {
	bool enabled;
	char *uri;
	char *user;
	char *password;
	char *conn_id;
	char *base_topic;
	char *will_topic;
} MQTT_config;

void mqtt_init(MQTT_config *new_config);

void mqtt_button(const char* message, void* user);
// void mqtt_set_config(MQTT_config *config);
// MQTT_config * mqtt_get_config(void);


#endif /* MQTT_H */
