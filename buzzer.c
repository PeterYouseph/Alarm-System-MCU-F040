#include "buzzer.h"
#include "delay.h"
#include "def_pinos.h"

#define BUZZER P2_7 // Pino do buzzer no MCU

void buzzer()
{
    BUZZER = 1;
    delay_ms(100);
    BUZZER = 0;
}

void init_buzzer()
{
    BUZZER = 0; // Configura o pino do buzzer como saída inicial
}
