/*
 * xpcosc_capi.c
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

#include "xpcosc.h"
#include "rtw_capi.h"
#include "xpcosc_private.h"

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, "Gain",
    "", 0, 0, 0, 0, 0 },

  { 1, 0, "Gain1",
    "", 0, 0, 0, 0, 0 },

  { 2, 0, "Gain2",
    "", 0, 0, 0, 0, 0 },

  { 3, 0, "Integrator",
    "", 0, 0, 0, 0, 0 },

  { 4, 0, "Integrator1",
    "", 0, 0, 0, 0, 0 },

  { 5, 0, "Rate Transition",
    "", 0, 0, 0, 0, 1 },

  { 6, 0, "Rate Transition1",
    "", 0, 0, 0, 0, 2 },

  { 7, 0, "PCI-6220 AD",
    "", 0, 0, 0, 0, 2 },

  { 8, 0, "Signal Generator",
    "", 0, 0, 0, 0, 0 },

  { 9, 0, "Sum",
    "", 0, 0, 0, 0, 0 },

  {
    0, 0, NULL, NULL, 0, 0, 0, 0, 0
  }
};

/* Tunable block parameters */
static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 10, "Gain",
    "Gain", 0, 0, 0 },

  { 11, "Gain1",
    "Gain", 0, 0, 0 },

  { 12, "Gain2",
    "Gain", 0, 0, 0 },

  { 13, "Integrator",
    "InitialCondition", 0, 0, 0 },

  { 14, "Integrator1",
    "InitialCondition", 0, 0, 0 },

  { 15, "Rate Transition",
    "X0", 0, 0, 0 },

  { 16, "PCI-6220 AD",
    "P1", 0, 0, 0 },

  { 17, "PCI-6220 AD",
    "P2", 0, 0, 0 },

  { 18, "PCI-6220 AD",
    "P3", 0, 0, 0 },

  { 19, "PCI-6220 AD",
    "P4", 0, 0, 0 },

  { 20, "PCI-6220 AD",
    "P5", 0, 0, 0 },

  { 21, "PCI-6220 AD",
    "P6", 0, 0, 0 },

  { 22, "PCI-6220 AD",
    "P7", 0, 0, 0 },

  { 23, "PCI-6713 DA",
    "P1", 0, 0, 0 },

  { 24, "PCI-6713 DA",
    "P2", 0, 0, 0 },

  { 25, "PCI-6713 DA",
    "P3", 0, 0, 0 },

  { 26, "PCI-6713 DA",
    "P4", 0, 0, 0 },

  { 27, "PCI-6713 DA",
    "P5", 0, 0, 0 },

  { 28, "PCI-6713 DA",
    "P6", 0, 0, 0 },

  { 29, "Signal Generator",
    "Amplitude", 0, 0, 0 },

  { 30, "Signal Generator",
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
  &xpcosc_B.Gain,                      /* 0: Signal */
  &xpcosc_B.Gain1,                     /* 1: Signal */
  &xpcosc_B.Gain2,                     /* 2: Signal */
  &xpcosc_B.Integrator,                /* 3: Signal */
  &xpcosc_B.Integrator1,               /* 4: Signal */
  &xpcosc_B.RateTransition,            /* 5: Signal */
  &xpcosc_B.RateTransition1,           /* 6: Signal */
  &xpcosc_B.PCI6220AD,                 /* 7: Signal */
  &xpcosc_B.SignalGenerator,           /* 8: Signal */
  &xpcosc_B.Sum,                       /* 9: Signal */
  &xpcosc_P.Gain_Gain,                 /* 10: Block Parameter */
  &xpcosc_P.Gain1_Gain,                /* 11: Block Parameter */
  &xpcosc_P.Gain2_Gain,                /* 12: Block Parameter */
  &xpcosc_P.Integrator_IC,             /* 13: Block Parameter */
  &xpcosc_P.Integrator1_IC,            /* 14: Block Parameter */
  &xpcosc_P.RateTransition_X0,         /* 15: Block Parameter */
  &xpcosc_P.PCI6220AD_P1,              /* 16: Block Parameter */
  &xpcosc_P.PCI6220AD_P2,              /* 17: Block Parameter */
  &xpcosc_P.PCI6220AD_P3,              /* 18: Block Parameter */
  &xpcosc_P.PCI6220AD_P4,              /* 19: Block Parameter */
  &xpcosc_P.PCI6220AD_P5,              /* 20: Block Parameter */
  &xpcosc_P.PCI6220AD_P6,              /* 21: Block Parameter */
  &xpcosc_P.PCI6220AD_P7,              /* 22: Block Parameter */
  &xpcosc_P.PCI6713DA_P1,              /* 23: Block Parameter */
  &xpcosc_P.PCI6713DA_P2,              /* 24: Block Parameter */
  &xpcosc_P.PCI6713DA_P3,              /* 25: Block Parameter */
  &xpcosc_P.PCI6713DA_P4,              /* 26: Block Parameter */
  &xpcosc_P.PCI6713DA_P5,              /* 27: Block Parameter */
  &xpcosc_P.PCI6713DA_P6,              /* 28: Block Parameter */
  &xpcosc_P.SignalGenerator_Amplitude, /* 29: Block Parameter */
  &xpcosc_P.SignalGenerator_Frequency  /* 30: Block Parameter */
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
  { rtwCAPI_SCALAR, 0, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1                                    /* 1 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.0, 0.00025, 0.001
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { NULL, NULL, rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[0],
    0, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[0],
    1, 0 },

  { (const void *) &rtcapiStoredFloats[2], (const void *) &rtcapiStoredFloats[0],
    2, 0 }
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
  { rtBlockSignals, 10 },

  { rtBlockParameters, 21,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void xpcosc_InitializeDataMapInfo(rtModel_xpcosc_T *xpcosc_rtM
  )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(xpcosc_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(xpcosc_rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(xpcosc_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(xpcosc_rtM->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(xpcosc_rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache C-API rtp Address and size  into the Real-Time Model Data structure */
  xpcosc_rtM->DataMapInfo.mmi.InstanceMap.rtpAddress = rtmGetDefaultParam
    (xpcosc_rtM);
  xpcosc_rtM->DataMapInfo.mmi.staticMap->rtpSize = sizeof(P_xpcosc_T);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(xpcosc_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(xpcosc_rtM->DataMapInfo.mmi, NULL);
  rtwCAPI_SetChildMMIArrayLen(xpcosc_rtM->DataMapInfo.mmi, 0);
}

/* EOF: xpcosc_capi.c */
