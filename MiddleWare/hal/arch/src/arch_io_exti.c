/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_exti.c
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_exti.h"


/*********************************************************************************************************
  �ֲ���������
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       ExtiIntEnable
** Descriptions:        EXTI�ж�ʹ��
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiIntEnable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_IMR) |= ((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntDisable
** Descriptions:        EXTI�жϽ�ֹ
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiIntDisable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_IMR) &= ~((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiEventEnable
** Descriptions:        EXTI�¼�ʹ��
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiEventEnable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_EMR) |= ((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiEventDisable
** Descriptions:        EXTI�¼���ֹ
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiEventDisable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_EMR) &= ~((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntEventRisingEnable
** Descriptions:        EXTI�жϼ��¼�������ʹ��
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
** ע�⣺�������غ��½���ͬʱʹ�ܵ�ʱ����ͬʱ��Ч
*********************************************************************************************************/
void ExtiIntEventRisingEnable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_RTSR) |= ((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntEventRisingDisable
** Descriptions:        EXTI�жϼ��¼������ؽ�ֹ
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
** ע�⣺�������غ��½���ͬʱʹ�ܵ�ʱ����ͬʱ��Ч
*********************************************************************************************************/
void ExtiIntEventRisingDisable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_RTSR) &= ~((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntEventFallingEnable
** Descriptions:        EXTI�жϼ��¼��½���ʹ��
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
** ע�⣺�������غ��½���ͬʱʹ�ܵ�ʱ����ͬʱ��Ч
*********************************************************************************************************/
void ExtiIntEventFallingEnable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_FTSR) |= ((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntEventFallingDisable
** Descriptions:        EXTI�жϼ��¼��½��ؽ�ֹ
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
** ע�⣺�������غ��½���ͬʱʹ�ܵ�ʱ����ͬʱ��Ч
*********************************************************************************************************/
void ExtiIntEventFallingDisable(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_FTSR) &= ~((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiSoftInterruptTrigger
** Descriptions:        EXTI�жϼ��¼��������
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiSoftInterruptTrigger(uint32 u32Line)
{
    HWREG32(EXTI_BASE + EXTI_O_SWIER) |= ((uint32)1 << u32Line);
}

/*********************************************************************************************************
** Function name:       ExtiIntEventClear
** Descriptions:        EXTI�жϼ��¼����
** input parameters:    u32Line:    �ⲿӲ���жϺţ�ȡ0-22
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void ExtiIntEventClear(uint32 u32Line)
{
     HWREG32(EXTI_BASE + EXTI_O_PR) |= ((uint32)1 << u32Line);
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
