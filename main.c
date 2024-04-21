#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcoes.h"

int main(){
	int opc;

	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

	inicializarLista(lista);

	/* NAO APAGAR ESSE COMENTARIO
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
	}while(opc > 3 || opc < 1);*/

	lerArquivoLista("./arquivos/texto.txt", lista);
	clear();

	int entrada;
	int maxLinhas, maxColunas;
	int linhaAtual=1, colunaAtual=1;
	getTerminalColumnsRows(&maxColunas, &maxLinhas);

	LINHA *inicioBuffer = lista->inicio;
	LINHA *atualBuffer = inicioBuffer;
	
	// Imprimir a tela ate os limites do terminal e armazenar a última linha percorrida
	LINHA *fimBuffer = escreverCadeiasTela(lista->inicio, 1, maxLinhas, 1, maxColunas);

	do{
		int posY = getCursorRow();
		saveCursor();
		gotoxy(maxColunas-3, 1);
		clearTillEndLine();
		gotoxy(maxColunas-3, 1);
		printf("%d", atualBuffer->cadeia->tamanho);
		loadCursor();

		entrada = getch();

		if(entrada == 224 || entrada == 0){
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
				case PAGE_UP:
					if(inicioBuffer->ant != NULL){
						scrollUp();
						linhaAtual--;
						atualBuffer = atualBuffer->ant;
						inicioBuffer = inicioBuffer->ant;
						fimBuffer = fimBuffer->ant;
						escreverCadeiasTela(inicioBuffer, 1, 1, 1, maxColunas);
					}
					break;

				case PAGE_DOWN:
					if(fimBuffer->prox != NULL){
						scrollDown();
						linhaAtual++;
						atualBuffer = atualBuffer->prox;
						fimBuffer = fimBuffer->prox;
						inicioBuffer = inicioBuffer->prox;
						escreverCadeiasTela(fimBuffer, maxLinhas, maxLinhas, 1, maxColunas);
					}
					break;
				default:
					break;
			}
			continue;
		}

		switch(entrada){
			case BACKSPACE:
				cursorLeft();
				removerChar();
				break;

			case ENTER:
				clearTillEndLine();
				cursorNextLine();
				lineFeed();
				inserirLinhaPosicao(lista, linhaAtual++);
				atualBuffer = atualBuffer->prox;
				fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow(), maxLinhas);
				//fimBuffer = escreverCadeiasTela(atualBuffer, getCursorRow(), maxLinhas, 1, maxColunas);
				break;

			default:
				inserirChar();
				for (int i = 0; i < numberOfBytesInChar((unsigned char)entrada) - 1; i++) {
					printf("%c", entrada);
					entrada = getch();
				}
				printf("%c", entrada);
				break;
		}
	}while(entrada != '0');
	clear();
	gravarListaArquivo("./arquivos/novo.txt", lista);
    return 0;
}
