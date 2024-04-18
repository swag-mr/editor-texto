#ifndef FUNCOES_H
#define FUNCOES_H

#define PAGE_UP 73
#define PAGE_DOWN 81
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define BACKSPACE 8
#define ENTER 13
#define clear() printf("\033[H\033[J")
#define clearTillEndLine() printf("\033[K")
#define clearTillEndScreen() printf("\033[J")
#define cursorPrevLine() printf("\033[F")
#define cursorNextLine() printf("\033[E")
#define cursorUp() printf("\033[A")
#define cursorDown() printf("\033[B")
#define cursorRight() printf("\033[C")
#define cursorLeft() printf("\033[D")
#define scrollDown() printf("\033[1S")
#define scrollUp() printf("\033[1T")
#define saveCursor() printf("\033[s");
#define loadCursor() printf("\033[u");
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define cursorPosition() printf("\033[6n")

typedef struct caractere{
    struct caractere *ant;
    struct caractere *prox;
    char c;
}CARACTERE;

typedef struct cadeia{
    CARACTERE *inicio;
    CARACTERE *fim;
	int tamanho;
}CADEIA;

typedef struct linha{
    CADEIA *cadeia;
    struct linha *ant;
    struct linha *prox;
}LINHA;

typedef struct lista{
    LINHA *inicio;
    LINHA *fim;
    int tamanho;
}LISTA;

void inicializarCadeia(CADEIA *c);
void inicializarLista(LISTA *l);

int cadeiaEstaVazia(CADEIA *cadeia);
int listaEstaVazia(LISTA *l);

CARACTERE *criarCaractere(char c);
LINHA *criarLinha();

void inserirLinhaFim(LISTA *lista);
void inserirLinhaInicio(LISTA *lista);
void inserirLinhaPosicao(LISTA *lista, int pos);

void removerLinhaInicio(LISTA *lista);
void removerLinhaFim(LISTA *lista);

void inserirCaractereCadeiaInicio(CADEIA *cadeia, char c);
void inserirCaractereCadeiaFim(CADEIA *cadeia, char c);
void inserirCaractereCadeiaPosicao(CADEIA *cadeia, char c, int pos);

void removerCaractereCadeiaInicio(CADEIA *cadeia);
void removerCaractereCadeiaFim(CADEIA *cadeia);
void removerCaractereCadeiaPosicao(CADEIA *cadeia, int pos);

void imprimirCadeia(CADEIA *cadeia);
void imprimirCadeiaInversa(CADEIA *cadeia);

void lerArquivoLista(char *nome, LISTA *lista);
void gravarListaArquivo(char *nome, LISTA *lista);
void getTerminalColumnsRows(int *columns, int *rows);

LINHA *escreverCadeiasTela(LINHA *inicio, int startLinha, int endLinha, int startColuna, int endColuna);

int getCursorRow();
#include "funcoes.c"
#endif
