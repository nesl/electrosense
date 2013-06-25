/*
 * UnWaterChannelProbe3_data.c
 *
 * Code generation for model "UnWaterChannelProbe3.mdl".
 *
 * Model version              : 1.78
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Wed Jun 19 16:37:21 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UnWaterChannelProbe3.h"
#include "UnWaterChannelProbe3_private.h"

/* Block parameters (auto storage) */
Parameters_UnWaterChannelProbe3 UnWaterChannelProbe3_P = {
  /*  Computed Parameter: PCI6220AD1_P1_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 3.0 },

  /*  Expression: channel
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 2.0, 3.0 },

  /*  Computed Parameter: PCI6220AD1_P2_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 3.0 },

  /*  Expression: range
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 0.0, 0.0, 0.0 },

  /*  Computed Parameter: PCI6220AD1_P3_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 3.0 },

  /*  Expression: coupling
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 3.0, 3.0, 3.0 },

  /*  Computed Parameter: PCI6220AD1_P4_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  5.0E-6,                              /* Expression: scantime
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

  /*  Computed Parameter: PCI6220AD1_P5_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  0.0001,                              /* Expression: sampletime
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

  /*  Computed Parameter: PCI6220AD1_P6_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  -1.0,                                /* Expression: slot
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

  /*  Computed Parameter: PCI6220AD1_P7_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  20.0,                                /* Expression: boardType
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain3'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<Root>/Signal Generator1'
                                        */
  500.0,                               /* Expression: 500
                                        * Referenced by: '<Root>/Signal Generator1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P1_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: channel
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P2_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  0.0001,                              /* Expression: sampletime
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P3_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  -1.0,                                /* Expression: pcislot
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P4_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: boardType
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P5_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  0.0,                                 /* Expression: reset
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */

  /*  Computed Parameter: PCI6713DA1_P6_Size
   * Referenced by: '<Root>/PCI-6713 DA1'
   */
  { 1.0, 1.0 },
  0.0,                                 /* Expression: initval
                                        * Referenced by: '<Root>/PCI-6713 DA1'
                                        */
  0.0,                                 /* Expression: MinVal
                                        * Referenced by: '<Root>/Random Source'
                                        */
  4.0,                                 /* Expression: MaxVal
                                        * Referenced by: '<Root>/Random Source'
                                        */
  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/Gain1'
                                        */
};
