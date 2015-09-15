#include <msp430.h> 

/*
 * main.c for SPI to Acclerometer ADXL362
 *
 */

void SetUART (void);
void putS(char *str);
void putC(char byte);
void putI(int k);
void putH(unsigned char byte);


void setSPI(void);
unsigned char readByte(unsigned char address);
void writeByte(unsigned char address, unsigned char data);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    /* Setting DCO to 16MHZ
    	• Auxiliary clock (ACLK), sourced either from a 32768-Hz watch crystal or the internal LF oscillator (4-20kHZ).
		• Main clock (MCLK), the system clock used by the CPU.
		• Sub-Main clock (SMCLK), the sub-system clock used by the peripheral modules.
    */

    DCOCTL = 0;		// set to lowest speed for safety before changing
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	BCSCTL2 |= BIT2 | BIT1;  //   SMCLK = DCO / 8, so 2 MHz;
/*
	P1DIR &= ~BIT0;		// P1.0 INPUT
	P1IES &= ~BIT0;      // P1.0 lO/Hi edge
	P1IFG &= ~BIT0;		// P1.0 IFG cleared
	P1IE  |= BIT0;		// P1.0 IRQ ENABLE
*/
	// DCO is used for the master system clock (MCLK) and SMCLK on BCSCTL2

	//setSPI(); spiRead();

	// *((volatile unsigned char *) 0x7b) = 8;

	SetUART();
	setSPI();

	putS("Hello ! \r\n");

	writeByte(0x20, 100);
	writeByte(0x21, 0);		// Set Activity Threshould

	writeByte(0x2d, 2);		// Measurement mode
	writeByte(0x2a, 0x10);	// INT1 pin is active high, maps the activity status to INT1 pin.
	writeByte(0x27, 0x03);  // activity detection in referenced mode and activity Enable



	P1DIR &= ~BIT0;		// P1.0 INPUT
	P1IES &= ~BIT0;      // P1.0 Hi/lO edge
	P1IFG &= ~BIT0;		// P1.0 IFG cleared
	P1IE  |= BIT0;		// P1.0 IRQ ENABLE

	readByte(0x0b);			// clear INT1 by reading the Status register

	int ii = 0;
	while(1) {

	_BIS_SR(LPM4_bits + GIE);    // Enter LPM4

	putS( " Activity Detacted-");
	readByte(0x0b);
	putI(ii++);
	putS("\r\n");

	}


	while(1) {

	putS("X-");putH(readByte(8));
	putS(" Y-");putH(readByte(9));
	putS(" Z-");putH(readByte(10));
	putS( " Activity-");putH(readByte(0x0b)&0x10);

	putS("\r\n");
	}


	putS("Ready ! \r\n");
	while(1);
	return 0;
}

// Port 1 interrup service routine
#pragma vector=PORT1_VECTOR
__interrupt void port1(void) {
	__bic_SR_register_on_exit(CPUOFF);		// Clear CPUOFF bit 0(SR)
	_delay_cycles(16*1000);
	P1IFG &= ~BIT0;		// P1.0 IFG cleard
	readByte(0x0b);		// clear INT1 by reading the Status register
}

