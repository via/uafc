#ifndef _BOARD_H
#define _BOARD_H

/* Board specific things */
#define SPI1 ((void*)0xB1000000 )
#define GPIO0 ((void*)0x91000000 )
#define CG0 ((void*)0x93000000 )

#define KVAFM
#define BARGRAPH


void set_bar(unsigned int val);
unsigned int get_kvafm();
unsigned int get_rpm();
double get_throttle();
double get_o2();

void board_init(void (*tick)());

#endif

