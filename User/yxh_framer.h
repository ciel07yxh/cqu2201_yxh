/****************************************Copyright (c)****************************************************
**                               
**                                                       
**  
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               yxh_framer.h
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
#ifndef __YXH_FRAMER_H__
#define __YXH_FRAMER_H__ 

#include "Contiki\core\dev\radio.h"

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
typedef struct {
  uint8_t frame_type;        /**< 3 bit. Frame type field, see 802.15.4 */
  uint8_t security_enabled;  /**< 1 bit. True if security is used in this frame */
  uint8_t frame_pending;     /**< 1 bit. True if sender has more data to send */
  uint8_t ack_required;      /**< 1 bit. Is an ack frame required? */
  uint8_t panid_compression; /**< 1 bit. Is this a compressed header? */
  /*   uint8_t reserved; */  /**< 3 bit. Unused bits */
  uint8_t dest_addr_mode;    /**< 2 bit. Destination address mode, see 802.15.4 */
  uint8_t frame_version;     /**< 2 bit. 802.15.4 frame version */
  uint8_t src_addr_mode;     /**< 2 bit. Source address mode, see 802.15.4 */
}yxh_frame802154_fcf_t;

typedef struct {
  yxh_frame802154_fcf_t fcf;          /**< Frame control field  */
  uint8_t seq;                    /**< Sequence number */
  uint16_t dest_pid;              /**< Destination PAN ID */
  uint8_t dest_addr[8];           /**< Destination address */
  uint16_t src_pid;               /**< Source PAN ID */
  uint8_t src_addr[8];            /**< Source address */
  //frame802154_aux_hdr_t aux_hdr;  /**< Aux security header */             //  No Aux security header
  uint8_t *payload;               /**< Pointer to 802.15.4 payload */
  uint32_t time_stamp;
  int payload_len;                /**< Length of payload field */         //  ??
}yxh_frame802154_t;

typedef struct {
  uint8_t buf[30];
  int payload_len;
}yxh_playload_t;

/**
 *  \brief Structure that contains the lengths of the various addressing and security fields
 *  in the 802.15.4 header.  This structure is used in \ref frame802154_create()
 */
typedef struct {
  uint8_t dest_pid_len;    /**<  Length (in bytes) of destination PAN ID field */
  uint8_t dest_addr_len;   /**<  Length (in bytes) of destination address field */
  uint8_t src_pid_len;     /**<  Length (in bytes) of source PAN ID field */
  uint8_t src_addr_len;    /**<  Length (in bytes) of source address field */
  //uint8_t aux_sec_len;     /**<  Length (in bytes) of aux security header field */
} field_length_t;


int yxh_frame802154_create(yxh_frame802154_t *p, uint8_t *buf);
void yxh_frame802154_parse(void);


#endif /* __CONTIKI_CONF_H__ */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/