/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_rcc.c
** Last modified Date:  2013-04-01
** Last Version:        v1.0
** Description:         rccģ��Ĵ�����װ����ʵ��
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_rcc.h"

/*********************************************************************************************************
  ʱ�����ú�ת��
*********************************************************************************************************/
#if (RCC_CLOCK_HCLK_DIV == 1)
#define RCC_CFGR_HPRE   (0<<4)
#elif (RCC_CLOCK_HCLK_DIV == 2)
#define RCC_CFGR_HPRE   (8<<4)
#elif (RCC_CLOCK_HCLK_DIV == 4)
#define RCC_CFGR_HPRE   (9<<4)
#elif (RCC_CLOCK_HCLK_DIV == 8)
#define RCC_CFGR_HPRE   (10<<4)
#elif (RCC_CLOCK_HCLK_DIV == 16)
#define RCC_CFGR_HPRE   (11<<4)
#elif (RCC_CLOCK_HCLK_DIV == 64)
#define RCC_CFGR_HPRE   (12<<4)
#elif (RCC_CLOCK_HCLK_DIV == 128)
#define RCC_CFGR_HPRE   (13<<4)
#elif (RCC_CLOCK_HCLK_DIV == 256)
#define RCC_CFGR_HPRE   (14<<4)
#elif (RCC_CLOCK_HCLK_DIV == 512)
#define RCC_CFGR_HPRE   (15<<4)
#endif

#if (RCC_CLOCK_PCLK1_DIV == 1)
#define RCC_CFGR_PPRE1  (0<<8)
#elif (RCC_CLOCK_PCLK1_DIV == 2)
#define RCC_CFGR_PPRE1  (4<<8)
#elif (RCC_CLOCK_PCLK1_DIV == 4)
#define RCC_CFGR_PPRE1  (5<<8)
#elif (RCC_CLOCK_PCLK1_DIV == 8)
#define RCC_CFGR_PPRE1  (6<<8)
#elif (RCC_CLOCK_PCLK1_DIV == 16)
#define RCC_CFGR_PPRE1  (7<<8)
#endif

#if (RCC_CLOCK_PCLK2_DIV == 1)
#define RCC_CFGR_PPRE2  (0<<11)
#elif (RCC_CLOCK_PCLK2_DIV == 2)
#define RCC_CFGR_PPRE2  (4<<11)
#elif (RCC_CLOCK_PCLK2_DIV == 4)
#define RCC_CFGR_PPRE2  (5<<11)
#elif (RCC_CLOCK_PCLK2_DIV == 8)
#define RCC_CFGR_PPRE2  (6<<11)
#elif (RCC_CLOCK_PCLK2_DIV == 16)
#define RCC_CFGR_PPRE2  (7<<11)
#endif

/*********************************************************************************************************
  �ֲ���������
*********************************************************************************************************/
// ʱ����ض���
static __no_init uint32 __G_stm32_sysclk;
static __no_init uint32 __G_stm32_hclk;
static __no_init uint32 __G_stm32_pclk1;
static __no_init uint32 __G_stm32_pclk2;
static __no_init uint32 __G_cortexm_systick_clock;

// ���踴λ�Ĵ�������
static const uint32 __GSysPeripheralResetReg[] = {
    0, // ��������֧��AHB����ĸ�λ
    RCC_O_APB1RSTR,
    RCC_O_APB2RSTR,
};

// ����ʱ��ʱ�ܼĴ�������
static const uint32 __GSysPeripheralEnableReg[] = {
    RCC_O_AHBENR,
    RCC_O_APB1ENR,
    RCC_O_APB2ENR,
};

