#include "lp.h"

#include <stdio.h>
#include <assert.h>

int main() {
 const size_t bits = 64;
 const size_t hashes = 4;

 const char* key = "cat";
 const char* not_key = "dog";

 const size_t len_key = 3;

 struct lp_pt_bloom* pb = lp_pt_bloom_create(bits, hashes);
 assert(pb != NULL);

 lp_pt_bloom_insert(pb, key, len_key);

 bool check = lp_pt_bloom_check(pb, key, len_key);
 if (check) {
  puts("cat is in the bloom filter");
 } else {
  puts("cat is not in the bloom filter");
 }

 check = lp_pt_bloom_check(pb, not_key, len_key);

 if (check) {
  puts("dog is in the bloom filter");
 } else {
  puts("dog is not in the bloom filter");
 }

 lp_pt_bloom_free(&pb);

 return 0;
}
