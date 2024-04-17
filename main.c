#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

	inicializarLista(lista);
	
	lerArquivoLista("./arquivos/texto.txt", lista);
	gravarListaArquivo("./arquivos/novo.txt", lista);
    return 0;
}
