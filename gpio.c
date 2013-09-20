#include "gpio.h"


void
gpio_alloc(struct gpio *g, void *base, unsigned int size) {
  g->size = size * 8; /*Store in bits */
  g->data = (unsigned char *)base;
  g->dir = g->data + size;
}

void 
gpio_set_direction(struct gpio *g, unsigned int gpio_num, gpio_direction d) {
  if (d == GPIO_OUT) /* Set high */
    g->dir[gpio_num / g->size] |= (1 << (gpio_num % 8));
  else 
    g->dir[gpio_num / g->size] &= ~(1 << (gpio_num % 8));
}

void
gpio_set_pin(struct gpio *g, unsigned int gpio_num, int val) {
  if (val == 0) 
    g->data[gpio_num / g->size] &= ~(1 << (gpio_num % 8));
  else
    g->data[gpio_num / g->size] |= (1 << (gpio_num % 8));
}

void 
gpio_set_byte(struct gpio *g, unsigned int byte, unsigned char val) {
  g->data[byte] = val;
}

unsigned char
gpio_get_byte(struct gpio *g, unsigned int byte) {
  return g->data[byte];
}
 
