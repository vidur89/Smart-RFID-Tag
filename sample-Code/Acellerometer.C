//  Interfacing ADXL345 accelerometer with MSP430G2553 with I2C communication

//

//                                /|\  /|\

//               ADXL345          10k  10k     MSP430G2xx3

//                slave            |    |        master

//             -----------------   |    |  -----------------

//            |                          SDA|<-|---+->|P3.1/UCB0SDA  XIN|-

//            |                 |  |      |                 |

//            |                        |  |      |             XOUT|-

//            |             SCL|<-+----->|P3.2/UCB0SCL     |

//            |                 |         |                 |

//

//  Attribute: Code modified from I2C multiple byte TX/RX Master example by

//  D. Dang

//  Texas Instruments Inc.

//

//  Code Made By :

//  Prof. Ravi Butani

//  Marwadi Education Foundation, Rajkot GUJARAT-INDIA

//  ravi.butani@marwadieducation.edu.in

//

//  Code Released under Creative Commons By-SA  license

//  Visit http://creativecommons.org/licenses/by-sa/3.0/deed.en_US  to know more about license

//  Built with CCS Version 5.1.0

//******************************************************************************

#include <msp430.h>

 

#define NUM_BYTES_TX 2                         // How many bytes?

#define NUM_BYTES_RX 6

#define ADXL_345     0x53

int RXByteCtr, RPT_Flag = 0,x1,y1,z1;       // enables repeated start when 1

volatile unsigned char RxBuffer[6];         // Allocate 6 byte of RAM

unsigned char *PRxData;                     // Pointer to RX data

unsigned char TXByteCtr, RX = 0;

unsigned char MSData[3];

 

void Setup_TX(unsigned char);

void Setup_RX(unsigned char);

void Transmit(unsigned char,unsigned char);

void Receive(void);

 

int main(void)

{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0

  P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0

  P1DIR |= BIT0;

 

  // Init sequence for ADXL345

  //Transmit process

    Setup_TX(ADXL_345);

    RPT_Flag = 1;

    Transmit(0x2D,0x00);

    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

 

   //Transmit process

     Setup_TX(ADXL_345);

     RPT_Flag = 1;

     Transmit(0x2D,0x10);

     while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

 

    //Transmit process

      Setup_TX(ADXL_345);

      RPT_Flag = 1;

      Transmit(0x2D,0x08);

      while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

 

      // Un-comment next block to change range of ADXL345

    /*

       Setup_TX(ADXL_345);

       RPT_Flag = 1;

       Transmit(0x31,0x01);                            // Range Select at add 0x31 write 0x00 for 2g(default)/ 0x01 for 4g/ 0x02 for 8g/ 0x03 for 16g

        while (UCB0CTL1 & UCTXSTP);         // Ensure stop condition got sent

    */

 

  while(1){

 

         //Transmit process

          Setup_TX(ADXL_345);

          RPT_Flag = 1;

          Transmit(0x32,0xFE);                                   // Request Data from ADXL345 in 2g Range 10Bit resolution

          while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

 

 

  //Receive process

  Setup_RX(ADXL_345);

  Receive();

  while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

 

  x1 = (((int)RxBuffer[1]) << 8) | RxBuffer[0];

  y1 = (((int)RxBuffer[3]) << 8) | RxBuffer[2];

  z1 = (((int)RxBuffer[5]) << 8) | RxBuffer[4];

 

  // now You have XYZ axis reading in x1,x2,x3 variable....Bingo... you can play with it as you like....

  // Below if sense x and y angle and Red led is on if its more then 45 or less then -45...

  // you can put your own condition here...

   if ((x1 > 128) || (y1 > 128) || (x1 < -128) || (y1 < -128))

         {

                P1OUT |= BIT0; // red led on

         }

 

         else

         {

                P1OUT &= ~BIT0; // red led off

         }

  __delay_cycles(10000);  // sample rate ~100 samples/sec

                                            // you can change by changing delay

  }

}

 

//-------------------------------------------------------------------------------

// The USCI_B0 data ISR is used to move received data from the I2C slave

// to the MSP430 memory. It is structured such that it can be used to receive

// any 2+ number of bytes by pre-loading RXByteCtr with the byte count.

//-------------------------------------------------------------------------------

#pragma vector = USCIAB0TX_VECTOR

__interrupt void USCIAB0TX_ISR(void)

{

  if(RX == 1){                              // Master Recieve?

  RXByteCtr--;                              // Decrement RX byte counter

  if (RXByteCtr)

  {

    *PRxData++ = UCB0RXBUF;                 // Move RX data to address PRxData

  }

  else

  {

    if(RPT_Flag == 0)

        UCB0CTL1 |= UCTXSTP;                // No Repeated Start: stop condition

      if(RPT_Flag == 1){                    // if Repeated Start: do nothing

        RPT_Flag = 0;

      }

    *PRxData = UCB0RXBUF;                   // Move final RX data to PRxData

    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0

  }}

 

  else{                                     // Master Transmit

      if (TXByteCtr)                        // Check TX byte counter

  {

    UCB0TXBUF = MSData[TXByteCtr];          // Load TX buffer

    TXByteCtr--;                            // Decrement TX byte counter

  }

  else

  {

    if(RPT_Flag == 1){

    RPT_Flag = 0;

    TXByteCtr = NUM_BYTES_TX;                // Load TX byte counter

    __bic_SR_register_on_exit(CPUOFF);

    }

    else{

    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition

    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag

    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0

    }

  }

 }

 

}

 

void Setup_TX(unsigned char Dev_ID){

  _DINT();

  RX = 0;

  IE2 &= ~UCB0RXIE; 

  while (UCB0CTL1 & UCTXSTP);               // Ensure stop condition got sent// Disable RX interrupt

  UCB0CTL1 |= UCSWRST;                      // Enable SW reset

  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode

  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset

  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz

  UCB0BR1 = 0;

  UCB0I2CSA = Dev_ID;                         // Slave Address is 048h

  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

  IE2 |= UCB0TXIE;                          // Enable TX interrupt

}

void Setup_RX(unsigned char Dev_ID){

  _DINT();

  RX = 1;

  IE2 &= ~UCB0TXIE; 

  UCB0CTL1 |= UCSWRST;                      // Enable SW reset

  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode

  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset

  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz

  UCB0BR1 = 0;

  UCB0I2CSA = Dev_ID;                       // Slave Address is 048h

  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

  IE2 |= UCB0RXIE;                          // Enable RX interrupt

}

void Transmit(unsigned char Reg_ADD,unsigned char Reg_DAT){

    MSData[2]= Reg_ADD;

       MSData[1]= Reg_DAT;

    TXByteCtr = NUM_BYTES_TX;                  // Load TX byte counter

    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition

    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

}

void Receive(void){

    PRxData = (unsigned char *)RxBuffer;    // Start of RX buffer

    RXByteCtr = NUM_BYTES_RX-1;             // Load RX byte counter

    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

    UCB0CTL1 |= UCTXSTT;                    // I2C start condition

    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

}

