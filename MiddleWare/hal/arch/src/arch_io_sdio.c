/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           arch_io_sdio.c
** Last modified Date:  2013-05-21
** Last Version:        v1.0
** Description:         SDIOģ��Ĵ�����װ����ʵ��
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2013-05-21
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
#include "hal/arch/inc/arch_io_sdio.h"

/*========================================================================================================
                        Initialization and Configuration functions
========================================================================================================*/

/*********************************************************************************************************
** Function name:       SdioInit
** Descriptions:        SDIOģ���ʼ������
** input parameters:    u32Base:  SDIO����ַ
**                      u32Config: ���ò���������ȡ���м�������Ļ�
**                      sdio ʱ�ӵĲ���ԭ��
**                      SDIO_CLOCK_EDGE_RISING          // SDIO CLK�����ز���
**                      SDIO_CLOCK_EDGE_FALLING         // SDIO CLK�½��ز���
**                      SDIOʱ�ӷ�Ƶ�Ƿ���·
**                      SDIO_CLOCK_BYPASS_DISABLE       // Clock��·��ֹ
**                      SDIO_CLOCK_BYPASS_ENABLE        // Clock��·ʹ��
**                      SDIO�Ƿ���ʡ��ģʽ
**                      SDIO_POWER_SAVE_DISABLE         // ʡ��ģʽ��ֹ
**                      SDIO_POWER_SAVE_ENABLE          // ʡ��ģʽʹ��
**                      SDIO���߿��
**                      SDIO_BUS_WIDE_1B                // 1λ���ݿ��
**                      SDIO_BUS_WIDE_4B                // 4λ���ݿ��
**                      SDIO_BUS_WIDE_8B                // 8λ���ݿ��
**                      SDIO ����
**                      SDIO_HW_FLOW_CTRL_DISABLE       // ���ؽ�ֹ
**                      SDIO_HW_FLOW_CTRL_ENABLE        // ����ʹ��
**                      SDIO��Ƶϵ��
**                      SDIO_CLOCK_DIV_NUM(x)           // ��Ƶϵ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioInit(uint32 u32Base, uint32 u32Config)
{
    uint32 u32Temp;
    
    u32Temp = HWREG32(u32Base + SDIO_CLKCR);
    u32Temp &= ((uint32)0xFFFF8100);
    u32Temp |= u32Config;
    HWREG32(u32Base + SDIO_CLKCR) = u32Temp;
}

/*********************************************************************************************************
** Function name:       SdioEnable
** Descriptions:        SDIOģ��ʹ�ܣ�ʹ�ܺ�ʼ����
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioEnable(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_CLKCR) |= ((uint32)0x000000100);
}

/*********************************************************************************************************
** Function name:       SdioDisable
** Descriptions:        SDIOģ���ֹ����ֹ��ֹͣ����
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioDisable(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_CLKCR) &= ~((uint32)0x000000100);
}

/*********************************************************************************************************
** Function name:       SdioPowerOn
** Descriptions:        SDIO��Դ���ơ���
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioPowerOn(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_POWER) |= ((uint32)0x000000003);
}

/*********************************************************************************************************
** Function name:       SdioPowerOff
** Descriptions:        SDIO��Դ���ơ��ر�
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioPowerOff(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_POWER) &= ~((uint32)0x000000003);
}

/*********************************************************************************************************
** Function name:       SdioPowerStatus
** Descriptions:        SDIO��Դz״̬
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      true: ��״̬�� false���ر�״̬
*********************************************************************************************************/
boolean SdioPowerStatus(uint32 u32Base)
{
  return (((HWREG32(u32Base + SDIO_POWER) & ((uint32)0x000000003)) == ((uint32)0x000000003)) ?true:false);
}
/*========================================================================================================
                    Command path state machine (CPSM) management functions
========================================================================================================*/
/*********************************************************************************************************
** Function name:       SdioCMDSend
** Descriptions:        SDIO��������
** input parameters:    u32Base:            SDIO����ַ
**                      u32SdioArg:         �������
**                      uint32SendConfig:   ���͵����ò���, ����ȡ���м�������Ļ�
**                      �����
**                      SDIO_CMD_INDEX(x)           // �����

**                      ��Ӧ����
**                      SDIO_RESPONSE_NO            // �޻�Ӧ
**                      SDIO_RESPONSE_SHORT         // �̻�Ӧ
**                      SDIO_RESPONSE_LONG          // ����Ӧ

**                      SDIO�ȴ�����
**                      SDIO_WAIT_NO                // �޵ȴ�
**                      SDIO_WAIT_INT               // �ȴ��ж�
**                      SDIO_WAIT_PEND              // �ȴ��������

**                      SDIO CPSM״̬
**                      SDIO_CPSM_DISABLE           // CPSM��ֹ
**                      SDIO_CPSM_ENABLE            // CPSMʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioCMDSend(uint32 u32Base, uint32 u32SdioArg, uint32 u32SendConfig)
{
    uint32 u32Temp;
    
    HWREG32(u32Base + SDIO_ARG) = u32SdioArg;
    
    u32Temp = HWREG32(u32Base + SDIO_CMD);
    u32Temp &= ((uint32)0xFFFFF800);
    u32Temp |= u32SendConfig;
    HWREG32(u32Base + SDIO_CMD) = u32Temp;
}

/*********************************************************************************************************
** Function name:       SdioCommandResponseGet
** Descriptions:        ��ȡ��һ�ε������Ӧ
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      Returns command index of last command for which response received.
*********************************************************************************************************/
uint8 SdioCommandResponseGet(uint32 u32Base)
{
    return ((uint8)HWREG32(u32Base + SDIO_RESPCMD));
}

