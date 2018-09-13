/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_spi_bus_adapter.h
** Last modified Date:  2013-07-08
** Last Version:        V1.0
** Description:         SPI���������
**
**--------------------------------------------------------------------------------------------------------
** Created By:          �κ���
** Created date:        2013-07-08
** Version:             V1.0
** Descriptions:        The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/
#include "devs/spi/rhb_spi_bus_adapter.h"

#include "hal/arch/inc/arch_io_memmap.h"
#include "hal/arch/inc/arch_io_reg.h"
#include "hal/arch/inc/arch_io_rcc.h"
#include "hal/arch/inc/arch_io_gpio.h"
#include "hal/arch/inc/arch_io_spi.h"

#include "hal/CortexM3/hal_io_level.h"

#include "contiki/stm32_def.h"

/*********************************************************************************************************
** �ֲ���������
*********************************************************************************************************/
static void spi_bus_init(struct rhb_spi_bus *bus);
static void spi_bus_lock(struct rhb_spi_bus *bus);
static void spi_bus_unlock(struct rhb_spi_bus *bus);
static uint8 spi_bus_send_recv_byte(struct rhb_spi_bus *bus, uint8 Data);
static boolean spi_bus_is_busy(struct rhb_spi_bus *bus);
static void spi_bus_flush(struct rhb_spi_bus *bus);

/*********************************************************************************************************
** ����SPI������������ӿ�
*********************************************************************************************************/
rhb_spi_bus __GtSpiBusDriver = {
  .int_state = 0,
  .spi_bus_init = spi_bus_init,
  .spi_bus_lock = spi_bus_lock,
  .spi_bus_unlock = spi_bus_unlock,
  .spi_bus_send_recv_byte = spi_bus_send_recv_byte,
  .spi_bus_is_busy = spi_bus_is_busy,
  .spi_bus_flush = spi_bus_flush
};

/*********************************************************************************************************
** Function name:       spi_bus_init
** Descriptions:        SPI����Ӳ����ʼ��
** input parameters:    bus: SPI���߿�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
static void spi_bus_init(struct rhb_spi_bus *bus)
{
    SystemPeripheralEnable(RCC_PERIPHERAL_IOPA);
    SystemPeripheralEnable(RCC_PERIPHERAL_SPI1);
    
    // CLK��MOSI��Ƭѡ����SS��������Ϊ���츴�����
    GPIOConfigSet(GPIOA_BASE, GPIO_PIN_5 | GPIO_PIN_7, GPIO_AF_PP | GPIO_SPEED_50MHZ);
    // MISO����Ϊ��������
    GPIOConfigSet(GPIOA_BASE, GPIO_PIN_6, GPIO_DIR_IN_Floating);

    // ��ʼSPI�ӿ�
    SPIInit(SPI1_BASE, SPI_DIR_2Lines_FullDuplex | SPI_MODE_Master |
                       SPI_DATA_Len8 | SPI_CPOL_Low | SPI_CPHA_1Edge |
                       SPI_NSS_Soft | SPI_Baud_Prescaler_32 | SPI_First_MSB);
    SPI_SSOutEnable(SPI1_BASE);
    SPIEnable(SPI1_BASE);
}

/*********************************************************************************************************
** Function name:       spi_bus_init
** Descriptions:        �������ߣ�������̲߳����ĳ�ͻ
** input parameters:    bus: SPI���߿�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
static void spi_bus_lock(struct rhb_spi_bus *bus)
{
    bus->int_state = hal_enter_critical(1);
}

/*********************************************************************************************************
** Function name:       spi_bus_unlock
** Descriptions:        �Ӵ��������ߣ�����SPI�豸����ʹ��������
** input parameters:    bus: SPI���߿�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
static void spi_bus_unlock(struct rhb_spi_bus *bus)
{
   hal_exit_critical(bus->int_state);
}
/*********************************************************************************************************
** Function name:       spi_bus_send_recv_byte
** Descriptions:        SPI���߷���ͬʱ����һ���ֽ�
** input parameters:    bus: SPI���߿�����
**                      Data: ���߷��͵�����
** output parameters:   NONE
** Returned value:      ���յ�������
*********************************************************************************************************/
static uint8 spi_bus_send_recv_byte(struct rhb_spi_bus *bus, uint8 Data)
{
  uint8 temp;
  
  // �ȴ����ͼĴ���Ϊ��
  while(!(HWREG32(SPI1_BASE + SPI_O_SR) & 0x02));
  // ��䷢�ͼĴ�������ʼ����
  HWREG32(SPI1_BASE + SPI_O_DR) = Data;
  // �ȴ����ռĴ�������
  while(!(HWREG32(SPI1_BASE + SPI_O_SR) & 0x01));
  // ���ط�������
  temp = HWREG32(SPI1_BASE + SPI_O_DR);

  return temp;
}

/*********************************************************************************************************
** Function name:       spi_bus_is_busy
** Descriptions:        �ж�SPI�����Ƿ�æ
** input parameters:    bus: SPI���߿�����
** output parameters:   NONE
** Returned value:      true: ���߷�æ��false: ���߲�æ
*********************************************************************************************************/
static boolean spi_bus_is_busy(struct rhb_spi_bus *bus)
{
  // �������æ
  if(HWREG32(SPI1_BASE+SPI_O_SR) & 0x80) {
 // if((HWREG32(SPI1_BASE+SPI_O_SR) & 0x01)) {
      return true;
  } else {
      return false;
  }
}

/*********************************************************************************************************
** Function name:       spi_bus_flush
** Descriptions:        ���spi���߽��ռĴ���
** input parameters:    bus: SPI���߿�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
static void spi_bus_flush(struct rhb_spi_bus *bus)
{
  uint8 temp;

  // �ȴ����߲�æ
  while(HWREG32(SPI2_BASE+SPI_O_SR) & 0x80);
  
  if((HWREG32(SPI1_BASE+SPI_O_SR) & 0x01)){
     temp = HWREG32(SPI1_BASE + SPI_O_DR);
     temp = temp;
  }
}

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
