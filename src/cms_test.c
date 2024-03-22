#include "cms.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

static void test_allocation_trivial(void) {
 printf("%s: ", __func__);

 struct lp_cms* ps = lp_cms_create(16, 4);
 assert(ps != NULL);
 assert(ps->counters[0][0] == 0);
 assert(ps->seeds[0] == 0);
 assert(ps->hashes == 4);
 assert(ps->bits == 16);

 lp_cms_free(&ps);

 printf("passed\n");
}

static void test_correctness_trivial(void) {
 printf("%s: ", __func__);

 const size_t bits = 64;
 const size_t hashes = 4;

 const char* key = "cat";
 const char* not_key = "dog";

 const size_t len_key = 3;

 struct lp_cms* ps = lp_cms_create(bits, hashes);

 lp_cms_insert(ps, key, len_key);

 int count = lp_cms_count(ps, key, len_key);
 assert(count == 1);

 count = lp_cms_count(ps, not_key, len_key);
 assert(count == 0);

 lp_cms_free(&ps);

 printf("passed\n");
}

static void test_correctness_many_inserts(void) {
 printf("%s: ", __func__);

 const size_t bits = 64;
 const size_t hashes = 4;

 const char* key = "cat";
 const char* not_key = "dog";

 const size_t len_key = 3;

 struct lp_cms* ps = lp_cms_create(bits, hashes);

 register size_t i;

 for (i = 0; i < 100; i++) {
  lp_cms_insert(ps, key, len_key);
 }

 int count = lp_cms_count(ps, key, len_key);
 assert(count >= 100);

 count = lp_cms_count(ps, not_key, len_key);
 assert(count == 0);

 lp_cms_free(&ps);

 printf("passed\n");
}


int main() {
 test_allocation_trivial();
 test_correctness_trivial();
 test_correctness_many_inserts();
}
