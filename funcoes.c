#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarUtfChar(UTFCHAR *u){
	u->inicio = NULL;
}

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

UTFBYTE *criarUtfByte(unsigned char c){
	UTFBYTE *utfByte = (UTFBYTE*)malloc(sizeof(UTFBYTE));
	utfByte->byte = c;
	utfByte->prox = NULL;
	return utfByte;
}

CARACTERE* criarCaractere(UTFCHAR *c){
	CARACTERE *caractere = (CARACTERE*) malloc(sizeof(CARACTERE));
	caractere->ant = NULL;
	caractere->prox = NULL;
	caractere->utfChar = c;
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

void inserirUtfByte(UTFCHAR *u, unsigned char c){
	UTFBYTE *utfByte = criarUtfByte(c);
	if(u->inicio == NULL){
		u->inicio = utfByte;
		return;
	}
	UTFBYTE *aux = u->inicio;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = utfByte;
}

void removerUtfByteInicio(UTFCHAR *u){
	if(u->inicio == NULL){
		return;
	}

	UTFBYTE *auxByte = u->inicio;
	u->inicio = auxByte->prox;

	free(auxByte);
}

void inserirLinhaInicio(LISTA *lista){
	LINHA *linha = criarLinha();
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
	LINHA *linha = criarLinha();
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

void inserirLinhaPosicao(LISTA *lista, LINHA *linhaAtual){
	if(linhaAtual == lista->fim){
		inserirLinhaFim(lista);
		return;
	}

	LINHA *linha = criarLinha();
	lista->tamanho++;

	linha->ant = linhaAtual;
	linha->prox = linhaAtual->prox;
	if(linhaAtual->prox != NULL){
		linhaAtual->prox->ant = linha;
	}
	linhaAtual->prox = linha;
}

void removerLinhaInicio(LISTA *lista){
	LINHA *linhaAux = lista->inicio;
	lista->inicio = linhaAux->prox;
	lista->tamanho--;

	free(linhaAux);
	free(linhaAux->cadeia);

	if(lista->inicio == NULL){
		lista->fim = NULL;
		return;
	}
	lista->inicio->ant = NULL;
}

void removerLinhaFim(LISTA *lista){
	LINHA *linhaAux = lista->fim;
	lista->fim = linhaAux->ant;
	lista->tamanho--;

	free(linhaAux);
	free(linhaAux->cadeia);

	if(lista->fim == NULL){
		lista->inicio = NULL;
		return;
	}

	lista->fim->prox = NULL;
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
	return;
    }else{
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
    }
}

void removerLinhaAtual(LISTA *lista, LINHA *linhaAtual){
	if(lista->inicio == linhaAtual){
		removerLinhaInicio(lista);
		return;
	}

	if(lista->fim == linhaAtual){
		removerLinhaFim(lista);
		return;
	}

	LINHA *linhaAnterior = linhaAtual->ant;
	LINHA *linhaProxima = linhaAtual->prox;

	linhaAnterior->prox = linhaProxima;
	linhaProxima->ant = linhaAnterior;

	lista->tamanho--;
	free(linhaAtual);
	free(linhaAtual->cadeia);
}

int cadeiaEstaVazia(CADEIA *cadeia){
	if(cadeia->inicio == NULL || cadeia->fim == NULL)
		return 1;
	return 0;
}

void inserirCaractereCadeiaInicio(CADEIA *cadeia, UTFCHAR *c){
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

void inserirCaractereCadeiaFim(CADEIA *cadeia, UTFCHAR *c){
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

void inserirCaractereCadeiaPosicao(CADEIA *cadeia, UTFCHAR *c, int pos){
	if(pos == 0){
		inserirCaractereCadeiaInicio(cadeia, c);
		return;
	}
	if(pos >= cadeia->tamanho){
		inserirCaractereCadeiaFim(cadeia, c);
		return;
	}

	CARACTERE *aux = cadeia->inicio;
	CARACTERE *caractere = criarCaractere(c);
	cadeia->tamanho++;

	int cont=1;
	while(aux != NULL && cont < pos){
		cont++;
		aux = aux->prox;
	}

	CARACTERE *proxima = aux->prox;

	aux->prox = caractere;
	caractere->prox = proxima;
	caractere->ant = aux;
	proxima->ant = caractere;
}

void removerCaractereCadeiaInicio(CADEIA *cadeia){
	if(cadeiaEstaVazia(cadeia)){
		printf("Cadeia vazia, impossível remover caractere\n");
		return;
	}

	CARACTERE *aux = cadeia->inicio;
	cadeia->inicio = aux->prox;
	cadeia->tamanho--;

	while(aux->utfChar->inicio != NULL){
		removerUtfByteInicio(aux->utfChar);
	}

	free(aux->utfChar);
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

	while(aux->utfChar->inicio != NULL){
		removerUtfByteInicio(aux->utfChar);
	}

	free(aux->utfChar);
	free(aux);

	if(cadeiaEstaVazia(cadeia)){
		cadeia->inicio = NULL;
		return;
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

	while(aux->utfChar->inicio != NULL){
		removerUtfByteInicio(aux->utfChar);
	}

	free(aux->utfChar);
	free(aux);

	if(cadeiaEstaVazia(cadeia)){
		cadeia->fim = NULL;
		cadeia->inicio = NULL;
	}
}

void lerArquivoLista(char *nome, LISTA *lista){
	FILE *file = fopen(nome, "r");

	inserirLinhaFim(lista);

	LINHA *aux = lista->inicio;

	unsigned char caractere;
	while(!feof(file)){
		caractere = fgetc(file);
		if(caractere == EOF)
			break;
		if(caractere == '\n'){
			inserirLinhaFim(lista);
			aux = aux->prox;
		}else{
			UTFCHAR *caractereCompleto = (UTFCHAR*)malloc(sizeof(UTFCHAR));

			inicializarUtfChar(caractereCompleto);

			int nBytes = numberOfBytesInChar(caractere)-1;
			for(int i=0;i < nBytes;i++) {
				inserirUtfByte(caractereCompleto, caractere);
				caractere = fgetc(file);
			}
			inserirUtfByte(caractereCompleto, caractere);
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
			UTFBYTE *auxByte = auxCadeia->utfChar->inicio;
			while(auxByte != NULL){
				fputc(auxByte->byte, file);
				auxByte = auxByte->prox;
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
	hideCursor()
	saveCursor();
	gotoxy(1, startLinha);
	LINHA *aux = inicio;
	LINHA *ant = NULL;
	int contLinhas = startLinha;
	while(aux != NULL && contLinhas <= endLinha){
		CARACTERE *auxCaractere = aux->cadeia->inicio;
		int contColunas=startColuna;
		while(auxCaractere != NULL && contColunas <= endColuna){
			UTFBYTE *auxByte = auxCaractere->utfChar->inicio;
			while(auxByte != NULL){
				printf("%c", auxByte->byte);
				auxByte = auxByte->prox;
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
	showCursor();
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

LINHA *determinarFimBuffer(LINHA *inicio, int start, int end){
	LINHA *ant = NULL;
	LINHA *aux = inicio;
	int cont = start;
	while(aux != NULL && cont <= end){
		cont++;
		ant = aux;
		aux = aux->prox;
	}

	return ant;
}

void desanexarParaNovaLinha(LISTA *lista, LINHA *linha, int posColuna){
	inserirLinhaPosicao(lista, linha);

	LINHA *novaLinha = linha->prox;
	CARACTERE *c = linha->cadeia->inicio;

	int cont = 0;
	while(c != NULL && cont < posColuna-1){
		c = c->prox;
		cont++;
	}

	novaLinha->cadeia->inicio = c;
	novaLinha->cadeia->fim = linha->cadeia->fim;

	if(c != NULL){
		if(c->ant != NULL){
			linha->cadeia->fim = c->ant;
			c->ant->prox = NULL;
		}else{
			linha->cadeia->inicio = NULL;
			linha->cadeia->fim = NULL;
		}
		c->ant = NULL;
	}

	novaLinha->cadeia->tamanho = linha->cadeia->tamanho - cont;
	linha->cadeia->tamanho = cont;
}

void desenharMoldura(int largura, int altura){
	int i, j, cont=0;
	char titulo[30] = "ODIN - Text Editor";

	while(titulo[cont] != '\0'){
		cont++;
	}

	hideCursor()

	clear();
	gotoxy(1,1);

	upperLeftCorner();
	for(i=0; i < largura-2; i++){
		horizontalLine();
	}
	upperRightCorner();

	printf("\n");

	for(i=2; i < altura; i++){
		if(i == 3){
			gotoxy(1, i);
			subBlockRight();
			for(j=0; j < largura-2; j++){
				horizontalLine();
			}
			subBlockLeft();
			continue;
		}
		gotoxy(1, i);
		verticalLine();

		gotoxy(largura, i);
		verticalLine();
		printf("\n");
	}

	lowerLeftCorner();
	for(i=0; i < largura-2; i++){
		horizontalLine();
	}
	lowerRightCorner();

	gotoxy(largura/2 - cont/2+1, 2);
	int k=0;
	for(int i=0; i < cont; i++){
		int mod;
		if(titulo[i] != ' '){
			mod = k % 2;
			k++;
		}
		switch(mod){
			case 0:
				textoAmarelo();
				break;
			case 1:
				textoCiano();
				break;
		}
		printf("%c", titulo[i]);
	}
	textoPadrao();

	showCursor();
}

int veririficarNomeArquivo(char nome[]){
	DIR *d;
	struct dirent *dir;
	d = opendir("./arquivos/");
	int cont = 0;
	if(d){
		while((dir = readdir(d)) != NULL){
			if(strcasecmp(dir->d_name, nome) == 0){
				cont++;
				break;
			}
		}
		closedir(d);
	}

	return cont;
}

int menu(char arquivo[], int maxLinhas, int maxColunas, LISTA *lista){
	int opc;
	desenharMoldura(maxColunas, maxLinhas);
	gotoxy(2, 4);
	do{
		printf("1 - Editar novo arquivo\n");
		gotoxy(2, getCursorRow());

		printf("2 - Editar arquivo existente\n");
		gotoxy(2, getCursorRow());

		printf("0 - Sair\n");
		gotoxy(2, getCursorRow());

		printf("Digite a sua opção: ");
		scanf("%d", &opc);

		fflush(stdin);

		switch(opc){
			char nome[30];
			case 1:
				// Função para novo arquivo
				printf("\n");
				gotoxy(2, getCursorRow());
				printf("Digite o nome do novo arquivo (texto.txt): ");
				gets(nome);

				int nomeIgual = veririficarNomeArquivo(nome);

				if(nomeIgual){
					textoVermelho();
					printf("\n");
					gotoxy(2, getCursorRow());
					printf("ERRO: Arquivo já existente\n\n");
					textoPadrao();
					gotoxy(2, getCursorRow());
					system("pause");
					opc = -1;
					clear();
					desenharMoldura(maxColunas, maxLinhas);
					gotoxy(2, 4);
				}else{
					strcat(arquivo, nome);
					inserirLinhaFim(lista);
				}
				break;
			case 2:
				// Função para editar arquivo existente
				gotoxy(2, getCursorRow());
				DIR *d;
				struct dirent *dir;
				d = opendir("./arquivos/");
				textoCiano();
				printf("\n\tArquivos Disponíveis:\n\n");
				textoVerde();
				if(d){
					while((dir = readdir(d)) != NULL){
						gotoxy(2, getCursorRow());
						if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
							char *ext = strrchr(dir->d_name, '.');
                			if (ext && strcmp(ext, ".txt") == 0) {
                    			printf("\t%s\n", dir->d_name); // Mostrar apenas arquivos .txt
                			}
						}
					}
					closedir(d);
					textoPadrao();
					printf("\n");
				}
				gotoxy(2, getCursorRow());
				printf("Digite o nome do arquivo (texto.txt): ");
				gets(nome);
				
				int nomeExistente = veririficarNomeArquivo(nome);

				if(nomeExistente == 0){
					textoVermelho();
					printf("\n");
					gotoxy(2, getCursorRow());
					printf("ERRO: Arquivo inexistente\n\n");
					textoPadrao();
					gotoxy(2, getCursorRow());
					system("pause");
					clear();
					opc = -1;
					desenharMoldura(maxColunas, maxLinhas);
					gotoxy(2, 4);
				}else{
					strcat(arquivo, nome);
					lerArquivoLista(arquivo, lista);
				}
				break;
			case 0:
				// Sair
				clear();
				return 0;
			default:
				textoVermelho();
				printf("\n");
				gotoxy(2, getCursorRow());
				printf("Opção inválida\n\n");
				textoPadrao();
				gotoxy(2, getCursorRow());
				system("pause");
				clear();
				desenharMoldura(maxColunas, maxLinhas);
				gotoxy(2, 4);
				break;
		}
	}while(opc > 2 || opc < 0);

	clear();

	return 1;
}

void interfaceEditor(int largura, int altura, char *nomeArquivo){
	int i;

	saveCursor();
	hideCursor();

	gotoxy(1, 1);
	printf("%s", nomeArquivo);

	gotoxy(1, 2);
	for(i=0; i < largura; i++){
		horizontalLine();
	}

	gotoxy(1, altura-1);
	for(i=0; i < largura; i++){
		horizontalLine();
	}
	gotoxy(1,altura);
	printf("CTRL-S Salvar\tCTRL-Q Sair");

	showCursor();
	loadCursor();
}

void limparLista(LISTA *l){
	LINHA *linhaAux = l->inicio;
	LINHA *linhaProx = l->inicio->prox;

	while(linhaAux != NULL){
		CARACTERE *caracAux = linhaAux->cadeia->inicio;
		CARACTERE *caracProx = linhaAux->cadeia->inicio->prox;

		while(caracAux != NULL){
			UTFBYTE *uftAux = caracAux->utfChar->inicio;
			UTFBYTE *uftProx = caracAux->utfChar->inicio->prox;

			while(uftAux != NULL){
				free(uftAux);
				uftAux = uftProx;
				uftProx = uftProx->prox;
			}

			free(caracAux);
			caracAux = caracProx;
			caracProx = caracProx->prox;
		}

		free(linhaAux);
		linhaAux = linhaProx;
		linhaProx = linhaProx->prox;
	}
}