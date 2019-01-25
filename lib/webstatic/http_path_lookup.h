/*
 * http_server.h
 *
 *  Created on: Nov 21, 2015
 *      Author: sguelland
 */

#ifndef HTTP_PATH_LOOKUP_H_
#define HTTP_PATH_LOOKUP_H_

typedef struct HttpPathLookup {
	const char* path;
	void (*requestCb)(struct HttpReqeuest * httpRequest, const char *at, size_t length);
	void* requestCbData;
} HttpPathLookup;

const struct HttpPathLookup *
http_path_lookup(const char *str, unsigned int len);

#endif /* HTTP_PATH_LOOKUP_H_ */
