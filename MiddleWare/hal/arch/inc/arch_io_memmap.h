/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_memmap.h
** Last modified Date:  2013-04-01
** Last Version:        v1.0
** Description:         IOģ���ڴ�ӳ�䶨��
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

#ifndef __ARCH_IO_MEMMAP_H__
#define __ARCH_IO_MEMMAP_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
** ����ӳ�����ַ����
*********************************************************************************************************/
#define RCC_BASE         0x40021000              //  ��mޓ�C���S��ҫݔ(RCC)�r�A�u
#define IWDG_BASE        0x40003000              //  �S����˟�gҫݔ�r�u
#define AFIO_BASE        0x40010000              //  AFIOҫݔ�r�A�u
#define EXTI_BASE        0x40010400              //  EXTIҫݔ�r�A�u
#define GPIOA_BASE       0x40010800              //  BS_GPIOAҫݔ�r�A�u
#define GPIOB_BASE       0x40010C00              //  BS_GPIOBҫݔ�r�A�u
#define GPIOC_BASE       0x40011000              //  BS_GPIOCҫݔ�r�A�u
#define GPIOD_BASE       0x40011400              //  BS_GPIODҫݔ�r�A�u
#define GPIOE_BASE       0x40011800              //  BS_GPIOEҫݔ�r�A�u
#define GPIOF_BASE       0x40011C00              //  BS_GPIOFҫݔ�r�A�u
#define GPIOG_BASE       0x40012000              //  BS_GPIOGҫݔ�r�A�u
#define ETH0_BASE        0x40028000              //  �p�Q��MACҫݔǻ�r�A�u
#define USART1_BASE      0x40013800              //  Usart1ҫݔ�r�A�u
#define USART2_BASE      0x40004400              //  Usart2ҫݔ�r�A�u
#define USART3_BASE      0x40004800              //  Usart3ҫݔ�r�A�u
#define USART4_BASE      0x40004C00              //  Usart4ҫݔ�r�A�u
#define USART5_BASE      0x40005000              //  Usart5ҫݔ�r�A�u
#define FLASH_BASE       0x40022000              //  Flash�S��ҫݔ�r�A�u
#define DMA1_BASE        0x40020000              //  DMA1ҫݔ�r�A�u
#define DMA2_BASE        0x40020400              //  DMA2ҫݔ�r�A�u
#define SPI1_BASE        0x40013000              //  SPI1ҫݔ�r�A�u
#define SPI2_BASE        0x40003800              //  SPI2ҫݔ�r�A�u
#define SPI3_BASE        0x40003C00             //  SPI3ҫݔ�r�A�u

#define TIM2_BASE        0x40000000             // TIM2ҫݔ�r�A�u
#define TIM3_BASE        0x40000400             // TIM3ҫݔ�r�A�u
#define TIM4_BASE        0x40000800             // TIM4ҫݔ�r�A�u
#define TIM5_BASE        0x40000C00             // TIM5ҫݔ�r�A�u
#define TIM6_BASE        0x40001000             // TIM6ҫݔ�r�A�u
#define TIM7_BASE        0x40001400             // TIM7ҫݔ�r�A�u
#define TIM12_BASE       0x40001800             // TIM12ҫݔ�r�A�u
#define TIM13_BASE       0x40001C00             // TIM13ҫݔ�r�A�u
#define TIM14_BASE       0x40002000             // TIM14ҫݔ�r�A�u
#define TIM1_BASE        0x40012C00             // TIM1ҫݔ�r�A�u
#define TIM8_BASE        0x40013400             // TIM8ҫݔ�r�A�u
#define TIM15_BASE       0x40014000             // TIM12ҫݔ�r�A�u
#define TIM16_BASE       0x40014400             // TIM13ҫݔ�r�A�u
#define TIM17_BASE       0x40014800             // TIM14ҫݔ�r�A�u
#define TIM9_BASE        0x40014C00             // TIM12ҫݔ�r�A�u
#define TIM10_BASE       0x40015000             // TIM13ҫݔ�r�A�u
#define TIM11_BASE       0x40015400             // TIM14ҫݔ�r�A�u


#ifdef __cplusplus
    }
#endif      // __cplusplus

#endif // endif of __ARCH_IO_MEMMAP_H__
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
