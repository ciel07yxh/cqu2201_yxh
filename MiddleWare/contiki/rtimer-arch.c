/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               rtime-arch.c
** Last modified Date:      2012-07-03
** Last Version:            v1.0
** Description:             Hardware-dependent functions used to support the contiki rtimer module.
**                          clock_init() has set our tick speed prescaler already, so we
**                          are ticking with 500 kHz freq.
**
**                          Contiki typedefs rtimer_clock_t as unsigned short (16bit)
**                          It thus makes sense to use the 16bit timer (Timer 1)
**
**                          This file contains an ISR and must reside in the HOME bank
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-07-03
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
#include "rtimer-arch.h"
#include "sys/energest.h"


#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

void hal_rtimer_isr(void);
/*********************************************************************************************************
** ȫ�ֱ�������
*********************************************************************************************************/
static uint32_t time_msb = 0;  // Most significant bits of the current time.
// time of the next rtimer event. Initially is set to the max value.
static rtimer_clock_t  next_rtimer_time = 0;
static uint32_t  __GTimerIntState = 0;

/*---------------------------------------------------------------------------*/
void rtimer_arch_init(void)
{
   uint32_t temp;
   // ʹ��ʱ��ģ��
   HAL_READ_UINT32(RCC_BASE + RCC_O_APB1ENR, temp);
   temp |= 1;
   HAL_WRITE_UINT32(RCC_BASE + RCC_O_APB1ENR, temp);
   
   // ��ʼ��ʼ��ʱ��ģ��
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_CR1, 0);
   // ����Ԥ��Ƶ
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_PSC, RT_PRESCALER);
   // �����Զ�װ��ֵ
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_ARR, 0xFFFF);
   // ���ò����Զ������¼�
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_EGR, 0x00000001);
   // ���ö�ʱ���ж����ѡ��
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, 0x00000000);    // �������ǰ���ж�״̬
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, 0x00000001);  // ʹ�ܸ����ж�
   hal_int_register(ARCH_INT_TIM2, hal_rtimer_isr);
   hal_int_priority_set(ARCH_INT_TIM2, 0x01);
   hal_int_enable(ARCH_INT_TIM2);
   
   // ��������
   HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_CR1, 0x00000001);
}

void rtimer_arch_disable_irq(void)
{
  HAL_READ_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, __GTimerIntState);
  HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, 0);
}

/*---------------------------------------------------------------------------*/
void rtimer_arch_enable_irq(void)
{
  HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, __GTimerIntState);
}

/*---------------------------------------------------------------------------*/
rtimer_clock_t rtimer_arch_now(void)
{
  uint16_t temp;
  rtimer_clock_t tRtnTime;
  
  HAL_READ_UINT16(RTIMER_ARCH_USE_BASE + TIMx_O_CNT, temp);
  tRtnTime = ((rtimer_clock_t)(time_msb << 16)) | temp;
  return tRtnTime;
}

/*---------------------------------------------------------------------------*/
void
rtimer_arch_schedule(rtimer_clock_t t)
{
  uint32_t temp;
  PRINTF("rtimer_arch_schedule time %4x\r\n", /*((uint32_t*)&t)+1,*/(uint32_t)t);
  
  next_rtimer_time = t;
  
  rtimer_clock_t now = rtimer_arch_now();
  
  rtimer_clock_t clock_to_wait = t - now;
  
  PRINTF("now %2x\r\n", TIM1_CNT);
  PRINTF("clock_to_wait %4x\r\n", clock_to_wait);
  
  if(clock_to_wait <= 0x10000){ // We must set now the Timer Compare Register.
    HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_CCR1, (uint16_t)now + (uint16_t)clock_to_wait);
   // HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, 0x00000002);    // �������ǰ�Ĳ����ж�״̬
    HAL_READ_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp); 
    temp |= 0x00000002;     // ʹ�ܲ����ж�
    HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp);    
    
    //PRINTF("2-INT_TIM1FLAG %2x\r\n", INT_TIM1FLAG);
    
  }
  // else compare register will be set at overflow interrupt closer to the rtimer event.
}

/*---------------------------------------------------------------------------*/
void hal_rtimer_isr(void)
{
  uint32_t temp;
  
  //  �ȶ�ȡ������ж�״̬
  HAL_READ_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, temp); 
  HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, ~temp); 
  
  //����ʼʵ�ʵ��жϴ���
  if(temp & 0x00000001){  // Overflow event. 
    
    //PRINTF("O %4x.\r\n", TIM1_CNT);
    //printf("OV ");
    
    time_msb++;
    HAL_READ_UINT16(RTIMER_ARCH_USE_BASE + TIMx_O_CNT, temp);
    rtimer_clock_t now= ((rtimer_clock_t)(time_msb << 16)) | temp;
    
    rtimer_clock_t clock_to_wait = next_rtimer_time - now;
    
    if(clock_to_wait <= 0x10000 && clock_to_wait > 0){ // We must set now the Timer Compare Register.
      HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_CCR1, (uint16_t)clock_to_wait);
     // HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, 0x00000002);    // �������ǰ�Ĳ����ж�״̬
      HAL_READ_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp); 
      temp |= 0x00000002;     // ʹ�ܲ����ж�
      HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp);  
      
    }   
    
   // HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, 0x00000001);
    
  }  else if(temp & 0x00000002){  // Compare event.  
    
     // Disable the next compare interrupt
    HAL_READ_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp); 
    temp &= ~0x00000002;
    HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_DIER, temp);
    
    PRINTF("\nCompare event %4x\r\n", TIM1_CNT);
    PRINTF("INT_TIM1FLAG %2x\r\n", INT_TIM1FLAG);
    ENERGEST_ON(ENERGEST_TYPE_IRQ);
    rtimer_run_next();
    ENERGEST_OFF(ENERGEST_TYPE_IRQ);
    
   // HAL_WRITE_UINT32(RTIMER_ARCH_USE_BASE + TIMx_O_SR, 0x00000002);
  }
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/