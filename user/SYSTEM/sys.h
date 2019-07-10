
#ifndef __sys_H__
#define __sys_H__
#include "io_macros.h"

/*-------------------------------------------------------------------------
*      Port A register definitions
*-----------------------------------------------------------------------*/
typedef struct
{
    unsigned char ODR0        : 1;
    unsigned char ODR1        : 1;
    unsigned char ODR2        : 1;
    unsigned char ODR3        : 1;
    unsigned char ODR4        : 1;
    unsigned char ODR5        : 1;
    unsigned char ODR6        : 1;
    unsigned char ODR7        : 1;
} __BITS_PA_ODR;
__IO_REG8_BIT(PA_ODR,      0x5000, __READ_WRITE, __BITS_PA_ODR);

typedef struct
{
    unsigned char IDR0        : 1;
    unsigned char IDR1        : 1;
    unsigned char IDR2        : 1;
    unsigned char IDR3        : 1;
    unsigned char IDR4        : 1;
    unsigned char IDR5        : 1;
    unsigned char IDR6        : 1;
    unsigned char IDR7        : 1;
} __BITS_PA_IDR;
__IO_REG8_BIT(PA_IDR,      0x5001, __READ, __BITS_PA_IDR);

/*-------------------------------------------------------------------------
*      Port A bit fields
*-----------------------------------------------------------------------*/
#define PA_ODR_ODR0              PA_ODR_bit.ODR0
#define PA_ODR_ODR1              PA_ODR_bit.ODR1
#define PA_ODR_ODR2              PA_ODR_bit.ODR2
#define PA_ODR_ODR3              PA_ODR_bit.ODR3
#define PA_ODR_ODR4              PA_ODR_bit.ODR4
#define PA_ODR_ODR5              PA_ODR_bit.ODR5
#define PA_ODR_ODR6              PA_ODR_bit.ODR6
#define PA_ODR_ODR7              PA_ODR_bit.ODR7

#define PA_IDR_IDR0              PA_IDR_bit.IDR0
#define PA_IDR_IDR1              PA_IDR_bit.IDR1
#define PA_IDR_IDR2              PA_IDR_bit.IDR2
#define PA_IDR_IDR3              PA_IDR_bit.IDR3
#define PA_IDR_IDR4              PA_IDR_bit.IDR4
#define PA_IDR_IDR5              PA_IDR_bit.IDR5
#define PA_IDR_IDR6              PA_IDR_bit.IDR6
#define PA_IDR_IDR7              PA_IDR_bit.IDR7

/*-------------------------------------------------------------------------
*      Port B register definitions
*-----------------------------------------------------------------------*/
typedef struct
{
    unsigned char ODR0        : 1;
    unsigned char ODR1        : 1;
    unsigned char ODR2        : 1;
    unsigned char ODR3        : 1;
    unsigned char ODR4        : 1;
    unsigned char ODR5        : 1;
    unsigned char ODR6        : 1;
    unsigned char ODR7        : 1;
} __BITS_PB_ODR;
__IO_REG8_BIT(PB_ODR,      0x5005, __READ_WRITE, __BITS_PB_ODR);

typedef struct
{
    unsigned char IDR0        : 1;
    unsigned char IDR1        : 1;
    unsigned char IDR2        : 1;
    unsigned char IDR3        : 1;
    unsigned char IDR4        : 1;
    unsigned char IDR5        : 1;
    unsigned char IDR6        : 1;
    unsigned char IDR7        : 1;
} __BITS_PB_IDR;
__IO_REG8_BIT(PB_IDR,      0x5006, __READ, __BITS_PB_IDR);

/*-------------------------------------------------------------------------
*      Port B bit fields
*-----------------------------------------------------------------------*/
#define PB_ODR_ODR0              PB_ODR_bit.ODR0
#define PB_ODR_ODR1              PB_ODR_bit.ODR1
#define PB_ODR_ODR2              PB_ODR_bit.ODR2
#define PB_ODR_ODR3              PB_ODR_bit.ODR3
#define PB_ODR_ODR4              PB_ODR_bit.ODR4
#define PB_ODR_ODR5              PB_ODR_bit.ODR5
#define PB_ODR_ODR6              PB_ODR_bit.ODR6
#define PB_ODR_ODR7              PB_ODR_bit.ODR7

