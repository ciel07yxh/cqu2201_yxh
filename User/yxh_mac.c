/****************************************Copyright (c)****************************************************
**                                
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           P2P.c
** Last modified Date:  2018-04-11
** Last Version:        v1.0
** Description:         
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Xaiohan Y
** Created date:        2012-06-21
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

yxh_frame802154_t rec_frame;

uint8_t payload_to_send[2]={1,2};
uint16_t frame_sequence = 0;
uint16_t recframe_count = 1;
uint16_t sentframe_count = 1;
uint16_t bufframe_count = 1;
uint8_t phy_seq=0;
//uint8_t synch_node_flag  = 0x01;
uint8_t sendflag = 0;

time_para synch={
  0,
  0,
  0,
  0,
  timeoffset_calc,
  get_synch_time
};

#define MAX_QUEUED_PACKETS 200
MEMB(frame_size, yxh_frame802154_t, MAX_QUEUED_PACKETS);
MEMB(packet_size, struct packet_list, MAX_QUEUED_PACKETS);
MEMB(playload_size, yxh_playload_t, MAX_QUEUED_PACKETS);
LIST(packet_list);

/*********************************************************************************************************
  TDMA configuration 
*********************************************************************************************************/
#define PERIOD_LENGTH   RTIMER_SECOND

#define NR_SLOTS        4
#define SLOT_LENGTH     (PERIOD_LENGTH / NR_SLOTS)
//#define GUARD_PERIOD    (PERIOD_LENGTH / 20)
#define MY_SLOT         (get_moteid() % NR_SLOTS)





/*********************************************************************************************************
** Function name:       get_synch_time
** Descriptions:        获取同步时间
** input parameters:    0
** output parameters:   无
** Returned value:      0
** Created by:          张校源
** Created Date:        2018-04-07
*********************************************************************************************************/

rtimer_clock_t get_synch_time(time_para *timepara)
{
  return  RTIMER_NOW() - timepara->time_offset;
} 

/*********************************************************************************************************
** Function name:       get_synch_time
** Descriptions:        计算时间偏置
** input parameters:    0
** output parameters:   无
** Returned value:      0
** Created by:          张校源
** Created Date:        2018-04-07
*********************************************************************************************************/



void timeoffset_calc(time_para *timepara,uint32_t time)
{
  timepara->time_offset = timepara->time_stamp -time;
  //对周期取与
  timepara->time_offset_period_align=timepara->time_offset%PEROID_LENGTH;
  //若果为负数
  if(timepara->time_offset_period_align<0)
      timepara->time_offset_period_align+=PEROID_LENGTH;
} 

/*********************************************************************************************************
** Function name:       frame_para_init
** Descriptions:        Init the parameters of the frame
** input parameters:    none
** output parameters:   none
** Returned value:      0
** Created by:          Xiaohan Y
** Created Date:        2018-04-11
*********************************************************************************************************/
time_para *timepara = & synch; 
void frame_para_init(yxh_frame802154_t *p,yxh_playload_t *app_data,uint16_t dest_addr)
{
    //init the fcf
    p->fcf.frame_type=0x01;
    p->fcf.security_enabled=0x00;
    p->fcf.frame_pending=0x00;
    p->fcf.ack_required=0x01;
    //p2p_frame.panid_compression=;                                      //this is to be determined in field_flen()
    p->fcf.dest_addr_mode=FRAME802154_SHORTADDRMODE;                      //short address
    p->fcf.frame_version=0x01;
    p->fcf.src_addr_mode=FRAME802154_SHORTADDRMODE;                        //short address
    //init the seq
    p->seq=phy_seq;
    //init the PAN id

    p->src_pid=get_cluster_name(get_moteid());
    //init the Adress

    p->src_addr[0]=get_moteid();
    p->src_addr[1]=0x00;
    
    
    p->payload=app_data->buf;
    p->payload_len=app_data->payload_len;

    p->dest_pid=get_cluster_name(dest_addr);
    p->dest_addr[0]=dest_addr;  
    p->dest_addr[1]=(dest_addr & 0xFF00)>>8;
    
    if(dest_addr == 0xFFFF ) 
    {
      p->dest_pid = 0xFFFF;
      p->dest_addr[0] = 0xFF;
      p->dest_addr[1] = 0xFF;
      p->fcf.ack_required=0x00;
    }
     p->time_stamp = timepara->get_synch_time(timepara);
     phy_seq++;
}

