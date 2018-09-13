/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           hal_io_ints.h
** Last modified Date:  2011-04-16
** Last Version:        v1.00
** Description:         �봦�����ܹ�����ж��������
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo
** Created date:        2011-04-16
** Version:             v1.00
** Descriptions:        
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Description:         
*********************************************************************************************************/
#ifndef __HAL_IO_INTS_H__
#define __HAL_IO_INTS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
**  Cortex-M3���ڲ��ж�
*********************************************************************************************************/
#define HAL_INT_NMI             2           // NMI fault
#define HAL_INT_HARD            3           // Hard fault
#define HAL_INT_MPU             4           // MPU fault
#define HAL_INT_BUS             5           // Bus fault
#define HAL_INT_USAGE           6           // Usage fault
#define HAL_INT_SVCALL          11          // SVCall
#define HAL_INT_DEBUG           12          // Debug monitor
#define HAL_INT_PENDSV          14          // PendSV
#define HAL_INT_SYSTICK         15          // System Tick

/*********************************************************************************************************
**  Cortex-M3���ⲿ�ж���ʼ���
*********************************************************************************************************/
#define HAL_EXTERN_INT_BASE     16          // �ⲿ�жϴ�16��ʼ

/*********************************************************************************************************
**  Cortex-M3��NVICģ��Ĵ������壬��������Ĵ�������
*********************************************************************************************************/
// �жϿ������ͼĴ���
#define HAL_NVIC_INT_TYPE           0xE000E004
// ϵͳtick���ƼĴ���
#define HAL_NVIC_ST_CTRL            0xE000E010 
#define HAL_NVIC_ST_RELOAD          0xE000E014
#define HAL_NVIC_ST_CURRENT         0xE000E018
#define HAL_NVIC_ST_CAL             0xE000E01C
// �ж�ʹ�ܼĴ�����ÿһ����Ӧ1λ����7��32λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_EN_BASE            0xE000E100
// �жϽ�ֹ�Ĵ�����ÿһ����Ӧ1λ����7��32λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_DIS_BASE           0xE000E180
// �ж�Pend�Ĵ�����ÿһ����Ӧ1λ����7��32λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_PEND_BASE          0xE000E200
// �ж�unPend�Ĵ�����ÿһ����Ӧ1λ����7��32λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_UNPEND_BASE        0xE000E280
// �жϻ״̬�Ĵ�����ÿһ����Ӧ1λ����7��32λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_ACTIVE_BASE        0xE000E300
// �ж����ȼ��Ĵ�����ÿһ����Ӧ1��8λ�ļĴ�������240��8λ�ļĴ���������ֻ��������ַ
#define HAL_NVIC_PRI_BASE           0xE000E400
// CPU ID�Ĵ���
#define HAL_NVIC_CPUID              0xE000ED00
// �жϿ��Ƽ�״̬�Ĵ���
#define HAL_NVIC_INT_CTRL           0xE000ED04
// �ж�������ƫ�ƼĴ���
#define HAL_NVIC_VTABLE             0xE000ED08
// Ӧ�ó����жϼ���λ���ƼĴ���
#define HAL_NVIC_APINT              0xE000ED0C
// ϵͳ���ƼĴ���
#define HAL_NVIC_SYS_CTRL           0xE000ED10
// ��������ƼĴ���
#define HAL_NVIC_CFG_CTRL           0xE000ED14
// ϵͳ�쳣���ȼ��Ĵ���
#define HAL_NVIC_SYS_PRI1           0xE000ED18  // Sys. Handlers 4 to 7 Priority
#define HAL_NVIC_SYS_PRI2           0xE000ED1C  // Sys. Handlers 8 to 11 Priority
#define HAL_NVIC_SYS_PRI3           0xE000ED20  // Sys. Handlers 12 to 15 Priority
// ϵͳHandler���Ƽ�״̬�Ĵ���SHCSR
#define HAL_NVIC_SYS_HND_CTRL       0xE000ED24
// �����Ĵ���
#define HAL_NVIC_FAULT_STAT         0xE000ED28  // Configurable Fault Status Reg
#define HAL_NVIC_HFAULT_STAT        0xE000ED2C  // Hard Fault Status Register
#define HAL_NVIC_DEBUG_STAT         0xE000ED30  // Debug Status Register
#define HAL_NVIC_MM_ADDR            0xE000ED34  // Mem Manage Address Register
#define HAL_NVIC_FAULT_ADDR         0xE000ED38  // Bus Fault Address Register
#define HAL_NVIC_MPU_TYPE           0xE000ED90  // MPU Type Register
#define HAL_NVIC_MPU_CTRL           0xE000ED94  // MPU Control Register
#define HAL_NVIC_MPU_NUMBER         0xE000ED98  // MPU Region Number Register
#define HAL_NVIC_MPU_BASE           0xE000ED9C  // MPU Region Base Address Register
#define HAL_NVIC_MPU_ATTR           0xE000EDA0  // MPU Region Attribute & Size Reg
#define HAL_NVIC_DBG_CTRL           0xE000EDF0  // Debug Control and Status Reg
#define HAL_NVIC_DBG_XFER           0xE000EDF4  // Debug Core Reg. Transfer Select
#define HAL_NVIC_DBG_DATA           0xE000EDF8  // Debug Core Register Data
#define HAL_NVIC_DBG_INT            0xE000EDFC  // Debug Reset Interrupt Control
#define HAL_NVIC_SW_TRIG            0xE000EF00  // Software Trigger Interrupt Reg

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_INT_TYPE register.
*********************************************************************************************************/
#define HAL_NVIC_INT_TYPE_LINES_M   0x0000001F  // Number of interrupt lines (x32)
#define HAL_NVIC_INT_TYPE_LINES_S   0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_ST_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define HAL_NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define HAL_NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define HAL_NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_ST_RELOAD register.
*********************************************************************************************************/
#define HAL_NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value
#define HAL_NVIC_ST_RELOAD_S        0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_ST_CURRENT register.
*********************************************************************************************************/
#define HAL_NVIC_ST_CURRENT_M       0x00FFFFFF  // Counter current value
#define HAL_NVIC_ST_CURRENT_S       0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_ST_CAL register.
*********************************************************************************************************/
#define HAL_NVIC_ST_CAL_NOREF       0x80000000  // No reference clock
#define HAL_NVIC_ST_CAL_SKEW        0x40000000  // Clock skew
#define HAL_NVIC_ST_CAL_ONEMS_M     0x00FFFFFF  // 1ms reference value
#define HAL_NVIC_ST_CAL_ONEMS_S     0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_CPUID register.
*********************************************************************************************************/
#define HAL_NVIC_CPUID_IMP_M        0xFF000000  // Implementer
#define HAL_NVIC_CPUID_VAR_M        0x00F00000  // Variant
#define HAL_NVIC_CPUID_PARTNO_M     0x0000FFF0  // Processor part number
#define HAL_NVIC_CPUID_REV_M        0x0000000F  // Revision

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_INT_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_INT_CTRL_NMI_SET   0x80000000  // Pend a NMI
#define HAL_NVIC_INT_CTRL_PEND_SV   0x10000000  // Pend a PendSV
#define HAL_NVIC_INT_CTRL_UNPEND_SV 0x08000000  // Unpend a PendSV
#define HAL_NVIC_INT_CTRL_ISR_PRE   0x00800000  // Debug interrupt handling
#define HAL_NVIC_INT_CTRL_ISR_PEND  0x00400000  // Debug interrupt pending
#define HAL_NVIC_INT_CTRL_VEC_PEN_M 0x003FF000  // Highest pending exception
#define HAL_NVIC_INT_CTRL_RET_BASE  0x00000800  // Return to base
#define HAL_NVIC_INT_CTRL_VEC_ACT_M 0x000003FF  // Current active exception
#define HAL_NVIC_INT_CTRL_VEC_PEN_S 12
#define HAL_NVIC_INT_CTRL_VEC_ACT_S 0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_VTABLE register.
*********************************************************************************************************/
#define HAL_NVIC_VTABLE_BASE        0x20000000  // Vector table base
#define HAL_NVIC_VTABLE_OFFSET_M    0x1FFFFF00  // Vector table offset
#define HAL_NVIC_VTABLE_OFFSET_S    8

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_APINT register.
*********************************************************************************************************/
#define HAL_NVIC_APINT_VECTKEY_M    0xFFFF0000  // Vector key mask
#define HAL_NVIC_APINT_VECTKEY      0x05FA0000  // Vector key
#define HAL_NVIC_APINT_ENDIANESS    0x00008000  // Data endianess
#define HAL_NVIC_APINT_PRIGROUP_M   0x00000700  // Priority group
#define HAL_NVIC_APINT_PRIGROUP_0_8 0x00000700  // Priority group 0.8 split
#define HAL_NVIC_APINT_PRIGROUP_1_7 0x00000600  // Priority group 1.7 split
#define HAL_NVIC_APINT_PRIGROUP_2_6 0x00000500  // Priority group 2.6 split
#define HAL_NVIC_APINT_PRIGROUP_3_5 0x00000400  // Priority group 3.5 split
#define HAL_NVIC_APINT_PRIGROUP_4_4 0x00000300  // Priority group 4.4 split
#define HAL_NVIC_APINT_PRIGROUP_5_3 0x00000200  // Priority group 5.3 split
#define HAL_NVIC_APINT_PRIGROUP_6_2 0x00000100  // Priority group 6.2 split
#define HAL_NVIC_APINT_SYSRESETREQ  0x00000004  // System reset request
#define HAL_NVIC_APINT_VECT_CLR_ACT 0x00000002  // Clear active NMI/fault info
#define HAL_NVIC_APINT_VECT_RESET   0x00000001  // System reset
#define HAL_NVIC_APINT_PRIGROUP_7_1 0x00000000  // Priority group 7.1 split

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_SYS_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_SYS_CTRL_SEVONPEND 0x00000010  // Wakeup on pend
#define HAL_NVIC_SYS_CTRL_SLEEPDEEP 0x00000004  // Deep sleep enable
#define HAL_NVIC_SYS_CTRL_SLEEPEXIT 0x00000002  // Sleep on ISR exit

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_CFG_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_CFG_CTRL_BFHFNMIGN 0x00000100  // Ignore bus fault in NMI/fault
#define HAL_NVIC_CFG_CTRL_DIV0      0x00000010  // Trap on divide by 0
#define HAL_NVIC_CFG_CTRL_UNALIGNED 0x00000008  // Trap on unaligned access
#define HAL_NVIC_CFG_CTRL_DEEP_PEND 0x00000004  // Allow deep interrupt trigger
#define HAL_NVIC_CFG_CTRL_MAIN_PEND 0x00000002  // Allow main interrupt trigger
#define HAL_NVIC_CFG_CTRL_BASE_THR  0x00000001  // Thread state control

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_SYS_PRI1 register.
*********************************************************************************************************/
#define HAL_NVIC_SYS_PRI1_RES_M     0xFF000000  // Priority of reserved handler
#define HAL_NVIC_SYS_PRI1_USAGE_M   0x00FF0000  // Priority of usage fault handler
#define HAL_NVIC_SYS_PRI1_BUS_M     0x0000FF00  // Priority of bus fault handler
#define HAL_NVIC_SYS_PRI1_MEM_M     0x000000FF  // Priority of mem manage handler
#define HAL_NVIC_SYS_PRI1_USAGE_S   16
#define HAL_NVIC_SYS_PRI1_BUS_S     8
#define HAL_NVIC_SYS_PRI1_MEM_S     0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_SYS_PRI2 register.
*********************************************************************************************************/
#define HAL_NVIC_SYS_PRI2_SVC_M     0xFF000000  // Priority of SVCall handler
#define HAL_NVIC_SYS_PRI2_RES_M     0x00FFFFFF  // Priority of reserved handlers
#define HAL_NVIC_SYS_PRI2_SVC_S     24

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_SYS_PRI3 register.
*********************************************************************************************************/
#define HAL_NVIC_SYS_PRI3_TICK_M    0xFF000000  // Priority of Sys Tick handler
#define HAL_NVIC_SYS_PRI3_PENDSV_M  0x00FF0000  // Priority of PendSV handler
#define HAL_NVIC_SYS_PRI3_RES_M     0x0000FF00  // Priority of reserved handler
#define HAL_NVIC_SYS_PRI3_DEBUG_M   0x000000FF  // Priority of debug handler
#define HAL_NVIC_SYS_PRI3_TICK_S    24
#define HAL_NVIC_SYS_PRI3_PENDSV_S  16
#define HAL_NVIC_SYS_PRI3_DEBUG_S   0

