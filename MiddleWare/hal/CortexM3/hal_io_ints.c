/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           hal_io_ints.c
** Last modified Date:  2013-04-01
** Last Version:        v1.00
** Description:         �ж���غ���ʵ��
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo
** Created date:        2013-04-01
** Version:             v1.00
** Descriptions:        
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Description:         
*********************************************************************************************************/
#include "infra/rhb_type.h"
#include "hal/CortexM3/hal_io_ints.h"
#include "hal/arch/inc/arch_io_ints.h"

/*********************************************************************************************************
  ȫ�ֱ������� 
*********************************************************************************************************/
// �ж��������壬�ñ���Ҫ����RAM��ʼ��ַ
static __no_init void (*__GfnRAMVectors[ARCH_NUM_INTERRUPTS])(void) @ "VTABLE";
// �ж����ȼ�����ֵ����
static const uint32 __GpulPriority[] =
{
    HAL_NVIC_APINT_PRIGROUP_0_8, HAL_NVIC_APINT_PRIGROUP_1_7, HAL_NVIC_APINT_PRIGROUP_2_6,
    HAL_NVIC_APINT_PRIGROUP_3_5, HAL_NVIC_APINT_PRIGROUP_4_4, HAL_NVIC_APINT_PRIGROUP_5_3,
    HAL_NVIC_APINT_PRIGROUP_6_2, HAL_NVIC_APINT_PRIGROUP_7_1
};


/*********************************************************************************************************
** Function name:       IntDefaultHandler
** Descriptions:        Ĭ�ϵ��жϷ���������
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
static void IntDefaultHandler(void)
{
    // ������ѭ��
    while(1)
    {
    }
}
/*********************************************************************************************************
** Function name:       hal_int_register
** Descriptions:        ע���жϷ�����
** input parameters:    u32IntNo:   �жϷ�����
**                      pfnHandler: ��ע����жϷ�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_register(uint32 u32IntNo, void (*pfnHandler)(void))
{
    uint32 i;
    uint32 u32Temp;
    
    if(HWREG32(HAL_NVIC_VTABLE) != (uint32)__GfnRAMVectors) {
        // ��Flash�е��������Ƶ�RAM������������
        u32Temp = HWREG32(HAL_NVIC_VTABLE);
        for(i=0; i<ARCH_NUM_INTERRUPTS; i++) {
            __GfnRAMVectors[i] = (void (*)(void))HWREG32((i * 4) + u32Temp);
        }
        // ������ϣ���������ӳ�䵽RAM��
        HWREG32(HAL_NVIC_VTABLE) = (uint32)__GfnRAMVectors;
    }
    
    // ע���жϷ�����
    __GfnRAMVectors[u32IntNo] = pfnHandler;
}

/*********************************************************************************************************
** Function name:       hal_int_unregister
** Descriptions:        ע���жϷ�����
** input parameters:    u32IntNo:   �жϷ�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_unregister(uint32 u32IntNo)
{
    __GfnRAMVectors[u32IntNo] = IntDefaultHandler;
}

/*********************************************************************************************************
** Function name:       hal_int_enable
** Descriptions:        ʹ���ж�
** input parameters:    u32IntNo:   �жϷ�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_enable(uint32 u32IntNo)
{
    // ������ڲ��ж�
    if(u32IntNo < 16) {
        if(u32IntNo == HAL_INT_MPU){
            // Enable the MemManage interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) |= HAL_NVIC_SYS_HND_CTRL_MEM;
        } else if(u32IntNo == HAL_INT_BUS) {
            // Enable the bus fault interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) |= HAL_NVIC_SYS_HND_CTRL_BUS;
        } else if(u32IntNo == HAL_INT_USAGE) {
            // Enable the usage fault interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) |= HAL_NVIC_SYS_HND_CTRL_USAGE;
        } else if(u32IntNo == HAL_INT_SYSTICK) {
            // Enable the System Tick interrupt.
            HWREG32(HAL_NVIC_ST_CTRL) |= HAL_NVIC_ST_CTRL_INTEN;
        }
        return;
    }
    
    if(u32IntNo > 255) {
        return;
    }
    u32IntNo -= HAL_EXTERN_INT_BASE;
    HWREG32(HAL_NVIC_EN_BASE + ((u32IntNo / 32) * 4)) |= (1 << (u32IntNo % 32));
}

/*********************************************************************************************************
** Function name:       hal_int_disable
** Descriptions:        ��ֹ�ж�
** input parameters:    u32IntNo:   �жϷ�����
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_disable(uint32 u32IntNo)
{
    // ������ڲ��ж�
    if(u32IntNo < 16) {
        if(u32IntNo == HAL_INT_MPU){
            // Enable the MemManage interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) &= ~HAL_NVIC_SYS_HND_CTRL_MEM;
        } else if(u32IntNo == HAL_INT_BUS) {
            // Enable the bus fault interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) &= ~HAL_NVIC_SYS_HND_CTRL_BUS;
        } else if(u32IntNo == HAL_INT_USAGE) {
            // Enable the usage fault interrupt.
            HWREG32(HAL_NVIC_SYS_HND_CTRL) &= ~HAL_NVIC_SYS_HND_CTRL_USAGE;
        } else if(u32IntNo == HAL_INT_SYSTICK) {
            // Enable the System Tick interrupt.
            HWREG32(HAL_NVIC_ST_CTRL) &= ~HAL_NVIC_ST_CTRL_INTEN;
        }
        return;
    }
    
    if(u32IntNo > 255) {
        return;
    }
    
    u32IntNo -= HAL_EXTERN_INT_BASE;
    HWREG32(HAL_NVIC_DIS_BASE + ((u32IntNo / 32) * 4)) |= (1 << (u32IntNo % 32));
}

/*********************************************************************************************************
** Function name:       hal_int_priority_group_set
** Descriptions:        �����ж����ȼ�����
** input parameters:    u32Bits:   ����ռ���ȼ�ռ�õ�λ��
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_priority_group_set(uint32 u32Bits)
{
    HWREG32(HAL_NVIC_APINT) = HAL_NVIC_APINT_VECTKEY | __GpulPriority[u32Bits];
}

/*********************************************************************************************************
** Function name:       hal_int_priority_group_get
** Descriptions:        ��ȡ�ж����ȼ�����
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      ����ռ���ȼ�ռ�õ�λ��
*********************************************************************************************************/
uint32 hal_int_priority_group_get(uint32 u32Bits)
{
    uint32 u32Temp, i;
    
    u32Temp = HWREG32(HAL_NVIC_APINT) & HAL_NVIC_APINT_PRIGROUP_M;
    for(i=0; i<ARCH_NUM_PRIORITY; i++) {
        if(u32Temp == __GpulPriority[i]) {
            break;
        }
    }
    
    return i;
}

