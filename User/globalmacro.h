/****************************************Copyright (c)****************************************************
**                                蓝精灵6lowpan无线开发平台
**                                  一切为开源应用而作
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           globalmacro.h
** Last modified Date:  2018-04-06
** Last Version:        v1.0
** Description:         全局宏定义
**
**--------------------------------------------------------------------------------------------------------
** Created By:          袁小涵
** Created date:        2018-06-03
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
/*
//定义是否启用自己定义的线程接管物理层
#define RECIVE_SELF                     1
//开启时间同步进程
#define TIME_STAMP                      1
//打印物理层接受的数据
#define PRINT_FRAME                     0
//时间同步节点
#define TIME_SYNCH_NODE                 15
//同步节点发送时间同步帧次数
#define TIME_SYNCH_TIMES                10
//帧延迟测试打印
#define PACKET_DELAY                    1
//BSM发送制定帧 与发送次数
#define BSM_FREAM_TEST                  1
#define BSM_FRAME_TEST_TIMES            1000
//开启或关闭 混杂模式 开启PADID过滤
#define ENABLE_PANID_FILTER             1
//同步之后多少时间开始发送 BSM
#define BSM_START_TIME                  5
#define PACKET_INFO_STATISTICS          1
//发送完成之后定时开启的时间
#define PACKET_INTO_REPORT_TIME         50
//TDMA 不使能的时候使用csma_ca 使能时候关闭csma_ca
#define TDMA_BSM_ENABLE                 1

#define START_PDR_INFO_TIME             5          
*/


//地址模式
#define FRAME802154_SHORTADDRMODE   (0x02)           
#define FRAME802154_LONGADDRMODE    (0x03)
//选择节点
//#define DEST_ADDR    (0x18)                //choose the destination address  no.02
#define SRC_ADDR        31           //choose the destination address   no.01
#define TIME_SYNCH_NODE               35
//#define INTERFERENCE_NODE               0x1a
//时间同步帧数
#define TIME_SYNCH_TIMES           30    
//帧类型
#define FRAME_TYPE_TIME_SYNCH   0x01
#define FRAME_TYPE_P2P          0x02
#define FRAME_TYPE_INTERF       0x03
//定义是否启用自己定义的线程接管物理层
#define YXH_RECV    1
//是否采用帧缓存机制
#define BUFFER    0
//接入信道方式选择
#define SEND_TDMA         0
#define SEND_CSMACA      1

#define BSM_FRE_HZ      10                              //BSM 10Hz
#define PEROID_LENGTH   (RTIMER_SECOND/BSM_FRE_HZ)      //BSM 周期时间     

#define SET_MAX_FRAME_RETRIES   0x00


