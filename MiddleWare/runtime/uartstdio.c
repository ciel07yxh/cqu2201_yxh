/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               uartstdio.c
** Last modified Date:      2012-06-30
** Last Version:            v1.0
** Description:             ���ڿ���̨����ʵ��
**
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-06-30
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
#include <stdarg.h>
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_rcc.h"
#include "hal/arch/inc/arch_io_usart.h"
#include "hal/arch/inc/arch_io_gpio.h"
#include "hal/CortexM3/hal_io_level.h"
#include "hal/arch/inc/arch_io_ints.h"
#include "runtime/uartstdio.h"

#include "dev/serial-line.h"

/*********************************************************************************************************
**  ����
*********************************************************************************************************/
#define UART_STDIO_BASE        USART1_BASE
#define RCC_UART_PERIPHERAL    RCC_PERIPHERAL_USART1
#define STDIO_UART_INT         ARCH_INT_USART1

/*********************************************************************************************************
**  int����ʮ������0-f�Ķ�Ӧ�ַ�����
*********************************************************************************************************/
static const char * const __GpcHexTable = "0123456789abcdef";

/*********************************************************************************************************
** Function name:       uart_byte_write
** Descriptions:        �򴮿ڷ���һ���ֽڵ�����
** Input parameters:    c: ���͵�����
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
static uint16 uart_byte_write(uint16 ch)
{
    // �ȴ��з��Ϳռ�
    while(!(HWREG32(UART_STDIO_BASE + USART_O_SR) & 0x0080)) ;
    HWREG32(UART_STDIO_BASE + USART_O_DR) = ch;
    //while(!(HWREG(UART_STDIO_BASE + USART_O_SR) & 0x0040));   //  �ȴ��������

    return ch;
}

/*********************************************************************************************************
** Function name:       uart_byte_read
** Descriptions:        �Ӵ��ڶ�ȡһ���ֽڵ�����
** Input parameters:    c: ���͵�����
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
static uint16 uart_byte_read(void)
{
    // �ȴ��յ�����
    while(!(HWREG32(UART_STDIO_BASE + USART_O_SR) & 0x0020));  
    // ��ȡ���ݲ�����
    return (HWREG32(UART_STDIO_BASE + USART_O_DR) & 0x01FF);
}

/*********************************************************************************************************
** Function name:       uart_stdio_isr
** Descriptions:        �жϷ�����
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
static void uart_stdio_isr(void)
{
   uint8 c;
   
   if(HWREG32(UART_STDIO_BASE + USART_O_SR) & 0x0020)             //  ����ǽ����ж�
   {
      c = (unsigned char)(HWREG32(UART_STDIO_BASE + USART_O_DR) & 0x01FF);
      serial_line_input_byte(c);
     //������ܵ��˴ӱʼǱ����Է��͵� 0x4c ������Ҫ����Bootloader ���ع̼� ����������BootLoader��
       if(0x4c==c){
        hal_cpu_reset();
      }
   }
   
   if(HWREG32(UART_STDIO_BASE + USART_O_SR) & 0x0008)             //  ��������ݹ�����
   {
      c = (unsigned char)(HWREG32(UART_STDIO_BASE + USART_O_DR) & 0x01FF);
      serial_line_input_byte(c);
   } 
}

/*********************************************************************************************************
** Function name:       uart_stdio_init
** Descriptions:        ���ڿ���̨��ʼ��
** Input parameters:    u32Baud: ��ʼ���Ĵ��ڲ�����
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void uart_stdio_init(uint32 u32Baud)
{
    uint32 u32Clock;
    
    // ��������ʱ��
    SystemPeripheralEnable(RCC_PERIPHERAL_IOPA);
    SystemPeripheralEnable(RCC_PERIPHERAL_AFIO);
    SystemPeripheralEnable(RCC_UART_PERIPHERAL);
    
    // ����������ӳ��
    //AFIORemapEnable(AFIO_REMAP_USART1_REAMP);
    
    // ����IO����Ϊ���ù���
    GPIOConfigSet(GPIOA_BASE, GPIO_PIN_9, GPIO_AF_PP | GPIO_SPEED_50MHZ);
    GPIOConfigSet(GPIOA_BASE, GPIO_PIN_10, GPIO_DIR_IN_Floating);

    // ��ȡ����ʱ��
    u32Clock = SystemPeripheralClockGet(RCC_UART_PERIPHERAL);
    // ���ô���
    UsartConfigSet(UART_STDIO_BASE,u32Clock,u32Baud,
                       (USART_WLEN_8 | USART_PAR_NONE | USART_STOP_1));
    hal_int_register(STDIO_UART_INT, uart_stdio_isr);
    hal_int_priority_set(STDIO_UART_INT, 0x00);
    hal_int_enable(STDIO_UART_INT);
    UsartIntEnable(UART_STDIO_BASE,USART_INT_RX);
    UsartEnable(UART_STDIO_BASE);
}

/*********************************************************************************************************
** Function name:       uart_write_string
** Descriptions:        �򴮿ڷ���ָ���ֽڵ�����
** Input parameters:    pcBuf:  �������ݵ�ַ
**                      u32Len: �������ݳ���
** Output parameters:   ��
** Returned value:      ʵ�ʷ��͵����ݳ���
*********************************************************************************************************/
int uart_write_string(const char *pcBuf, uint32 u32Len)
{
    int i;

    for(i=0; i<u32Len; i++)
    {
        if(pcBuf[i] == '\n') {
            uart_byte_write('\r');
        }
        uart_byte_write(pcBuf[i]);
    }

    return i;
}

