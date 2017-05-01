
#include <soc_C6748.h>
#include <interrupt.h>
#include <uart.h>
extern void inicializarUART();

static inline void main_loop()
{
    UARTCharPut(SOC_UART_2_REGS, 'A');
}

void main()
{
    // Initialize the DSP INTC
    IntDSPINTCInit();

    inicializarUART();

#if 1
    // Enable DSP interrupts globally
    IntGlobalEnable();
#endif

    while(1)
        main_loop();
}
