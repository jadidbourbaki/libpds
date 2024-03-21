#ifndef LP_PT_BLOOM_H
#define LP_PT_BLOOM_H

/* partitioned bloom filter */

struct lp_pt_bloom {
 unsigned char** bitmaps;

 /* this is the bits *per bitmap* */
 size_t bits;

 int* seeds;

 /* number of hash functions to use */
 /* this is also equal to the number of seeds used */
 size_t hashes;
};

struct lp_pt_bloom* lp_pt_bloom_create(const size_t bits, const size_t hashes);

void lp_pt_bloom_free(struct lp_bloom** ppb);

void lp_pt_bloom_insert(struct lp_bloom* pb, const char* key, const size_t len_key);

bool lp_pt_bloom_check(struct lp_bloom* pb, const char* key, const size_t len_key);



#endif /* LP_PT_BLOOM_H */
