#include "lp.h"

#include <stdio.h>
#include <assert.h>

int main() {
 const size_t bits = 64;
 const size_t hashes = 4;

 const char* key = "cat";
 const char* not_key = "dog";

 const size_t len_key = 3;

 struct lp_cms* ps = lp_cms_create(bits, hashes);
 assert(ps != NULL);

 lp_cms_insert(ps, key, len_key);

 int check = lp_cms_count(ps, key, len_key);
 if (check) {
  puts("cat is in the count min sketch");
 } else {
  puts("cat is not in the count min sketch");
 }

 check = lp_cms_count(ps, not_key, len_key);

 if (check) {
  puts("dog is in the count min sketch");
 } else {
  puts("dog is not in the count min sketch");
 }

 lp_cms_free(&ps);

 return 0;
}
