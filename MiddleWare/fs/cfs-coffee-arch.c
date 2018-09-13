/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           cfs-coffee-arch.h
** Last modified Date:  2012-08-03
** Last Version:        coffee�ļ�ϵͳģ����ֲ����ʵ��
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          �κ���
** Created date:        2012-08-03
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

/*********************************************************************************************************
** ͷ�ļ�����
*********************************************************************************************************/
#include <string.h>
#include "cfs-coffee-arch.h"

/*********************************************************************************************************
** Allocates a buffer of FLASH_PAGE_SIZE bytes statically (rather than on the stack).
*********************************************************************************************************/
#ifndef STATIC_FLASH_BUFFER
#define STATIC_FLASH_BUFFER     1
#endif

/*********************************************************************************************************
** Function name:       stm32f10xx_flash_read
** Descriptions:        ��ȡָ����ַflash�е�����
** Input parameters:    u32Addr:  ָ����д��flash��ַ
**                      data:     ��ȡ���ݴ�ŵ�ַ
**                      len:      ��ȡ���ݳ���
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void stm32f10xx_flash_read(uint32_t u32Addr, void *data, uint32_t len)
{
    uint8_t *pSrcData = (uint8_t *)u32Addr;
    ENERGEST_ON(ENERGEST_TYPE_FLASH_READ);
    memcpy(data, pSrcData, len);
    ENERGEST_OFF(ENERGEST_TYPE_FLASH_READ);
}

/*********************************************************************************************************
** Function name:       stm32f10xx_flash_erase
** Descriptions:        ����flashָ������������
** Input parameters:    sector:  ��������������
** Output parameters:   ��
** Returned value:      ��
** ע�⣺����Ĳ����ǽ�Flash���㣬����Flashһ��Ҫ�Ȳ�����Ȼ����д��0
*********************************************************************************************************/
void stm32f10xx_flash_erase(uint32_t sector)
{
    uint32_t addr = COFFEE_START + (sector) * COFFEE_SECTOR_SIZE;
  
    flashUnlock();
    flashPageErase(COFFEE_START + (sector) * COFFEE_SECTOR_SIZE);
    flashConstDataProgram(0, addr, COFFEE_SECTOR_SIZE);
    flashLock();
}


/*********************************************************************************************************
** Function name:       stm32f10xx_flash_write
** Descriptions:        ��Flash��ָ����ַд������
** Input parameters:    u32Addr:  ָ��д��flash��ַ
**                      data:     д���ݴ�ŵ�ַ
**                      len:      дȡ���ݳ���
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void stm32f10xx_flash_write(uint32_t u32Addr, const void *data, uint32_t len)
{
    const uint32_t end = u32Addr + len;
    uint32_t i;
    uint32_t next_page, curr_page;
    uint16_t offset;
  
#if STATIC_FLASH_BUFFER
    static uint8_t buf[FLASH_PAGE_SIZE];
#else
    uint8_t buf[FLASH_PAGE_SIZE];
#endif
  
    for(i = u32Addr; i<end;)
    {
        next_page = (i | (FLASH_PAGE_SIZE-1)) + 1;
        curr_page = i & ~(FLASH_PAGE_SIZE-1);
        offset = i - curr_page;
        if(next_page > end) {
          next_page = end;
        }
        // ��ȡһҳ�����ݵ�ָ���Ļ�����
        stm32f10xx_flash_read(curr_page, buf, FLASH_PAGE_SIZE);
        // ��������
        memcpy(buf + offset, data, next_page - i);
        // ������������д��������
        ENERGEST_ON(ENERGEST_TYPE_FLASH_WRITE);
        flashUnlock();
        flashPageErase(i);
        flashProgram((uint16_t *)buf, curr_page, FLASH_PAGE_SIZE);
        flashLock();
        ENERGEST_OFF(ENERGEST_TYPE_FLASH_WRITE);
        
        data = (u8_t *)data + next_page - i;
        i = next_page;
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
