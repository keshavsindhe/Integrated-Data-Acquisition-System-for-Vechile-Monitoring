/* Header.h */
/*
-> uart
p0.0 -> tx
p0.1 -> rx

-> lcd
   P1.17->RS
   P1.18->RW
   P1.19->EN
   P1.20 - P1.23->D4 - D7

-> spi0
	 p0.4 clk
	 p0.5	miso
	 p0.6	mosi 
	 p0.7 cs	//mcp3204
*/

#include<lpc21xx.h>

#define CS (1<<7)	 //for mcp3204

typedef unsigned char u8;
typedef unsigned int u32;

//delay
void delay_ms(u32);
void delay_sec(u32);

//lcd
void lcd_init(void);
void lcd_data(unsigned int);
void lcd_cmd(unsigned int);
void lcd_string(char *);
void lcd_int(int);
void lcd_float(float);

//uart
void uart_init(u32);
void u_tx(u8);
u8 u_rx(void);
void u_tx_string(u8 *);
void u_rx_string(u8 *,u8);
void u_tx_int(int);
void u_tx_float(float);

//timer1
void CONFIG_VIC_TIMER1(void);
void CONFIG_TIMER1(void);

//SPI0
void spi0_init(void);
u8 spi0(u8);

//MCP3204
u32 mcp3204_read(u8);

//Inbult ADC
void adc_init(void);
u8 adc_read(u8);
u8 temp(void);
u8 pot(void);

//i2c
void i2c_init(void);
void i2c_send(u8 ,u8 ,u8 );
u8 i2c_read (u8 ,u8 );