/*********************************************************************************************************
** Function name:       yxh_frame_send
** Descriptions:        send the frame with csma/ca
** input parameters:    null
** output parameters:   none
** Returned value:      0
** Created by:          Xiaohan Y
** Created Date:        2018-04-11
*********************************************************************************************************/
void yxh_frame_send(yxh_playload_t *playload,uint16_t dest_addr)
{
  //frame_to_send是为了给指针yxh_frame分配地址
  yxh_frame802154_t frame_to_send;
  yxh_frame802154_t *yxh_frame = &frame_to_send;   
  
  //initialize the p2p frame parameters
  frame_para_init(yxh_frame,playload,dest_addr);
    //帧放缓存
  qx_sendBuf(yxh_frame);
}


/*********************************************************************************************************
** Function name:       yxh_frame_parse
** Descriptions:        Parses an input frame
** input parameters:    uint8_t *data, int len, yxh_frame802154_t *pf
** output parameters:   
** Returned value:      0
** Created by:          Xiaohan Y
** Created Date:        2018-04-18
*********************************************************************************************************/
void yxh_frame802154_parse(void)
{ 
  uint8_t *p; 
  yxh_frame802154_fcf_t fcf;
  int c;
  
  uint8_t *data = packetbuf_dataptr();
  int len = (int)packetbuf_datalen();
  yxh_frame802154_t *pf = &rec_frame;
   
  if(len <= 3) {
    return ;
  }
  
  p = data;

  /* decode the FCF */
  fcf.frame_type = p[0] & 7;
  fcf.security_enabled = (p[0] >> 3) & 1;
  fcf.frame_pending = (p[0] >> 4) & 1;
  fcf.ack_required = (p[0] >> 5) & 1;
  fcf.panid_compression = (p[0] >> 6) & 1;

  fcf.dest_addr_mode = (p[1] >> 2) & 3;
  fcf.frame_version = (p[1] >> 4) & 3;
  fcf.src_addr_mode = (p[1] >> 6) & 3;

  /* copy fcf and seqNum */
  memcpy(&pf->fcf, &fcf, sizeof(frame802154_fcf_t));
  pf->seq = p[2];
  p += 3;                             /* Skip first three bytes */

  /* Destination address, if any */
  if(fcf.dest_addr_mode) 
  {
    /* Destination PAN */
    pf->dest_pid = p[0] + (p[1] << 8);
    p += 2;
    
    if(fcf.dest_addr_mode == FRAME802154_SHORTADDRMODE) 
    {
      linkaddr_copy((linkaddr_t *)&(pf->dest_addr), &linkaddr_null);
      pf->dest_addr[0] = p[0];
      pf->dest_addr[1] = p[1];
      p += 2;
    }
    else if(fcf.dest_addr_mode == FRAME802154_LONGADDRMODE) 
    {
      for(c = 0; c < 8; c++) 
      {
        pf->dest_addr[c] = p[c];
      }
      p += 8;
    }
  } 
  else 
  {
    linkaddr_copy((linkaddr_t *)&(pf->dest_addr), &linkaddr_null);
    pf->dest_pid = 0;
  }
  
  /* Source address, if any */
  if(fcf.src_addr_mode) {
    /* Source PAN */
    if(!fcf.panid_compression) {
      pf->src_pid = p[0] + (p[1] << 8);
      p += 2;
    } else {
      pf->src_pid = pf->dest_pid;
    }

    /* Source address */
    if(fcf.src_addr_mode == FRAME802154_SHORTADDRMODE) {
      linkaddr_copy((linkaddr_t *)&(pf->src_addr), &linkaddr_null);
      pf->src_addr[0] = p[0];
      pf->src_addr[1] = p[1];
      p += 2;
    } else if(fcf.src_addr_mode == FRAME802154_LONGADDRMODE) {
      for(c = 0; c < 8; c++) {
        pf->src_addr[c] = p[c];
      }
      p += 8;
    }
  } else {
    linkaddr_copy((linkaddr_t *)&(pf->src_addr), &linkaddr_null);
    pf->src_pid = 0;
  }
    
    pf->time_stamp = p[0] | p[1]<<8 | p[2]<<16 | p[3]<<24 ;
    p += 4;
    
    
    /* header length */
    c = p - data;          
    /* payload length */
    pf->payload_len = (len - c);
    /* payload */
    pf->payload = p;
    
    //判断接收节点类型来处理帧
    if(get_moteid() != TIME_SYNCH_NODE )
    {
      deal_recframe(pf);
    }
    else
    {
      //同步节点只发送同步帧，接收到包后什么都不做    
      return;  
    } 
  
    //打印接收到的帧
    PRINTF("The received frame is: ");
    for(uint8_t a=0;a<len;a++)
    {
      PRINTF("%x ",data[a]);
    }
    PRINTF("\r\n");  

  }
  

