/* spi_driver.c */
/*
-> spi0
	 p0.4 clk
	 p0.5	miso
	 p0.6	mosi
		p0.7 CS
*/
#include"header.h"

#define SPIF ((S0SPSR>>7)&1)

void spi0_init(void){
	 PINSEL0 |=0X1500;//selecting spi functionality
	 S0SPCR=0x20;//CPHA=CPOL=SPI_INTR=0,MASTER MODE,MSB_FIRST
	 //0010 0000
}

u8 spi0(u8 data){
	S0SPDR=data;//loading data into buffer
	while(SPIF==0);//waiting till transfer completes
	return S0SPDR;//redeang buf. after transfer completes
}
