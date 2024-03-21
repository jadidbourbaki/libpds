#include "pt_bloom.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static void test_allocation_trivial(void) {
 printf("%s: ", __func__);

 struct lp_pt_bloom* pb = lp_pt_bloom_create(16, 4);
 assert(pb != NULL);
 assert(pb->hashes == 4);
 assert(pb->bits == 16);
 assert(pb->bitmaps != NULL);
 assert(pb->seeds != NULL);

 lp_pt_bloom_free(&pb);

 printf("passed\n");
}

static void test_correctness_trivial(void) {
 printf("%s: ", __func__);

 const size_t bits = 64;
 const size_t hashes = 4;

 const char* key = "cat";
 const char* not_key = "dog";

 const size_t len_key = 3;

 struct lp_pt_bloom* pb = lp_pt_bloom_create(bits, hashes);

 lp_pt_bloom_insert(pb, key, len_key);

 bool check = lp_pt_bloom_check(pb, key, len_key);
 assert(check);

 check = lp_pt_bloom_check(pb, not_key, len_key);
 assert(!check);

 lp_pt_bloom_free(&pb);

 printf("passed\n");
}

static void benchmark_insert(void) {
 printf("%s: ", __func__);

 /* reasonably sized bloom filter */
 const size_t bits = 4096;
 const size_t hashes = 4;

 /* reasonably sized key */
 const char* key = "http://www.google.com";
 const size_t len_key = strlen(key);
 
 struct lp_pt_bloom* pb = lp_pt_bloom_create(bits, hashes);

 register size_t i;

 clock_t begin = clock();

 for (i = 0; i < 1000; i++) {
  lp_pt_bloom_insert(pb, key, len_key);
 }

 clock_t end = clock();

 lp_pt_bloom_free(&pb);

 double duration = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("benchmark %f seconds\n", duration);

}

static void benchmark_check(void) {
 printf("%s: ", __func__);

 /* reasonably sized bloom filter */
 const size_t bits = 4096;
 const size_t hashes = 4;

 /* reasonably sized key */
 const char* key = "http://www.google.com";
 const size_t len_key = strlen(key);
 
 struct lp_pt_bloom* pb = lp_pt_bloom_create(bits, hashes);
 lp_pt_bloom_insert(pb, key, len_key);

 register size_t i;

 clock_t begin = clock();

 for (i = 0; i < 1000; i++) {
  (void) lp_pt_bloom_check(pb, key, len_key);
 }

 clock_t end = clock();

 lp_pt_bloom_free(&pb);

 double duration = (double)(end - begin) / CLOCKS_PER_SEC;

 printf("benchmark %f seconds\n", duration);

}

int main() {
 test_allocation_trivial();
 test_correctness_trivial();
 benchmark_insert();
 benchmark_check();
}
