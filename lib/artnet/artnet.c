/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_devicefind.c
 *
 * Description: Find your hardware's information while working any mode.
 *
 * Modification history:
 *     2014/3/12, v1.0 create this file.
 *******************************************************************************/
//lwip INCLUDES
#include "lwipopts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/udp.h"

#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
//#include "mem.h"
#include "user_interface.h"

#include "espconn.h"

#include "artnet/artnet.h"

#define min(a, b) \
	({ __typeof__(a)_a = (a); \
	   __typeof__(b)_b = (b); \
	   _a < _b ? _a : _b; })

static ARTNET_config config = {
	.enabled = true,
	.nodeName	= "Default Artnet Node",
	.universe	= 0,
	.offset		= 0,
};

LOCAL struct espconn ptrespconn;

static struct udp_pcb *artnet_pcb;

static struct pbuf *pbuf_pollReply;

#include "artnet/artnet.h"
#define AnsiString char //quick fix
#include "Art-Net.h"

typedef struct S_ArtHeader {
	uint8_t id[8];
	uint16_t opCode;
} T_ArtHeader;

//
// static T_ArtPollReply pollReply;

static ARTNET_callbacks* artnet_callbacks;

static void handlePollDatagram(
	ARTNET_callbacks* callbacks,
	struct udp_pcb * upcb,
	struct pbuf * p,
	struct ip_addr * addr,
	u16_t port)
{
	const T_ArtPoll* packet = (const T_ArtPoll*)p->payload;

	if (p->len < sizeof(T_ArtPoll))
		return;

	pbuf_pollReply = (struct pbuf *)pbuf_alloc(PBUF_TRANSPORT, sizeof(T_ArtPollReply), PBUF_POOL);
	T_ArtPollReply* pollReply = (T_ArtPollReply*)(pbuf_pollReply->payload);

	memset(pollReply, 0, sizeof(pollReply));
	strcpy((char*)pollReply->ID, "Art-Net");
	pollReply->OpCode = OpPollReply;
	pollReply->BoxAddr.Port = DefaultPort;
	strncpy((char*)&(pollReply->ShortName), config.nodeName, ShortNameLength);
	strncpy((char*)&(pollReply->LongName), config.nodeName, LongNameLength);
	pollReply->NumPortsLo = 1;
	pollReply->PortTypes[0] = (1 << 7);
	pollReply->NetSwitch = (config.universe >> 8) & 0x7f;
	pollReply->SubSwitch = (config.universe >> 4) & 0x0f;
	pollReply->SwOut[0] = config.universe & 0x0f;
	wifi_get_macaddr(STATION_IF, pollReply->Mac);
	pbuf_pollReply->len = sizeof(T_ArtPollReply);

	//T_ArtPollReply* pollReply = (T_ArtPollReply*)pbuf_pollReply->payload);
	struct ip_info info;
	wifi_get_ip_info(STATION_IF, &info);
	memcpy(pollReply->BoxAddr.IP, &(info.ip), 4);

	udp_sendto(upcb, pbuf_pollReply, addr, port);
	pbuf_free(pbuf_pollReply);
}

static void handleDmxDatagram(ARTNET_callbacks* callbacks, const void* daten, uint16_t len)
{
	const T_ArtDmx* packet = (const T_ArtDmx*)daten;

	if (len < (sizeof(T_ArtDmx) - MaxDataLength) )
		return;

	if ( (packet->SubUni != (config.universe & 0xff))
	     || (packet->Net != ((config.universe >> 8) & 0x7f))
	     )
		return;

	uint16_t dmxLen =
		min( (len - (sizeof(T_ArtDmx) - MaxDataLength)),
		     ntohs(packet->Length));

	if (dmxLen < config.offset)
		return;
	else
		dmxLen -= config.offset;

	if (dmxLen < 3)
		return;

	callbacks->dmxData(packet->Data + config.offset,  dmxLen);
}
/*---------------------------------------------------------------------------*/


/******************************************************************************
 * FunctionName : user_devicefind_recv
 * Description  : Processing the received data from the host
 * Parameters   : arg -- Additional argument to pass to the callback function
 *                pusrdata -- The received data (or NULL when the connection has been closed!)
 *                length -- The length of received data
 * Returns      : none
 *******************************************************************************/
static void ICACHE_FLASH_ATTR
echo_udp_receive(void * arg,
		 struct udp_pcb * upcb,
		 struct pbuf * p,
		 struct ip_addr * addr,
		 u16_t port)
{
	if(config.enabled)
	{
		const T_ArtHeader* header = (const T_ArtHeader*)p->payload;
		//ARTNET_callbacks* callbacks = (ARTNET_callbacks*) arg;
		ARTNET_callbacks* callbacks = artnet_callbacks;

		switch (header->opCode) {
		case OpDmx:
			handleDmxDatagram(callbacks, p->payload, p->len);
			break;
		case OpPoll:
			handlePollDatagram(callbacks, upcb, p, addr, port);
			break;
		}
	}
	pbuf_free(p);
}

/******************************************************************************
 * FunctionName : user_devicefind_init
 * Description  : the espconn struct parame init
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
ARTNET_init(ARTNET_callbacks* callbacks, ARTNET_config *new_config)
{
	artnet_callbacks = callbacks;
	ARTNET_set_config(new_config);

	err_t err;

	artnet_pcb = udp_new();

	err = udp_bind(artnet_pcb, IP_ADDR_ANY, 6454);

	udp_recv(artnet_pcb, echo_udp_receive, (void*)callbacks);
}

void ICACHE_FLASH_ATTR
ARTNET_set_config(ARTNET_config *new_config)
{
	if (new_config != NULL)
		memcpy(&config, new_config, sizeof(config));
}

ARTNET_config * ICACHE_FLASH_ATTR
ARTNET_get_config(void)
{
	return &config;
}
