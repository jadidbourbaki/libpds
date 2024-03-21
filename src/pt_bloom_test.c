#include "pt_bloom.h"

#include <assert.h>
#include <stdio.h>

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

int main() {
 test_allocation_trivial();
}