/*********************************************************************************************************
** Function name:       rccClockSet
** Descriptions:        ʱ�����ã���Ҫ��ͷ�ļ���������Ӧ��ϵ��
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SystemClockInit(void)
{
    unsigned long ulTemp;
    HWREG32(RCC_BASE + RCC_O_CR) = 0x0083;
    HWREG32(RCC_BASE + RCC_O_CFGR) = 0x0000;
    HWREG32(RCC_BASE + RCC_O_CIR) = 0x0000;
    
    HWREG32(RCC_BASE + RCC_O_CR) = 0x00000001;     // reset RCC
    
    // Start up HSE clock
    HWREG32(RCC_BASE + RCC_O_CR) &= ((1<<16) | (1<<18));
    HWREG32(RCC_BASE + RCC_O_CR) |= (1<<16);
    
    // Wait for HSE clock to startup
    while(!(HWREG32(RCC_BASE + RCC_O_CR) & (1<<17))) ; 
    
    // ʹ��flashԤȡָ���ȴ�����2��wait
    HWREG32(FLASH_BASE + FLASH_O_ACR) |= ((1<<4) | 0x02);
    
    __G_stm32_sysclk = RCC_HSE_INPUT_CLOCK;
    ulTemp = 0;
#if defined (RCC_CLOCK_PLL_SOURCE_HSE)
    ulTemp |= (1<<16);
#elif defined (RCC_CLOCK_PLL_SOURCE_HSE_HALF)
    ulTemp |= ((1<<16) | (1<<17));
    __G_stm32_sysclk /= 2;
#elif defined (RCC_CLOCK_PLL_SOURCE_HSI_HALF)
    __G_stm32_sysclk /= 2;
#endif
    
    ulTemp |= ((RCC_CLOCK_PLL_MUL - 2) << 18);
    ulTemp |= RCC_CFGR_HPRE;
    ulTemp |= RCC_CFGR_PPRE1;
    ulTemp |= RCC_CFGR_PPRE2;

    HWREG32(RCC_BASE + RCC_O_CFGR) = ulTemp;

    // Enable the PLL and wait for it to lock
    HWREG32(RCC_BASE + RCC_O_CR) |= (1<<24);
    while(!(HWREG32(RCC_BASE + RCC_O_CR) & (1<<25))) ;

    // Now switch to use PLL as SYSCLK and wait it finish
    HWREG32(RCC_BASE + RCC_O_CFGR) |= 0x02;
    while(((HWREG32(RCC_BASE + RCC_O_CFGR) >> 2) & 0x03) != 0x02) ;

    //  ������Ҫ����MCO�����USBģ���ʱ�ӣ�ע�⵱ʹ��USBʱ��ʱ�ӱ�������Ϊ48M��72M
    
    // Calculate clocks from configuration
    __G_stm32_sysclk *= RCC_CLOCK_PLL_MUL;
    __G_stm32_hclk = __G_stm32_sysclk / RCC_CLOCK_HCLK_DIV;
    __G_stm32_pclk1 = __G_stm32_sysclk / RCC_CLOCK_PCLK1_DIV;
    __G_stm32_pclk2 = __G_stm32_sysclk / RCC_CLOCK_PCLK2_DIV;
    __G_cortexm_systick_clock = __G_stm32_sysclk / 8;
}
/*********************************************************************************************************
** Function name:       SystemSysClockGet
** Descriptions:        ��ȡϵͳ��Ƶ
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      ϵͳ��Ƶ
*********************************************************************************************************/
uint32 SystemSysClockGet(void)
{
    return __G_stm32_sysclk;
}

/*********************************************************************************************************
** Function name:       SystemAHBClockGet
** Descriptions:        ��ȡAHB����ʱ��Ƶ��
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      AHBʱ��Ƶ��
*********************************************************************************************************/
uint32 SystemAHBClockGet(void)
{
    return __G_stm32_hclk;
}

/*********************************************************************************************************
** Function name:       SystemAPB1ClockGet
** Descriptions:        ��ȡAPB1����ʱ��Ƶ��
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      APB1ʱ��Ƶ��
*********************************************************************************************************/
uint32 SystemAPB1ClockGet(void)
{
    return __G_stm32_pclk1;
}

