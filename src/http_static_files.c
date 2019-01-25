#include "lwipopts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"


#include "http11/http11_parser.h"
#include "http_server.h"

#include "static_web_files.h"
#include <mine_type_lookup.h>

#define min(a, b) \
	({ __typeof__(a)_a = (a); \
	   __typeof__(b)_b = (b); \
	   _a < _b ? _a : _b; })

static void transmit_file_data(HttpReqeuest* httpReqeuest, const char *at, size_t length)
{
	struct HttpFile * staticFile = (struct HttpFile *)httpReqeuest->requestCbData;

	if (httpReqeuest->requestCbPosition >= staticFile->size)
		//httpReqeuest->state = ES_CLOSING;
		return;

	u16_t bufferLen = tcp_sndbuf(httpReqeuest->pcb);

	u16_t send_size = min((staticFile->size -  httpReqeuest->requestCbPosition), bufferLen);

	tcp_write(httpReqeuest->pcb, &(staticFile->data[httpReqeuest->requestCbPosition]), send_size, 0);
	httpReqeuest->requestCbPosition += send_size;
}

void transmit_file(HttpReqeuest* httpReqeuest, const char *at, size_t length)
{
	struct HttpFile * staticFile = (struct HttpFile *)httpReqeuest->requestCbData;

	os_printf("Send File: %s\n", staticFile->path);


	const char* fileExtension =  strrchr(staticFile->path, '.');
	const struct MineType* mineType = NULL;
	if (fileExtension != NULL) {
		fileExtension++;
		os_printf("Lookup mine Type for %s\n", fileExtension);
		mineType = mineTypeLookup(fileExtension, strlen(fileExtension));
	}
	const char* mineTypeString;
	if (mineType == NULL)
		mineTypeString = "text/html";
	else
		mineTypeString = mineType->typ;

	send_response(httpReqeuest, 200, mineTypeString, staticFile->size);
	transmit_file_data(httpReqeuest, 0, 0);
	httpReqeuest->requestCb = transmit_file_data;
	tcp_output(httpReqeuest->pcb);


	//send_response(httpReqeuest->connectionSocket, 200, mineTypeString, *(staticFile->sizePtr));
	//send(httpReqeuest->connectionSocket, staticFile->data, *(staticFile->sizePtr), 0);
}