/*********************************************************************************************************
** Function name:       deal_recframe
** Descriptions:        对接收的帧做处理
** input parameters:    
** output parameters:   无
** Returned value:      0
** Created by:          袁小涵
** Created Date:        2018-05-24
*********************************************************************************************************/
void deal_recframe(yxh_frame802154_t *rec)
{
  if(rec->payload_len == sizeof(app_led_t))
  {
    set_mote_led_status((app_led_t *)rec->payload);
  }
  PRINTF("payload_len %d\r\n",rec->payload_len);
}


/*********************************************************************************************************
** Function name:       
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      0
** Created by:          
** Created Date:        2018-05-11
*********************************************************************************************************/
uint8_t startSend=0;
struct ctimer ctSendAir;

//放入缓存
void qx_sendBuf(yxh_frame802154_t * frame){
  
  if(list_length(packet_list)>=MAX_QUEUED_PACKETS){
  //空间已满
    return;
  }
  //缓存池赋值
  struct packet_list* q;
  q = memb_alloc(&packet_size);
  q->data=memb_alloc(&frame_size);
  q->playload=memb_alloc(&playload_size);
  
  memcpy(q->data,frame,sizeof(yxh_frame802154_t));
  
  memcpy(q->playload,frame->payload,frame->payload_len);
   
  q->data->payload = q->playload->buf;
      
  //添加进缓存池 最多51
  list_add(packet_list, q);
  //PRINTF("list已用空间为%d\r\n",list_length(packet_list));
  //PRINTF("No.%d frame is successfully put in the buffer! \r\n",bufframe_count++);
  
  //开始扫描缓存池
  if(startSend==0){
    startSend=1;
    ctimer_set(&ctSendAir,CLOCK_SECOND/10,sendAir, NULL); 
  }
}


/*********************************************************************************************************
** Function name:       sendAir
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      0
** Created by:          
** Created Date:        2018-05-11
*********************************************************************************************************/
struct ctimer ctSendAir;

void sendAir(void *p){
  uint8_t buf[100];
  if(!list_length(packet_list))
  {
    ctimer_set(&ctSendAir,10,sendAir, NULL); 
    return;
  }
  //检查缓存池
    struct packet_list *q = list_head(packet_list);
    if(q!=NULL){
      //修改时间戳，然后 装帧且发送
      q->data->time_stamp = timepara->get_synch_time(timepara);
      int sendlength = yxh_frame802154_create(q->data,buf);    
      int state = NETSTACK_RADIO.send(buf,sendlength); 
      
      //发送内容

      //n次发送未接收到ACK则发送下一帧
      if(state != RADIO_TX_OK)
          sendflag++;      
      
      if(sendflag >0)
      {
        list_remove(packet_list, q);
        
        memb_free(&playload_size,q->playload);
        memb_free(&frame_size,q->data);
        memb_free(&packet_size, q);
        
        //uart_printf("Send failed, next to send!\r\n");
        sendflag=0;
      }

      //处理缓存池
      if(state == RADIO_TX_OK){    
        list_remove(packet_list, q);
        
        memb_free(&playload_size,q->playload);
        memb_free(&frame_size,q->data);
        memb_free(&packet_size, q);
        //uart_printf("list已用空间为%d\r\n",list_length(packet_list));
        //uart_printf("No.%d frame is successfully sent! \r\n",sentframe_count++);
        sendflag = 0;
      }
    }  
  ctimer_set(&ctSendAir,0,sendAir, NULL);
  //sendAir(NULL);
  /*循环扫描缓存池
    if(sendflag)
    
    else
    ctimer_set(&ctSendAir,1,sendAir, NULL);
  */
}

uint16_t is_buffer_clear(void)
{
  return (list_length(packet_list) == 0);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/