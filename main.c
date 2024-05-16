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

	lerArquivoLista("./arquivos/novo.txt", lista);
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
		printf("%d", linhaAtual);
		loadCursor();

		entrada = getch();

		if(entrada == 224 || entrada == 0){
			entrada = getch();

			switch(entrada){
				case ARROW_UP:
					if(atualBuffer != inicioBuffer){
						if(colunaAtual > atualBuffer->ant->cadeia->tamanho){
							atualBuffer = atualBuffer->ant;
							colunaAtual = atualBuffer->cadeia->tamanho + 1;
							linhaAtual--;
							gotoxy(atualBuffer->cadeia->tamanho+1, getCursorRow()-1);
						}else{
							cursorUp();
							linhaAtual--;
							atualBuffer = atualBuffer->ant;
						}
					}
					break;

				case ARROW_DOWN:
					if(atualBuffer != fimBuffer){
						if(colunaAtual > atualBuffer->prox->cadeia->tamanho){
							atualBuffer = atualBuffer->prox;
							colunaAtual = atualBuffer->cadeia->tamanho + 1;
							linhaAtual++;
							gotoxy(atualBuffer->cadeia->tamanho+1, getCursorRow()+1);
						}else{
							cursorDown();
							linhaAtual++;
							atualBuffer = atualBuffer->prox;
						}
					}
					break;

				case ARROW_LEFT:
					if(colunaAtual == 1){
						if(atualBuffer->ant != NULL){
							atualBuffer = atualBuffer->ant;
							colunaAtual = atualBuffer->cadeia->tamanho+1;
							linhaAtual--;
							gotoxy(atualBuffer->cadeia->tamanho+1, getCursorRow()-1);
						}
					}else{
						cursorLeft();
						colunaAtual--;
					}
					break;

				case ARROW_RIGHT:
					if(colunaAtual == atualBuffer->cadeia->tamanho+1){
						if(atualBuffer != fimBuffer){
							atualBuffer = atualBuffer->prox;
							colunaAtual = 1;
							linhaAtual++;
							gotoxy(1, getCursorRow()+1);
						}
					}else{
						cursorRight();
						colunaAtual++;
					}
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
				case END:
					colunaAtual = atualBuffer->cadeia->tamanho + 1;
					gotoxy(atualBuffer->cadeia->tamanho+1, linhaAtual);
					break;
				case HOME:
					colunaAtual = 1;
					gotoxy(1, linhaAtual);
					break;
				default:
					break;
			}
			continue;
		}

		switch(entrada){
			case BACKSPACE:
				if(!cadeiaEstaVazia(atualBuffer->cadeia)){
					if(colunaAtual != 1){
						cursorLeft();
						removerChar();
						removerCaractereCadeiaPosicao(atualBuffer->cadeia, --colunaAtual);
					}else{
						if(atualBuffer->ant != NULL){
							atualBuffer = atualBuffer->ant;
							if(!cadeiaEstaVazia(atualBuffer->prox->cadeia)){
								int tamanhoNovo;

								if(atualBuffer->cadeia->fim != NULL){
									atualBuffer->cadeia->fim->prox = atualBuffer->prox->cadeia->inicio;
									atualBuffer->cadeia->fim = atualBuffer->prox->cadeia->fim;
									tamanhoNovo = atualBuffer->cadeia->tamanho + atualBuffer->prox->cadeia->tamanho;
									colunaAtual = atualBuffer->cadeia->tamanho + 1;
								}else{
									atualBuffer->cadeia = atualBuffer->prox->cadeia;
									tamanhoNovo = atualBuffer->cadeia->tamanho;
									colunaAtual = 1;
								}
								
								atualBuffer->cadeia->tamanho = tamanhoNovo;
							}

							deleteLine();
							removerLinhaAtual(lista, atualBuffer->prox);
							fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow()-1, maxLinhas); 

							gotoxy(colunaAtual, --linhaAtual);

							escreverCadeiasTela(atualBuffer, getCursorRow(), getCursorRow(), 1, maxColunas);
							escreverCadeiasTela(fimBuffer, maxLinhas, maxLinhas, 1, maxColunas);
							
						}
					}
				}else{
					if(atualBuffer->ant != NULL){
						atualBuffer = atualBuffer->ant;
						colunaAtual = atualBuffer->cadeia->tamanho + 1;
						
						deleteLine();
						removerLinhaAtual(lista, atualBuffer->prox);
						fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow()-1, maxLinhas);

						gotoxy(colunaAtual, --linhaAtual);

						escreverCadeiasTela(atualBuffer, getCursorRow(), getCursorRow(), 1, maxColunas);
						escreverCadeiasTela(fimBuffer, maxLinhas, maxLinhas, 1, maxColunas);
					}
				}
				break;

			case ENTER:
				clearTillEndLine();

				if(atualBuffer == fimBuffer && getCursorRow() == maxLinhas){
					scrollDown();
					inicioBuffer=inicioBuffer->prox;
				}

				cursorNextLine();
				lineFeed();
				desanexarParaNovaLinha(lista, atualBuffer, colunaAtual);
				linhaAtual++;
				colunaAtual=1;

				atualBuffer = atualBuffer->prox;

				escreverCadeiasTela(atualBuffer, getCursorRow(),  getCursorRow(), colunaAtual, maxColunas);
				fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow(), maxLinhas);
				break;
			
			case '0':
			break;

			case CTRL_S:
				gravarListaArquivo("./arquivos/novo.txt", lista);
				break;

			default:
				inserirChar();

				UTFCHAR *novoCaractere = (UTFCHAR*)malloc(sizeof(UTFCHAR));
				inicializarUtfChar(novoCaractere);

				for (int i = 0; i < numberOfBytesInChar((unsigned char)entrada) - 1; i++) {
					inserirUtfByte(novoCaractere, (unsigned char)entrada);
					printf("%c", entrada);
					entrada = getch();
				}
				printf("%c", entrada);

				inserirUtfByte(novoCaractere, entrada);
				inserirCaractereCadeiaPosicao(atualBuffer->cadeia, novoCaractere, colunaAtual-1);
				colunaAtual++;
				break;
		}
	}while(entrada != '0');
	clear();
    return 0;
}
