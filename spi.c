
#include "spi.h"

void 
spi_alloc(struct spi *s, void *spi_adr) {
  s->_regs = (struct spi_regs *)spi_adr;
}

void 
spi_enable(struct spi *s) {
  s->_regs->SPCR |= SPE;
}

void 
spi_disable(struct spi *s) {
  s->_regs->SPCR &= ~SPE;
}

void 
spi_enable_interrupt(struct spi *s) {
  s->_regs->SPCR |= SPIE;
}

void 
spi_disable_interrupt(struct spi *s) {
  s->_regs->SPCR &= ~SPIE;
}

void spi_set_polarity(struct spi *s, unsigned int pol) {
  if (pol > 0) {
    s->_regs->SPCR |= CPOL;
  } else {
    s->_regs->SPCR &= CPOL;
  }
}

void spi_set_phase(struct spi *s, unsigned int pha) {
  if (pha > 0) {
    s->_regs->SPCR |= CPHA;
  } else {
    s->_regs->SPCR &= CPHA;
  }
}

void
spi_set_divisor(struct spi *s, int unsigned div) {

  unsigned char espr, spr;

  switch (div) {
    case 2:
      espr = 0; spr = 0 ;
      break;
    case 4:
      espr = 0; spr = 1 ;
      break;
    case 16:
      espr = 0; spr = 2 ;
      break;
    case 32:
      espr = 0; spr = 3 ;
      break;
    case 8:
      espr = 1; spr = 0 ;
      break;
    case 64:
      espr = 1; spr = 1 ;
      break;
    case 128:
      espr = 1; spr = 2 ;
      break;
    case 256:
      espr = 1; spr = 3 ;
      break;
    case 512:
      espr = 2; spr = 0 ;
      break;
    case 1024:
      espr = 2; spr = 1 ;
      break;
    case 2048:
      espr = 2; spr = 2 ;
      break;
    case 4096:
    default:
      espr = 2; spr = 3;
      break;
  }
  
  s->_regs->SPCR = (s->_regs->SPCR & (~SPR)) + spr;
  s->_regs->SPER = (s->_regs->SPER & (~ESPR)) + espr;
}

int
spi_interrupt_flag(struct spi *s) {
  return ((s->_regs->SPSR & SPIF) != 0);
}

int
spi_collision(struct spi *s) {
  return ((s->_regs->SPSR & WCOL) != 0);
}

int
spi_write_fifo_full(struct spi *s) {
  return ((s->_regs->SPSR & WFFULL) != 0);
}

int
spi_write_fifo_empty(struct spi *s) {
  return ((s->_regs->SPSR & WFEMPTY) != 0);
}

int
spi_read_fifo_full(struct spi *s) {
  return ((s->_regs->SPSR & RFFULL) != 0);
}

int
spi_read_fifo_empty(struct spi *s) {
  return ((s->_regs->SPSR & RFEMPTY) != 0);
}

void
spi_write(struct spi *s, unsigned char c) {
  s->_regs->SPDR = c;
}

unsigned char
spi_read(struct spi *s) {
  return s->_regs->SPDR;
}
