#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

	inicializarLista(lista);

	inserirLinhaInicio(lista);
	inserirLinhaInicio(lista);
	inserirLinhaInicio(lista);
	/*
	inserirLinhaFim(lista);
	inserirLinhaFim(lista);
	inserirLinhaPosicao(lista, 1);
	inserirLinhaPosicao(lista, 2);*/

	inserirCaractereCadeiaFim(lista->inicio->cadeia, 'J');
	inserirCaractereCadeiaFim(lista->inicio->cadeia, 'o');
	inserirCaractereCadeiaFim(lista->inicio->cadeia, 's');
	inserirCaractereCadeiaFim(lista->inicio->cadeia, 'e');

	inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'V');
	inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'i');
	inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 't');
	inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'o');
	inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'r');

	inserirCaractereCadeiaFim(lista->fim->cadeia, 'K');
	inserirCaractereCadeiaFim(lista->fim->cadeia, 'a');
	inserirCaractereCadeiaFim(lista->fim->cadeia, 'u');
	inserirCaractereCadeiaFim(lista->fim->cadeia, 'a');
	inserirCaractereCadeiaFim(lista->fim->cadeia, 'n');

	removerCaractereCadeiaFim(lista->fim->cadeia);

	LINHA *aux = lista->inicio;
	while(aux != NULL){
		printf("Cadeia: ");
		imprimirCadeia(aux->cadeia);
		printf("\n");
		printf("Caracteres: %d\n",aux->cadeia->tamanho);
		printf("\n");
		aux = aux->prox;
	}

	printf("Qtd: %d\n", lista->tamanho);

	/*
	CADEIA *cadeia = (CADEIA*)malloc(sizeof(CADEIA));

	inicializarCadeia(cadeia);

	inserirCaractereCadeiaInicio(cadeia, 'J');
	inserirCaractereCadeiaFim(cadeia, 'e');
	inserirCaractereCadeiaPosicao(cadeia, 'o', 1);
	inserirCaractereCadeiaPosicao(cadeia, 's', 2);

	inserirCaractereCadeiaFim(cadeia, 'x');
	inserirCaractereCadeiaInicio(cadeia, 'y');

	removerCaractereCadeiaInicio(cadeia);
	removerCaractereCadeiaFim(cadeia);
	removerCaractereCadeiaPosicao(cadeia, 1);
	removerCaractereCadeiaPosicao(cadeia, 3);

	printf("Cadeia: ");
	imprimirCadeia(cadeia);
	printf("\n");

	printf("Cadeia invertida: ");
	imprimirCadeiaInvertida(cadeia);*/
    return 0;
}
