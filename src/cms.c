#include "cms.h"

#include "hash.h"
#include <assert.h>

struct lp_cms* lp_cms_create(const size_t bits, const size_t hashes) {
 assert(bits != 0);
 assert(hashes != 0);

 struct lp_cms* ps = malloc(sizeof(struct lp_cms));
 if (ps == NULL) {
  return NULL;
 }

 ps->seeds = calloc(hashes, sizeof(int));
 if (ps->seeds == NULL) {
  free(ps);
  return NULL;
 }

 register size_t i;
 
 for (i = 0; i < hashes; i++) {
  ps->seeds[i] = i;
 }


 ps->counters = calloc(hashes, sizeof(unsigned int*));
 if (ps->counters == NULL) {
  free(ps->seeds);
  free(ps);
  return NULL;
 }


 for (i = 0; i < hashes; i++) {
  ps->counters[i] = calloc(bits, sizeof(unsigned int));

  if (ps->counters[i] == NULL) {
   register size_t j;

   for (j = 0; j < i; j++) {
    free(ps->counters[j]);
   }

   free(ps->seeds);
   free(ps->counters);
   free(ps);
   return NULL;
  }
 }

 ps->bits = bits;
 ps->hashes = hashes;

 return ps;
}

void lp_cms_free(struct lp_cms** pps) {
 struct lp_cms *ps = *pps;

 free(ps->seeds);

 register size_t i;
 
 for (i = 0; i < ps->hashes; i++) {
  free(ps->counters[i]);
 }

 free(ps->counters);
 free(ps);

 *pps = NULL;
}
