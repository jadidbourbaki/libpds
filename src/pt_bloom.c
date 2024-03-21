#include "pt_bloom.h"

#include <assert.h>

struct lp_pt_bloom* lp_pt_bloom_create(const size_t bits, const size_t hashes) {
 assert(bits != 0);
 assert(hashes != 0);

 struct lp_pt_bloom* pb = malloc(sizeof(struct lp_pt_bloom));
 if (pb == NULL) {
  return NULL;
 }

 pb->bitmaps = calloc(hashes, sizeof(unsigned char*));
 if (pb->bitmaps == NULL) {
  free(pb);
  return NULL;
 }

 register size_t i;

 for (i = 0; i < hashes; i++) {
  pb->bitmaps[i] = calloc(bits, 1);
  
  if (pb->bitmaps[i] == NULL) {
   
   register size_t j;
   for (j = 0; j < i; j++) {
    free(pb->bitmaps[j]);
   }

   free(pb->bitmaps);
   free(pb);
   return NULL;
  }
 }

 pb->seeds = calloc(hashes, sizeof(int));
 if (pb->seeds == NULL) {
  for (i = 0; i < hashes; i++) {
   free(pb->bitmaps[i]);
  }

  free(pb->bitmaps);
  free(pb);
  return NULL;
 }

 for (i = 0; i < hashes; i++) {
  pb->seeds[i] = i;
 }

 pb->bits = bits;
 pb->hashes = hashes;

 return pb;

}

void lp_pt_bloom_free(struct lp_pt_bloom** ppb) {
 assert(ppb != NULL);

 struct lp_pt_bloom* pb = *ppb;

 register size_t i;

 for (i = 0; i < pb->hashes; i++) {
  free(pb->bitmaps[i]);
 }

 free(pb->bitmaps);
 free(pb->seeds);

 free(pb);

 *ppb = NULL;
}
