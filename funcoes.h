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
}CADEIA;

typedef struct linha{
    CADEIA cadeia;
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
#include "funcoes.c"
#endif
