/*
timer1 INtr.c
slot 0 timer-1 for 1 sec
*/
#include"header.h"

extern u8 tf;
extern u32 lcd; 

void TIMER1_INTR(void) __irq{
	T1IR=1;//CLRARING INTR FLAG 
	//flag setting
	tf=1;
	//lcd++;

	VICVectAddr=0;//must
}

void CONFIG_VIC_TIMER1(void){
	VICVectAddr0 =(u32)TIMER1_INTR;
	VICVectCntl0= 5|(1<<5);

	VICIntEnable=(1<<5);//timer 1
}														
void CONFIG_TIMER1(void){
	T1PC=0;//starting from 0
	T1PR=14999999;//ending value as 1sec
	T1MR0=1;//comared with t1tc	
	T1MCR=3;//reset and interrupt enable
	T1TC=0;// final counter as zero
	T1TCR=1;//starting timer
}
