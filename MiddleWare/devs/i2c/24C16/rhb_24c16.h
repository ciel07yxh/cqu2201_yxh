/****************************************Copyright (c)****************************************************
**
**                                     
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_24c16.h
** Last modified Date:  2011-1-11
** Last Version:        v1.0
** Description:         ����24C16ʵ�ֺ���
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2011-1-11
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
#ifndef  __RHB_24C16_H__
#define  __RHB_24C16_H__

#include "dev/I2C/common/rhb_softI2C_Host.h"
#include "dev/I2C/24C02/rhb_24c02.h"

/*********************************************************************************************************
  24c16����غ궨��
*********************************************************************************************************/
#define  rhb_I2C_24C16_ADDR         0xA0    //  �����������ϵĵ�ַ
#define  rhb_24C16_DEVICE_ADDR_MAX  0x7FF   //  �����ڲ��洢��Ԫ����ַ,������16Kλ����2K���ֽڣ�����ַΪ0x7FF
#define  rhb_I2C_24C16_PAGE_SEZE    16      //  ҳ��С

//  ����ȡ����ʱ��keyȡֵֻ��ΪI2C_24c16_Normal
#define  I2C_24C16_Normal   rhb_I2C_Normal      //  ��������24c16
#define  I2C_24C16_AllSet   rhb_I2C_AllSet      //  ��ָ����ַ��������Ϊ0xFF
#define  I2C_24C16_AllReset rhb_I2C_AllReset    //  ��ָ����ַ��������Ϊ0x00

/*********************************************************************************************************
** �������ڵĽṹ�嶨��
*********************************************************************************************************/
typedef struct
{
    void (*i2c_operate)(unsigned char I2CAddr, unsigned long ulAddr, 
                   unsigned char addrLen, void *buf,unsigned long *len);
    OS_EVENT        *sem_I2C;                         // �����ź�����������̲߳�������
} rhb_24c16_info;

/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern rhb_24c16_info __tGrhb_24c16;
extern rhb_ErrNo rhb_24c16_init(rhb_io_handle handle);
extern rhb_ErrNo rhb_24c16_fread(rhb_io_handle handle, unsigned long ulAddr, 
                                 unsigned char key, void *buf, unsigned long *len);
extern rhb_ErrNo rhb_24c16_fwrite(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len);
extern rhb_ErrNo rhb_24c16_IsBusy(rhb_io_handle handle);
extern rhb_ErrNo rhb_24c16_setConfig(rhb_io_handle handle, void *data, unsigned long *len);
extern rhb_ErrNo rhb_24c16_getConfig(rhb_io_handle handle, void *data, unsigned long *len);

#endif // endif of __RHB_24C16_H__

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
