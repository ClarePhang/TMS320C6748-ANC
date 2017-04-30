
#include <soc_C6748.h>
#include <interrupt.h>

extern void inicializarUART();

void main()
{
    // Initialize the DSP INTC
    IntDSPINTCInit();

    inicializarUART();

    // Enable DSP interrupts globally
    IntGlobalEnable();

    while(1);
}
