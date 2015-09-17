/*----------------------------------------------------------------------
  File Name          : 
  Author             : MPD Application Team
  Version            : V0.0.1
  Date               : 12/14/2011
  Description        : 
  File ID            : $Id: xl362_io_pic.c,v 1.1.1.1 2012/01/10 15:18:18 jlee11 Exp $

  Analog Devices ADXL 345 digital output accellerometer 
  with advanced digital features.

  (c) 2008 Analog Devices application support team.
  xxx@analog.com

  ----------------------------------------------------------------------

  The present firmware which is for guidance only aims at providing
  customers with coding information regarding their products in order
  for them to save time.  As a result, Analog Devices shall not be
  held liable for any direct, indirect or consequential damages with
  respect to any claims arising from the content of such firmware and/or
  the use made by customers of the coding information contained herein
  in connection with their products.

----------------------------------------------------------------------*/
#include <pic.h>
#include "XL362.h"

// defines needed for the spi code configuration
#define BITNUM(adr, bit)       ((unsigned)(&adr)*8+(bit))
static bit CSN       @ BITNUM(PORTB,3);   //-- The CSN output pin
static bit CSN_TRIS  @ BITNUM(TRISB,3);   //-- The CSN Direction Register Bit
static bit SCLK      @ BITNUM(PORTB,2);   //-- The SCLK output pin
static bit SCLK_TRIS @ BITNUM(TRISB,2);   //-- The SCLK Direction Register Bit
static bit MOSI      @ BITNUM(PORTB,1);   //-- The MOSI input pin
static bit MOSI_TRIS @ BITNUM(TRISB,1);   //-- The MOSI Direction Register Bit
static bit MISO      @ BITNUM(PORTB,0);   //-- The MISO output pin
static bit MISO_TRIS @ BITNUM(TRISB,0);   //-- The MISO Direction Register Bit

/* -- local functions -- */
void spidelay(void);
void spistart(void);
void spistop(void);
char xfer_byte(char byte_out);

void xl362Write(unsigned char count, unsigned char regaddr, unsigned char *buf){
  char mybyte;
  spistart();
  mybyte = xfer_byte(XL362_REG_WRITE);
  mybyte = xfer_byte(regaddr);
  while(count--) {
    mybyte = xfer_byte(*buf);
    buf++;
  }
  spistop();
}

void xl362Read(unsigned char count, unsigned char regaddr, unsigned char *buf){
  /* send I2c start and the slave address, the the register address */
  char mybyte;
  spistart();
  mybyte = xfer_byte(XL362_REG_READ);
  mybyte = xfer_byte(regaddr);
  while(count--) {
    *buf = xfer_byte(0);
    buf++;
  }
  spistop();
}

void xl362FifoRead(unsigned int count, unsigned char *buf){
  /* send I2c start and the slave address, the the register address */
  char mybyte;
  spistart();
  mybyte = xfer_byte(XL362_FIFO_READ);
  while(count--) {
    *buf = xfer_byte(0);
    buf++;
  }
  spistop();
}

/* -- utility routines -- */
void spidelay(){
  char delay =1;
 while(--delay != 0)continue;
}
void spistart() {
  SCLK = 0;
  SCLK_TRIS = 0; // output
  CSN = 0;
  CSN_TRIS  = 0; // output
  MISO_TRIS = 1; // input
  MOSI_TRIS = 0; // output
  spidelay();
}
void spistop() {
  CSN=1;
  spidelay();
}

char xfer_byte(char byte_out) {
  char count;
  char byte_in =0;
  for(count=8;count>0;count--) {
    if(byte_out & 0x80) {
      MOSI = 1;
    } else{
      MOSI = 0;
    }
    spidelay();
    byte_out = byte_out <<1;
    byte_in = byte_in <<1;
    SCLK = 1;
    if(MISO) byte_in +=1;
    spidelay();
    SCLK = 0;
  }
  return(byte_in);
}
/* --------------- end -------------------- */
