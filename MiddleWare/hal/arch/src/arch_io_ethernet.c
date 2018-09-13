/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_ethernet.c
** Last modified Date:  2013-04-04
** Last Version:        v1.0
** Description:         ethernetģ��Ĵ�����װ����ʵ������
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
#include "hal/arch/inc/arch_io_ethernet.h"


/*********************************************************************************************************
  �ֲ���������
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       EthernetInit
** Descriptions:        Ethernetģ������
** input parameters:    u32Base:    ethernetģ�����ַ
**                      u32Clock:   �ṩ����̫��ģ���ʱ�ӣ���AHB��ʱ��Ƶ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetInit(uint32 u32Base, uint32 u32Clock)
{
    uint32 u32Temp;
    uint32 u32PhyRegValue;
    uint32 u32AutoValue;

    // ����u32Clock��ֵ��ȷ��MDCģ���ʱ��
    u32Temp = HWREG32(u32Base + ETH_MACMIIAR);
    u32Temp &= 0xFFFFFFE3;
    if((u32Clock >= 20000000) && (u32Clock < 35000000)) {
        u32Temp |= (0x00000002 << 2);
    } else if((u32Clock >= 35000000) && (u32Clock < 60000000)) {
        u32Temp |= (0x00000003 << 2);
    } else if((u32Clock >= 60000000) && (u32Clock < 100000000)) {
        u32Temp |= (0x00000000 << 2);
    } else {  // ��������ǣ�ʱ�Ӿ���100M-120M
        u32Temp |= (0x00000001 << 2);
    }
    HWREG32(u32Base + ETH_MACMIIAR) = u32Temp;

    /*
    ** �����������룬���PHY��صĳ�ʼ������
    */
    // ��ȡPHY LAN8700��ID���������ֱ�ӷ���
    u32PhyRegValue = EthernetPHYRead(u32Base, PHYAddress, 16);
    if(u32PhyRegValue != 0x0040) {
      return;
    }

    EthernetPHYWrite(u32Base, PHYAddress, 0, 0x8000);           //  ��λPHY
    while(EthernetPHYRead(u32Base, PHYAddress, 0) & 0x8000);   //  �ȴ���λ���

    //u32PhyRegValue = EthernetPHYRead(u32Base, PHYAddress, 18);

    //  ����PHY����Э�̹���
    u32Temp = EthernetPHYRead(u32Base, PHYAddress, 0);
    u32Temp |= 0x1000;
    EthernetPHYWrite(u32Base, PHYAddress, 0, u32Temp);

//    while(!((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0004)));
//    while(!((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0020)));
#if 0
    //  ��ȡ����״̬������������
    if ((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0004)) {
        // �����Э�������
        if((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0020)) {
            //  ��ȡ��Э�̵Ľ��
            u32PhyRegValue = EthernetPHYRead(u32Base, PHYAddress, 0);

            if (u32PhyRegValue & 0x0100) {
                //  ȫ˫��ͨ��ģʽ
                u32AutoValue = 0x00000800;
            } else {
                //  ��˫��ͨ��ģʽ
                u32AutoValue = 0x00000000;
            }

            if (u32PhyRegValue & 0x2000) {
                //  100M��̫��ͨ��ģʽ
                u32AutoValue |= 0x00004000;
            } else {
                //  10M��̫��ͨ��ģʽ
                u32AutoValue |= 0x00000000;
            }
        } else {
            u32AutoValue = 0x00000000;
        }
    } else {
        u32AutoValue = 0x00000000;
    }
#endif

    // ��MACֱ�����ó�100M��ȫ˫����ͨ��ģʽ
    u32AutoValue = 0x00004800;

    /*  PHY��ʼ����������ɣ���Э�̽�������ڱ���u32AutoValue�У��ȴ��Ժ�����MAC�Ĵ��� */

    /*  ��̫��MAC���� */
    /* ������̫��MAC���üĴ��������û�������ģʽ */
    u32Temp = HWREG32(u32Base + ETH_MACCR);
    // Clear WD, PCE, PS, TE and RE bits
    u32Temp &= 0xFF20810F;
    u32Temp |= (uint32)(0x00000000 |    //  ���رտ��Ź�
                        0x00000000 |    //  ���رՆ��¶�ʱ��
                        0x00000000 |    //  ��������֮֡�����̼�϶Ϊ96λ��ʱ��
                        0x00000000 |    //  ���ر��ز���������
                        0x00000000 |    //�����ر��Խ��ܹ��ܣ���ȫ˫��ģʽ��������
                        0x00000000 |    //  ��������ѭ��ģʽ
                        0x00000000 |    //  ���Է��ͳ��Թ��ܣ����ͳ�ͻ������ʱ���ط�
                        0x00000000 |    //  MACת�����е�֡�����ı�֡�����ݣ�����֡�����Ƿ�С��1500�ֽ�
                        0x00000000 |    //  �����˺�����
                        0x00000000      //  MAC�ر�˳�Ӽ���
                        );
