/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_dma.c
** Last modified Date:  2013-04-23
** Last Version:        v1.0
** Description:         dmaģ��Ĵ�����װ����ʵ������
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_dma.h"


/*********************************************************************************************************
** Function name:       DMAModeSet
** Descriptions:        DMAģ�鹤��ģʽ����
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      ucConfig        DMA���ò���������ȡ���м�������Ļ�
**                      DMA_DIR_M_READ            //  �Ӵ洢��������֮Ϊ�����
**                      DMA_CIRC_EN               //  ִ��ѭ������ģʽ
**                      DMA_PINC_EN               //  ʹ�������ַ����ģʽ
**                      DMA_MINC_EN               //  ʹ�ܴ洢����ַ����ģʽ
**                      //  �����ĸ�����ȡ���е�һ��������ֵ���л�����
**                      DMA_PSIZE_8               //  �������ݿ��Ϊ8λ
**                      DMA_PSIZE_16              //  �������ݿ��Ϊ16λ
**                      DMA_PSIZE_32              //  �������ݿ��Ϊ32λ
**                      DMA_PSIZE_RESERVED        //  �������ݿ�ȱ���
**                      //  �����ĸ�����ȡ���е�һ��������ֵ���л�����
**                      DMA_MSIZE_8               //  �洢�����ݿ��Ϊ8λ
**                      DMA_MSIZE_16              //  �洢�����ݿ��Ϊ16λ
**                      DMA_MSIZE_32              //  �洢�����ݿ��Ϊ32λ
**                      DMA_MSIZE_RESERVED        //  �洢�����ݿ�ȱ���
**                      //  �����ĸ�����ȡ���е�һ��������ֵ���л�����
**                      DMA_PL_LOW                //  ͨ�����ȼ�Ϊ��
**                      DMA_PL_MEDIUM             //  ͨ�����ȼ�Ϊ��
**                      DMA_PL_HIGH               //  ͨ�����ȼ�Ϊ��
**                      DMA_PL_HITHEST            //  ͨ�����ȼ�Ϊ���
**
**                      DMA_MTOM_EN               //  �洢�����洢������ģʽʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAModeSet(unsigned long ulBase, unsigned char ucChannel,unsigned long ulConfig)
{
    unsigned long ulTemp;
    ulTemp = HWREG32(ulBase + DMA_O_CCR1 + (ucChannel-1)*0x14);
    ulTemp &= 0xFFFF800F;
    ulTemp |= ulConfig;
    HWREG32(ulBase + DMA_O_CCR1+ (ucChannel-1)*0x14)= ulTemp;
}

/*********************************************************************************************************
** Function name:       DMAAddrSet
** Descriptions:        DMA����洢����ַ�������ַ����
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      ulMemAddr       ָ��DMA����Ĵ洢����ַ
**                      ulPeriAddr      ָ��DMA����������ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAAddrSet(unsigned long ulBase, unsigned char ucChannel, 
                unsigned long ulMemAddr, unsigned long ulPeriAddr)
{
    HWREG32(ulBase + DMA_O_CPAR1 + (ucChannel-1)*0x14)= ulPeriAddr;
    HWREG32(ulBase + DMA_O_CMAR1 + (ucChannel-1)*0x14)= ulMemAddr;
}

/*********************************************************************************************************
** Function name:       DMABufferSizeSet
** Descriptions:        DMAģ�鴫�����ݻ�������С����
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      usSize          ָ������Ĵ�С
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMABufferSizeSet(unsigned long ulBase, unsigned char ucChannel, unsigned short usSize)
{
    HWREG32(ulBase + DMA_O_CNDTR1 + (ucChannel-1)*0x14)= usSize;
}

/*********************************************************************************************************
** Function name:       DMAEnable
** Descriptions:        DMAģ��ʹ��
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAEnable(unsigned long ulBase, unsigned char ucChannel)
{
    HWREG32(ulBase + DMA_O_CCR1 + (ucChannel-1)*0x14) |= 0x00000001;
}

/*********************************************************************************************************
** Function name:       DMAModeSet
** Descriptions:        DMAģ�����
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMADisable(unsigned long ulBase, unsigned char ucChannel)
{
    HWREG32(ulBase + DMA_O_CCR1 + (ucChannel-1)*0x14) &= 0xFFFFFFFE;
}

/*********************************************************************************************************
** Function name:       DMAIntEnable
** Descriptions:        DMA�ж�ʹ��
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      ulFlags         ָ��ʹ�ܵ��жϣ�����ȡ����ֵ�Ļ�
**                      DMA_INT_TC      //  ��������ж�
**                      DMA_INT_HT      //  ����һ��ʱ���ж�
**                      DMA_INT_TE      //  ��������ж�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAIntEnable(unsigned long ulBase, unsigned char ucChannel,unsigned long ulFlags)
{
    HWREG32(ulBase + DMA_O_CCR1 + (ucChannel-1)*0x14) |= ulFlags;
}

/*********************************************************************************************************
** Function name:       DMAIntDisable
** Descriptions:        DMA�жϽ���
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      ulFlags         ָ��ʹ�ܵ��жϣ�����ȡ����ֵ�Ļ�
**                      DMA_INT_TC      //  ��������ж�
**                      DMA_INT_HT      //  ����һ��ʱ���ж�
**                      DMA_INT_TE      //  ��������ж�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAIntDisable(unsigned long ulBase, unsigned char ucChannel,unsigned long ulFlags)
{
    HWREG32(ulBase + DMA_O_CCR1 + (ucChannel-1)*0x14) &= ~ulFlags;
}

/*********************************************************************************************************
** Function name:       DMAIntStatus
** Descriptions:        DMA�ж�״̬��ȡ
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
** output parameters:   NONE
** Returned value:      ��ǰͨ�����ж�״̬������Ϊ��������ֵ����������������DMA_INT_GLOBAL�Ļ�
**                      DMA_INT_GLOBAL����ʾȫ���ж�״̬��ֻҪ��������ֵ��һ����������ͳ���
**                      DMA_INT_TC      //  ��������ж�
**                      DMA_INT_HT      //  ����һ��ʱ���ж�
**                      DMA_INT_TE      //  ��������ж�
*********************************************************************************************************/
unsigned long DMAIntStatus(unsigned long ulBase, unsigned char ucChannel)
{
    unsigned long ulTemp;
    ulTemp = HWREG32(ulBase + DMA_O_ISR);
    ulTemp >>= (ucChannel - 1);
    
    return (ulTemp);
}

/*********************************************************************************************************
** Function name:       DMAIntStatus
** Descriptions:        DMA�жϽ���
** input parameters:    ulBase          DMAģ��Ļ���ַ
**                      ucChannel       DMAͨ����ţ�DMA1Ϊ1-7��DMA2Ϊ1-5
**                      ulIntFlags      ��ǰͨ�����ж�״̬������Ϊ��������ֵ�Ļ������DMA_INT_GLOBAL�Ļ�
**                      DMA_INT_GLOBAL����ʾȫ���ж�״̬��ֻҪ��������ֵ��һ����������ͳ���
**                      DMA_INT_TC      //  ��������ж�
**                      DMA_INT_HT      //  ����һ��ʱ���ж�
**                      DMA_INT_TE      //  ��������ж�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void DMAIntClear(unsigned long ulBase, unsigned char ucChannel,unsigned long ulIntFlags)
{
    unsigned long ulTemp = (ulIntFlags << (ucChannel - 1));
    
    HWREG32(ulBase + DMA_O_IFCR) |= ulTemp;
    
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
