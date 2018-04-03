#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char* palavra = "";
	int numero = 0;
	int i, contador = 0;

	if (argc > 0){
		palavra = argv[1];

		printf("Digite o número: ");
		scanf("%d", &numero);

		for (i=0;palavra[i]!='\0';i++) 
		{
			if (palavra[i] == 'a' || palavra[i] == 'e' || palavra[i] == 'i' || palavra[i] == 'o' || palavra[i] == 'u')
				contador++;
		}
	}
	else{
		printf("A palavra não foi informada por linha de comando!\n");	
	}

	printf("Número de vogais: %d\n", contador);
	printf("Número de vogais x Número lido: %d\n", contador * numero);
	return 0;
}
