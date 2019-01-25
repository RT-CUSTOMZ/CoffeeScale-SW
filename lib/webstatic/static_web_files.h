/*
 * static_web_files.h
 *
 *  Created on: Dec 10, 2015
 *      Author: sguelland
 */

#ifndef STATIC_WEB_FILES_H_
#define STATIC_WEB_FILES_H_

#include <stdint.h>

typedef struct HttpFile {
	const unsigned char* path;
	const uint8_t* data;
	const unsigned int size;
} HttpFile;

//const struct HttpFile * staticWebFileLookup(const char * str, unsigned int len);

#endif /* STATIC_WEB_FILES_H_ */
