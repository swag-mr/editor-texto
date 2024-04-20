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

typedef struct utf_byte{
	unsigned char byte;
	struct utf_byte *prox;
}UTFBYTE;

typedef struct utf_char{
	UTFBYTE *inicio;
}UTFCHAR;

typedef struct caractere{
    struct caractere *ant;
    struct caractere *prox;
    UTFCHAR *utfChar;
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
void inicializarUtfChar(UTFCHAR *u);

int cadeiaEstaVazia(CADEIA *cadeia);
int listaEstaVazia(LISTA *l);

UTFBYTE *criarUtfByte(unsigned char c);
CARACTERE *criarCaractere(UTFCHAR *c);
LINHA *criarLinha();

void inserirUtfByte(UTFCHAR *u, unsigned char c);

void inserirLinhaFim(LISTA *lista);
void inserirLinhaInicio(LISTA *lista);
void inserirLinhaPosicao(LISTA *lista, int pos);

void removerLinhaInicio(LISTA *lista);
void removerLinhaFim(LISTA *lista);

void inserirCaractereCadeiaInicio(CADEIA *cadeia, UTFCHAR *c);
void inserirCaractereCadeiaFim(CADEIA *cadeia, UTFCHAR *c);
void inserirCaractereCadeiaPosicao(CADEIA *cadeia, UTFCHAR *c, int pos);

void removerCaractereCadeiaInicio(CADEIA *cadeia);
void removerCaractereCadeiaFim(CADEIA *cadeia);
void removerCaractereCadeiaPosicao(CADEIA *cadeia, int pos);

void lerArquivoLista(char *nome, LISTA *lista);
void gravarListaArquivo(char *nome, LISTA *lista);
void getTerminalColumnsRows(int *columns, int *rows);

LINHA *escreverCadeiasTela(LINHA *inicio, int startLinha, int endLinha, int startColuna, int endColuna);

int getCursorRow();

int numberOfBytesInChar(unsigned char val);
#include "funcoes.c"
#endif
