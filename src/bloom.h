#ifndef PDS_BLOOM_H
#define PDS_BLOOM_H

#include <stdlib.h>

struct pds_bloom {
	unsigned char* bitmap;
	size_t bits;

	/* array of hash function seeds */
	int* seeds;

	/* number of hash functions to use */
	/* this is also equal to the number of seeds used */
	size_t hashes;

};

struct pds_bloom* pds_bloom_create(const size_t bits, const size_t hashes);

void pds_bloom_free(struct pds_bloom** ppb);

#endif /* PDS_BLOOM_H */ 
