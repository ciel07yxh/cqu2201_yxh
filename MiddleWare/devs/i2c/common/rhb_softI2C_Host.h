/****************************************Copyright (c)****************************************************
**
**
**                                 http://www.ourtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_softI2C_Host.h
** Last modified Date:  2010-8-05
** Last Version:        v1.0
** Description:         ���ģ��I2C������ʵ����������ü����������ļ�
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo
** Created date:        2010-8-05
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
#ifndef  __RHB_SOFTI2C_HOST_H__
#define  __RHB_SOFTI2C_HOST_H__

#ifdef __cplusplus
extern "C" {
#endif

  
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
/*********************************************************************************************************
  ���ģ��I2Cʵ�����ú���
*********************************************************************************************************/
#define rhb_I2C_Delay        10   //  ������ʱ������I2C���ߵ��ٶȣ�Ϊ0ʱ��ʹ����ʱ����������0ʱ��Ҫ�ṩһ��
                                  //  delay(a)����ʱ����

#define rhb_SCL_H()          (HWREG(GPIOC_BASE + GPIO_O_BSRR) = 0x4000)     //  ��ʱ����SCL�ø�
#define rhb_SCL_L()          (HWREG(GPIOC_BASE + GPIO_O_BRR) = 0x4000)      //  ��ʱ����SCL�õ�

#define rhb_SDA_H()          (HWREG(GPIOC_BASE + GPIO_O_BSRR) = 0x8000)     //  ��������SDA�ø�
#define rhb_SDA_L()          (HWREG(GPIOC_BASE + GPIO_O_BRR) = 0x8000)      //  ��������SDA�õ�

#define rhb_I2C_READ      0x01
#define rhb_I2C_WRITE     0x00

//  ����ȡ����ʱ��keyȡֵֻ��ΪI2C_24c16_Normal
#define  rhb_I2C_Normal         0x00    //  ��������
#define  rhb_I2C_AllSet         0x01    //  ��ָ����ַ��������Ϊ0xFF
#define  rhb_I2C_AllReset       0x02    //  ��ָ����ַ��������Ϊ0x00

//  ���û��tBoolean���ͣ���Ҫ�û����壬������߼����ͣ�����Ϊ�߼����ͣ���������Ϊunsigned char�����£�
//  typedef unsigned char tBoolean;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

/*********************************************************************************************************
  ʵ���ⲿ��������
*********************************************************************************************************/
extern void rhb_I2C_Start(void);
extern void rhb_I2C_Stop(void);
extern void rhb_I2C_Ack(void);
extern void rhb_I2C_NoAck(void);
extern tBoolean rhb_I2C_WaitAck(void);
extern void rhb_I2C_SendByte(unsigned char ucByte);
extern unsigned char rhb_I2C_RecvByte(void);
extern void rhb_i2c_read(unsigned char I2CAddr, unsigned long ulAddr, 
                         unsigned char addrLen, void *buf, unsigned long *len);
extern void rhb_i2c_write(unsigned char I2CAddr, unsigned long ulAddr, 
                          unsigned char addrLen, void *buf, unsigned long *len);
extern void rhb_i2c_set(unsigned char I2CAddr, unsigned long ulAddr, 
                        unsigned char addrLen, void *buf, unsigned long *len);
extern void rhb_i2c_reset(unsigned char I2CAddr, unsigned long ulAddr, 
                          unsigned char addrLen, void *buf, unsigned long *len);
#ifdef __cplusplus
    }
#endif      //  END OF __cplusplus

#endif      // END OF __RHB_SOFTI2C_M_H__

/*********************************************************************************************************
** End of File
*********************************************************************************************************/