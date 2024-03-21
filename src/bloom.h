#ifndef LP_BLOOM_H
#define LP_BLOOM_H

#include <stdlib.h>
#include <stdbool.h>

struct lp_bloom {
 unsigned char* bitmap;
 size_t bits;

 /* array of hash function seeds */
 int* seeds;

 /* number of hash functions to use */
 /* this is also equal to the number of seeds used */
 size_t hashes;

};

struct lp_bloom* lp_bloom_create(const size_t bits, const size_t hashes);

void lp_bloom_free(struct lp_bloom** ppb);

void lp_bloom_insert(struct lp_bloom* pb, const char* key, const size_t len_key);

bool lp_bloom_check(struct lp_bloom* pb, const char* key, const size_t len_key);

#endif /* LP_BLOOM_H */ 
