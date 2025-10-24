/* Inbuild ACD */
/*
for rhydolabz board
PINSEL 1 and 1st functionality of each pin

			p0.27 -> free (anything we can connect)
			p0.28 -> temp sensor (default)
			p0.29 -> pot (default)
			p0.30 -> free

*/

#include"header.h"

#define DONE ((ADDR>>31)&1)

void adc_init(void){
			PINSEL1 |= 5<<24;
			//0x15400000;//all channel selected
			ADCR = 0x00200400;	// 3mhz sampling rate and off PDN(power down mode)
}

u8 adc_read(u8 ch){
	   u8 res=0;
				ADCR |= (1<<ch);//channel selection
				ADCR |= (1<<24);//start convertion of ADC
																		
				while(DONE == 0);//waiting till convertion completion

				ADCR ^= (1<<24);//stop convertion of ADC
				ADCR ^= (1<<ch);//channel DE-selection

				res=(ADDR>>6)&0x3ff;//extracting 10bitb result
				return res;
}

u8 temp(void){
				int adc;
				float vout,temp=0;

				adc = adc_read(1);//on channel one temp sensor default
				vout = (adc*3.3)/1023;//10bit resolution and 3.3v ref volt
				temp = (vout-0.5)/0.01;//formula for converting vout to temprature

				return temp;
}

u8 pot(void){
				int adc;
				float vout=0;
				adc = adc_read(2);//pot at by defauklt on channel no two
				vout = (adc*3.3)/1023;//3.3 is ref voltage and 10 bit resolution

				return vout;
}
