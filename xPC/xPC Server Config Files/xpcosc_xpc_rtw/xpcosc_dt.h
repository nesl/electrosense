/*
 * xpcosc_dt.h
 *
 * Code generation for model "xpcosc".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon May 13 14:42:33 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&xpcosc_B.Integrator1), 0, 0, 10 }
  ,

  { (char_T *)(&xpcosc_DW.RateTransition_Buffer0), 0, 0, 2 },

  { (char_T *)(&xpcosc_DW.PCI6220AD_PWORK), 11, 0, 1 },

  { (char_T *)(&xpcosc_DW.PCI6713DA_IWORK[0]), 10, 0, 44 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  4U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&xpcosc_P.Integrator1_IC), 0, 0, 47 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  1U,
  rtPTransitions
};

/* [EOF] xpcosc_dt.h */
