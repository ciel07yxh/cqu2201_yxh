/****************************************Copyright (c)****************************************************
**
**                          һ��Ϊ�������������Ƕ��ʽWEB��ʡ��Դ�����Ż�Ӧ��
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               memsearch.h
** Last modified Date:      2008.11.22
** Last Version:            v1.0
** Description:             ��ָ�����ڴ��в����ַ����ַ����ȵĴ�������ͷ�ļ�����
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
#ifndef	 __memsearch_h
#define	 __memsearch_h

extern void *memSearch(void *mem, unsigned long ulmemSize, 
                       unsigned char ucData, unsigned long ulDataSize);
extern void *memchrExt(void *mem, unsigned long ulmemSize, unsigned char ucCh);
extern unsigned char bMemStr(void *mem, unsigned long ulmemSize, 
                             unsigned char *pucStr, unsigned long ulStrSize);
extern void *pMemStr(void *mem, unsigned long ulmemSize,
                     unsigned char *pucStr, unsigned long ulStrSize);

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