#if (TCPIP_CHECKSUM_EN > 0)
    u32Temp |= 0x00000400;                      //  ���ʹ����TCP/IP��Ӳ��У��͹��ܣ�������
#endif

    u32Temp |= u32AutoValue;

    HWREG32(u32Base + ETH_MACCR) = u32Temp;    //  д�����ý��

    /* �˲�ģʽ���ã�����̫����������ι��˽������ݵ�MAC��ַ */
    HWREG32(u32Base + ETH_MACFFR) = (0x00000000 |   //  ��ֹ����ȫ�����ܣ�������MAC��ַ����
                                 0x00000000 |   //  ����HASH������������λΪ0�������Ͳ�������������
                                 0x00000000 |   //  Դ��ַ���˽���
                                 0x00000040 |   //  MACת�����еĿ���֡��Ӧ�ó���
                                 0x00000000 |   //  �������еĹ㲥֡ͨ��
                                 0x00000010 |   //  �������еĶಥ֡�������Ҫ֧��IPv6���ͱ������ø���
                                 0x00000000 |   //  Ŀ�ĵ�ַ��������������
                                 0x00000000 |   //  �ಥHASH���ã����Ĵ�����HMλ
                                 0x00000000 |   //  ����HASH���ã����Ĵ�����HUλ
                                 0x00000000     //  ����ģʽ���ã�ʹ�ܽ��ܹ���
                                );
    /* ����HASH�б�Ĵ��� */
    HWREG32(u32Base + ETH_MACHTHR) = 0x00000000;
    HWREG32(u32Base + ETH_MACHTLR) = 0x00000000;

    /* ������̫��MAC���ؼĴ��� */
    u32Temp = HWREG32(u32Base + ETH_MACFCR);
    u32Temp &= 0x0000FF41;                       //  ��ձ�Ҫ��λ
    u32Temp |= ((0x00 << 16) |                   //  PAUSEʱ��
               0x00000080   |                   //  �ر��Զ���ֵPAUSE֡���Զ�����
               0x00000000   |                   //  Pauseʱ��Ϊ4ʱ���϶
               0x00000000   |                   //  ����Pause֡���
               0x00000000   |                   //  �رս�������
               0x00000000                       //  �رշ�������
                );
    HWREG32(u32Base + ETH_MACFCR) = u32Temp;

    /* ����VLAN  */
    HWREG32(u32Base + ETH_MACVLANTR) = 0x00000000;

    /* DMA���ã�����DMA�Ŀ������Ĺ���ģʽ */
    /* ��̫��DMA OMR�Ĵ������� */
    u32Temp = HWREG32(u32Base + ETH_DMAOMR);
    u32Temp &= 0xF8DE3F23;                       //  �����Ҫ��λ����������
    u32Temp |= (0x00000000 |                     //  ��������TCP/IP��CRCУ������֡
               0x02000000 |                     //  ���ý��ܴ洢ת��
               0x00000000 |                     //  ��ս���֡���Դ���FIFO���
               0x00200000 |                     //  ���÷��ʹ洢ת��
               0x00000000 |                     //  ���ͷ�ֵ���ƣ�ֻ��TSFλΪ0ʱ��Ч��������Ч
               0x00000000 |                     //  ���������֡
               0x00000000 |                     //  �������Ȳ�����֡������������֡
               0x00000000 |                     //  ���ܷ�ֵ���ƣ�ֻ����RSFΪ0ʱ��Ч��������Ч
               0x00000004                       //  ��������һ֡
                );
    HWREG32(u32Base + ETH_DMAOMR) = u32Temp;

    /*  ����DMA BMR�Ĵ��� */
    HWREG32(u32Base + ETH_DMABMR) =(0x02000000 |   //  �����ַ����
                                    0x00010000 |   //  �̶�����ͻ��
                                    0x00400000 |   //  /* !! if 4xPBL is selected for Tx or Rx it is applied for the other */
                                    0x00002000 |
                                   (0x00000000 << 2) |   //  ��������Ծ����
                                    0x00004000 |   //  DMA�ٲ�����
                                    0x00800000     // Use separate PBL
                                );
