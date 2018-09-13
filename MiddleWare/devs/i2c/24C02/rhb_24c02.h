/****************************************Copyright (c)****************************************************
**
**                                     
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_24c02.h
** Last modified Date:  2010-11-9
** Last Version:        v1.0
** Description:         STM32 I2C�м��
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2010-11-9
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
#ifndef  __RHB_24C02_H__
#define  __RHB_24C02_H__

#include "dev/I2C/common/rhb_softI2C_Host.h"

/*********************************************************************************************************
  24C02����غ궨��
*********************************************************************************************************/
#define  I2C_24C02_ADDR         0xA0    //  �����������ϵĵ�ַ
#define  DEVICE_ADDR_MAX        0xFF    //  �����ڲ��洢��Ԫ����ַ,������2Kλ����256���ֽڣ�����ַΪ0xFF
#define  I2C_24C02_PAGE_SEZE    8       //  ҳ��С

//  ����ȡ����ʱ��keyȡֵֻ��ΪI2C_24C02_Normal
#define  I2C_24C02_Normal   rhb_I2C_Normal      //  ��������24C02
#define  I2C_24C02_AllSet   rhb_I2C_AllSet      //  ��ָ����ַ��������Ϊ0xFF
#define  I2C_24C02_AllReset rhb_I2C_AllReset    //  ��ָ����ַ��������Ϊ0x00

/*********************************************************************************************************
** �������ڵĽṹ�嶨��
*********************************************************************************************************/
typedef struct
{
    void (*i2c_operate)(unsigned char I2CAddr, unsigned long ulAddr, 
                   unsigned char addrLen, void *buf,unsigned long *len);
    OS_EVENT        *sem_I2C;                         // �����ź�����������̲߳�������
} rhb_24c02_info;

/*********************************************************************************************************
** �ⲿ����������
*********************************************************************************************************/
extern rhb_24c02_info __tGrhb_24c02;
extern rhb_ErrNo rhb_24c02_init(rhb_io_handle handle);
extern rhb_ErrNo rhb_24c02_fread(rhb_io_handle handle, unsigned long ulAddr, 
                                 unsigned char key, void *buf, unsigned long *len);
extern rhb_ErrNo rhb_24c02_fwrite(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len);
extern rhb_ErrNo rhb_24c02_IsBusy(rhb_io_handle handle);
extern rhb_ErrNo rhb_24c02_setConfig(rhb_io_handle handle, void *data, unsigned long *len);
extern rhb_ErrNo rhb_24c02_getConfig(rhb_io_handle handle, void *data, unsigned long *len);

#endif // endif of __STM32_SERIAL_H__

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
