#include <or1k-support.h>
#include <spr-defs.h>

#include <stdio.h>

#include "spi.h"
#include "adc.h"
#include "gpio.h"
#include "countgen.h"
#include "uafc.h"
#include "history.h"

#define SPI1 ((void*)0xB1000000 )
#define GPIO0 ((void*)0x91000000 )
#define CG0 ((void*)0x93000000 )

struct spi spi1;
struct adc adc1;
struct gpio gpio0;
struct countgen cg0;

static struct sensors sensors;
static struct calculated_values cvals __attribute__((unused)) /* for now */;

struct sensors *
get_sensors() {
  return &sensors;
}

static void 
set_bar(struct gpio *g, unsigned int val) {

  gpio_set_pin(g, 0, (val > 0 ? 1 : 0));
  gpio_set_pin(g, 1, (val > 40 ? 1 : 0));
  gpio_set_pin(g, 2, (val > 100 ? 1 : 0));
  gpio_set_pin(g, 3, (val > 200 ? 1 : 0));
  gpio_set_pin(g, 4, (val > 400 ? 1 : 0));
  gpio_set_pin(g, 5, (val > 800 ? 1 : 0));
  gpio_set_pin(g, 6, (val > 1200 ? 1 : 0));
  gpio_set_pin(g, 7, (val > 1600 ? 1 : 0));
}

static unsigned int 
get_kvafm() {
  return countgen_get_counter(&cg0, 0);
}

static unsigned int 
get_rpm() {
    return countgen_get_counter(&cg0, 0);
}

static double
get_throttle() {
  return adc_acquire(&adc1, 0);
}

static double
get_o2() {
  double afr = adc_acquire(&adc1, 0);
  return 7.35 + (afr / 5.0) * (22.35 - 7.35);
}

void acquire_inputs() {
  sensors.afm = get_kvafm();
  sensors.rpm = get_rpm();
  sensors.throttle = get_throttle();
  sensors.afr = get_o2();
  set_bar(&gpio0, (int)sensors.afm);
  history_append(&sensors);
}  


void clock_interrupt(void) {
      
  or1k_mtspr(SPR_TTMR, or1k_mfspr(SPR_TTMR) & ~SPR_TTMR_IP);

}

void setuptimer(void) {
  or1k_timer_init(200);
  or1k_mtspr(SPR_TTCR, 0);
  or1k_exception_handler_add(0x05,  clock_interrupt);
  or1k_timer_enable();
}

int
main(void) {
  int pin;
  printf("main()\n");


  gpio_alloc(&gpio0, GPIO0, 2);
  countgen_alloc(&cg0, CG0);
  countgen_set_direction(&cg0, 0, COUNTGEN_IN);
  for (pin = 0; pin < 8; ++pin)
    gpio_set_direction(&gpio0, pin, GPIO_OUT);

  gpio_set_byte(&gpio0, 0, 0xAA);

  spi_alloc(&spi1, SPI1); 
  spi_set_polarity(&spi1, 1);
  spi_set_phase(&spi1, 1);
  spi_set_divisor(&spi1, 16);

  adc_alloc(&adc1, &spi1);

  setuptimer();
  while (1) {
  }

  return 0;
}
