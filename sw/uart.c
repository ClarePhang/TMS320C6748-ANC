/*
 * uart.c
 *
 *  Created on: 29 abr. 2017
 *      Author: Matías Silva Bustos.
 */

#include <uart.h>
#include <soc_C6748.h>
#include <hw_psc_C6748.h>
#include <psc.h>
#include <interrupt.h>
#include <lcdkC6748.h>
#include <hw_types.h>

static void UARTIsr();

void inicializarUART()
{
    int config = 0;
    int intFlags = 0;

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

   /* Preparing the 'intFlags' variable to be passed as an argument.*/
       intFlags |= (UART_INT_LINE_STAT  |  \
                    UART_INT_TX_EMPTY |    \
                    UART_INT_RXDATA_CTI);

       /* Enable the Interrupts in UART.*/
       UARTIntEnable(SOC_UART_2_REGS, intFlags);

}

static void UARTIsr()
{
    int int_id;
    int rxData;

    /* This determines the cause of UART2 interrupt.*/
    int_id = UARTIntStatus(SOC_UART_2_REGS);

    switch(int_id){
    case UART_INTID_RX_DATA:
        rxData = UARTCharGetNonBlocking(SOC_UART_2_REGS);
        UARTCharPutNonBlocking(SOC_UART_2_REGS, rxData);
        break;
    }

    return;
}
