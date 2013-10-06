#include "spi.h"
#include "adc.h"
#include "gpio.h"
#include "countgen.h"
#include "uafc.h"
#include "board.h"

#include <stdio.h>
#include <or1k-support.h>
#include <spr-defs.h>


static struct spi spi1;
static struct adc adc1;
static struct gpio gpio0;
static struct countgen cg0;
static uafc_tick_callback uafc_tick = NULL;

void 
set_bar(unsigned int val) {

  gpio_set_pin(&gpio0, 0, (val > 0 ? 1 : 0));
  gpio_set_pin(&gpio0, 1, (val > 40 ? 1 : 0));
  gpio_set_pin(&gpio0, 2, (val > 100 ? 1 : 0));
  gpio_set_pin(&gpio0, 3, (val > 200 ? 1 : 0));
  gpio_set_pin(&gpio0, 4, (val > 400 ? 1 : 0));
  gpio_set_pin(&gpio0, 5, (val > 800 ? 1 : 0));
  gpio_set_pin(&gpio0, 6, (val > 1200 ? 1 : 0));
  gpio_set_pin(&gpio0, 7, (val > 1600 ? 1 : 0));
}

unsigned int 
get_kvafm() {
  return countgen_get_counter(&cg0, 0);
}

unsigned int 
get_rpm() {
    return countgen_get_counter(&cg0, 2);
}

double
get_throttle() {
  int raw = adc_acquire(&adc1, 0);
  return raw / 4096.0;
}

double
get_o2() {
  int raw = adc_acquire(&adc1, 1);
  double afr = raw / 4096.0;
  return 7.35 + (afr / 5.0) * (22.35 - 7.35);
}

static void 
clock_interrupt(void) {
      
  if (uafc_tick)
    uafc_tick();
  or1k_mtspr(SPR_TTMR, or1k_mfspr(SPR_TTMR) & ~SPR_TTMR_IP);

}

static void 
setuptimer() {
  or1k_timer_init(200);
  or1k_mtspr(SPR_TTCR, 0);
  or1k_exception_handler_add(0x05,  clock_interrupt);
  or1k_timer_enable();
}


void board_init(uafc_tick_callback tick) {
  int pin;

  printf("board_init() enter\r\n");
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
  uafc_tick = tick;
  setuptimer();
  printf("board_init() exit\r\n");
}
