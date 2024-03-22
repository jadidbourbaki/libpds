#ifndef LP_CMS_H
#define LP_CMS_H

#include <stdlib.h>

struct lp_cms {
 /* also knows as the depth*/
 size_t hashes;

 /* bits per hash --- also known as the width */
 size_t bits;
 
 unsigned int** counters;

 /* array of hash function seeds */
 int* seeds;
};

struct lp_cms* lp_cms_create(const size_t bits, const size_t hashes);

void lp_cms_free(struct lp_cms** pps);

#endif /* LP_CMS_H */
