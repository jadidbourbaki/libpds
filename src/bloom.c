#include "bloom.h"

#include "fnv1a.h"
#include <assert.h>
#include <limits.h>

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

	register size_t i;

	for (i = 0; i < pb->hashes; i++) {
		pb->seeds[i] = i;
	}

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

void pds_bloom_insert(struct pds_bloom* pb, const char* key, const size_t len_key) {
	register size_t i;

	for (i = 0; i < pb->hashes; i++) {
		uint64_t hash = pds_fnv1a(key, len_key, pb->seeds[i]);
		hash %= pb->bits;

		size_t index = hash / CHAR_BIT;
		int bit = hash % CHAR_BIT;

		pb->bitmap[index] |= (1 << bit);
	}
}

bool pds_bloom_check(struct pds_bloom* pb, const char* key, const size_t len_key) {
	register size_t i;

	for (i = 0; i < pb->hashes; i++) {
		uint64_t hash = pds_fnv1a(key, len_key, pb->seeds[i]);
		hash %= pb->bits;

		size_t index = hash / CHAR_BIT;
		int bit = hash % CHAR_BIT;

		char result = pb->bitmap[index] & (1 << bit);
		if (result == 0) {
			return false;
		}

	}

	return true;
}
