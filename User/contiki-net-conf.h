/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���                            
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               contiki-net-conf.h
** Last modified Date:      2012-06-29
** Last Version:            v1.0
** Description:             contiki������ģ������ͷ�ļ�,���ļ����½�����һ����Ϊ�˺�contiki-conf.h���룬��
**                          ��Ҫ��contiki-conf.h�б�����
**
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2012-06-29
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
#ifndef __CONTIKI_NET_CONF_H__
#define __CONTIKI_NET_CONF_H__


#include <string.h>

/*********************************************************************************************************
** ����ģ������
*********************************************************************************************************/
// ���崦�����Ĵ�С�ˣ�����;���Ĵ��������
#define UIP_CONF_BYTE_ORDER       UIP_LITTLE_ENDIAN  //UIP_BIG_ENDIAN

 // When set, this directive also configures the following bypasses:
 // - process_post_synch() in tcpip_input() (we call packet_input())
 // - process_post_synch() in tcpip_uipcall (we call the relevant pthread)
 // - mac_call_sent_callback() is replaced with sent() in various places
 // These are good things to do, they reduce stack usage and prevent crashes
#define NETSTACK_CONF_SHORTCUTS   1

#define NETSTACK_CONF_RADIO	    at86rf231_rf_driver

 // ���������������ӿ�
#define NETSTACK_CONF_NETWORK       sicslowpan_driver
#define NETSTACK_CONF_MAC           nullmac_driver  // nullmac_driver //csma_driver  
#define NETSTACK_CONF_RDC           nullrdc_driver // contikimac_driver // nullrdc_driver
#define NETSTACK_CONF_FRAMER        framer_802154

#define NULLRDC_802154_AUTOACK      0
#define NULLRDC_802154_AUTOACK_HW   1
#define NULLRDC_CONF_SEND_802154_ACK      0
#define NETSTACK_CONF_MAC_SEQNO_HISTORY   16


#if (NETSTACK_CONF_RDC == nullrdc_driver)
#endif

// contikimac������
#if (NETSTACK_CONF_RDC == contikimac_driver)
#define CONTIKIMAC_CONF_WITH_PHASE_OPTIMIZATION         0
#define CONTIKIMAC_CONF_WITH_CONTIKIMAC_HEADER          0
#define RDC_CONF_HARDWARE_CSMA       1
#define RDC_CONF_HARDWARE_ACK        1
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE            16
#define CONTIKIMAC_CONF_SHORTEST_PACKET_SIZE            43-18
#define CONTIKIMAC_CONF_AFTER_ACK_DETECTECT_WAIT_TIME   RTIMER_ARCH_SECOND / 1400
#define CONTIKIMAC_CONF_COMPOWER               1
#endif



////#define CONTIKIMAC_CONF_SHORTEST_PACKET_SIZE                   43-18
////#define CONTIKIMAC_CONF_AFTER_ACK_DETECTECT_WAIT_TIME          RTIMER_ARCH_SECOND / 1400
//#define RDC_CONF_HARDWARE_ACK	                               1
//#define RDC_CONF_HARDWARE_CSMA	                               1
//#define CONTIKIMAC_CONF_WITH_PHASE_OPTIMIZATION                0
////#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE                   16
//#define CONTIKIMAC_CONF_WITH_CONTIKIMAC_HEADER                 0
//#endif




// �������������PAN ID
#define IEEE802154_CONF_PANID       0x1420   // UIP_HTONS(0x2014)
// ����ͨ���ŵ�, 15, 16, 21, 22����WIFI�����ŵ��ŵ�
#define IEEE802154_RF_CONF_CHANNEL  22

// �Ƿ�ʹ��uIPv6
#define NETSTACK_CONF_WITH_IPV6			1
// ���������uIPv6��������ص�����
#if NETSTACK_CONF_WITH_IPV6
// Addresses, Sizes and Interfaces
// 8-byte addresses here, 2 otherwise
#define LINKADDR_CONF_SIZE              8
#define UIP_CONF_LL_802154              1
#define UIP_CONF_LLH_LEN                0
#define UIP_CONF_NETIF_MAX_ADDRESSES    3
 
