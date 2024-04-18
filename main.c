#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
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
#define clearTillEndLine() printf("\033[K")
#define clearTillEndScreen() printf("\033[J")
#define cursorPrevLine() printf("\033[F")
#define cursorNextLine() printf("\033[E")
#define cursorUp() printf("\033[A")
#define cursorDown() printf("\033[B")
#define cursorRight() printf("\033[C")
#define cursorLeft() printf("\033[D")
#define scrollDown() printf("\033[1S")
#define scrollUp() printf("\033[1T")
#define saveCursor() printf("\033[s");
#define loadCursor() printf("\033[u");
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

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

	char entrada;
	int maxLinhas, maxColunas;
	int contLinhas=0, contColunas=0;
	int linhaAtual=1, colunaAtual=1;
	getTerminalColumnsRows(&maxColunas, &maxLinhas);

	LINHA *auxLinha = lista->inicio;

	// Imprimir a tela ate os limites do terminal
	while(auxLinha != NULL && contLinhas != maxLinhas){
		CARACTERE *auxCaractere = auxLinha->cadeia->inicio;
		contColunas=0;
		while(auxCaractere != NULL && contColunas != maxColunas){
			putchar(auxCaractere->c);
			contColunas++;
			auxCaractere = auxCaractere->prox;
		}
		cursorNextLine();
		contLinhas++;
		linhaAtual++;
		auxLinha = auxLinha->prox;
	}

	LINHA *inicioBuffer = lista->inicio;
	LINHA *atualBuffer = inicioBuffer;
	LINHA *fimBuffer;
	if(auxLinha != NULL){
		fimBuffer = auxLinha->ant;
	}else{
		fimBuffer = inicioBuffer;
	}	

	gotoxy(1,1); // Posiciona o cursor no canto superior direito

	do{
		entrada = getch();

		switch(entrada){
			case ARROW_UP:
				if(atualBuffer != inicioBuffer){
					cursorUp();
					linhaAtual--;
					atualBuffer = atualBuffer->ant;
				}
				break;

			case ARROW_DOWN:
				if(atualBuffer != fimBuffer){
					cursorDown();
					linhaAtual++;
					atualBuffer = atualBuffer->prox;
				}
				break;

			case ARROW_LEFT:
				cursorLeft();
				colunaAtual--;
				break;

			case ARROW_RIGHT:
				cursorRight();
				colunaAtual++;
				break;

			case BACKSPACE:
				cursorLeft();
				putch(' ');
				cursorLeft();
				break;

			case ENTER:
				clearTillEndScreen();
				cursorNextLine();
				inserirLinhaPosicao(lista, linhaAtual++);
				auxLinha = atualBuffer;
				//while(auxLinha != NULL && linhaAtual !
				fimBuffer = fimBuffer->ant;
				break;

			case PAGE_UP:
				if(inicioBuffer->ant != NULL){
					saveCursor();
					scrollUp();
					gotoxy(1,1);
					linhaAtual--;
					atualBuffer = atualBuffer->ant;
					inicioBuffer = inicioBuffer->ant;
					fimBuffer = fimBuffer->ant;
					imprimirCadeia(inicioBuffer->cadeia);
					loadCursor();
				}
				break;

			case PAGE_DOWN:
				if(fimBuffer->prox != NULL){
					saveCursor();
					scrollDown();
					gotoxy(1,maxLinhas);
					linhaAtual++;
					atualBuffer = atualBuffer->prox;
					fimBuffer = fimBuffer->prox;
					inicioBuffer = inicioBuffer->prox;
					imprimirCadeia(fimBuffer->cadeia);
					loadCursor();
				}
				break;
			default:
				break;
		}
	}while(entrada != '0');
	clear();
	//gravarListaArquivo("./arquivos/novo.txt", lista);
    return 0;
}
