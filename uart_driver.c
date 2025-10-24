/*
uart driver
P0.0->TX 1ST FUNCTIONALITY
P0.1->RX

*/
#include"header.h"
#define THRE ((U0LSR>>5)&1)
#define	RDR (U0LSR&1)

extern u8 a[5];

void uart_init(u32 baud){
  int dll,pclk;
  PINSEL0|=5;//p0.0 as tx,p0.1 as rx
  pclk=a[VPBDIV]*1000000;
  U0LCR=0x83;//unlock baud
  dll=pclk/(16*baud);
  U0DLL=dll&0xff;
  U0DLM=(dll>>8)&0xff;
  U0LCR=0x03;//8bit data and baudrate lock
}

void u_tx(u8 ch){
  U0THR=ch;
  while(THRE==0);
}

u8 u_rx(void){
  u8 ch;
  while(RDR==0);
  ch=U0RBR;
  return ch;
}

void u_tx_string(u8 *p){
  while(*p){
	U0THR=*p++;
	while(THRE==0);
  }
}

void u_rx_string(u8 *p, u8 size){
  u8 i;
  for(i=0;i<size;i++){
  while(RDR==0);
  p[i]=U0RBR;

  if(a[i]=='\r')//enter key
  break;
  }
  a[i]='\0';//null char
}

void u_tx_int(int num){
   int i=0;
   u8 a[16];
	if(num==0){
		u_tx('0');
		return;
		}

	if(num<0){
		num=-num;//making number as positive
		u_tx('-');//neg sign on display
	}

	while(num){//NOTE HAS REVERCED NUMBER
		a[i++]=num%10+48;//converting int to character
		num/=10;
	}
	for(i--;i>=0;i--)
		u_tx(a[i]);//printing on screen
}

void u_tx_float(float f){
	int i=0,num;
	char a[16]={0};
	if(f==0) {
		u_tx_string("0.000");
		return;
		}
	if(f<0){
		u_tx('-');
		f=-f;
	}
	num=(int)f;//decimal part
	if(num==0)
		u_tx('0');
	else{
		while(num){
			a[i++]=num%10+48;
			num/=10;
		}
		for(i--;i>=0;i--)
			u_tx(a[i]);
	}

	u_tx('.');

	num=(f-num)*1000;
	if(f==0)
		u_tx_string("000");
	else{
		i=0;
		while(i<3){
			a[i++]=num%10+48;
			num/=10;
		}
		for(i--;i>=0;i--)
			u_tx(a[i]);
	}
}

void u_tx_hex(int num){
   int i=0,h=1,v=0;
   u8 a[16];
	if(num==0){
		u_tx('0');
		return;
		}
		while(num){
								v += ((num%10)*h); 
								h *= 16;
		}

	while(v){//NOTE HAS REVERCED NUMBER
		a[i++] = (v%10) + 48;//converting int to character
		v /= 10;
	}
	for(i--;i>=0;i--)
		u_tx(a[i]);//printing on screen
}
