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

void inserirLinhaFim(LISTA *lista){
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
                linhaAnterior = linha;
                linha = linhaProx;
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

int cadeiaEstaVazia(CADEIA *cadeia){
	if(cadeia->inicio == NULL || cadeia->fim == NULL)
		return 1;
	return 0;
}

void inserirCaractereCadeiaInicio(CADEIA *cadeia, char c){
	CARACTERE *caractere = criarCaractere(c);
	cadeia->tamanho++;

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = caractere;
		cadeia->fim = caractere;
		return;
	}

	caractere->prox = cadeia->inicio;
	cadeia->inicio->ant = caractere;
	cadeia->inicio = caractere;
}

void inserirCaractereCadeiaFim(CADEIA *cadeia, char c){
	CARACTERE *caractere = criarCaractere(c);
	cadeia->tamanho++;

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = caractere;
		cadeia->fim = caractere;
		return;
	}

	caractere->ant = cadeia->fim;
	cadeia->fim->prox = caractere;
	cadeia->fim = caractere;
}

void inserirCaractereCadeiaPosicao(CADEIA *cadeia, char c, int pos){
	if(pos > cadeia->tamanho){
		printf("Posição inválida\n");
		return;
	}

	CARACTERE *caractere = criarCaractere(c);
	cadeia->tamanho++;

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = caractere;
		cadeia->fim = caractere;
		return;
	}

	CARACTERE *aux = cadeia->inicio;
	CARACTERE *ant = NULL;
	int cont = 0;
	while(aux != NULL && cont < pos){
		cont++;
		ant = aux;
		aux = aux->prox;
	}

	if(ant == NULL){
		caractere->prox = cadeia->inicio;
		cadeia->inicio->ant = caractere;
		cadeia->inicio = caractere;
		return;
	}

	caractere->ant = ant;
	ant->prox = caractere;
	caractere->prox = aux;
	aux->ant = caractere;
}

void removerCaractereCadeiaInicio(CADEIA *cadeia){
	if(cadeiaEstaVazia(cadeia)){
		printf("Cadeia vazia, impossível remover caractere\n");
		return;
	}

	CARACTERE *aux = cadeia->inicio;
	cadeia->inicio = aux->prox;
	cadeia->inicio->ant = NULL;
	free(aux);
	cadeia->tamanho--;

	if(cadeiaEstaVazia(cadeia)){
		cadeia->fim = NULL;
	}
}

void removerCaractereCadeiaFim(CADEIA *cadeia){
	if(cadeiaEstaVazia(cadeia)){
		printf("Cadeia vazia, impossível remover caractere\n");
		return;
	}

	CARACTERE *aux = cadeia->fim;
	cadeia->fim = aux->ant;
	cadeia->fim->prox = NULL;
	free(aux);
	cadeia->tamanho--;

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = NULL;
	}
}
void removerCaractereCadeiaPosicao(CADEIA *cadeia, int pos){
	if(pos > cadeia->tamanho){
		printf("Posição inválida\n");
		return;
	}

	if(pos == 1){
		removerCaractereCadeiaInicio(cadeia);
		return;
	}

	if(pos == cadeia->tamanho){
		removerCaractereCadeiaFim(cadeia);
		return;
	}

	if(cadeiaEstaVazia(cadeia)){
		printf("Cadeia vazia, impossível remover caractere\n");
		return;
	}

	CARACTERE *aux = cadeia->inicio;
	CARACTERE *ant = NULL;
	cadeia->tamanho--;

	int cont = 0;

	while(aux != NULL && cont < pos-1){
		cont++;
		ant = aux;
		aux = aux->prox;
	}

	ant->prox = aux->prox;
	aux->prox->ant = ant;

	free(aux);

	if(cadeiaEstaVazia(cadeia)){
		cadeia->fim = NULL;
		cadeia->inicio = NULL;
	}
}

void imprimirCadeia(CADEIA *cadeia){
	CARACTERE *aux = cadeia->inicio;

	while(aux != NULL){
		printf("%c", aux->c);
		aux = aux->prox;
	}
}

void imprimirCadeiaInvertida(CADEIA *cadeia){
	CARACTERE *aux = cadeia->fim;

	while(aux != NULL){
		printf("%c", aux->c);
		aux = aux->ant;
	}
}
