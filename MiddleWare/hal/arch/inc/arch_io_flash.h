/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_flash.h
** Last modified Date:  2013-04-04
** Last Version:        v1.0
** Description:         flashģ��Ĵ�����װ����ʵ������
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
#ifndef __ARCH_IO_FLASH_H__
#define __ARCH_IO_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"
  
/*********************************************************************************************************
**  �����豸�Ƿ���STM32F10xx XL-densityϵ��.1:��XLϵ�У�0������XLϵ��
*********************************************************************************************************/
#define STM32F10XX_XL_Density       1

/*********************************************************************************************************
**  ����BANK1������ַ�������ж�BANK2�Ĵ���
*********************************************************************************************************/
#define FLASH_BANK1_END_ADDRESS   ((uint32)0x807FFFF)

/*********************************************************************************************************
** �ⲿ����ʹ�õ�����
*********************************************************************************************************/
extern void flashUnlock(void);
extern void flashLock(void);
extern boolean flashPageErase(unsigned long ulPageAddr);
extern boolean flashMassErase(void);
extern boolean flashWriteHalfWord(unsigned long ulAddr, unsigned short usData);
extern boolean flashProgram(unsigned short *pusData, unsigned long ulAddr, unsigned long ulSize);
extern boolean flashConstDataProgram(unsigned short usData, unsigned long ulAddr, unsigned long ulSize);


#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_FLASH_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
