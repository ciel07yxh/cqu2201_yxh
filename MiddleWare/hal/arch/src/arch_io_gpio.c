/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_gpio.c
** Last modified Date:  2013-04-02
** Last Version:        v1.0
** Description:         gpioģ��Ĵ�����װ����ʵ������
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_gpio.h"


/*********************************************************************************************************
** Function name:       GPIOConfigSet
** Descriptions:        GPIO��������
** input parameters:    ulBase:     GPIOģ��Ļ���ַ
**                      usPin:      ָ�����õ�����
**                      ulConfig:   ���õĲ���,����ȡ����ֵ
**                      // IO����Ϊ����ʱȡ����ֵ�е�һ��
**                      GPIO_DIR_IN_Analog      //  ģ������ģʽ
**                      GPIO_DIR_IN_Floating    //  ��������ģʽ
**                      GPIO_DIR_IN_UpDown      //  ������������ģʽ
**
**                      // IO����Ϊ���ʱ����Ϊ��������ֵ�Ļ�
**                      GPIO_OUT_PP             //  ͨ������ģʽ���
**                      GPIO_OUT_OD             //  ͨ�ÿ�©ģʽ���
**                      GPIO_AF_PP              //  ��������ģʽ���
**                      GPIO_AF_OD              //  ���ÿ�©ģʽ���

**                      GPIO_SPEED_2MHZ         //  ����ٶ�Ϊ2MHz
**                      GPIO_SPEED_10MHZ        //  ����ٶ�Ϊ10MHz
**                      GPIO_SPEED_50MHZ        //  ����ٶ�Ϊ50MHz
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void GPIOConfigSet(unsigned long ulBase, unsigned short usPin, unsigned long ulConfig)
{
    unsigned char i;
    for(i=0; i<8; i++)
    {
        if(usPin & (1<<i))
        {
            HWREG32(ulBase + GPIO_O_CRL) &= ~(0x0F<<(4*i));
            HWREG32(ulBase + GPIO_O_CRL) |= (ulConfig<<(4*i));
            usPin &= ~(1<<i);
        }
        if(!(usPin & 0xFF))
            break;
    }
    
    usPin >>= 8;
    for(i=0; i<8; i++)
    {
        if(usPin & (1<<i))
        {
            HWREG32(ulBase + GPIO_O_CRH) &= ~(0x0F<<(4*i));
            HWREG32(ulBase + GPIO_O_CRH) |= (ulConfig<<(4*i));
            usPin &= ~(1<<i);
        }
        if(!(usPin & 0xFF))
            break;
    }
}

/*********************************************************************************************************
** Function name:       GPIODataPut
** Descriptions:        GPIO����������ú�����16λ����ʽ�������
** input parameters:    ulBase:     GPIOģ��Ļ���ַ
**                      usData:     ���������
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void GPIODataPut(unsigned long ulBase, unsigned short usData)
{
    HWREG32(ulBase + GPIO_O_ODR) = usData;
}

/*********************************************************************************************************
** Function name:       GPIODataGet
** Descriptions:        GPIO����������ú�����16λ����ʽ��������
** input parameters:    ulBase:     GPIOģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      ��ȡ����GPIO�˿ڵ�����
*********************************************************************************************************/
unsigned short GPIODataGet(unsigned long ulBase)
{
    return (HWREG32(ulBase + GPIO_O_IDR));
}

/*********************************************************************************************************
** Function name:       GPIOBitSet
** Descriptions:        GPIOλ����
** input parameters:    ulBase:     GPIOģ��Ļ���ַ
**                      usPin:      ָ��IO����
** output parameters:   NONE
** Returned value:      ��ȡ����GPIO�˿ڵ�����
*********************************************************************************************************/
void GPIOBitSet(unsigned long ulBase,unsigned short usPin)
{
    HWREG32(ulBase + GPIO_O_BSRR) = usPin;
}

/*********************************************************************************************************
** Function name:       GPIOBitReset
** Descriptions:        GPIOλ���
** input parameters:    ulBase:     GPIOģ��Ļ���ַ
**                      usPin:      ָ��IO����
** output parameters:   NONE
** Returned value:      ��ȡ����GPIO�˿ڵ�����
*********************************************************************************************************/
void GPIOBitReset(unsigned long ulBase,unsigned short usPin)
{
    HWREG32(ulBase + GPIO_O_BRR) = usPin;
}

/*********************************************************************************************************
** Function name:       GPIOToggleBit
** Descriptions:        ��תָ����IO����
** input parameters:    u32Base:  ָ��������GPIOģ�����ַ
**                      u32Pins�� ָ��������GPIO����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void GPIOToggleBit(uint32 u32Base, uint32 u32Pins)
{
    HWREG32(u32Base + GPIO_O_ODR) ^= u32Pins;
}
/*********************************************************************************************************
** Function name:       AFIORemapConfig
** Descriptions:        AFIO������ӳ������
** input parameters:    u32Base:     GPIOģ��Ļ���ַ
**                      u32Remap:    Remap����
** output parameters:   NONE
** Returned value:      ��ȡ����GPIO�˿ڵ�����
*********************************************************************************************************/
void AFIORemapEnable(uint32 u32Remap)
{
    HWREG32(AFIO_BASE + AFIO_O_MAPR) |= u32Remap;
}
/*********************************************************************************************************
** Function name:       AFIORemapReset
** Descriptions:        AFIO������ӳ��ر�
** input parameters:    u32Base:     GPIOģ��Ļ���ַ
**                      u32Remap:    Remap����
** output parameters:   NONE
** Returned value:      ��ȡ����GPIO�˿ڵ�����
*********************************************************************************************************/
void AFIORemapReset(uint32 u32Remap)
{
    HWREG32(AFIO_BASE + AFIO_O_MAPR) &= ~u32Remap;
}

/*********************************************************************************************************
** Function name:       AFIOExtiLineConfig
** Descriptions:        AFIO���ж������߿���
** input parameters:    u32GPIOLinex:   EXTI_GPIO_A....EXTI_GPIO_G
**                      u32Pin:         ָ�����õ�GPIO���ţ�ȡ0-15
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void AFIOExtiLineConfig(uint32 u32GPIOLinex, uint32 u32Pin)
{
    uint32 u32Temp = u32Pin / 4;
    uint32 u32Value = u32Pin % 4;

    u32Temp *= 4;
    u32Value *= 4;
    HWREG32(AFIO_BASE + AFIO_O_EXTICR1 + u32Temp) &= ~(((uint32)0x0000000F) << u32Value);
    HWREG32(AFIO_BASE + AFIO_O_EXTICR1 + u32Temp) |= (u32GPIOLinex << u32Value);
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
