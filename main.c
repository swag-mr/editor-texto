#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
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
	imprimirCadeiaInvertida(cadeia);
    return 0;
}
