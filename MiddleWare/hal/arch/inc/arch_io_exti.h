/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_exti.h
** Last modified Date:  2013-04-04
** Last Version:        v1.0
** Description:         extiģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-04
** Version:             v1.0
** Descriptions:        The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/
#ifndef __ARCH_IO_EXTI_H__
#define __ARCH_IO_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"

/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern void ExtiIntEnable(uint32 u32Line);
extern void ExtiIntDisable(uint32 u32Line);
extern void ExtiEventEnable(uint32 u32Line);
extern void ExtiEventDisable(uint32 u32Line);
extern void ExtiIntEventRisingEnable(uint32 u32Line);
extern void ExtiIntEventRisingDisable(uint32 u32Line);
extern void ExtiIntEventFallingEnable(uint32 u32Line);
extern void ExtiIntEventFallingDisable(uint32 u32Line);
extern void ExtiSoftInterruptTrigger(uint32 u32Line);
extern void ExtiIntEventClear(uint32 u32Line);


#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_EXTI_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
