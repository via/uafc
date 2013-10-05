

CC=or1k-elf-gcc
AS=or1k-elf-as
LD=or1k-elf-ld
CFLAGS=-g2 -Wall  -mboard=de0_nano_std  -mhard-div -mhard-mul

OBJS= spi.o adc.o test.o gpio.o shell.o countgen.o history.o board.o

test: ${OBJS}
	${CC} ${CFLAGS} -o test ${OBJS}

test.hex: test
	or1k-elf-objcopy -I elf32-or1k -O binary test test.bin
	printf "%08x" `stat -c"%s" test.bin` | xxd -r -p | dd of=test.bin  conv=notrunc
	or1k-elf-objcopy -I binary -O ihex test.bin test.hex
 


clean:
	-rm test ${OBJS} test.bin test.hex
