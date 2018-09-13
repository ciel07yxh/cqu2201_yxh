/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               contiki_net_init.h
** Last modified Date:      2012-06-28
** Last Version:            v1.0
** Description:             ����ģ���ʼ����������
**
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-06-28
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
#ifndef __CONTIKI_NET_INIT_H__
#define __CONTIKI_NET_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "contiki.h"
#include "contiki-net.h"

/*********************************************************************************************************
  MAC��ַ����
*********************************************************************************************************/
#define LINK_ADDR_DEFAULT       {{0x02,0x00,0x00,0xff,0xfe,0x00,0x00,0x01}}


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
#if ENERGEST_CONF_ON
#define ENERGEST_IRQ_SAVE(a) do { \
    a = energest_type_time(ENERGEST_TYPE_IRQ); } while(0)
#define ENERGEST_IRQ_RESTORE(a) do { \
    energest_type_set(ENERGEST_TYPE_IRQ, a); } while(0)
#else
#define ENERGEST_IRQ_SAVE(a) do {} while(0)
#define ENERGEST_IRQ_RESTORE(a) do {} while(0)
#endif

/*********************************************************************************************************
** �ⲿ��������
*********************************************************************************************************/
extern void contiki_set_link_addr(bool_t bIsTest, uint8 *macaddr);
extern void contiki_net_init(void);
extern void contiki_net_handle(void);
extern uint8_t contiki_net_rssi_get(void);
extern uint8_t contiki_net_lqi_get(void);

#ifdef __cplusplus
    }
#endif


#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

