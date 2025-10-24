/* main.c */
#include"header.h"
u32 lcd=0;
u8 a[5]={15,60,30,15,15},tf=0;
u8 u_str[20];//received string stored here
int main(){
  struct RTC TIME;//structure for day and time
  u32 temp;
  int ldr,adc;
  float res;
  u8 upper[16],lower[16],a[7][5]={"SUN","MON","TUE","WED","THU","FRI","SAT"},h,m,s;
  lcd_init();
  uart_init(9600);
  CONFIG_VIC_TIMER1();
  CONFIG_TIMER1();
  spi0_init();
  adc_init();
  i2c_init();
///////-> SET RTC VALUE
//12hrs mode
	i2c_send(0xD0, 0x2, 0x47);//hrs
// (0100 0111) 0x47 for 7:00 AM
	i2c_send(0xD0, 0x1, 0x59);//min
//(0101 1001) 0x59 for 59min
	i2c_send(0xD0, 0x0, 0x55);//sec
//(0101 0101) 0x55 for 55sec

  while(1){
  	if(tf){
		 tf=0;
		 lcd_cmd(0x01);
		 
//ldr sensor
		 temp = mcp3204_read(2);//ldr sensor
		 ldr = (temp * 100) / 4095;//converting in percentage

		 u_tx_string("LDR: ");
		 u_tx_int(ldr);//in percentage form
		 u_tx_string("%\r\n");
		 
		 lcd_string("LDR:");
		 lcd_int(ldr);
		 lcd_data('%');
	 
//temp
	 	 res = TEMP();
		 u_tx_string("TEMP: ");
		 u_tx_float(res);//in float form
		 u_tx_string("\r\n");
		 
		 lcd_string("T:");
		 lcd_float(res);
		  
//pot
		lcd_cmd(0xC0);
		 adc = pot();
		 u_tx_string("POT: ");
		 u_tx_int(adc);//in float form
		 u_tx_string("\r\n");	
		 
		 lcd_string("P:");
		 lcd_int(adc);
		
	//	sprintf(lower,"T:%2d P:%2d%% L:%2d%%",temp,res,ldr);
		// T:XX P:XX% L:XX%
	//	u_tx_string(lower);

////-> READ RTC VALUES
h = i2c_read(0xD0, 0x2);

if((h>>6)&1){//12hrs
  if((h>>5)&1)//PM
	 TIME.ap = 'P';
  else
  	 TIME.ap = 'A';
  
  if((h>>4)&1)//10hrs added
	 TIME.hours = 10;
  TIME.hours += (h & 0x0f);
}
else{//24hrs
TIME.ap = '-';
  TIME.hours = ((h >> 4) & 3) * 10;//10hars added
  TIME.hours += (h & 0x0f);

}

m = 0x7F & i2c_read(0xD0, 0x1);
   TIME.min = (m>>4)*10 + (m&0x0F);

s = i2c_read(0xD0, 0x0);
   TIME.sec = (s>>4)*10 + (s&0x0F);

	u_tx_int(TIME.hours);
	u_tx(':');
	u_tx_int(TIME.min);
	u_tx(':');	
	u_tx_int(TIME.sec);
	u_tx(' ');
		u_tx(TIME.ap);
	u_tx_string("\n\r");		
	}
  
  }
}

