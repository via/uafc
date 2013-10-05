#ifndef _COUNTGEN_H
#define _COUNTGEN_H

typedef enum {
  COUNTGEN_IN,
  COUNTGEN_OUT,
} countgen_direction;

struct countgen {
  unsigned int volatile *data; /* base of io */
  unsigned int volatile *dir;  /* base of direction bits */
};


void countgen_alloc(struct countgen *, void *base);
void countgen_set_direction(struct countgen *, unsigned int countgen_num, countgen_direction d);
void countgen_set_generator(struct countgen *, unsigned int countgen_num, unsigned int freq);
unsigned int countgen_get_counter(struct countgen *, unsigned int countgen);

#endif

