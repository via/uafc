#include "countgen.h"


void
countgen_alloc(struct countgen *g, void *base) {
  g->dir = (unsigned int *)base;
  g->data = g->dir + 1;
}

void 
countgen_set_direction(struct countgen *g, unsigned int countgen_num, countgen_direction d) {
  if (d == COUNTGEN_OUT) /* Set high */
    *g->dir &= ~(1 << countgen_num);
  else 
    *g->dir |= (1 << countgen_num);
}

void
countgen_set_generator(struct countgen *g, unsigned int countgen_num, unsigned int freq) {
  unsigned int period = 50000000/freq;
  g->data[countgen_num] = period;
}

unsigned int
countgen_get_counter(struct countgen *g, unsigned int countgen) {
  unsigned int period = g->data[countgen];
  return 50000000/period;
}
 