/*********************************************************************************************************
** Function name:       uart_read_string
** Descriptions:        �Ӵ����ж�ȡһ��������
** Input parameters:    pcBuf:  ��ȡ���ݵ�ַ
**                      u32Len: ��ȡ���ݳ���
** Output parameters:   ��
** Returned value:      ʵ�ʶ�ȡ�����ݳ���
*********************************************************************************************************/
int uart_read_string(char *pcBuf, uint32 u32Len)
{
    uint32 u32Count;
    char ch;
    static char bLastWasCR = 0;

    u32Len--;

    // �����ַ���ֱ���µ�һ�������յ�
    while(1)
    {
        // ��ȡһ������
        ch = (char)uart_byte_read();

        // ���������Backspace
        if(ch == '\b')
        {
            // ���buffer�����ݣ�ɾ�����һ������
            if(u32Count)
            {
                // ����֮ǰ������
                uart_write_string("\b \b", 3);

                // ���ٻ����������ݸ���
                u32Count--;
            }

            // ��������һ������
            continue;
        }

        // ����ַ���LF����һ���ַ���CR������EQL
        if((ch == '\n') && bLastWasCR)
        {
            bLastWasCR = 0;
            continue;
        }

        // �Ƿ�Ҫ��س�����
        if((ch == '\r') || (ch == '\n') || (ch == 0x1b))
        {
            // �س�����
            if(ch == '\r')
            {
                bLastWasCR = 1;
            }

            // ������������
            break;
        }

        // �����յ����ַ�
        if(u32Count < u32Len)
        {
            // �洢�յ����ַ�
            pcBuf[u32Count] = ch;

            // �����յ����ַ���������
            u32Count++;

            // �����ַ���
            uart_byte_write(ch);
        }
    }

    // ���'\0'���ַ���������־
    pcBuf[u32Count] = 0;

    // ����һ���س�����
    uart_write_string("\r\n", 2);

    // ����buffer�е��ַ�������������'\0'
    return(u32Count);
}

/*********************************************************************************************************
** Function name:       uart_getc
** Descriptions:        �Ӵ����ж�ȡһ���ֽڵ����ݣ�������������CPU��ֱ���յ�����
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��ȡ��������
*********************************************************************************************************/
unsigned char uart_getc(void)
{
    // �Ӵ��ڶ�ȡһ���ַ�
    return(uart_byte_read());
}

