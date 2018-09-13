/****************************************Copyright (c)****************************************************
**                                蓝精灵6lowpan无线开发平台
**                                  一切为开源应用而作
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           Main.c
** Last modified Date:  2012-06-21
** Last Version:        v1.0
** Description:         contiki下主函数的模板
**
**--------------------------------------------------------------------------------------------------------
** Created By:          任海波
** Created date:        2012-06-21
** Version:             v1.0
** Descriptions:        The original version 初始版本
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
**  全局变量定义
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
**  外部函数声明
*********************************************************************************************************/
//PROCESS_NAME(udp_client_process);

/*********************************************************************************************************
**  内部函数声明
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
**  自启动的线程
*********************************************************************************************************/
AUTOSTART_PROCESSES(&led_process);

/*********************************************************************************************************
**  操作系统需要的定义
*********************************************************************************************************/
PROCINIT(NULL);


/*********************************************************************************************************
** Function name:       main
** Descriptions:        主函数的模板，一般不要随意更改
** input parameters:    无
** output parameters:   无
** Returned value:      0
** Created by:          任海波
** Created Date:        2012-06-21
*********************************************************************************************************/
int main (void)
{
    // 初始化系统服务
    sys_services_init();

    // 初始化总线驱动
    __GtSpiBusDriver.spi_bus_init(&__GtSpiBusDriver);

    // 初始化控制台
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
    /****************自定義初始化************/
    // 初始化网络协议栈
    //只初始化物理层
      moteid_init();
      NETSTACK_RADIO.init();
      NETSTACK_RADIO.on();
      //初始化moteid
     
    /*****************************************/    
        
    energest_init();
    ENERGEST_ON(ENERGEST_TYPE_CPU);

    autostart_start(autostart_processes);
    for(;;)
    {
        do
        {
            // 喂狗
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
