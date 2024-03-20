#ifndef PDS_FNV1A_H
#define PDS_FNV1A_H

#include <stdint.h>
#include <stdlib.h>

uint64_t pds_fnv1a(const char* key, const size_t len_key, const int seed);

#endif /* FNV1A_H */
