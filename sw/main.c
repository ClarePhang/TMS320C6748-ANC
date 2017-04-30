
#include <soc_C6748.h>
#include <interrupt.h>

extern void inicializarUART();

void main()
{
    inicializarUART();

    // Initialize the DSP INTC
    IntDSPINTCInit();

    // Enable DSP interrupts globally
    IntGlobalEnable();

    while(1);
}
