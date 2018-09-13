/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               contiki_net_init.c
** Last modified Date:      2012-06-28
** Last Version:            v1.0
** Description:             ����ģ���ʼ������ʵ��
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

/*********************************************************************************************************
** ͷ�ļ�����
*********************************************************************************************************/
#include "contiki.h"
#include "contiki-net.h"
#include "net/at86rf23x_drv.h"
#include "contiki_net_init.h"

#if NETSTACK_CONF_WITH_IPV6

#include "net/packetbuf.h"
#include <stdlib.h>

#define DEBUG 0
#if DEBUG
#include "uart_stdio/uartstdio.h"
#define PRINTF(...)   uart_printf(__VA_ARGS__)
#define PRINT6ADDR(addr) PRINTF(" %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x ", ((u8_t *)addr)[0], ((u8_t *)addr)[1], ((u8_t *)addr)[2], ((u8_t *)addr)[3], ((u8_t *)addr)[4], ((u8_t *)addr)[5], ((u8_t *)addr)[6], ((u8_t *)addr)[7], ((u8_t *)addr)[8], ((u8_t *)addr)[9], ((u8_t *)addr)[10], ((u8_t *)addr)[11], ((u8_t *)addr)[12], ((u8_t *)addr)[13], ((u8_t *)addr)[14], ((u8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF(" %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x ",lladdr.u8[0], lladdr.u8[1], lladdr.u8[2], lladdr.u8[3],lladdr.u8[4], lladdr.u8[5], lladdr.u8[6], lladdr.u8[7])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

// ���ʹ������������
#if ENERGEST_CONF_ON
static unsigned long irq_energest = 0;
#define ENERGEST_IRQ_SAVE(a) do { \
    a = energest_type_time(ENERGEST_TYPE_IRQ); } while(0)
#define ENERGEST_IRQ_RESTORE(a) do { \
    energest_type_set(ENERGEST_TYPE_IRQ, a); } while(0)
#else
#define ENERGEST_IRQ_SAVE(a) do {} while(0)
#define ENERGEST_IRQ_RESTORE(a) do {} while(0)
#endif

/*********************************************************************************************************
** Function name:       contiki_set_link_addr
** Descriptions:        ����mac�ĵ�ַ���õ�ַ��8���ֽڵĳ���ַ
** Input parameters:    bIsTest: �Ƿ��ڲ���ģʽ
**                      macaddr:  ���õ�mac��ַ����bIsTestΪfalseʱ��Ч    
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void contiki_set_link_addr(bool_t bIsTest, uint8 *macaddr)
{
  int i;
  linkaddr_t tLinkAddr = LINK_ADDR_DEFAULT;
  
  if(bIsTest == false) {
     memcpy(tLinkAddr.u8, macaddr, 8);
  }

  PRINTF("Link Address is %d bytes long\r\n", sizeof(sizeof(linkaddr_t)));


#if NETSTACK_CONF_WITH_IPV6
  memcpy(&uip_lladdr.addr, &tLinkAddr, sizeof(uip_lladdr.addr));
#endif

#if NETSTACK_CONF_WITH_IPV6
  linkaddr_set_node_addr(&tLinkAddr);
#else  
  linkaddr_set_node_addr((linkaddr_t *)&tLinkAddr.u8[8 - LINKADDR_CONF_SIZE]);
#endif

  PRINTF("Link Address started with address \r\n");
  for(i = 0; i < sizeof(linkaddr_t) - 1; i++) {
    PRINTF("%d.", linkaddr_node_addr.u8[i]);
  }
  PRINTF("%d\n", linkaddr_node_addr.u8[i]);

  i = (((int)linkaddr_node_addr.u8[LINKADDR_CONF_SIZE - 1]) << 8) | ((int)linkaddr_node_addr.u8[LINKADDR_CONF_SIZE - 2]);
  ieee_set_pan_addr(IEEE802154_CONF_PANID,i, linkaddr_node_addr.u8);
  
  return;
}

/*********************************************************************************************************
** Function name:       contiki_net_init
** Descriptions:        contiki����ģ���ʼ��
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void contiki_net_init(void)
{
    // ��ʼ������Э��ջ
    netstack_init();
    contiki_set_link_addr(true, NULL);
    queuebuf_init();
    process_start(&tcpip_process, NULL);
}

/*********************************************************************************************************
** Function name:       contiki_net_handle
** Descriptions:        contiki���紦��
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void contiki_net_handle(void)
{
    static uint8_t u8Len;
    u8Len = NETSTACK_RADIO.pending_packet();
    if(u8Len) {
      packetbuf_clear();
      u8Len = NETSTACK_RADIO.read(packetbuf_dataptr(), PACKETBUF_SIZE);
      if(u8Len > 0) {
        packetbuf_set_datalen(u8Len);
        NETSTACK_RDC.input();
      }
    }
}

/*********************************************************************************************************
** Function name:       contiki_net_rssi_get
** Descriptions:        ��ȡ��ǰ�ź�ǿ��
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��ǰ֡���ź�ǿ��
*********************************************************************************************************/
uint8_t contiki_net_rssi_get(void)
{
    return (packetbuf_attr(PACKETBUF_ATTR_RSSI));
}

/*********************************************************************************************************
** Function name:       contiki_net_lqi_get
** Descriptions:        ��ȡ������·����
** Input parameters:    ��
** Output parameters:   ��
** Returned value:      ��ǰ֡����·����
*********************************************************************************************************/
uint8_t contiki_net_lqi_get(void)
{
   return (packetbuf_attr(PACKETBUF_ATTR_LINK_QUALITY));
}
#endif /* NETSTACK_CONF_WITH_IPV6 */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

