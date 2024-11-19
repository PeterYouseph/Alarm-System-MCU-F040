#include "config.c"
#include <stdio.h>
#include <string.h>
#include "def_pinos.h"
#include "delay.h"
#include "fonte.c"
#include "glcd.h"
#include "bluetooth.h"
#include "buzzer.h"
#include "led_matrix.h"
#include "ultrasonic_sensor.h"
#include "watchdog.h"

void main(void)
{
    Init_Device();
    SFRPAGE = LEGACY_PAGE;

    init_GLCD();
    init_bluetooth();
    init_watchdog();

    // Limpar GLCD no início
    limpa_glcd(GLCD_ESQ);
    limpa_glcd(GLCD_DIR);
    // Config page do GLCD
    conf_pag(0, GLCD_ESQ);
    conf_pag(0, GLCD_DIR);

     printf_fast_f("\x2
                      Dist.: %3u cm");

    // Loop principal do sistema de alarme
    while (1)
    {
        // unsigned int distancia = le_hcsr04();

        // Verifica a distância medida pelo sensor ultrassônico
        // printf_fast_f("\x2
        //               Dist.: %3u cm");
        // if (distancia < 30)
        // { // Distância menor que 30cm aciona o alarme
        //     buzzer();
        //     desloca_texto("ALARM!", 200);

        // }

        // Comunicação Bluetooth
        verifica_bluetooth_comando();

        // Reseta o watchdog timer
        reset_watchdog();

        delay_ms(500); // Delay para evitar leituras contínuas
    }
}
