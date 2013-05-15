/*
 * UnWaterChannelProbe.c
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

#include "rt_logging_mmi.h"
#include "UnWaterChannelProbe_capi.h"
#include "UnWaterChannelProbe.h"
#include "UnWaterChannelProbe_private.h"
#include <stdio.h>
#include "UnWaterChannelProbe_dt.h"

/* Block signals (auto storage) */
BlockIO_UnWaterChannelProbe UnWaterChannelProbe_B;

/* Block states (auto storage) */
D_Work_UnWaterChannelProbe UnWaterChannelProbe_DWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_UnWaterChannelProbe UnWaterChannelProbe_Y;

/* Real-time model */
rtModel_UnWaterChannelProbe UnWaterChannelProbe_rtM_;
rtModel_UnWaterChannelProbe *const UnWaterChannelProbe_rtM =
  &UnWaterChannelProbe_rtM_;
void RandSrcInitState_U_64(const uint32_T seed[], real_T state[], int32_T nChans)
{
  int32_T i;
  uint32_T j;
  int32_T k;
  int32_T n;
  real_T d;

  /* Start for S-Function (sdsprandsrc2): '<Root>/Random Source' */
  /* RandSrcInitState_U_64 */
  for (i = 0; i < nChans; i++) {
    j = seed[i] != 0U ? seed[i] : 2147483648U;
    state[35 * i + 34] = (real_T)j;
    for (k = 0; k < 32; k++) {
      d = 0.0;
      for (n = 0; n < 53; n++) {
        j ^= j << 13;
        j ^= j >> 17;
        j ^= j << 5;
        d = (real_T)((int32_T)(j >> 19) & 1) + (d + d);
      }

      state[35 * i + k] = ldexp(d, -53);
    }

    state[35 * i + 32] = 0.0;
    state[35 * i + 33] = 0.0;
  }

  /* End of S-Function (sdsprandsrc2): '<Root>/Random Source' */
}

void RandSrc_U_D(real_T y[], const real_T minVec[], int32_T minLen, const real_T
                 maxVec[], int32_T maxLen, real_T state[], int32_T nChans,
                 int32_T nSamps)
{
  int32_T one;
  int32_T lsw;
  int8_T (*onePtr)[];
  int32_T chan;
  real_T min;
  real_T max;
  int32_T samps;
  real_T d;
  int32_T i;
  uint32_T j;

  /* Start for S-Function (sdsprandsrc2): '<Root>/Random Source' */
  /* RandSrc_U_D */
  one = 1;
  onePtr = (int8_T (*)[])&one;
  lsw = ((*onePtr)[0U] == 0);
  for (chan = 0; chan < nChans; chan++) {
    min = minVec[minLen > 1 ? chan : 0];
    max = maxVec[maxLen > 1 ? chan : 0];
    max -= min;
    d = state[chan * 35 + 33];
    i = (int32_T)((uint32_T)d & 31U);
    d = state[chan * 35 + 34];
    j = (uint32_T)d;
    for (samps = 0; samps < nSamps; samps++) {
      /* "Subtract with borrow" generator */
      d = state[((i + 20) & 31) + chan * 35];
      d -= state[((i + 5) & 31) + chan * 35];
      d -= state[chan * 35 + 32];
      if (d >= 0.0) {
        state[chan * 35 + 32] = 0.0;
      } else {
        d++;

        /* set 1 in LSB */
        state[chan * 35 + 32] = 1.1102230246251565E-16;
      }

      state[chan * 35 + i] = d;
      i = (i + 1) & 31;

      /* XOR with shift register sequence */
      (*(int32_T (*)[])&d)[lsw] ^= (int32_T)j;
      j ^= j << 13;
      j ^= j >> 17;
      j ^= j << 5;
      (*(int32_T (*)[])&d)[lsw ^ 1] ^= (int32_T)(j & 1048575U);
      y[chan * nSamps + samps] = max * d + min;
    }

    state[chan * 35 + 33] = (real_T)i;
    state[chan * 35 + 34] = (real_T)j;
  }

  /* End of S-Function (sdsprandsrc2): '<Root>/Random Source' */
}

void RandSrcCreateSeeds_64(uint32_T initSeed, uint32_T seedArray[], int32_T
  numSeeds)
{
  real_T state[35];
  real_T tmp;
  real_T min;
  real_T max;
  int32_T i;
  real_T tmp_0;

  /* Start for S-Function (sdsprandsrc2): '<Root>/Random Source' */
  /* RandSrcCreateSeeds_64 */
  min = 0.0;
  max = 1.0;
  RandSrcInitState_U_64(&initSeed, state, 1);
  for (i = 0; i < numSeeds; i++) {
    RandSrc_U_D(&tmp, &min, 1, &max, 1, state, 1, 1);
    tmp_0 = tmp * 2.147483648E+9;
    seedArray[i] = (uint32_T)tmp_0;
  }

  /* End of S-Function (sdsprandsrc2): '<Root>/Random Source' */
}

