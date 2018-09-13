/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           Main.c
** Last modified Date:  2012-06-21
** Last Version:        v1.0
** Description:         contiki����������ģ��
**
**--------------------------------------------------------------------------------------------------------
** Created By:          �κ���
** Created date:        2012-06-21
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
#include "includes.h"
#include "yxh_mac.h"
#include "globalmacro.h"
#include "app.h"
/*********************************************************************************************************
**  ȫ�ֱ�������
*********************************************************************************************************/
#define DEBUG 1
#if DEBUG
#include "runtime/uartstdio.h"
#define PRINTF(...)   uart_printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
uint8_t mote=1;
uint8_t off=0;
uint8_t mote_num =50;
uint8_t mode_code[50]=
{1,2,6,7,11,12,16,17,21,22,
  3,4,8,9,13,14,18,19,23,24,
    5,50,10,45,15,40,20,35,25,30,
      46,47,41,42,36,37,31,32,26,27,
        48,49,43,44,38,39,33,34,28,29};
/*********************************************************************************************************
**  �ⲿ��������
*********************************************************************************************************/
//PROCESS_NAME(udp_client_process);

/*********************************************************************************************************
**  �ڲ���������
*********************************************************************************************************/
PROCESS(led_process, "Blink1");
PROCESS_THREAD(led_process, ev, data)
{
  PROCESS_BEGIN();
  
  while(1)
  {
    static struct etimer et;
    etimer_set(&et, CLOCK_SECOND/20);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
      
    if(get_moteid() == 16)
    {
    /*
      if(is_buffer_clear()){
         while(mote<mote_num )
        {
        if(off%2)
        control_mote_led_status(mode_code[mote],LED_OFF,LED_OFF);
        else
        control_mote_led_status(mode_code[mote],LED_ON,LED_ON);
        mote++;
        }
        mote =0;
        off++;
    
      }*/
      
      if(is_buffer_clear())
      {
        mote_shift(mode_code,mote);

        mote++;
        if(mote>9)
          mote=0;
      }
      
    }
      

  
    PRINTF("The moteid is %d \r\n",get_moteid());
  }
   PROCESS_END();
}

/*********************************************************************************************************
**  ���������߳�
*********************************************************************************************************/
AUTOSTART_PROCESSES(&led_process);

/*********************************************************************************************************
**  ����ϵͳ��Ҫ�Ķ���
*********************************************************************************************************/
PROCINIT(NULL);


/*********************************************************************************************************
** Function name:       main
** Descriptions:        ��������ģ�壬һ�㲻Ҫ�������
** input parameters:    ��
** output parameters:   ��
** Returned value:      0
** Created by:          �κ���
** Created Date:        2012-06-21
*********************************************************************************************************/
int main (void)
{
    // ��ʼ��ϵͳ����
    sys_services_init();

    // ��ʼ����������
    __GtSpiBusDriver.spi_bus_init(&__GtSpiBusDriver);

    // ��ʼ������̨
    uart_stdio_init(115200);
    moteid_init();

    PRINTF("The Contiki System Start!\r\n");

    clock_init();
    rtimer_init();
    process_init();

    random_init(0);

    procinit_init();
    process_start(&etimer_process, NULL);
    ctimer_init();
    /****************�Զ��x��ʼ��************/
    // ��ʼ������Э��ջ
    //ֻ��ʼ�������
      moteid_init();
      NETSTACK_RADIO.init();
      NETSTACK_RADIO.on();
      //��ʼ��moteid
     
    /*****************************************/    
        
    energest_init();
    ENERGEST_ON(ENERGEST_TYPE_CPU);

    autostart_start(autostart_processes);
    for(;;)
    {
        do
        {
            // ι��
            // watchdog_periodic();
        } while(process_run() > 0);
      // contiki_net_handle();
        //contiki_power_manager();

        // Stop processor clock
         //asm("wfi"::);
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
