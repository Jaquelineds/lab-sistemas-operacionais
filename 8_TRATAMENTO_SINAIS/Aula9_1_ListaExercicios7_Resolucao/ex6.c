#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

volatile char* url;

void abre_firefox(){
        pid_t p = fork();                                       
        if (p < 0) {                                            
                printf("\nFalha na criação do novo processo!\n");
                exit(-1);                                       
        } else if (p == 0) {
		execlp("firefox","--new-window", url, NULL);
        }
}

void tratador(int signum){
	abre_firefox();	
}

int main(int argc, char* args[]){
	
	if(argc < 2){
		printf("Deve ser informada a URL pela linha de comando!\n");
		exit(-1);
	}

	url = args[1];
	
	sigset_t mask;
	struct sigaction action;
	memset(&action, 0, sizeof(action));

	action.sa_handler = &tratador;

	if(sigaction(SIGUSR2, &action, NULL) == -1){
		perror("Falha no sinal");
		exit(-1);
	}

	printf("Meu PID = %d", getpid());
	fflush(stdout);

	sigfillset(&mask);
	sigdelset(&mask,SIGUSR2);
	sigdelset(&mask,SIGINT);

	while(1){
		sigsuspend(&mask);
	}
	return 0;
}
