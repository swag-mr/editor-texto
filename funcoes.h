#ifndef _FUNCOES
#define _FUNCOES

typedef struct caractere{
    struct caractere ant;
    struct caractereprox;
    char c;
}CARACTERE;

typedef struct cadeia{
    CARACTERE inicio;
    CARACTEREfim;
}CADEIA;

typedef struct linha{
    CADEIA cadeia;
    struct linhaant;
    struct linha prox;
}LINHA;

typedef struct lista{
    LINHAinicio;
    LINHA fim;
}LISTA;

void inicializarCadeia(CADEIAc);
void inicializarLista(LISTA *l);
#include "funcoes.c"
#endif
