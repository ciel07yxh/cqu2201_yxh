/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           globalmacro.h
** Last modified Date:  2018-04-06
** Last Version:        v1.0
** Description:         ȫ�ֺ궨��
**
**--------------------------------------------------------------------------------------------------------
** Created By:          ԬС��
** Created date:        2018-06-03
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
/*
//�����Ƿ������Լ�������߳̽ӹ������
#define RECIVE_SELF                     1
//����ʱ��ͬ������
#define TIME_STAMP                      1
//��ӡ�������ܵ�����
#define PRINT_FRAME                     0
//ʱ��ͬ���ڵ�
#define TIME_SYNCH_NODE                 15
//ͬ���ڵ㷢��ʱ��ͬ��֡����
#define TIME_SYNCH_TIMES                10
//֡�ӳٲ��Դ�ӡ
#define PACKET_DELAY                    1
//BSM�����ƶ�֡ �뷢�ʹ���
#define BSM_FREAM_TEST                  1
#define BSM_FRAME_TEST_TIMES            1000
//������ر� ����ģʽ ����PADID����
#define ENABLE_PANID_FILTER             1
//ͬ��֮�����ʱ�俪ʼ���� BSM
#define BSM_START_TIME                  5
#define PACKET_INFO_STATISTICS          1
//�������֮��ʱ������ʱ��
#define PACKET_INTO_REPORT_TIME         50
//TDMA ��ʹ�ܵ�ʱ��ʹ��csma_ca ʹ��ʱ��ر�csma_ca
#define TDMA_BSM_ENABLE                 1

#define START_PDR_INFO_TIME             5          
*/


//��ַģʽ
#define FRAME802154_SHORTADDRMODE   (0x02)           
#define FRAME802154_LONGADDRMODE    (0x03)
//ѡ��ڵ�
//#define DEST_ADDR    (0x18)                //choose the destination address  no.02
#define SRC_ADDR        31           //choose the destination address   no.01
#define TIME_SYNCH_NODE               35
//#define INTERFERENCE_NODE               0x1a
//ʱ��ͬ��֡��
#define TIME_SYNCH_TIMES           30    
//֡����
#define FRAME_TYPE_TIME_SYNCH   0x01
#define FRAME_TYPE_P2P          0x02
#define FRAME_TYPE_INTERF       0x03
//�����Ƿ������Լ�������߳̽ӹ������
#define YXH_RECV    1
//�Ƿ����֡�������
#define BUFFER    0
//�����ŵ���ʽѡ��
#define SEND_TDMA         0
#define SEND_CSMACA      1

#define BSM_FRE_HZ      10                              //BSM 10Hz
#define PEROID_LENGTH   (RTIMER_SECOND/BSM_FRE_HZ)      //BSM ����ʱ��     

#define SET_MAX_FRAME_RETRIES   0x00


