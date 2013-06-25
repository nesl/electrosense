#ifndef __UnWaterChannelProbe_XPCOPTIONS_H___
#define __UnWaterChannelProbe_XPCOPTIONS_H___
#include "simstruc_types.h"
#ifndef MT
#define MT                             0                         /* MT may be undefined by simstruc_types.h */
#endif

#include "UnWaterChannelProbe.h"
#define XPCMDSSUPPORT                  0
#define MDSTASKSNUM                    0
#define FULLMULTITHREAD                0
#define SIZEOF_PARAMS                  (-1 * (int)sizeof(Parameters_UnWaterChannelProbe))
#define SIMMODE                        0
#define LOGTET                         1
#define LOGBUFSIZE                     100000
#define PROFILINGFLAG                  0
#define EVENTNUMBER                    5000
#define IRQ_NO                         0
#define IO_IRQ                         0
#define WWW_ACCESS_LEVEL               0
#define CPUCLOCK                       0
#define MAXOVERLOAD                    0
#define MAXOVERLOADLEN                 0
#define XPCSTARTUPFLAG                 1
#define PTLOADPARAMFLAG                0

/* Change all stepsize using the newBaseRateStepSize */
void UnWaterChannelProbe_ChangeStepSize(real_T newBaseRateStepSize,
  rtModel_UnWaterChannelProbe *const UnWaterChannelProbe_rtM)
{
  real_T ratio = newBaseRateStepSize / 0.0001;

  /* update non-zore stepsize of periodic
   * sample time. Stepsize of asynchronous
   * sample time is not changed in this function */
  UnWaterChannelProbe_rtM->Timing.stepSize0 =
    UnWaterChannelProbe_rtM->Timing.stepSize0 * ratio;
  UnWaterChannelProbe_rtM->Timing.stepSize1 =
    UnWaterChannelProbe_rtM->Timing.stepSize1 * ratio;
  UnWaterChannelProbe_rtM->Timing.stepSize2 =
    UnWaterChannelProbe_rtM->Timing.stepSize2 * ratio;
  UnWaterChannelProbe_rtM->Timing.stepSize =
    UnWaterChannelProbe_rtM->Timing.stepSize * ratio;
}

void XPCCALLCONV changeStepSize(real_T stepSize)
{
  /* Change all stepsize using the newBaseRateStepSize */
  UnWaterChannelProbe_ChangeStepSize(stepSize, UnWaterChannelProbe_rtM);
}

#endif                                 /* __UnWaterChannelProbe_XPCOPTIONS_H___ */
