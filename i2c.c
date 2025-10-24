/* i2c_driver.c */
/*
   BOTH AT 1ST FUNCTIONALITY
   p0.2 -> SCL
   p0.3 -> SDA
*/

#include"header.h"

#define CSI (1<<3)
#define SI	((I2CONSET>>3)&1)
#define STA (1<<5)
#define STO (1<<4)

void i2c_init(void){
	PINSEL0 |= 0x50;
	I2SCLH = 75;
	I2SCLL = 75;
	//100KBPS AT 15MHZ
	
	I2CONSET = (1<<6);//ENABLE I2C PERIPHERAL
	//aa as 0 and i2en as 1
}

void i2c_send(u8 sa,u8 mr,u8 data){
//1-> start bit
	  I2CONSET = STA;//STA (START) CONDITION ON
	  I2CONCLR = CSI;//SI=0
	  while(SI == 0);
	  I2CONCLR = STA;//STA (START) CONDITION OFF
	
//	if(I2STAT != 0X08){
//	u_tx_string("Err: In start condition\r\n");
//	goto out;
//	}

//2-> sending slave address	and Cheking ACK
	I2DAT = sa&0xFE;//SA + W(0) FOR WRITE 
	I2CONCLR = CSI;//CLEARING
	while(SI == 0);//monitoring SI
	if(I2STAT == 0X20){
	u_tx_string("Err: In Slave Selection\r\n");
	goto out;
	}
//3-> sending memory location and cheking ACK
		I2DAT = mr;//sending mr location	
		I2CONCLR = CSI;//CLEARING
		while(SI==0);
		if(I2STAT == 0X30){
			u_tx_string("Err: In M/R location selecting.\r\n");
			goto out;		
		}
//4-> sending data and cheking ACK
	I2DAT = data;
	I2CONCLR = CSI;
	while(SI==0);
	if(I2STAT == 0x30){
			u_tx_string("Err: In Data sending.\r\n");
			goto out;	
	}
//5-> stop condition			
out:	I2CONSET = STO;//STOP CONDITION
		I2CONCLR = CSI;//SI CLEARING
}

u8 i2c_read (u8 sa,u8 mr){
	 u8 temp=0;
//1-> STAT BIT
	 I2CONSET = STA;//START CONDITION ON
	 I2CONCLR = CSI;//CLEARING
	 while(SI == 0);//WAITING TILL SI SET
	 I2CONCLR = STA;//START CONDITION OFF

//2-> SLAVE + WRITE OPTION and checking ACK
	I2DAT = (sa & 0XFE);//SLAVE + WRITE(0) OPTION
	I2CONCLR = CSI;//CLEARING
	while(SI == 0);
	if(I2STAT == 0X20){
	u_tx_string("Err: In 1 slave selection\r\n");
	goto exit;
	}
//3-> memroy address sending and checking ACK
	I2DAT = mr;
	I2CONCLR = CSI;
	while(SI ==0);
	if(I2STAT == 0X30){
	u_tx_string("Err: In M/R location selection\r\n");
	goto exit;	
	}
//4-> RESTART CONDITION
	I2CONSET = STA;//RE-START CONDITION 
	I2CONCLR = CSI;
	while(SI == 0);
	I2CONCLR = STA;//STOP RE-START CONDITION

//5-> Sending slave adrress again for reading data 
	I2DAT = SI | 1;//SLAVE ADDRESS + READING
	I2CONCLR = CSI;
	while(SI == 0);
	if(I2STAT == 0X48){
	u_tx_string("Err: In slave selection\r\n");
	goto exit;	
	}
//6-> READ DATA
	I2CONCLR = CSI;
	while(SI == 0);
	temp = I2DAT;
//7-> STOP CONDITION
exit:	I2CONSET = STO;//STOP CONDITION ON
		I2CONCLR = CSI;
			
		return temp;
}
