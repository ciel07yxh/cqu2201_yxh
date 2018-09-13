/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_flash.c
** Last modified Date:  2013-04-04
** Last Version:        v1.0
** Description:         flashģ��Ĵ�����װ����ʵ������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-04-04
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
#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_flash.h"

extern void watchdog_periodic(void);
/*********************************************************************************************************
** Function name:       flashUnlock
** Descriptions:        ��flashģ���������������Բ��������Flash
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void flashUnlock(void)
{
    HWREG32(FLASH_BASE + FLASH_O_KEYR) = FLASH_UNLOCK_KER1;
    HWREG32(FLASH_BASE + FLASH_O_KEYR) = FLASH_UNLOCK_KER2;
    
#if (STM32F10XX_XL_Density > 0)
    HWREG32(FLASH_BASE + FLASH_O_KEYR2) = FLASH_UNLOCK_KER1;
    HWREG32(FLASH_BASE + FLASH_O_KEYR2) = FLASH_UNLOCK_KER2;
#endif
}

/*********************************************************************************************************
** Function name:       flashLock
** Descriptions:        ��flashģ�������������flash��������������
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void flashLock(void)
{
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000080;
    
#if (STM32F10XX_XL_Density > 0)
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000080;
#endif
}

/*********************************************************************************************************
** Function name:       flashPageErase
** Descriptions:        ����ָ����һҳ
** input parameters:    ulPageAddr��ָ������ҳ�ĵ�ַ����ͬ��ϵ��оƬҳ��С���ܲ�ͬ
** output parameters:   NONE
** Returned value:      true�������ɹ��� false: �����˴��󣬲���ʧ��
*********************************************************************************************************/
boolean flashPageErase(unsigned long ulPageAddr)
{
#if (STM32F10XX_XL_Density > 0)
  if(ulPageAddr < FLASH_BANK1_END_ADDRESS) {
      while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){   //  �ȴ�������æ
        watchdog_periodic();
      }
      
      if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
      {
          HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000002;       //  ѡ��ҳ����
          HWREG32(FLASH_BASE + FLASH_O_AR)  = ulPageAddr;       //  д��ҳ��ַ
          HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000040;       //  ��������
          while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){ //  �ȴ��������
            watchdog_periodic();
          }
          HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFD;       //  ҳ������ɣ����ҳ������־
          if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ���û�д�����,������̴����д��������
          {
            return true;
          } else {
            return false;
          }
      } else {
          return false;
      }
  } else {
      while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001){   //  �ȴ�������æ
        watchdog_periodic();
      }
      
      if (!((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
      {
          HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000002;       //  ѡ��ҳ����
          HWREG32(FLASH_BASE + FLASH_O_AR2)  = ulPageAddr;       //  д��ҳ��ַ
          HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000040;       //  ��������
          while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001){ //  �ȴ��������
            watchdog_periodic();
          }
          HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFD;       //  ҳ������ɣ����ҳ������־
          if (!((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014))       //  ���û�д�����,������̴����д��������
          {
            return true;
          } else {
            return false;
          }
      } else {
          return false;
      }
  }
#else
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){   //  �ȴ�������æ
      watchdog_periodic();
    }
      
    if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
    {
        HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000002;       //  ѡ��ҳ����
        HWREG32(FLASH_BASE + FLASH_O_AR)  = ulPageAddr;       //  д��ҳ��ַ
        HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000040;       //  ��������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){ //  �ȴ��������
          watchdog_periodic();
        }
        HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFD;       //  ҳ������ɣ����ҳ������־
        if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ���û�д�����,������̴����д��������
        {
          return true;
        } else {
          return false;
        }
    } else {
        return false;
    }
#endif
}

