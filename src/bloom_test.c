#include "bloom.h"

#include <assert.h>
#include <stdio.h>

static void test_allocation_trivial(void) {
	printf("%s: ", __func__);

	struct pds_bloom* pb = pds_bloom_create(1, 1);
	assert(pb != NULL);
	assert(pb->bitmap[0] == 0);
	assert(pb->seeds[0] == 0);
	assert(pb->hashes == 1);
	assert(pb->bits == 1);

	printf("passed\n");
}

int main() {
	test_allocation_trivial();
}
