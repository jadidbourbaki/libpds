#include "fnv1a.h"

uint64_t pds_fnv1a(const char* key, const size_t len_key, const int seed) {
 size_t i = len_key;

 uint64_t h = 14695981039346656037ULL + (31 * seed);

 for (i = 0; i < len_key; i++) {
  h = h ^ (unsigned char) key[i];
  h = h * 1099511628211ULL;
 }

 return h;
}