/*********************************************************************************************************
**   The following are defines for the bit fields in the HAL_NVIC_SYS_HND_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_SYS_HND_CTRL_USAGE 0x00040000  // Usage fault enable
#define HAL_NVIC_SYS_HND_CTRL_BUS   0x00020000  // Bus fault enable
#define HAL_NVIC_SYS_HND_CTRL_MEM   0x00010000  // Mem manage fault enable
#define HAL_NVIC_SYS_HND_CTRL_SVC   0x00008000  // SVCall is pended
#define HAL_NVIC_SYS_HND_CTRL_BUSP  0x00004000  // Bus fault is pended
#define HAL_NVIC_SYS_HND_CTRL_TICK  0x00000800  // Sys tick is active
#define HAL_NVIC_SYS_HND_CTRL_PNDSV 0x00000400  // PendSV is active
#define HAL_NVIC_SYS_HND_CTRL_MON   0x00000100  // Monitor is active
#define HAL_NVIC_SYS_HND_CTRL_SVCA  0x00000080  // SVCall is active
#define HAL_NVIC_SYS_HND_CTRL_USGA  0x00000008  // Usage fault is active
#define HAL_NVIC_SYS_HND_CTRL_BUSA  0x00000002  // Bus fault is active
#define HAL_NVIC_SYS_HND_CTRL_MEMA  0x00000001  // Mem manage is active

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_FAULT_STAT register.
*********************************************************************************************************/
#define HAL_NVIC_FAULT_STAT_DIV0    0x02000000  // Divide by zero fault
#define HAL_NVIC_FAULT_STAT_UNALIGN 0x01000000  // Unaligned access fault
#define HAL_NVIC_FAULT_STAT_NOCP    0x00080000  // No coprocessor fault
#define HAL_NVIC_FAULT_STAT_INVPC   0x00040000  // Invalid PC fault
#define HAL_NVIC_FAULT_STAT_INVSTAT 0x00020000  // Invalid state fault
#define HAL_NVIC_FAULT_STAT_UNDEF   0x00010000  // Undefined instruction fault
#define HAL_NVIC_FAULT_STAT_BFARV   0x00008000  // BFAR is valid
#define HAL_NVIC_FAULT_STAT_BSTKE   0x00001000  // Stack bus fault
#define HAL_NVIC_FAULT_STAT_BUSTKE  0x00000800  // Unstack bus fault
#define HAL_NVIC_FAULT_STAT_IMPRE   0x00000400  // Imprecise data bus error
#define HAL_NVIC_FAULT_STAT_PRECISE 0x00000200  // Precise data bus error
#define HAL_NVIC_FAULT_STAT_IBUS    0x00000100  // Instruction bus fault
#define HAL_NVIC_FAULT_STAT_MMARV   0x00000080  // MMAR is valid
#define HAL_NVIC_FAULT_STAT_MSTKE   0x00000010  // Stack access violation
#define HAL_NVIC_FAULT_STAT_MUSTKE  0x00000008  // Unstack access violation
#define HAL_NVIC_FAULT_STAT_DERR    0x00000002  // Data access violation
#define HAL_NVIC_FAULT_STAT_IERR    0x00000001  // Instruction access violation

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_HFAULT_STAT register.
*********************************************************************************************************/
#define HAL_NVIC_HFAULT_STAT_DBG    0x80000000  // Debug event
#define HAL_NVIC_HFAULT_STAT_FORCED 0x40000000  // Cannot execute fault handler
#define HAL_NVIC_HFAULT_STAT_VECT   0x00000002  // Vector table read fault

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_DEBUG_STAT register.
*********************************************************************************************************/
#define HAL_NVIC_DEBUG_STAT_EXTRNL  0x00000010  // EDBGRQ asserted
#define HAL_NVIC_DEBUG_STAT_VCATCH  0x00000008  // Vector catch
#define HAL_NVIC_DEBUG_STAT_DWTTRAP 0x00000004  // DWT match
#define HAL_NVIC_DEBUG_STAT_BKPT    0x00000002  // Breakpoint instruction
#define HAL_NVIC_DEBUG_STAT_HALTED  0x00000001  // Halt request

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MM_ADDR register.
*********************************************************************************************************/
#define HAL_NVIC_MM_ADDR_M          0xFFFFFFFF  // Data fault address
#define HAL_NVIC_MM_ADDR_S          0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_FAULT_ADDR register.
*********************************************************************************************************/
#define HAL_NVIC_FAULT_ADDR_M       0xFFFFFFFF  // Data bus fault address
#define HAL_NVIC_FAULT_ADDR_S       0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MPU_TYPE register.
*********************************************************************************************************/
#define HAL_NVIC_MPU_TYPE_IREGION_M 0x00FF0000  // Number of I regions
#define HAL_NVIC_MPU_TYPE_DREGION_M 0x0000FF00  // Number of D regions
#define HAL_NVIC_MPU_TYPE_SEPARATE  0x00000001  // Separate or unified MPU
#define HAL_NVIC_MPU_TYPE_IREGION_S 16
#define HAL_NVIC_MPU_TYPE_DREGION_S 8

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MPU_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_MPU_CTRL_PRIVDEFEN 0x00000004  // MPU default region in priv mode
#define HAL_NVIC_MPU_CTRL_HFNMIENA  0x00000002  // MPU enabled during faults
#define HAL_NVIC_MPU_CTRL_ENABLE    0x00000001  // MPU enable

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MPU_NUMBER register.
*********************************************************************************************************/
#define HAL_NVIC_MPU_NUMBER_M       0x000000FF  // MPU region to access
#define HAL_NVIC_MPU_NUMBER_S       0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MPU_BASE register.
*********************************************************************************************************/
#define HAL_NVIC_MPU_BASE_ADDR_M    0xFFFFFFE0  // Base address mask
#define HAL_NVIC_MPU_BASE_VALID     0x00000010  // Region number valid
#define HAL_NVIC_MPU_BASE_REGION_M  0x0000000F  // Region number
#define HAL_NVIC_MPU_BASE_ADDR_S    8
#define HAL_NVIC_MPU_BASE_REGION_S  0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_MPU_ATTR register.
*********************************************************************************************************/
#define HAL_NVIC_MPU_ATTR_M         0xFFFF0000  // Attributes
#define HAL_NVIC_MPU_ATTR_AP_NO_NO  0x00000000  // prv: no access, usr: no access
#define HAL_NVIC_MPU_ATTR_BUFFRABLE 0x00010000  // Bufferable
#define HAL_NVIC_MPU_ATTR_CACHEABLE 0x00020000  // Cacheable
#define HAL_NVIC_MPU_ATTR_SHAREABLE 0x00040000  // Shareable
#define HAL_NVIC_MPU_ATTR_TEX_M     0x00380000  // Type extension mask
#define HAL_NVIC_MPU_ATTR_AP_RW_NO  0x01000000  // prv: rw, usr: none
#define HAL_NVIC_MPU_ATTR_AP_RW_RO  0x02000000  // prv: rw, usr: read-only
#define HAL_NVIC_MPU_ATTR_AP_RW_RW  0x03000000  // prv: rw, usr: rw
#define HAL_NVIC_MPU_ATTR_AP_RO_NO  0x05000000  // prv: ro, usr: none
#define HAL_NVIC_MPU_ATTR_AP_RO_RO  0x06000000  // prv: ro, usr: ro
#define HAL_NVIC_MPU_ATTR_AP_M      0x07000000  // Access permissions mask
#define HAL_NVIC_MPU_ATTR_XN        0x10000000  // Execute disable
#define HAL_NVIC_MPU_ATTR_SRD_M     0x0000FF00  // Sub-region disable mask
#define HAL_NVIC_MPU_ATTR_SRD_0     0x00000100  // Sub-region 0 disable
#define HAL_NVIC_MPU_ATTR_SRD_1     0x00000200  // Sub-region 1 disable
#define HAL_NVIC_MPU_ATTR_SRD_2     0x00000400  // Sub-region 2 disable
#define HAL_NVIC_MPU_ATTR_SRD_3     0x00000800  // Sub-region 3 disable
#define HAL_NVIC_MPU_ATTR_SRD_4     0x00001000  // Sub-region 4 disable
#define HAL_NVIC_MPU_ATTR_SRD_5     0x00002000  // Sub-region 5 disable
#define HAL_NVIC_MPU_ATTR_SRD_6     0x00004000  // Sub-region 6 disable
#define HAL_NVIC_MPU_ATTR_SRD_7     0x00008000  // Sub-region 7 disable
#define HAL_NVIC_MPU_ATTR_SIZE_M    0x0000003E  // Region size mask
#define HAL_NVIC_MPU_ATTR_SIZE_32B  0x00000008  // Region size 32 bytes
#define HAL_NVIC_MPU_ATTR_SIZE_64B  0x0000000A  // Region size 64 bytes
#define HAL_NVIC_MPU_ATTR_SIZE_128B 0x0000000C  // Region size 128 bytes
#define HAL_NVIC_MPU_ATTR_SIZE_256B 0x0000000E  // Region size 256 bytes
#define HAL_NVIC_MPU_ATTR_SIZE_512B 0x00000010  // Region size 512 bytes
#define HAL_NVIC_MPU_ATTR_SIZE_1K   0x00000012  // Region size 1 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_2K   0x00000014  // Region size 2 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_4K   0x00000016  // Region size 4 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_8K   0x00000018  // Region size 8 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_16K  0x0000001A  // Region size 16 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_32K  0x0000001C  // Region size 32 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_64K  0x0000001E  // Region size 64 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_128K 0x00000020  // Region size 128 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_256K 0x00000022  // Region size 256 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_512K 0x00000024  // Region size 512 Kbytes
#define HAL_NVIC_MPU_ATTR_SIZE_1M   0x00000026  // Region size 1 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_2M   0x00000028  // Region size 2 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_4M   0x0000002A  // Region size 4 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_8M   0x0000002C  // Region size 8 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_16M  0x0000002E  // Region size 16 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_32M  0x00000030  // Region size 32 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_64M  0x00000032  // Region size 64 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_128M 0x00000034  // Region size 128 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_256M 0x00000036  // Region size 256 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_512M 0x00000038  // Region size 512 Mbytes
#define HAL_NVIC_MPU_ATTR_SIZE_1G   0x0000003A  // Region size 1 Gbytes
#define HAL_NVIC_MPU_ATTR_SIZE_2G   0x0000003C  // Region size 2 Gbytes
#define HAL_NVIC_MPU_ATTR_SIZE_4G   0x0000003E  // Region size 4 Gbytes
#define HAL_NVIC_MPU_ATTR_ENABLE    0x00000001  // Region enable

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_DBG_CTRL register.
*********************************************************************************************************/
#define HAL_NVIC_DBG_CTRL_DBGKEY_M  0xFFFF0000  // Debug key mask
#define HAL_NVIC_DBG_CTRL_DBGKEY    0xA05F0000  // Debug key
#define HAL_NVIC_DBG_CTRL_S_RESET_ST \
                                0x02000000  // Core has reset since last read
