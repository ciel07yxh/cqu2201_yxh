/****************************************Copyright (c)****************************************************
**                               
**                                                       
**  
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               P2P.h
** Last modified Date:      2012-06-21
** Last Version:            v1.0
** Description:             
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              Xiaohan Y
** Created date:            2018-04-10
** Version:                 v1.0
** Descriptions:            The original version 
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Description:             
**
*********************************************************************************************************/
#ifndef __P2P_H__ 
#define __P2P_H__ 

#include "Contiki\core\dev\radio.h"
#include "yxh_framer.h"
/*********************************************************************************************************
**  Define global variaty
*********************************************************************************************************/


/**
 *    @brief  The IEEE 802.15.4 frame has a number of constant/fixed fields that
 *            can be counted to make frame construction and max payload
 *            calculations easier.
 *
 *            These include:
 *            1. FCF                  - 2 bytes       - Fixed
 *            2. Sequence number      - 1 byte        - Fixed
 *            3. Addressing fields    - 4 - 20 bytes  - Variable
 *            4. Aux security header  - 0 - 14 bytes  - Variable
 *            5. CRC                  - 2 bytes       - Fixed
*/



typedef struct time_para{
        uint8_t  IsSyched;
        uint32_t time_stamp;
        int32_t  time_offset;
        int32_t  time_offset_period_align;         //用于时间同步周期对齐
        void (*timeoffset)(struct time_para *timepara,uint32_t time);
        rtimer_clock_t (*get_synch_time)(struct time_para *timepara);
} time_para;


struct packet_list{
  struct packet_list * next;
  yxh_frame802154_t   * data;
  yxh_playload_t     * playload;
};




void frame_para_init(yxh_frame802154_t *p,yxh_playload_t *app_data,uint16_t dest_addr);//init the parameters used in creating the frame and the operation machianism
//void peration_init();        //init the parameters used in the operation machianism

void yxh_frame_send(yxh_playload_t *app_data,uint16_t dest_addr);
void yxh_send_tdma(void *type);
void interferencing(void); 


rtimer_clock_t get_synch_time(time_para *timepara);
void timeoffset_calc(time_para *timepara,uint32_t time);
void time_synch_gps(void *ptr);

void qx_sendBuf(yxh_frame802154_t * frame);
void sendAir(void *p);
void deal_recframe(yxh_frame802154_t * rec);
uint16_t is_buffer_clear(void);
/*********************************************************************************************************
  外部函数及变量定义
*********************************************************************************************************/
extern time_para synch;


#endif /* __CONTIKI_CONF_H__ */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/










