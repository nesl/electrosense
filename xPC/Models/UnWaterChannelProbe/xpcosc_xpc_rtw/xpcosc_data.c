/*
 * xpcosc_data.c
 *
 * Code generation for model "xpcosc.mdl".
 *
 * Model version              : 1.22
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Tue Jul 09 12:17:55 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "xpcosc.h"
#include "xpcosc_private.h"

/* Block parameters (auto storage) */
Parameters_xpcosc xpcosc_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */

  /*  Computed Parameter: PCI6221AD_P1_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: channel
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P2_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  0.0,                                 /* Expression: range
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P3_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  3.0,                                 /* Expression: coupling
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P4_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  5.0E-6,                              /* Expression: scantime
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P5_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  0.001,                               /* Expression: sampletime
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P6_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  -1.0,                                /* Expression: slot
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */

  /*  Computed Parameter: PCI6221AD_P7_Size
   * Referenced by: '<Root>/PCI-6221 AD'
   */
  { 1.0, 1.0 },
  20.0,                                /* Expression: boardType
                                        * Referenced by: '<Root>/PCI-6221 AD'
                                        */
  4.0,                                 /* Expression: 4
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  20.0,                                /* Expression: 20
                                        * Referenced by: '<Root>/Signal Generator'
                                        */

  /*  Computed Parameter: PCI6713DA_P1_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: channel
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */

  /*  Computed Parameter: PCI6713DA_P2_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  0.001,                               /* Expression: sampletime
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */

  /*  Computed Parameter: PCI6713DA_P3_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  -1.0,                                /* Expression: pcislot
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */

  /*  Computed Parameter: PCI6713DA_P4_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  1.0,                                 /* Expression: boardType
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */

  /*  Computed Parameter: PCI6713DA_P5_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  0.0,                                 /* Expression: reset
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */

  /*  Computed Parameter: PCI6713DA_P6_Size
   * Referenced by: '<Root>/PCI-6713 DA'
   */
  { 1.0, 1.0 },
  0.0,                                 /* Expression: initval
                                        * Referenced by: '<Root>/PCI-6713 DA'
                                        */
  1.0E+6,                              /* Expression: 1000^2
                                        * Referenced by: '<Root>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  400.0,                               /* Expression: 2*0.2*1000
                                        * Referenced by: '<Root>/Gain1'
                                        */
  1.0E+6                               /* Expression: 1000^2
                                        * Referenced by: '<Root>/Gain2'
                                        */
};
