/*
 * xpcosc_private.h
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
#ifndef RTW_HEADER_xpcosc_private_h_
#define RTW_HEADER_xpcosc_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

extern const serialfifoptr serialfifoground;
extern const bcmsglist1553 bcmsg1553ground;
extern const bcstatus1553 bcstatground;
extern const bmmsglist1553 bmmsg1553ground;
extern void danipci671x(SimStruct *rts);
extern void adnipcim(SimStruct *rts);
void xpcosc_output0(void);
void xpcosc_update0(void);
void xpcosc_output2(void);
void xpcosc_update2(void);             /* private model entry point functions */
extern void xpcosc_derivatives(void);

#endif                                 /* RTW_HEADER_xpcosc_private_h_ */
