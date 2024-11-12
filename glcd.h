#ifndef GLCD_H
#define GLCD_H

void glcd_init();                                      // Inicializa o display
void putchar(char c);                                  // Função para escrever um caractere no display do GLCD
void init_GLCD(void);                                  // Inicializa o display
void limpa_glcd(__bit cs);                             // Limpa o display
void conf_Y(unsigned char y, __bit cs);                // Configura a posição Y
void conf_pag(unsigned char pag, __bit cs);            // Configura a página
unsigned char le_glcd(__bit cd, __bit cs);             // Lê um dado do display
void esc_glcd(unsigned char dado, __bit cd, __bit cs); // Escreve um dado no display

#endif
