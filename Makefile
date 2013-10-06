

CC=or1k-elf-gcc
AS=or1k-elf-as
LD=or1k-elf-ld
OBJCOPY=or1k-elf-objcopy
CFLAGS=-g2 -Wall  -mboard=de0_nano_std  -mhard-div -mhard-mul

OBJS= uafc.o spi.o adc.o gpio.o shell.o countgen.o history.o board.o

uafc: ${OBJS}
	${CC} ${CFLAGS} -o uafc ${OBJS}

uafc.hex: uafc
	${OBJCOPY} -I elf32-or1k -O binary uafc uafc.bin
	printf "%08x" `stat -c"%s" uafc.bin` | xxd -r -p | dd of=uafc.bin  conv=notrunc
	${OBJCOPY} -I binary -O ihex uafc.bin uafc.hex
	rm uafc.bin


clean:
	-rm uafc ${OBJS} uafc.hex
