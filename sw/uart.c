/*
 * uart.c
 *
 *  Created on: 29 abr. 2017
 *      Author: mat
 */

#include <uart.h>
#include <soc_C6748.h>

void inicializarUART()
{

    /* Enabling the PSC for UART2.*/
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UART2, PSC_POWERDOMAIN_ALWAYS_ON,
             PSC_MDCTL_NEXT_ENABLE);

    /* Setup PINMUX */
    UARTPinMuxSetup(2, FALSE);

    /* Enabling the transmitter and receiver*/
    UARTEnable(SOC_UART_2_REGS);

   /* 1 stopbit, 8-bit character, no parity */
   config = UART_WORDL_8BITS;

   /* Configuring the UART parameters*/
   UARTConfigSetExpClk(SOC_UART_2_REGS, SOC_UART_2_MODULE_FREQ,
                       BAUD_115200, config,
                       UART_OVER_SAMP_RATE_16);

   IntRegister(C674X_MASK_INT4, UARTIsr);
   IntEventMap(C674X_MASK_INT4, SYS_INT_UART2_INT);
   IntEnable(C674X_MASK_INT4);



}
