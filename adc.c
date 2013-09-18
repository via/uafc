#include "spi.h"
#include "adc.h"

void
adc_alloc(struct adc *adc, struct spi *s) {
  adc->s = s;
}


unsigned int
adc_acquire(struct adc *a, int input) {

  unsigned char adr, in1, in2;
  adr = (input & 0x7) << 3;

  spi_write(a->s, adr);
  spi_write(a->s, 0);

  while(spi_read_fifo_empty(a->s));
  in1 = spi_read(a->s);
  
  while(spi_read_fifo_empty(a->s));
  in2 = spi_read(a->s);

  return (in1 << 8) + in2 ;

}
