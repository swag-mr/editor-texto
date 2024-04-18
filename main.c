#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "funcoes.h"

#define PAGE_UP 73
#define PAGE_DOWN 81
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define BACKSPACE 8
#define ENTER 13
#define clear() printf("\033[H\033[J")
#define clearTillEnd() printf("\033[K")
#define cursorPrevLine() printf("\033[F")
#define cursorNextLine() printf("\033[E")
#define cursorUp() printf("\033[A")
#define cursorDown() printf("\033[B")
#define cursorRight() printf("\033[C")
#define cursorLeft() printf("\033[D")
#define scrollDown() printf("\033[10S")
#define scrollUp() printf("\033[10T")

int main(){
	int opc;

	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

	inicializarLista(lista);

	// inserirLinhaInicio(lista);
	// inserirLinhaInicio(lista);
	// inserirLinhaInicio(lista);

	// inserirCaractereCadeiaFim(lista->inicio->cadeia, 'J');
	// inserirCaractereCadeiaFim(lista->inicio->cadeia, 'o');
	// inserirCaractereCadeiaFim(lista->inicio->cadeia, 's');
	// inserirCaractereCadeiaFim(lista->inicio->cadeia, 'e');

	// inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'V');
	// inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'i');
	// inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 't');
	// inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'o');
	// inserirCaractereCadeiaFim(lista->inicio->prox->cadeia, 'r');

	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'K');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'a');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'u');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'a');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'n');

	// removerCaractereCadeiaFim(lista->fim->cadeia);

	// LINHA *aux = lista->inicio;
	// while(aux != NULL){
	// 	printf("Cadeia: ");
	// 	imprimirCadeia(aux->cadeia);
	// 	printf("\n");
	// 	printf("Caracteres: %d\n",aux->cadeia->tamanho);
	// 	printf("\n");
	// 	aux = aux->prox;
	// }

	// printf("\n\n=====================\n\n");

	// inserirLinhaPosicao(lista, 3);

	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'H');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'E');
	// inserirCaractereCadeiaFim(lista->fim->cadeia, 'O');

	// LINHA *aux1 = lista->inicio;
	// while(aux1 != NULL){
	// 	printf("Cadeia: ");
	// 	imprimirCadeia(aux1->cadeia);
	// 	printf("\n");
	// 	printf("Caracteres: %d\n",aux1->cadeia->tamanho);
	// 	printf("\n");
	// 	aux1 = aux1->prox;
	// }

	do{
		printf("1 - Editar novo arquivo\n");
		printf("2 - Editar arquivo existente\n");
		printf("3 - Sair\n");
		printf("Digite a sua opção: ");
		scanf("%d", &opc);

		fflush(stdin);

		switch(opc){
			char arquivo[100];
			case 1:
				// Função para novo arquivo
				inserirLinhaFim(lista);
				break;
			case 2:
				// Função para editar arquivo existente
				printf("Digite o arquivo com o caminho: ");
				gets(arquivo);
				lerArquivoLista(arquivo, lista);
				break;
			case 3:
				// Sair
				return 0;
			default:
				printf("Opção inválida\n");
				break;
		}
	}while(opc > 3 || opc < 1);

	clear();

	LINHA *auxLinha = lista->inicio;
	while(auxLinha != NULL){
		CARACTERE *auxCaractere = auxLinha->cadeia->inicio;
		while(auxCaractere != NULL){
			putchar(auxCaractere->c);
			auxCaractere = auxCaractere->prox;
		}
		cursorNextLine();
		auxLinha = auxLinha->prox;
	}

	char entrada;
	do{
		entrada = getch();

		switch(entrada){
			case ARROW_UP:
				cursorUp();
				break;

			case ARROW_DOWN:
				cursorDown();
				break;

			case ARROW_LEFT:
				cursorLeft();
				break;

			case ARROW_RIGHT:
				cursorRight();
				break;

			case BACKSPACE:
				cursorLeft();
				putch(' ');
				cursorLeft();
				break;

			case ENTER:
				clearTillEnd();
				cursorNextLine();
				break;

			case PAGE_UP:
				scrollUp();
				break;

			case PAGE_DOWN:
				scrollDown();
				break;
			default:
				break;
		}
	}while(entrada != '0');
	gravarListaArquivo("./arquivos/novo.txt", lista);
    return 0;
}
