void inicializarCadeia(CADEIA c){
    c->inicio = NULL;
    c->fim = NULL;
}

void inicializarLista(LISTAl){
    l->inicio = NULL;
    l->fim = NULL;
}

CARACTERE criarCaractere(char c){
    CARACTEREcaractere = (CARACTERE)malloc(sizeof(CARACTERE));
    caractere->ant = NULL;
    caractere->prox = NULL;
    caractere->c = c;
    return caractere;
}

LINHAcriarLinha(){
    LINHA linha = (LINHA)malloc(sizeof(LINHA));
    linha->cadeia = NULL;
    linha->ant = NULL;
    linha->prox = NULL;
    return linha;
}

void inserirCaractereCadeiaInicio(CADEIA cadeia, char c){
    CARACTEREcaractere = criarCaractere(c);
    caractere->prox =
}
