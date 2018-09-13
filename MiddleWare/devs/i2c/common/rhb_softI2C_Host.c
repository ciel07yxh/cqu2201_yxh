/****************************************Copyright (c)****************************************************
**
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               rhb_softI2C_Host.c
** Last modified Date:      2010-8-05
** Last Version:            v1.0
** Description:             ���ģ��I2C������ʵ�������
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              Renhaibo
** Created date:            2010-8-05
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
#include "rhb_softI2C_Host.h"
#include "target.h"

#if (rhb_I2C_Delay > 0)
#define I2C_Delay()      usdelay(rhb_I2C_Delay)
#else
#define I2C_Delay()
#endif

unsigned long stm32_SDA_Read(void)       
{
   unsigned long ulTemp;
   HWREG(GPIOC_BASE + GPIO_O_CRH) &= 0x0FFFFFFF;
   HWREG(GPIOC_BASE + GPIO_O_CRH) |= 0x40000000;
   ulTemp = (HWREG(GPIOC_BASE + GPIO_O_IDR) & 0x8000);     //  ��SDA�ߵ�״̬
   HWREG(GPIOC_BASE + GPIO_O_CRH) &= 0x0FFFFFFF;
   HWREG(GPIOC_BASE + GPIO_O_CRH) |= 0x70000000;
   
   return ulTemp;  
}
#define rhb_SDA_Read() stm32_SDA_Read()
/*********************************************************************************************************
** Function name:       rhb_I2C_Start
** Descriptions:        IOģ��I2C������ʼ����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      true:��ʼ������ȷ������fasle������æ��
*********************************************************************************************************/
void rhb_I2C_Start(void)
{
    rhb_SDA_H();
    rhb_SCL_H();
    I2C_Delay();
    rhb_SDA_L();
    I2C_Delay();
    rhb_SCL_L();
    I2C_Delay();
}

/*********************************************************************************************************
** Function name:       rhb_I2C_Stop
** Descriptions:        IOģ��I2C����ֹͣ����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_I2C_Stop(void)
{
    rhb_SCL_L();
    rhb_SDA_L();
    I2C_Delay();
    rhb_SCL_H();
    I2C_Delay();
    rhb_SDA_H();
    I2C_Delay();
}
/*********************************************************************************************************
** Function name:       rhb_I2C_Ack
** Descriptions:        IOģ��I2C����Ack�ź�
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_I2C_Ack(void)
{ 
    rhb_SCL_L();
    I2C_Delay();
    rhb_SDA_L();
    I2C_Delay();
    rhb_SCL_H();
    I2C_Delay();
    rhb_SCL_L();
    I2C_Delay();
}

/*********************************************************************************************************
** Function name:       rhb_I2C_NoAck
** Descriptions:        IOģ��I2C����NOAck�ź�
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_I2C_NoAck(void)
{ 
    rhb_SCL_L();
    I2C_Delay();
    rhb_SDA_H();
    I2C_Delay();
    rhb_SCL_H();
    I2C_Delay();
    rhb_SCL_L();
    I2C_Delay();
}

/*********************************************************************************************************
** Function name:       rhb_I2C_WaitAck
** Descriptions:        IOģ��I2C����WaitAck�ź�
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      true:��Ack�źţ�false:��Ack�ź�
*********************************************************************************************************/
tBoolean rhb_I2C_WaitAck(void)
{
    rhb_SCL_L();
    I2C_Delay();
    rhb_SDA_H();
    I2C_Delay();
    rhb_SCL_H();
    I2C_Delay();
    if(rhb_SDA_Read())
    {
      rhb_SCL_L();
      return false;
    }
    rhb_SCL_L();
    return true;
}

/*********************************************************************************************************
** Function name:       rhb_I2C_WaitAck
** Descriptions:        IOģ��I2C����һ���ֽ�
** input parameters:    ucByte: ���͵����ݣ������ȷ���MSB�������LSB
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_I2C_SendByte(unsigned char ucByte)
{
    unsigned char i=8;
    while(i--)
    {
        rhb_SCL_L();
        I2C_Delay();
        if(ucByte&0x80)
            rhb_SDA_H(); 
        else 
            rhb_SDA_L();   
        ucByte<<=1;
        I2C_Delay();
        rhb_SCL_H();
        I2C_Delay();
    }
    rhb_SCL_L();
}

/*********************************************************************************************************
** Function name:       rhb_I2C_RecvByte
** Descriptions:        IOģ��I2C����һ���ֽڵ�����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      ���յ������ݣ����ݴӸ�λ����λ���ա�
*********************************************************************************************************/
unsigned char rhb_I2C_RecvByte(void)
{ 
    unsigned char i=8;
    unsigned char ucByte=0;

    rhb_SDA_H();
    while(i--)
    {
      ucByte <<= 1;
      rhb_SCL_L();
      I2C_Delay();
      rhb_SCL_H();
      I2C_Delay(); 
      if(rhb_SDA_Read())
      {
        ucByte|=0x01;
      }
    }
    rhb_SCL_L();
    return ucByte;
}

