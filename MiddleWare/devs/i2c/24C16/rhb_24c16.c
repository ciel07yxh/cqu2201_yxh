/****************************************Copyright (c)****************************************************
**
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_24c16.c
** Last modified Date:  2010-11-9
** Last Version:        v1.0
** Description:         ����24C16ʵ�ֺ���
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
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_usart.h"
#include "hw_ints.h"
#include "hw_dma.h"
#include "dma.h"
#include "usart.h"
#include "interrupt.h"
#include "string.h"

#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h>

#include "io/rhb_io.h"

#include "dev/I2C/24c16/rhb_24c16.h"


rhb_24c16_info __tGrhb_24c16 = {NULL, NULL};
/*********************************************************************************************************
** Function name:       rhb_24c16_init
** Descriptions:        ��ʼ��I2C�豸����ϵͳ�ں˵���
** input parameters:    handle: ��������������
**                      NONE
** output parameters:   NONE
** Returned value:      1:��ʼ���豸�ɹ� 
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_init(rhb_io_handle handle)
{
   rhb_24c16_info *i2c_handle = handle;
   
   i2c_handle->sem_I2C = OSSemCreate(1);
   i2c_handle->i2c_operate = rhb_i2c_read;
   
   return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c16_fread
** Descriptions:        ��24c16ָ���洢��Ԫ��ʼ��ȡָ��ֱ�ӵ�����
** input parameters:    handle:   ��������������
**                      ulAddr��  24c16��ȡ��ʼ��ַ
**                      key��     ��ȡ���ԣ�����ֻ��ΪI2C_24c16_Normal
**                      buf:      ��ȡ���ݴ�ŵ�ַ
**                      len:      ��ȡ���ݳ���ָ��
** output parameters:   NONE
** Returned value:      ������ȷ������1����֮������0
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_fread(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len) 
{
    INT8U err;
    unsigned char ucI2cAddr;
    unsigned long ulCount = *len;
    unsigned long ulNumOnce = 0;
    unsigned char *data = buf;
    rhb_24c16_info *i2c_handle = handle;
    
    if((buf == NULL)|| ((*len) <= 0) || (len==NULL))
      return 0;
    
    if(key != I2C_24C16_Normal)
    {
        *len = 0;
        return 0;
    } else {
        i2c_handle->i2c_operate = rhb_i2c_read;
    }
    
    OSSemPend(i2c_handle->sem_I2C,0,&err);
    if(err == OS_ERR_NONE)
    {
        if(ulAddr > rhb_24C16_DEVICE_ADDR_MAX) {
            *len = 0;
            OSSemPost(i2c_handle->sem_I2C);
            return 0;                                               //   ��ȡ��ַ���������洢��Ԫ����ַ������0
        }
        if((ulAddr + ulCount - 1) > rhb_24C16_DEVICE_ADDR_MAX) {    //   ָ����ַ��ʣ���ֽ�������Ҫ���ȡ���ֽ���
            ulCount = rhb_24C16_DEVICE_ADDR_MAX - ulAddr + 1;       //   �������ȡ��ʣ����ֽ�
            *len = ulCount;
        }
        
        //  ��ʼ��ȡ����
        ulNumOnce = (256 - (ulAddr % 256));
        if(ulNumOnce > 0)                           //  ���д��ַû��256���룬��д������ĵ�ַ
        {
            if(ulCount > ulNumOnce) {
              ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
              i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulNumOnce);
              data += ulNumOnce;
              ulAddr += ulNumOnce;
              ulCount -= ulNumOnce;
            } else {
              ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
              i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulCount);
              ulAddr += ulCount;
              OSSemPost(i2c_handle->sem_I2C);
              return 1;
            }
        }
        while((ulCount / 256) > 0)                 //  ��256�ֽڶ����ȡ����
        {
            ulNumOnce = 256;
            ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
            i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulNumOnce);
            data += ulNumOnce;
            ulAddr += 256;
            ulCount -= 256;
        }
        if(ulCount > 0)                                   //  дʣ�²���һҳ������
        {
            ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
            i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulCount);
            ulAddr += ulCount;
        }
    }
    OSSemPost(i2c_handle->sem_I2C);
    
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c16_fwrite
** Descriptions:        ��24c16ָ���洢��Ԫ��ʼд��һ��������
** input parameters:    handle:   ��������������
**                      ulAddr��  24c16д����ʼ��ַ
**                      key��     д�����ԣ�����ȡ��������ֵ
**                      I2C_24c16_Normal            //  ��������24c16
**                      I2C_24c16_AllSet            //  ��ָ����ַ��������Ϊ0xFF
**                      I2C_24c16_AllReset          //  ��ָ����ַ��������Ϊ0x00
**                      buf:      д��������ʼ��ַ
**                      len:      д�����ݳ���ָ��
** output parameters:   NONE
** Returned value:      ������ȷ������1����֮������0
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_fwrite(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len)
{
    INT8U err;
    unsigned char ucI2cAddr;
    unsigned long ulCount = *len;
    unsigned long ulNumOnce = 0;
    unsigned char *data = buf;
    rhb_24c16_info *i2c_handle = handle;
    
    if(((*len) <= 0) || (len==NULL))
      return 0;
    
    OSSemPend(i2c_handle->sem_I2C,0,&err);
    if(err == OS_ERR_NONE)
    {
        if(ulAddr > rhb_24C16_DEVICE_ADDR_MAX) {
            *len = 0;
            OSSemPost(i2c_handle->sem_I2C);
            return 0;                                   //   дȡ��ַ���������洢��Ԫ����ַ������0
        }
        if((ulAddr + ulCount - 1) > rhb_24C16_DEVICE_ADDR_MAX) {  //   ָ����ַ��ʣ���ֽ�������Ҫ���ȡ���ֽ���
            ulCount = rhb_24C16_DEVICE_ADDR_MAX - ulAddr + 1;     //   �����д��ʣ����ֽ�
            *len = ulCount;
        }
        
        switch(key)                                     //     ѡ�������ʽ
        {
            case I2C_24C16_Normal:
                i2c_handle->i2c_operate = rhb_i2c_write;
                break;
            case I2C_24C16_AllSet:
                i2c_handle->i2c_operate = rhb_i2c_set;
                break;
            case I2C_24C16_AllReset:
                i2c_handle->i2c_operate = rhb_i2c_reset;
                break;
            default:
                *len = 0;
                OSSemPost(i2c_handle->sem_I2C);
                return 0;
        }
        
        ulNumOnce = (rhb_I2C_24C16_PAGE_SEZE - (ulAddr % rhb_I2C_24C16_PAGE_SEZE));
        if(ulNumOnce > 0)                           //  ���д��ַû�а�ҳ���룬��д������ĵ�ַ
        {
            if(ulCount > ulNumOnce) {
              ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
              i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulNumOnce);
              data += ulNumOnce;
              ulAddr += ulNumOnce;
              ulCount -= ulNumOnce;
              OSTimeDly(2);
            } else {
              ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
              i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulCount);
              ulAddr += ulCount;
              OSTimeDly(2);
              OSSemPost(i2c_handle->sem_I2C);
              return 1;
            }
        }
        while((ulCount / rhb_I2C_24C16_PAGE_SEZE) > 0)      //  ��ҳ����д����
        {
            ulNumOnce = rhb_I2C_24C16_PAGE_SEZE;
            ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
            i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulNumOnce);
            data += ulNumOnce;
            ulAddr += rhb_I2C_24C16_PAGE_SEZE;
            ulCount -= rhb_I2C_24C16_PAGE_SEZE;
            OSTimeDly(2);
        }
        if(ulCount > 0)                                   //  дʣ�²���һҳ������
        {
            ucI2cAddr = (((ulAddr & 0x700) >> 7) | rhb_I2C_24C16_ADDR);
            i2c_handle->i2c_operate(ucI2cAddr, ulAddr, 1, data, &ulCount);
            ulAddr += ulCount;
            OSTimeDly(2);
        }
    }
    OSSemPost(i2c_handle->sem_I2C);
    
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c16_IsBusy
** Descriptions:        I2C�����Ƿ�æ
** input parameters:    handle: ��������������
**                      NONE
** output parameters:   NONE
** Returned value:      true: ���ݿ��Է��ͣ����ڷ����У���֮false: �������ڽ����У��������ٴη���
ע�⣺��Ϊ���ź����ı�����������Ϊ�������ǲ�æ�ġ����Ƕ�ȡʱ�������������ֱ�����ź������á�
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_IsBusy(rhb_io_handle handle)
{
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c16_setConfig
** Descriptions:        ����ʱ�������ô��ڲ���
** input parameters:    handle: ��������������
**                      data��  ��ȡ����
**                      len��   ��������
** output parameters:   NONE
** Returned value:      0�����豸��������
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_setConfig(rhb_io_handle handle, void *data, unsigned long *len)
{
    
    return 0;
}

/*********************************************************************************************************
** Function name:       rhb_24c16_getConfig
** Descriptions:        ����ʱ�������ô��ڲ���
** input parameters:    handle: ��������������
**                      data��  ��ȡ����
**                      len��   ��������
**                      NONE
** output parameters:   NONE
** Returned value:      0�����豸���ɻ�ȡ����
*********************************************************************************************************/
rhb_ErrNo rhb_24c16_getConfig(rhb_io_handle handle, void *data, unsigned long *len)
{
    return 0;
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/

