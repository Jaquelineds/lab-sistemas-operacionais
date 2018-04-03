//***********JAQUELINE DAHMER STEFFENON*************
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include "simplificado.c"

void tratador(int signum){
   switch(signum){
      case SIGUSR1: printf("Sinal recebido! Aguardando a conclusão do processo filho!\n"); break;
      case SIGUSR2: printf("Sinal recebido! Ainda em processamento...\n", signum); break;
   }
}

void load_page(){
   char call[500];
   strcpy(call, "firefox -new-window http://www.receita.fazenda.gov.br");
   system(call);

}

int main(){

   struct sigaction sa;
   memset(&sa, 0, sizeof(sa));

   sa.sa_handler = &tratador;

   float salario = 0;
   printf("Digite o salário anual do colaborador: \n");
   scanf("%f", &salario);

   if (salario < 2000){
      pid_t pid = fork();
      if(pid < 0){
         perror("Falha no fork");
      }

      else if (pid == 0){
         simples(salario); //não lembrei como chamar função de outra classe aqui
         printf("PID DO FILHO: %d\n", getpid());
         printf("PID DO PAI: %d\n", getppid());
      }
   }
   else if (salario >= 2000){
      load_page();
   }

   if(sigaction(SIGUSR1, &sa, NULL) != 0){
      perror("Falha ao instalar tratador de sinal SIGUSR1");
      exit(-1);
   }

   if(sigaction(SIGUSR2, &sa, NULL) != 0){
      perror("Falha ao instalar tratador de sinal SIGUSR2");
      exit(-1);
   }

   for(;;){}
   return 0;
}
