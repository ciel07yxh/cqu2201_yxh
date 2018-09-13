/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_spi.c
** Last modified Date:  2013-04-20
** Last Version:        v1.0
** Description:         spi��i2sģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-20
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
#include "hal/arch/inc/arch_io_spi.h"


/*********************************************************************************************************
** Function name:       SPIInit
** Descriptions:        SPIģ�鹤��ģʽ����
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      ulConfig    SPIģ�鹤��ģ���ʼ�����ã�����ȥ���м������ֵĻ�
**                      // ����ģʽ����ѡ��
**                      SPI_DIR_2Lines_FullDuplex       //  ����ȫ˫��ģʽ
**                      SPI_DIR_2Lines_RxOnly           //  ����ֻ����ģʽ
**                      SPI_DIR_1Lines_Rx               //  ����ֻ����
**                      SPI_DIR_1Lines_Tx               //  ����ֻ����
**
**                      //  ��������ѡ��
**                      SPI_MODE_Master                 //  SPI����ģʽ
**                      SPI_MODE_Slave                  //  SPI�ӻ�ģʽ
**
**                      //  ���ݳ���ѡ��
**                      SPI_DATA_Len8                   //  ���ݳ��ȳ���Ϊ8
**                      SPI_DATA_Len16                  //  ���ݳ���Ϊ16
**
**                      // �������շ�ʱ��SPI_CLK����ѡ��
**                      SPI_CPOL_Low                    //  SPI_CLK����Ϊ�͵�ƽ
**                      SPI_CPOL_High                   //  SPI_CLK����Ϊ�ߵ�ƽ
**
**                      // ʱ�Ӳ�������λѡ��
**                      SPI_CPHA_1Edge                  //  �ڵ�һ��ʱ�ӱ��ز���
**                      SPI_CPHA_2Edge                  //  �ڵڶ���ʱ�ӱ��ز���
**
**                      // �ӻ�Ƭѡ����
**                      SPI_NSS_Soft                    //  Ƭѡ�ź����������
**                      SPI_NSS_Hard                    //  Ƭѡ�ź���Ӳ������
**
**                      // SPI�����ʷ�Ƶ��ѡ��
**                      SPI_Baud_Prescaler_2            //  �����ʷ���ϵ��Ϊ2
**                      SPI_Baud_Prescaler_4            //  �����ʷ���ϵ��Ϊ4
**                      SPI_Baud_Prescaler_8            //  �����ʷ���ϵ��Ϊ8
**                      SPI_Baud_Prescaler_16           //  �����ʷ���ϵ��Ϊ16
**                      SPI_Baud_Prescaler_32           //  �����ʷ���ϵ��Ϊ32
**                      SPI_Baud_Prescaler_64           //  �����ʷ���ϵ��Ϊ64
**                      SPI_Baud_Prescaler_128          //  �����ʷ���ϵ��Ϊ128
**                      SPI_Baud_Prescaler_256          //  �����ʷ���ϵ��Ϊ256
**
**                      // ��������λ��MSB��ʼ�����Ǵ�LSB��ʼѡ��
**                      SPI_First_MSB                   //  MSB�ȷ���
**                      SPI_First_LSB                   //  LSB�ȷ���
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPIInit(unsigned long ulBase,unsigned long ulConfig)
{
    unsigned long ulTemp;
    
    ulTemp = HWREG32(ulBase + SPI_O_CR1);
    
    ulTemp &= 0x3040; //�������������
    ulTemp |= ulConfig;
    
    /* Write to SPIx CR1 */
    HWREG32(ulBase + SPI_O_CR1) = ulTemp;
  
    /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
    HWREG32(ulBase + SPI_O_I2SCFGR) &= ~(0x0800);
    
   /* CRCУ��Ķ���ʽ���� ,��ʱ���ø�λ������ */
    HWREG32(ulBase + SPI_O_CRCPR) = 0x0007;
}

