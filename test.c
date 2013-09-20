#include <or1k-support.h>
#include <spr-defs.h>

#include <stdio.h>

#include "spi.h"
#include "adc.h"
#include "gpio.h"

#define SPI1 ((void*)0xB1000000 )
#define GPIO0 ((void*)0x91000000 )

struct spi s;
struct adc a;
struct gpio gpio0;
int prev = 0;
int count = 0;
int lastcount = 0;

void set_bar(struct gpio *g, unsigned int val) {

  gpio_set_pin(g, 0, (val > 0 ? 1 : 0));
  gpio_set_pin(g, 1, (val > 500 ? 1 : 0));
  gpio_set_pin(g, 2, (val > 1000 ? 1 : 0));
  gpio_set_pin(g, 3, (val > 1500 ? 1 : 0));
  gpio_set_pin(g, 4, (val > 2000 ? 1 : 0));
  gpio_set_pin(g, 5, (val > 2500 ? 1 : 0));
  gpio_set_pin(g, 6, (val > 3000 ? 1 : 0));
  gpio_set_pin(g, 7, (val > 3500 ? 1 : 0));
}

void trigger(void) {
  int x;
  x = adc_acquire(&a, 0);
  if (x > 2500) {
    if (prev == 0) {
      prev = 1;
      lastcount = count;
      count = 0;
    }
  } else {
    prev = 0;
  }
  count++;
      
  or1k_mtspr(SPR_TTMR, SPR_TTMR_IE | SPR_TTMR_RT | 
	((50000000/100000) & SPR_TTMR_PERIOD));

}

void setuptimer(void) {
  or1k_timer_init(100000);
  or1k_exception_handler_add(0x05,  trigger);
  or1k_timer_enable();
}

int
main(void) {
  int pin;
  printf("main()\n");


  gpio_alloc(&gpio0, GPIO0, 2);
  for (pin = 0; pin < 8; ++pin)
    gpio_set_direction(&gpio0, pin, GPIO_OUT);

  gpio_set_byte(&gpio0, 0, 0xAA);

  spi_alloc(&s, SPI1); 
  spi_set_polarity(&s, 1);
  spi_set_phase(&s, 1);
  spi_set_divisor(&s, 32);

  adc_alloc(&a, &s);

  setuptimer();
  while (1) {
    for (pin = 0; pin < 500000; ++pin);
    int hz = (200/lastcount);
    printf("%d\r\n", lastcount);
  }

  return 0;
}