/*********************************************************************************************************
** Function name:       hal_int_priority_set
** Descriptions:        �����ж����ȼ�
** input parameters:    u32IntNo:   �жϱ��
**                      u8Priority: �����õ��ж����ȼ�
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void hal_int_priority_set(uint32 u32IntNo, uint8 u8Priority)
{
    // �ú����������ں˵��жϣ��������ô���16���ⲿ�ж�
    if((u32IntNo < 16) || (u32IntNo > 255)) {
        return;
    }
    u32IntNo -= HAL_EXTERN_INT_BASE;
    HWREG8(HAL_NVIC_PRI_BASE + u32IntNo) = u8Priority;
}

/*********************************************************************************************************
** Function name:       hal_int_priority_get
** Descriptions:        ��ȡ�ж����ȼ�
** input parameters:    u32IntNo:   �жϱ��
** output parameters:   NONE
** Returned value:      ��ȡ���ж����ȼ�
*********************************************************************************************************/
uint8 hal_int_priority_get(uint32 u32IntNo)
{
    // �ú����������ں˵��жϣ��������ô���16���ⲿ�ж�
    if((u32IntNo < 16) || (u32IntNo > 255)) {
        return 0;
    }
    u32IntNo -= HAL_EXTERN_INT_BASE;
    return (HWREG8(HAL_NVIC_PRI_BASE + u32IntNo));
}
/*********************************************************************************************************
END FILE
*********************************************************************************************************/