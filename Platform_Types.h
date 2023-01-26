/*
* Std_Types.h
 *
 *  Created on: Nov 26, 2022
 *      Author: O. A.
 *
 * Description:
 *
 */
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

/*
 * AUTOSAR Version 4.0.3
 */
#define PLATFORM_MODULE_ID                          (1000U)

#define PLATFORM_AR_RELEASE_MAJOR_VERSION           (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION           (0U)
#define PLATFORM_AR_RELEASE_PATCH_VERSION           (3U)

/*
 * CPU register type width
 */
#define CPU_TYPE_8        (8U)
#define CPU_TYPE_16       (16U)
#define CPU_TYPE_32       (32U)

/*
 * Bit order definition
 */
#define MSB_FIRST         (0U)    /* Big endian bit ordering */
#define LSB_FIRST         (1U)    /* Little endian bit ordering */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST   (0U)    /* Big endian bit ordering */
#define LOW_BYTE_FIRST    (1U)    /* Little endian bit ordering */

/*
 * Platform type and endianess definitions, specific for ARM Cortex-M4F
 */
#define CPU_TYPE        CPU_TYPE_32
#define CPU_BIT_ORDER   LSB_FIRST
#define CPU_BYTE_ORDER  LOW_BYTE_FIRST

/*
 * Boolean Values
 */
#ifndef TRUE
 #define TRUE              ((boolean) 1)
#endif

#ifndef FALSE
 #define FALSE             ((boolean) 0)
#endif

#ifndef NULL
 #define NULL ((void*)0)
#endif

typedef unsigned char      boolean;

typedef unsigned char       uint8;        /*           0 .. 255             */
typedef signed char         sint8;        /*        -128 .. +127            */
typedef unsigned short      uint16;       /*           0 .. 65535           */
typedef signed short        sint16;       /*      -32768 .. +32767          */
typedef unsigned long       uint32;       /*           0 .. 4294967295      */
typedef signed long         sint32;       /* -2147483648 .. +2147483647     */
typedef unsigned long long  uint64;       /*       0..18446744073709551615  */
typedef signed long long    sint64;
typedef float               float32;
typedef double              float64;

typedef unsigned char       uint8_least;
typedef signed char         sint8_least;
typedef unsigned short      uint16_least;
typedef signed short        sint16_least;
typedef unsigned long       uint32_least;
typedef signed long         sint32_least;
typedef unsigned long long  uint64_least;
typedef signed long long    sint64_least;

typedef volatile uint8      vuint8_t;
typedef volatile sint8      vsint8_t;
typedef volatile uint16     vuint16_t;
typedef volatile sint16     vsint16_t;
typedef volatile uint32     vuint32_t;
typedef volatile sint32     vsint32_t;
typedef volatile float32    vfloat32_t;
typedef volatile float64    vfloat64_t;


#endif /* PLATFORM_TYPES_H_ */