/*********************************************************************************************************
** Function name:       SdioResponseGet
** Descriptions:        ��ȡ��һ�ε������Ӧ
** input parameters:    u32Base:  SDIO����ַ
**                      u32RESP:  ��ȡ��RESP�Ĵ���,����ȡ����ֵ��
**                      SDIO_RESP1          // RESP1�Ĵ���
**                      SDIO_RESP2          // RESP2�Ĵ���
**                      SDIO_RESP3          // RESP3�Ĵ���
**                      SDIO_RESP4          // RESP4�Ĵ���
** output parameters:   NONE
** Returned value:      ���ػ�Ӧֵ
*********************************************************************************************************/
uint32 SdioResponseGet(uint32 u32Base, uint32 u32RESP)
{
    return (HWREG32(u32Base + SDIO_RESP_BASE + u32RESP));
}

/*========================================================================================================
                    Data path state machine (DPSM) management functions
========================================================================================================*/

/*********************************************************************************************************
** Function name:       SdioDataConfigSet
** Descriptions:        ��ʼ��SDIO Data Path
** input parameters:    u32Base:        SDIO����ַ
**                      u32DataTimeOut: SDIO Data TimeOut value
**                      u32DataLen:     SDIO DataLength value
**                      u32DataCtrl:    SDIO DCTRL value, ����ȡ���м�������Ļ�
**                      SDIO���ݿ��С
**                      SDIO_DATABLOCK_SIZE_1B          // 1���ֽ�
**                      SDIO_DATABLOCK_SIZE_2B          // 2���ֽ�
**                      SDIO_DATABLOCK_SIZE_4B          // 4���ֽ�
**                      SDIO_DATABLOCK_SIZE_8B          // 8���ֽ�
**                      SDIO_DATABLOCK_SIZE_16B         // 16���ֽ�
**                      SDIO_DATABLOCK_SIZE_32B         // 32���ֽ�
**                      SDIO_DATABLOCK_SIZE_64B         // 64���ֽ�
**                      SDIO_DATABLOCK_SIZE_128B        // 128���ֽ�
**                      SDIO_DATABLOCK_SIZE_256B        // 256���ֽ�
**                      SDIO_DATABLOCK_SIZE_512B        // 512���ֽ�
**                      SDIO_DATABLOCK_SIZE_1024B       // 1024���ֽ�
**                      SDIO_DATABLOCK_SIZE_2048B       // 2048���ֽ�
**                      SDIO_DATABLOCK_SIZE_4096B       // 4096���ֽ�
**                      SDIO_DATABLOCK_SIZE_8192B       // 8192���ֽ�
**                      SDIO_DATABLOCK_SIZE_16384B      // 16384���ֽ�
**                      SDIO���ݴ��䷽��
**                      SDIO_TRANSFERDIR_TO_CARD        // ���ݴ���CARD
**                      SDIO_TRANSFERDIR_TO_SDIO        // ���ݴ���SDIO
**                      SDIO��������
**                      SDIO_TRANSFER_MODE_BLOCK        // Blockģʽ
**                      SDIO_TRANSFER_MODE_STREAM       // Streamģʽ
**                      SDIO_DPSM_State 
**                      SDIO_DPSM_DISABLE               // DPSM��ֹ
**                      SDIO_DPSM_ENABLE                // DPSMʹ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioDataConfigInit(uint32 u32Base, uint32 u32DataTimeOut, uint32 u32DataLen, uint32 u32DataCtrl)
{
    uint32 u32Temp;
    
    HWREG32(u32Base + SDIO_DTIMER) = u32DataTimeOut;
    HWREG32(u32Base + SDIO_DLEN) = u32DataLen;
    
    u32Temp = HWREG32(u32Base + SDIO_DCTRL);
    u32Temp &= ((uint32)0xFFFFFF08);
//    HWREG32(u32Base + SDIO_DCTRL) = 0x00000000;
//    u32Temp = 0x00000000;
    u32Temp |= u32DataCtrl;
    HWREG32(u32Base + SDIO_DCTRL) = u32Temp;
}

/*********************************************************************************************************
** Function name:       SdioDataCounterGet
** Descriptions:        ��ȡ�����ʣ����������
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      ʣ�ഫ�����������
*********************************************************************************************************/
uint32 SdioDataCounterGet(uint32 u32Base)
{
    return (HWREG32(u32Base + SDIO_DCOUNT));
}

