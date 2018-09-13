/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               rtime-arch.h
** Last modified Date:      2012-07-03
** Last Version:            v1.0
** Description:             Hardware-dependent function declarations used to support the 
**                          contiki rtimer module.
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-07-03
** Version:                 v1.0
** Descriptions:            The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/
#ifndef __RTIMER_ARCH_H__
#define __RTIMER_ARCH_H__

#include "contiki-conf.h"
#include "sys/rtimer.h"
#include "sys/clock.h"

#include "infra/rhb_type.h"
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_rcc.h"
#include "hal/arch/inc/arch_io_ints.h"
#include "hal/CortexM3/hal_io_level.h"


#define RTIMER_ARCH_USE_BASE  TIM2_BASE   // ʹ��TIM1��Ϊrtimer��ʱ��
#define RTIMER_INT_NO         INT_TIM2    // �жϱ��
#define RT_PRESCALER          639        // ��ʱ����Ԥ��Ƶֵ��PCLK1/4096 = 32M / (639 + 1) = 50000 Hz
#define RTIMER_ARCH_SECOND    50000        // One tick: 20 us. 

void rtimer_arch_set(rtimer_clock_t t);

rtimer_clock_t rtimer_arch_now(void);


#endif // __RTIMER_ARCH_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/