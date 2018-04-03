#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

void sinal_chegou(){
	printf("\nO sinal chegou\n");
	fflush(stdout);
}

void tratador(int signum){
	sinal_chegou();	
}

int main(){
	sigset_t mask;
	struct sigaction action;
	memset(&action, 0, sizeof(action));

	action.sa_handler = &tratador;

	if(sigaction(SIGINT, &action, NULL) == -1){
		perror("Falha em sigaction");
		exit(-1);
	}

	sigfillset(&mask);
	sigdelset(&mask,SIGINT);

	while(1){
		sigsuspend(&mask);
	}
	return 0;
}
