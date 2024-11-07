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

unsigned char le_glcd(__bit cd, __bit cs)
{
    unsigned char dado;
    GLCD_RW = 1;   // Leitura
    GLCD_CS1 = cs; // Escolha do lado do display
    GLCD_CS2 = !cs;
    GLCD_RS = cd; // Comando ou dado. RS == D/I
    NOP4();
    GLCD_ENABLE = 1;
    NOP8();
    SFRPAGE = CONFIG_PAGE; // Para acessar P4 (para ler DB)
    dado = GLCD_DB;
    SFRPAGE = LEGACY_PAGE; // Volto para P0
    NOP4();
    GLCD_ENABLE = 0;
    NOP12();
    return dado;
}

void esc_glcd(unsigned char dado, __bit cd, __bit cs)
{
    // Checar status
    unsigned char status;
    do
        status = le_glcd(GLCD_CO, cs);
    while (status & 0x80);

    GLCD_RW = 0;   // Escrita
    GLCD_CS1 = cs; // Escolha do lado do display
    GLCD_CS2 = !cs;
    GLCD_RS = cd;          // Comando ou dado. RS == D/I
    SFRPAGE = CONFIG_PAGE; // Para acessar P4 (para ler DB)
    GLCD_DB = dado;
    SFRPAGE = LEGACY_PAGE; // Volto para P0
    NOP4();
    GLCD_ENABLE = 1;
    NOP12();
    GLCD_ENABLE = 0;
    SFRPAGE = CONFIG_PAGE; // Para acessar P4 (para ler DB)
    GLCD_DB = 0xFF;
    SFRPAGE = LEGACY_PAGE; // Volto para P0
    NOP12();
}

void conf_Y(unsigned char y, __bit cs)
{
    // Um or, para ou usar o padrão, ou o que está sendo chamado
    y = y & 0x7F;
    y = y | 0x40;
    esc_glcd(y, GLCD_CO, cs);
}

void conf_pag(unsigned char pag, __bit cs)
{
    pag = pag & 0x07; // estou protegendo este os bits que me interessam
    pag = pag | 0xB8;
    esc_glcd(pag, GLCD_CO, cs);
}

void limpa_glcd(__bit cs)
{
    unsigned char i;
    unsigned char j;

    for (i = 0; i < 8; i++)
    {
        conf_Y(0, cs);
        conf_pag(i, cs);
        for (j = 0; j < 64; j++)
        {
            esc_glcd(0, GLCD_DA, cs);
        }
    }
}

void init_GLCD(void)
{
    // Estado inicial
    GLCD_ENABLE = LOW;
    GLCD_CS1 = GLCD_CS2 = GLCD_RST = HIGH;
    SFRPAGE = CONFIG_PAGE;
    GLCD_DB = 0xFF;
    SFRPAGE = LEGACY_PAGE;

    // Aguardar por status
    while (le_glcd(GLCD_CO, GLCD_ESQ) & 0x80)
    {
    }
    while (le_glcd(GLCD_CO, GLCD_DIR) & 0x80)
    {
    }

    // Liga o controlador
    esc_glcd(0x3F, GLCD_CO, GLCD_ESQ);
    esc_glcd(0x3F, GLCD_CO, GLCD_DIR);

    // Y = 0
    esc_glcd(0x40, GLCD_CO, GLCD_ESQ);
    esc_glcd(0x40, GLCD_CO, GLCD_DIR);

    // X = 0
    esc_glcd(0xB8, GLCD_CO, GLCD_ESQ);
    esc_glcd(0xB8, GLCD_CO, GLCD_DIR);

    // Z = 0
    esc_glcd(0xC0, GLCD_CO, GLCD_ESQ);
    esc_glcd(0xC0, GLCD_CO, GLCD_DIR);
}

void putchar(char c) // Função para escrever um caractere no display do GLCD
{
    static unsigned char coluna = 0;
    unsigned char lado = (coluna < 8) ? GLCD_ESQ : GLCD_DIR;

    if (1 <= c && c <= 8)
    {
        conf_pag(c - 1, GLCD_ESQ);
        conf_pag(c - 1, GLCD_DIR);
        conf_Y(0, GLCD_ESQ);
        conf_Y(0, GLCD_DIR);
        coluna = 0;
    }
    else
    {
        esc_glcd(fonte[c - 32][0], GLCD_DA, lado);
        esc_glcd(fonte[c - 32][1], GLCD_DA, lado);
        esc_glcd(fonte[c - 32][2], GLCD_DA, lado);
        esc_glcd(fonte[c - 32][3], GLCD_DA, lado);
        esc_glcd(fonte[c - 32][4], GLCD_DA, lado);

        esc_glcd(0, GLCD_DA, lado);
        esc_glcd(0, GLCD_DA, lado);
        esc_glcd(0, GLCD_DA, lado);

        coluna = (coluna + 1) & 0xf;
    }
}