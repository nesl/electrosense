/*
 * UnWaterChannelProbeTestSymmetry_dt.h
 *
 * Code generation for model "UnWaterChannelProbeTestSymmetry.mdl".
 *
 * Model version              : 1.83
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Fri Jun 28 15:44:20 2013
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
  { (char_T *)(&UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1), 0, 0, 23 }
  ,

  { (char_T *)(&UnWaterChannelProbeTestSymmetry_DWork.RandomSource_STATE_DWORK[0]),
    0, 0, 36 },

  { (char_T *)(&UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_PWORK), 11, 0,
    2 },

  { (char_T *)(&UnWaterChannelProbeTestSymmetry_DWork.RandomSource_SEED_DWORK),
    7, 0, 1 },

  { (char_T *)(&UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_IWORK[0]), 10,
    0, 45 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  5U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P1_Size[0]), 0, 0,
    65 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  1U,
  rtPTransitions
};

/* [EOF] UnWaterChannelProbeTestSymmetry_dt.h */
