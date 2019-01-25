/* C code produced by gperf version 3.0.4 */
/* Command-line: /usr/bin/gperf --output-file=/home/sguelland/testWorkspace/bootloader_build/mine_type_lookup.c mine_type_lookup.gperf  */
/* Computed positions: -k'' */

#line 1 "mine_type_lookup.gperf"

#include <stdint.h>
#include "mine_type_lookup.h"

const char* Mine_Type_Lookup(const char * filename)
{

};
#line 19 "mine_type_lookup.gperf"
struct MineType;
#include <string.h>

#define TOTAL_KEYWORDS 3
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 4
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 4
/* maximum key range = 3, duplicates = 0 */

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
     register unsigned int len;
{
  return len;
}

static const struct MineType wordlist[] =
  {
#line 23 "mine_type_lookup.gperf"
    {"js", "text/html"},
#line 21 "mine_type_lookup.gperf"
    {"css", "text/css"},
#line 22 "mine_type_lookup.gperf"
    {"html", "text/html"}
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct MineType *
mineTypeLookup (str, len)
     register const char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register const struct MineType *resword;

          switch (key - 2)
            {
              case 0:
                resword = &wordlist[0];
                goto compare;
              case 1:
                resword = &wordlist[1];
                goto compare;
              case 2:
                resword = &wordlist[2];
                goto compare;
            }
          return 0;
        compare:
          {
            register const char *s = resword->extension;

            if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
              return resword;
          }
        }
    }
  return 0;
}
