/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//******************************************************************************
// RO_CSIO_TA0_RTC_One_Button_Compact example for MSP430FR4xx
// Touch the middle element to turn on/off the center button LED
// RO method capactiance measurement using CSIO, TimerA0, and RTC
//
//          Schematic Description: 
// 
//                         MSP430FR4xx
//                      +---------------+
//                      |               |
//        middle--------|P1.3        XIN|---+
//          up----------|P1.4           |   32Khz
//           right------|P1.5       XOUT|---+
//          down--------|P8.2
//                      |
//        left----------|P8.2
//                      |
//         LED----------|P8.1
// 
//        The RTC interval represents the measurement window.  The number of
//        counts within the TA0R that have accumulated during the measurement
//        window represents the capacitance of the element. This is lowest 
//        power option with either LPM3 (ACLK VLO source) or LPM0 (SMCLK
//        source).
//
// This is the preliminary code revised by Eric Fu
// 12 May, 2014
//******************************************************************************
#include "CTS_Layer.h"
#include "msp430.h"

// Uncomment to have this compiler directive run characterization functions only
// Comment to have this compiler directive run example application
//#define ELEMENT_CHARACTERIZATION_MODE

//Revised for Gradon
#define DELAY 3276 		// Timer delay timeout count - 3277/32768 = 100 msec


// Sensor settings
#define KEY_lvl     50             // Defines the min count for a "key press"
                                    // Set to ~ half the max delta expected
// Global variables for sensing
unsigned int base_cnt;
unsigned int meas_cnt;
unsigned int delta_cnt;

char key_pressed, key_loc;
int cycles;


// Sleep Function
// Configures Timer A to run off ACLK, count in UP mode, places the CPU in LPM3 
// and enables the interrupt vector to jump to ISR upon timeout 
void sleep(unsigned int time)
{
    TA0CCR0 = time;
    TA0CTL = TASSEL__ACLK + MC__UP + TACLR;
    TA0CCTL0 &= ~CCIFG;
    TA0CCTL0 = CCIE;
    __bis_SR_register(LPM3_bits+GIE);
    __no_operation();

}

// Main Function
void main(void)
{ 

	 // Initialize System Clocks
 WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

	  //Clock Setting
  CSCTL1 &= ~(DCORSEL_7);                 // Clear DCO frequency select bits first
  CSCTL1 |= DCORSEL_3;                    // Set DCO = 8MHz
  CSCTL2 = FLLD_0 + 243;                  // DCODIV = 8MHz
  CSCTL3 |= SELREF__XT1CLK;              // Set REFO as FLL reference source
  CSCTL4 = SELMS__DCOCLKDIV | SELREF__XT1CLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
	                                              // default DCODIV as MCLK and SMCLK source
  CSCTL5 |= DIVM_0 | DIVS_0;              // SMCLK = MCLK = DCODIV = 8MHz

  // Initializing GPIO
  P8DIR |= BIT1;                         //Set the pin controlling the center LED P8.1  as output pin
  PM5CTL0 &= ~LOCKLPM5;

  // Initialize Baseline measurement
  int i = 0;
  TI_CAPT_Raw(&middle_button,&base_cnt);
  for( i = 0; i < 100; i++)
  {
      TI_CAPT_Raw(&middle_button,&meas_cnt);
      base_cnt += meas_cnt;
      base_cnt /= 2;
  }

   // Main loop starts here
   while (1)
   {
   	  // Take raw delta measurement
       TI_CAPT_Raw(&middle_button,&meas_cnt);

 #ifndef fRO_CSIO_TA2_TA3
       if(base_cnt < meas_cnt)
       // Handle baseline measurment for a base C decrease
       {                             // beyond baseline, i.e. cap decreased
           base_cnt = (base_cnt+meas_cnt) >> 1; // Re-average baseline up quickly
           delta_cnt = 0;            // Zero out delta for position determination
       }
       else
       {
           delta_cnt = base_cnt - meas_cnt;  // Calculate delta: c_change
       }
 #endif

 #ifdef fRO_CSIO_TA2_TA3
       if(base_cnt > meas_cnt)
       // Handle baseline measurment for a base C decrease
       {                             // beyond baseline, i.e. cap decreased
           base_cnt = (base_cnt+meas_cnt) >> 1; // Re-average baseline up quickly
           delta_cnt = 0;            // Zero out delta for position determination
       }
       else
       {
           delta_cnt = meas_cnt - base_cnt;  // Calculate delta: c_change
       }
 #endif
       /* Determine if each key is pressed per a preset threshold */
       if (delta_cnt > KEY_lvl)
       {
         // turn on LED
         P8OUT |= BIT1;
       }
       else
       {
         // turn off LED
         base_cnt = base_cnt - 1;  // Adjust baseline down, should be slow to
         P8OUT &= ~BIT1;
       }

     // Put the MSP430 into LPM3 for a certain DELAY period
     sleep(DELAY);

   }
} // End Main

/******************************************************************************/
// Timer0_A0 Interrupt Service  Routine: Disables the timer and exists LPM3
/******************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void ISR_Timer0_A0(void)
{
  TA0CTL &= ~(MC_1);
  TA0CCTL0 &= ~(CCIE);
  __bic_SR_register_on_exit(LPM3_bits+GIE);
}

#pragma vector = LCD_E_VECTOR, PORT2_VECTOR, PORT1_VECTOR, ADC_VECTOR, USCI_B0_VECTOR,USCI_A0_VECTOR,\
	WDT_VECTOR, /*RTC_VECTOR,*/TIMER1_A1_VECTOR, TIMER1_A0_VECTOR, TIMER0_A1_VECTOR, /*TIMER0_A0_VECTOR,*/\
	UNMI_VECTOR, SYSNMI_VECTOR
__interrupt void ISR_trap(void)
{
  // the following will cause an access violation which results in a SW BOR
    PMMCTL0 = PMMPW | PMMSWBOR;
}
