#include "bloom.h"

#include <assert.h>

struct pds_bloom* pds_bloom_create(const size_t bits, const size_t hashes) {
	assert(bits != 0);
	assert(hashes != 0);

	struct pds_bloom* pb = malloc(sizeof(struct pds_bloom));
	if (pb == NULL) {
		return NULL;
	}

	pb->bitmap = calloc(bits, 1);
	if (pb->bitmap == NULL) {
		free(pb);
		return NULL;
	}

	pb->bits = bits;

	pb->seeds = calloc(hashes, sizeof(int));
	if (pb->seeds == NULL) {
		free(pb->bitmap);
		free(pb);
		return NULL;
	}

	pb->hashes = hashes;

	return pb;
}

void pds_bloom_free(struct pds_bloom** ppb) {
	assert(ppb != NULL);

	struct pds_bloom* pb = *ppb;
	free(pb->bitmap);
	free(pb->seeds);
	free(pb);
	*ppb = NULL;
}
