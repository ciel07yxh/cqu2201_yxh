/****************************************Copyright (c)****************************************************
**                                ������6lowpan���߿���ƽ̨
**                                  һ��Ϊ��ԴӦ�ö���                                    
**
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           rhb_type.h
** Last modified Date:  2010-12-01
** Last Version:        v1.0
** Description:         �������ͼ������Ĵ����Ľṹ����
** 
**--------------------------------------------------------------------------------------------------------
** Created By:          Renhaibo�κ���
** Created date:        2010-12-01
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
#ifndef __RHB_TYPE_H__
#define __RHB_TYPE_H__

/*********************************************************************************************************
** �������Ͷ���
*********************************************************************************************************/
// Ĭ���������Ͷ���
typedef unsigned char       uint8;                                      /* Unsigned  8 bit quantity     */
typedef signed   char       int8;                                       /* Signed    8 bit quantity     */
typedef unsigned short      uint16;                                     /* Unsigned  16 bit quantity    */
typedef signed   short      int16;                                      /* Signed    16 bit quantity    */
typedef unsigned long       uint32;                                     /* Unsigned  32 bit quantity    */
typedef signed   long       int32;                                      /* Signed    32 bit quantity    */
typedef unsigned long long  uint64;                                     /* Unsigned  64 bit quantity    */
typedef signed long long    int64;                                      /* Signed    64 bit quantity    */
typedef float               fp32;                                       /* Single    precision          */
                                                                        /* floating  point              */
typedef double              fp64;                                       /* Double    precision          */
                                                                        /* floating  point              */
typedef unsigned char       boolean;                                    /* bool���Ͷ���                 */

#ifndef NULL
#define NULL        (void *)0
#endif

#ifndef false
#define false       0
#endif

#ifndef true
#define true        (!false)
#endif

/*********************************************************************************************************
** ����궨��
*********************************************************************************************************/
#define RHB_MACRO_START     do {
#define RHB_MACRO_END       } while (0)

/*********************************************************************************************************
** ���ʼĴ����ĺ궨��
*********************************************************************************************************/
/*********************************************************************************************************
** ֱ�ӽ��Ĵ���ӳ��
*********************************************************************************************************/
#define HWREG32(x)          (*((volatile uint32 *)(x)))
#define HWREG16(x)          (*((volatile uint16 *)(x)))
#define HWREG8(x)           (*((volatile uint8 *)(x)))

/*********************************************************************************************************
** �ο�ecos��ֲ�����ģ�ͨ����������
*********************************************************************************************************/
//  8λ���ʼĴ����ĺ궨��
#define HAL_READ_UINT8( _register_, _value_ )       \
        ((_value_) = *((volatile uint8 *)(_register_)))

#define HAL_WRITE_UINT8( _register_, _value_ )      \
        (*((volatile uint8 *)(_register_)) = (_value_))

#define HAL_READ_UINT8_VECTOR( _register_, _buf_, _count_, _step_ )     \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        (_buf_)[_i_] = ((volatile uint8 *)(_register_))[_j_];           \
    RHB_MACRO_END

#define HAL_WRITE_UINT8_VECTOR( _register_, _buf_, _count_, _step_ )    \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile uint8 *)(_register_))[_j_] = (_buf_)[_i_];           \
    RHB_MACRO_END

#define HAL_READ_UINT8_STRING( _register_, _buf_, _count_ )             \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        (_buf_)[_i_] = ((volatile uint8 *)(_register_))[_i_];           \
    RHB_MACRO_END

#define HAL_WRITE_UINT8_STRING( _register_, _buf_, _count_ )            \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        ((volatile uint8 *)(_register_)) = (_buf_)[_i_];                \
    RHB_MACRO_END

//  16λ���ʼĴ����ĺ궨��
#define HAL_READ_UINT16( _register_, _value_ )      \
        ((_value_) = *((volatile uint16 *)(_register_)))

#define HAL_WRITE_UINT16( _register_, _value_ )     \
        (*((volatile uint16 *)(_register_)) = (_value_))

#define HAL_READ_UINT16_VECTOR( _register_, _buf_, _count_, _step_ )    \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        (_buf_)[_i_] = ((volatile uint16 *)(_register_))[_j_];          \
    RHB_MACRO_END

#define HAL_WRITE_UINT16_VECTOR( _register_, _buf_, _count_, _step_ )   \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile uint16 *)(_register_))[_j_] = (_buf_)[_i_];          \
    RHB_MACRO_END

#define HAL_READ_UINT16_STRING( _register_, _buf_, _count_)             \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        (_buf_)[_i_] = ((volatile uint16 *)(_register_))[_i_];          \
    RHB_MACRO_END

#define HAL_WRITE_UINT16_STRING( _register_, _buf_, _count_)            \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        ((volatile uint16 *)(_register_))[_i_] = (_buf_)[_i_];          \
    RHB_MACRO_END

// 32λ���ʼĴ����ĺ궨��
#define HAL_READ_UINT32( _register_, _value_ )      \
        ((_value_) = *((volatile uint32 *)(_register_)))

#define HAL_WRITE_UINT32( _register_, _value_ )     \
        (*((volatile uint32 *)(_register_)) = (_value_))

#define HAL_READ_UINT32_VECTOR( _register_, _buf_, _count_, _step_ )    \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        (_buf_)[_i_] = ((volatile uint32 *)(_register_))[_j_];          \
    RHB_MACRO_END

#define HAL_WRITE_UINT32_VECTOR( _register_, _buf_, _count_, _step_ )   \
    RHB_MACRO_START                                                     \
    uint32 _i_,_j_;                                                     \
    for( _i_ = 0, _j_ = 0; _i_ < (_count_); _i_++, _j_ += (_step_))     \
        ((volatile uint32 *)(_register_))[_j_] = (_buf_)[_i_];          \
    RHB_MACRO_END

#define HAL_READ_UINT32_STRING( _register_, _buf_, _count_)             \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        (_buf_)[_i_] = ((volatile uint32 *)(_register_))[_i_];          \
    RHB_MACRO_END

#define HAL_WRITE_UINT32_STRING( _register_, _buf_, _count_)            \
    RHB_MACRO_START                                                     \
    uint32 _i_;                                                         \
    for( _i_ = 0; _i_ < (_count_); _i_++)                               \
        ((volatile uint32 *)(_register_))[_i_] = (_buf_)[_i_];          \
    RHB_MACRO_END

#endif // endif of __RHB_TYPE_H__
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
