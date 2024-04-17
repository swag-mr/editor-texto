#ifndef _FUNCOES
#define _FUNCOES

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

CARACTERE *criarCaractere(char c);

void inserirCaractereCadeiaInicio(CADEIA *cadeia, char c);
void inserirCaractereCadeiaFim(CADEIA *cadeia, char c);
void inserirCaractereCadeiaPosicao(CADEIA *cadeia, char c, int pos);

void removerCaractereCadeiaInicio(CADEIA *cadeia);
void removerCaractereCadeiaFim(CADEIA *cadeia);
void removerCaractereCadeiaPosicao(CADEIA *cadeia, int pos);

void imprimirCadeia(CADEIA *cadeia);
void imprimirCadeiaInversa(CADEIA *cadeia);
#include "funcoes.c"
#endif
