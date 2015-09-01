/*Hi Guys, do not drown in so much detail. 
There is no need to include UCBUSY in SPI communication for basic reading and writing. 
The code below works perfectly fine for reading device ID of ADXL345 with MSP430G2553;
*/
#include <msp430g2553.h>

volatile char received_byte1 = 0;
volatile char received_byte2 = 0;
volatile char received_byte3 = 0;
volatile char received_byte4 = 0;
volatile char received_byte5 = 0;
unsigned int i;

void spi_conf(void);
void general_clock_cong(void);
void spi_read(void);


void main(void){
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
P1DIR |= BIT0;

general_clock_cong();
spi_conf();
spi_read();
P1OUT &= ~BIT0;

}

void general_clock_cong(void){

DCOCTL = CAL_DCO_16MHZ;
BCSCTL1 = CAL_BC1_16MHZ;

}

void spi_conf(void){

UCA0CTL1 = UCSWRST; // Reset
UCA0CTL0 = UCCKPL + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master
UCA0CTL1 |= UCSSEL_2 ; // USCI clock source select. (SMCLK)
UCA0BR0 = 128; // Baud Rate
UCA0BR1 = 0; // Baud Rate
//UCA0CTL1 &= ~UCCKPH; // phase 0
//UCA0CTL1 |= UCCKPL; // polarity 1
//UC0IE = (UCA0RXIE + UCA0TXIE); // enable interrrupt

//UCA0CTL1 |= UCSWRST; // reset usci

UCA0CTL1 &= ~UCSWRST; // clear reset

P1SEL = (BIT1 + BIT2 + BIT4); // Set SPI CLK, MOSI and MISO
P1SEL2 = (BIT1 + BIT2 + BIT4);
P1DIR = BIT5 + BIT0; // BIT 5 SPI EN, BIT0 LED

}

void spi_read(void){

P1OUT |= BIT5;
P1OUT &= ~BIT5;               // BIT 5 is CS

for(i=1000;i>0;i--){

}

while (!(IFG2&UCA0TXIFG)); // Wait for TXBUF ready
UCA0TXBUF = 0x80; // Send address
while(!(IFG2 & UCA0RXIFG)); // Wait for RXBUF ready
received_byte1 = UCA0RXBUF;
while (!(IFG2&UCA0TXIFG)); // Wait for TXBUF ready
UCA0TXBUF = 0xFF; // Send address
while(!(IFG2 & UCA0RXIFG)); // Wait for RXBUF ready
received_byte2 = UCA0RXBUF;

P1OUT |= BIT5;
//P1OUT &= ~BIT5;

}

/*You can configure for your pins of the chip you re using. When you read the datasheet of ADXL carefully,
you will see you need to set MSB as 1 for reading and 0 for Writting. 
And the rest is pretty standart for SPI communication. I hope I can help. Take care!
*/
