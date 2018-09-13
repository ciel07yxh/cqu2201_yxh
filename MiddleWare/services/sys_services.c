/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           sys_services.c
** Last modified Date:  2012-11-14
** Last Version:        v1.0
** Description:         ϵͳ������ʵ��ͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created By:          �κ���
** Created date:        2012-11-14
** Version:             v1.0
** Descriptions:        ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/

/*********************************************************************************************************
  ��Ҫ��ͷ�ļ�����
*********************************************************************************************************/
#include "infra/rhb_type.h"
#include "hal/CortexM3/hal_io_level.h"

#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_rcc.h"
#include "hal/arch/inc/arch_io_gpio.h"
/*********************************************************************************************************
** Function name:           sys_clock_get
** Descriptions:            ��ȡϵͳ��Ƶ
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint32 sys_clock_get(void)
{
   return SystemSysClockGet();
}

/*********************************************************************************************************
** Function name:       sys_beep_init
** Descriptions:        beep��������ʼ��
** Input parameters:    None ��
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
static void sys_beep_init(void)
{

}

/*********************************************************************************************************
** Function name:       sys_beep_up
** Descriptions:        beep��������ʼ��
** Input parameters:    u32time: ����ʱ�䣬��10msΪ��λ
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void sys_beep_up(uint32 u32time)
{
  
}

/*********************************************************************************************************
** Function name:       sys_led_init
** Descriptions:        led�ƿ��Ƴ�ʼ��
** Input parameters:    None ��
** Output parameters:   None ��
** Returned value:      None ��
** Ӳ�����ӣ� LED0 ---->PB10
**            LED1 ---->PB11
*********************************************************************************************************/
static void sys_led_init(void)
{
    SystemPeripheralEnable(RCC_PERIPHERAL_IOPB);
    SystemPeripheralEnable(RCC_PERIPHERAL_IOPD);
    GPIOConfigSet(GPIOB_BASE, GPIO_PIN_5, GPIO_OUT_PP | GPIO_SPEED_50MHZ);
    GPIOConfigSet(GPIOD_BASE, GPIO_PIN_2, GPIO_OUT_PP | GPIO_SPEED_50MHZ);
    GPIOBitSet(GPIOB_BASE,GPIO_PIN_5);
    GPIOBitSet(GPIOD_BASE,GPIO_PIN_2);
}

/*********************************************************************************************************
** Function name:       sys_led_on
** Descriptions:        ����ָ����LED
** Input parameters:    led: ָ����led��
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void sys_led_on(uint8 led)
{
    switch(led) {
        case 0:
            GPIOBitReset(GPIOB_BASE,GPIO_PIN_5);
            break;
        case 1:
            GPIOBitReset(GPIOD_BASE,GPIO_PIN_2);
            break;
        default:
            break;
    }
}

/*********************************************************************************************************
** Function name:       sys_led_off
** Descriptions:        Ϩ��ָ����LED
** Input parameters:    led: ָ����led��
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void sys_led_off(uint8 led)
{
    switch(led) {
        case 0:
            GPIOBitSet(GPIOB_BASE,GPIO_PIN_5);
            break;
        case 1:
            GPIOBitSet(GPIOD_BASE,GPIO_PIN_2);
            break;
        default:
            break;
    }
}

/*********************************************************************************************************
** Function name:       sys_led_toggle
** Descriptions:        ��תָ����LED
** Input parameters:    led: ָ����led��
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void sys_led_toggle(uint8 led)
{
    switch(led) {
        case 0:
            GPIOToggleBit(GPIOB_BASE, GPIO_PIN_5);
            break;
        case 1:
            GPIOToggleBit(GPIOD_BASE, GPIO_PIN_2);
            break;
        default:
            break;
    }
}

/*********************************************************************************************************
** Function name:       sys_services_init
** Descriptions:        ϵͳ�����ʼ������Ҫ���ϵͳ����ĳ�ʼ��
** Input parameters:    None ��
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void sys_services_init(void)
{
    // ��������ʼ��
    sys_beep_init();
    // LED�ƿ��Ƴ�ʼ��
    sys_led_init();
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