/*********************************************************************************************************
** Function name:       rhb_i2c_read
** Descriptions:        IO�����Ӵӻ���ȡһ���ֽڵ�����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_i2c_read(unsigned char I2CAddr, unsigned long ulAddr, 
                  unsigned char addrLen, void *buf, unsigned long *len)
{
    unsigned char i = 0;
    unsigned char *data = buf;
    unsigned long ulCount = *len;
    
    rhb_I2C_Start();                                //  �ȴ�����ֹͣ����
    rhb_I2C_SendByte(I2CAddr | rhb_I2C_WRITE);      //  ����������ַ
    for(i=0; i< addrLen; i++)
    {
        rhb_I2C_Ack();
        rhb_I2C_SendByte((char)(ulAddr>>((addrLen-i-1)*8)));    //  ���Ͷ�ȡ�洢����Ԫ��ַ
    }
    rhb_I2C_Ack();
    rhb_I2C_Start();                                //  �ȴ�����ֹͣ����
    rhb_I2C_SendByte(I2CAddr | rhb_I2C_READ);       //  ����������ַ������־��
    while(ulCount--){
        rhb_I2C_Ack();                              //  ��ʼ��ȡ���ݣ������뻺��
        *data++ = rhb_I2C_RecvByte();
    }
    rhb_I2C_NoAck();
    rhb_I2C_Stop();
}

/*********************************************************************************************************
** Function name:       rhb_i2c_write
** Descriptions:        IO������ӻ�д��һ���ֽڵ�����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_i2c_write(unsigned char I2CAddr, unsigned long ulAddr, 
                   unsigned char addrLen, void *buf, unsigned long *len)
{
    unsigned char i = 0;
    unsigned char *data = buf;
    unsigned long ulCount = *len;
    
    rhb_I2C_Start();                            //  �ȴ�����ֹͣ����
    rhb_I2C_SendByte(I2CAddr | rhb_I2C_WRITE);  //  ����������ַ
    for(i=0; i< addrLen; i++)
    {
        rhb_I2C_Ack();
        rhb_I2C_SendByte((char)(ulAddr>>((addrLen-i-1)*8)));    //  ���Ͷ�ȡ�洢����Ԫ��ַ
    }
    while(ulCount--){
        rhb_I2C_Ack();                          //  ��ʼ��ȡ���ݣ������뻺��
        rhb_I2C_SendByte(*data++);             //  д��һ���ֽڵ�����
    }
    rhb_I2C_Ack();
    rhb_I2C_Stop();
}

/*********************************************************************************************************
** Function name:       rhb_i2c_set
** Descriptions:        I2Cָ����ַ����������Ϊ0xFF
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_i2c_set(unsigned char I2CAddr, unsigned long ulAddr, 
                   unsigned char addrLen, void *buf,unsigned long *len)
{
    unsigned char i = 0;
    unsigned long ulCount = *len;
    
    rhb_I2C_Start();                            //  �ȴ�����ֹͣ����
    rhb_I2C_SendByte(I2CAddr | rhb_I2C_WRITE);  //  ����������ַ
    for(i=0; i< addrLen; i++)
    {
        rhb_I2C_Ack();
        rhb_I2C_SendByte((char)(ulAddr>>((addrLen-i-1)*8)));    //  ���Ͷ�ȡ�洢����Ԫ��ַ
    }
    while(ulCount--){
        rhb_I2C_Ack();                          //  ��ʼ��ȡ���ݣ������뻺��
        rhb_I2C_SendByte(0xFF);                //  д��һ���ֽڵ�����
    }
    rhb_I2C_Ack();
    rhb_I2C_Stop();
}

/*********************************************************************************************************
** Function name:       rhb_i2c_set
** Descriptions:        I2Cָ����ַ����������Ϊ0x00
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void rhb_i2c_reset(unsigned char I2CAddr, unsigned long ulAddr, 
                   unsigned char addrLen, void *buf,unsigned long *len)
{
    unsigned char i = 0;
    unsigned long ulCount = *len;
    
    rhb_I2C_Start();                            //  �ȴ�����ֹͣ����
    rhb_I2C_SendByte(I2CAddr | rhb_I2C_WRITE);  //  ����������ַ
    for(i=0; i< addrLen; i++)
    {
        rhb_I2C_Ack();
        rhb_I2C_SendByte((char)(ulAddr>>((addrLen-i-1)*8)));    //  ���Ͷ�ȡ�洢����Ԫ��ַ
    }
    while(ulCount--){
        rhb_I2C_Ack();                          //  ��ʼ��ȡ���ݣ������뻺��
        rhb_I2C_SendByte(0x00);                 //  д��һ���ֽڵ�����
    }
    rhb_I2C_Ack();
    rhb_I2C_Stop();
}

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
