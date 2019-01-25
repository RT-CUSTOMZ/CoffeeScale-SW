/*
 * mine_type_lookup.h
 *
 *  Created on: Dec 10, 2015
 *      Author: sguelland
 */

#ifndef MINE_TYPE_LOOKUP_H_
#define MINE_TYPE_LOOKUP_H_


struct MineType {
	const char * extension;
	const char * typ;
};

const struct MineType *
mineTypeLookup (const char *str, unsigned int len);
const char* Mine_Type_Lookup(const char * filename);
#endif /* MINE_TYPE_LOOKUP_H_ */
