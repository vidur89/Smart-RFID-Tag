#include <msp430g2553.h> 

/*

//#define SFR_8BIT(address)   extern volatile unsigned char address

*/
//#define USICNT	(volatile unsigned cahr) *(0x07b)


/*

for SPI to Acclerometer ADXL362
 
  
• 7- or 8-bit data length
• LSB-first or MSB-first data transmit and receive
• 3-pin and 4-pin SPI operation
• Master or slave modes

Wire connection MSP430 <-> ADXL362

MSP430 using SCB0               ADXL362

p1.4 				<->			CS				
p1.5 (UCB0CLK)		<->			SCK	
p1.6 (UCB0SOMI)		<->			MIS0
P1.7 (UCB0SIMO)		<->			MOSI

ADXL362 SPI clock speed 1-8 MHz, 8-bit data length, LSB-first

*/

void setSPI(void) {

	P1SEL  &= ~BIT4; 
    P1SEL2 &= ~BIT4;
    P1DIR  |=  BIT4; // output For CS
    P1OUT |= BIT4;

	P1SEL  |= BIT5 | BIT6 | BIT7;	// set P1.5 - 7 for SPI on page 43 of hardware data sheet
	P1SEL2 |= BIT5 | BIT6 | BIT7;

//	ME1 |= USPIE0;		//enable the SPI mode for USART0  not needed
//	ME2 |= USPIE0;		//enable the SPI mode for USART1  not needed

/*
	Synchronous mode is for SPI
	
	Asynchronous mode is for UART

*/

/*
NOTE: Initializing or Re-Configuring the USCI Module
The recommended USCI initialization/re-configuration process is:

1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
3. Configure ports
4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE

*/

	UCB0CTL1 |= UCSWRST;		// set UCSWRST to put in reset state

	UCB0CTL1 |= BIT6 | BIT7;	// use SMCLK

 	//Clock phase, Clock inactive state is low, MSB first, 8-bit data, Master mode, 3-pin SPI, pp 445
	UCB0CTL0 |= BIT7 | UCMST | UCSYNC | UCMSB;
	
	
	//Bit clock prescaler setting, the 16-bit valuse of (UCB0BRO + UCB0BR1 * 256)
	//SMCLK = 2 MHz  by BCSCTL2
	UCB0BR0 = 4;
	UCB0BR1 = 0;
	
	UCB0CTL1 &= ~UCSWRST;	// clear UCSWRST to get out of reset state

}

void spiByteWrite(unsigned char data) {

   UCB0TXBUF = data; 
   while (( UCB0STAT & BIT0 ));   //wait for tranmitting, buffering-wise

}

unsigned char readByte(unsigned char address) {

   P1OUT &= ~BIT4;			 // set CS to low

   spiByteWrite(0x0b);	     // read command for ADXL362
   spiByteWrite(address);    // address
   spiByteWrite(0x00);       // provide clk to read from ADXL362

   while (!(IFG2 & BIT2));   // wait for receiving a byte

   P1OUT |= BIT4;			 // set CS to high
   return UCB0RXBUF;

   //_delay_cycles(8*4*8); 
}


void writeByte(unsigned char address, unsigned char data) {

   P1OUT &= ~BIT4;			// set CS to low

   spiByteWrite(0x0a);	    // write command for ADXL362
   spiByteWrite(address);   // address
   spiByteWrite(data);      // data
 
   while (!(IFG2 & BIT3));   // wait for sending the last byte, hardware signal - wise

   P1OUT |= BIT4;			// set CS to high
 
}
