/*********************************************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mahmoud Hashish
 **********************************************************************************************************/

#include "Port.h"
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

const Port_ConfigType Port_Configuration[43] = {
                                            PORTA_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_1, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_4, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_5, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_6, INPUT, OFF, STD_LOW, GPIO,
                                            PORTA_INDEX, PIN_7, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_1, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_4, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_5, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_6, INPUT, OFF, STD_LOW, GPIO,
                                            PORTB_INDEX, PIN_7, INPUT, OFF, STD_LOW, GPIO,
   /*       JTAG PROTECTION                 PORTC_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,     JTAG PROTECTION
            JTAG PROTECTION                 PORTC_INDEX, PIN_1, INPUT, OFF, STD_LOW, GPIO,     JTAG PROTECTION
            JTAG PROTECTION                 PORTC_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,     JTAG PROTECTION
            JTAG PROTECTION                 PORTC_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,     JTAG PROTECTION       */
                                            PORTC_INDEX, PIN_4, INPUT, OFF, STD_LOW, GPIO,
                                            PORTC_INDEX, PIN_5, INPUT, OFF, STD_LOW, GPIO,
                                            PORTC_INDEX, PIN_6, INPUT, OFF, STD_LOW, GPIO,
                                            PORTC_INDEX, PIN_7, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_1, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_4, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_5, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_6, INPUT, OFF, STD_LOW, GPIO,
                                            PORTD_INDEX, PIN_7, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_1, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_4, INPUT, OFF, STD_LOW, GPIO,
                                            PORTE_INDEX, PIN_5, INPUT, OFF, STD_LOW, GPIO,
                                            PORTF_INDEX, PIN_0, INPUT, OFF, STD_LOW, GPIO,
                                            PORTF_INDEX, PIN_1, OUTPUT, OFF, STD_LOW, GPIO,
                                            PORTF_INDEX, PIN_2, INPUT, OFF, STD_LOW, GPIO,
                                            PORTF_INDEX, PIN_3, INPUT, OFF, STD_LOW, GPIO,
                                            PORTF_INDEX, PIN_4, INPUT, PULL_UP, STD_LOW, GPIO
};
