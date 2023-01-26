/*
 * Std_Types.h
 *
 *  Created on: Nov 26, 2022
 *      Author: O. A.
 * 
 * Description:
 * 
 */
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Platform_Types.h"
//#include "Compiler.h"

/*
 *  Describes the standard Return Type Definitions used in the project
 */
typedef uint8 Std_ReturnType;

#define STD_HIGH      (1U)     /* Standard HIGH */
#define STD_LOW       (0U)     /* Standard LOW */

#define STD_ACTIVE    (1U)     /* Logical state active */
#define STD_IDLE      (0U)     /* Logical state idle */

#define STD_ON        (1U)     /* Standard ON */
#define STD_OFF       (0U)     /* Standard OFF */

#define E_OK          ((Std_ReturnType) 0)     /* Function Return OK */
#define E_NOT_OK      ((Std_ReturnType) 1)     /* Function Return NOT OK */


/* Id for the company in the AUTOSAR
 * for example George Marc ID = 555 */
#define STD_TYPES_VENDOR_ID                                  (1000U)

/*
 * Module Version 1.0.0
 */
#define STD_TYPES_SW_MAJOR_VERSION                           (1U)
#define STD_TYPES_SW_MINOR_VERSION                           (0U)
#define STD_TYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION                   (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION                   (0U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION                   (3U)

/*
 * Structure for the Version of the module.
 * This is requested by calling <Module name>_GetVersionInfo()
 */
typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8   sw_major_version;
  uint8   sw_minor_version;
  uint8   sw_patch_version;
}Std_VersionInfoType;

#endif /* STD_TYPES_H_ */
