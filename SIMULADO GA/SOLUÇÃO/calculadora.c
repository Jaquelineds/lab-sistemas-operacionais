#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int valor1, valor2, resultado, opcao;

	while(opcao!=5){
		printf("\n****** MENU ******\n");
		printf("1 - Adição\n");
		printf("2 - Subtração\n");
		printf("3 - Multiplicação\n");
		printf("4 - Divisão\n");
		printf("5 - Sair\n");
		printf("Escolha a operação:");
		scanf("%d", &opcao);

		if (opcao > 0 && opcao < 5){
			printf("Digite o primeiro valor: ");
			scanf("%d", &valor1);
			printf("Digite o segundo valor: ");
			scanf("%d", &valor2);
		}

		switch (opcao)
		{
			case 1:
				resultado = valor1 + valor2;
			break;

			case 2:
				resultado = valor1 - valor2;
			break;

			case 3:
				resultado = valor1 * valor2;
			break;

			case 4:
				resultado = valor1 / valor2;
			break;

			case 5:
				resultado = 0;
			break;

			default:
				printf("Valor inválido, digite 1, 2, 3, 4 ou 5!\n");
		}

		if (opcao > 0 && opcao < 5){
			printf("Resultado: %d\n", resultado);
		}
	}
	return 0;
}

