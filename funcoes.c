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

CARACTERE* criarCaractere(int c[4]){
    CARACTERE *caractere = (CARACTERE*) malloc(sizeof(CARACTERE));
    caractere->ant = NULL;
    caractere->prox = NULL;
	for(int i=0; i < 4; i++){
		caractere->c[i] = c[i];
	}
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
	if(pos == 0){
		// Inserir Inicio
		inserirLinhaInicio(lista);
		return;
	}

	if(pos == lista->tamanho){
		// Inserir Final
		inserirLinhaFim(lista);
		return;
	}

    LINHA *linha;
    linha = criarLinha();
	lista->tamanho++;

    if(listaEstaVazia(lista)){
        lista->inicio = linha;
        lista->fim = linha;
    }else{
		if(pos <= lista->tamanho/2){
			// Comeca a buscar do inicio
			LINHA *linhaAnterior = NULL;
			LINHA *linhaAtual;
			linhaAtual = lista->inicio;
			int i=0;

			while(linhaAtual != NULL){
				if(i == pos){
					// Inserir Meio
					linhaAtual->ant = linha;
					linha->prox = linhaAtual;
					linha->ant = linhaAnterior;
					linhaAnterior->prox = linha;
					return;
				}
				i++;
				linhaAnterior = linhaAtual;
				linhaAtual = linhaAtual->prox;
			}
		}else{
			// Comeca a buscar do final
			LINHA *linhaProx = NULL;
			LINHA *linhaAtual;
			linhaAtual = lista->fim;
			int i=lista->tamanho;

			while(linhaAtual != NULL){
				if(i == pos){
					// Inserir Meio
					linhaAtual->prox = linha;
					linhaProx->ant = linha;
					linha->prox = linhaProx;
					linha->ant = linhaAtual;
					return;
				}
				i--;
				linhaProx = linhaAtual;
				linhaAtual = linhaAtual->ant;
			}
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
		return;
	}

	if(listaEstaVazia(lista)){
		printf("Lista vazia, impossivel remover!");
		return;
	}else{
		if(pos <= lista->tamanho/2){
			// Comeca a buscar do inicio
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
		}else{
			// Comeca a buscar do final
			LINHA *linhaProx = NULL;
			LINHA *linhaAtual;
			linhaAtual = lista->fim;
			int i=0;

			while(linhaAtual != NULL){
				if(i == pos){
					// Remover Meio
					linhaProx->ant = linhaAtual->ant;
					linhaAtual->ant->prox = linhaProx;
					lista->tamanho--;
					free(linhaAtual);
					return;
				}
				i++;
				linhaProx = linhaAtual;
				linhaAtual = linhaAtual->ant;
			}
		}
	}
}

int cadeiaEstaVazia(CADEIA *cadeia){
	if(cadeia->inicio == NULL || cadeia->fim == NULL)
		return 1;
	return 0;
}

void inserirCaractereCadeiaInicio(CADEIA *cadeia, int c[4]){
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

void inserirCaractereCadeiaFim(CADEIA *cadeia, int c[4]){
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

void inserirCaractereCadeiaPosicao(CADEIA *cadeia, int c[4], int pos){
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

	int caractere;
	while(!feof(file)){
		caractere = fgetc(file);
		if(caractere == EOF)
			break;
		if(caractere == '\n'){
			inserirLinhaFim(lista);
			aux = aux->prox;
		}else{
			int caractereCompleto[4] = {0,0,0,0};
			int i=0;
			while(i < numberOfBytesInChar((unsigned char)caractere) - 1) {
				caractereCompleto[i++] = caractere;
				caractere = fgetc(file);
			}
			caractereCompleto[i] = caractere;
			inserirCaractereCadeiaFim(aux->cadeia, caractereCompleto);
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
			for(int i=0; i < 4; i++){
				fputc(auxCadeia->c[i], file);
			}
			auxCadeia = auxCadeia->prox;
		}
		fputc('\n', file);
		auxLinha = auxLinha->prox;
	}
	fclose(file);
}


void getTerminalColumnsRows(int *columns, int *rows){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

LINHA *escreverCadeiasTela(LINHA *inicio, int startLinha, int endLinha, int startColuna, int endColuna){
	saveCursor();
	gotoxy(1, startLinha);
	LINHA *aux = inicio;
	LINHA *ant = NULL;
	int contLinhas = startLinha;
	while(aux != NULL && contLinhas <= endLinha){
		CARACTERE *auxCaractere = aux->cadeia->inicio;
		int contColunas=startColuna;
		while(auxCaractere != NULL && contColunas <= endColuna){
			int i;
			for(i=0; i < 4 && auxCaractere->c[i] != 0; i++){
				printf("%c", auxCaractere->c[i]);
			}
			contColunas++;
			auxCaractere = auxCaractere->prox;
		}
		cursorNextLine();
		contLinhas++;
		ant = aux;
		aux = aux->prox;
	}
	loadCursor();
	if(ant == NULL){
		return inicio;
	}
	return ant;
}

int getCursorRow(){
	int row=0;
	int c;

	cursorPosition();

	getch(); //eliminates the \033
	getch(); //eliminates the [
	c = getch(); //read first number
	while(c != ';'){
		row = row*10 + (int)c - '0';
		c = getch();
	}

	while(c != 'R'){
		c = getch();
	}
		
	return row;
}

int numberOfBytesInChar(unsigned char val){
	if(val < 128){
		return 1;
	}else if(val < 224){
		return 2;
	}else if(val < 240){
		return 3;
	}else{
		return 4;
	}
}
