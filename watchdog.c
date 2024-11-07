#include "watchdog.h"

void init_watchdog()
{
    WDTCN = 0xA5; // Ativa o watchdog timer
}

void reset_watchdog()
{
    WDTCN = 0xA5; // Reseta o watchdog timer
}
