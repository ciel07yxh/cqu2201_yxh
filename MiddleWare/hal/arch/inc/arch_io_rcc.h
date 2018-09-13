/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_rcc.h
** Last modified Date:  2013-04-01
** Last Version:        v1.0
** Description:         rccģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-01
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
#ifndef __ARCH_IO_RCC_H__
#define __ARCH_IO_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "infra/rhb_type.h"

/*********************************************************************************************************
  ʱ��ģ�����ö���
*********************************************************************************************************/
#define RCC_HSE_INPUT_CLOCK            12000000// 8000000    //  �ⲿ����������Ƶ��
//  ���������궨������PLLʱ��Դ��ѡ�񣬸����Ƿ�����ѡ��3��ֻ��Ҫ�������е�һ��
#define RCC_CLOCK_PLL_SOURCE_HSE        1
//#define RCC_CLOCK_PLL_SOURCE_HSE_HALF   1
//#define RCC_CLOCK_PLL_SOURCE_HSI_HALF   1

#define RCC_CLOCK_PLL_MUL               6   //  PLL������ȡ2-16����
#define RCC_CLOCK_HCLK_DIV              1   //  HCLK��Ƶϵ��,����ȡ{ 1 2 4 8 16 64 128 256 512 }
#define RCC_CLOCK_PCLK1_DIV             2   //  PCLK1��Ƶϵ��������ȡ{ 1 2 4 8 16 }
#define RCC_CLOCK_PCLK2_DIV             1   //  PCLK2��Ƶϵ��������ȡ{ 1 2 4 8 16 }

/*********************************************************************************************************
** ��������Ĵ������ƣ����ڿ�������ʱ�ӡ��궨��Ϊ˫��������һ��Ϊ�Ǹ����ߣ�����ȡ����ֵ��
** 0x00: AHB
** 0x01: APB1
** 0x02: APB2
** �ڶ�������Ϊ�ڿ��ƼĴ�����λ��
*********************************************************************************************************/
// AHB����
#define RCC_PERIPHERAL_SDIO         0, (((uint32)1) << 10)
#define RCC_PERIPHERAL_FSMC         0, (((uint32)1) << 8)
#define RCC_PERIPHERAL_CRC          0, (((uint32)1) << 6)
#define RCC_PERIPHERAL_FLITF        0, (((uint32)1) << 4)
#define RCC_PERIPHERAL_SRAM         0, (((uint32)1) << 2)
#define RCC_PERIPHERAL_DMA2         0, (((uint32)1) << 1)
#define RCC_PERIPHERAL_DMA1         0, (((uint32)1) << 0)

// APB1����
#define RCC_PERIPHERAL_DAC          1, (((uint32)1) << 29)
#define RCC_PERIPHERAL_PWR          1, (((uint32)1) << 28)
#define RCC_PERIPHERAL_BKP          1, (((uint32)1) << 27)
#define RCC_PERIPHERAL_CAN          1, (((uint32)1) << 25)
#define RCC_PERIPHERAL_USB          1, (((uint32)1) << 23
#define RCC_PERIPHERAL_I2C2         1, (((uint32)1) << 22)
#define RCC_PERIPHERAL_I2C1         1, (((uint32)1) << 21)
#define RCC_PERIPHERAL_UART5        1, (((uint32)1) << 20)
#define RCC_PERIPHERAL_UART4        1, (((uint32)1) << 19)
#define RCC_PERIPHERAL_USART3       1, (((uint32)1) << 18)
#define RCC_PERIPHERAL_USART2       1, (((uint32)1) << 17)
#define RCC_PERIPHERAL_SPI3         1, (((uint32)1) << 15)
#define RCC_PERIPHERAL_SPI2         1, (((uint32)1) << 14)
#define RCC_PERIPHERAL_WWD          1, (((uint32)1) << 11)
#define RCC_PERIPHERAL_TIM14        1, (((uint32)1) << 8)
#define RCC_PERIPHERAL_TIM13        1, (((uint32)1) << 7)
#define RCC_PERIPHERAL_TIM12        1, (((uint32)1) << 6)
#define RCC_PERIPHERAL_TIM7         1, (((uint32)1) << 5)
#define RCC_PERIPHERAL_TIM6         1, (((uint32)1) << 4)
#define RCC_PERIPHERAL_TIM5         1, (((uint32)1) << 3)
#define RCC_PERIPHERAL_TIM4         1, (((uint32)1) << 2)
#define RCC_PERIPHERAL_TIM3         1, (((uint32)1) << 1)
#define RCC_PERIPHERAL_TIM2         1, (((uint32)1) << 0)

// APB2����
#define RCC_PERIPHERAL_TIM11        2, (((uint32)1) << 21)
#define RCC_PERIPHERAL_TIM10        2, (((uint32)1) << 20)
#define RCC_PERIPHERAL_TIM9         2, (((uint32)1) << 19)
#define RCC_PERIPHERAL_ADC3         2, (((uint32)1) << 15)
#define RCC_PERIPHERAL_USART1       2, (((uint32)1) << 14)
#define RCC_PERIPHERAL_TIM8         2, (((uint32)1) << 13)
#define RCC_PERIPHERAL_SPI1         2, (((uint32)1) << 12)
#define RCC_PERIPHERAL_TIM1         2, (((uint32)1) << 11)
#define RCC_PERIPHERAL_ADC2         2, (((uint32)1) << 10)
#define RCC_PERIPHERAL_ADC1         2, (((uint32)1) << 9)
#define RCC_PERIPHERAL_IOPG         2, (((uint32)1) << 8)
#define RCC_PERIPHERAL_IOPF         2, (((uint32)1) << 7)
#define RCC_PERIPHERAL_IOPE         2, (((uint32)1) << 6)
#define RCC_PERIPHERAL_IOPD         2, (((uint32)1) << 5)
#define RCC_PERIPHERAL_IOPC         2, (((uint32)1) << 4)
#define RCC_PERIPHERAL_IOPB         2, (((uint32)1) << 3)
#define RCC_PERIPHERAL_IOPA         2, (((uint32)1) << 2)
#define RCC_PERIPHERAL_AFIO         2, (((uint32)1) << 0)

/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern void SystemClockInit(void);
extern uint32 SystemSysClockGet(void);
extern uint32 SystemAHBClockGet(void);
extern uint32 SystemAPB1ClockGet(void);
extern uint32 SystemAPB2ClockGet(void);
extern uint32 SystemSysTickClockGet(void);
extern void SystemPeripheralReset(uint8 u8WhichBus, uint32 u32Ctrl);
extern void SystemPeripheralEnable(uint8 u8WhichBus, uint32 u32Ctrl);
extern void SystemPeripheralDisable(uint8 u8WhichBus, uint32 u32Ctrl);
extern uint32 SystemPeripheralClockGet(uint8 u8WhichBus, uint32 u32Ctrl);

#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_RCC_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
