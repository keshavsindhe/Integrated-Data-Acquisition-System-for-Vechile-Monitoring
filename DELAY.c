/*	DELAY_C	 */
#include"header.h"
extern u8 a[5];

void delay_ms(u32 ms){

T0PC=0;
T0PR=a[VPBDIV]*1000-1;
T0TC=0;
T0TCR=1;
while(T0TC<ms);
T0TCR=0;
}

void delay_sec(u32 sec){

T0PC=0;
T0PR=a[VPBDIV]*1000-1;
T0TC=0;
T0TCR=1;
while(T0TC<sec);
T0TCR=0;
}
