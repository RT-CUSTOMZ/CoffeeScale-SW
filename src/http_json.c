#include "lwipopts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"


#include "user_interface.h"
#include "json/jsonparse.h"

#include "http11/http11_parser.h"
#include "http_server.h"

// #include "mine_type_lookup.h"
#include "json_state.h"

#define CRLF "\r\n"

static const char http_response_pre_string[] = {
	"HTTP/1.1 %d"CRLF
//		"Server: nginx/1.9.4"CRLF
//		"Date: Fri, 04 Dec 2015 18:18:38 GMT"CRLF
	// "Content-Type: %s"CRLF
	"Access-Control-Allow-Origin: *"CRLF
	"Access-Control-Allow-Methods: GET, PUT"CRLF
	"Content-Length: 0"CRLF
	"Connection: close"CRLF
	//"Connection: keep-alive"CRLF
	CRLF
};

static int ICACHE_FLASH_ATTR
send_head_response(HttpReqeuest* httpReqeuest, int responseCode)
{
	uint8_t buffer[300];

	os_sprintf(buffer, http_response_pre_string, responseCode
	           // , mineTyp, length
		   );
	tcp_write(httpReqeuest->pcb, buffer, strlen(buffer), TCP_WRITE_FLAG_COPY);
}

void ICACHE_FLASH_ATTR
transmit_json(HttpReqeuest* httpReqeuest, const char *at, size_t length)
{
	json_state_t * json_state = (json_state_t *)httpReqeuest->requestCbData;


	switch (httpReqeuest->requestMethod) {
	case GET:
	{
		if(NULL == json_state->get_json )
			break;
		const char * json_data = json_state->get_json(json_state->user);
		if( NULL == json_data)
			break;
		uint32_t length = strlen(json_data);
		httpReqeuest->requestCb = NULL;
		send_response(httpReqeuest, 200, "application/json", length);
		tcp_write(httpReqeuest->pcb, json_data, length, TCP_WRITE_FLAG_COPY);
		return;
	}
	case PUT:
	{
		if(NULL == json_state->set_json )
			break;
		bool result = json_state->set_json(at, length, json_state->user);

		if(result) {
			os_printf("200\n");
			httpReqeuest->requestCb = NULL;
			send_response(httpReqeuest, 200, "", 0);
      return;
		}
		os_printf("400\n");
		httpReqeuest->requestCb = NULL;
		send_response(httpReqeuest, 400, "", 0);
		return;
	}
	case HEAD:
	case OPTIONS:
	{
		httpReqeuest->requestCb = NULL;
		send_head_response(httpReqeuest, 200);
		return;
	}
	default:
		break;
	}
	httpReqeuest->requestCb = NULL;
	send_head_response(httpReqeuest, 405); //Method Not Allowed
}
