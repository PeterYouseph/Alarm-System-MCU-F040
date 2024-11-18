#include "delay.h"
#include "C8051F040_defs.h"
// #include "config.c"

void delay_ms(unsigned int t)
{
    TMOD |= 0x01;
    TMOD &= ~0x02;
    for (; t > 0; t--)
    {
        TR0 = 0;
        TF0 = 0;
        TL0 = 0x58;
        TH0 = 0x9E;
        TR0 = 1;
        while (!TF0)
            ;
        TF0 = 0;
    }
}

void delay_us(unsigned int t)
{
    TMOD &= ~0x01;
    TMOD |= 0x02;
    TR0 = 0;
    TF0 = 0;
    TL0 = 231;
    TH0 = 231;
    TR0 = 1;
    for (; t > 0; t--)
    {
        while (!TF0)
            ;
        TF0 = 0;
    }
    TR0 = 0;
}