/*********************************************************************************************************
** Function name:       uart_putc
** Descriptions:        �Ӵ����з���һ���ֽڵ�����
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void uart_putc(unsigned char ch)
{
    uart_byte_write(ch);
}

/*********************************************************************************************************
** Function name:       uart_printf
** Descriptions:        ͨ������ʵ��printf������Ŀǰ֧��\%c, \%d, \%p, \%s, \%u, \%x, and \%X.
**                      \%c to print a character
**                      \%d to print a decimal value
**                      \%s to print a string
**                      \%u to print an unsigned decimal value
**                      \%x to print a hexadecimal value using lower case letters
**                      \%X to print a hexadecimal value using lower case letters (not upper case
**                      letters as would typically be used)
**                      \%p to print a pointer as a hexadecimal value
**                      \%\% to print out a \% character
** Input parameters:    �ͱ�׼IO����printf��ͬ
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void uart_printf(const char *pcString, ...)
{
    uint32 u32Idx, u32Value, u32Pos,u32Count,u32Base,u32Neg;
    char *pcStr, pcBuf[16], cFill;
    va_list vaArgP;

    // ��ʼ��������
    va_start(vaArgP, pcString);

    // ѭ��ֱ���ַ�������
    while(*pcString)
    {
        // Ѱ�ҵ�һ��'%'��λ�û����ַ�������'\0'��λ��
        for(u32Idx = 0; (pcString[u32Idx] != '%') && (pcString[u32Idx] != '\0');
            u32Idx++)
        {
        }

        // ����%֮ǰ���ַ�
        uart_write_string(pcString, u32Idx);

        // �ַ�ָ�����
        pcString += u32Idx;

        // �����һ���ַ���'%'
        if(*pcString == '%')
        {
            // ����%
            pcString++;

            // ������ֵ����Ϊ0��Ĭ���ѿո����
            u32Count = 0;
            cFill = ' ';

            // ѭ�����������ַ�������ʹ��gotoʵ�֣���Ȼ�����飬���Ǻܸ�Ч
uart_printf_again:

            // ������δ�����һ���ַ�
            switch(*pcString++)
            {
                // ��������
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    // �����һ��������0�����滻�ո���0���
                    if((pcString[-1] == '0') && (u32Count == 0))
                    {
                        cFill = '0';
                    }

                    // ����ֵ��10
                    u32Count *= 10;
                    u32Count += pcString[-1] - '0';

                    // ��ȡ��һ���ַ�
                    goto uart_printf_again;
                }

                // ����%c����
                case 'c':
                {
                    // ��ȡ����
                    //u32Value = va_arg(vaArgP, uint32);
                    u32Value = (uint32)va_arg(vaArgP, int);

                    // �����ַ�
                    uart_write_string((char *)&u32Value, 1);

                    break;
                }

                // ����%d����
                case 'd':
                {
                    // ��ȡ����
                    //u32Value = va_arg(vaArgP, uint32);
                    u32Value = (uint32)va_arg(vaArgP, int);

                    // ��λbufferλ��ָ��
                    u32Pos = 0;

                    // ���ֵ�Ǹ�����������������Ҽ�һ�����ű�־
                    if((int32)u32Value < 0)
                    {
                        // ȡ�෴��
                        u32Value = -(int32)u32Value;

                        // ��־����
                        u32Neg = 1;
                    } else {
                        // ��־����
                        u32Neg = 0;
                    }

                    // ����10����
                    u32Base = 10;

                    // ת��ΪASCII.
                    goto uart_printf_convert;
                }

                // ����%s����
                case 's':
                {
                    // ��ȡ�ַ�������ָ��
                    pcStr = va_arg(vaArgP, char *);

                    // �ж��ַ�������
                    for(u32Idx = 0; pcStr[u32Idx] != '\0'; u32Idx++)
                    {
                    }

                    // �����ַ���
                    uart_write_string(pcStr, u32Idx);

                    // д��Ҫ�Ŀո�
                    if(u32Count > u32Idx)
                    {
                        u32Count -= u32Idx;
                        while(u32Count--)
                        {
                            uart_write_string(" ", 1);
                        }
                    }

                    break;
                }

                //
                // Handle the %u command.
                // ����%u
                case 'u':
                {
                    // ��ȡ����
                    //u32Value = va_arg(vaArgP, uint32);
                    u32Value = (uint32)va_arg(vaArgP, int);

                    // ��λbufferλ��ָ��
                    u32Pos = 0;

                    // ����ʮ����
                    u32Base = 10;

                    // ��־������
                    u32Neg = 0;

                    // ת��ΪASCII
                    goto uart_printf_convert;
                }

                // ����%x��%X��%p, ��ʱ%p��%x����ͬ�Ĵ���.
                case 'x':
                case 'X':
                case 'p':
                {
                    // ��ȡ����
                   // u32Value = va_arg(vaArgP, uint32);
                    u32Value = va_arg(vaArgP, int);

                    // ��λbufferλ��ָ��
                    u32Pos = 0;

                    // ����ʮ������
                    u32Base = 16;

                    // ָʾ����
                    u32Neg = 0;

                    // ת��ASCIIʵ��
uart_printf_convert:
                    for(u32Idx = 1;
                        (((u32Idx * u32Base) <= u32Value) &&
                         (((u32Idx * u32Base) / u32Base) == u32Idx));
                        u32Idx *= u32Base, u32Count--)
                    {
                    }

                    // ����Ǹ����������ַ�����
                    if(u32Neg)
                    {
                        u32Count--;
                    }

                    // ����Ǹ�����������0���
                    if(u32Neg && (cFill == '0'))
                    {
                        // ���ȱ�ٵķ���λ
                        pcBuf[u32Pos++] = '-';

                        // ��������λ���رշ��ű�־
                        u32Neg = 0;
                    }

                    // �����Ҫ�����Ӷ�������
                    if((u32Count > 1) && (u32Count < 16))
                    {
                        for(u32Count--; u32Count; u32Count--)
                        {
                            pcBuf[u32Pos++] = cFill;
                        }
                    }

                    // ����Ǹ����ڣ�����ֵǰ��һ������
                    if(u32Neg)
                    {
                        // ��ӷ���
                        pcBuf[u32Pos++] = '-';
                    }

                    // ����ֵת��Ϊstring
                    for(; u32Idx; u32Idx /= u32Base)
                    {
                        pcBuf[u32Pos++] = __GpcHexTable[(u32Value / u32Idx) % u32Base];
                    }

                    // ����string
                    uart_write_string(pcBuf, u32Pos);

                    break;
                }

                // ����%%
                case '%':
                {
                    // �򵥵ط���һ��string
                    uart_write_string(pcString - 1, 1);
                    break;
                }

                // ��������������
                default:
                {
                    // ָʾ������ʾ
                    uart_write_string("ERROR", 5);
                    break;
                }
            }
        }
    }

    // �����������
    va_end(vaArgP);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
