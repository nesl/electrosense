/*
 * UnWaterChannelProbe_data.c
 *
 * Code generation for model "UnWaterChannelProbe.mdl".
 *
 * Model version              : 1.43
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Tue May 14 17:10:03 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UnWaterChannelProbe.h"
#include "UnWaterChannelProbe_private.h"

/* Block parameters (auto storage) */
Parameters_UnWaterChannelProbe UnWaterChannelProbe_P = {
  /*  Computed Parameter: PCI6220AD1_P1_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: channel
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

  /*  Computed Parameter: PCI6220AD1_P2_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  4.0,                                 /* Expression: range
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

  /*  Computed Parameter: PCI6220AD1_P3_Size
   * Referenced by: '<Root>/PCI-6220 AD1'
   */
  { 1.0, 1.0 },
  3.0,                                 /* Expression: coupling
                                        * Referenced by: '<Root>/PCI-6220 AD1'
                                        */

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
  1.0,                                 /* Expression: MaxVal
                                        * Referenced by: '<Root>/Random Source'
                                        */
  0.25,                                /* Expression: 0.25
                                        * Referenced by: '<Root>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Signal Generator1'
                                        */
  1000.0                               /* Expression: 1e3
                                        * Referenced by: '<Root>/Signal Generator1'
                                        */
};