/*********************************************************************************************************
** Function name:       SystemAPB2ClockGet
** Descriptions:        ��ȡAPB2����ʱ��Ƶ��
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      APB2ʱ��Ƶ��
*********************************************************************************************************/
uint32 SystemAPB2ClockGet(void)
{
    return __G_stm32_pclk2;
}

/*********************************************************************************************************
** Function name:       SystemSysTickClockGet
** Descriptions:        ��ȡSystem tick����ʱ��Ƶ��
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      APB2ʱ��Ƶ��
*********************************************************************************************************/
uint32 SystemSysTickClockGet(void)
{
  return __G_cortexm_systick_clock;
}

/*********************************************************************************************************
** Function name:       SystemPeripheralReset
** Descriptions:        ��λ����
** input parameters:    u8WhichBus:  ����λ����������
**                      u32Ctrl���������λ
** output parameters:   NONE
** Returned value:      NONE
ע�⣺����������һ��ͳһ�ĺ궨�壬����ȡֵ���Բο�arch_io_rcc.h�еĶ���
*********************************************************************************************************/
void SystemPeripheralReset(uint8 u8WhichBus, uint32 u32Ctrl)
{
    // AHB���費֧�ָ�λ
    if(u8WhichBus == 0) {
        return;
    }
    HWREG32(RCC_BASE + __GSysPeripheralResetReg[u8WhichBus]) |= u32Ctrl;
    HWREG32(RCC_BASE + __GSysPeripheralResetReg[u8WhichBus]) &= ~u32Ctrl;
}

/*********************************************************************************************************
** Function name:       SystemPeripheralEnable
** Descriptions:        ʹ������ʱ��
** input parameters:    u8WhichBus:  ����λ����������
**                      u32Ctrl���������λ
** output parameters:   NONE
** Returned value:      NONE
ע�⣺����������һ��ͳһ�ĺ궨�壬����ȡֵ���Բο�arch_io_rcc.h�еĶ���
*********************************************************************************************************/
void SystemPeripheralEnable(uint8 u8WhichBus, uint32 u32Ctrl)
{
    HWREG32(RCC_BASE + __GSysPeripheralEnableReg[u8WhichBus]) |= u32Ctrl;
}

/*********************************************************************************************************
** Function name:       SystemPeripheralDisable
** Descriptions:        ��������ʱ��
** input parameters:    u8WhichBus:  ����λ����������
**                      u32Ctrl���������λ
** output parameters:   NONE
** Returned value:      NONE
ע�⣺����������һ��ͳһ�ĺ궨�壬����ȡֵ���Բο�arch_io_rcc.h�еĶ���
*********************************************************************************************************/
void SystemPeripheralDisable(uint8 u8WhichBus, uint32 u32Ctrl)
{
    HWREG32(RCC_BASE + __GSysPeripheralEnableReg[u8WhichBus]) &= ~u32Ctrl;
}

/*********************************************************************************************************
** Function name:       SystemPeripheralClockGet
** Descriptions:        ��ȡָ��������ʱ��
** input parameters:    u8WhichBus:  ����λ����������
**                      u32Ctrl���������λ
** output parameters:   NONE
** Returned value:      NONE
ע�⣺����������һ��ͳһ�ĺ궨�壬����ȡֵ���Բο�arch_io_rcc.h�еĶ���
*********************************************************************************************************/
uint32 SystemPeripheralClockGet(uint8 u8WhichBus, uint32 u32Ctrl)
{
    uint32 u32Clock;
    switch(u8WhichBus) {
        case 0:
            u32Clock = SystemAHBClockGet();
            break;
        case 1:
            u32Clock = SystemAPB1ClockGet();
            break;
        case 2:
            u32Clock = SystemAPB2ClockGet();
            break;
        default:
            u32Clock = 0;
            break;
    }
    return u32Clock;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
