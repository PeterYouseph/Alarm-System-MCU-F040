#include "led_matrix.h"
#include "delay.h"

__code unsigned char caract[44][4] = {
    {0xFF, 0x81, 0x81, 0xFF}, // 0
    {0x84, 0x82, 0xFF, 0x80}, // 1
    {0xF9, 0x99, 0x99, 0x9F}, // 2
    {0x99, 0x99, 0x99, 0xFF}, // 3
    {0x1F, 0x10, 0x10, 0xFF}, // 4
    {0x9F, 0x99, 0x99, 0xF9}, // 5
    {0xFF, 0x99, 0x99, 0xF9}, // 6
    {0x01, 0x01, 0xFF, 0x00}, // 7
    {0xFF, 0x99, 0x99, 0xFF}, // 8
    {0x9F, 0x99, 0x99, 0xFF}  // 9
};

void desloca_display(unsigned char novo)
{
    P0 = P1;
    P1 = P2;
    P2 = P3;
    SFRPAGE = CONFIG_PAGE;
    P3 = P4;
    P4 = P5;
    P5 = P6;
    P6 = P7;
    P7 = novo;
    SFRPAGE = LEGACY_PAGE;
}

void desloca_texto(unsigned char *pont, unsigned int delay)
{
    unsigned char i, *repr;
    unsigned char prox[5];

    P0 = P1 = P2 = P3 = P4 = P5 = P6 = P7 = 0;
    while (*pont)
    {
        repr = caract[*pont - 48];
        prox[0] = repr[0];
        prox[1] = repr[1];
        prox[2] = repr[2];
        prox[3] = repr[3];
        prox[4] = 0;

        for (i = 0; i < 5; i++)
        {
            desloca_display(prox[i]);
            delay_ms(delay);
        }
        pont++;
    }
}
