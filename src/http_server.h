/*
 * http_server.h
 *
 *  Created on: Nov 21, 2015
 *      Author: sguelland
 */

#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include "http11/http11_parser.h"

enum http_states {
	ES_NONE = 0,
	ES_ACCEPTED,
	ES_HEADER_DONE,
	ES_RESPONSE_DONE,
	ES_CLOSING
};

typedef enum RequestMethods {
	GET = 0,
	HEAD,
	POST,
	PUT,
	DELETE,
	OPTIONS,
}RequestMethods;

typedef struct HttpReqeuest {
	enum http_states state;
	struct tcp_pcb *pcb;
	http_parser httpParser;
	void (*requestCb)(struct HttpReqeuest * httpRequest, const char *at, size_t length);
	void * requestCbData;
	uint32_t requestCbPosition;
	RequestMethods requestMethod;
	uint32_t content_length;
	/* pbuf (chain) to recycle */
	//struct pbuf *p;
} HttpReqeuest;


int send_response(HttpReqeuest* httpReqeuest, int responseCode, const char * mineTyp, size_t length);
void
http_close(struct tcp_pcb *tpcb, HttpReqeuest *es);

#endif /* HTTP_SERVER_H_ */
