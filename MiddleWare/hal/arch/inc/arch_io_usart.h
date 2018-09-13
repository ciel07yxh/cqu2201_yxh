/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_usart.h
** Last modified Date:  2013-04-02
** Last Version:        v1.0
** Description:         usart��uartģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-02
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
#ifndef __ARCH_IO_USART_H__
#define __ARCH_IO_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"

/*********************************************************************************************************
** ��Ҫ�ĺ궨��
*********************************************************************************************************/
//  �������ú���UsartConfigSet�Ĳ�������,�ú�����12λ������ж�д��Ĵ���
#define USART_STOP_0_5      0x0001
#define USART_STOP_1        0x0000
#define UASRT_STOP_1_5      0x0003
#define USART_STOP_2        0x0002

#define USART_WLEN_8        0x0000
#define USART_WLEN_9        0x1000

#define USART_PAR_NONE      0x0000
#define USART_PAR_EVEN      0x0400
#define USART_PAR_ODD       0x0600

#define USART_DMA_TX        0x0080    //  DMA���͹���
#define USART_DMA_RX        0x0040    //  DMA���ܹ���
//  �����ж�Դ��Ϊ����UsartIntEnable()�Ĳ���
#define USART_INT_TX_EMPTY  0x0080      //  ���ͻ��������ж�
#define USART_INT_TX_FINISH 0x0040      //  ��������ж�
#define USART_INT_RX        0x0020      //  �����ж�ʹ�ܣ�˵�����ռĴ�������������
#define USART_INT_IDLE      0x0010      //  IDLE�ж�ʹ��
/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern void UsartConfigSet(unsigned long ulBase, unsigned long ulClock, 
                            unsigned long ulBaud, unsigned long ulConfig);
extern void UsartEnable(unsigned long ulBase);
extern void UsartDisable(unsigned long ulBase);
extern void UsartDMAEnable(unsigned long ulBase,unsigned long ulFlags);
extern void UsartDMADisable(unsigned long ulBase, unsigned long ulFlags);
extern void UsartIntEnable(unsigned long ulBase,unsigned long ulIntFlags);
extern void UsartIntDisable(unsigned long ulBase,unsigned long ulIntFlags);
extern boolean UsartSpaceAvial(unsigned long ulBase);
extern void UsartCharPut(unsigned long ulBase,unsigned char ucData);
extern boolean UsartCharsAvial(unsigned long ulBase);
extern unsigned long  UsartCharGet(unsigned long ulBase);
extern void UsartPutS(unsigned long ulBase,const char *s);
extern void UsartPutN(unsigned long ulBase, const  char  *pStr , unsigned short  usNum);



#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_USART_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
