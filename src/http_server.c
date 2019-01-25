/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of and a contribution to the lwIP TCP/IP stack.
 *
 * Credits go to Adam Dunkels (and the current maintainers) of this software.
 *
 * Christiaan Simons rewrote this file to get a more stable echo example.
 */

/**
 * @file
 * TCP echo server example using raw API.
 *
 * Echos all bytes sent by connecting client,
 * and passively closes when client is done.
 *
 */

#include "lwipopts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

#include "driver/uart.h"
// #include "ets_sys.h"
// #include "osapi.h"
#include "user_interface.h"
#include "json/jsonparse.h"

#include "http11/http11_parser.h"
#include "http_server.h"

#include "http_path_lookup.h"
#include "static_web_files.h"
#include "mine_type_lookup.h"

#include "http_server.h"

#if LWIP_TCP

static struct tcp_pcb *http_pcb;

//#define HTTP_DEBUG

////////////////////////////////////////////////////////////////////////////////

#define CRLF "\r\n"

static const char http_response_pre_string[] = {
	"HTTP/1.1 %d"CRLF
//		"Server: nginx/1.9.4"CRLF
//		"Date: Fri, 04 Dec 2015 18:18:38 GMT"CRLF
	"Content-Type: %s"CRLF
	"Access-Control-Allow-Origin: *"CRLF
	"Content-Length: %d"CRLF
	"Connection: close"CRLF
	//"Connection: keep-alive"CRLF
	CRLF
};

int ICACHE_FLASH_ATTR
send_response(HttpReqeuest* httpReqeuest, int responseCode, const char * mineTyp, size_t length)
{
	uint8_t buffer[300];

	os_sprintf(buffer, http_response_pre_string, responseCode, mineTyp, length);
	tcp_write(httpReqeuest->pcb, buffer, strlen(buffer), TCP_WRITE_FLAG_COPY);
}

////////////////////////////////////////////////////////////////////////////////



static void ICACHE_FLASH_ATTR
transmit_404(HttpReqeuest* httpReqeuest, const char *at, size_t length)
{
	httpReqeuest->requestCb = NULL;
	send_response(httpReqeuest, 404, "text/html", 0);
}

