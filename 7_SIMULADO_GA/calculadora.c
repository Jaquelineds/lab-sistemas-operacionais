#include <stdio.h>

int main(){
   int n1, n2, r;
   printf("Digite o primeiro número: ");
   scanf("%d", &n1);
   printf("Digite o segundo número: ");
   scanf("%d", &n2);
   int operacao;
   printf("Qual operação deseja fazer?\n[1] Soma\n[2] Subtração\n[3] Produto\n[4] Divisão\n[5] Sair\n");
   scanf("%d", &operacao);
   switch (operacao){
   case 1:
	r = n1 + n2;
        printf("%d + %d = %d\n", n1, n2, r);
	break;
   case 2:
	r = n1 - n2;
        printf("%d - %d = %d\n", n1, n2, r);
	break;
   case 3:
	r = n1 * n2;
        printf("%d * %d = %d\n", n1, n2, r);
	break;
   case 4:
	r = n1 / n2;
        printf("%d / %d = %d\n", n1, n2, r);
	break;
   case 5:
	return 0;
   default:
	printf("Opção inválida!\n");
   }
   return 0;
}
