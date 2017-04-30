
#include <soc_C6748.h>
#include <interrupt.h>

extern void inicializarUART();

static inline void main_loop()
{

}
void main()
{
    // Initialize the DSP INTC
    IntDSPINTCInit();

    inicializarUART();

    // Enable DSP interrupts globally
    IntGlobalEnable();

    while(1)
        main_loop();
}
