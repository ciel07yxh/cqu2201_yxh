/****************************************Copyright (c)****************************************************
**
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_CRC.c
** Last modified Date:  2010-8-3
** Last Version:        v1.0
** Description:         ����CRCУ���㷨��������ͷ�ļ�
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2010-8-8
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
#include "rhb_checksum.h"

/*********************************************************************************************************
** Function name:       rhb_checksum8
** Descriptions:        checksum8��У��
** input parameters:    pucMsg��ָ��������ʼ��ַ
**                      ulLen�� ָ�����ݳ���
**                      u8Starter: �������ĳ�ֵ����һ�μ������е�����ʱ������Ϊ0
** output parameters:   NONE
** Returned value:      checksum8У����
*********************************************************************************************************/
uint8 rhb_checksum8(uint8 *pu8Msg, uint32 u32Len, uint8 u8Starter)
{
    uint32 i;
    
    for(i=0; i<u32Len; i++)
    {
        u8Starter += *pu8Msg++;
    }

    return u8Starter;
}

/*********************************************************************************************************
** Function name:       rhb_checksum16
** Descriptions:        checksum16��У��
** input parameters:    pucMsg��ָ��������ʼ��ַ
**                      ulLen�� ָ�����ݳ���
**                      u16Starter: �������ĳ�ֵ����һ�μ������е�����ʱ������Ϊ0
** output parameters:   NONE
** Returned value:      checksum8У����
*********************************************************************************************************/
uint16 rhb_checksum16(uint8 *pu8Msg, uint32 u32Len, uint16 u16Starter)
{
    uint32 i;
    
    for(i=0; i<u32Len; i++)
    {
        u16Starter += *pu8Msg++;
    }

    return u16Starter;
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/