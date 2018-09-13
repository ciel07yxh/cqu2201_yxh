/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_usart.c
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_usart.h"


/*********************************************************************************************************
** Function name:       UsartConfigSet
** Descriptions:        usartģ������
** input parameters:    ulBase  usartģ�����ַ
**                      ulClock �ṩ��usartģ���ʱ�ӣ�usart1ΪAPB2��ʱ�ӣ����72M������ΪAPB1��ʱ�ӣ����36M
**                      ulBaud  ͨ�Ų�����,ֱ��ָ������
**                      ulConfig ������Ϣ������ȡ��������ֵ�Ļ�
**                      USART_STOP_0_5          //  0.5λֹͣλ
**                      USART_STOP_1            //  1λֹͣλ
**                      UASRT_STOP_1_5          //  1.5λֹͣλ
**                      USART_STOP_2            //  2λֹͣλ

**                      USART_WLEN_8            //  �ֳ�Ϊ8
**                      USART_WLEN_9            //  �ֳ�Ϊ9

**                      USART_PAR_NONE          //  ��У��
**                      USART_PAR_EVEN          //  żУ��
**                      USART_PAR_ODD           //  ��У��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartConfigSet(unsigned long ulBase, unsigned long ulClock, 
                    unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulTemp;
    unsigned long ulIntergerDiv;
    unsigned long ulFloatDiv;
    
    //  ����ֹͣλ�������üĴ���CR2
    ulTemp = HWREG32(ulBase + USART_O_CR2);
    ulTemp &= 0xCFFF;
    ulTemp |= (ulConfig << 12);
    HWREG32(ulBase + USART_O_CR2) = ulTemp;
    
    //  ���üĴ���CR1���������ֳ���У��
    ulTemp = HWREG32(ulBase + USART_O_CR1);
    ulTemp &= 0xE9F3;
    ulTemp |= ulConfig;
    ulTemp |= 0x000C;    //  ʹ�ܷ��ͺͽ���
    HWREG32(ulBase + USART_O_CR1) = ulTemp;
    
    //  ע�⣺���ع���������ʱ�����ã���Ҫ�Ļ���������Ӵ���
    
    //  ���ݲ����ʼ���BRR�Ĵ�����ֵ����д������
    //  �ȼ�����������
    if((HWREG32(ulBase + USART_O_CR1)) & 0x8000) {
        ulIntergerDiv = ((25 * ulClock) / (2 * ulBaud));
    } else {
        ulIntergerDiv = ((25 * ulClock) / (4 * ulBaud));
    }
    ulTemp = ((ulIntergerDiv / 100) << 4);
    //  ����С������
    ulFloatDiv = ulIntergerDiv - (100*(ulTemp >> 4));
    if((HWREG32(ulBase + USART_O_CR1)) & 0x8000) {
        ulTemp |= ((((ulFloatDiv * 8) + 50) / 100)) & ((unsigned char)0x07);
    } else {
        ulTemp |= ((((ulFloatDiv * 16) + 50) / 100)) & ((unsigned char)0x0F);
    }
    
    HWREG32(ulBase + USART_O_BRR) = ulTemp;
}

/*********************************************************************************************************
** Function name:       UsartEnable
** Descriptions:        usartģ��ʹ�ܣ�ʹ�ܺ�ģ�������������
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartEnable(unsigned long ulBase)
{
    HWREG32(ulBase + USART_O_CR1) |= 0x2000;
}

/*********************************************************************************************************
** Function name:       UsartDisable
** Descriptions:        usartģ����ܣ����ܺ�ģ�����ֹͣ����������������usartǰͨ���ȵ��øú���
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartDisable(unsigned long ulBase)
{
    HWREG32(ulBase + USART_O_CR1) &= 0xDFFF;
}


/*********************************************************************************************************
** Function name:       UsartDMAEnable
** Descriptions:        usartģ��DMA����ʹ��
** input parameters:    ulBase  usartģ�����ַ
**                      ulFlags ָ��ʹ�ܵ�DMA���ܣ�����ȡ����ֵ
**                      USART_DMA_TX    //  DMA���͹���
**                      USART_DMA_RX    //  DMA���ܹ���
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartDMAEnable(unsigned long ulBase,unsigned long ulFlags)
{
  HWREG32(ulBase + USART_O_CR3) |= ulFlags;
}
/*********************************************************************************************************
** Function name:       UsartDMADisable
** Descriptions:        usartģ��DMA���ܽ���
** input parameters:    ulBase  usartģ�����ַ
**                      ulFlags ָ�����ܵ�DMA���ܣ�����ȡ����ֵ
**                      USART_DMA_TX    //  DMA���͹���
**                      USART_DMA_RX    //  DMA���ܹ���
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartDMADisable(unsigned long ulBase, unsigned long ulFlags)
{
  HWREG32(ulBase + USART_O_CR3) &= ~ulFlags;
}
/*********************************************************************************************************
** Function name:       UsartIntEnable
** Descriptions:        usartģ���ж�ʹ��
** input parameters:    ulBase:     usartģ�����ַ
**                      ulIntFlags: ��Ҫʹ�ܵ��ж�, ��������г����õ��жϣ������Ŀ���ͨ���Ĵ������ã�����
**                                  ȡ����ֵ�Ļ�
**                      USART_INT_TX_EMPTY          //  ���ͻ��������ж�
**                      USART_INT_TX_FINISH         //  ��������ж�
**                      USART_INT_RX                //  �����ж�ʹ�ܣ�˵�����ռĴ�������������
**                      USART_INT_IDLE              //  IDLE�ж�ʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartIntEnable(unsigned long ulBase,unsigned long ulIntFlags)
{
    HWREG32(ulBase + USART_O_CR1) |= ulIntFlags;
}

/*********************************************************************************************************
** Function name:       UsartIntEnable
** Descriptions:        usartģ���жϽ���
** input parameters:    ulBase:     usartģ�����ַ
**                      ulIntFlags: ��Ҫ���ܵ��ж�, ��������г����õ��жϣ������Ŀ���ͨ���Ĵ������ã�����
**                                  ȡ����ֵ�Ļ�
**                      USART_INT_TX_EMPTY          //  ���ͻ��������ж�
**                      USART_INT_TX_FINISH         //  ��������ж�
**                      USART_INT_RX                //  �����ж�ʹ�ܣ�˵�����ռĴ�������������
**                      USART_INT_IDLE              //  IDLE�ж�ʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartIntDisable(unsigned long ulBase,unsigned long ulIntFlags)
{
    HWREG32(ulBase + USART_O_CR1) &= ~ulIntFlags;
}

/*********************************************************************************************************
** Function name:       UsartSpaceAvial
** Descriptions:        �жϷ��ͼĴ����Ƿ�Ϊ�գ����Ƿ���Է�����һ������
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      true: ���Է�����һ������ ��false�����ܷ�����һ������
*********************************************************************************************************/
boolean UsartSpaceAvial(unsigned long ulBase)
{
    if (HWREG32(ulBase + USART_O_SR) & 0x0080)
        return true;
    else
        return false;
}

