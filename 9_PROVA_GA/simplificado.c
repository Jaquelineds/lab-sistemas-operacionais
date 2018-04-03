//***********JAQUELINE DAHMER STEFFENON*************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void simples(){
   printf(__DATE__"\n");
   printf(__TIME__"\n");
   printf("Isento de imposto de renda!\n");
}

int main(){
   simples();
   return 0;
}
