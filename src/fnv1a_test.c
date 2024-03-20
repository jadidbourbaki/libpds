#include "fnv1a.h"

#include <assert.h>
#include <stdio.h>

static void test_hash_correct(void) {
	printf("%s: ", __func__);

	const char* key = "cat";
	const size_t key_len = 3;
	const int seed = 0;

	uint64_t result = pds_fnv1a(key, key_len, seed);
	uint64_t expected_result = 0xf5e307190ce4a327;

	assert(result == expected_result);
	printf("passed\n");
}

static void test_empty(void) {
	printf("%s: ", __func__);

	const char* key = "";
	const size_t key_len = 0;
	const int seed = 0;

	uint64_t result = pds_fnv1a(key, key_len, seed);
	uint64_t expected_result = 14695981039346656037ULL;

	assert(result == expected_result);
	printf("passed\n");
}

static void test_seed(void) {
	printf("%s: ", __func__);

	const char* key = "cat";
	const size_t key_len = 3;
	const int seed1 = 0;
	const int seed2 = 1;

	uint64_t result1 = pds_fnv1a(key, key_len, seed1);
	uint64_t result2 = pds_fnv1a(key, key_len, seed2);

	assert(result1 != result2);
	printf("passed\n");
}

static void test_avalanche(void) {
	printf("%s: ", __func__);

	const uint8_t key1 = 0;
	const uint8_t key2 = 1;

	const size_t key_len = 1;
	const int seed = 42;

	uint64_t result1 = pds_fnv1a(((char*) &key1), key_len, seed);
	uint64_t result2 = pds_fnv1a(((char*) &key2), key_len, seed);

	assert(result1 != result2);
	printf("passed\n");
}

int main() {
	test_hash_correct();
	test_empty();
	test_seed();
	test_avalanche();
}
