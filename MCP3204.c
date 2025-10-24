/* mcp3204.c */
#include"header.h"

//#define CS (1<<7)  //(1<<pin number)

u32 mcp3204_read(u8 ch_num){
	u32 res=0;
	u8 bh=0,bl=0;
	ch_num <<= 6;//for second transfer 
	IOCLR0 =CS;//TO SELECT SLAVE FOR SPI COMMUNICATION
				//not decided yet
	//SELECTING MCP3204 SLAVE IN THAT PERTICULAR SENSOR
	spi0(0x06);//1st transfer
	bh=spi0(ch_num);//2nd tx ->	sending sensor selection bits 
					//and recieving last 4bits of result (8-11)
	bl=spi0(0x00);//3rd tx -> no valid data sending but 
				  // recieving valid 8 bit of convertion (0-7)
	bh &= 0x0f;
	res = (bh<<8)|bl;

	return res;	
	}
