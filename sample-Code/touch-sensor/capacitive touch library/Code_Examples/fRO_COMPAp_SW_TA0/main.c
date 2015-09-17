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
/*!
 *  This example is uses the MSP430F2132 to support the fRO_COMPAp_SW_TA0 
 *  implementation.  There are 7 elements, four are grouped to create a 
 *  slider while the remaining elements are used for discrete buttons. 
 *  
 *                                   MSP430F2132
 *                                +---------------+
 *                                | 
 *                             +--<P3.7 
 *                             |  
 *                             R  
 *                             |  
 *                         +---+-->P2.3/CA0
 *                         |   |  
 *                         R   R                
 *                         |   |  
 *                        GND  |
 *                             |  
 *  c-+-------------------+-R--+--<P1.0/CAOUT  
 *   |                        |
 *   | c-+---------------+-R--+ 
 *   |   |                    |
 *   |   | c-+-----------+-R--+ 
 *   |   |   |                |
 *   |   |   | c-+-------+-R--+  
 *   |   |   |   |            |
 *   |   |   |   | c-+-----R--+  
 *   |   |   |   |   |        |
 *   |   |   |   |   | c-+-R--+  
 *   |   |   |   |   |   |    |
 *   |   |   |   |   |   |    R
 *   |   |   |   |   |   |    |
 *   |   |   |   |   |   | c--+-->P2.7/CA7   (slider:2)
 *   |   |   |   |   |   +------->P2.6/CA6   (slider:1)
 *   |   |   |   |   +----------->P2.5/CA5   (slider:3)
 *   |   |   |   +--------------->P2.2/CA4   (menu:left)
 *   |   |   +------------------->P2.1/CA3   (menu: right)
 *   |   +----------------------->P2.0/CA2   (slider:0)
 *   +--------------------------->P2.4/CA1   (Power button)
 *
 *  The element and sensor definitions found in the configuration file 
 *  structure.c use designated initializer lists. This allows members to be 
 *  initialized in any order and also enhances the readability of the element
 *  being initialized.  
 *  This feature requires the GCC language extension found in Code Composer 
 *  Studio (CCS).  C99 is the default dialect found in IAR and therefore the 
 *  default settings can be used.
 */
#include "CTS_Layer.h"

uint16_t position;
struct Element * direction;
//unsigned int Cnt[3];

// Main Function
void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  
  // establish baseline
  TI_CAPT_Init_Baseline(&slider);
  TI_CAPT_Update_Baseline(&slider,5);
  TI_CAPT_Init_Baseline(&menu);
  TI_CAPT_Update_Baseline(&menu,5);
  TI_CAPT_Init_Baseline(&power);
  TI_CAPT_Update_Baseline(&power,5);


  // Main loop starts here
  while (1)
  {
    // TI_CAPT_Raw(&slider,Cnt);
	// TI_CAPT_Custom(&slider,Cnt);
    position = TI_CAPT_Slider(&slider);
	direction = (struct Element*)TI_CAPT_Buttons(&menu);
	if(TI_CAPT_Button(&power))
	{
	    __no_operation();
	}
	if(direction == (struct Element*)&right)
	{
	    __no_operation();
	}
	if(direction == (struct Element*)&left);
	{
	    __no_operation();
	}
    if(position != ILLEGAL_SLIDER_WHEEL_POSITION)   
    {
        __no_operation();
    }
    __delay_cycles(100); 
  }
} // End Main

