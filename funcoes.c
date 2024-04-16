void inicializarCadeia(CADEIA *c){
    c->inicio = NULL;
    c->fim = NULL;
}

void inicializarLista(LISTA *l){
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
}

CARACTERE* criarCaractere(char c){
    CARACTERE *caractere = (CARACTERE*) malloc(sizeof(CARACTERE));
    caractere->ant = NULL;
    caractere->prox = NULL;
    caractere->c = c;
    return caractere;
}

LINHA* criarLinha(){
    LINHA *linha = (LINHA*) malloc(sizeof(LINHA));
    linha->cadeia = NULL;
    linha->ant = NULL;
    linha->prox = NULL;
    return linha;
}

int listaEstaVazia(LISTA *l){
    if(l->inicio == NULL){
        return 1;
    }
    return 0;
}

void inserirLinhaInicio(LISTA *lista){
    LINHA *linha;
    linha = criarLinha();

    if(listaEstaVazia(lista)){
        lista->inicio = linha;
        lista->fim = linha;
    }else{
        linha->prox = lista->inicio;
        lista->inicio->ant = linha;
        lista->inicio = linha;
    }
}

void inserirLinhaFim(LISTA *l){
    LINHA *linha;
    linha = criarLinha();

    if(listaEstaVazia(lista)){
        lista->inicio = linha;
        lista->fim = linha;
    }else{
        lista->fim->prox = linha;
        linha->ant = lista->fim;
        lista->fim = linha;
    }
}

void inserirLinhaPosicao(LISTA *lista, int pos){
    LINHA *linha;
    linha = criarLinha();

    if(listaEstaVazia(lista)){
        lista->inicio = linha;
        lista->fim = linha;
    }else{
        if((pos > lista->tamanho) || (pos < 0)){
            if(pos > lista->tamanho){
                // Inserir no final
                lista->fim->prox = linha;
                linha->ant = lista->fim;
                lista->fim = linha;
            }else{
                // Inserir no inicio
                linha->prox = lista->inicio;
                lista->inicio->ant = linha;
                lista->inicio = linha;
            }
        }else{
            LINHA *linhaAnterior;
            LINHA *linhaProx;
            linhaAnterior = NULL;
            linha = lista->inicio;
            linhaProx = lista->inicio->prox;
            int i=0;

            while(linha != NULL){
                if(i == pos){
                    if(linhaAnterior == NULL){
                        // Inserir Inicio
                        linha->prox = lista->inicio;
                        lista->inicio->ant = linha;
                        lista->inicio = linha;
                    }else{
                        // Inserir Meio
                        linhaAnterior->prox = linha;
                        linhaProx->ant = linha;
                        linha->prox = linhaProx;
                        linha->ant = linhaAnterior;
                    }
                }
                i++;
                linhaAnterior = linhaAux;
                linhaAux = linhaProx;
                linhaProx = linhaProx->prox;
            }
            //Inserir no final
            lista->fim->prox = linha;
            linha->ant = lista->fim;
            lista->fim = linha;
        }
    }
}

void removerLinhaInicio(LISTA *lista){
    if(listaEstaVazia(lista)){
        printf("Lista vazia, impossivel remover!");
        return;
    }else{
        LINHA *linhaAux = NULL;
        linhaAux = lista->inicio;

        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        free(linhaAux);

        if(lista->inicio == NULL){
            lista->fim = lista->inicio;
        }
    }
}

void removerLinhaFinal(LISTA *lista){
    if(listaEstaVazia(lista)){
        printf("Lista vazia, impossivel remover!");
        return;
    }else{
        LINHA *linhaAux = NULL;
        linhaAux = lista->fim;

        lista->fim = lista->fim->ant;
        lista->fim->prox = NULL;
        free(linhaAux);

        if(lista->fim == NULL){
            lista->inicio = lista->fim;
        }
    }
}
