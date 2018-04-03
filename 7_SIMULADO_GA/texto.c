#include <stdio.h>
#include <string.h>

int main(){
   int n, vogais = 0;
   char p[150];
   printf("Digite uma palavra: ");
   scanf("%[^\n]s", p);
   printf("Digite um número: ");
   scanf("%d", &n);
   for (int i = 0; i < strlen(p); i++){
      if (p[i] == 'a' || p[i] == 'e' || p[i] == 'i' || p[i] == 'o' || p[i] == 'u'){
         vogais++;
      }
   }
   int resultado = (vogais * n);
   printf("Resultado: %d\n", resultado);
   return 0;
}
