/*
 * UnWaterChannelProbe3_capi.c
 *
 * Code generation for model "UnWaterChannelProbe3.mdl".
 *
 * Model version              : 1.123
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Thu Sep 12 14:52:22 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UnWaterChannelProbe3.h"
#include "rtw_capi.h"
#include "UnWaterChannelProbe3_private.h"

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

  { 5, 0, "Rate Transition",
    "", 0, 0, 0, 0, 0 },

  { 6, 0, "Rate Transition1",
    "", 0, 0, 0, 0, 0 },

  { 7, 0, "Rate Transition2",
    "", 0, 0, 0, 0, 0 },

  { 8, 0, "Rate Transition3",
    "", 0, 0, 0, 0, 0 },

  { 9, 0, "PCI-6220 AD1/p1",
    "", 0, 0, 0, 0, 0 },

  { 10, 0, "PCI-6220 AD1/p2",
    "", 1, 0, 0, 0, 0 },

  { 11, 0, "PCI-6220 AD1/p3",
    "", 2, 0, 0, 0, 0 },

  { 12, 0, "Random Source",
    "", 0, 0, 0, 0, 0 },

  { 13, 0, "Signal Generator1",
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
  { 14, "Gain",
    "Gain", 0, 0, 0 },

  { 15, "Gain1",
    "Gain", 0, 0, 0 },

  { 16, "Gain2",
    "Gain", 0, 0, 0 },

  { 17, "Gain3",
    "Gain", 0, 0, 0 },

  { 18, "PCI-6220 AD1",
    "P1", 0, 1, 0 },

  { 19, "PCI-6220 AD1",
    "P2", 0, 1, 0 },

  { 20, "PCI-6220 AD1",
    "P3", 0, 1, 0 },

  { 21, "PCI-6220 AD1",
    "P4", 0, 0, 0 },

  { 22, "PCI-6220 AD1",
    "P5", 0, 0, 0 },

  { 23, "PCI-6220 AD1",
    "P6", 0, 0, 0 },

  { 24, "PCI-6220 AD1",
    "P7", 0, 0, 0 },

  { 25, "PCI-6713 DA1",
    "P1", 0, 0, 0 },

  { 26, "PCI-6713 DA1",
    "P2", 0, 0, 0 },

  { 27, "PCI-6713 DA1",
    "P3", 0, 0, 0 },

  { 28, "PCI-6713 DA1",
    "P4", 0, 0, 0 },

  { 29, "PCI-6713 DA1",
    "P5", 0, 0, 0 },

  { 30, "PCI-6713 DA1",
    "P6", 0, 0, 0 },

  { 31, "Random Source",
    "MinRTP", 0, 0, 0 },

  { 32, "Random Source",
    "MaxRTP", 0, 0, 0 },

  { 33, "Signal Generator1",
    "Amplitude", 0, 0, 0 },

  { 34, "Signal Generator1",
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
  &UnWaterChannelProbe3_B.FromWorkspace,/* 0: Signal */
  &UnWaterChannelProbe3_B.Gain,        /* 1: Signal */
  &UnWaterChannelProbe3_B.Gain1,       /* 2: Signal */
  &UnWaterChannelProbe3_B.Gain2,       /* 3: Signal */
  &UnWaterChannelProbe3_B.Gain3,       /* 4: Signal */
  &UnWaterChannelProbe3_B.RateTransition,/* 5: Signal */
  &UnWaterChannelProbe3_B.RateTransition1,/* 6: Signal */
  &UnWaterChannelProbe3_B.RateTransition2,/* 7: Signal */
  &UnWaterChannelProbe3_B.RateTransition3,/* 8: Signal */
  &UnWaterChannelProbe3_B.PCI6220AD1_o1,/* 9: Signal */
  &UnWaterChannelProbe3_B.PCI6220AD1_o2,/* 10: Signal */
  &UnWaterChannelProbe3_B.PCI6220AD1_o3,/* 11: Signal */
  &UnWaterChannelProbe3_B.RandomSource,/* 12: Signal */
  &UnWaterChannelProbe3_B.SignalGenerator1,/* 13: Signal */
  &UnWaterChannelProbe3_P.Gain_Gain,   /* 14: Block Parameter */
  &UnWaterChannelProbe3_P.Gain1_Gain,  /* 15: Block Parameter */
  &UnWaterChannelProbe3_P.Gain2_Gain,  /* 16: Block Parameter */
  &UnWaterChannelProbe3_P.Gain3_Gain,  /* 17: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P1[0],/* 18: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P2[0],/* 19: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P3[0],/* 20: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P4,/* 21: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P5,/* 22: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P6,/* 23: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6220AD1_P7,/* 24: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P1,/* 25: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P2,/* 26: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P3,/* 27: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P4,/* 28: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P5,/* 29: Block Parameter */
  &UnWaterChannelProbe3_P.PCI6713DA1_P6,/* 30: Block Parameter */
  &UnWaterChannelProbe3_P.RandomSource_MinRTP,/* 31: Block Parameter */
  &UnWaterChannelProbe3_P.RandomSource_MaxRTP,/* 32: Block Parameter */
  &UnWaterChannelProbe3_P.SignalGenerator1_Amplitude,/* 33: Block Parameter */
  &UnWaterChannelProbe3_P.SignalGenerator1_Frequency/* 34: Block Parameter */
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
  3                                    /* 3 */
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
  { rtBlockSignals, 14 },

  { rtBlockParameters, 21,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void UnWaterChannelProbe3_InitializeDataMapInfo(rtModel_UnWaterChannelProbe3
  *UnWaterChannelProbe3_rtM
  )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(UnWaterChannelProbe3_rtM->DataMapInfo.mmi,
    rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(UnWaterChannelProbe3_rtM->DataMapInfo.mmi,
    rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, NULL);
  rtwCAPI_SetChildMMIArrayLen(UnWaterChannelProbe3_rtM->DataMapInfo.mmi, 0);
}

/* EOF: UnWaterChannelProbe3_capi.c */
