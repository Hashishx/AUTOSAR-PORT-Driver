/********************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mahmoud Hashish
 ********************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/********************************************************************
 *                      Global Variables                                        *
 ********************************************************************/
//STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
Port_ConfigType ConfigPtr2[43];
/********************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module
*********************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ) {
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        //Port_Status = PORT_INITIALIZED;
        uint8 i;
        for (i = 0; i < 44; i++) {

            /* saving data in a global variable */
            ConfigPtr2[i].port_num = ConfigPtr[i].port_num;
            ConfigPtr2[i].pin_num = ConfigPtr[i].pin_num;
            ConfigPtr2[i].direction = ConfigPtr[i].direction;
            ConfigPtr2[i].resistor = ConfigPtr[i].resistor;
            ConfigPtr2[i].initial_value = ConfigPtr[i].initial_value;
            ConfigPtr2[i].pin_mode = ConfigPtr[i].pin_mode;

            switch (ConfigPtr[i].port_num)
            {
            case 0:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case 1:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case 2:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case 3:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case 4:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case 5:
                PortGpio_Ptr = (volatile uint32 *) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            }

            if (((ConfigPtr[i].port_num == 3) && (ConfigPtr[i].pin_num == 7)) || ((ConfigPtr[i].port_num == 5) && (ConfigPtr[i].pin_num == 0))) /* PD7 or PF0 */
            {
                *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this Pin */
            }
            else if ((ConfigPtr[i].port_num == 2) && (ConfigPtr[i].pin_num <= 3)) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG Pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this Pin */
            }

            if (ConfigPtr[i].direction == OUTPUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */

                if (ConfigPtr[i].initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), ConfigPtr[i].pin_num); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if (ConfigPtr[i].direction == INPUT)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), ConfigPtr[i].pin_num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */

                if (ConfigPtr[i].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up Pin */
                }
                else if (ConfigPtr[i].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down Pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), ConfigPtr[i].pin_num); /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up Pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), ConfigPtr[i].pin_num); /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down Pin */
                }
            }
            else
            {
                /* Do Nothing */
            }

            /* Setup the Pin mode as required */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), ConfigPtr[i].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), ConfigPtr[i].pin_num); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[i].pin_num * 4)); /* Clear the PMCx bits for this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), ConfigPtr[i].pin_num); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }
}
/***********************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
************************************************************************/
void Port_RefreshPortDirection( void ) {

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    uint8 i;
    for (i = 0; i < 44; i++) {
        switch (ConfigPtr2[i].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }
        if (ConfigPtr2[i].direction == OUTPUT) {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), ConfigPtr2[i].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (ConfigPtr2[i].direction == INPUT) {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), ConfigPtr2[i].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
    }
}

/*******************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port Pin ID number, Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port Pin direction
********************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ) {

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint8 real_Pin_Num = 0;

    /* The required Pin to set it's direction is in PORT A */
    if (Pin >= PORT_A_PIN_0 && Pin < PORT_B_PIN_0) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        real_Pin_Num = Pin - 0;
        if (Direction == OUTPUT) {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT) {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }

    /* The required Pin to set it's direction is in PORT B */
    else if (Pin >= PORT_B_PIN_0 && Pin < PORT_C_PIN_0) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        real_Pin_Num = Pin - 8;
        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }

    /* The required Pin to set it's direction is in PORT C */
    else if (Pin >= PORT_C_PIN_0 && Pin < PORT_D_PIN_0) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        real_Pin_Num = Pin - 16;
        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }

    /* The required Pin to set it's direction is in PORT D */
    else if (Pin >= PORT_D_PIN_0 && Pin < PORT_E_PIN_0) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        real_Pin_Num = Pin - 24;
        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }

    /* The required Pin to set it's direction is in PORT E */
    else if (Pin >= PORT_E_PIN_0 && Pin < PORT_F_PIN_0) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        real_Pin_Num = Pin - 32;
        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }

    /* The required Pin to set it's direction is in PORT F */
    else if (Pin >= PORT_F_PIN_0 && Pin <= PORT_F_PIN_4) {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        real_Pin_Num = Pin - 38;
        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Set the corresponding bit in the GPIODIR register to configure it as output Pin */
        }
        else if (Direction == INPUT)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), real_Pin_Num); /* Clear the corresponding bit in the GPIODIR register to configure it as input Pin */
        }
    }
}

/**************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port Pin ID number, New Port Pin mode to be set on port Pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port Pin mode
***************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ) {

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    if (Pin >= PORT_A_PIN_0 && Pin < PORT_B_PIN_0)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        if (Pin == PORT_A_PIN_0 && Mode == MODE_1) {
            /* Setup the Pin mode as required */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_0); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_0); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_0); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }

    else if (Pin >= PORT_B_PIN_0 && Pin < PORT_C_PIN_0)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        if (Pin == PORT_B_PIN_0 && Mode == MODE_1) {
        /* Setup the Pin mode as required */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_0); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_0); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_0); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }

    else if (Pin >= PORT_C_PIN_0 && Pin < PORT_D_PIN_0)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            if (Pin == PORT_C_PIN_4 && Mode == MODE_1) {
                /* Setup the Pin mode as required */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_4); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_4); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_4); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
            }
    }

    else if (Pin >= PORT_D_PIN_0 && Pin < PORT_E_PIN_0)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        if (Pin == PORT_D_PIN_4 && Mode == MODE_1) {
            /* Setup the Pin mode as required */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_4); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_4); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_4); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }

    else if (Pin >= PORT_E_PIN_0 && Pin < PORT_F_PIN_0)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        if (Pin == PORT_E_PIN_0 && Mode == MODE_1) {
            /* Setup the Pin mode as required */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_0); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_0); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_0); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }

    else if (Pin >= PORT_F_PIN_0 && Pin <= PORT_F_PIN_4)
    {
        PortGpio_Ptr = (volatile uint32 *) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        if (Pin == PORT_F_PIN_0 && Mode == MODE_1) {
            /* Setup the Pin mode as required */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_0); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PIN_0); /* Disable Alternative function for this Pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= 0xFFFFFFF1; /*  PMCx bits for this Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_0); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this Pin */
        }
    }
}

/***********************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif
