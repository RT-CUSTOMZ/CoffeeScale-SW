#ifndef __SNTP_H__
#define __SNTP_H__

#include "ets_sys.h"

//void set_system_time(uint32_t  timestamp);

//#define SNTP_SERVER_DNS 1
//#define SNTP_SERVER_ADDRESS         "pool.ntp.org"
#define SNTP_SERVER_ADDRESS         "144.76.115.197"

//#define SNTP_STARTUP_DELAY          8000
#define SNTP_SET_SYSTEM_TIME(sec) (set_system_time(sec))

void sntp_init(void);

#endif /* __SNTP_H__ */