#define PB_IDR_IDR0              PB_IDR_bit.IDR0
#define PB_IDR_IDR1              PB_IDR_bit.IDR1
#define PB_IDR_IDR2              PB_IDR_bit.IDR2
#define PB_IDR_IDR3              PB_IDR_bit.IDR3
#define PB_IDR_IDR4              PB_IDR_bit.IDR4
#define PB_IDR_IDR5              PB_IDR_bit.IDR5
#define PB_IDR_IDR6              PB_IDR_bit.IDR6
#define PB_IDR_IDR7              PB_IDR_bit.IDR7

/*-------------------------------------------------------------------------
*      Port C register definitions
*-----------------------------------------------------------------------*/
typedef struct
{
    unsigned char ODR0        : 1;
    unsigned char ODR1        : 1;
    unsigned char ODR2        : 1;
    unsigned char ODR3        : 1;
    unsigned char ODR4        : 1;
    unsigned char ODR5        : 1;
    unsigned char ODR6        : 1;
    unsigned char ODR7        : 1;
} __BITS_PC_ODR;
__IO_REG8_BIT(PC_ODR,      0x500A, __READ_WRITE, __BITS_PC_ODR);

typedef struct
{
    unsigned char IDR0        : 1;
    unsigned char IDR1        : 1;
    unsigned char IDR2        : 1;
    unsigned char IDR3        : 1;
    unsigned char IDR4        : 1;
    unsigned char IDR5        : 1;
    unsigned char IDR6        : 1;
    unsigned char IDR7        : 1;
} __BITS_PC_IDR;
__IO_REG8_BIT(PC_IDR,      0x500B, __READ, __BITS_PC_IDR);

/*-------------------------------------------------------------------------
*      Port C bit fields
*-----------------------------------------------------------------------*/
#define PC_ODR_ODR0              PC_ODR_bit.ODR0
#define PC_ODR_ODR1              PC_ODR_bit.ODR1
#define PC_ODR_ODR2              PC_ODR_bit.ODR2
#define PC_ODR_ODR3              PC_ODR_bit.ODR3
#define PC_ODR_ODR4              PC_ODR_bit.ODR4
#define PC_ODR_ODR5              PC_ODR_bit.ODR5
#define PC_ODR_ODR6              PC_ODR_bit.ODR6
#define PC_ODR_ODR7              PC_ODR_bit.ODR7

#define PC_IDR_IDR0              PC_IDR_bit.IDR0
#define PC_IDR_IDR1              PC_IDR_bit.IDR1
#define PC_IDR_IDR2              PC_IDR_bit.IDR2
#define PC_IDR_IDR3              PC_IDR_bit.IDR3
#define PC_IDR_IDR4              PC_IDR_bit.IDR4
#define PC_IDR_IDR5              PC_IDR_bit.IDR5
#define PC_IDR_IDR6              PC_IDR_bit.IDR6
#define PC_IDR_IDR7              PC_IDR_bit.IDR7
/*-------------------------------------------------------------------------
*      Port D register definitions
*-----------------------------------------------------------------------*/
typedef struct
{
    unsigned char ODR0        : 1;
    unsigned char ODR1        : 1;
    unsigned char ODR2        : 1;
    unsigned char ODR3        : 1;
    unsigned char ODR4        : 1;
    unsigned char ODR5        : 1;
    unsigned char ODR6        : 1;
    unsigned char ODR7        : 1;
} __BITS_PD_ODR;
__IO_REG8_BIT(PD_ODR,      0x500F, __READ_WRITE, __BITS_PD_ODR);