/*********************************************************************************************************
** Function name:       SdioDataRead
** Descriptions:        SDIO���ݶ�ȡ
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      ��ȡ��������
*********************************************************************************************************/
uint32 SdioDataRead(uint32 u32Base)
{
    return (HWREG32(u32Base + SDIO_FIFO));
}

/*********************************************************************************************************
** Function name:       SdioDataWrite
** Descriptions:        SDIO����д
** input parameters:    u32Base:  SDIO����ַ
**                      u32Data:  д������
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioDataWrite(uint32 u32Base, uint32 u32Data)
{
    HWREG32(u32Base + SDIO_FIFO) = u32Data;
}

/*********************************************************************************************************
** Function name:       SdioFIFOCounterGet
** Descriptions:        ��ȡ�����FIFOʣ������
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      Returns the number of words left to be written to or read from FIFO
*********************************************************************************************************/
uint32 SdioFIFOCounterGet(uint32 u32Base)
{
    return (HWREG32(u32Base + SDIO_FIFOCNT));
}

/*========================================================================================================
                    SDIO IO Cards mode management functions
========================================================================================================*/

/*********************************************************************************************************
** Function name:       SdioReadWaitSdioStart
** Descriptions:        Starts the SD I/O Read Wait operation
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioReadWaitSdioStart(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_DCTRL) |= ((uint32)0x00000100);
    } 
    else {
        HWREG32(u32Base + SDIO_DCTRL) &= ~((uint32)0x00000100);
    }
}

/*********************************************************************************************************
** Function name:       SdioReadWaitSdioStop
** Descriptions:        Stops the SD I/O Read Wait operation.
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioReadWaitSdioStop(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_DCTRL) |= ((uint32)0x00000200);
    } 
    else {
        HWREG32(u32Base + SDIO_DCTRL) &= ~((uint32)0x00000200);
    }
}

/*********************************************************************************************************
** Function name:       SdioReadWaitSdioModeSet
** Descriptions:        Sets one of the two options of inserting read wait interval.
** input parameters:    u32Base:  SDIO����ַ
**                      u32Mode:  �ȴ�ģʽ������ȡ����ֵ��
**                      SDIO_READ_WAIT_MODE_CLK         // Read Wait control using SDIO_CK
**                      SDIO_READ_WAIT_MODE_DATA2       // Read Wait control stopping SDIO_D2
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioReadWaitSdioModeSet(uint32 u32Base, uint32 u32Mode)
{
    HWREG32(u32Base + SDIO_DCTRL) &= ~((uint32)0x00000400);
    HWREG32(u32Base + SDIO_DCTRL) |= u32Mode;
}

/*********************************************************************************************************
** Function name:       SdioOperationSdioSet
** Descriptions:        Enables or disables the SD I/O Mode Operation.
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioOperationSdioSet(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_DCTRL) |= ((uint32)0x00000800);
    } 
    else {
        HWREG32(u32Base + SDIO_DCTRL) &= ~((uint32)0x00000800);
    }
}

/*********************************************************************************************************
** Function name:       SdioSendSDIOSuspendCmd
** Descriptions:        Enables or disables the SD I/O Mode suspend command sending.
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioSendSDIOSuspendCmd(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_CMD) |= ((uint32)0x00000800);
    } 
    else {
        HWREG32(u32Base + SDIO_CMD) &= ~((uint32)0x00000800);
    }
}

/*========================================================================================================
                    CE-ATA mode management functions
========================================================================================================*/
/*********************************************************************************************************
** Function name:       SdioCommandCompletionSet
** Descriptions:        Enables or disables the command completion signal.
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioCommandCompletionSet(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_CMD) |= ((uint32)0x00001000);
    } 
    else {
        HWREG32(u32Base + SDIO_CMD) &= ~((uint32)0x00001000);
    }
}

/*********************************************************************************************************
** Function name:       SdioCEATAIntSet
** Descriptions:        Enables or disables the CE-ATA interrupt.
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioCEATAIntSet(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_CMD) |= ((uint32)0x00002000);
    } 
    else {
        HWREG32(u32Base + SDIO_CMD) &= ~((uint32)0x00002000);
    }
}

/*********************************************************************************************************
** Function name:       SdioSendCEATASet
** Descriptions:        Sends CE-ATA command (CMD61).
** input parameters:    u32Base:  SDIO����ַ
**                      bIsSet:   ����״̬������ȡtrue����false
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioSendCEATASet(uint32 u32Base, boolean bIsSet)
{
    if(true == bIsSet) {
        HWREG32(u32Base + SDIO_CMD) |= ((uint32)0x00004000);
    } 
    else {
        HWREG32(u32Base + SDIO_CMD) &= ~((uint32)0x00004000);
    }
}

/*========================================================================================================
                    DMA transfers management functions
========================================================================================================*/
/*********************************************************************************************************
** Function name:       SdioDmaEnable
** Descriptions:        Enable the SDIO DMA request.
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioDmaEnable(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_DCTRL) |= ((uint32)0x00000008);
}

/*********************************************************************************************************
** Function name:       SdioDmaDisable
** Descriptions:        Disable the SDIO DMA request.
** input parameters:    u32Base:  SDIO����ַ
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioDmaDisable(uint32 u32Base)
{
    HWREG32(u32Base + SDIO_DCTRL) &= ~((uint32)0x00000008);
}

/*========================================================================================================
                    Interrupts and flags management functions
========================================================================================================*/
/*********************************************************************************************************
** Function name:       SdioIntEnable
** Descriptions:        Enable the SDIO interrupts.
** input parameters:    u32Base:    SDIO����ַ
**                      u32IntFlag: ���Ƶ��ж�Դ, ����ȡ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_INT_CCRCFAIL: Command response received (CRC check failed) interrupt
**                      SDIO_INT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
**                      SDIO_INT_CTIMEOUT: Command response timeout interrupt
**                      SDIO_INT_DTIMEOUT: Data timeout interrupt
**                      SDIO_INT_TXUNDERR: Transmit FIFO underrun error interrupt
**                      SDIO_INT_RXOVERR:  Received FIFO overrun error interrupt
**                      SDIO_INT_CMDREND:  Command response received (CRC check passed) interrupt
**                      SDIO_INT_CMDSENT:  Command sent (no response required) interrupt
**                      SDIO_INT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
**                      SDIO_INT_STBITERR: Start bit not detected on all data signals in wide 
  *                                   bus mode interrupt
**                      SDIO_INT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
**                      SDIO_INT_CMDACT:   Command transfer in progress interrupt
**                      SDIO_INT_TXACT:    Data transmit in progress interrupt
**                      SDIO_INT_RXACT:    Data receive in progress interrupt
**                      SDIO_INT_TXFIFOHE: Transmit FIFO Half Empty interrupt
**                      SDIO_INT_RXFIFOHF: Receive FIFO Half Full interrupt
**                      SDIO_INT_TXFIFOF:  Transmit FIFO full interrupt
**                      SDIO_INT_RXFIFOF:  Receive FIFO full interrupt
**                      SDIO_INT_TXFIFOE:  Transmit FIFO empty interrupt
**                      SDIO_INT_RXFIFOE:  Receive FIFO empty interrupt
**                      SDIO_INT_TXDAVL:   Data available in transmit FIFO interrupt
**                      SDIO_INT_RXDAVL:   Data available in receive FIFO interrupt
**                      SDIO_INT_SDIOIT:   SD I/O interrupt received interrupt
**                      SDIO_INT_CEATAEND: CE-ATA command completion signal received for CMD61 interrupt
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioIntEnable(uint32 u32Base, uint32 u32IntFlag)
{
    HWREG32(u32Base + SDIO_MASK) |= u32IntFlag;
}

/*********************************************************************************************************
** Function name:       SdioIntDisable
** Descriptions:        Disable the SDIO interrupts.
** input parameters:    u32Base:    SDIO����ַ
**                      u32IntFlag: ���Ƶ��ж�Դ�� ����ȡ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_INT_CCRCFAIL: Command response received (CRC check failed) interrupt
**                      SDIO_INT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
**                      SDIO_INT_CTIMEOUT: Command response timeout interrupt
**                      SDIO_INT_DTIMEOUT: Data timeout interrupt
**                      SDIO_INT_TXUNDERR: Transmit FIFO underrun error interrupt
**                      SDIO_INT_RXOVERR:  Received FIFO overrun error interrupt
**                      SDIO_INT_CMDREND:  Command response received (CRC check passed) interrupt
**                      SDIO_INT_CMDSENT:  Command sent (no response required) interrupt
**                      SDIO_INT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
**                      SDIO_INT_STBITERR: Start bit not detected on all data signals in wide 
  *                                   bus mode interrupt
**                      SDIO_INT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
**                      SDIO_INT_CMDACT:   Command transfer in progress interrupt
**                      SDIO_INT_TXACT:    Data transmit in progress interrupt
**                      SDIO_INT_RXACT:    Data receive in progress interrupt
**                      SDIO_INT_TXFIFOHE: Transmit FIFO Half Empty interrupt
**                      SDIO_INT_RXFIFOHF: Receive FIFO Half Full interrupt
**                      SDIO_INT_TXFIFOF:  Transmit FIFO full interrupt
**                      SDIO_INT_RXFIFOF:  Receive FIFO full interrupt
**                      SDIO_INT_TXFIFOE:  Transmit FIFO empty interrupt
**                      SDIO_INT_RXFIFOE:  Receive FIFO empty interrupt
**                      SDIO_INT_TXDAVL:   Data available in transmit FIFO interrupt
**                      SDIO_INT_RXDAVL:   Data available in receive FIFO interrupt
**                      SDIO_INT_SDIOIT:   SD I/O interrupt received interrupt
**                      SDIO_INT_CEATAEND: CE-ATA command completion signal received for CMD61 interrupt
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioIntDisable(uint32 u32Base, uint32 u32IntFlag)
{
    HWREG32(u32Base + SDIO_MASK) &= ~u32IntFlag;
}

/*********************************************************************************************************
** Function name:       SdioFlagStatus
** Descriptions:        ��ȡFlag״̬
** input parameters:    u32Base:    SDIO����ַ
** output parameters:   NONE
** Returned value:      flag״ֵ̬��Ϊ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_FLAG_CCRCFAIL: Command response received (CRC check failed)
**                      SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
**                      SDIO_FLAG_CTIMEOUT: Command response timeout
**                      SDIO_FLAG_DTIMEOUT: Data timeout
**                      SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error
**                      SDIO_FLAG_RXOVERR:  Received FIFO overrun error
**                      SDIO_FLAG_CMDREND:  Command response received (CRC check passed)
**                      SDIO_FLAG_CMDSENT:  Command sent (no response required)
**                      SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
**                      SDIO_FLAG_STBITERR: Start bit not detected on all data signals in wide bus mode.
**                      SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
**                      SDIO_FLAG_CMDACT:   Command transfer in progress
**                      SDIO_FLAG_TXACT:    Data transmit in progress
**                      SDIO_FLAG_RXACT:    Data receive in progress
**                      SDIO_FLAG_TXFIFOHE: Transmit FIFO Half Empty
**                      SDIO_FLAG_RXFIFOHF: Receive FIFO Half Full
**                      SDIO_FLAG_TXFIFOF:  Transmit FIFO full
**                      SDIO_FLAG_RXFIFOF:  Receive FIFO full
**                      SDIO_FLAG_TXFIFOE:  Transmit FIFO empty
**                      SDIO_FLAG_RXFIFOE:  Receive FIFO empty
**                      SDIO_FLAG_TXDAVL:   Data available in transmit FIFO
**                      SDIO_FLAG_RXDAVL:   Data available in receive FIFO
**                      SDIO_FLAG_SDIOIT:   SD I/O interrupt received
**                      SDIO_FLAG_CEATAEND: CE-ATA command completion signal received for CMD61
*********************************************************************************************************/
uint32 SdioFlagStatus(uint32 u32Base)
{
    return (HWREG32(u32Base + SDIO_STA));
}

