#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarCadeia(CADEIA *c){
    c->inicio = NULL;
    c->fim = NULL;
    c->tamanho = 0;
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
    linha->cadeia = (CADEIA*) malloc(sizeof(CADEIA));
    linha->ant = NULL;
    linha->prox = NULL;

	inicializarCadeia(linha->cadeia);
    return linha;
}

int listaEstaVazia(LISTA *l){
    if(l->inicio == NULL || l->fim == NULL){
        return 1;
    }
    return 0;
}

void inserirLinhaInicio(LISTA *lista){
    LINHA *linha;
    linha = criarLinha();
	lista->tamanho++;

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
	lista->tamanho++;

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
	lista->tamanho++;

    if(listaEstaVazia(lista)){
        lista->inicio = linha;
        lista->fim = linha;
    }else{
        LINHA *linhaAnterior = NULL;
        LINHA *linhaAtual;
		linhaAtual = lista->inicio;
        int i=0;

        while(linhaAtual != NULL){
            if(i == pos){
                if(linhaAnterior == NULL){
                    // Inserir Inicio
                    linha->prox = lista->inicio;
                    lista->inicio->ant = linha;
                    lista->inicio = linha;
					return;
                }else{
                    // Inserir Meio
                    linhaAtual->ant = linha;
                    linha->prox = linhaAtual;
                    linha->ant = linhaAnterior;
					linhaAnterior->prox = linha;
					return;
                }
            }
            i++;
            linhaAnterior = linhaAtual;
            linhaAtual = linhaAtual->prox;
        }
        //Inserir no final
        lista->fim->prox = linha;
        linha->ant = lista->fim;
        lista->fim = linha;
        
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
		lista->tamanho--;
        free(linhaAux);

        if(lista->inicio == NULL){
            lista->fim = lista->inicio;
			return;
        }
        lista->inicio->ant = NULL;
    }
}

void removerLinhaFim(LISTA *lista){
    if(listaEstaVazia(lista)){
        printf("Lista vazia, impossivel remover!");
        return;
    }else{
        LINHA *linhaAux = NULL;
        linhaAux = lista->fim;

        lista->fim = lista->fim->ant;
		lista->tamanho--;
        free(linhaAux);

        if(lista->fim == NULL){
            lista->inicio = lista->fim;
			return;
        }

        lista->fim->prox = NULL;
    }
}

void removerLinhaPosicao(LISTA *lista, int pos){
	if(pos == 0){
		// Remover Inicio
		removerLinhaInicio(lista);
		return;
	}

	if(pos == lista->tamanho-1){
		// Remover Final
		removerLinhaFim(lista);
	}

	if(listaEstaVazia(lista)){
		printf("Lista vazia, impossivel remover!");
		return;
	}else{
		LINHA *linhaAnterior = NULL;
		LINHA *linhaAtual;
		linhaAtual = lista->inicio;
		int i=0;

		while(linhaAtual != NULL){
			if(i == pos){
				// Remover Meio
				linhaAnterior->prox = linhaAtual->prox;
				linhaAtual->prox->ant = linhaAnterior;
				lista->tamanho--;
				free(linhaAtual);
				return;
			}
			i++;
			linhaAnterior = linhaAtual;
			linhaAtual = linhaAtual->prox;
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
	cadeia->tamanho--;

	free(aux);
	if(cadeiaEstaVazia(cadeia)){
		cadeia->fim = NULL;
		return;
	}

	cadeia->inicio->ant = NULL;
}

void removerCaractereCadeiaFim(CADEIA *cadeia){
	if(cadeiaEstaVazia(cadeia)){
		printf("Cadeia vazia, impossível remover caractere\n");
		return;
	}

	CARACTERE *aux = cadeia->fim;
	cadeia->fim = aux->ant;
	cadeia->tamanho--;
	free(aux);

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = NULL;
	}
	cadeia->fim->prox = NULL;
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

void lerArquivoLista(char *nome, LISTA *lista){
	FILE *file = fopen(nome, "r");

	inserirLinhaFim(lista);

	LINHA *aux = lista->inicio;

	char c;
	while(!feof(file)){
		c = fgetc(file);
		if(c == EOF)
			break;
		if(c == '\n'){
			inserirLinhaFim(lista);
			aux = aux->prox;
		}else{
			inserirCaractereCadeiaFim(aux->cadeia, c);
		}
	}
	fclose(file);

	removerLinhaFim(lista);
}

void gravarListaArquivo(char *nome, LISTA *lista){
	FILE *file = fopen(nome, "w");
	LINHA *auxLinha = lista->inicio;
	while(auxLinha != NULL){
		CARACTERE *auxCadeia = auxLinha->cadeia->inicio;
		while(auxCadeia != NULL){
			fputc(auxCadeia->c, file);
			auxCadeia = auxCadeia->prox;
		}
		fputc('\n', file);
		auxLinha = auxLinha->prox;
	}
	fclose(file);
}

