/****************************************Copyright (c)****************************************************
**
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_24c02.c
** Last modified Date:  2010-11-9
** Last Version:        v1.0
** Description:         STM32���������м������ʵ��
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

#include "dev/I2C/24C02/rhb_24C02.h"


rhb_24c02_info __tGrhb_24c02 = {NULL, NULL};
/*********************************************************************************************************
** Function name:       rhb_24c02_init
** Descriptions:        ��ʼ��I2C�豸����ϵͳ�ں˵���
** input parameters:    handle: ��������������
**                      NONE
** output parameters:   NONE
** Returned value:      1:��ʼ���豸�ɹ� 
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_init(rhb_io_handle handle)
{
   rhb_24c02_info *i2c_handle = handle;
   
   i2c_handle->sem_I2C = OSSemCreate(1);
   i2c_handle->i2c_operate = rhb_i2c_read;
   
   return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c02_fread
** Descriptions:        ��24C02ָ���洢��Ԫ��ʼ��ȡָ��ֱ�ӵ�����
** input parameters:    handle:   ��������������
**                      ulAddr��  24C02��ȡ��ʼ��ַ
**                      key��     ��ȡ���ԣ�����ֻ��ΪI2C_24C02_Normal
**                      buf:      ��ȡ���ݴ�ŵ�ַ
**                      len:      ��ȡ���ݳ���ָ��
** output parameters:   NONE
** Returned value:      ������ȷ������1����֮������0
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_fread(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len) 
{
    INT8U err;
    unsigned long ulCount = *len;
    rhb_24c02_info *i2c_handle = handle;
    
    if((buf == NULL)|| ((*len) <= 0) || (len==NULL))
      return 0;
    
    if(key != I2C_24C02_Normal)
    {
        *len = 0;
        return 0;
    } else {
        i2c_handle->i2c_operate = rhb_i2c_read;
    }
    
    OSSemPend(i2c_handle->sem_I2C,0,&err);
    if(err == OS_ERR_NONE)
    {
        if(ulAddr > DEVICE_ADDR_MAX) {
            *len = 0;
            OSSemPost(i2c_handle->sem_I2C);
            return 0;                                   //   ��ȡ��ַ���������洢��Ԫ����ַ������0
        }
        if((ulAddr + ulCount - 1) > DEVICE_ADDR_MAX) {  //   ָ����ַ��ʣ���ֽ�������Ҫ���ȡ���ֽ���
            ulCount = DEVICE_ADDR_MAX - ulAddr + 1;     //   �������ȡ��ʣ����ֽ�
            *len = ulCount;
        }
        //  ��ʼ��ȡ����
        i2c_handle->i2c_operate(I2C_24C02_ADDR, ulAddr, 1, buf, &ulCount);
        ulAddr += ulCount;
    }
    OSSemPost(i2c_handle->sem_I2C);
    
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c02_fwrite
** Descriptions:        ��24C02ָ���洢��Ԫ��ʼд��һ��������
** input parameters:    handle:   ��������������
**                      ulAddr��  24C02д����ʼ��ַ
**                      key��     д�����ԣ�����ȡ��������ֵ
**                      I2C_24C02_Normal            //  ��������24C02
**                      I2C_24C02_AllSet            //  ��ָ����ַ��������Ϊ0xFF
**                      I2C_24C02_AllReset          //  ��ָ����ַ��������Ϊ0x00
**                      buf:      д��������ʼ��ַ
**                      len:      д�����ݳ���ָ��
** output parameters:   NONE
** Returned value:      ������ȷ������1����֮������0
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_fwrite(rhb_io_handle handle, unsigned long ulAddr, 
                          unsigned char key, void *buf, unsigned long *len)
{
    INT8U err;
    unsigned long ulCount = *len;
    unsigned long ulNumOnce = 0;
    unsigned char *data = buf;
    rhb_24c02_info *i2c_handle = handle;
    
    if(((*len) <= 0) || (len==NULL))
      return 0;
    
    OSSemPend(i2c_handle->sem_I2C,0,&err);
    if(err == OS_ERR_NONE)
    {
        if(ulAddr > DEVICE_ADDR_MAX) {
            *len = 0;
            OSSemPost(i2c_handle->sem_I2C);
            return 0;                                   //   дȡ��ַ���������洢��Ԫ����ַ������0
        }
        if((ulAddr + ulCount - 1) > DEVICE_ADDR_MAX) {  //   ָ����ַ��ʣ���ֽ�������Ҫ���ȡ���ֽ���
            ulCount = DEVICE_ADDR_MAX - ulAddr + 1;     //   �����д��ʣ����ֽ�
            *len = ulCount;
        }
        
        switch(key)                                     //     ѡ�������ʽ
        {
            case I2C_24C02_Normal:
                i2c_handle->i2c_operate = rhb_i2c_write;
                break;
            case I2C_24C02_AllSet:
                i2c_handle->i2c_operate = rhb_i2c_set;
                break;
            case I2C_24C02_AllReset:
                i2c_handle->i2c_operate = rhb_i2c_reset;
                break;
            default:
                *len = 0;
                OSSemPost(i2c_handle->sem_I2C);
                return 0;
        }
        
        ulNumOnce = (I2C_24C02_PAGE_SEZE - (ulAddr % I2C_24C02_PAGE_SEZE));
        if(ulNumOnce > 0)                           //  ���д��ַû�а�ҳ���룬��д������ĵ�ַ
        {
            if(ulCount > ulNumOnce) {
              i2c_handle->i2c_operate(I2C_24C02_ADDR, ulAddr, 1, data, &ulNumOnce);
              data += ulNumOnce;
              ulAddr += ulNumOnce;
              ulCount -= ulNumOnce;
              OSTimeDly(2);
            } else {
              i2c_handle->i2c_operate(I2C_24C02_ADDR, ulAddr, 1, data, &ulCount);
              ulAddr += ulNumOnce;
              OSTimeDly(2);
              OSSemPost(i2c_handle->sem_I2C);
              return 1;
            }
        }
        while((ulCount / I2C_24C02_PAGE_SEZE) > 0)      //  ��ҳ����д����
        {
            ulNumOnce = I2C_24C02_PAGE_SEZE;
            i2c_handle->i2c_operate(I2C_24C02_ADDR, ulAddr, 1, data, &ulNumOnce);
            data += ulNumOnce;
            ulAddr += I2C_24C02_PAGE_SEZE;
            ulCount -= I2C_24C02_PAGE_SEZE;
            OSTimeDly(2);
        }
        if(ulCount > 0)                             //  дʣ�²���һҳ������
        {
            i2c_handle->i2c_operate(I2C_24C02_ADDR, ulAddr, 1, data, &ulCount);
            ulAddr += ulNumOnce;
            OSTimeDly(2);
        }
    }
    OSSemPost(i2c_handle->sem_I2C);
    
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c02_IsBusy
** Descriptions:        I2C�����Ƿ�æ
** input parameters:    handle: ��������������
**                      NONE
** output parameters:   NONE
** Returned value:      true: ���ݿ��Է��ͣ����ڷ����У���֮false: �������ڽ����У��������ٴη���
ע�⣺��Ϊ���ź����ı�����������Ϊ�������ǲ�æ�ġ����Ƕ�ȡʱ�������������ֱ�����ź������á�
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_IsBusy(rhb_io_handle handle)
{
    return 1;
}

/*********************************************************************************************************
** Function name:       rhb_24c02_setConfig
** Descriptions:        ����ʱ�������ô��ڲ���
** input parameters:    handle: ��������������
**                      data��  ��ȡ����
**                      len��   ��������
** output parameters:   NONE
** Returned value:      0�����豸��������
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_setConfig(rhb_io_handle handle, void *data, unsigned long *len)
{
    
    return 0;
}

/*********************************************************************************************************
** Function name:       rhb_24c02_getConfig
** Descriptions:        ����ʱ�������ô��ڲ���
** input parameters:    handle: ��������������
**                      data��  ��ȡ����
**                      len��   ��������
**                      NONE
** output parameters:   NONE
** Returned value:      0�����豸���ɻ�ȡ����
*********************************************************************************************************/
rhb_ErrNo rhb_24c02_getConfig(rhb_io_handle handle, void *data, unsigned long *len)
{
    return 0;
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/

