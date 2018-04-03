//***********JAQUELINE DAHMER STEFFENON*************
#include <stdio.h>
#include <string.h>

float quantidade, valoruni;

float custo_total(){
   return quantidade * valoruni;
}

float margem_contribuicao(){
   return custo_total()*0.5;
}

float icms(){
   return ((custo_total() + margem_contribuicao()) * 0.17);
}

float soma(){
   return (custo_total() + margem_contribuicao() + icms()) ;
}

int main(){
   
   printf("Digite a quantidade: ");
   scanf("%f", &quantidade);
   printf("Digite o valor unitário: ");
   scanf("%f", &valoruni);

   printf("O valor de custo do produto é %f\n", custo_total());
   printf("O valor de margem de contribuição é %f\n", margem_contribuicao());
   printf("O valor do ICMS para o produto é %f\n", icms());
   printf("O valor de venda do produto é %f\n\n", soma());

   return 0;

}
