#ifndef _SPI_H
#define _SPI_H

struct spi_regs {
  unsigned char volatile SPCR;
  unsigned char volatile SPSR;
  unsigned char volatile SPDR;
  unsigned char volatile SPER;
};

struct spi {
  struct spi_regs *_regs;
};

void spi_alloc(struct spi *s, void *spi_adr);
void spi_enable(struct spi *);
void spi_disable(struct spi *);  
void spi_enable_interrupt(struct spi *s);
void spi_disable_interrupt(struct spi *s);
void spi_set_polarity(struct spi *s, unsigned int polarity);
void spi_set_phase(struct spi *s, unsigned int phase);
void spi_set_divisor(struct spi *, unsigned int clk_divisor);

int spi_interrupt_flag(struct spi *s);
int spi_collision(struct spi *s);
int spi_write_fifo_full(struct spi *s);
int spi_write_fifo_empty(struct spi *s);
int spi_read_fifo_full(struct spi *s);
int spi_read_fifo_empty(struct spi *s);

void spi_write(struct spi *s, unsigned char);
unsigned char spi_read(struct spi *s);


#define SPIE (1<<7)
#define SPE  (1<<6)
#define MSTR (1<<4)
#define CPOL (1<<3)
#define CPHA (1<<2)
#define SPR (3<<0)

#define SPIF (1<<7)
#define WCOL (1<<6)
#define WFFULL (1<<3)
#define WFEMPTY (1<<2)
#define RFFULL (1<<1)
#define RFEMPTY (1<<0)

#define ICNT (3 << 6)
#define ESPR (3 << 0)

#endif