/* Model output function */
void UnWaterChannelProbe_output(int_T tid)
{
  real_T temp;

  /* Level2 S-Function Block: '<Root>/PCI-6220 AD1' (adnipcim) */
  {
    SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[0];
    sfcnOutputs(rts, 1);
  }

  /* RateTransition: '<Root>/Rate Transition1' */
  UnWaterChannelProbe_B.RateTransition1 = UnWaterChannelProbe_B.PCI6220AD1;

  /* Gain: '<Root>/Gain' */
  UnWaterChannelProbe_B.Gain = UnWaterChannelProbe_P.Gain_Gain *
    UnWaterChannelProbe_B.RateTransition1;

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T t = UnWaterChannelProbe_rtM->Timing.t[1];
    real_T *pTimeValues = (real_T *)
      UnWaterChannelProbe_DWork.FromWorkspace_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      UnWaterChannelProbe_DWork.FromWorkspace_PWORK.DataPtr;
    if (t < pTimeValues[0]) {
      UnWaterChannelProbe_B.FromWorkspace = 0.0;
    } else if (t == pTimeValues[999]) {
      UnWaterChannelProbe_B.FromWorkspace = pDataValues[999];
    } else if (t > pTimeValues[999]) {
      UnWaterChannelProbe_B.FromWorkspace = 0.0;
    } else {
      int_T currTimeIndex =
        UnWaterChannelProbe_DWork.FromWorkspace_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }

      UnWaterChannelProbe_B.FromWorkspace = pDataValues[currTimeIndex];
      UnWaterChannelProbe_DWork.FromWorkspace_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* Outport: '<Root>/Outport' */
  UnWaterChannelProbe_Y.Outport[0] = UnWaterChannelProbe_B.Gain;
  UnWaterChannelProbe_Y.Outport[1] = UnWaterChannelProbe_B.FromWorkspace;

  /* RateTransition: '<Root>/Rate Transition' */
  UnWaterChannelProbe_B.RateTransition = UnWaterChannelProbe_B.FromWorkspace;

  /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
  {
    SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[1];
    sfcnOutputs(rts, 1);
  }

  /* ok to acquire for <S1>/S-Function */
  UnWaterChannelProbe_DWork.SFunction_IWORK.AcquireOK = 1;

  /* S-Function (sdsprandsrc2): '<Root>/Random Source' */
  RandSrc_U_D(&UnWaterChannelProbe_B.RandomSource,
              &UnWaterChannelProbe_P.RandomSource_MinRTP, 1,
              &UnWaterChannelProbe_P.RandomSource_MaxRTP, 1,
              UnWaterChannelProbe_DWork.RandomSource_STATE_DWORK, 1, 1);

  /* Gain: '<Root>/Gain1' */
  UnWaterChannelProbe_B.Gain1 = UnWaterChannelProbe_P.Gain1_Gain *
    UnWaterChannelProbe_B.RandomSource;

  /* SignalGenerator: '<Root>/Signal Generator1' */
  temp = UnWaterChannelProbe_P.SignalGenerator1_Frequency *
    UnWaterChannelProbe_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    UnWaterChannelProbe_B.SignalGenerator1 =
      UnWaterChannelProbe_P.SignalGenerator1_Amplitude;
  } else {
    UnWaterChannelProbe_B.SignalGenerator1 =
      -UnWaterChannelProbe_P.SignalGenerator1_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator1' */

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void UnWaterChannelProbe_update(int_T tid)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++UnWaterChannelProbe_rtM->Timing.clockTick0)) {
    ++UnWaterChannelProbe_rtM->Timing.clockTickH0;
  }

  UnWaterChannelProbe_rtM->Timing.t[0] =
    UnWaterChannelProbe_rtM->Timing.clockTick0 *
    UnWaterChannelProbe_rtM->Timing.stepSize0 +
    UnWaterChannelProbe_rtM->Timing.clockTickH0 *
    UnWaterChannelProbe_rtM->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++UnWaterChannelProbe_rtM->Timing.clockTick1)) {
      ++UnWaterChannelProbe_rtM->Timing.clockTickH1;
    }

    UnWaterChannelProbe_rtM->Timing.t[1] =
      UnWaterChannelProbe_rtM->Timing.clockTick1 *
      UnWaterChannelProbe_rtM->Timing.stepSize1 +
      UnWaterChannelProbe_rtM->Timing.clockTickH1 *
      UnWaterChannelProbe_rtM->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void UnWaterChannelProbe_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)UnWaterChannelProbe_rtM, 0,
                sizeof(rtModel_UnWaterChannelProbe));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&UnWaterChannelProbe_rtM->solverInfo,
                          &UnWaterChannelProbe_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&UnWaterChannelProbe_rtM->solverInfo, &rtmGetTPtr
                (UnWaterChannelProbe_rtM));
    rtsiSetStepSizePtr(&UnWaterChannelProbe_rtM->solverInfo,
                       &UnWaterChannelProbe_rtM->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&UnWaterChannelProbe_rtM->solverInfo,
                          (&rtmGetErrorStatus(UnWaterChannelProbe_rtM)));
    rtsiSetRTModelPtr(&UnWaterChannelProbe_rtM->solverInfo,
                      UnWaterChannelProbe_rtM);
  }

  rtsiSetSimTimeStep(&UnWaterChannelProbe_rtM->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&UnWaterChannelProbe_rtM->solverInfo,"FixedStepDiscrete");
  UnWaterChannelProbe_rtM->solverInfoPtr = (&UnWaterChannelProbe_rtM->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = UnWaterChannelProbe_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    UnWaterChannelProbe_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    UnWaterChannelProbe_rtM->Timing.sampleTimes =
      (&UnWaterChannelProbe_rtM->Timing.sampleTimesArray[0]);
    UnWaterChannelProbe_rtM->Timing.offsetTimes =
      (&UnWaterChannelProbe_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    UnWaterChannelProbe_rtM->Timing.sampleTimes[0] = (0.0);
    UnWaterChannelProbe_rtM->Timing.sampleTimes[1] = (0.0001);

    /* task offsets */
    UnWaterChannelProbe_rtM->Timing.offsetTimes[0] = (0.0);
    UnWaterChannelProbe_rtM->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(UnWaterChannelProbe_rtM, &UnWaterChannelProbe_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = UnWaterChannelProbe_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    UnWaterChannelProbe_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(UnWaterChannelProbe_rtM, 0.1);
  UnWaterChannelProbe_rtM->Timing.stepSize0 = 0.0001;
  UnWaterChannelProbe_rtM->Timing.stepSize1 = 0.0001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    UnWaterChannelProbe_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(UnWaterChannelProbe_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(UnWaterChannelProbe_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(UnWaterChannelProbe_rtM->rtwLogInfo, "tout");
    rtliSetLogX(UnWaterChannelProbe_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(UnWaterChannelProbe_rtM->rtwLogInfo, "");
    rtliSetSigLog(UnWaterChannelProbe_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(UnWaterChannelProbe_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(UnWaterChannelProbe_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(UnWaterChannelProbe_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(UnWaterChannelProbe_rtM->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &UnWaterChannelProbe_Y.Outport[0]
      };

      rtliSetLogYSignalPtrs(UnWaterChannelProbe_rtM->rtwLogInfo,
                            ((LogSignalPtrsType)rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        2
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        2
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0
      };

      static int_T* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "UnWaterChannelProbe/Outport" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          1,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(UnWaterChannelProbe_rtM->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(UnWaterChannelProbe_rtM->rtwLogInfo, "yout");
  }

  /* external mode info */
  UnWaterChannelProbe_rtM->Sizes.checksums[0] = (3748120327U);
  UnWaterChannelProbe_rtM->Sizes.checksums[1] = (2937057282U);
  UnWaterChannelProbe_rtM->Sizes.checksums[2] = (659460889U);
  UnWaterChannelProbe_rtM->Sizes.checksums[3] = (3830473576U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    UnWaterChannelProbe_rtM->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(UnWaterChannelProbe_rtM->extModeInfo,
      &UnWaterChannelProbe_rtM->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(UnWaterChannelProbe_rtM->extModeInfo,
                        UnWaterChannelProbe_rtM->Sizes.checksums);
    rteiSetTPtr(UnWaterChannelProbe_rtM->extModeInfo, rtmGetTPtr
                (UnWaterChannelProbe_rtM));
  }

  UnWaterChannelProbe_rtM->solverInfoPtr = (&UnWaterChannelProbe_rtM->solverInfo);
  UnWaterChannelProbe_rtM->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&UnWaterChannelProbe_rtM->solverInfo, 0.0001);
  rtsiSetSolverMode(&UnWaterChannelProbe_rtM->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  UnWaterChannelProbe_rtM->ModelData.blockIO = ((void *) &UnWaterChannelProbe_B);

  {
    UnWaterChannelProbe_B.PCI6220AD1 = 0.0;
    UnWaterChannelProbe_B.RateTransition1 = 0.0;
    UnWaterChannelProbe_B.Gain = 0.0;
    UnWaterChannelProbe_B.FromWorkspace = 0.0;
    UnWaterChannelProbe_B.RateTransition = 0.0;
    UnWaterChannelProbe_B.RandomSource = 0.0;
    UnWaterChannelProbe_B.Gain1 = 0.0;
    UnWaterChannelProbe_B.SignalGenerator1 = 0.0;
  }

  /* parameters */
  UnWaterChannelProbe_rtM->ModelData.defaultParam = ((real_T *)
    &UnWaterChannelProbe_P);

  /* states (dwork) */
  UnWaterChannelProbe_rtM->Work.dwork = ((void *) &UnWaterChannelProbe_DWork);
  (void) memset((void *)&UnWaterChannelProbe_DWork, 0,
                sizeof(D_Work_UnWaterChannelProbe));

  {
    int_T i;
    for (i = 0; i < 35; i++) {
      UnWaterChannelProbe_DWork.RandomSource_STATE_DWORK[i] = 0.0;
    }
  }

  UnWaterChannelProbe_DWork.PCI6713DA1_RWORK = 0.0;

  /* external outputs */
  UnWaterChannelProbe_rtM->ModelData.outputs = (&UnWaterChannelProbe_Y);
  UnWaterChannelProbe_Y.Outport[0] = 0.0;
  UnWaterChannelProbe_Y.Outport[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    UnWaterChannelProbe_rtM->SpecialInfo.mappingInfo = (&dtInfo);
    UnWaterChannelProbe_rtM->SpecialInfo.xpcData = ((void*) &dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  UnWaterChannelProbe_InitializeDataMapInfo(UnWaterChannelProbe_rtM);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &UnWaterChannelProbe_rtM->NonInlinedSFcns.sfcnInfo;
    UnWaterChannelProbe_rtM->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(UnWaterChannelProbe_rtM)));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &UnWaterChannelProbe_rtM->Sizes.numSampTimes);
    UnWaterChannelProbe_rtM->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (UnWaterChannelProbe_rtM)[0]);
    UnWaterChannelProbe_rtM->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr
      (UnWaterChannelProbe_rtM)[1]);
    rtssSetTPtrPtr(sfcnInfo,
                   UnWaterChannelProbe_rtM->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(UnWaterChannelProbe_rtM));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(UnWaterChannelProbe_rtM));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (UnWaterChannelProbe_rtM));
    rtssSetStepSizePtr(sfcnInfo, &UnWaterChannelProbe_rtM->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (UnWaterChannelProbe_rtM));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &UnWaterChannelProbe_rtM->ModelData.derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &UnWaterChannelProbe_rtM->ModelData.zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo,
      &UnWaterChannelProbe_rtM->ModelData.blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo, &UnWaterChannelProbe_rtM->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &UnWaterChannelProbe_rtM->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &UnWaterChannelProbe_rtM->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &UnWaterChannelProbe_rtM->solverInfoPtr);
  }

  UnWaterChannelProbe_rtM->Sizes.numSFcns = (2);

  /* register each child */
  {
    (void) memset((void *)
                  &UnWaterChannelProbe_rtM->NonInlinedSFcns.childSFunctions[0],
                  0,
                  2*sizeof(SimStruct));
    UnWaterChannelProbe_rtM->childSfunctions =
      (&UnWaterChannelProbe_rtM->NonInlinedSFcns.childSFunctionPtrs[0]);
    UnWaterChannelProbe_rtM->childSfunctions[0] =
      (&UnWaterChannelProbe_rtM->NonInlinedSFcns.childSFunctions[0]);
    UnWaterChannelProbe_rtM->childSfunctions[1] =
      (&UnWaterChannelProbe_rtM->NonInlinedSFcns.childSFunctions[1]);

    /* Level2 S-Function Block: UnWaterChannelProbe/<Root>/PCI-6220 AD1 (adnipcim) */
    {
      SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &UnWaterChannelProbe_rtM->
                         NonInlinedSFcns.blkInfo2[0]);
      }

      ssSetRTWSfcnInfo(rts, UnWaterChannelProbe_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &UnWaterChannelProbe_rtM->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &UnWaterChannelProbe_rtM->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &UnWaterChannelProbe_rtM->NonInlinedSFcns.statesInfo2[0]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &UnWaterChannelProbe_B.PCI6220AD1));
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6220 AD1");
      ssSetPath(rts, "UnWaterChannelProbe/PCI-6220 AD1");
      ssSetRTModel(rts,UnWaterChannelProbe_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       UnWaterChannelProbe_P.PCI6220AD1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &UnWaterChannelProbe_DWork.PCI6220AD1_IWORK[0]);
      ssSetPWork(rts, (void **) &UnWaterChannelProbe_DWork.PCI6220AD1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 41);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &UnWaterChannelProbe_DWork.PCI6220AD1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidth(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &UnWaterChannelProbe_DWork.PCI6220AD1_PWORK);
      }

      /* registration */
      adnipcim(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: UnWaterChannelProbe/<Root>/PCI-6713 DA1 (danipci671x) */
    {
      SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &UnWaterChannelProbe_rtM->
                         NonInlinedSFcns.blkInfo2[1]);
      }

      ssSetRTWSfcnInfo(rts, UnWaterChannelProbe_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &UnWaterChannelProbe_rtM->NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &UnWaterChannelProbe_rtM->NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &UnWaterChannelProbe_rtM->NonInlinedSFcns.statesInfo2[1]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.inputPortInfo[0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.UPtrs0;
          sfcnUPtrs[0] = &UnWaterChannelProbe_B.RateTransition;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6713 DA1");
      ssSetPath(rts, "UnWaterChannelProbe/PCI-6713 DA1");
      ssSetRTModel(rts,UnWaterChannelProbe_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 6);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       UnWaterChannelProbe_P.PCI6713DA1_P6_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &UnWaterChannelProbe_DWork.PCI6713DA1_RWORK);
      ssSetIWork(rts, (int_T *) &UnWaterChannelProbe_DWork.PCI6713DA1_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &UnWaterChannelProbe_rtM->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* RWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &UnWaterChannelProbe_DWork.PCI6713DA1_RWORK);

        /* IWORK */
        ssSetDWorkWidth(rts, 1, 2);
        ssSetDWorkDataType(rts, 1,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &UnWaterChannelProbe_DWork.PCI6713DA1_IWORK[0]);
      }

      /* registration */
      danipci671x(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }
  }
}

/* Model terminate function */
void UnWaterChannelProbe_terminate(void)
{
  /* Level2 S-Function Block: '<Root>/PCI-6220 AD1' (adnipcim) */
  {
    SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
  {
    SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[1];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  UnWaterChannelProbe_output(tid);
}

void MdlUpdate(int_T tid)
{
  UnWaterChannelProbe_update(tid);
}

void MdlInitializeSizes(void)
{
  UnWaterChannelProbe_rtM->Sizes.numContStates = (0);/* Number of continuous states */
  UnWaterChannelProbe_rtM->Sizes.numY = (2);/* Number of model outputs */
  UnWaterChannelProbe_rtM->Sizes.numU = (0);/* Number of model inputs */
  UnWaterChannelProbe_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  UnWaterChannelProbe_rtM->Sizes.numSampTimes = (2);/* Number of sample times */
  UnWaterChannelProbe_rtM->Sizes.numBlocks = (11);/* Number of blocks */
  UnWaterChannelProbe_rtM->Sizes.numBlockIO = (8);/* Number of block outputs */
  UnWaterChannelProbe_rtM->Sizes.numBlockPrms = (45);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  {
    uint32_T initSeed;

    /* Level2 S-Function Block: '<Root>/PCI-6220 AD1' (adnipcim) */
    {
      SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[0];
      sfcnStart(rts);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }

    /* Start for FromWorkspace: '<Root>/From Workspace' */
    {
      static real_T pTimeValues[] = { 0.0, 0.0001, 0.0002,
        0.00030000000000000003, 0.0004, 0.0005, 0.00060000000000000006, 0.0007,
        0.0008, 0.00090000000000000008, 0.001, 0.0011, 0.0012000000000000001,
        0.0013000000000000002, 0.0014, 0.0015, 0.0016, 0.0017000000000000001,
        0.0018000000000000002, 0.0019, 0.002, 0.0021000000000000003, 0.0022,
        0.0023, 0.0024000000000000002, 0.0025, 0.0026000000000000003, 0.0027,
        0.0028, 0.0029000000000000002, 0.003, 0.0031000000000000003, 0.0032,
        0.0033, 0.0034000000000000002, 0.0035, 0.0036000000000000003, 0.0037,
        0.0038, 0.0039000000000000003, 0.004, 0.0041, 0.0042000000000000006,
        0.0043, 0.0044, 0.0045000000000000005, 0.0046, 0.0047,
        0.0048000000000000004, 0.0049, 0.005, 0.0051, 0.0052000000000000006,
        0.0053, 0.0054, 0.0055000000000000005, 0.0056, 0.0057,
        0.0058000000000000005, 0.0059, 0.006, 0.0061, 0.0062000000000000006,
        0.0063, 0.0064, 0.0065000000000000006, 0.0066, 0.0067,
        0.0068000000000000005, 0.0069000000000000008, 0.007, 0.0071,
        0.0072000000000000007, 0.0073, 0.0074, 0.0075000000000000006, 0.0076,
        0.0077, 0.0078000000000000005, 0.0079, 0.008, 0.0081, 0.0082, 0.0083,
        0.0084000000000000012, 0.0085, 0.0086, 0.0087000000000000011, 0.0088,
        0.0089, 0.0090000000000000011, 0.0091, 0.0092, 0.009300000000000001,
        0.0094, 0.0095, 0.0096000000000000009, 0.0097, 0.0098, 0.0099, 0.01,
        0.010100000000000001, 0.0102, 0.0103, 0.010400000000000001, 0.0105,
        0.0106, 0.010700000000000001, 0.0108, 0.0109, 0.011000000000000001,
        0.0111, 0.0112, 0.011300000000000001, 0.0114, 0.0115,
        0.011600000000000001, 0.0117, 0.0118, 0.0119, 0.012,
        0.012100000000000001, 0.0122, 0.0123, 0.012400000000000001, 0.0125,
        0.0126, 0.012700000000000001, 0.0128, 0.0129, 0.013000000000000001,
        0.0131, 0.0132, 0.013300000000000001, 0.0134, 0.0135,
        0.013600000000000001, 0.0137, 0.013800000000000002, 0.013900000000000001,
        0.014, 0.014100000000000001, 0.0142, 0.0143, 0.014400000000000001,
        0.0145, 0.0146, 0.014700000000000001, 0.0148, 0.0149,
        0.015000000000000001, 0.0151, 0.0152, 0.015300000000000001, 0.0154,
        0.0155, 0.015600000000000001, 0.015700000000000002, 0.0158, 0.0159,
        0.016, 0.0161, 0.0162, 0.016300000000000002, 0.0164, 0.0165, 0.0166,
        0.0167, 0.016800000000000002, 0.016900000000000002, 0.017, 0.0171,
        0.0172, 0.0173, 0.017400000000000002, 0.0175, 0.0176, 0.0177, 0.0178,
        0.0179, 0.018000000000000002, 0.0181, 0.0182, 0.0183, 0.0184,
        0.018500000000000003, 0.018600000000000002, 0.0187, 0.0188, 0.0189,
        0.019, 0.019100000000000002, 0.019200000000000002, 0.0193, 0.0194,
        0.0195, 0.0196, 0.019700000000000002, 0.0198, 0.0199, 0.02, 0.0201,
        0.020200000000000003, 0.020300000000000002, 0.0204, 0.0205, 0.0206,
        0.0207, 0.020800000000000003, 0.020900000000000002, 0.021, 0.0211,
        0.0212, 0.0213, 0.021400000000000002, 0.021500000000000002, 0.0216,
        0.0217, 0.0218, 0.0219, 0.022000000000000002, 0.0221, 0.0222, 0.0223,
        0.0224, 0.022500000000000003, 0.022600000000000002, 0.0227, 0.0228,
        0.0229, 0.023, 0.023100000000000002, 0.023200000000000002, 0.0233,
        0.0234, 0.0235, 0.0236, 0.023700000000000002, 0.0238, 0.0239, 0.024,
        0.0241, 0.024200000000000003, 0.024300000000000002, 0.0244, 0.0245,
        0.0246, 0.0247, 0.024800000000000003, 0.024900000000000002, 0.025,
        0.0251, 0.0252, 0.0253, 0.025400000000000002, 0.025500000000000002,
        0.0256, 0.0257, 0.0258, 0.025900000000000003, 0.026000000000000002,
        0.0261, 0.0262, 0.0263, 0.0264, 0.026500000000000003,
        0.026600000000000002, 0.0267, 0.0268, 0.0269, 0.027,
        0.027100000000000003, 0.027200000000000002, 0.0273, 0.0274, 0.0275,
        0.027600000000000003, 0.027700000000000002, 0.027800000000000002, 0.0279,
        0.028, 0.0281, 0.028200000000000003, 0.028300000000000002, 0.0284,
        0.0285, 0.0286, 0.0287, 0.028800000000000003, 0.028900000000000002,
        0.029, 0.0291, 0.0292, 0.029300000000000003, 0.029400000000000003,
        0.029500000000000002, 0.0296, 0.0297, 0.0298, 0.029900000000000003,
        0.030000000000000002, 0.030100000000000002, 0.0302, 0.0303, 0.0304,
        0.030500000000000003, 0.030600000000000002, 0.0307, 0.0308, 0.0309,
        0.031, 0.031100000000000003, 0.031200000000000002, 0.0313,
        0.031400000000000004, 0.0315, 0.0316, 0.0317, 0.0318,
        0.031900000000000005, 0.032, 0.032100000000000004, 0.0322, 0.0323,
        0.0324, 0.0325, 0.032600000000000004, 0.0327, 0.0328, 0.0329, 0.033,
        0.033100000000000004, 0.0332, 0.0333, 0.0334, 0.0335,
        0.033600000000000005, 0.0337, 0.033800000000000004, 0.0339, 0.034,
        0.0341, 0.0342, 0.034300000000000004, 0.0344, 0.0345, 0.0346, 0.0347,
        0.034800000000000005, 0.0349, 0.035, 0.0351, 0.0352,
        0.035300000000000005, 0.0354, 0.035500000000000004, 0.0356, 0.0357,
        0.0358, 0.0359, 0.036000000000000004, 0.0361, 0.0362, 0.0363, 0.0364,
        0.036500000000000005, 0.0366, 0.0367, 0.0368, 0.0369,
        0.037000000000000005, 0.0371, 0.037200000000000004, 0.0373, 0.0374,
        0.0375, 0.0376, 0.037700000000000004, 0.0378, 0.0379, 0.038, 0.0381,
        0.038200000000000005, 0.0383, 0.038400000000000004, 0.0385, 0.0386,
        0.038700000000000005, 0.0388, 0.038900000000000004, 0.039, 0.0391,
        0.0392, 0.0393, 0.039400000000000004, 0.0395, 0.0396, 0.0397, 0.0398,
        0.039900000000000005, 0.04, 0.040100000000000004, 0.0402, 0.0403,
        0.040400000000000005, 0.0405, 0.040600000000000004, 0.0407, 0.0408,
        0.0409, 0.041, 0.041100000000000005, 0.0412, 0.0413, 0.0414, 0.0415,
        0.041600000000000005, 0.0417, 0.041800000000000004, 0.0419, 0.042,
        0.042100000000000005, 0.0422, 0.042300000000000004, 0.0424, 0.0425,
        0.0426, 0.0427, 0.042800000000000005, 0.0429, 0.043000000000000003,
        0.0431, 0.0432, 0.043300000000000005, 0.0434, 0.043500000000000004,
        0.0436, 0.0437, 0.0438, 0.0439, 0.044000000000000004, 0.0441, 0.0442,
        0.0443, 0.0444, 0.044500000000000005, 0.0446, 0.044700000000000004,
        0.0448, 0.0449, 0.045000000000000005, 0.0451, 0.045200000000000004,
        0.0453, 0.0454, 0.0455, 0.0456, 0.045700000000000005, 0.0458, 0.0459,
        0.046, 0.0461, 0.046200000000000005, 0.0463, 0.046400000000000004,
        0.0465, 0.0466, 0.046700000000000005, 0.0468, 0.046900000000000004,
        0.047, 0.0471, 0.0472, 0.0473, 0.047400000000000005, 0.0475, 0.0476,
        0.0477, 0.0478, 0.047900000000000005, 0.048, 0.048100000000000004,
        0.0482, 0.0483, 0.048400000000000006, 0.0485, 0.048600000000000004,
        0.0487, 0.0488, 0.0489, 0.049, 0.049100000000000005, 0.0492,
        0.049300000000000004, 0.0494, 0.0495, 0.049600000000000005, 0.0497,
        0.049800000000000004, 0.0499, 0.05, 0.0501, 0.0502, 0.0503, 0.0504,
        0.0505, 0.0506, 0.0507, 0.0508, 0.0509, 0.051000000000000004, 0.0511,
        0.0512, 0.0513, 0.0514, 0.0515, 0.0516, 0.0517, 0.0518, 0.0519, 0.052,
        0.0521, 0.0522, 0.0523, 0.0524, 0.0525, 0.0526, 0.052700000000000004,
        0.0528, 0.0529, 0.053, 0.0531, 0.0532, 0.0533, 0.0534, 0.0535, 0.0536,
        0.0537, 0.0538, 0.0539, 0.054, 0.0541, 0.0542, 0.0543,
        0.054400000000000004, 0.0545, 0.0546, 0.0547, 0.0548, 0.0549, 0.055,
        0.0551, 0.0552, 0.0553, 0.0554, 0.0555, 0.055600000000000004, 0.0557,
        0.0558, 0.0559, 0.056, 0.056100000000000004, 0.0562, 0.0563, 0.0564,
        0.0565, 0.0566, 0.0567, 0.0568, 0.0569, 0.057, 0.0571, 0.0572,
        0.057300000000000004, 0.0574, 0.0575, 0.0576, 0.0577, 0.0578, 0.0579,
        0.058, 0.0581, 0.0582, 0.0583, 0.0584, 0.0585, 0.0586, 0.0587, 0.0588,
        0.0589, 0.059000000000000004, 0.0591, 0.0592, 0.0593, 0.0594, 0.0595,
        0.0596, 0.0597, 0.0598, 0.0599, 0.06, 0.0601, 0.060200000000000004,
        0.0603, 0.0604, 0.0605, 0.0606, 0.060700000000000004, 0.0608, 0.0609,
        0.061, 0.0611, 0.0612, 0.0613, 0.0614, 0.0615, 0.0616, 0.0617, 0.0618,
        0.061900000000000004, 0.062, 0.0621, 0.0622, 0.0623,
        0.062400000000000004, 0.0625, 0.0626, 0.0627, 0.0628, 0.0629, 0.063,
        0.0631, 0.0632, 0.0633, 0.0634, 0.0635, 0.0636, 0.0637, 0.0638, 0.0639,
        0.064, 0.0641, 0.064200000000000007, 0.0643, 0.0644, 0.0645,
        0.064599999999999991, 0.064700000000000008, 0.0648, 0.0649, 0.065,
        0.065099999999999991, 0.065200000000000008, 0.0653, 0.0654, 0.0655,
        0.065599999999999992, 0.065700000000000008, 0.0658, 0.0659, 0.066,
        0.066099999999999992, 0.066200000000000009, 0.0663, 0.0664, 0.0665,
        0.066599999999999993, 0.066700000000000009, 0.0668, 0.0669, 0.067,
        0.067099999999999993, 0.06720000000000001, 0.0673, 0.0674, 0.0675,
        0.0676, 0.06770000000000001, 0.0678, 0.0679, 0.068, 0.0681,
        0.068200000000000011, 0.0683, 0.0684, 0.0685, 0.0686, 0.0687, 0.0688,
        0.0689, 0.069, 0.0691, 0.0692, 0.0693, 0.0694, 0.0695, 0.0696, 0.0697,
        0.0698, 0.0699, 0.07, 0.0701, 0.0702, 0.0703, 0.0704,
        0.070500000000000007, 0.0706, 0.0707, 0.0708, 0.0709,
        0.071000000000000008, 0.0711, 0.0712, 0.0713, 0.0714,
        0.071500000000000008, 0.0716, 0.0717, 0.0718, 0.0719,
        0.072000000000000008, 0.0721, 0.0722, 0.0723, 0.0724,
        0.072500000000000009, 0.0726, 0.0727, 0.0728, 0.0729,
        0.073000000000000009, 0.0731, 0.0732, 0.0733, 0.073399999999999993,
        0.07350000000000001, 0.0736, 0.0737, 0.0738, 0.0739, 0.074, 0.0741,
        0.0742, 0.0743, 0.0744, 0.0745, 0.0746, 0.0747, 0.0748, 0.0749, 0.075,
        0.0751, 0.0752, 0.0753, 0.0754, 0.0755, 0.0756, 0.0757, 0.0758, 0.0759,
        0.076, 0.0761, 0.0762, 0.0763, 0.0764, 0.0765, 0.0766, 0.0767,
        0.076800000000000007, 0.0769, 0.077, 0.0771, 0.0772,
        0.077300000000000008, 0.0774, 0.0775, 0.0776, 0.0777,
        0.077800000000000008, 0.0779, 0.078, 0.0781, 0.0782,
        0.078300000000000008, 0.0784, 0.0785, 0.0786, 0.0787,
        0.078800000000000009, 0.0789, 0.079, 0.0791, 0.0792,
        0.079300000000000009, 0.0794, 0.0795, 0.0796, 0.0797,
        0.07980000000000001, 0.0799, 0.08, 0.0801, 0.0802, 0.08030000000000001,
        0.0804, 0.0805, 0.0806, 0.0807, 0.0808, 0.0809, 0.081, 0.0811, 0.0812,
        0.0813, 0.0814, 0.0815, 0.0816, 0.0817, 0.0818, 0.0819, 0.082, 0.0821,
        0.0822, 0.0823, 0.0824, 0.0825, 0.0826, 0.0827, 0.0828, 0.0829, 0.083,
        0.083100000000000007, 0.0832, 0.0833, 0.0834, 0.0835,
        0.083600000000000008, 0.0837, 0.0838, 0.0839, 0.084,
        0.084100000000000008, 0.0842, 0.0843, 0.0844, 0.0845,
        0.084600000000000009, 0.0847, 0.0848, 0.0849, 0.085,
        0.085100000000000009, 0.0852, 0.0853, 0.0854, 0.0855,
        0.085600000000000009, 0.0857, 0.0858, 0.0859, 0.086000000000000007,
        0.0861, 0.0862, 0.0863, 0.0864, 0.086500000000000007, 0.0866, 0.0867,
        0.0868, 0.0869, 0.087000000000000008, 0.0871, 0.0872, 0.0873, 0.0874,
        0.0875, 0.0876, 0.0877, 0.0878, 0.0879, 0.088, 0.0881, 0.0882, 0.0883,
        0.0884, 0.0885, 0.0886, 0.0887, 0.0888, 0.0889, 0.089, 0.0891, 0.0892,
        0.0893, 0.089400000000000007, 0.0895, 0.0896, 0.0897, 0.0898,
        0.089900000000000008, 0.09, 0.0901, 0.0902, 0.0903, 0.090400000000000008,
        0.0905, 0.0906, 0.0907, 0.0908, 0.090900000000000009, 0.091, 0.0911,
        0.0912, 0.0913, 0.091400000000000009, 0.0915, 0.0916, 0.0917, 0.0918,
        0.091900000000000009, 0.092, 0.0921, 0.0922, 0.092300000000000007,
        0.0924, 0.0925, 0.0926, 0.0927, 0.092800000000000007, 0.0929, 0.093,
        0.0931, 0.0932, 0.093300000000000008, 0.0934, 0.0935, 0.0936, 0.0937,
        0.093800000000000008, 0.0939, 0.094, 0.0941, 0.0942,
        0.094300000000000009, 0.0944, 0.0945, 0.0946, 0.0947, 0.0948, 0.0949,
        0.095, 0.0951, 0.0952, 0.0953, 0.0954, 0.0955, 0.0956,
        0.095700000000000007, 0.0958, 0.0959, 0.096, 0.0961,
        0.096200000000000008, 0.0963, 0.0964, 0.0965, 0.0966,
        0.096700000000000008, 0.0968, 0.0969, 0.097, 0.0971,
        0.097200000000000009, 0.0973, 0.0974, 0.0975, 0.0976,
        0.097700000000000009, 0.0978, 0.0979, 0.098, 0.0981, 0.09820000000000001,
        0.0983, 0.0984, 0.0985, 0.098600000000000007, 0.0987, 0.0988, 0.0989,
        0.099, 0.099100000000000008, 0.0992, 0.0993, 0.0994, 0.0995,
        0.099600000000000008, 0.0997, 0.0998, 0.0999 } ;

      static real_T pDataValues[] = { 0.25, -0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25,
        0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25,
        0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25,
        0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25,
        0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25,
        -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25,
        0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25,
        -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25,
        -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25,
        0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, -0.25,
        0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25,
        0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25, 0.25, -0.25,
        0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25,
        0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25,
        0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25,
        0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25,
        0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25,
        0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25,
        0.25, -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, 0.25,
        -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25,
        -0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
        -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25,
        -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25,
        0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25,
        -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, -0.25, -0.25, 0.25,
        -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25,
        0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25,
        -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25,
        0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25,
        0.25, -0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25,
        -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, -0.25, 0.25,
        0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25,
        0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25,
        -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25,
        0.25, 0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, -0.25,
        0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25,
        -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25,
        -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25,
        0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25,
        -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, 0.25,
        -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25,
        0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, 0.25,
        0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25,
        0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25,
        -0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, -0.25,
        -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25,
        -0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, -0.25,
        0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25,
        -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25,
        0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, -0.25,
        -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, 0.25, -0.25,
        0.25, -0.25, 0.25, 0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25,
        0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, 0.25,
        -0.25, -0.25, 0.25, 0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25,
        0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, -0.25,
        -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, 0.25, -0.25,
        0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25, 0.25, 0.25, 0.25,
        0.25, 0.25, -0.25, -0.25, 0.25, 0.25, -0.25, -0.25, -0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25, -0.25, 0.25, 0.25,
        -0.25, 0.25, -0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25, 0.25,
        -0.25, -0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25,
        -0.25, -0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25, 0.25, -0.25,
        0.25, -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, 0.25, 0.25,
        0.25, 0.25, 0.25, 0.25, 0.25, -0.25, 0.25, -0.25, -0.25, -0.25, -0.25,
        -0.25, 0.25, -0.25, 0.25, -0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25,
        0.25, 0.25, 0.25, -0.25, -0.25, -0.25 } ;

      UnWaterChannelProbe_DWork.FromWorkspace_PWORK.TimePtr = (void *)
        pTimeValues;
      UnWaterChannelProbe_DWork.FromWorkspace_PWORK.DataPtr = (void *)
        pDataValues;
      UnWaterChannelProbe_DWork.FromWorkspace_IWORK.PrevIndex = 0;
    }

    /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
    {
      SimStruct *rts = UnWaterChannelProbe_rtM->childSfunctions[1];
      sfcnStart(rts);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }

    /* S-Function Block: <S1>/S-Function (scblock) */
    {
      int i;
      if ((i = rl32eScopeExists(4)) == 0) {
        if ((i = rl32eDefScope(4,2)) != 0) {
          printf("Error creating scope 4\n");
        } else {
          rl32eAddSignal(4, rl32eGetSignalNo("Gain"));
          rl32eAddSignal(4, rl32eGetSignalNo("From Workspace"));
          rl32eSetScope(4, 4, 100);
          rl32eSetScope(4, 40, 0);
          rl32eSetScope(4, 7, 1);
          rl32eSetScope(4, 0, 0);
          rl32eSetScope(4, 3, rl32eGetSignalNo("Gain"));
          rl32eSetScope(4, 1, 0.0);
          rl32eSetScope(4, 2, 0);
          rl32eSetScope(4, 10, 0);
          rl32eSetTargetScope(4, 11, 0.0);
          rl32eSetTargetScope(4, 10, 0.0);
          xpceScopeAcqOK(4, &UnWaterChannelProbe_DWork.SFunction_IWORK.AcquireOK);
        }
      }

      if (i) {
        rl32eRestartAcquisition(4);
      }
    }

    /* Start for S-Function (sdsprandsrc2): '<Root>/Random Source' */
    initSeed = (uint32_T)(100000 * rand());
    RandSrcCreateSeeds_64(initSeed,
                          &UnWaterChannelProbe_DWork.RandomSource_SEED_DWORK, 1);
    RandSrcInitState_U_64(&UnWaterChannelProbe_DWork.RandomSource_SEED_DWORK,
                          UnWaterChannelProbe_DWork.RandomSource_STATE_DWORK, 1);
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  UnWaterChannelProbe_terminate();
}

rtModel_UnWaterChannelProbe *UnWaterChannelProbe(void)
{
  UnWaterChannelProbe_initialize(1);
  return UnWaterChannelProbe_rtM;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
