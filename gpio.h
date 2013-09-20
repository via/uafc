#ifndef _GPIO_H
#define _GPIO_H

typedef enum {
  GPIO_OUT,
  GPIO_IN,
} gpio_direction;

struct gpio {
  unsigned char volatile *data; /* base of io */
  unsigned char volatile *dir;  /* base of direction bits */
  unsigned int size;
};


void gpio_alloc(struct gpio *, void *base, unsigned int size /*bytes*/);
void gpio_set_direction(struct gpio *, unsigned int gpio_num, gpio_direction d);
void gpio_set_pin(struct gpio *, unsigned int gpio_num, int val);
void gpio_set_byte(struct gpio *, unsigned int byte, unsigned char val);
unsigned char gpio_get_byte(struct gpio *, unsigned int byte);

#endif

