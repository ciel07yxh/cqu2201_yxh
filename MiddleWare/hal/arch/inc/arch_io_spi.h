/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_spi.h
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
#ifndef __ARCH_IO_SPI_H__
#define __ARCH_IO_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"

/*********************************************************************************************************
** ��Ҫ�ĺ궨��
*********************************************************************************************************/
// ����SPI_Init����ulConfig�궨��,����ȡ���м�������Ļ�
// ����ģʽ����ѡ��
#define SPI_DIR_2Lines_FullDuplex       0x0000
#define SPI_DIR_2Lines_RxOnly           0x0400
#define SPI_DIR_1Lines_Rx               0x8000
#define SPI_DIR_1Lines_Tx               0xC000

//  ��������ѡ��
#define SPI_MODE_Master                 0x0104
#define SPI_MODE_Slave                  0x0000

//  ���ݳ���ѡ��
#define SPI_DATA_Len8                   0x0000
#define SPI_DATA_Len16                  0x0800

// �������շ�ʱ��SPI_CLK����ѡ��
#define SPI_CPOL_Low                    0x0000
#define SPI_CPOL_High                   0x0002

// ʱ�Ӳ�������λѡ��
#define SPI_CPHA_1Edge                  0x0000
#define SPI_CPHA_2Edge                  0x0001

// �ӻ�Ƭѡ����
#define SPI_NSS_Soft                    0x0200
#define SPI_NSS_Hard                    0x0000

// SPI�����ʷ�Ƶ��ѡ��
#define SPI_Baud_Prescaler_2            0x0000
#define SPI_Baud_Prescaler_4            0x0008
#define SPI_Baud_Prescaler_8            0x0010
#define SPI_Baud_Prescaler_16           0x0018
#define SPI_Baud_Prescaler_32           0x0020
#define SPI_Baud_Prescaler_64           0x0028
#define SPI_Baud_Prescaler_128          0x0030
#define SPI_Baud_Prescaler_256          0x0038

// ��������λ��MSB��ʼ�����Ǵ�LSB��ʼѡ��
#define SPI_First_MSB                   0x0000
#define SPI_First_LSB                   0x0080

// ����SPI_I2S_IntEnable��SPI_I2S_IntDisable�Ĳ������壬ָ��ʹ�ܵ��ж�Դ
#define SPI_I2S_INT_TXE                 (1<<7)
#define SPI_I2S_INT_RXNE                (1<<6)
#define SPI_I2S_INT_ERR                 (1<<5)

// ����SPI_I2S_DMAEnable��SPI_I2S_DMADisable�Ĳ�������
#define SPI_I2S_DMA_TX                  (1<<1)
#define SPI_I2S_DMA_RX                  (1<<0)

/*********************************************************************************************************
** �꺯����һЩ����
*********************************************************************************************************/
#define SPI_Busy(ulBase)                (HWREG(ulBase+SPI_O_SR) & 0x80)  // Ϊ0����ʾSPI���߲�æ����0����ʾæ
#define SPISpaceAvial(ulBase)           (!(HWREG(ulBase+SPI_O_SR) & 0x02))// 0�����ͻ������գ���0�����ͻ���������
#define SPICharsAvial(ulBase)           (HWREG(ulBase+SPI_O_SR) & 0x01)  // 0,���ջ������գ���0�����ջ������ǿ�

// ����������ͨ���������Ƭѡ���������ֻ��Ƭѡ��������Ϊ�������ʱ����Ч
#define SPI_SSSet(ulBase)               (HWREG(ulBase+SPI_O_CR1) |= 0x0100)
#define SPI_SSReset(ulBase)             (HWREG(ulBase+SPI_O_CR1) &= 0xFEFF)
/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern void SPIInit(unsigned long ulBase,unsigned long ulConfig);
extern void SPI_SSOutEnable(unsigned long ulBase);
extern void SPI_SSOutDisable(unsigned long ulBase);
extern void SPIEnable(unsigned long ulBase);
extern void SPIDisable(unsigned long ulBase);
extern void SPI_I2S_IntEnable(unsigned long ulBase,unsigned long ulIntFlag);
extern void SPI_I2S_IntEDisable(unsigned long ulBase,unsigned long ulIntFlag);
extern void SPI_I2S_DMAEnable(unsigned long ulBase,unsigned long ulDMAFlag);
extern void SPI_I2S_DMADisable(unsigned long ulBase,unsigned long ulDMAFlag);
extern void SPI_I2S_DataPut(unsigned long ulBase,unsigned short usData);
extern unsigned short SPI_I2S_DataGet(unsigned long ulBase);



#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_SPI_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
