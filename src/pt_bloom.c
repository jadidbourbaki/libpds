#include "pt_bloom.h"

#include <assert.h>

struct lp_pt_bloom* lp_pt_bloom_create(const size_t bits, const size_t hashes) {
 assert(bits != 0);
 assert(hashes != 0);

 struct lp_pt_bloom pptb = malloc(sizeof(struct lp_pt_bloom));
 if (pptb == NULL) {
  return NULL;
 }

 pptb->bitmaps = calloc(hashes, sizeof(unsigned char*));
 if (pptb->bitmaps == NULL) {
  free(pptb);
  return NULL;
 }

 register size_t i;

 for (i = 0; i < hashes; i++) {
  pptb->bitmaps[i] = calloc(bits, 1);
  
  if (pptb->bitmaps[i] == NULL) {
   
   register size_t j;
   for (j = 0; j < i; j++) {
    free(pptb->bitmaps[j];
   }

   free(pptb->bitmaps);
   free(pptb);
   return NULL;
  }
 }

 pptb->seeds = calloc(hashes, sizeof(int));
 if (pptb->seeds == NULL) {
  for (i = 0; i < hashes; i++) {
   free(pptb->bitmaps[i]);
  }

  free(pptb->bitmaps);
  free(pptb);
  return NULL;
 }

 for (i = 0; i < hashes; i++) {
  pptb->seeds[i] = i;
 }

 pptb->bits = bits;
 pptb->hashes = hashes;

 return pptb;

}