/*********************************************************************************************************
** Function name:       flashMassErase
** Descriptions:        ȫƬ����flash
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      true�������ɹ��� false: �����˴��󣬲���ʧ��
*********************************************************************************************************/
boolean flashMassErase(void)
{
#if (STM32F10XX_XL_Density > 0)
    // �Ȳ���Bank1
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){   //  �ȴ�������æ
      watchdog_periodic();
    }
    
    if (((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014)) {      //  ����ϴ��д�����,������̴����д��������
       return false;
    }
      
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000004;       //  ѡ��ȫƬ����
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000040;       //  ��������
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001) { //  �ȴ��������
      watchdog_periodic();
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFB;       //  ȫƬ������ɣ����������־
    if (((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014)) {      //  ����д�����,������̴����д��������
       return false;
    }
    
    // �ٲ���Bank2
    while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001){   //  �ȴ�������æ
      watchdog_periodic();
    }
    
    if (((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014)) {      //  ����ϴ��д�����,������̴����д��������
       return false;
    }
      
    HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000004;       //  ѡ��ȫƬ����
    HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000040;       //  ��������
    while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001){ //  �ȴ��������
      watchdog_periodic();
    }
    HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFB;       //  ȫƬ������ɣ����������־
    if (((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014)) {      //  ����д�����,������̴����д��������
       return false;
    }
    
    return true;
  
  
#else
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){   //  �ȴ�������æ
      watchdog_periodic();
    }
    
    if (((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014)) {      //  ����ϴ��д�����,������̴����д��������
       return false;
    }
      
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000004;       //  ѡ��ȫƬ����
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000040;       //  ��������
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001){ //  �ȴ��������
       watchdog_periodic();
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFB;       //  ȫƬ������ɣ����������־
    if (((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014)) {      //  ����д�����,������̴����д��������
       return false;
    }
    
    return true;
#endif
}

/*********************************************************************************************************
** Function name:       flashWriteHalfWord
** Descriptions:        ��Flash��ָ����ַд��һ��16λ������
** input parameters:    ulAddr:   ָ��д��ĵ�ַ
**                      usData:   ָ��Ҫд�������
** output parameters:   NONE
** Returned value:      true��д�ɹ��� false: �����˴���дʧ��
*********************************************************************************************************/
boolean flashWriteHalfWord(unsigned long ulAddr, unsigned short usData)
{
#if (STM32F10XX_XL_Density > 0)
   if(ulAddr < FLASH_BANK1_END_ADDRESS) {
      while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
      
      if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
      {
          HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;        //  ѡ��flash���ģʽ
          HWREG16(ulAddr) = usData;                            //  д���̵İ�������
          while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
          HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;        // �����ɣ������̱�־
          if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ���û�д�����,������̴����д��������
          {
            return true;
          } else {
            return false;
          }
      }
      return false;
   }else {
      while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
      
      if (!((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
      {
          HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000001;        //  ѡ��flash���ģʽ
          HWREG16(ulAddr) = usData;                            //  д���̵İ�������
          while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
          HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFE;        // �����ɣ������̱�־
          if (!((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x0014))       //  ���û�д�����,������̴����д��������
          {
            return true;
          } else {
            return false;
          }
      }
      return false;
   }
#else 
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
    
    if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ����ϴ�û�д�����,������̴����д��������
    {
        HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;        //  ѡ��flash���ģʽ
        HWREG16(ulAddr) = usData;                            //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
        HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;        // �����ɣ������̱�־
        if (!((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x0014))       //  ���û�д�����,������̴����д��������
        {
          return true;
        } else {
          return false;
        }
    }
    return false;
#endif
}

/*********************************************************************************************************
** Function name:       flashProgram
** Descriptions:        ��Flash��ָ����ַ���ָ���ֽڵ�����
** input parameters:    pusData:   ������ݻ�����ָ��
**                      ulAddr:    ָ����̵�ַ
**                      ulSize:    ָ����̵��ֽ�����������2�ı���
** output parameters:   NONE
** Returned value:      true��д�ɹ��� false: �����˴���дʧ��
*********************************************************************************************************/
boolean flashProgram(unsigned short *pusData, unsigned long ulAddr, unsigned long ulSize)
{
    if ((ulSize < 2) || (ulAddr < 0x08000000) || ((ulSize % 2) != 0))
        return false;
    
#if (STM32F10XX_XL_Density > 0)
    if(ulAddr < FLASH_BANK1_END_ADDRESS) {
      while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
      
      HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;            //  ѡ��flash���ģʽ
    } else {
      goto FlashProgramBank2;
    }
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = *pusData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
        pusData++;
        ulAddr += 2;
        ulSize -= 2;
        if(ulAddr > FLASH_BANK1_END_ADDRESS) {
          HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;       // �����ɣ������̱�־
          goto FlashProgramBank2;
        }
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;            // �����ɣ������̱�־
    
FlashProgramBank2:
    while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
      
    HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000001;            //  ѡ��flash���ģʽ
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = *pusData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
        pusData++;
        ulAddr += 2;
        ulSize -= 2;
    }
    HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFE;            // �����ɣ������̱�־
    
    return true;
#else
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
    
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;            //  ѡ��flash���ģʽ
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = *pusData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
        pusData++;
        ulAddr += 2;
        ulSize -= 2;
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;            // �����ɣ������̱�־
    return true;
#endif
}

/*********************************************************************************************************
** Function name:       flashConstDataProgram
** Descriptions:        ��Flash��ָ����ַ���д��̶�������
** input parameters:    usData:    ��̵Ĺ̶�����
**                      ulAddr:    ָ����̵�ַ
**                      ulSize:    ָ����̵��ֽ�����������2�ı���
** output parameters:   NONE
** Returned value:      true��д�ɹ��� false: �����˴���дʧ��
*********************************************************************************************************/
boolean flashConstDataProgram(unsigned short usData, unsigned long ulAddr, unsigned long ulSize)
{
    if ((ulSize < 2) || (ulAddr < 0x08000000) || ((ulSize % 2) != 0))
        return false;
#if (STM32F10XX_XL_Density > 0)
    if(ulAddr < FLASH_BANK1_END_ADDRESS) {
      while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
      
      HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;            //  ѡ��flash���ģʽ
    } else {
      goto FlashProgramConstBank2;
    }
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = usData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
        ulAddr += 2;
        ulSize -= 2;
        if(ulAddr > FLASH_BANK1_END_ADDRESS) {
          HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;            // �����ɣ������̱�־
          goto FlashProgramConstBank2;
        }
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;            // �����ɣ������̱�־
    
FlashProgramConstBank2:
    while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
      
    HWREG32(FLASH_BASE + FLASH_O_CR2) |= 0x00000001;            //  ѡ��flash���ģʽ
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = usData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR2)) & 0x00000001);   //  �ȴ�������æ
        ulAddr += 2;
        ulSize -= 2;
    }
    HWREG32(FLASH_BASE + FLASH_O_CR2) &= 0x00001FFE;            // �����ɣ������̱�־
    
    return true;
#else 
    while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
    
    HWREG32(FLASH_BASE + FLASH_O_CR) |= 0x00000001;            //  ѡ��flash���ģʽ
    while(ulSize)
    {
        if((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x001)       //  ����ϴ��д�����,������̴����д��������
        {
            HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;    // �����ɣ������̱�־
            return false;
        }
        HWREG16(ulAddr) = usData;                          //  д���̵İ�������
        while((HWREG32(FLASH_BASE + FLASH_O_SR)) & 0x00000001);   //  �ȴ�������æ
        ulAddr += 2;
        ulSize -= 2;
    }
    HWREG32(FLASH_BASE + FLASH_O_CR) &= 0x00001FFE;            // �����ɣ������̱�־
    return true;
#endif
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