#if (ENHANCED_DMA_DESCRIPTORS_EN > 0)
    /* Enable the Enhanced DMA descriptors */
    HWREG32(u32Base + ETH_DMABMR)  |= (uint32)0x00000080;
#endif /* ENHANCED_DMA_DESCRIPTORS_EN */

#if 0
    // ����PHY�жϣ���Э������ж�
    u32Temp = EthernetPHYRead(u32Base, PHYAddress, 30);
    u32Temp |= 0x0040;
    EthernetPHYWrite(u32Base, PHYAddress, 30, u32Temp);
#endif
}

/*********************************************************************************************************
** Function name:       EthernetPHYIntISR
** Descriptions:        PHY�ж��е��øú�������������PHY��MAC
** input parameters:    u32Base:        ��̫��ģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetPHYIntISR(uint32 u32Base)
{
    uint32 u32Temp;
    uint32 u32PhyRegValue;
    uint32 u32AutoValue;

    u32Temp = HWREG32(u32Base + ETH_MACCR);

    // ���10M/100M��־�Ͱ�˫����ȫ˫���ı�־λ
    u32Temp &= ~((uint32)0x00004800);

     //  ��ȡ�ж�״̬
    u32PhyRegValue = EthernetPHYRead(u32Base, PHYAddress, 29);
    // �����Э������жϲ���
    if((u32PhyRegValue & 0x0040)) {
//      while(!((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0004)));
//      while(!((EthernetPHYRead(u32Base, PHYAddress, 1) & 0x0020)));
        //  ��ȡ��Э�̵Ľ��
        u32PhyRegValue = EthernetPHYRead(u32Base, PHYAddress, 0);

        if (u32PhyRegValue & 0x0100) {
            //  ȫ˫��ͨ��ģʽ
            u32AutoValue = 0x00000800;
        } else {
            //  ��˫��ͨ��ģʽ
            u32AutoValue = 0x00000000;
        }

        if (u32PhyRegValue & 0x2000) {
            //  100M��̫��ͨ��ģʽ
            u32AutoValue |= 0x00004000;
        } else {
            //  10M��̫��ͨ��ģʽ
            u32AutoValue |= 0x00000000;
        }

        u32Temp |= u32AutoValue;
        HWREG32(u32Base + ETH_MACCR) = u32Temp;
    }
}
/*********************************************************************************************************
** Function name:       EthernetPHYRead
** Descriptions:        ��ȡָ����ַ��PHY�Ĵ���
** input parameters:    u32Base:        ��̫��ģ�����ַ
**                      u8PHYDevAddr:   PHY�����ĵ�ַ
**                      u8PHYRegAddr:   PHY�Ĵ����ĵ�ַ
** output parameters:   NONE
** Returned value:      ��ȡ��PHY�Ĵ���������
*********************************************************************************************************/
uint32 EthernetPHYRead(uint32 u32Base, uint8 u8PHYDevAddr, uint8 u8PHYRegAddr)
{
    uint32 u32Temp;

    //  �ȴ�MAC MII��ַ�Ĵ�����MAC MII���ݼĴ�����д
    while(HWREG32(u32Base + ETH_MACMIIAR) & 0x01);

    u32Temp = HWREG32(u32Base + ETH_MACMIIAR);
    u32Temp &= ~(0xFFFFFFE3);                               // ��������CR[2:0]������λ����
    u32Temp |= (((uint32)u8PHYDevAddr << 11) & 0x0000F800); //  дPHY������ַ
    u32Temp |= (((uint32)u8PHYRegAddr << 6)  & 0x000007C0); //  дPHY�Ĵ�����ַ
    u32Temp &= ~(0x00000002);                               //  ����Ϊ��PHY�Ĵ���ģʽ
    u32Temp |= 0x00000001;                                  //  ����MIIæ����ʼ������
    HWREG32(u32Base + ETH_MACMIIAR) = u32Temp;

    //  �ȶ�PHY�Ĵ����������
    while(HWREG32(u32Base + ETH_MACMIIAR) & 0x01);
    return (HWREG32(u32Base + ETH_MACMIIDR) & 0xFFFF);
}

