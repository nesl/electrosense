/*
 * xpcosc.c
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
#include "rt_logging_mmi.h"
#include "xpcosc_capi.h"
#include "xpcosc.h"
#include "xpcosc_private.h"
#include "xpcosc_dt.h"

/* Block signals (auto storage) */
B_xpcosc_T xpcosc_B;

/* Continuous states */
X_xpcosc_T xpcosc_X;

/* Block states (auto storage) */
DW_xpcosc_T xpcosc_DW;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_xpcosc_T xpcosc_Y;

/* Real-time model */
rtModel_xpcosc_T xpcosc_rtM_;
rtModel_xpcosc_T *const xpcosc_rtM = &xpcosc_rtM_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(xpcosc_rtM, 1);
  rtmSampleHitPtr[2] = rtmStepTask(xpcosc_rtM, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rate: 2 */
  xpcosc_rtM->Timing.RateInteraction.TID0_2 =
    (xpcosc_rtM->Timing.TaskCounters.TID[2] == 0);

  /* update PerTaskSampleHits matrix for non-inline sfcn */
  xpcosc_rtM->Timing.perTaskSampleHits[2] =
    xpcosc_rtM->Timing.RateInteraction.TID0_2;

  /* tid 1 shares data with slower tid rate: 2 */
  if (xpcosc_rtM->Timing.TaskCounters.TID[1] == 0) {
    xpcosc_rtM->Timing.RateInteraction.TID1_2 =
      (xpcosc_rtM->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    xpcosc_rtM->Timing.perTaskSampleHits[5] =
      xpcosc_rtM->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (xpcosc_rtM->Timing.TaskCounters.TID[2])++;
  if ((xpcosc_rtM->Timing.TaskCounters.TID[2]) > 3) {/* Sample time: [0.001s, 0.0s] */
    xpcosc_rtM->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  xpcosc_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  xpcosc_output0();
  xpcosc_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  xpcosc_output0();
  xpcosc_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  xpcosc_output0();
  xpcosc_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void xpcosc_output0(void)              /* Sample time: [0.0s, 0.0s] */
{
  real_T temp;
  if (rtmIsMajorTimeStep(xpcosc_rtM)) {
    /* set solver stop time */
    if (!(xpcosc_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&xpcosc_rtM->solverInfo,
                            ((xpcosc_rtM->Timing.clockTickH0 + 1) *
        xpcosc_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&xpcosc_rtM->solverInfo,
                            ((xpcosc_rtM->Timing.clockTick0 + 1) *
        xpcosc_rtM->Timing.stepSize0 + xpcosc_rtM->Timing.clockTickH0 *
        xpcosc_rtM->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(xpcosc_rtM)) {
    xpcosc_rtM->Timing.t[0] = rtsiGetT(&xpcosc_rtM->solverInfo);
  }

  /* Integrator: '<Root>/Integrator1' */
  xpcosc_B.Integrator1 = xpcosc_X.Integrator1_CSTATE;

  /* RateTransition: '<Root>/Rate Transition' */
  if (rtmIsMajorTimeStep(xpcosc_rtM) &&
      xpcosc_rtM->Timing.RateInteraction.TID1_2) {
    xpcosc_B.RateTransition = xpcosc_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<Root>/Rate Transition' */

  /* Outport: '<Root>/Outport' */
  xpcosc_Y.Outport[0] = xpcosc_B.Integrator1;
  xpcosc_Y.Outport[1] = xpcosc_B.RateTransition;

  /* SignalGenerator: '<Root>/Signal Generator' */
  temp = xpcosc_P.SignalGenerator_Frequency * xpcosc_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    xpcosc_B.SignalGenerator = xpcosc_P.SignalGenerator_Amplitude;
  } else {
    xpcosc_B.SignalGenerator = -xpcosc_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* RateTransition: '<Root>/Rate Transition1' */
  if (rtmIsMajorTimeStep(xpcosc_rtM) &&
      xpcosc_rtM->Timing.RateInteraction.TID0_2) {
    xpcosc_B.RateTransition1 = xpcosc_B.SignalGenerator;
  }

  /* End of RateTransition: '<Root>/Rate Transition1' */
  /* ok to acquire for <S1>/S-Function */
  xpcosc_DW.SFunction_IWORK.AcquireOK = 1;

  /* Gain: '<Root>/Gain' */
  xpcosc_B.Gain = xpcosc_P.Gain_Gain * xpcosc_B.Integrator1;

  /* Integrator: '<Root>/Integrator' */
  xpcosc_B.Integrator = xpcosc_X.Integrator_CSTATE;

  /* Gain: '<Root>/Gain1' */
  xpcosc_B.Gain1 = xpcosc_P.Gain1_Gain * xpcosc_B.Integrator;

  /* Gain: '<Root>/Gain2' */
  xpcosc_B.Gain2 = xpcosc_P.Gain2_Gain * xpcosc_B.SignalGenerator;

  /* Sum: '<Root>/Sum' */
  xpcosc_B.Sum = (xpcosc_B.Gain2 - xpcosc_B.Gain) - xpcosc_B.Gain1;
}

/* Model update function for TID0 */
void xpcosc_update0(void)              /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(xpcosc_rtM)) {
    rt_ertODEUpdateContinuousStates(&xpcosc_rtM->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++xpcosc_rtM->Timing.clockTick0)) {
    ++xpcosc_rtM->Timing.clockTickH0;
  }

  xpcosc_rtM->Timing.t[0] = rtsiGetSolverStopTime(&xpcosc_rtM->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++xpcosc_rtM->Timing.clockTick1)) {
    ++xpcosc_rtM->Timing.clockTickH1;
  }

  xpcosc_rtM->Timing.t[1] = xpcosc_rtM->Timing.clockTick1 *
    xpcosc_rtM->Timing.stepSize1 + xpcosc_rtM->Timing.clockTickH1 *
    xpcosc_rtM->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void xpcosc_derivatives(void)
{
  XDot_xpcosc_T *_rtXdot;
  _rtXdot = ((XDot_xpcosc_T *) xpcosc_rtM->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = xpcosc_B.Integrator;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = xpcosc_B.Sum;
}

/* Model output function for TID2 */
void xpcosc_output2(void)              /* Sample time: [0.001s, 0.0s] */
{
  /* Level2 S-Function Block: '<Root>/PCI-6713 DA' (danipci671x) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[0];
    sfcnOutputs(rts, 2);
  }

  /* Level2 S-Function Block: '<Root>/PCI-6220 AD' (adnipcim) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[1];
    sfcnOutputs(rts, 2);
  }
}

/* Model update function for TID2 */
void xpcosc_update2(void)              /* Sample time: [0.001s, 0.0s] */
{
  /* Update for RateTransition: '<Root>/Rate Transition' */
  xpcosc_DW.RateTransition_Buffer0 = xpcosc_B.PCI6220AD;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++xpcosc_rtM->Timing.clockTick2)) {
    ++xpcosc_rtM->Timing.clockTickH2;
  }

  xpcosc_rtM->Timing.t[2] = xpcosc_rtM->Timing.clockTick2 *
    xpcosc_rtM->Timing.stepSize2 + xpcosc_rtM->Timing.clockTickH2 *
    xpcosc_rtM->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void xpcosc_output(int_T tid)
{
  switch (tid) {
   case 0 :
    xpcosc_output0();
    break;

   case 2 :
    xpcosc_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void xpcosc_update(int_T tid)
{
  switch (tid) {
   case 0 :
    xpcosc_update0();
    break;

   case 2 :
    xpcosc_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void xpcosc_initialize(void)
{
  /* Start for RateTransition: '<Root>/Rate Transition' */
  xpcosc_B.RateTransition = xpcosc_P.RateTransition_X0;

  /* Level2 S-Function Block: '<Root>/PCI-6713 DA' (danipci671x) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* S-Function Block: <S1>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(1)) == 0) {
      if ((i = rl32eDefScope(1,2)) != 0) {
        printf("Error creating scope 1\n");
      } else {
        rl32eAddSignal(1, rl32eGetSignalNo("Integrator1"));
        rl32eAddSignal(1, rl32eGetSignalNo("Rate Transition"));
        rl32eSetScope(1, 4, 250);
        rl32eSetScope(1, 40, 0);
        rl32eSetScope(1, 7, 1);
        rl32eSetScope(1, 0, 0);
        rl32eSetScope(1, 3, rl32eGetSignalNo("Integrator1"));
        rl32eSetScope(1, 1, 0.0);
        rl32eSetScope(1, 2, 0);
        rl32eSetScope(1, 10, 0);
        rl32eSetTargetScope(1, 11, 0.0);
        rl32eSetTargetScope(1, 10, 0.0);
        xpceScopeAcqOK(1, &xpcosc_DW.SFunction_IWORK.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(1);
    }
  }

  /* Level2 S-Function Block: '<Root>/PCI-6220 AD' (adnipcim) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  xpcosc_X.Integrator1_CSTATE = xpcosc_P.Integrator1_IC;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition' */
  xpcosc_DW.RateTransition_Buffer0 = xpcosc_P.RateTransition_X0;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  xpcosc_X.Integrator_CSTATE = xpcosc_P.Integrator_IC;
}

/* Model terminate function */
void xpcosc_terminate(void)
{
  /* Level2 S-Function Block: '<Root>/PCI-6713 DA' (danipci671x) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Level2 S-Function Block: '<Root>/PCI-6220 AD' (adnipcim) */
  {
    SimStruct *rts = xpcosc_rtM->childSfunctions[1];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  xpcosc_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  xpcosc_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  xpcosc_initialize();
}

void MdlTerminate(void)
{
  xpcosc_terminate();
}

/* Registration function */
rtModel_xpcosc_T *xpcosc(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)xpcosc_rtM, 0,
                sizeof(rtModel_xpcosc_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&xpcosc_rtM->solverInfo,
                          &xpcosc_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&xpcosc_rtM->solverInfo, &rtmGetTPtr(xpcosc_rtM));
    rtsiSetStepSizePtr(&xpcosc_rtM->solverInfo, &xpcosc_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&xpcosc_rtM->solverInfo, &xpcosc_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&xpcosc_rtM->solverInfo,
                         &xpcosc_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&xpcosc_rtM->solverInfo,
      &xpcosc_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&xpcosc_rtM->solverInfo, (&rtmGetErrorStatus
      (xpcosc_rtM)));
    rtsiSetRTModelPtr(&xpcosc_rtM->solverInfo, xpcosc_rtM);
  }

  rtsiSetSimTimeStep(&xpcosc_rtM->solverInfo, MAJOR_TIME_STEP);
  xpcosc_rtM->ModelData.intgData.y = xpcosc_rtM->ModelData.odeY;
  xpcosc_rtM->ModelData.intgData.f[0] = xpcosc_rtM->ModelData.odeF[0];
  xpcosc_rtM->ModelData.intgData.f[1] = xpcosc_rtM->ModelData.odeF[1];
  xpcosc_rtM->ModelData.intgData.f[2] = xpcosc_rtM->ModelData.odeF[2];
  xpcosc_rtM->ModelData.intgData.f[3] = xpcosc_rtM->ModelData.odeF[3];
  xpcosc_rtM->ModelData.contStates = ((real_T *) &xpcosc_X);
  rtsiSetSolverData(&xpcosc_rtM->solverInfo, (void *)
                    &xpcosc_rtM->ModelData.intgData);
  rtsiSetSolverName(&xpcosc_rtM->solverInfo,"ode4");
  xpcosc_rtM->solverInfoPtr = (&xpcosc_rtM->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = xpcosc_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    xpcosc_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    xpcosc_rtM->Timing.sampleTimes = (&xpcosc_rtM->Timing.sampleTimesArray[0]);
    xpcosc_rtM->Timing.offsetTimes = (&xpcosc_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    xpcosc_rtM->Timing.sampleTimes[0] = (0.0);
    xpcosc_rtM->Timing.sampleTimes[1] = (0.00025);
    xpcosc_rtM->Timing.sampleTimes[2] = (0.001);

    /* task offsets */
    xpcosc_rtM->Timing.offsetTimes[0] = (0.0);
    xpcosc_rtM->Timing.offsetTimes[1] = (0.0);
    xpcosc_rtM->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(xpcosc_rtM, &xpcosc_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = xpcosc_rtM->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = xpcosc_rtM->Timing.perTaskSampleHitsArray;
    xpcosc_rtM->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    xpcosc_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(xpcosc_rtM, 0.2);
  xpcosc_rtM->Timing.stepSize0 = 0.00025;
  xpcosc_rtM->Timing.stepSize1 = 0.00025;
  xpcosc_rtM->Timing.stepSize2 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    xpcosc_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    /*
     * Set pointers to the data and signal info each state
     */
    {
      static int_T rt_LoggedStateWidths[] = {
        1,
        1
      };

      static int_T rt_LoggedStateNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedStateDimensions[] = {
        1,
        1
      };

      static boolean_T rt_LoggedStateIsVarDims[] = {
        0,
        0
      };

      static BuiltInDTypeId rt_LoggedStateDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedStateComplexSignals[] = {
        0,
        0
      };

      static const char_T *rt_LoggedStateLabels[] = {
        "CSTATE",
        "CSTATE"
      };

      static const char_T *rt_LoggedStateBlockNames[] = {
        "xpcosc/Integrator1",
        "xpcosc/Integrator"
      };

      static const char_T *rt_LoggedStateNames[] = {
        "",
        ""
      };

      static boolean_T rt_LoggedStateCrossMdlRef[] = {
        0,
        0
      };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedStateSignalInfo = {
        2,
        rt_LoggedStateWidths,
        rt_LoggedStateNumDimensions,
        rt_LoggedStateDimensions,
        rt_LoggedStateIsVarDims,
        (NULL),
        (NULL),
        rt_LoggedStateDataTypeIds,
        rt_LoggedStateComplexSignals,
        (NULL),

        { rt_LoggedStateLabels },
        (NULL),
        (NULL),
        (NULL),

        { rt_LoggedStateBlockNames },

        { rt_LoggedStateNames },
        rt_LoggedStateCrossMdlRef,
        rt_RTWLogDataTypeConvert
      };

      static void * rt_LoggedStateSignalPtrs[2];
      rtliSetLogXSignalPtrs(xpcosc_rtM->rtwLogInfo, (LogSignalPtrsType)
                            rt_LoggedStateSignalPtrs);
      rtliSetLogXSignalInfo(xpcosc_rtM->rtwLogInfo, &rt_LoggedStateSignalInfo);
      rt_LoggedStateSignalPtrs[0] = (void*)&xpcosc_X.Integrator1_CSTATE;
      rt_LoggedStateSignalPtrs[1] = (void*)&xpcosc_X.Integrator_CSTATE;
    }

    rtliSetLogT(xpcosc_rtM->rtwLogInfo, "tout");
    rtliSetLogX(xpcosc_rtM->rtwLogInfo, "xout");
    rtliSetLogXFinal(xpcosc_rtM->rtwLogInfo, "");
    rtliSetSigLog(xpcosc_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(xpcosc_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(xpcosc_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(xpcosc_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(xpcosc_rtM->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &xpcosc_Y.Outport[0]
      };

      rtliSetLogYSignalPtrs(xpcosc_rtM->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
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

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4
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
        "xpcosc/Outport" };

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
          rt_LoggedCurrentSignalDimensionsSize,
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

      rtliSetLogYSignalInfo(xpcosc_rtM->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(xpcosc_rtM->rtwLogInfo, "yout");
  }

  /* External mode info */
  xpcosc_rtM->Sizes.checksums[0] = (3002493303U);
  xpcosc_rtM->Sizes.checksums[1] = (1263664876U);
  xpcosc_rtM->Sizes.checksums[2] = (4128668038U);
  xpcosc_rtM->Sizes.checksums[3] = (2018944610U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    xpcosc_rtM->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(xpcosc_rtM->extModeInfo,
      &xpcosc_rtM->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(xpcosc_rtM->extModeInfo, xpcosc_rtM->Sizes.checksums);
    rteiSetTPtr(xpcosc_rtM->extModeInfo, rtmGetTPtr(xpcosc_rtM));
  }

  xpcosc_rtM->solverInfoPtr = (&xpcosc_rtM->solverInfo);
  xpcosc_rtM->Timing.stepSize = (0.00025);
  rtsiSetFixedStepSize(&xpcosc_rtM->solverInfo, 0.00025);
  rtsiSetSolverMode(&xpcosc_rtM->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  xpcosc_rtM->ModelData.blockIO = ((void *) &xpcosc_B);

  {
    xpcosc_B.Integrator1 = 0.0;
    xpcosc_B.RateTransition = 0.0;
    xpcosc_B.SignalGenerator = 0.0;
    xpcosc_B.RateTransition1 = 0.0;
    xpcosc_B.Gain = 0.0;
    xpcosc_B.Integrator = 0.0;
    xpcosc_B.Gain1 = 0.0;
    xpcosc_B.Gain2 = 0.0;
    xpcosc_B.PCI6220AD = 0.0;
    xpcosc_B.Sum = 0.0;
  }

  /* parameters */
  xpcosc_rtM->ModelData.defaultParam = ((real_T *)&xpcosc_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &xpcosc_X;
    xpcosc_rtM->ModelData.contStates = (x);
    (void) memset((void *)&xpcosc_X, 0,
                  sizeof(X_xpcosc_T));
  }

  /* states (dwork) */
  xpcosc_rtM->ModelData.dwork = ((void *) &xpcosc_DW);
  (void) memset((void *)&xpcosc_DW, 0,
                sizeof(DW_xpcosc_T));
  xpcosc_DW.RateTransition_Buffer0 = 0.0;
  xpcosc_DW.PCI6713DA_RWORK = 0.0;

  /* external outputs */
  xpcosc_rtM->ModelData.outputs = (&xpcosc_Y);
  xpcosc_Y.Outport[0] = 0.0;
  xpcosc_Y.Outport[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    xpcosc_rtM->SpecialInfo.mappingInfo = (&dtInfo);
    xpcosc_rtM->SpecialInfo.xpcData = ((void*) &dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  xpcosc_InitializeDataMapInfo(xpcosc_rtM);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &xpcosc_rtM->NonInlinedSFcns.sfcnInfo;
    xpcosc_rtM->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(xpcosc_rtM)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &xpcosc_rtM->Sizes.numSampTimes);
    xpcosc_rtM->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(xpcosc_rtM)[0]);
    xpcosc_rtM->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr(xpcosc_rtM)[1]);
    xpcosc_rtM->NonInlinedSFcns.taskTimePtrs[2] = &(rtmGetTPtr(xpcosc_rtM)[2]);
    rtssSetTPtrPtr(sfcnInfo,xpcosc_rtM->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(xpcosc_rtM));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(xpcosc_rtM));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(xpcosc_rtM));
    rtssSetStepSizePtr(sfcnInfo, &xpcosc_rtM->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(xpcosc_rtM));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &xpcosc_rtM->ModelData.derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &xpcosc_rtM->ModelData.zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo, &xpcosc_rtM->ModelData.blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo, &xpcosc_rtM->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &xpcosc_rtM->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &xpcosc_rtM->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &xpcosc_rtM->solverInfoPtr);
  }

  xpcosc_rtM->Sizes.numSFcns = (2);

  /* register each child */
  {
    (void) memset((void *)&xpcosc_rtM->NonInlinedSFcns.childSFunctions[0], 0,
                  2*sizeof(SimStruct));
    xpcosc_rtM->childSfunctions =
      (&xpcosc_rtM->NonInlinedSFcns.childSFunctionPtrs[0]);
    xpcosc_rtM->childSfunctions[0] =
      (&xpcosc_rtM->NonInlinedSFcns.childSFunctions[0]);
    xpcosc_rtM->childSfunctions[1] =
      (&xpcosc_rtM->NonInlinedSFcns.childSFunctions[1]);

    /* Level2 S-Function Block: xpcosc/<Root>/PCI-6713 DA (danipci671x) */
    {
      SimStruct *rts = xpcosc_rtM->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = xpcosc_rtM->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = xpcosc_rtM->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = xpcosc_rtM->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &xpcosc_rtM->NonInlinedSFcns.blkInfo2[0]);
      }

      ssSetRTWSfcnInfo(rts, xpcosc_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &xpcosc_rtM->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &xpcosc_rtM->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &xpcosc_rtM->NonInlinedSFcns.statesInfo2[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &xpcosc_rtM->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &xpcosc_rtM->NonInlinedSFcns.Sfcn0.UPtrs0;
          sfcnUPtrs[0] = &xpcosc_B.RateTransition1;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6713 DA");
      ssSetPath(rts, "xpcosc/PCI-6713 DA");
      ssSetRTModel(rts,xpcosc_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 6);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)xpcosc_P.PCI6713DA_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)xpcosc_P.PCI6713DA_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)xpcosc_P.PCI6713DA_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)xpcosc_P.PCI6713DA_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)xpcosc_P.PCI6713DA_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)xpcosc_P.PCI6713DA_P6_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &xpcosc_DW.PCI6713DA_RWORK);
      ssSetIWork(rts, (int_T *) &xpcosc_DW.PCI6713DA_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* RWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &xpcosc_DW.PCI6713DA_RWORK);

        /* IWORK */
        ssSetDWorkWidth(rts, 1, 2);
        ssSetDWorkDataType(rts, 1,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &xpcosc_DW.PCI6713DA_IWORK[0]);
      }

      /* registration */
      danipci671x(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 2;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }

    /* Level2 S-Function Block: xpcosc/<Root>/PCI-6220 AD (adnipcim) */
    {
      SimStruct *rts = xpcosc_rtM->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod = xpcosc_rtM->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset = xpcosc_rtM->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = xpcosc_rtM->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &xpcosc_rtM->NonInlinedSFcns.blkInfo2[1]);
      }

      ssSetRTWSfcnInfo(rts, xpcosc_rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &xpcosc_rtM->NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &xpcosc_rtM->NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &xpcosc_rtM->NonInlinedSFcns.statesInfo2[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &xpcosc_rtM->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *) &xpcosc_B.PCI6220AD));
        }
      }

      /* path info */
      ssSetModelName(rts, "PCI-6220 AD");
      ssSetPath(rts, "xpcosc/PCI-6220 AD");
      ssSetRTModel(rts,xpcosc_rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)xpcosc_P.PCI6220AD_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)xpcosc_P.PCI6220AD_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)xpcosc_P.PCI6220AD_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)xpcosc_P.PCI6220AD_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)xpcosc_P.PCI6220AD_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)xpcosc_P.PCI6220AD_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)xpcosc_P.PCI6220AD_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &xpcosc_DW.PCI6220AD_IWORK[0]);
      ssSetPWork(rts, (void **) &xpcosc_DW.PCI6220AD_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &xpcosc_rtM->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 41);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &xpcosc_DW.PCI6220AD_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidth(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &xpcosc_DW.PCI6220AD_PWORK);
      }

      /* registration */
      adnipcim(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 2;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }
  }

  /* Initialize Sizes */
  xpcosc_rtM->Sizes.numContStates = (2);/* Number of continuous states */
  xpcosc_rtM->Sizes.numY = (2);        /* Number of model outputs */
  xpcosc_rtM->Sizes.numU = (0);        /* Number of model inputs */
  xpcosc_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  xpcosc_rtM->Sizes.numSampTimes = (3);/* Number of sample times */
  xpcosc_rtM->Sizes.numBlocks = (13);  /* Number of blocks */
  xpcosc_rtM->Sizes.numBlockIO = (10); /* Number of block outputs */
  xpcosc_rtM->Sizes.numBlockPrms = (47);/* Sum of parameter "widths" */
  return xpcosc_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
