/**************************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mahmoud Hashish
 **************************************************************************************/
#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mahmoud Hashish ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/**********************************************************************************
 *                              Module Definitions                             *
 **********************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*******************************************************************************
 *                      API Service Id Macros                                 *
 *******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                             (uint8)0x00

/* Service ID for Port set pin direction */
#define PORT_SET_PIN_DIRECTION_SID                (uint8)0x01

/* Service ID for Port refresh port direction */
#define PORT_REFRESH_PORT_DIRECTION_SID           (uint8)0x02

/* Service ID for Port GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID                 (uint8)0x03

/* Service ID for Port set pin mode */
#define PORT_SET_PIN_MODE_SID                     (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* Det error to report Invalid Port Pin ID */
#define PORT_E_PARAM_PIN                (uint8)0x0A

/* Det error to report Port Pin not configured */
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B

/* Port_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C

/* Det error to report Invalid Pin mode */
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D

/* Det error to report unchangeable mode */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/* Det error to report uninitialized port */
#define PORT_E_UNINIT                   (uint8)0x0F

/* Det error to report API called with NULL pointer */
#define PORT_E_PARAM_POINTER            (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Enum to hold Pins number from 0 to 7 */
typedef enum {
    PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7
}Pins;

typedef enum {
    GPIO, MODE_1, MODE_2, MODE_3, MODE_4, MODE_5, MODE_6, MODE_7, MODE_8, MODE_9, MODE_14=14
}mode_Num;

/*  Description: Structure to configure each individual PIN:
 *  1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *  2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the initial value --> HIGH or LOW
 *  6. the pin mode
 */
typedef struct
{
    uint8 port_num;
    Pins pin_num;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    mode_Num pin_mode;
}Port_ConfigType;

/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for PORT Initialization API */
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for Setting Pin Direction of a Port */
#if (CHANGEABLE_DIRECTION_STATE == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Function to refresh port direction */
void Port_RefreshPortDirection( void );

/* Function to set Pin mode */
#if (CHANGEABLE_MODE_STATE == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif

/* Function for PORT Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration[43];

#endif /* PORT_H */
