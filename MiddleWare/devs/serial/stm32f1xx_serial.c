/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           stm32f1xx_serial.c
** Last modified Date:  2013-08-28
** Last Version:        v1.0
** Description:         ����contiki��stm32�Ĵ����������򡣷��ͺͽ��ܶ������жϷ�ʽ
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-08-28
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
/*********************************************************************************************************
  ͷ�ļ�����
*********************************************************************************************************/
#include "devs/serial/stm32f1xx_serial.h"


/*********************************************************************************************************
  �ֲ���̬����
*********************************************************************************************************/
// ����1
stm32_serial_info tUsart1Info  =  {
    USART1_BASE,            // ģ�����ַ
    RCC_PERIPHERAL_USART1,  //  �����������ԣ�����ȷ������ʱ��
    ARCH_INT_USART1,        // �ж����
    0,                      // �����Ƿ��ڷ���״̬��0��û�����ڷ��ͣ�1�����ڷ���
    {0},                    // ���ͻ�������������contiki�Ļ��λ�������
    19200,                  // Ĭ�ϲ�����
    {0},                    // ���ͻ��λ�����
    NULL                    // Ĭ���������뺯��
};

// ����2
stm32_serial_info tUsart2Info  =  {
    USART2_BASE,            // ģ�����ַ
    RCC_PERIPHERAL_USART2,  //  �����������ԣ�����ȷ������ʱ��
    ARCH_INT_USART2,        // �ж����
    0,                      // �����Ƿ��ڷ���״̬��0��û�����ڷ��ͣ�1�����ڷ���
    {0},                    // ���ͻ�������������contiki�Ļ��λ�������
    19200,                  // Ĭ�ϲ�����
    {0},                    // ���ͻ��λ�����
    NULL                    // Ĭ���������뺯��
};
// ����3
stm32_serial_info tUsart3Info  =  {
    USART3_BASE,            // ģ�����ַ
    RCC_PERIPHERAL_USART3,  //  �����������ԣ�����ȷ������ʱ��
    ARCH_INT_USART3,        // �ж����
    0,                      // �����Ƿ��ڷ���״̬��0��û�����ڷ��ͣ�1�����ڷ���
    {0},                    // ���ͻ�������������contiki�Ļ��λ�������
    19200,                  // Ĭ�ϲ�����
    {0},                    // ���ͻ��λ�����
    NULL                    // Ĭ���������뺯��
};

/*********************************************************************************************************
** Function name:       serial_set_input
** Descriptions:        ���ô������봦����
** input parameters:    handle: ��������������
**                      input:  ָ��������
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void serial_set_input(void *handle, int (*input)(unsigned char c))
{
    stm32_serial_info *serial_handle = handle;
    
    serial_handle->serial_input_handler = input;
}

/*********************************************************************************************************
** Function name:       serial_writeb
** Descriptions:        ���ڷ������ݣ�����һ���ֽڵ�����
** input parameters:    handle: ��������������
**                      c:      �����͵�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void serial_writeb(void *handle, unsigned char c)
{
    stm32_serial_info *serial_handle = handle;
    //watchdog_periodic();
    
    //�������ݷ��뷢�ͻ�����
    while(ringbuf_put(&serial_handle->txbuf, c) == 0);

    if(0 == serial_handle->transmitting) {
        serial_handle->transmitting = 1;
        while(!(UsartSpaceAvial(serial_handle->base)));
        UsartCharPut(serial_handle->base, ringbuf_get(&serial_handle->txbuf));
        UsartIntEnable(serial_handle->base,USART_INT_TX_EMPTY);
    }
}

/*********************************************************************************************************
** Function name:       serial_init
** Descriptions:        ���ڳ�ʼ��
** input parameters:    handle: ��������������
**                      u32Buad: ���ڲ�����
**                      pfIsrHandler: �жϷ�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void serial_init(void *handle, uint32 u32Buad, void(*pfIsrHandler)(void))
{
    uint32 u32Clock;
    stm32_serial_info *serial_handle = handle;
    
    // ��������ʱ��
    SystemPeripheralEnable(serial_handle->u8WhichBus, serial_handle->u32Ctrl);
    // ��ȡ����ʱ��
    u32Clock = SystemPeripheralClockGet(serial_handle->u8WhichBus, serial_handle->u32Ctrl);

    serial_handle->transmitting = 0;
    ringbuf_init(&serial_handle->txbuf, serial_handle->sndBuf, UART_SEND_BUFFER_SIZE); 

    UsartConfigSet(serial_handle->base,u32Clock,u32Buad,
                       (USART_WLEN_8 | USART_PAR_NONE | USART_STOP_1));
   
    serial_handle->Baud = u32Buad;
    UsartIntEnable(serial_handle->base,USART_INT_RX);
    hal_int_register(serial_handle->int_num, pfIsrHandler);
    hal_int_priority_set(serial_handle->int_num, 0x00);
    hal_int_enable(serial_handle->int_num);
    UsartEnable(serial_handle->base);
}

/*********************************************************************************************************
** Function name:       stm32_serial_ISR
** Descriptions:        �����жϴ��������ú�����Ҫ���ж������
** input parameters:    handle
**                      NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void stm32_serial_ISR(void *handle)
{
   unsigned char c;
   stm32_serial_info *serial_handle = handle;
   
   if(!(HWREG32(serial_handle->base + USART_O_CR1) & USART_INT_TX_EMPTY)) // ������Ϳ��ж�δʹ��
   {
     goto STM32_USART_RECV_HANDLER;
   }
   if(HWREG32(serial_handle->base + USART_O_SR) & 0x0080)                 //  ����Ƿ����ж�
   {
        if(1 == serial_handle->transmitting) {
            if(0 == ringbuf_elements(&serial_handle->txbuf)) {
                UsartIntDisable(serial_handle->base,USART_INT_TX_EMPTY);
                while(!(HWREG32(serial_handle->base + USART_O_SR) & 0x0040)); //  �ȴ��������
                serial_handle->transmitting = 0;
            } else {
                HWREG32(serial_handle->base + USART_O_DR) = ringbuf_get(&serial_handle->txbuf);
            }
        } else {
            UsartIntDisable(serial_handle->base,USART_INT_TX_EMPTY);
        }
    }

   
STM32_USART_RECV_HANDLER:
    if(HWREG32(serial_handle->base + USART_O_SR) & 0x0020)            //  ����ǽ����ж�
    {
        c = (unsigned char)(HWREG32(serial_handle->base + USART_O_DR) & 0x01FF);
        if(NULL != serial_handle->serial_input_handler) {
            serial_handle->serial_input_handler(c);
        }
    }
   
   if(HWREG32(serial_handle->base + USART_O_SR) & 0x0008)             //  ��������ݹ�����
   {
        c = (unsigned char)(HWREG32(serial_handle->base + USART_O_DR) & 0x01FF);
        if(NULL != serial_handle->serial_input_handler) {
            serial_handle->serial_input_handler(c);
        }
   } 
}

// ���ڵ��жϷ���������Ҫע�����ж���������
void Usart1_ISR(void)
{
   stm32_serial_ISR(&tUsart1Info);
}

void Usart2_ISR(void)
{
   stm32_serial_ISR(&tUsart2Info);
}

void Usart3_ISR(void)
{
   stm32_serial_ISR(&tUsart3Info);
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
