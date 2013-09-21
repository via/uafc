

CC=or1k-elf-gcc
AS=or1k-elf-as
LD=or1k-elf-ld
CFLAGS=-g2 -Wall  -mboard=de0_nano_std  -mhard-div -mhard-mul

test: spi.o adc.o test.o gpio.o
	${CC} ${CFLAGS} -o test spi.o adc.o test.o gpio.o
 


clean:
	-rm spi.o adc.o test gpio.o
