/****************************************Copyright (c)****************************************************
**                                
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           app.c
** Last modified Date:  2018-06-07
** Last Version:        v1.0
** Description:         
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Zxy
** Created date:        2018-06-07
** Version:             v1.0
** Descriptions:        The original version 
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
#include "moteid.h"
#include "app.h"
/*********************************************************************************************************
**  Define global variaty
*********************************************************************************************************/
#define DEBUG 1
#if DEBUG
#include "runtime/uartstdio.h"
#define PRINTF(...)   uart_printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
/*********************************************************************************************************
** Function name:       control_mote_led_status
** Descriptions:        ����ָ���Ľڵ�LED״̬
** Input parameters:    �ڵ�� �̵�״̬ ���״̬
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void control_mote_led_status(uint16 moteid,uint8_t led_green_status,uint16_t led_red_status)
{
  //��ʼ���ṹ����
  app_led_t app_led =
  {
    moteid,
    led_green_status,
    led_red_status
  };
  
  //�����µ�֡
  yxh_playload_t payload;
 
  //��������
  payload.payload_len = sizeof(app_led_t);
  memcpy(payload.buf,&app_led,sizeof(app_led_t));
  
  //����һ֡����
  yxh_frame_send(&payload,app_led.moteid);
}

/*********************************************************************************************************
** Function name:       set_mote_led_status
** Descriptions:        ����ָ���Ľڵ�LED״̬
** Input parameters:    �ṹ�� app_led_t
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void set_mote_led_status(app_led_t *app_led)
{
  if(app_led->moteid!=get_moteid())
    PRINTF("��ַ���� %d %d \r\n",get_moteid(),app_led->moteid);
  
  if(app_led->green_led_state == LED_ON)
    sys_led_on(LED_GREEN);
  if(app_led->green_led_state == LED_OFF)
    sys_led_off(LED_GREEN);
  if(app_led->red_led_state == LED_ON)
    sys_led_on(LED_RED);
  if(app_led->red_led_state == LED_OFF)
    sys_led_off(LED_RED);
}


/*********************************************************************************************************
** Function name:       set_mote_led_status
** Descriptions:        ����ָ���Ľڵ�LED״̬
** Input parameters:    �ṹ�� app_led_t
** Output parameters:   None ��
** Returned value:      None ��
*********************************************************************************************************/
void mote_shift(uint8 *list,uint8 pos)
{
  if(pos>47)
    pos=47;
  for(uint8_t i=0;i<3;i++){
    control_mote_led_status(*(list+pos+i),LED_ON,LED_ON);
    control_mote_led_status(*(list+pos+i+10),LED_ON,LED_ON);
    control_mote_led_status(*(list+pos+i+20),LED_ON,LED_ON);
    control_mote_led_status(*(list+pos+i+30),LED_ON,LED_ON);
    control_mote_led_status(*(list+pos+i+40),LED_ON,LED_ON);
  }
  
    
    control_mote_led_status(*(list+pos),LED_OFF,LED_OFF);
    control_mote_led_status(*(list+pos+10),LED_OFF,LED_OFF);
    control_mote_led_status(*(list+pos+20),LED_OFF,LED_OFF);
    control_mote_led_status(*(list+pos+30),LED_OFF,LED_OFF);
    control_mote_led_status(*(list+pos+40),LED_OFF,LED_OFF);
}