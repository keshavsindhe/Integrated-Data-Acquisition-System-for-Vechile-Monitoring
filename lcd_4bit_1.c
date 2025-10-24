/*
   lcd driver
   PIN DISCREPTION

   P1.17->RS
   P1.18->RW
   P1.19->EN
   P1.20 - P1.23->D4 - D7
 */ 

#include"header.h"

#define LCD (0xFE<<16);

#define D1 ((data & 0xf0)<<16)
#define D0 ((data & 0x0f)<<20)

#define C1 ((cmd&0xf0)<<16)
#define C0 ((cmd&0x0f)<<20)

#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)

void lcd_init(void){
	IODIR1=LCD;//AS OUTPUT PIN
	lcd_cmd(0x02);//4bit mode
 	lcd_cmd(0x28);//2 rows enable
	lcd_cmd(0x0e);//cursor enable
	lcd_cmd(0x01);//clear screen
}

void lcd_data(unsigned int data){
	//upper half
	IOCLR1=LCD;//CLEAR
	IOSET1=D1;
	IOSET1=RS;//AS DATA
	IOCLR1=RW;//AS WRITE
	IOSET1=EN;//ENABLE OPERATION OF LCD
	delay_ms(2);
	IOCLR1=EN;//DISABLE OPERATIONS OF LCD

	//lowwer half
	IOCLR1=LCD;//CLEAR
	IOSET1=D0;
	IOSET1=RS;//AS DATA
	IOCLR1=RW;//AS WRITE
	IOSET1=EN;//ENABLE OPERATION OF LCD
	delay_ms(2);
	IOCLR1=EN;//DISABLE OPERATIONS OF LCD 
}

void lcd_cmd(unsigned int cmd){
	//UPPER NIBBLE
	IOCLR1=LCD;//CLEAR SCREEM
	IOSET1=C1;//UPPER NIBBLE SENT
	IOCLR1=RS;//AS COMMAND  MODE
	IOCLR1=RW;//WRITE ON LCD
	IOSET1=EN;//ENABLE LCD OPERATIONS
	delay_ms(2);
	IOCLR1=EN;//disable lcd operations
	//lowwer nible 
	IOCLR1=LCD;//CLEAD PINS
	IOSET1=C0;///LOWWER NIBBLE
	IOCLR1=RS;//AS CMD
	IOCLR1=RW;//AS WRITE MODE
	IOSET1=EN;//ENABLE OPERATION OF LCD
	delay_ms(2);
	IOCLR1=EN;//DISBALE LCD OPERATIONS

}

void lcd_int(int num){
	int i=0,a[16];
	if(num==0)
		lcd_data('0');

	if(num<0){
		num=-num;//making number as positive
		lcd_data('-');//neg sign on display
	}

	while(num){//NOTE HAS REVERCED NUMBER
		a[i++]=num%10+48;//converting int to character
		num/=10;
	}
	for(i--;i>=0;i--)
		lcd_data(a[i]);//printing on screen

}

void lcd_string(char * p){
	while(*p)
		lcd_data(*p++);

}

void lcd_float(float f){
	int i=0,num;
	char a[16]={0};
	if(f==0) {
		lcd_string("0.000");
		return;
		}
	if(f<0){
		lcd_data('-');
		f=-f;
	}
	num=(int)f;//decimal part
	if(num==0)
		lcd_data('0');
	else{
		while(num){
			a[i++]=num%10+48;
			num/=10;
		}
		for(i--;i>=0;i--)
			lcd_data(a[i]);
	}

	lcd_data('.');

	num=(f-num)*1000;
	if(f==0)
		lcd_string("000");
	else{
		i=0;
		while(i<3){
			a[i++]=num%10+48;
			num/=10;
		}
		for(i--;i>=0;i--)
			lcd_data(a[i]);
	}
}