void transmit_wifi_connect(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_wifi_status(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_wifi_ipInfo(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_pwm(HttpReqeuest* httpReqeuest, const char *at, size_t length);
void transmit_adc(HttpReqeuest* httpReqeuest, const char *at, size_t length);

extern HttpFile fileIndexHtml;
void transmit_file(HttpReqeuest* httpReqeuest, const char *at, size_t length);

////////////////////////////////////////////////////////////////////////////////

static void ICACHE_FLASH_ATTR
header_done_callback(void *data, const char *at, size_t length)
{
	HttpReqeuest* httpReqeuest = (HttpReqeuest*)data;

#ifdef HTTP_DEBUG
	os_printf("Header parsing done\n");
	#endif
	//send_response(httpReqeuest, 404, "text/html", 0);
	if(length > 0 || httpReqeuest->requestMethod == GET)
		httpReqeuest->requestCb(httpReqeuest, at, length);
	//httpReqeuest->requestCb(httpReqeuest, at, length);
}

static void ICACHE_FLASH_ATTR
query_string_callback(void *data, const char *at, size_t length)
{
	//log4c_category_notice(log, "Query string: %.*s", length, at);
	#ifdef HTTP_DEBUG
	os_printf("Query string: ");
	uart0_tx_buffer((uint8*)at, length);
	os_printf("\n");
	#endif
}

static void ICACHE_FLASH_ATTR
request_path_callback(void *data, const char *at, size_t length)
{
	HttpReqeuest* httpReqeuest = (HttpReqeuest*)data;

	//log4c_category_notice(log, "Request path: %.*s", length, at);
	#ifdef HTTP_DEBUG
	os_printf("Request path: ");
	uart0_tx_buffer((uint8*)at, length);
	os_printf("\n");
	#endif

	if (strncmp("GET", at, length) == 0)
		httpReqeuest->requestMethod = GET;
	else if (strncmp("PUT", at, length) == 0)
		httpReqeuest->requestMethod = PUT;
	else if (strncmp("POST", at, length) == 0)
		httpReqeuest->requestMethod = POST;
	else if (strncmp("DELETE", at, length) == 0)
		httpReqeuest->requestMethod = DELETE;
	else if (strncmp("HEAD", at, length) == 0)
		httpReqeuest->requestMethod = HEAD;
	else if (strncmp("OPTIONS", at, length) == 0)
		httpReqeuest->requestMethod = OPTIONS;
}

static void ICACHE_FLASH_ATTR
request_uri_callback(void *data, const char *at, size_t length)
{
	HttpReqeuest* httpReqeuest = (HttpReqeuest*)data;

#ifdef HTTP_DEBUG
	os_printf("Request uri: ");
	uart0_tx_buffer((uint8*)at, length);
	os_printf("\n");
#endif

	const HttpPathLookup* lookup = http_path_lookup(at, length);
	if (lookup == NULL) {
		httpReqeuest->requestCb = transmit_404;
		httpReqeuest->requestCbData = 0;
		return;
	}else {
		httpReqeuest->requestCb = lookup->requestCb;
		httpReqeuest->requestCbData = lookup->requestCbData;
		httpReqeuest->requestCbPosition = 0;
	}
	return;
}

static void ICACHE_FLASH_ATTR
field_callback(void *data, const char *field, size_t flen, const char *value, size_t vlen)
{
	#ifdef HTTP_DEBUG
	os_printf("Field: ");
	uart0_tx_buffer((uint8*)field, flen);
	os_printf(" Value: ");
	uart0_tx_buffer((uint8*)value, vlen);
	os_printf("\n");
	#endif
	HttpReqeuest* httpReqeuest = (HttpReqeuest*)data;

	if (strncmp("Content-Length", field, flen) == 0) {
		uint32_t number = 0;
		uint32_t i;
		for (i = 0; i < vlen; i++)
			number = number * 10 + (value[i] - '0');
		httpReqeuest->content_length = number;
	}
}

////////////////////////////////////////////////////////////////////////////////

static err_t http_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t http_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void http_error(void *arg, err_t err);
static err_t http_poll(void *arg, struct tcp_pcb *tpcb);
static err_t http_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void http_send(struct tcp_pcb *tpcb, HttpReqeuest *es);
//static void http_close(struct tcp_pcb *tpcb, HttpReqeuest *es);

void ICACHE_FLASH_ATTR
http_server_init(void)
{
	http_pcb = tcp_new();
	if (http_pcb != NULL) {
		err_t err;

		err = tcp_bind(http_pcb, IP_ADDR_ANY, 80);
		if (err == ERR_OK) {
			http_pcb = tcp_listen(http_pcb);
			tcp_accept(http_pcb, http_accept);
		}else {
			/* abort? output diagnostic? */
		}
	}else {
		/* abort? output diagnostic? */
	}
}


static err_t ICACHE_FLASH_ATTR
http_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	err_t ret_err;
	struct HttpReqeuest *es;


	/* commonly observed practive to call tcp_setprio(), why? */
	tcp_setprio(newpcb, TCP_PRIO_MIN);

	es = (HttpReqeuest*)mem_malloc(sizeof(HttpReqeuest));
	if (es != NULL) {
		es->state = ES_ACCEPTED;
		es->pcb = newpcb;
		//es->retries = 0;
		//es->p = NULL;
		/* pass newly allocated es to our callbacks */
		tcp_arg(newpcb, es);
		tcp_recv(newpcb, http_recv);
		tcp_err(newpcb, http_error);
		tcp_poll(newpcb, http_poll, 0);
		tcp_sent(newpcb, http_sent);
		memset(&(es->httpParser), 0, sizeof(http_parser));
		es->httpParser.http_field = field_callback;
		es->httpParser.header_done = header_done_callback;
		es->httpParser.query_string = query_string_callback;
		es->httpParser.request_method = request_path_callback;
		es->httpParser.request_uri = request_uri_callback;
		es->httpParser.data = es;
		http_parser_init(&(es->httpParser));
		ret_err = ERR_OK;
	}else
		ret_err = ERR_MEM;
	return ret_err;
}

static err_t ICACHE_FLASH_ATTR
http_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct HttpReqeuest *es = (HttpReqeuest*)arg;

	if (p == NULL) {
		http_close(tpcb, es);
		return ERR_OK;
	}
	#ifdef HTTP_DEBUG
	os_printf("Recv: \n");
	#endif
	if( http_parser_is_finished(&(es->httpParser)) == 0) {
		http_parser_execute(&(es->httpParser), p->payload, p->len, 0);
	} else {
		os_printf("%s\n", p->payload);
		es->requestCb(es, p->payload, p->len);

	}
	//uart0_tx_buffer((uint8*)p->payload, p->len);
	tcp_recved(tpcb, p->len);
	pbuf_free(p);
	return ERR_OK;
}

void ICACHE_FLASH_ATTR
http_error(void *arg, err_t err)
{
	struct HttpReqeuest *es = (HttpReqeuest*)arg;

#ifdef HTTP_DEBUG
	os_printf("Error: \n");
	#endif
	LWIP_UNUSED_ARG(err);

	if (es != NULL)
		mem_free(es);
}

static err_t ICACHE_FLASH_ATTR
http_poll(void *arg, struct tcp_pcb *tpcb)
{
	//os_printf("Poll: \n");
	return ERR_OK;
}

static err_t ICACHE_FLASH_ATTR
http_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct HttpReqeuest *httpReqeuest = (HttpReqeuest*)arg;

#ifdef HTTP_DEBUG
	os_printf("Sent: \n");
#endif

	if (httpReqeuest->requestCb != NULL)
		httpReqeuest->requestCb(httpReqeuest, 0, 0);
	return ERR_OK;
}


void ICACHE_FLASH_ATTR
http_close(struct tcp_pcb *tpcb, HttpReqeuest *es)
{
	tcp_arg(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_recv(tpcb, NULL);
	tcp_err(tpcb, NULL);
	tcp_poll(tpcb, NULL, 0);

	if (es != NULL)
		mem_free(es);
	tcp_close(tpcb);
		#ifdef HTTP_DEBUG
	os_printf("Connection Closed\n");
	#endif
}

#endif /* LWIP_TCP */
