#include "spi.h"
#include "adc.h"

#define SPI1 ((void*)0xB1000000 )

int
main() {
  struct spi s;
  struct adc a;
  int x;

  spi_alloc(&s, SPI1); 
  spi_set_polarity(&s, 1);
  spi_set_phase(&s, 1);
  spi_set_divisor(&s, 1024);

  adc_alloc(&a, &s);
  x = adc_acquire(&a, 0);
  while (1); 
  return 0;
}
