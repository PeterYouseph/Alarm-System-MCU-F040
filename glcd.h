#ifndef GLCD_H
#define GLCD_H
#include "def_pinos.h"
#include "fonte.c"
// #include "config.c"

void glcd_init();                                      // Inicializa o display
void putchar(char c);                                  // Função para escrever um caractere no display do GLCD
void init_GLCD(void);                                  // Inicializa o display
void limpa_glcd(__bit cs);                             // Limpa o display
void conf_Y(unsigned char y, __bit cs);                // Configura a posição Y
void conf_pag(unsigned char pag, __bit cs);            // Configura a página
unsigned char le_glcd(__bit cd, __bit cs);             // Lê um dado do display
void esc_glcd(unsigned char dado, __bit cd, __bit cs); // Escreve um dado no display

#define NOP4() \
    NOP();     \
    NOP();     \
    NOP();     \
    NOP()
#define NOP8() \
    NOP4();    \
    NOP4()
#define NOP12() \
    NOP8();     \
    NOP4()

#define GLCD_ESQ 0
#define GLCD_DIR 1
#define GLCD_CO 0
#define GLCD_DA 1
#define GLCD_CS1 P2_0
#define GLCD_CS2 P2_1
#define GLCD_RST P2_5
#define GLCD_RS P2_2
#define GLCD_RW P2_3
#define GLCD_ENABLE P2_4
#define GLCD_DB P4
#define LOW 0
#define HIGH 1
#define TECS_OPEN 255

#endif
