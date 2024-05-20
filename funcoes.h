#ifndef FUNCOES_H
#define FUNCOES_H

#define textoPadrao() printf("\033[37m")
#define fundoPadrao() printf("\033[40m")
#define textoVerde() printf("\033[32m")
#define textoVermelho() printf("\033[31m")
#define textoAmarelo() printf("\033[33m")
#define textoAzul() printf("\033[34m")
#define textoMagenta() printf("\033[35m")
#define textoCiano() printf("\033[36m")
#define padrao() printf("\033[0m")
#define CTRL_S 19
#define CTRL_Q 17
#define END 79
#define HOME 71
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
#define lineFeed() printf("\033[1L");
#define deleteLine() printf("\033[1M");
#define inserirChar() printf("\033[1@");
#define removerChar() printf("\033[1P");
#define hideCursor() printf("\033[?25l");
#define showCursor() printf("\033[?25h");
#define scrollMargins(s,e) printf("\033[%d;%dr", s, e)

#define horizontalLine() printf("\xE2\x94\x80");
#define verticalLine() printf("\xE2\x94\x82");
#define upperLeftCorner() printf("\xE2\x94\x8C");
#define upperRightCorner() printf("\xE2\x94\x90");
#define lowerLeftCorner() printf("\xE2\x94\x94");
#define lowerRightCorner() printf("\xE2\x94\x98");
#define subBlockRight() printf("\xE2\x94\x9C");
#define subBlockLeft() printf("\xE2\x94\xA4");

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

void desenharMoldura(int largura, int altura);

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
void inserirLinhaPosicao(LISTA *lista, LINHA *linhaAtual);

void removerLinhaInicio(LISTA *lista);
void removerLinhaFim(LISTA *lista);

void inserirCaractereCadeiaInicio(CADEIA *cadeia, UTFCHAR *c);
void inserirCaractereCadeiaFim(CADEIA *cadeia, UTFCHAR *c);
void inserirCaractereCadeiaPosicao(CADEIA *cadeia, UTFCHAR *c, int pos);

void desanexarParaNovaLinha(LISTA *lista, LINHA *linha, int posColuna);

void removerCaractereCadeiaInicio(CADEIA *cadeia);
void removerCaractereCadeiaFim(CADEIA *cadeia);
void removerCaractereCadeiaPosicao(CADEIA *cadeia, int pos);

void lerArquivoLista(char *nome, LISTA *lista);
void gravarListaArquivo(char *nome, LISTA *lista);
void getTerminalColumnsRows(int *columns, int *rows);

LINHA *escreverCadeiasTela(LINHA *inicio, int startLinha, int endLinha, int startColuna, int endColuna);
LINHA *determinarFimBuffer(LINHA *inicio, int start, int end);

int getCursorRow();

int numberOfBytesInChar(unsigned char val);

int veririficarNomeArquivo(char nome[]);
int menu(char arquivo[], int maxLinhas, int maxColunas, LISTA *lista);
void interfaceEditor(int largura, int altura, char *nomeArquivo);

#include "funcoes.c"
#endif