/*********************************************************************************************************
** Function name:       SdioFlagClear
** Descriptions:        ���Flag״̬
** input parameters:    u32Base:    SDIO����ַ
**                      u32Flag: ���Ƶ�Flagֵ ����ȡ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_FLAG_CCRCFAIL: Command response received (CRC check failed)
**                      SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
**                      SDIO_FLAG_CTIMEOUT: Command response timeout
**                      SDIO_FLAG_DTIMEOUT: Data timeout
**                      SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error
**                      SDIO_FLAG_RXOVERR:  Received FIFO overrun error
**                      SDIO_FLAG_CMDREND:  Command response received (CRC check passed)
**                      SDIO_FLAG_CMDSENT:  Command sent (no response required)
**                      SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
**                      SDIO_FLAG_STBITERR: Start bit not detected on all data signals in wide bus mode
**                      SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
**                      SDIO_FLAG_SDIOIT:   SD I/O interrupt received
**                      SDIO_FLAG_CEATAEND: CE-ATA command completion signal received for CMD61
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioFlagClear(uint32 u32Base, uint32 u32Flag)
{
    HWREG32(u32Base + SDIO_ICR) = u32Flag;
}

/*********************************************************************************************************
** Function name:       SdioIntStatus
** Descriptions:        ��ȡInt״̬
** input parameters:    u32Base:    SDIO����ַ
** output parameters:   NONE
** Returned value:      ���ص��ж�״ֵ̬������ȡ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
**                      SDIO_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
**                      SDIO_IT_CTIMEOUT: Command response timeout interrupt
**                      SDIO_IT_DTIMEOUT: Data timeout interrupt
**                      SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt
**                      SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt
**                      SDIO_IT_CMDREND:  Command response received (CRC check passed) interrupt
**                      SDIO_IT_CMDSENT:  Command sent (no response required) interrupt
**                      SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
**                      SDIO_IT_STBITERR: Start bit not detected on all data signals in wide 
  *                                   bus mode interrupt
**                      SDIO_IT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
**                      SDIO_IT_CMDACT:   Command transfer in progress interrupt
**                      SDIO_IT_TXACT:    Data transmit in progress interrupt
**                      SDIO_IT_RXACT:    Data receive in progress interrupt
**                      SDIO_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt
**                      SDIO_IT_RXFIFOHF: Receive FIFO Half Full interrupt
**                      SDIO_IT_TXFIFOF:  Transmit FIFO full interrupt
**                      SDIO_IT_RXFIFOF:  Receive FIFO full interrupt
**                      SDIO_IT_TXFIFOE:  Transmit FIFO empty interrupt
**                      SDIO_IT_RXFIFOE:  Receive FIFO empty interrupt
**                      SDIO_IT_TXDAVL:   Data available in transmit FIFO interrupt
**                      SDIO_IT_RXDAVL:   Data available in receive FIFO interrupt
**                      SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt
**                      SDIO_IT_CEATAEND: CE-ATA command completion signal received for CMD61 interrupt
*********************************************************************************************************/
uint32 SdioIntStatus(uint32 u32Base)
{
    return (HWREG32(u32Base + SDIO_STA));
}

/*********************************************************************************************************
** Function name:       SdioIntClear
** Descriptions:        ���Int״̬
** input parameters:    u32Base:    SDIO����ַ
**                      u32IntFlag: ���Ƶ��ж�Դ������ȡ����ֵ�е�һ���򼸸��Ļ�
**                      SDIO_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
**                      SDIO_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
**                      SDIO_IT_CTIMEOUT: Command response timeout interrupt
**                      SDIO_IT_DTIMEOUT: Data timeout interrupt
**                      SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt
**                      SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt
**                      SDIO_IT_CMDREND:  Command response received (CRC check passed) interrupt
**                      SDIO_IT_CMDSENT:  Command sent (no response required) interrupt
**                      SDIO_IT_DATAEND:  Data end (data counter, SDIO_DCOUNT, is zero) interrupt
**                      SDIO_IT_STBITERR: Start bit not detected on all data signals in wide 
  *                                   bus mode interrupt
**                      SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt
**                      SDIO_IT_CEATAEND: CE-ATA command completion signal received for CMD61
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void SdioIntClear(uint32 u32Base, uint32 u32IntFlag)
{
    HWREG32(u32Base + SDIO_ICR) = u32IntFlag;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
