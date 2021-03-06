/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 /*
 * structure.c
 *  RO_COMPB_TA1_WDTA example with 12 elements on the MSP430F5529.  
 * 
 *                                                         MSP430F5529
 *                                     +---------------+
 *                                     | 
 *   c-+-------------------------R--+--<P1.6/TA1CLK/CBOUT  
 *     |                            |
 *     | c-+---------------------R--+  
 *     |   |                        |
 *     |   |  c-+----------------R--+  
 *     |   |    |                   |
 *                     ...
 *     |   |    |                   |
 *     |   |    |    c-+---------R--+  
 *     |   |    |      |            |
 *     |   |    |      | c-+-----R--+  
 *     |   |    |      |   |        |
 *     |   |    |      |   | c-+-R--+                               
 *     |   |    |      |   |   |
 *     |   |    |      |   |   +------->CB0
 *     |   |    |      |   +----------->CB1
 *     |   |    |      +--------------->CB2
 *     |   |    |
 *                    ...
 *     |   |    |
 *     |   |    +---------------------->CB9
 *     |   +--------------------------->CB10
 *     +------------------------------->CB11
 */

#include "structure.h"

// Actual demo structures
const struct Element element0 = {   //CB0
              .inputBits = CBIMSEL_0,
              .maxResponse = 250,
              .threshold = 125
};
const struct Element element1 = {   //CB1
              .inputBits = CBIMSEL_1,
              .maxResponse = 390,
              .threshold = 195
};
const struct Element element2 = {   //CB2
              .inputBits = CBIMSEL_2,
              .maxResponse = 340,
              .threshold = 170
};
const struct Element element3 = {   //CB3
              .inputBits = CBIMSEL_3,
              .maxResponse = 500,
              .threshold = 230
};
const struct Element element4 = {   //CB4
              .inputBits = CBIMSEL_4,
              .maxResponse = 400,
              .threshold = 200
};
const struct Element element5 = {   //CB5
              .inputBits = CBIMSEL_5,
              .maxResponse = 250,
              .threshold = 125
};
const struct Element element6 = {   //CB6
              .inputBits = CBIMSEL_6,
              .maxResponse = 390,
              .threshold = 195
};
const struct Element element7 = {   //CB7
              .inputBits = CBIMSEL_7,
              .maxResponse = 340,
              .threshold = 170
};
const struct Element element8 = {   //CB8
              .inputBits = CBIMSEL_8,
              .maxResponse = 500,
              .threshold = 230
};
const struct Element element9 = {   //CB9
              .inputBits = CBIMSEL_9,
              .maxResponse = 400,
              .threshold = 200
};
const struct Element elementA = {   //CB10
              .inputBits = CBIMSEL_10,
              .maxResponse = 340,
              .threshold = 170
};
const struct Element elementB = {   //CB11
              .inputBits = CBIMSEL_11,
              .maxResponse = 500,
              .threshold = 230
};


//*** Sensor        *******************************************************/
// This defines the grouping of sensors, the method to measure change in
// capacitance, and the function of the group

const struct Sensor keypad =
               { 
                  .halDefinition = RO_COMPB_TA1_WDTA,
                  .numElements = 5,
                  .baseOffset = 0,
                  .cbpdBits = 0x0FFF, //CB0,CB1,...CB11
                  // Pointer to elements
                  .arrayPtr[0] = &element0,  // point to first element 
                  .arrayPtr[1] = &element1,    
                  .arrayPtr[2] = &element2,  
                  .arrayPtr[3] = &element3, 
                  .arrayPtr[4] = &element4,  
                  .arrayPtr[5] = &element5,  // point to first element 
                  .arrayPtr[6] = &element6,    
                  .arrayPtr[7] = &element7,  
                  .arrayPtr[8] = &element8, 
                  .arrayPtr[9] = &element9,    
				  .arrayPtr[10] = &elementA, 
                  .arrayPtr[11] = &elementB,    
 
                  .cboutTAxDirRegister = (uint8_t *)&P1DIR,  // PxDIR
                  .cboutTAxSelRegister = (uint8_t *)&P1SEL,  // PxSEL
                  .cboutTAxBits = BIT6, // P1.6
                  // Timer Information
                  .measGateSource= GATE_WDTA_ACLK,     //  0->SMCLK, 1-> ACLK
                  .accumulationCycles= WDTA_GATE_512  //
               };

