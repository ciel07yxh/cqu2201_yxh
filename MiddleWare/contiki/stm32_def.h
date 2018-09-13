/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               stm32_def
** Last modified Date:      2012-07-27
** Last Version:            v1.0
** Description:             STM32��ض��壬���ļ���Ӧsys\cc.h�ڵĶ���
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-07-27
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
#ifndef __STM32_DEF_H__
#define __STM32_DEF_H__

#include <stdint.h>
/*********************************************************************************************************
** �궨�壬�����滻sys\cc.h�еĶ���
*********************************************************************************************************/
#define CC_CONF_FUNCTION_POINTER_ARGS       1
#define CC_CONF_FASTCALL
#define CC_CONF_VA_ARGS                     1
#define CC_CONF_UNSIGNED_CHAR_BUGS          0
#define CC_CONF_REGISTER_ARGS               0
#define CC_CONF_FUNCTION_POINTER_KEYWORD    __reentrant
//#define CC_CONF_NON_BANKED_OPTIMIZATION     1

/*********************************************************************************************************
** ���ã����ṩ�ܹ���ص�У�麯��
*********************************************************************************************************/
#define UIP_ARCH_ADD32    0
#define UIP_ARCH_CHKSUM	  0

/*********************************************************************************************************
** ͨ����������������
*********************************************************************************************************/
typedef unsigned char   u8_t;
typedef unsigned short  u16_t;
typedef unsigned long   u32_t;
typedef signed long     s32_t;
typedef unsigned short  uip_stats_t;
typedef unsigned long   clock_time_t;
typedef unsigned char   bool_t;
typedef unsigned long   rtimer_clock_t;

#define RTIMER_CLOCK_LT(a,b)     ((signed short)((a)-(b)) < 0)

#ifndef BV
#define BV(x) (1<<(x))
#endif

#ifndef NULL
#define NULL        (void *)0
#endif

#ifndef false
#define false       0
#endif

#ifndef true
#define true        (!false)
#endif

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
#define CCIF
#define CLIF
#define CC_CONF_CONST_FUNCTION_BUG

/*********************************************************************************************************
** �ٽ��������꺯������
*********************************************************************************************************/
#include "hal/CortexM3/hal_io_level.h"
#define splhigh()    ((int)hal_enter_critical(0));
#define splx(s)      hal_exit_critical(s);

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
#define CC_CONF_ASSIGN_AGGREGATE(dest, src)	\
    memcpy(dest, src, sizeof(*dest))

#define uip_ipaddr_copy(dest, src)		\
    memcpy(dest, src, sizeof(*dest))

#endif /* __STM32_DEF_H__ */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/