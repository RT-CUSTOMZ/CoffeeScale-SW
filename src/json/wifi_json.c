#include "lwipopts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"


#include "user_interface.h"

#include "artnet/artnet.h"
#include "config.h"
#include "json_state.h"

#include "jsmn.h"

 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

 #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

static const char* wifi_get_json(void* user);
static bool wifi_set_json(const char* json, uint32_t len, void* user);

json_state_t wifi_json_state = {
  .get_json = wifi_get_json,
  .set_json = wifi_set_json,
  .user = NULL,
};

static const char* ICACHE_FLASH_ATTR
wifi_get_json(void* user)
{
  struct station_config config;

  wifi_station_get_config(&config);

  static char buffer[100];
  os_sprintf(buffer, "{ \"ssid\" : \"%s\"}", config.ssid);
  os_printf("%s\n",buffer);
	return &(buffer[0]);
}


static bool ICACHE_FLASH_ATTR
wifi_set_json(const char* json, uint32_t len, void* user)
{
  struct station_config config;
  memset(&config, 0, sizeof(config));

  jsmn_parser p;
	jsmntok_t token[10];

	jsmn_init(&p);

  uint32_t jsmn_result = jsmn_parse(
    &p, 
    json, 
    len, 
    (jsmntok_t*) &token, 
    sizeof(token)/sizeof(token[0]
    ));

  if(jsmn_result < 0)
    return false;

  os_printf("Json: %s\n", json);
  os_printf("Json count: %d\n", jsmn_result);

  for(uint32_t i = 0; i < jsmn_result; i++) {
    if( (JSMN_PRIMITIVE == token[i].type) || (JSMN_STRING == token[i].type) ) {
      if( 0 == strncmp("ssid", json + token[i].start, token[i].end - token[i].start)) {
        i++;
        if(! (i < jsmn_result) )
          return false;
        if(JSMN_STRING == token[i].type) {
          uint32_t len = min(
            sizeof(config.ssid), 
            token[i].end - token[i].start
            );
          strncpy(
            (char*)       config.ssid,
            (const char*) json + token[i].start,
            len
            );
        }
      }
      else if( 0 == strncmp("password", json + token[i].start, token[i].end - token[i].start)) {
        i++;
        if(! (i < jsmn_result) )
          return false;
        if(JSMN_STRING == token[i].type) {
          uint32_t len = min(
            sizeof(config.password), 
            token[i].end - token[i].start
            );
          strncpy(
            (char*)       config.password,
            (const char*) json + token[i].start,
            len
            );
        }
      }
    }
  }

  wifi_set_opmode_current(STATIONAP_MODE);
  wifi_station_set_config(&config);
  wifi_station_set_auto_connect(1);
  wifi_station_connect();
	return true;
}
