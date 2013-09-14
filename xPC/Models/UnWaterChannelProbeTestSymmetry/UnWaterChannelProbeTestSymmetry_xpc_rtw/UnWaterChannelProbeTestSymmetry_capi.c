/*
 * UnWaterChannelProbeTestSymmetry_capi.c
 *
 * Code generation for model "UnWaterChannelProbeTestSymmetry.mdl".
 *
 * Model version              : 1.97
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Mon Jul 15 14:46:02 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UnWaterChannelProbeTestSymmetry.h"
#include "rtw_capi.h"
#include "UnWaterChannelProbeTestSymmetry_private.h"

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, "From Workspace",
    "", 0, 0, 0, 0, 0 },

  { 1, 0, "Gain",
    "", 0, 0, 0, 0, 0 },

  { 2, 0, "Gain1",
    "", 0, 0, 0, 0, 0 },

  { 3, 0, "Gain2",
    "", 0, 0, 0, 0, 0 },

  { 4, 0, "Gain3",
    "", 0, 0, 0, 0, 0 },

  { 5, 0, "Gain4",
    "", 0, 0, 0, 0, 0 },

  { 6, 0, "Gain5",
    "", 0, 0, 0, 0, 0 },

  { 7, 0, "Gain6",
    "", 0, 0, 0, 0, 0 },

  { 8, 0, "Gain7",
    "", 0, 0, 0, 0, 0 },

  { 9, 0, "Rate Transition",
    "", 0, 0, 0, 0, 0 },

  { 10, 0, "Rate Transition1",
    "", 0, 0, 0, 0, 0 },

  { 11, 0, "Rate Transition2",
    "", 0, 0, 0, 0, 0 },

  { 12, 0, "Rate Transition3",
    "", 0, 0, 0, 0, 0 },

  { 13, 0, "Rate Transition4",
    "", 0, 0, 0, 0, 0 },

  { 14, 0, "Rate Transition5",
    "", 0, 0, 0, 0, 0 },

  { 15, 0, "Rate Transition6",
    "", 0, 0, 0, 0, 0 },

  { 16, 0, "Rate Transition7",
    "", 0, 0, 0, 0, 0 },

  { 17, 0, "PCI-6220 AD1/p1",
    "", 0, 0, 0, 0, 0 },

  { 18, 0, "PCI-6220 AD1/p2",
    "", 1, 0, 0, 0, 0 },

  { 19, 0, "PCI-6220 AD1/p3",
    "", 2, 0, 0, 0, 0 },

  { 20, 0, "PCI-6220 AD1/p4",
    "", 3, 0, 0, 0, 0 },

  { 21, 0, "PCI-6220 AD1/p5",
    "", 4, 0, 0, 0, 0 },

  { 22, 0, "PCI-6220 AD1/p6",
    "", 5, 0, 0, 0, 0 },

  { 23, 0, "PCI-6220 AD1/p7",
    "", 6, 0, 0, 0, 0 },

  { 24, 0, "Random Source",
    "", 0, 0, 0, 0, 0 },

  { 25, 0, "Signal Generator1",
    "", 0, 0, 0, 0, 1 },

  {
    0, 0, NULL, NULL, 0, 0, 0, 0, 0
  }
};

/* Tunable block parameters */
static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 26, "Gain",
    "Gain", 0, 0, 0 },

  { 27, "Gain1",
    "Gain", 0, 0, 0 },

  { 28, "Gain2",
    "Gain", 0, 0, 0 },

  { 29, "Gain3",
    "Gain", 0, 0, 0 },

  { 30, "Gain4",
    "Gain", 0, 0, 0 },

  { 31, "Gain5",
    "Gain", 0, 0, 0 },

  { 32, "Gain6",
    "Gain", 0, 0, 0 },

  { 33, "Gain7",
    "Gain", 0, 0, 0 },

  { 34, "PCI-6220 AD1",
    "P1", 0, 1, 0 },

  { 35, "PCI-6220 AD1",
    "P2", 0, 1, 0 },

  { 36, "PCI-6220 AD1",
    "P3", 0, 1, 0 },

  { 37, "PCI-6220 AD1",
    "P4", 0, 0, 0 },

  { 38, "PCI-6220 AD1",
    "P5", 0, 0, 0 },

  { 39, "PCI-6220 AD1",
    "P6", 0, 0, 0 },

  { 40, "PCI-6220 AD1",
    "P7", 0, 0, 0 },

  { 41, "PCI-6713 DA1",
    "P1", 0, 0, 0 },

  { 42, "PCI-6713 DA1",
    "P2", 0, 0, 0 },

  { 43, "PCI-6713 DA1",
    "P3", 0, 0, 0 },

  { 44, "PCI-6713 DA1",
    "P4", 0, 0, 0 },

  { 45, "PCI-6713 DA1",
    "P5", 0, 0, 0 },

  { 46, "PCI-6713 DA1",
    "P6", 0, 0, 0 },

  { 47, "Random Source",
    "MinRTP", 0, 0, 0 },

  { 48, "Random Source",
    "MaxRTP", 0, 0, 0 },

  { 49, "Signal Generator1",
    "Amplitude", 0, 0, 0 },

  { 50, "Signal Generator1",
    "Frequency", 0, 0, 0 },

  {
    0, NULL, NULL, 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, NULL, 0, 0, 0 }
};

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &UnWaterChannelProbeTestSymmetry_B.FromWorkspace,/* 0: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain,/* 1: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain1,/* 2: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain2,/* 3: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain3,/* 4: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain4,/* 5: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain5,/* 6: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain6,/* 7: Signal */
  &UnWaterChannelProbeTestSymmetry_B.Gain7,/* 8: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition,/* 9: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition1,/* 10: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition2,/* 11: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition3,/* 12: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition4,/* 13: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition5,/* 14: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition6,/* 15: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RateTransition7,/* 16: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1,/* 17: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o2,/* 18: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o3,/* 19: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o4,/* 20: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o5,/* 21: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o6,/* 22: Signal */
  &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o7,/* 23: Signal */
  &UnWaterChannelProbeTestSymmetry_B.RandomSource,/* 24: Signal */
  &UnWaterChannelProbeTestSymmetry_B.SignalGenerator1,/* 25: Signal */
  &UnWaterChannelProbeTestSymmetry_P.Gain_Gain,/* 26: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain1_Gain,/* 27: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain2_Gain,/* 28: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain3_Gain,/* 29: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain4_Gain,/* 30: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain5_Gain,/* 31: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain6_Gain,/* 32: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.Gain7_Gain,/* 33: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P1[0],/* 34: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P2[0],/* 35: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P3[0],/* 36: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P4,/* 37: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P5,/* 38: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P6,/* 39: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P7,/* 40: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P1,/* 41: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P2,/* 42: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P3,/* 43: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P4,/* 44: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P5,/* 45: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P6,/* 46: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.RandomSource_MinRTP,/* 47: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.RandomSource_MaxRTP,/* 48: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Amplitude,/* 49: Block Parameter */
  &UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Frequency/* 50: Block Parameter */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

/* Data Type Map - use dataTypeMapIndex to access this structure */
static const rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 }
};

/* Structure Element Map - use elemMapIndex to access this structure */
static const rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { NULL, 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  1,                                   /* 2 */
  7                                    /* 3 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.0001, 0.0
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { NULL, NULL, rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    1, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[1],
    0, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 26 },

  { rtBlockParameters, 25,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void UnWaterChannelProbeTestSymmetry_InitializeDataMapInfo
  (rtModel_UnWaterChannelProbeTestSymmetry *UnWaterChannelProbeTestSymmetry_rtM
   )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi,
                       &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap
    (UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi,
    rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap
    (UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo
    (UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi,
    NULL);
  rtwCAPI_SetChildMMIArrayLen
    (UnWaterChannelProbeTestSymmetry_rtM->DataMapInfo.mmi, 0);
}

/* EOF: UnWaterChannelProbeTestSymmetry_capi.c */
