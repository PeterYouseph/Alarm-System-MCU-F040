#include "watchdog.h"

// Interruption para funcionamento do Watchdog Timer na F040

void WDT_ISR(void) __interrupt 16
{
    WDTCN = 0xA5; // Reseta o watchdog timer
}

void init_watchdog()
{
    WDTCN = 0xA5; // Ativa o watchdog timer
}

void reset_watchdog()
{
    WDTCN = 0xA5; // Reseta o watchdog timer
}
