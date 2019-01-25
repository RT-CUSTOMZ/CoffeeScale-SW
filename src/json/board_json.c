#include <string.h>
#include <stdint.h>
#include "json_state.h"

static const char* board_get_json(void* user)
{
    return "{ board: \"Led-Cube\" }";
}

json_state_t board_json_state = {
  .get_json = board_get_json,
  .set_json = NULL,
  .user = NULL,
};
