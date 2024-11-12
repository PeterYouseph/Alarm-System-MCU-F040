#include "config.c"
#include <stdio.h>
#include <string.h>
#include "def_pinos.h"
#include "delay.h"
// #include "fonte.c"
#include "glcd.h"
#include "bluetooth.h"
#include "buzzer.h"
#include "led_matrix.h"
#include "ultrasonic_sensor.h"
#include "watchdog.h"

void main(void)
{
    SFRPAGE = LEGACY_PAGE;
    Init_Device();
    init_GLCD();
    init_bluetooth();
    init_watchdog();

    // Limpar GLCD no início
    limpa_glcd(GLCD_ESQ);
    limpa_glcd(GLCD_DIR);

    // Loop principal do sistema de alarme
    while (1)
    {
        unsigned int distancia = le_hcsr04();

        // Verifica a distância medida pelo sensor ultrassônico
        if (distancia < 30)
        { // Distância menor que 30cm aciona o alarme
            buzzer();
            desloca_texto("ALARM!", 200);
            printf("Intruder detected! Dist.: %5u cm\n", distancia);
        }

        // Comunicação Bluetooth
        verifica_bluetooth_comando();

        // Reseta o watchdog timer
        reset_watchdog();

        delay_ms(500); // Delay para evitar leituras contínuas
    }
}
