// Este arquivo tem funções e variáveis definidas para os botões do shield de interface da Circuitar.

// Pino analógico em que estão conectados os botões do shield de interface.
// Mais detalhes aqui: https://www.circuitar.com.br/nanoshields/modulos/interface/
#define BOTOES A0

// Cada tecla recebe um nome para facilitar a identificação no código.
#define SEM_TECLA 0
#define TECLA_SEL 1

#define TECLA_ESQ 2
#define TECLA_BAIXO 3
#define TECLA_CIMA 4
#define TECLA_DIR 5


void inicia_teclas();    
int tecla_pressionada();
