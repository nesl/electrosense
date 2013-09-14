#ifndef __UnWaterChannelProbeTestSymmetry_XPCOPTIONS_H___
#define __UnWaterChannelProbeTestSymmetry_XPCOPTIONS_H___
#include "simstruc_types.h"
#ifndef MT
#define MT                             0                         /* MT may be undefined by simstruc_types.h */
#endif

#include "UnWaterChannelProbeTestSymmetry.h"
#define XPCMDSSUPPORT                  0
#define MDSTASKSNUM                    0
#define FULLMULTITHREAD                0
#define SIZEOF_PARAMS                  (-1 * (int)sizeof(Parameters_UnWaterChannelProbeTestSymmetry))
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
void UnWaterChannelProbeTestSymmetry_ChangeStepSize(real_T newBaseRateStepSize,
  rtModel_UnWaterChannelProbeTestSymmetry *const
  UnWaterChannelProbeTestSymmetry_rtM)
{
  real_T ratio = newBaseRateStepSize / 0.0001;

  /* update non-zore stepsize of periodic
   * sample time. Stepsize of asynchronous
   * sample time is not changed in this function */
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0 =
    UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize0 * ratio;
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize1 =
    UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize1 * ratio;
  UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize =
    UnWaterChannelProbeTestSymmetry_rtM->Timing.stepSize * ratio;
}

void XPCCALLCONV changeStepSize(real_T stepSize)
{
  /* Change all stepsize using the newBaseRateStepSize */
  UnWaterChannelProbeTestSymmetry_ChangeStepSize(stepSize,
    UnWaterChannelProbeTestSymmetry_rtM);
}

#endif                                 /* __UnWaterChannelProbeTestSymmetry_XPCOPTIONS_H___ */