// TCP, UDP, ICMP
#define UIP_CONF_TCP                    1
#define UIP_CONF_UDP                    1
#define UIP_CONF_UDP_CHECKSUMS          1
#define UIP_CONF_MAX_CONNECTIONS	10
#define UIP_CONF_MAX_LISTENPORTS	10
#define UIP_CONF_UDP_CONNS              5

// �Ƿ�ʹ��·�ɹ���
#define UIP_CONF_ROUTER                 1
#define UIP_CONF_IPV6_RPL               1

#if UIP_CONF_IPV6_RPL
#define UIP_CONF_ROUTER                 1
#define UIP_CONF_ND6_SEND_RA		    0
#define UIP_CONF_ND6_REACHABLE_TIME     600000
#define UIP_CONF_ND6_RETRANS_TIMER      10000

#undef UIP_CONF_UDP_CONNS
#define UIP_CONF_UDP_CONNS       12
#undef UIP_CONF_FWCACHE_SIZE
#define UIP_CONF_FWCACHE_SIZE    30
#define UIP_CONF_BROADCAST       1
#define UIP_ARCH_IPCHKSUM        1
#define UIP_CONF_PINGADDRCONF    0
#define UIP_CONF_LOGGING         0
#endif

// A trick to resolve a compilation error with IAR.
#if !UIP_CONF_ROUTER
#define UIP_CONF_DS6_AADDR_NBU          1
#endif

#define UIP_CONF_IP_FORWARD             0
#define RPL_CONF_STATS                  0
#define RPL_CONF_MAX_DAG_ENTRIES        1
#define RPL_CONF_OF                     rpl_mrhof //rpl_of0 //rpl_mrhof
#define RPL_CONF_MAX_PARENTS_PER_DAG    4
#define RPL_CONF_MAX_INSTANCES          1
#define RPL_CONF_MAX_DAG_PER_INSTANCE   1



//#define UIP_CONF_ND6_REACHABLE_TIME     (CLOCK_CONF_SECOND * 100)
//#define UIP_CONF_ND6_RETRANS_TIMER      (CLOCK_CONF_SECOND * 5)
// Handle n Neighbors
#define UIP_CONF_DS6_NBR_NBU            30
// Handle n Routes
#define UIP_CONF_DS6_ROUTE_NBU          30
#define UIP_CONF_ND6_MAX_PREFIXES	2
#define UIP_CONF_ND6_MAX_NEIGHBORS	2
#define UIP_CONF_ND6_MAX_DEFROUTERS	1



// uIP����
#define UIP_CONF_BUFFER_SIZE            240
// ʹ�ܱ�ѡ�����������ڴ�ʹ��������ΪThis is a very costly feature
// as it increases the RAM usage by approximately UIP_ND6_MAX_NEIGHBORS * UIP_LINK_MTU bytes.
#define UIP_CONF_IPV6_QUEUE_PKT         0
#define UIP_CONF_IPV6_CHECKS            1
#define UIP_CONF_IPV6_REASSEMBLY        0


// 6lowpan����
//#define SICSLOWPAN_CONF_COMPRESSION_IPV6        0
//#define SICSLOWPAN_CONF_COMPRESSION_HC1         1
//#define SICSLOWPAN_CONF_COMPRESSION_HC06        2
#define SICSLOWPAN_CONF_COMPRESSION     SICSLOWPAN_COMPRESSION_HC06
#define SICSLOWPAN_CONF_FRAG                    1   // About 2KB of CODE if 1
#define SICSLOWPAN_CONF_MAXAGE                  8

// Define our IPv6 prefixes/contexts here
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS    2
#define SICSLOWPAN_CONF_ADDR_CONTEXT_0 { \
  addr_contexts[0].prefix[0] = 0x30; \
  addr_contexts[0].prefix[1] = 0xaa; \
}

#define MAC_CONF_CHANNEL_CHECK_RATE          8
#define QUEUEBUF_CONF_NUM                    8
#define CSMA_CONF_MAX_NEIGHBOR_QUEUES        4

#else   // ��֮��û�ж���UIP_CONF_IPV6����Network setup for non-IPv6 (rime)
#define UIP_CONF_IP_FORWARD                  1
#define UIP_CONF_BUFFER_SIZE               108
#define RIME_CONF_NO_POLITE_ANNOUCEMENTS     0
#define QUEUEBUF_CONF_NUM                    8
#endif  // NETSTACK_CONF_WITH_IPV6


#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
