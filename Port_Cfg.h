/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mahmoud Hashish
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for changeable direction of pins */
#define CHANGEABLE_DIRECTION_STATE           (STD_ON)

/* Pre-compile option for changeable mode of pins */
#define CHANGEABLE_MODE_STATE                (STD_ON)

/* Ports index */
#define PORTA_INDEX                          (uint8)0x00
#define PORTB_INDEX                          (uint8)0x01
#define PORTC_INDEX                          (uint8)0x02
#define PORTD_INDEX                          (uint8)0x03
#define PORTE_INDEX                          (uint8)0x04
#define PORTF_INDEX                          (uint8)0x05

/* PortA pins index */
#define PORT_A_PIN_0                          0
#define PORT_A_PIN_1                          1
#define PORT_A_PIN_2                          2
#define PORT_A_PIN_3                          3
#define PORT_A_PIN_4                          4
#define PORT_A_PIN_5                          5
#define PORT_A_PIN_6                          6
#define PORT_A_PIN_7                          7

/* PortB pins index */
#define PORT_B_PIN_0                          8
#define PORT_B_PIN_1                          9
#define PORT_B_PIN_2                         10
#define PORT_B_PIN_3                         11
#define PORT_B_PIN_4                         12
#define PORT_B_PIN_5                         13
#define PORT_B_PIN_6                         14
#define PORT_B_PIN_7                         15

/* PortC pins index */
#define PORT_C_PIN_0                         16
#define PORT_C_PIN_1                         17
#define PORT_C_PIN_2                         18
#define PORT_C_PIN_3                         19
#define PORT_C_PIN_4                         20
#define PORT_C_PIN_5                         21
#define PORT_C_PIN_6                         22
#define PORT_C_PIN_7                         23

/* PortD pins index */
#define PORT_D_PIN_0                         24
#define PORT_D_PIN_1                         25
#define PORT_D_PIN_2                         26
#define PORT_D_PIN_3                         27
#define PORT_D_PIN_4                         28
#define PORT_D_PIN_5                         29
#define PORT_D_PIN_6                         30
#define PORT_D_PIN_7                         31

/* PortE pins index */
#define PORT_E_PIN_0                         32
#define PORT_E_PIN_1                         33
#define PORT_E_PIN_2                         34
#define PORT_E_PIN_3                         35
#define PORT_E_PIN_4                         36
#define PORT_E_PIN_5                         37

/* PortF pins index */
#define PORT_F_PIN_0                         38
#define PORT_F_PIN_1                         39
#define PORT_F_PIN_2                         40
#define PORT_F_PIN_3                         41
#define PORT_F_PIN_4                         42

#endif /* PORT_CFG_H_ */
