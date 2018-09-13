/****************************************Copyright (c)****************************************************
**
**                          һ��Ϊ�������������Ƕ��ʽWEB��ʡ��Դ�����Ż�Ӧ��
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               memsearch.c
** Last modified Date:      2008.11.20
** Last Version:            v1.0
** Description:             ��ָ�����ڴ��в����ַ����ַ����ȵĴ�����
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              �κ���
** Created date:            2008.11.20
** Version:                 v1.0
** Descriptions:            The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Description:             
**
*********************************************************************************************************/
#include  "includes.h"
#include  "memsearch.h"

/*********************************************************************************************************
** Function name:       memSearch
** Descriptions:        ��ָ����С���ڴ�����������ݣ��ú������Բ����������͵�����
** input parameters:    mem:        ָ����һ���ڴ�����ָ��
**                      ulmemSize:  ָ�����ڴ����Ĵ�С
**                      ucData:     ָ��Ҫ���ҵ�����
**                      ulDataSize: ָ���������ݵĴ�С(���ֽ�Ϊ��λ)
** output parameters:   ��
** Returned value:      ��������ҵ�������λ��ָ�룻��֮������NULL
** Created by:          �κ���
** Created Date:        2008.11.22
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void *memSearch(void *mem, unsigned long ulmemSize, unsigned char ucData, unsigned long ulDataSize)
{
    unsigned char *__pAddr = (unsigned char *)mem;
    unsigned char *__pData = &ucData;
    unsigned long   i;
    unsigned char   __blIsMatch;

    do{
        __pAddr = memchrExt(__pAddr, (unsigned long)(((unsigned char *)mem + ulmemSize) - __pAddr), *__pData);
        if(__pAddr != NULL)
        {
            __blIsMatch = 1;
            for(i=1; i<ulDataSize; i++)
            {
                if(*(__pAddr + i) != *(__pData + i))
                {
                    __blIsMatch = 0;
                    break;
                }
            }

            if(__blIsMatch)
                return (void *)__pAddr;
                __pAddr++;
            } else break;
    }while(1);

    return NULL;
}

/*********************************************************************************************************
** Function name:       memchrExt  
** Descriptions:        ��ָ����С���ڴ���������ַ�
** input parameters:    mem: ָ����һ���ڴ�����ָ��
**                      ulmemSize:  ָ�����ڴ����Ĵ�С
**                      ucCh:   ָ��Ҫ���ҵ��ַ�
** output parameters:   ��
** Returned value:      ��������ҵ�������λ��ָ�룻��֮������NULL
** Created by:          �κ���
** Created Date:        2008.11.22
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void *memchrExt(void *mem, unsigned long ulmemSize, unsigned char ucCh)
{
    unsigned char *__pbNext = (unsigned char *)mem;
    unsigned long    i;

    for(i=0; i<ulmemSize; i++)
    {
        if(*(__pbNext+i) == ucCh)
            return (__pbNext + i);
    }
    
    return NULL;
}

/*********************************************************************************************************
** Function name:       bMemStr  
** Descriptions:        ��ָ����С���ڴ���������ַ���
** input parameters:    mem: ָ����һ���ڴ�����ָ��
**                      ulmemSize:  ָ�����ڴ����Ĵ�С
**                      pucStr:   ָ��Ҫ���ҵ��ַ���
**                      ulStrSize��ָ���ַ����Ĵ�С(���ֽ�Ϊ��λ)
** output parameters:   ��
** Returned value:      ��������ҵ�������λ���߼�ֵ1����֮�������߼�ֵ0
** Created by:          �κ���
** Created Date:        2008.11.22
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
unsigned char bMemStr(void *mem, unsigned long ulmemSize, unsigned char *pucStr, unsigned long ulStrSize)
{
        unsigned char  *__pbNext =(unsigned char*)mem;
    unsigned long   i;
    unsigned char   __blIsMatch;
    
    do{
           __pbNext = memchrExt(__pbNext, 
                                    (unsigned long)(((unsigned char*)mem + ulmemSize) - __pbNext),
                                    *pucStr);
           if(__pbNext != NULL)
           {
            __blIsMatch = 1;
            for(i=1; i<ulStrSize; i++)
            {
                if(*(__pbNext + i) != *(pucStr + i))
                {
                    __blIsMatch = 0;
                    break;
                }
            }

            if(__blIsMatch)
                return 1;

            __pbNext++;
           }
        else
            break;
    }while(1);

        return 0;
}

/*********************************************************************************************************
** Function name:       pMemStr 
** Descriptions:        ��ָ����С���ڴ���������ַ���
** input parameters:    mem: ָ����һ���ڴ�����ָ��
**                      ulmemSize:  ָ�����ڴ����Ĵ�С
**                      pucStr:   ָ��Ҫ���ҵ��ַ���
**                      ulStrSize��ָ���ַ����Ĵ�С(���ֽ�Ϊ��λ)
** output parameters:   ��
** Returned value:      ��������ҵ�������λ��ָ�룻��֮������NULL
** Created by:          �κ���
** Created Date:        2008.11.22
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void *pMemStr(void *mem, unsigned long ulmemSize, unsigned char *pucStr, unsigned long ulStrSize)
{
    unsigned char  *__pbNext =(unsigned char*)mem;
    unsigned long   i;
    unsigned char   __blIsMatch;
    
    do{
          __pbNext = memchrExt(__pbNext, 
                               (unsigned long)(((unsigned char*)mem + ulmemSize) - __pbNext),
                               *pucStr);
           if(__pbNext != NULL)
           {
            __blIsMatch = 1;
            for(i=1; i<ulStrSize; i++)
            {
                if(*(__pbNext + i) != *(pucStr + i))
                {
                    __blIsMatch = 0;
                    break;
                }
            }

            if(__blIsMatch)
                return (void *)__pbNext;
                __pbNext++;
           }
        else
            break;
    }while(1);

       return NULL;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

