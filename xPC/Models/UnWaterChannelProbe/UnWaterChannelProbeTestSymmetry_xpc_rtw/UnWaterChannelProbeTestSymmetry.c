/*
 * UnWaterChannelProbeTestSymmetry.c
 *
 * Code generation for model "UnWaterChannelProbeTestSymmetry.mdl".
 *
 * Model version              : 1.90
 * Simulink Coder version : 8.0 (R2011a) 09-Mar-2011
 * C source code generated on : Tue Jul 09 13:02:09 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rt_logging_mmi.h"
#include "UnWaterChannelProbeTestSymmetry_capi.h"
#include "UnWaterChannelProbeTestSymmetry.h"
#include "UnWaterChannelProbeTestSymmetry_private.h"
#include <stdio.h>
#include "UnWaterChannelProbeTestSymmetry_dt.h"

/* Block signals (auto storage) */
BlockIO_UnWaterChannelProbeTestSymmetry UnWaterChannelProbeTestSymmetry_B;

/* Block states (auto storage) */
D_Work_UnWaterChannelProbeTestSymmetry UnWaterChannelProbeTestSymmetry_DWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_UnWaterChannelProbeTestSymmetry
  UnWaterChannelProbeTestSymmetry_Y;

/* Real-time model */
rtModel_UnWaterChannelProbeTestSymmetry UnWaterChannelProbeTestSymmetry_rtM_;
rtModel_UnWaterChannelProbeTestSymmetry *const
  UnWaterChannelProbeTestSymmetry_rtM = &UnWaterChannelProbeTestSymmetry_rtM_;
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
void UnWaterChannelProbeTestSymmetry_output(int_T tid)
{
  real_T temp;

  /* Level2 S-Function Block: '<Root>/PCI-6220 AD1' (adnipcim) */
  {
    SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[0];
    sfcnOutputs(rts, 1);
  }

  /* RateTransition: '<Root>/Rate Transition1' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition1 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1;

  /* Gain: '<Root>/Gain' */
  UnWaterChannelProbeTestSymmetry_B.Gain =
    UnWaterChannelProbeTestSymmetry_P.Gain_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition1;

  /* RateTransition: '<Root>/Rate Transition2' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition2 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o2;

  /* Gain: '<Root>/Gain2' */
  UnWaterChannelProbeTestSymmetry_B.Gain2 =
    UnWaterChannelProbeTestSymmetry_P.Gain2_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition2;

  /* RateTransition: '<Root>/Rate Transition3' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition3 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o3;

  /* Gain: '<Root>/Gain3' */
  UnWaterChannelProbeTestSymmetry_B.Gain3 =
    UnWaterChannelProbeTestSymmetry_P.Gain3_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition3;

  /* RateTransition: '<Root>/Rate Transition4' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition4 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o4;

  /* Gain: '<Root>/Gain4' */
  UnWaterChannelProbeTestSymmetry_B.Gain4 =
    UnWaterChannelProbeTestSymmetry_P.Gain4_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition4;

  /* RateTransition: '<Root>/Rate Transition5' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition5 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o5;

  /* Gain: '<Root>/Gain5' */
  UnWaterChannelProbeTestSymmetry_B.Gain5 =
    UnWaterChannelProbeTestSymmetry_P.Gain5_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition5;

  /* RateTransition: '<Root>/Rate Transition6' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition6 =
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o6;

  /* Gain: '<Root>/Gain6' */
  UnWaterChannelProbeTestSymmetry_B.Gain6 =
    UnWaterChannelProbeTestSymmetry_P.Gain6_Gain *
    UnWaterChannelProbeTestSymmetry_B.RateTransition6;

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T t = UnWaterChannelProbeTestSymmetry_rtM->Timing.t[1];
    real_T *pTimeValues = (real_T *)
      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_PWORK.DataPtr;
    if (t < pTimeValues[0]) {
      UnWaterChannelProbeTestSymmetry_B.FromWorkspace = 0.0;
    } else if (t == pTimeValues[499]) {
      UnWaterChannelProbeTestSymmetry_B.FromWorkspace = pDataValues[499];
    } else if (t > pTimeValues[499]) {
      UnWaterChannelProbeTestSymmetry_B.FromWorkspace = 0.0;
    } else {
      int_T currTimeIndex =
        UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }

      UnWaterChannelProbeTestSymmetry_B.FromWorkspace =
        pDataValues[currTimeIndex];
      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_IWORK.PrevIndex =
        currTimeIndex;
    }
  }

  /* Outport: '<Root>/Outport' */
  UnWaterChannelProbeTestSymmetry_Y.Outport[0] =
    UnWaterChannelProbeTestSymmetry_B.Gain;
  UnWaterChannelProbeTestSymmetry_Y.Outport[1] =
    UnWaterChannelProbeTestSymmetry_B.Gain2;
  UnWaterChannelProbeTestSymmetry_Y.Outport[2] =
    UnWaterChannelProbeTestSymmetry_B.Gain3;
  UnWaterChannelProbeTestSymmetry_Y.Outport[3] =
    UnWaterChannelProbeTestSymmetry_B.Gain4;
  UnWaterChannelProbeTestSymmetry_Y.Outport[4] =
    UnWaterChannelProbeTestSymmetry_B.Gain5;
  UnWaterChannelProbeTestSymmetry_Y.Outport[5] =
    UnWaterChannelProbeTestSymmetry_B.Gain6;
  UnWaterChannelProbeTestSymmetry_Y.Outport[6] =
    UnWaterChannelProbeTestSymmetry_B.FromWorkspace;

  /* RateTransition: '<Root>/Rate Transition' */
  UnWaterChannelProbeTestSymmetry_B.RateTransition =
    UnWaterChannelProbeTestSymmetry_B.FromWorkspace;

  /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
  {
    SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[1];
    sfcnOutputs(rts, 1);
  }

  /* ok to acquire for <S1>/S-Function */
  UnWaterChannelProbeTestSymmetry_DWork.SFunction_IWORK.AcquireOK = 1;

  /* S-Function (sdsprandsrc2): '<Root>/Random Source' */
  RandSrc_U_D(&UnWaterChannelProbeTestSymmetry_B.RandomSource,
              &UnWaterChannelProbeTestSymmetry_P.RandomSource_MinRTP, 1,
              &UnWaterChannelProbeTestSymmetry_P.RandomSource_MaxRTP, 1,
              UnWaterChannelProbeTestSymmetry_DWork.RandomSource_STATE_DWORK, 1,
              1);

  /* Gain: '<Root>/Gain1' */
  UnWaterChannelProbeTestSymmetry_B.Gain1 =
    UnWaterChannelProbeTestSymmetry_P.Gain1_Gain *
    UnWaterChannelProbeTestSymmetry_B.RandomSource;

  /* SignalGenerator: '<Root>/Signal Generator1' */
  temp = UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Frequency *
    UnWaterChannelProbeTestSymmetry_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    UnWaterChannelProbeTestSymmetry_B.SignalGenerator1 =
      UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Amplitude;
  } else {
    UnWaterChannelProbeTestSymmetry_B.SignalGenerator1 =
      -UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator1' */

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void UnWaterChannelProbeTestSymmetry_update(int_T tid)
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
  if (!(++UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTick0)) {
    ++UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTickH0;
  }

  UnWaterChannelProbeTestSymmetry_rtM->Timing.t[0] =
    UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTick0 *
    UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0 +
    UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTickH0 *
    UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0 * 4294967296.0;

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
    if (!(++UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTick1)) {
      ++UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTickH1;
    }

    UnWaterChannelProbeTestSymmetry_rtM->Timing.t[1] =
      UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTick1 *
      UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize1 +
      UnWaterChannelProbeTestSymmetry_rtM->Timing.clockTickH1 *
      UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void UnWaterChannelProbeTestSymmetry_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)UnWaterChannelProbeTestSymmetry_rtM, 0,
                sizeof(rtModel_UnWaterChannelProbeTestSymmetry));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                          &UnWaterChannelProbeTestSymmetry_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo, &rtmGetTPtr
                (UnWaterChannelProbeTestSymmetry_rtM));
    rtsiSetStepSizePtr(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                       &UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                          (&rtmGetErrorStatus
      (UnWaterChannelProbeTestSymmetry_rtM)));
    rtsiSetRTModelPtr(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                      UnWaterChannelProbeTestSymmetry_rtM);
  }

  rtsiSetSimTimeStep(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                     MAJOR_TIME_STEP);
  rtsiSetSolverName(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                    "FixedStepDiscrete");
  UnWaterChannelProbeTestSymmetry_rtM->solverInfoPtr =
    (&UnWaterChannelProbeTestSymmetry_rtM->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimeTaskIDPtr =
      (&mdlTsMap[0]);
    UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimes =
      (&UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimesArray[0]);
    UnWaterChannelProbeTestSymmetry_rtM->Timing.offsetTimes =
      (&UnWaterChannelProbeTestSymmetry_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimes[0] = (0.0);
    UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleTimes[1] = (0.0001);

    /* task offsets */
    UnWaterChannelProbeTestSymmetry_rtM->Timing.offsetTimes[0] = (0.0);
    UnWaterChannelProbeTestSymmetry_rtM->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(UnWaterChannelProbeTestSymmetry_rtM,
             &UnWaterChannelProbeTestSymmetry_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits =
      UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(UnWaterChannelProbeTestSymmetry_rtM, 0.5);
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0 = 0.0001;
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize1 = 0.0001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, "tout");
    rtliSetLogX(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, "");
    rtliSetSigLog(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo,
      "rt_");
    rtliSetLogFormat(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &UnWaterChannelProbeTestSymmetry_Y.Outport[0]
      };

      rtliSetLogYSignalPtrs(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo,
                            ((LogSignalPtrsType)rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        7
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        7
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
        "UnWaterChannelProbeTestSymmetry/Outport" };

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

      rtliSetLogYSignalInfo(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(UnWaterChannelProbeTestSymmetry_rtM->rtwLogInfo, "yout");
  }

  /* external mode info */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.checksums[0] = (2378764892U);
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.checksums[1] = (4128182189U);
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.checksums[2] = (396650687U);
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.checksums[3] = (765639314U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    UnWaterChannelProbeTestSymmetry_rtM->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(UnWaterChannelProbeTestSymmetry_rtM->extModeInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(UnWaterChannelProbeTestSymmetry_rtM->extModeInfo,
                        UnWaterChannelProbeTestSymmetry_rtM->Sizes.checksums);
    rteiSetTPtr(UnWaterChannelProbeTestSymmetry_rtM->extModeInfo, rtmGetTPtr
                (UnWaterChannelProbeTestSymmetry_rtM));
  }

  UnWaterChannelProbeTestSymmetry_rtM->solverInfoPtr =
    (&UnWaterChannelProbeTestSymmetry_rtM->solverInfo);
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo, 0.0001);
  rtsiSetSolverMode(&UnWaterChannelProbeTestSymmetry_rtM->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  UnWaterChannelProbeTestSymmetry_rtM->ModelData.blockIO = ((void *)
    &UnWaterChannelProbeTestSymmetry_B);

  {
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o2 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o3 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o4 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o5 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o6 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition1 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition2 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain2 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition3 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain3 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition4 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain4 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition5 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain5 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition6 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain6 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.FromWorkspace = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RateTransition = 0.0;
    UnWaterChannelProbeTestSymmetry_B.RandomSource = 0.0;
    UnWaterChannelProbeTestSymmetry_B.Gain1 = 0.0;
    UnWaterChannelProbeTestSymmetry_B.SignalGenerator1 = 0.0;
  }

  /* parameters */
  UnWaterChannelProbeTestSymmetry_rtM->ModelData.defaultParam = ((real_T *)
    &UnWaterChannelProbeTestSymmetry_P);

  /* states (dwork) */
  UnWaterChannelProbeTestSymmetry_rtM->Work.dwork = ((void *)
    &UnWaterChannelProbeTestSymmetry_DWork);
  (void) memset((void *)&UnWaterChannelProbeTestSymmetry_DWork, 0,
                sizeof(D_Work_UnWaterChannelProbeTestSymmetry));

  {
    int_T i;
    for (i = 0; i < 35; i++) {
      UnWaterChannelProbeTestSymmetry_DWork.RandomSource_STATE_DWORK[i] = 0.0;
    }
  }

  UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_RWORK = 0.0;

  /* external outputs */
  UnWaterChannelProbeTestSymmetry_rtM->ModelData.outputs =
    (&UnWaterChannelProbeTestSymmetry_Y);

  {
    int_T i;
    for (i = 0; i < 7; i++) {
      UnWaterChannelProbeTestSymmetry_Y.Outport[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    UnWaterChannelProbeTestSymmetry_rtM->SpecialInfo.mappingInfo = (&dtInfo);
    UnWaterChannelProbeTestSymmetry_rtM->SpecialInfo.xpcData = ((void*) &dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  UnWaterChannelProbeTestSymmetry_InitializeDataMapInfo
    (UnWaterChannelProbeTestSymmetry_rtM);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo =
      &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.sfcnInfo;
    UnWaterChannelProbeTestSymmetry_rtM->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus
      (UnWaterChannelProbeTestSymmetry_rtM)));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->Sizes.numSampTimes);
    UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.taskTimePtrs[0] =
      &(rtmGetTPtr(UnWaterChannelProbeTestSymmetry_rtM)[0]);
    UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.taskTimePtrs[1] =
      &(rtmGetTPtr(UnWaterChannelProbeTestSymmetry_rtM)[1]);
    rtssSetTPtrPtr(sfcnInfo,
                   UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(UnWaterChannelProbeTestSymmetry_rtM));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(UnWaterChannelProbeTestSymmetry_rtM));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (UnWaterChannelProbeTestSymmetry_rtM));
    rtssSetStepSizePtr(sfcnInfo,
                       &UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (UnWaterChannelProbeTestSymmetry_rtM));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->ModelData.derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->ModelData.zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->ModelData.blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo,
                         &UnWaterChannelProbeTestSymmetry_rtM->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &UnWaterChannelProbeTestSymmetry_rtM->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &UnWaterChannelProbeTestSymmetry_rtM->simMode);
    rtssSetSolverInfoPtr(sfcnInfo,
                         &UnWaterChannelProbeTestSymmetry_rtM->solverInfoPtr);
  }

  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numSFcns = (2);

  /* register each child */
  {
    (void) memset((void *)
                  &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.childSFunctions
                  [0], 0,
                  2*sizeof(SimStruct));
    UnWaterChannelProbeTestSymmetry_rtM->childSfunctions =
      (&UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.childSFunctionPtrs
       [0]);
    UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[0] =
      (&UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.childSFunctions[0]);
    UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[1] =
      (&UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.childSFunctions[1]);

    /* Level2 S-Function Block: UnWaterChannelProbeTestSymmetry/<Root>/PCI-6220 AD1 (adnipcim) */
    {
      SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.blkInfo2
                         [0]);
      }

      ssSetRTWSfcnInfo(rts, UnWaterChannelProbeTestSymmetry_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.statesInfo2
                         [0]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 6);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o4));
        }

        /* port 4 */
        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidth(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o5));
        }

        /* port 5 */
        {
          _ssSetOutputPortNumDimensions(rts, 5, 1);
          ssSetOutputPortWidth(rts, 5, 1);
          ssSetOutputPortSignal(rts, 5, ((real_T *)
            &UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o6));
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6220 AD1");
      ssSetPath(rts, "UnWaterChannelProbeTestSymmetry/PCI-6220 AD1");
      ssSetRTModel(rts,UnWaterChannelProbeTestSymmetry_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_IWORK[0]);
      ssSetPWork(rts, (void **)
                 &UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 41);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0,
                   &UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidth(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1,
                   &UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_PWORK);
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
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortConnected(rts, 5, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);
      _ssSetOutputPortBeingMerged(rts, 5, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: UnWaterChannelProbeTestSymmetry/<Root>/PCI-6713 DA1 (danipci671x) */
    {
      SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.blkInfo2
                         [1]);
      }

      ssSetRTWSfcnInfo(rts, UnWaterChannelProbeTestSymmetry_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.statesInfo2
                         [1]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.inputPortInfo
          [0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.UPtrs0;
          sfcnUPtrs[0] = &UnWaterChannelProbeTestSymmetry_B.RateTransition;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6713 DA1");
      ssSetPath(rts, "UnWaterChannelProbeTestSymmetry/PCI-6713 DA1");
      ssSetRTModel(rts,UnWaterChannelProbeTestSymmetry_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 6);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P6_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *)
                 &UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_RWORK);
      ssSetIWork(rts, (int_T *)
                 &UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &UnWaterChannelProbeTestSymmetry_rtM->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* RWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0,
                   &UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_RWORK);

        /* IWORK */
        ssSetDWorkWidth(rts, 1, 2);
        ssSetDWorkDataType(rts, 1,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1,
                   &UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_IWORK[0]);
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
void UnWaterChannelProbeTestSymmetry_terminate(void)
{
  /* Level2 S-Function Block: '<Root>/PCI-6220 AD1' (adnipcim) */
  {
    SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
  {
    SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[1];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  UnWaterChannelProbeTestSymmetry_output(tid);
}

void MdlUpdate(int_T tid)
{
  UnWaterChannelProbeTestSymmetry_update(tid);
}

void MdlInitializeSizes(void)
{
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numContStates = (0);/* Number of continuous states */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numY = (7);/* Number of model outputs */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numU = (0);/* Number of model inputs */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numSampTimes = (2);/* Number of sample times */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numBlocks = (21);/* Number of blocks */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numBlockIO = (23);/* Number of block outputs */
  UnWaterChannelProbeTestSymmetry_rtM->Sizes.numBlockPrms = (65);/* Sum of parameter "widths" */
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
      SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[0];
      sfcnStart(rts);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }

    /* Start for FromWorkspace: '<Root>/From Workspace' */
    {
      static real_T pTimeValues[] = { 0.0, 0.001, 0.002, 0.003, 0.004, 0.005,
        0.006, 0.007, 0.008, 0.0090000000000000011, 0.01, 0.011, 0.012,
        0.013000000000000001, 0.014, 0.015, 0.016, 0.017, 0.018000000000000002,
        0.019, 0.02, 0.021, 0.022, 0.023, 0.024, 0.025, 0.026000000000000002,
        0.027, 0.028, 0.029, 0.03, 0.031, 0.032, 0.033, 0.034, 0.035,
        0.036000000000000004, 0.037, 0.038, 0.039, 0.04, 0.041, 0.042,
        0.043000000000000003, 0.044, 0.045, 0.046, 0.047, 0.048, 0.049, 0.05,
        0.051000000000000004, 0.052000000000000005, 0.053, 0.054, 0.055, 0.056,
        0.057, 0.058, 0.059000000000000004, 0.06, 0.061, 0.062, 0.063, 0.064,
        0.065, 0.066, 0.067, 0.068, 0.069, 0.07, 0.071000000000000008,
        0.072000000000000008, 0.073, 0.074, 0.075, 0.076, 0.077, 0.078, 0.079,
        0.08, 0.081, 0.082, 0.083, 0.084, 0.085, 0.086000000000000007,
        0.087000000000000008, 0.088, 0.089, 0.09, 0.091, 0.092, 0.093, 0.094,
        0.095, 0.096, 0.097, 0.098, 0.099, 0.1, 0.101, 0.10200000000000001,
        0.10300000000000001, 0.10400000000000001, 0.105, 0.106, 0.107, 0.108,
        0.109, 0.11, 0.111, 0.112, 0.113, 0.114, 0.115, 0.116, 0.117,
        0.11800000000000001, 0.11900000000000001, 0.12, 0.121, 0.122, 0.123,
        0.124, 0.125, 0.126, 0.127, 0.128, 0.129, 0.13, 0.131, 0.132, 0.133,
        0.134, 0.135, 0.136, 0.137, 0.138, 0.139, 0.14, 0.14100000000000001,
        0.14200000000000002, 0.14300000000000002, 0.14400000000000002, 0.145,
        0.146, 0.147, 0.148, 0.149, 0.15, 0.151, 0.152, 0.153, 0.154, 0.155,
        0.156, 0.157, 0.158, 0.159, 0.16, 0.161, 0.162, 0.163, 0.164, 0.165,
        0.166, 0.167, 0.168, 0.169, 0.17, 0.171, 0.17200000000000001,
        0.17300000000000001, 0.17400000000000002, 0.17500000000000002, 0.176,
        0.177, 0.178, 0.179, 0.18, 0.181, 0.182, 0.183, 0.184, 0.185, 0.186,
        0.187, 0.188, 0.189, 0.19, 0.191, 0.192, 0.193, 0.194, 0.195, 0.196,
        0.197, 0.198, 0.199, 0.2, 0.201, 0.202, 0.203, 0.20400000000000001,
        0.20500000000000002, 0.20600000000000002, 0.20700000000000002,
        0.20800000000000002, 0.209, 0.21, 0.211, 0.212, 0.213, 0.214, 0.215,
        0.216, 0.217, 0.218, 0.219, 0.22, 0.221, 0.222, 0.223, 0.224, 0.225,
        0.226, 0.227, 0.228, 0.229, 0.23, 0.231, 0.232, 0.233, 0.234,
        0.23500000000000001, 0.23600000000000002, 0.23700000000000002,
        0.23800000000000002, 0.23900000000000002, 0.24, 0.241, 0.242, 0.243,
        0.244, 0.245, 0.246, 0.247, 0.248, 0.249, 0.25, 0.251, 0.252, 0.253,
        0.254, 0.255, 0.256, 0.257, 0.258, 0.259, 0.26, 0.261, 0.262, 0.263,
        0.264, 0.265, 0.266, 0.267, 0.268, 0.269, 0.27, 0.271, 0.272, 0.273,
        0.274, 0.275, 0.276, 0.277, 0.278, 0.279, 0.28, 0.281,
        0.28200000000000003, 0.28300000000000003, 0.28400000000000003,
        0.28500000000000003, 0.28600000000000003, 0.28700000000000003,
        0.28800000000000003, 0.28900000000000003, 0.29000000000000004, 0.291,
        0.292, 0.293, 0.294, 0.295, 0.296, 0.297, 0.298, 0.299, 0.3, 0.301,
        0.302, 0.303, 0.304, 0.305, 0.306, 0.307, 0.308, 0.309, 0.31, 0.311,
        0.312, 0.313, 0.314, 0.315, 0.316, 0.317, 0.318, 0.319, 0.32, 0.321,
        0.322, 0.323, 0.32399999999999995, 0.32499999999999996,
        0.32599999999999996, 0.32699999999999996, 0.32799999999999996,
        0.32899999999999996, 0.32999999999999996, 0.33099999999999996,
        0.33199999999999996, 0.33299999999999996, 0.33399999999999996,
        0.33499999999999996, 0.33599999999999997, 0.33699999999999997,
        0.33799999999999997, 0.33899999999999997, 0.33999999999999997,
        0.34099999999999997, 0.34199999999999997, 0.34299999999999997, 0.344,
        0.345, 0.346, 0.347, 0.348, 0.349, 0.35, 0.351, 0.352, 0.353, 0.354,
        0.355, 0.356, 0.357, 0.358, 0.359, 0.36, 0.361, 0.362, 0.363, 0.364,
        0.365, 0.366, 0.367, 0.368, 0.369, 0.37, 0.371, 0.372, 0.373, 0.374,
        0.375, 0.376, 0.377, 0.378, 0.379, 0.38, 0.381, 0.382, 0.383, 0.384,
        0.385, 0.386, 0.387, 0.388, 0.389, 0.39, 0.391, 0.392, 0.393, 0.394,
        0.395, 0.396, 0.397, 0.398, 0.399, 0.4, 0.401, 0.402, 0.403, 0.404,
        0.405, 0.406, 0.40700000000000003, 0.40800000000000003,
        0.40900000000000003, 0.41000000000000003, 0.41100000000000003, 0.412,
        0.413, 0.414, 0.415, 0.416, 0.417, 0.418, 0.419, 0.42, 0.421, 0.422,
        0.423, 0.424, 0.425, 0.426, 0.427, 0.428, 0.429, 0.43, 0.431, 0.432,
        0.433, 0.434, 0.435, 0.436, 0.437, 0.438, 0.439, 0.44, 0.441, 0.442,
        0.443, 0.444, 0.445, 0.446, 0.447, 0.448, 0.449, 0.45, 0.451, 0.452,
        0.453, 0.454, 0.455, 0.456, 0.457, 0.458, 0.459, 0.46, 0.461, 0.462,
        0.46299999999999997, 0.46399999999999997, 0.46499999999999997,
        0.46599999999999997, 0.46699999999999997, 0.46799999999999997, 0.469,
        0.47, 0.471, 0.472, 0.473, 0.474, 0.475, 0.476, 0.477, 0.478, 0.479,
        0.48, 0.481, 0.482, 0.483, 0.484, 0.485, 0.486, 0.487, 0.488, 0.489,
        0.49, 0.491, 0.492, 0.493, 0.494, 0.495, 0.496, 0.497, 0.498, 0.499 } ;

      static real_T pDataValues[] = { -3.0, -3.0, -3.0, -3.0, -3.0, -3.0, -3.0,
        3.0, 3.0, 3.0, -3.0, -3.0, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        -3.0, 3.0, 3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, 3.0, 3.0,
        3.0, 3.0, -3.0, -3.0, -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0,
        3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0,
        -3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0,
        -3.0, -3.0, -3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0, -3.0, -3.0,
        3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0,
        -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0,
        -3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, -3.0, 3.0, -3.0, 3.0, -3.0, -3.0,
        -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0, 3.0, 3.0, -3.0,
        3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0,
        -3.0, -3.0, -3.0, -3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0, -3.0, -3.0,
        3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0, -3.0,
        3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0, 3.0, 3.0, -3.0,
        -3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0,
        -3.0, 3.0, -3.0, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0, 3.0, 3.0,
        3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, -3.0, -3.0,
        -3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0, 3.0,
        -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0, -3.0, 3.0, -3.0, -3.0, -3.0, 3.0,
        3.0, 3.0, 3.0, 3.0, -3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0, 3.0, -3.0,
        -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0, -3.0, -3.0, 3.0, -3.0, -3.0,
        3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, -3.0, -3.0,
        -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, 3.0, -3.0, -3.0, -3.0,
        -3.0, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0, -3.0, 3.0, 3.0, 3.0,
        -3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0,
        -3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0,
        3.0, 3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0,
        3.0, -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, -3.0, -3.0, 3.0,
        -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, -3.0, -3.0,
        -3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, -3.0, -3.0, 3.0, 3.0,
        -3.0, -3.0, -3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0,
        -3.0, 3.0, -3.0, 3.0, -3.0, -3.0, 3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0,
        -3.0, 3.0, 3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, 3.0, 3.0, 3.0,
        3.0, 3.0, -3.0, 3.0, -3.0, 3.0, -3.0, -3.0, -3.0, 3.0, -3.0, 3.0, 3.0,
        3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0, 3.0, -3.0, -3.0, -3.0, -3.0,
        3.0, 3.0, -3.0, -3.0, 3.0, 3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0,
        -3.0, -3.0, -3.0, -3.0, -3.0, 3.0, 3.0, 3.0, -3.0, 3.0, -3.0, -3.0, 3.0,
        3.0, 3.0, 3.0, -3.0, 3.0, -3.0, -3.0, 3.0, 3.0, -3.0, 3.0, -3.0, 3.0,
        -3.0, -3.0, 3.0, -3.0, -3.0 } ;

      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_PWORK.TimePtr = (void *)
        pTimeValues;
      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_PWORK.DataPtr = (void *)
        pDataValues;
      UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_IWORK.PrevIndex = 0;
    }

    /* Level2 S-Function Block: '<Root>/PCI-6713 DA1' (danipci671x) */
    {
      SimStruct *rts = UnWaterChannelProbeTestSymmetry_rtM->childSfunctions[1];
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
          rl32eAddSignal(4, rl32eGetSignalNo("Gain2"));
          rl32eAddSignal(4, rl32eGetSignalNo("Gain3"));
          rl32eAddSignal(4, rl32eGetSignalNo("Gain4"));
          rl32eAddSignal(4, rl32eGetSignalNo("Gain5"));
          rl32eAddSignal(4, rl32eGetSignalNo("Gain6"));
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
          xpceScopeAcqOK(4,
                         &UnWaterChannelProbeTestSymmetry_DWork.SFunction_IWORK.AcquireOK);
        }
      }

      if (i) {
        rl32eRestartAcquisition(4);
      }
    }

    /* Start for S-Function (sdsprandsrc2): '<Root>/Random Source' */
    initSeed = (uint32_T)(100000 * rand());
    RandSrcCreateSeeds_64(initSeed,
                          &UnWaterChannelProbeTestSymmetry_DWork.RandomSource_SEED_DWORK,
                          1);
    RandSrcInitState_U_64
      (&UnWaterChannelProbeTestSymmetry_DWork.RandomSource_SEED_DWORK,
       UnWaterChannelProbeTestSymmetry_DWork.RandomSource_STATE_DWORK, 1);
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  UnWaterChannelProbeTestSymmetry_terminate();
}

rtModel_UnWaterChannelProbeTestSymmetry *UnWaterChannelProbeTestSymmetry(void)
{
  UnWaterChannelProbeTestSymmetry_initialize(1);
  return UnWaterChannelProbeTestSymmetry_rtM;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