typedef struct
{
    unsigned char IDR0        : 1;
    unsigned char IDR1        : 1;
    unsigned char IDR2        : 1;
    unsigned char IDR3        : 1;
    unsigned char IDR4        : 1;
    unsigned char IDR5        : 1;
    unsigned char IDR6        : 1;
    unsigned char IDR7        : 1;
} __BITS_PD_IDR;
__IO_REG8_BIT(PD_IDR,      0x5010, __READ, __BITS_PD_IDR);


/*-------------------------------------------------------------------------
*      Port D bit fields
*-----------------------------------------------------------------------*/
#define PD_ODR_ODR0              PD_ODR_bit.ODR0
#define PD_ODR_ODR1              PD_ODR_bit.ODR1
#define PD_ODR_ODR2              PD_ODR_bit.ODR2
#define PD_ODR_ODR3              PD_ODR_bit.ODR3
#define PD_ODR_ODR4              PD_ODR_bit.ODR4
#define PD_ODR_ODR5              PD_ODR_bit.ODR5
#define PD_ODR_ODR6              PD_ODR_bit.ODR6
#define PD_ODR_ODR7              PD_ODR_bit.ODR7

#define PD_IDR_IDR0              PD_IDR_bit.IDR0
#define PD_IDR_IDR1              PD_IDR_bit.IDR1
#define PD_IDR_IDR2              PD_IDR_bit.IDR2
#define PD_IDR_IDR3              PD_IDR_bit.IDR3
#define PD_IDR_IDR4              PD_IDR_bit.IDR4
#define PD_IDR_IDR5              PD_IDR_bit.IDR5
#define PD_IDR_IDR6              PD_IDR_bit.IDR6
#define PD_IDR_IDR7              PD_IDR_bit.IDR7

///////////////////////////////////////////////////////////
//IO口操作,只对单一的IO口!
//确保n的值小于16!
//X表示端口，确保小于16，n表示高低1为高 0为低
#define PAout(x,n)    switch(x){         \
        case 0:PA_ODR_ODR0 = n;break;    \
        case 1:PA_ODR_ODR1 = n;break;    \
        case 2:PA_ODR_ODR2 = n;break;    \
        case 3:PA_ODR_ODR3 = n;break;    \
        case 4:PA_ODR_ODR4 = n;break;    \
        case 5:PA_ODR_ODR5 = n;break;    \
        case 6:PA_ODR_ODR6 = n;break;    \
        case 7:PA_ODR_ODR7 = n;break;}


#define PBout(x,n)    switch(x){         \
        case 0:PB_ODR_ODR0 = n;break;    \
        case 1:PB_ODR_ODR1 = n;break;    \
        case 2:PB_ODR_ODR2 = n;break;    \
        case 3:PB_ODR_ODR3 = n;break;    \
        case 4:PB_ODR_ODR4 = n;break;    \
        case 5:PB_ODR_ODR5 = n;break;    \
        case 6:PB_ODR_ODR6 = n;break;    \
        case 7:PB_ODR_ODR7 = n;break;}


#define PCout(x,n)    switch(x){         \
        case 0:PC_ODR_ODR0 = n;break;    \
        case 1:PC_ODR_ODR1 = n;break;    \
        case 2:PC_ODR_ODR2 = n;break;    \
        case 3:PC_ODR_ODR3 = n;break;    \
        case 4:PC_ODR_ODR4 = n;break;    \
        case 5:PC_ODR_ODR5 = n;break;    \
        case 6:PC_ODR_ODR6 = n;break;    \
        case 7:PC_ODR_ODR7 = n;break;}

#define PDout(x,n)    switch(x){         \
        case 0:PD_ODR_ODR0 = n;break;    \
        case 1:PD_ODR_ODR1 = n;break;    \
        case 2:PD_ODR_ODR2 = n;break;    \
        case 3:PD_ODR_ODR3 = n;break;    \
        case 4:PD_ODR_ODR4 = n;break;    \
        case 5:PD_ODR_ODR5 = n;break;    \
        case 6:PD_ODR_ODR6 = n;break;    \
        case 7:PD_ODR_ODR7 = n;break;}

#endif    /* __SYS_H__ */

/*----------------------------------------------
*      End of file
*--------------------------------------------*/
