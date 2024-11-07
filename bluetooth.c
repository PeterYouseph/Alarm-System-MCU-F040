#include "bluetooth.h"
#include <stdio.h>

volatile __bit comando_recebido = 0;
volatile unsigned char comando;

void init_bluetooth()
{
    // Configuração inicial da comunicação UART para o módulo Bluetooth
    SCON0 = 0x50; // Modo UART 8 bits, taxa de 9600 bps
    TMOD |= 0x20; // Timer 1, modo 2, auto-reload
    TH1 = 0xFD;   // Configuração para 9600 bps
    TR1 = 1;      // Ativa o Timer 1
    TI0 = 1;      // Indica pronto para transmitir
    EA = 1;       // Habilita interrupções globais
    ES0 = 1;      // Habilita interrupções do UART
}

void putchar(char c)
{
    SBUF0 = c;
    while (!TI0)
        ;
    TI0 = 0;
}

// ISR para o UART, armazena o comando recebido
void uart_ISR() __interrupt 4
{
    if (RI0)
    {
        comando = SBUF0;
        comando_recebido = 1;
        RI0 = 0;
    }
}

void verifica_bluetooth_comando()
{
    if (comando_recebido)
    {
        comando_recebido = 0;
        if (comando == 'm')
        {
            printf("MENU:\na - Check distance\nb - Activate alarm\n");
        }
        else if (comando == 'a')
        {
            unsigned int distancia = le_hcsr04();
            printf("Distance: %u cm\n", distancia);
        }
        else if (comando == 'b')
        {
            buzzer();
            printf("Alarm activated.\n");
        }
    }
}
