#include "spi.h"
#include "adc.h"

#define SPI1 ((void*)0xB1000000 )

int
main() {
  struct spi s;
  struct adc a;

  spi_alloc(&s, SPI1); 
  spi_set_polarity(&s, 0);
  spi_set_phase(&s, 0);
  spi_set_divisor(&s, 1024);
  spi_enable(&s);

  adc_alloc(&a, &s);
  while (1) {
    int x;
    x = adc_acquire(&a, 0);
  }
  
  return 0;
}
