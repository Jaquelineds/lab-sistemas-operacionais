#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>

void tratador(int signum){
	if(signum == SIGALRM){
		printf("O processo está executando a 5 segundos!");
		fflush(stdout);
	}
}

int main(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &tratador;

	//agenda SIGALRM para daqui a 5 segundos
	if (alarm(5) < 0){
		perror("Falha ao agendar alarme");
	}

	if(sigaction(SIGALRM, &sa, NULL) != 0){
		perror("Falha ao instalar tratador de sinal SIGUSR1");
		exit(-1);
	}

	printf("O processo é eterno, enquanto dura...\n");

	//espera ocupada (busy-waiting) pelo alarme
	while(1);
	
	printf("Linha que nunca aparece...\n");

	return 0;
}




