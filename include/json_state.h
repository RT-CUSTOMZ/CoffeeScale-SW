#ifndef JSON_STATE_H
#define JSON_STATE_H
#include <stdbool.h>
#include <stdint.h>

typedef const char* (*get_json_t)(void* user);
typedef void (*callback_json_t)(const char* json, void* user);
typedef bool (*set_json_t)(const char* json, uint32_t len, void* user);


typedef struct json_state_s {
  get_json_t get_json;
  set_json_t set_json;
  void* user;
} json_state_t;

#endif //JSON_STATE_H