/*********************************************************************************************************
** Function name:       EthernetPHYRead
** Descriptions:        ��ȡָ����ַ��PHY�Ĵ���
** input parameters:    u32Base:        ��̫��ģ�����ַ
**                      u8PHYDevAddr:   PHY�����ĵ�ַ
**                      u8PHYRegAddr:   PHY�Ĵ����ĵ�ַ
**                      u32Data:        д��ָ��PHY�Ĵ���������
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetPHYWrite(uint32 u32Base, uint8 u8PHYDevAddr, uint8 u8PHYRegAddr, uint32 u32Data)
{
    uint32 u32Temp;

    //  �ȴ�MAC MII��ַ�Ĵ�����MAC MII���ݼĴ�����д
    while(HWREG32(u32Base + ETH_MACMIIAR) & 0x01);

    u32Temp = HWREG32(u32Base + ETH_MACMIIAR);
    u32Temp &= ~(0xFFFFFFE3);                               // ��������CR[2:0]������λ����
    u32Temp |= (((uint32)u8PHYDevAddr << 11) & 0x0000F800); //  дPHY������ַ
    u32Temp |= (((uint32)u8PHYRegAddr << 6)  & 0x000007C0); //  дPHY�Ĵ�����ַ
    u32Temp |= 0x00000002;                                  //  ����Ϊ��PHY�Ĵ���ģʽ
    u32Temp |= 0x00000001;                                  //  ����MIIæ����ʼ������
    HWREG32(u32Base + ETH_MACMIIDR) = u32Data;
    HWREG32(u32Base + ETH_MACMIIAR) = u32Temp;

    //  �ȶ�PHY�Ĵ����������
    while(HWREG32(u32Base + ETH_MACMIIAR) & 0x01);
}

/*********************************************************************************************************
** Function name:       EthernetEnable
** Descriptions:        ʹ����̫�����������������ͺͽ��ܵ�
** input parameters:    u32Base      ��̫��ģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetEnable(uint32 u32Base)
{
    HWREG32(u32Base + ETH_MACCR) |= 0x00000008;     //  ʹ��MAC����״̬��
    HWREG32(u32Base + ETH_DMAOMR) |= 0x00100000;    //  ��շ���FIFO
    HWREG32(u32Base + ETH_MACCR) |= 0x00000004;     //  ʹ��MAC����״̬��
    HWREG32(u32Base + ETH_DMAOMR) |= 0x00002000;    //  ����DMA����
    HWREG32(u32Base + ETH_DMAOMR) |= 0x00000002;    //  ����DMA����
}

/*********************************************************************************************************
** Function name:       EthernetMACAddrSet
** Descriptions:        ������̫����MAC��ַ���������ʹ��MAC0��MAC1-MAC3��ʹ��
** input parameters:    u32Base      ��̫��ģ�����ַ
**                      pu8MacAddr  ��Ҫ�趨��MAC��ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetMACAddrSet(uint32 u32Base, uint8 *pu8MacAddr)
{
    uint32 u32Temp;

    u32Temp = (((uint32)pu8MacAddr[5] << 8) | (uint32)pu8MacAddr[4]);
    HWREG32(u32Base + ETH_MACA0HR) = u32Temp;

    u32Temp = (((uint32)pu8MacAddr[3] << 24) | ((uint32)pu8MacAddr[2] << 16) |
             ((uint32)pu8MacAddr[1] << 8) | (uint32)pu8MacAddr[0]);

    HWREG32(u32Base + ETH_MACA0LR) = u32Temp;
}

/*********************************************************************************************************
** Function name:       EthernetMACAddrGet
** Descriptions:        ��ȡ��̫����MAC��ַ���������ʹ��MAC0��MAC1-MAC3��ʹ��
** input parameters:    u32Base      ��̫��ģ�����ַ
**                      pu8MacAddr  ��ȡ��MAC��ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetMACAddrGet(uint32 u32Base, uint8 *pu8MacAddr)
{
    uint32 u32Temp;

    u32Temp = HWREG32(u32Base + ETH_MACA0HR);
    pu8MacAddr[5] = ((u32Temp >> 8) & (uint8)0xFF);
    pu8MacAddr[4] = (u32Temp & (uint8)0xFF);

    u32Temp = HWREG32(u32Base + ETH_MACA0LR);
    pu8MacAddr[3] = ((u32Temp >> 24) & (uint8)0xFF);
    pu8MacAddr[2] = ((u32Temp >> 16) & (uint8)0xFF);
    pu8MacAddr[1] = ((u32Temp >> 8 ) & (uint8)0xFF);
    pu8MacAddr[0] = (u32Temp & (uint8)0xFF);
}

/*********************************************************************************************************
** Function name:       EthernetReset
** Descriptions:        �����λ��̫��������
** input parameters:    u32Base          ��̫��ģ�����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetReset(uint32 u32Base)
{
    HWREG32(u32Base + ETH_DMABMR) |= 0x00000001;
}
/*********************************************************************************************************
** Function name:       EthernetResetStatusGet
** Descriptions:        �ж���̫���������Ƿ��ڸ�λ״̬
** input parameters:    u32Base          ��̫��ģ�����ַ
** output parameters:   NONE
** Returned value:      true:  ��̫�����������ڸ�λ״̬
**                      false����̫����������λ���
*********************************************************************************************************/
boolean EthernetResetStatusGet(uint32 u32Base)
{
    if((HWREG32(u32Base + ETH_DMABMR)) & 0x00000001)
        return true;
    else
        return false;
}
/*********************************************************************************************************
** Function name:       EthernetDMAIntEnable
** Descriptions:        ʹ����̫����������DMA�ж�
** input parameters:    u32Base          ��̫��ģ�����ַ
**                      u32Config        ʹ�ܵ��ж�Դ������ȡ����ֵ������ֵ�Ļ�
**                      DMA_INTRUPT_NISE    //  �����жϻ���ʹ��
**                      DMA_INTRUPT_AISE    //  �쳣�жϻ���ʹ��
**                      DMA_INTRUPT_ERS     //  ������ж�ʹ��
**                      DMA_INTRUPT_FBES    //  �������������ж�ʹ��
**                      DMA_INTRUPT_ETIE    //  �緢���ж�ʹ��
**                      DMA_INTRUPT_RWITE   //  ���ܿ��Ź���ʱ�ж�ʹ��
**                      DMA_INTRUPT_RPSIE   //  ��������ֹͣ�ж�ʹ��
**                      DMA_INTRUPT_RBUIE   //  ���ܻ��治�����ж�ʹ��
**                      DMA_INTRUPT_RIE     //  �����ж�ʹ��
**                      DMA_INTRUPT_TUIE    //  ���������ж�ʹ��
**                      DMA_INTRUPT_ROIE    //  �����洦�ж�ʹ��
**                      DMA_INTRUPT_TITIE   //  ���͆��³�ʱ�ж�ʹ��
**                      DMA_INTRUPT_TBUIE   //  ���ͻ��治�����ж�ʹ��
**                      DMA_INTRUPT_TPSIE   //  ��������ֹͣ�ж�ʹ��
**                      DMA_INTRUPT_TIE     //  �����ж�ʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetDMAIntEnable(uint32 u32Base, uint32 u32Config)
{
    HWREG32(u32Base + ETH_DMAIER) |= u32Config;
}

/*********************************************************************************************************
** Function name:       EthernetDMAIntDisable
** Descriptions:        ������̫����������DMA�ж�
** input parameters:    u32Base          ��̫��ģ�����ַ
**                      u32Config        ���ܵ��ж�Դ������ȡ����ֵ������ֵ�Ļ�
**                      DMA_INTRUPT_NISE    //  �����жϻ���ʹ��
**                      DMA_INTRUPT_AISE    //  �쳣�жϻ���ʹ��
**                      DMA_INTRUPT_ERS     //  ������ж�ʹ��
**                      DMA_INTRUPT_FBES    //  �������������ж�ʹ��
**                      DMA_INTRUPT_ETIE    //  �緢���ж�ʹ��
**                      DMA_INTRUPT_RWITE   //  ���ܿ��Ź���ʱ�ж�ʹ��
**                      DMA_INTRUPT_RPSIE   //  ��������ֹͣ�ж�ʹ��
**                      DMA_INTRUPT_RBUIE   //  ���ܻ��治�����ж�ʹ��
**                      DMA_INTRUPT_RIE     //  �����ж�ʹ��
**                      DMA_INTRUPT_TUIE    //  ���������ж�ʹ��
**                      DMA_INTRUPT_ROIE    //  �����洦�ж�ʹ��
**                      DMA_INTRUPT_TITIE   //  ���͆��³�ʱ�ж�ʹ��
**                      DMA_INTRUPT_TBUIE   //  ���ͻ��治�����ж�ʹ��
**                      DMA_INTRUPT_TPSIE   //  ��������ֹͣ�ж�ʹ��
**                      DMA_INTRUPT_TIE     //  �����ж�ʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void EthernetDMAIntDisable(uint32 u32Base, uint32 u32Config)
{
    HWREG32(u32Base + ETH_DMAIER) &= ~u32Config;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
