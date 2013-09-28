

CC=or1k-elf-gcc
AS=or1k-elf-as
LD=or1k-elf-ld
CFLAGS=-g2 -Wall  -mboard=de0_nano_std  -mhard-div -mhard-mul

OBJS= spi.o adc.o test.o gpio.o shell.o

test: ${OBJS}
	${CC} ${CFLAGS} -o test ${OBJS}
 


clean:
	-rm test ${OBJS}
