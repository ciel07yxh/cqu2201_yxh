/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               clock.c
** Last modified Date:      2012-06-21
** Last Version:            v1.0
** Description:             ����ϵͳʱ��tick��ʼ�����Լ�tick������ʵ��
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-06-21
** Version:                 v1.0
** Descriptions:            The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/

/*********************************************************************************************************
** ͷ�ļ�����
*********************************************************************************************************/
#include <stdio.h>
#include "sys/clock.h"
#include "sys/cc.h"
#include "sys/etimer.h"
#include "sys/energest.h"

#include "hal/arch/inc/arch_io_rcc.h"

/*********************************************************************************************************
** ��Cortex-M3�ں���صĺ궨��
*********************************************************************************************************/
#define  OS_CPU_CM3_NVIC_ST_CTRL    (*((volatile uint32_t *)0xE000E010))   /* SysTick Ctrl & Status Reg. */
#define  OS_CPU_CM3_NVIC_ST_RELOAD  (*((volatile uint32_t *)0xE000E014))   /* SysTick Reload  Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CURRENT (*((volatile uint32_t *)0xE000E018))   /* SysTick Current Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CAL     (*((volatile uint32_t *)0xE000E01C))   /* SysTick Cal     Value Reg. */
#define  OS_CPU_CM3_NVIC_PRIO_ST    (*((volatile uint8_t  *)0xE000ED23))   /* SysTick Handler Prio  Reg. */

#define  OS_CPU_CM3_NVIC_ST_CTRL_COUNT                    0x00010000     /* Count flag.                */
#define  OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC                  0x00000000     /* Clock Source, ʹ���ⲿ��   */
#define  OS_CPU_CM3_NVIC_ST_CTRL_INTEN                    0x00000002     /* Interrupt enable.          */
#define  OS_CPU_CM3_NVIC_ST_CTRL_ENABLE                   0x00000001     /* Counter mode.              */
#define  OS_CPU_CM3_NVIC_PRIO_MIN                               0xFF     /* Min handler prio.          */

/*********************************************************************************************************
** ȫ�ֱ�������
*********************************************************************************************************/
static volatile clock_time_t current_clock = 0;
static volatile clock_time_t current_seconds = 0;
static clock_time_t second_countdown = CLOCK_SECOND;

/*********************************************************************************************************
** Function name:       clock_delay
** Descriptions:        ʱ����ʱ����,һ����ʱlen*2 + 1��ʱ��
** Input parameters:    len�� ��ʱ����
** Output parameters:   ��
** Returned value:      ��
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
void clock_delay(unsigned int len)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   clock_delay\n"
          "    bx      lr");
}

/*********************************************************************************************************
** Function name:       clock_wait
** Descriptions:        Wait for a multiple of ~8 ms (a tick)
** Input parameters:    t: �ȴ�����
** Output parameters:   ��
** Returned value:      ��
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
void clock_wait(clock_time_t t)
{
  clock_time_t start;

  start = clock_time();
  while(clock_time() - start < (clock_time_t)t);
}

/*********************************************************************************************************
** Function name:       clock_time
** Descriptions:        ��ȡʱ�Ӽ���
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��ǰʱ�Ӽ���ֵ
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
CCIF clock_time_t clock_time(void)
{
  return current_clock;
}

/*********************************************************************************************************
** Function name:       clock_seconds
** Descriptions:        ��ȡ��ǰʱ������
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��ǰʱ�Ӽ���ֵ������Ϊ��λ
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
CCIF unsigned long clock_seconds(void)
{
  return current_seconds;
}

/*********************************************************************************************************
** Function name:       clock_init
** Descriptions:        ʱ�ӳ�ʼ��
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
void clock_init(void)
{
    uint32_t  cnts;

    cnts = SystemSysTickClockGet() / CLOCK_SECOND;

    OS_CPU_CM3_NVIC_ST_RELOAD = (cnts - 1);
                                                 /* Set prio of SysTick handler to min prio.           */
    OS_CPU_CM3_NVIC_PRIO_ST   = OS_CPU_CM3_NVIC_PRIO_MIN;
                                                 /* Enable timer.                                      */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC | OS_CPU_CM3_NVIC_ST_CTRL_ENABLE;
                                                 /* Enable timer interrupt.                            */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_INTEN;
}

/*********************************************************************************************************
** Function name:       OS_CPU_SysTickHandler
** Descriptions:        ʱ��tick�жϷ�����
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
void  OS_CPU_SysTickHandler (void)
{
  current_clock++;
  
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();
    /* printf("%d,%d\n", clock_time(),etimer_next_expiration_time  	()); */

  }
  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