/*********************************************************************************************************
** Function name:       UsartCharPut
** Descriptions:        ��������
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartCharPut(unsigned long ulBase,unsigned char ucData)
{
    HWREG32(ulBase + USART_O_DR) = ucData;           //  ������д�뷢�ͼĴ���
}

/*********************************************************************************************************
** Function name:       UsartCharsAvial
** Descriptions:        �жϽ��ռĴ������Ƿ��п�������
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      true: ���ܼĴ������п������ݣ����Զ���; false: ���ռĴ������޿�������
*********************************************************************************************************/
boolean UsartCharsAvial(unsigned long ulBase)
{
    if(HWREG32(ulBase + USART_O_SR) & 0x0020)
        return true;
    else
        return false;
}

/*********************************************************************************************************
** Function name:       UsartCharPut
** Descriptions:        �������ݣ����ӽ��ռĴ����ж�������
** input parameters:    ulBase  usartģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
unsigned long  UsartCharGet(unsigned long ulBase)
{
    return (HWREG32(ulBase + USART_O_DR) & 0x01FF);   //  �������ݣ���9Ϊ��Ч
}

/*********************************************************************************************************
** Function name:       UsartPutS
** Descriptions:        ����һ��ָ�����ַ���
** input parameters:    ulBase: usartģ�����ַ
**                      s:      ָ�����͵��ַ���
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartPutS(unsigned long ulBase,const char *s)
{
    while (*s != '\0') {
       while(!(UsartSpaceAvial(ulBase))) ;          //  �ȴ����ͼĴ�������
       UsartCharPut(ulBase,*(s++));
    }
}
/*********************************************************************************************************
** Function name:       UsartPutS
** Descriptions:        ����һ��ָ�����ȵ��ַ���
** input parameters:    ulBase: usartģ�����ַ
**                      s:      ָ�������ַ����Ļ���ַ
**                      usNum:  ָ�������ַ����ĳ���
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void UsartPutN(unsigned long ulBase, const  char  *pStr , unsigned short  usNum)
{
    while(usNum) 
    {
        if(UsartSpaceAvial(ulBase))                 //  ������ͻ������пռ䣬����䷢�ͼĴ���
        {  
            UsartCharPut(ulBase,*pStr++);
            usNum--;
        }
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
