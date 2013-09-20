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

  spi_enable(a->s);
  spi_set_slave_select(a->s, 1);
  spi_write(a->s, adr);
  spi_write(a->s, 0);
  while(!spi_write_fifo_empty(a->s));
  spi_set_slave_select(a->s, 0);

  in1 = spi_read(a->s);
  in2 = spi_read(a->s);
  spi_disable(a->s);

  return (in1 << 8) + in2 ;

}
