/* C code produced by gperf version 3.1 */
/* Command-line: gperf -L C --output-file=http_path_lookup.c http_path_lookup.gperf  */
/* Computed positions: -k'' */

#line 1 "http_path_lookup.gperf"

#include <stdint.h>
#include "http_server.h"
#include "http_path_lookup.h"
#include "static_web_files.h"
#include "json_state.h"

void transmit_wifi_connect(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_wifi_reset(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_wifi_status(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_wifi_ipInfo(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void http_wifi_aplist(HttpReqeuest* httpReqeuest, const char *at, size_t length);


void transmit_json(HttpReqeuest* httpReqeuest, const char *at, size_t length);
extern json_state_t artnet_json_state;
extern json_state_t board_json_state;
extern json_state_t ip_json_state;
extern json_state_t wifi_json_state;
extern json_state_t cube_cmd_json_state;

extern HttpFile fileIndexHtml;
extern HttpFile fileArtnetHtml;
void transmit_file(HttpReqeuest* httpReqeuest, const char *at, size_t length);

#line 36 "http_path_lookup.gperf"
struct HttpPathLookup;
#include <string.h>

#define TOTAL_KEYWORDS 5
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 11
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 11
/* maximum key range = 11, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
/*ARGSUSED*/
static unsigned int
hash (str, len)
     register const char *str;
     register size_t len;
{
  return len;
}

static const struct HttpPathLookup wordlist[] =
  {
#line 38 "http_path_lookup.gperf"
    {"/", transmit_file, (void*) &fileIndexHtml},
#line 41 "http_path_lookup.gperf"
    {"/ip", transmit_json, &ip_json_state},
#line 42 "http_path_lookup.gperf"
    {"/wifi", transmit_json, &wifi_json_state},
#line 40 "http_path_lookup.gperf"
    {"/board", transmit_json, &board_json_state},
#line 39 "http_path_lookup.gperf"
    {"/index.html", transmit_file, (void*) &fileIndexHtml}
  };

const struct HttpPathLookup *
http_path_lookup (str, len)
     register const char *str;
     register size_t len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register const struct HttpPathLookup *resword;

          switch (key - 1)
            {
              case 0:
                resword = &wordlist[0];
                goto compare;
              case 2:
                resword = &wordlist[1];
                goto compare;
              case 4:
                resword = &wordlist[2];
                goto compare;
              case 5:
                resword = &wordlist[3];
                goto compare;
              case 10:
                resword = &wordlist[4];
                goto compare;
            }
          return 0;
        compare:
          {
            register const char *s = resword->path;

            if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
              return resword;
          }
        }
    }
  return 0;
}
