/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_dma.h
** Last modified Date:  2013-04-23
** Last Version:        v1.0
** Description:         DMAģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-23
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
#ifndef __ARCH_IO_DMA_H__
#define __ARCH_IO_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"

/*********************************************************************************************************
** ��Ҫ�ĺ궨��
*********************************************************************************************************/
//  DMA������ز�����Ϊ����DMAModeSet�Ĳ���ulConfig
#define DMA_DIR_M_READ      0x00000010      //  �Ӵ洢��������֮Ϊ�����

#define DMA_CIRC_EN         0x00000020      //  ִ��ѭ������ģʽ
#define DMA_PINC_EN         0x00000040      //  ʹ�������ַ����ģʽ
#define DMA_MINC_EN         0x00000080      //  ʹ�ܴ洢����ַ����ģʽ

#define DMA_PSIZE_8         0x00000000      //  �������ݿ��Ϊ8λ
#define DMA_PSIZE_16        0x00000100      //  �������ݿ��Ϊ16λ
#define DMA_PSIZE_32        0x00000200      //  �������ݿ��Ϊ32λ
#define DMA_PSIZE_RESERVED  0x00000300      //  �������ݿ�ȱ���

#define DMA_MSIZE_8         0x00000000      //  �洢�����ݿ��Ϊ8λ
#define DMA_MSIZE_16        0x00000400      //  �洢�����ݿ��Ϊ16λ
#define DMA_MSIZE_32        0x00000800      //  �洢�����ݿ��Ϊ32λ
#define DMA_MSIZE_RESERVED  0x00000C00      //  �洢�����ݿ�ȱ���

#define DMA_PL_LOW          0x00000000      //  ͨ�����ȼ�Ϊ��
#define DMA_PL_MEDIUM       0x00001000      //  ͨ�����ȼ�Ϊ��
#define DMA_PL_HIGH         0x00002000      //  ͨ�����ȼ�Ϊ��
#define DMA_PL_HITHEST      0x00003000      //  ͨ�����ȼ�Ϊ���

#define DMA_MTOM_EN         0x00004000      //  �洢�����洢������ģʽʹ��
//  ��ص��ж��źŶ��壬Ϊ�ж���غ����Ĳ����򷵻�ֵ
#define DMA_INT_TC          0x00000002      //  ��������ж�
#define DMA_INT_HT          0x00000004      //  ����һ��ʱ���ж�
#define DMA_INT_TE          0x00000008      //  ��������ж�
#define DMA_INT_GLOBAL      0x00000001      //  ȫ���жϣ�ֻҪ����������һ����������ͳ���

/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern void DMAModeSet(unsigned long ulBase, unsigned char ucChannel,unsigned long ulConfig);
extern void DMAAddrSet(unsigned long ulBase, unsigned char ucChannel, 
                unsigned long ulMemAddr, unsigned long ulPeriAddr);
extern void DMABufferSizeSet(unsigned long ulBase, unsigned char ucChannel, unsigned short usSize);
extern void DMAEnable(unsigned long ulBase, unsigned char ucChannel);
extern void DMADisable(unsigned long ulBase, unsigned char ucChannel);
extern void DMAIntEnable(unsigned long ulBase, unsigned char ucChannel,unsigned long ulFlags);
extern void DMAIntDisable(unsigned long ulBase, unsigned char ucChannel,unsigned long ulFlags);
extern unsigned long DMAIntStatus(unsigned long ulBase, unsigned char ucChannel);
extern void DMAIntClear(unsigned long ulBase, unsigned char ucChannel,unsigned long ulIntFlags);

#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_DMA_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