#define HAL_NVIC_DBG_CTRL_S_RETIRE_ST \
                                0x01000000  // Core has executed insruction
                                            // since last read
#define HAL_NVIC_DBG_CTRL_S_LOCKUP  0x00080000  // Core is locked up
#define HAL_NVIC_DBG_CTRL_S_SLEEP   0x00040000  // Core is sleeping
#define HAL_NVIC_DBG_CTRL_S_HALT    0x00020000  // Core status on halt
#define HAL_NVIC_DBG_CTRL_S_REGRDY  0x00010000  // Register read/write available
#define HAL_NVIC_DBG_CTRL_C_SNAPSTALL \
                                0x00000020  // Breaks a stalled load/store
#define HAL_NVIC_DBG_CTRL_C_MASKINT 0x00000008  // Mask interrupts when stepping
#define HAL_NVIC_DBG_CTRL_C_STEP    0x00000004  // Step the core
#define HAL_NVIC_DBG_CTRL_C_HALT    0x00000002  // Halt the core
#define HAL_NVIC_DBG_CTRL_C_DEBUGEN 0x00000001  // Enable debug

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_DBG_XFER register.
*********************************************************************************************************/
#define HAL_NVIC_DBG_XFER_REG_WNR   0x00010000  // Write or not read
#define HAL_NVIC_DBG_XFER_REG_SEL_M 0x0000001F  // Register
#define HAL_NVIC_DBG_XFER_REG_CFBP  0x00000014  // Control/Fault/BasePri/PriMask
#define HAL_NVIC_DBG_XFER_REG_DSP   0x00000013  // Deep SP
#define HAL_NVIC_DBG_XFER_REG_PSP   0x00000012  // Process SP
#define HAL_NVIC_DBG_XFER_REG_MSP   0x00000011  // Main SP
#define HAL_NVIC_DBG_XFER_REG_FLAGS 0x00000010  // xPSR/Flags register
#define HAL_NVIC_DBG_XFER_REG_R15   0x0000000F  // Register R15
#define HAL_NVIC_DBG_XFER_REG_R14   0x0000000E  // Register R14
#define HAL_NVIC_DBG_XFER_REG_R13   0x0000000D  // Register R13
#define HAL_NVIC_DBG_XFER_REG_R12   0x0000000C  // Register R12
#define HAL_NVIC_DBG_XFER_REG_R11   0x0000000B  // Register R11
#define HAL_NVIC_DBG_XFER_REG_R10   0x0000000A  // Register R10
#define HAL_NVIC_DBG_XFER_REG_R9    0x00000009  // Register R9
#define HAL_NVIC_DBG_XFER_REG_R8    0x00000008  // Register R8
#define HAL_NVIC_DBG_XFER_REG_R7    0x00000007  // Register R7
#define HAL_NVIC_DBG_XFER_REG_R6    0x00000006  // Register R6
#define HAL_NVIC_DBG_XFER_REG_R5    0x00000005  // Register R5
#define HAL_NVIC_DBG_XFER_REG_R4    0x00000004  // Register R4
#define HAL_NVIC_DBG_XFER_REG_R3    0x00000003  // Register R3
#define HAL_NVIC_DBG_XFER_REG_R2    0x00000002  // Register R2
#define HAL_NVIC_DBG_XFER_REG_R1    0x00000001  // Register R1
#define HAL_NVIC_DBG_XFER_REG_R0    0x00000000  // Register R0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_DBG_DATA register.
*********************************************************************************************************/
#define HAL_NVIC_DBG_DATA_M         0xFFFFFFFF  // Data temporary cache
#define HAL_NVIC_DBG_DATA_S         0

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_DBG_INT register.
*********************************************************************************************************/
#define HAL_NVIC_DBG_INT_HARDERR    0x00000400  // Debug trap on hard fault
#define HAL_NVIC_DBG_INT_INTERR     0x00000200  // Debug trap on interrupt errors
#define HAL_NVIC_DBG_INT_BUSERR     0x00000100  // Debug trap on bus error
#define HAL_NVIC_DBG_INT_STATERR    0x00000080  // Debug trap on usage fault state
#define HAL_NVIC_DBG_INT_CHKERR     0x00000040  // Debug trap on usage fault check
#define HAL_NVIC_DBG_INT_NOCPERR    0x00000020  // Debug trap on coprocessor error
#define HAL_NVIC_DBG_INT_MMERR      0x00000010  // Debug trap on mem manage fault
#define HAL_NVIC_DBG_INT_RESET      0x00000008  // Core reset status
#define HAL_NVIC_DBG_INT_RSTPENDCLR 0x00000004  // Clear pending core reset
#define HAL_NVIC_DBG_INT_RSTPENDING 0x00000002  // Core reset is pending
#define HAL_NVIC_DBG_INT_RSTVCATCH  0x00000001  // Reset vector catch

/*********************************************************************************************************
**  The following are defines for the bit fields in the HAL_NVIC_SW_TRIG register.
*********************************************************************************************************/
#define HAL_NVIC_SW_TRIG_INTID_M    0x000003FF  // Interrupt to trigger
#define HAL_NVIC_SW_TRIG_INTID_S    0



#ifdef __cplusplus
    }
#endif      // __cplusplus
    
#endif      // __HAL_IO_INTS_H__
/*********************************************************************************************************
END FILE
*********************************************************************************************************/