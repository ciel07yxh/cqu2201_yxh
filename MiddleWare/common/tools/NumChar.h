/****************************************Copyright (c)****************************************************
**
**                          һ��Ϊ�������������Ƕ��ʽWEB��ʡ��Դ�����Ż�Ӧ��
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           NumChar.h
** Last modified Date:  2008.11.20
** Last Version:        v1.0
** Description:         �ַ���������֮���һЩ��������ͷ�ļ�����
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          �κ���
** Created date:        2008.11.20
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
#ifndef __NumChar_h
#define __NumChar_h

/***********************************����ԭ������********************************************************/

extern unsigned long PowerCall(unsigned long ulSrc, unsigned long ulPower);
extern void strToNumArray(unsigned char *pucDest, const unsigned char *pscSrc, unsigned long ulLen);
extern unsigned long strToLNum(unsigned char *pscSrc, unsigned long ulLen);
extern unsigned char charToHex(unsigned char *Buffer);

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

