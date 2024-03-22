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

int main() {
 test_allocation_trivial();
}
