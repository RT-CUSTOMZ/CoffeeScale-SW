//#include <stdint.h>
#include <string.h>

#define ShortNameLength 18
#define FLASH_VERSION_CHECKER 0xDEADBEAA
//0xDEADBEEF

#include "ets_sys.h"
#include "user_esp_platform.h"
#include "artnet/artnet.h"

typedef struct {
	bool enabled;
	uint16_t universe;
	uint16_t offset;
	char nodeName[ShortNameLength];
} config_artnet_t;

typedef struct {
	uint32_t initial_config;
	config_artnet_t artnet;
} config_t;

void
config_save(void)
{
	static config_t config;

	config.initial_config = FLASH_VERSION_CHECKER;

	ARTNET_config* artnet = ARTNET_get_config();
	config.artnet.enabled = artnet->enabled;
	config.artnet.offset = artnet->offset;
	config.artnet.universe = artnet->universe;
	strncpy( &(config.artnet.nodeName[0]),
		 artnet->nodeName,
		 sizeof(config.artnet.nodeName));
	config.artnet.nodeName[sizeof(config.artnet.nodeName) - 1] = '\0';

	system_param_save_with_protect(ESP_PARAM_START_SEC, &config, sizeof(config));
}

bool
config_load(void)
{
	static config_t config;

	system_param_load(ESP_PARAM_START_SEC, 0, &config, sizeof(config));

	if (config.initial_config != FLASH_VERSION_CHECKER)
		return false;

	static char artnet_name[ShortNameLength];
	artnet_name[0] = '\0';

	ARTNET_config* artnet = ARTNET_get_config();
	artnet->enabled = config.artnet.enabled;
	artnet->offset = config.artnet.offset;
	artnet->universe = config.artnet.universe;


	strncpy(artnet_name, config.artnet.nodeName, sizeof(artnet_name));
	artnet->nodeName = artnet_name;
	ARTNET_set_config(artnet);
}
