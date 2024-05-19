#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "funcoes.h"

int main(){
	textoPadrao();
	fundoPadrao();
	char arquivo[100] = "./arquivos/";
	int maxLinhas, maxColunas;
	getTerminalColumnsRows(&maxColunas, &maxLinhas);

	LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
	inicializarLista(lista);

	int opc = menu(arquivo, maxLinhas, maxColunas, lista);

	int entrada;
	int linhaAtual=1, colunaAtual=1;

	LINHA *inicioBuffer = lista->inicio;
	LINHA *atualBuffer = inicioBuffer;
	
	// Imprimir a tela ate os limites do terminal e armazenar a última linha percorrida
	LINHA *fimBuffer = escreverCadeiasTela(lista->inicio, 1, maxLinhas, 1, maxColunas);
	while(opc != 0){
		do{
			int posY = getCursorRow();
			saveCursor();
			gotoxy(maxColunas-3, 1);
			clearTillEndLine();
			gotoxy(maxColunas-3, 1);
			printf("%d", colunaAtual);
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
							if(colunaAtual <= atualBuffer->ant->cadeia->tamanho+1){
								scrollUp();
							}else{
								colunaAtual = atualBuffer->ant->cadeia->tamanho+1;
								scrollUp();
								gotoxy(colunaAtual, getCursorRow());
							}
							linhaAtual--;
							atualBuffer = atualBuffer->ant;
							inicioBuffer = inicioBuffer->ant;
							fimBuffer = fimBuffer->ant;
							escreverCadeiasTela(inicioBuffer, 1, 1, 1, maxColunas);
						}
						break;

					case PAGE_DOWN:
						if(fimBuffer->prox != NULL){
							if(colunaAtual <= atualBuffer->prox->cadeia->tamanho+1){
							scrollDown();
							}else{
								colunaAtual = atualBuffer->prox->cadeia->tamanho+1;
								scrollDown();
								gotoxy(colunaAtual, getCursorRow());
							}
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
										atualBuffer->prox->cadeia->inicio->ant = atualBuffer->cadeia->fim;
										atualBuffer->cadeia->fim = atualBuffer->prox->cadeia->fim;
										tamanhoNovo = atualBuffer->cadeia->tamanho + atualBuffer->prox->cadeia->tamanho;
										colunaAtual = atualBuffer->cadeia->tamanho + 1;
									}else{
										atualBuffer->cadeia->inicio = atualBuffer->prox->cadeia->inicio;
										atualBuffer->cadeia->fim = atualBuffer->prox->cadeia->fim;
										tamanhoNovo = atualBuffer->cadeia->tamanho;
										colunaAtual = 1;
									}
									
									atualBuffer->cadeia->tamanho = tamanhoNovo;
								}
								if(atualBuffer->prox == inicioBuffer){
									inicioBuffer = atualBuffer;

									removerLinhaAtual(lista, atualBuffer->prox);
									linhaAtual--;
									gotoxy(colunaAtual, getCursorRow());

									saveCursor()
									gotoxy(1, getCursorRow());
									clearTillEndLine();
									loadCursor();

									escreverCadeiasTela(atualBuffer, getCursorRow(), getCursorRow(), 1, maxColunas);
								}else{
									deleteLine();
									removerLinhaAtual(lista, atualBuffer->prox);
									linhaAtual--;
									gotoxy(colunaAtual, getCursorRow()-1);
									fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow(), maxLinhas); 

									saveCursor()
									gotoxy(1, getCursorRow());
									clearTillEndLine();
									loadCursor();

									int bufferRow=getCursorRow();
									LINHA *aux = atualBuffer;
									while(aux != fimBuffer){
										aux = aux->prox;
										bufferRow++;
									}
									escreverCadeiasTela(atualBuffer, getCursorRow(), getCursorRow(), 1, maxColunas);
									if(bufferRow == maxLinhas){
										escreverCadeiasTela(fimBuffer, maxLinhas, maxLinhas, 1, maxColunas);
									}
								}
								
							}
						}
					}else{
						if(atualBuffer->ant != NULL){
							if(atualBuffer == inicioBuffer){
								inicioBuffer = atualBuffer->ant;
							}
							atualBuffer = atualBuffer->ant;
							colunaAtual = atualBuffer->cadeia->tamanho + 1;
							
							deleteLine();
							removerLinhaAtual(lista, atualBuffer->prox);
							linhaAtual--;
							gotoxy(colunaAtual, getCursorRow()-1);
							fimBuffer = determinarFimBuffer(atualBuffer, getCursorRow(), maxLinhas); 

							saveCursor()
							gotoxy(1, getCursorRow());
							clearTillEndLine();
							loadCursor();

							int bufferRow=getCursorRow();
							LINHA *aux = atualBuffer;
							while(aux != fimBuffer){
								aux = aux->prox;
								bufferRow++;
							}
							escreverCadeiasTela(atualBuffer, getCursorRow(), getCursorRow(), 1, maxColunas);
							if(bufferRow == maxLinhas){
								escreverCadeiasTela(fimBuffer, maxLinhas, maxLinhas, 1, maxColunas);
							}
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

				case CTRL_S:
					gravarListaArquivo(arquivo, lista);
					break;

				case CTRL_Q:
					break;

				default:
					inserirChar();

					UTFCHAR *novoCaractere = (UTFCHAR*)malloc(sizeof(UTFCHAR));
					inicializarUtfChar(novoCaractere);

					for (int i = 0; i < numberOfBytesInChar((unsigned char)entrada)- 1; i++) {
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
		}while(entrada != CTRL_Q);
		clear();
		strcpy(arquivo, "./arquivos/");
		//limparLista(lista); IMPLEMENTAR A FUNCAO DE LIMPARLISTA
		opc = menu(arquivo, maxLinhas, maxColunas, lista);
	}
	padrao();
	clear();
    return 0;
}