/*********************************************************************************************************
** Function name:       SPI_SSOutEnable
** Descriptions:        SPI��Ƭѡ�ź����ʹ��
** input parameters:    ulBase      SPIģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_SSOutEnable(unsigned long ulBase)
{
    HWREG32(ulBase + SPI_O_CR2) |= (1<<2);
}

/*********************************************************************************************************
** Function name:       SPI_SSOutDisable
** Descriptions:        SPI��Ƭѡ�ź��������
** input parameters:    ulBase      SPIģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_SSOutDisable(unsigned long ulBase)
{
    HWREG32(ulBase + SPI_O_CR2) &= ~(1<<2);
}

/*********************************************************************************************************
** Function name:       SPIEnable
** Descriptions:        SPI����ʹ��
** input parameters:    ulBase      SPIģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPIEnable(unsigned long ulBase)
{
    HWREG32(ulBase + SPI_O_CR1) |= (1<<6);
}

/*********************************************************************************************************
** Function name:       SPIDisable
** Descriptions:        SPI��������
** input parameters:    ulBase      SPIģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPIDisable(unsigned long ulBase)
{
    HWREG32(ulBase + SPI_O_CR1) &= ~(1<<6);
}

/*********************************************************************************************************
** Function name:       SPI_I2S_IntEnable
** Descriptions:        SPI��I2S�ж�ʹ��
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      ulIntFlag   ʹ�ܵ��ж�Դ������ȡ����������ֵ�ĵĻ�
**                      SPI_I2S_INT_TXE             //  ���ͻ��������ж�
**                      SPI_I2S_INT_RXNE            //  ���ջ������������ж�
**                      SPI_I2S_INT_ERR             //  �����ж�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_I2S_IntEnable(unsigned long ulBase,unsigned long ulIntFlag)
{
    HWREG32(ulBase + SPI_O_CR2) |= ulIntFlag;
}

/*********************************************************************************************************
** Function name:       SPI_I2S_IntEDisable
** Descriptions:        SPI��I2S�жϽ���
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      ulIntFlag   ���ܵ��ж�Դ������ȡ����������ֵ�ĵĻ�
**                      SPI_I2S_INT_TXE             //  ���ͻ��������ж�
**                      SPI_I2S_INT_RXNE            //  ���ջ������������ж�
**                      SPI_I2S_INT_ERR             //  �����ж�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_I2S_IntEDisable(unsigned long ulBase,unsigned long ulIntFlag)
{
    HWREG32(ulBase + SPI_O_CR2) &= ~ulIntFlag;
}

/*********************************************************************************************************
** Function name:       SPI_I2S_DMAEnable
** Descriptions:        SPI��I2SDMAģʽʹ��
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      ulDMAFlag   ָ��ʹ�ܵ�DMA�����Ƿ��ͻ��ǽ��գ�����ȥ��������ֵ�Ļ�
**                      SPI_I2S_DMA_TX               //  ����DMA
**                      SPI_I2S_DMA_RX               //  ����DMA
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_I2S_DMAEnable(unsigned long ulBase,unsigned long ulDMAFlag)
{
    HWREG32(ulBase + SPI_O_CR2) |= ulDMAFlag;
}

/*********************************************************************************************************
** Function name:       SPI_I2S_DMADisable
** Descriptions:        SPI��I2SDMAģʽ����
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      ulDMAFlag   ָ�����ܵ�DMA�����Ƿ��ͻ��ǽ��գ�����ȥ��������ֵ�Ļ�
**                      SPI_I2S_DMA_TX               //  ����DMA
**                      SPI_I2S_DMA_RX               //  ����DMA
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_I2S_DMADisable(unsigned long ulBase,unsigned long ulDMAFlag)
{
    HWREG32(ulBase + SPI_O_CR2) &= ~ulDMAFlag;
}

/*********************************************************************************************************
** Function name:       SPI_I2S_DataPut
** Descriptions:        SPI��I2S��������
** input parameters:    ulBase      SPIģ��Ļ���ַ
**                      usData      ���͵����ݣ���������8λģʽʱ��ֻ�е�8λ��Ч
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SPI_I2S_DataPut(unsigned long ulBase,unsigned short usData)
{
    HWREG32(ulBase + SPI_O_DR) = usData;
}

/*********************************************************************************************************
** Function name:       SPI_I2S_DataPut
** Descriptions:        SPI��I2S��������
** input parameters:    ulBase      SPIģ��Ļ���ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
unsigned short SPI_I2S_DataGet(unsigned long ulBase)
{
    return (HWREG32(ulBase + SPI_O_DR));
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
