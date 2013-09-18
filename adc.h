#ifndef _ADC_H
#define _ADC_H

struct spi;

struct adc {
  struct spi *s;
};

void adc_alloc(struct adc *a, struct spi *s);
unsigned int adc_acquire(struct adc *a, int input);


#endif

