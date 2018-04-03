#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

void tratador(int signum){
	switch(signum){
		case SIGUSR1: printf("Recebido sinal SIGUSR1 (%d)\n", signum); break;
		case SIGCONT: printf("Recebido sinal SIGCONT (%d)\n", signum); break;
		case SIGTERM: printf("Recebido sinal SIGTERM (%d)\n", signum); break;
		case SIGINT: printf("Recebido sinal SIGINT (%d)\n", signum); break;
		case SIGTSTP: printf("Recebido sinal SIGTSTP (%d)\n", signum); break;
		case SIGQUIT: printf("Recebido sinal SIGQUIT (%d)\n", signum); break;
	}
}

int main(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &tratador;

	printf("Meu PID = %d\n", getpid());

	if(sigaction(SIGUSR1, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGUSR1");
		exit(-1);
	}
	if(sigaction(SIGCONT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGCONT");
		exit(-1);
	}
	if(sigaction(SIGTERM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGTERM");
		exit(-1);
	}
	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGINT");
		exit(-1);
	}
	if(sigaction(SIGTSTP, &sa, NULL) != 0){	//conforme visto em aula o STOP é capturado pelo SO
		perror("Falha ao instalar tratador de sinal SIGTSTP");
		exit(-1);
	}
	if(sigaction(SIGQUIT, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGQUIT");
		exit(-1);
	}
	for(;;)	{
	}	//espera (busy-waiting) pelo sinal
	return 0;
}




