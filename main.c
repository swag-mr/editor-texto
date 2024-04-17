#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

	inicializarLista(lista);

	lerArquivoLista("./arquivos/texto.txt", lista);

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
