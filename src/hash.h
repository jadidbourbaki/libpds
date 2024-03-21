#ifndef LP_HASH_H
#define LP_HASH_H

#include <stdint.h>
#include <stdlib.h>

uint64_t lp_hash(const char* key, const size_t len_key, const int seed);

#endif /* LP_HASH_H */
