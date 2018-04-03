#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<pthread.h>
#include<string.h>
#include <semaphore.h>

//Declaracao das funcoes a serem executadas nas Threads
void* fatorial(void *p);
void* fibonacci(void *p);
void* primalidade(void *p);

//Setup da SHM
const char* CHAVE = "/shm1";
const int   SIZE  = 1024*4096;

//Array de int a ser processado
static int partes[3];

//Funcao de SHM com SEM
void compartilharViaMemoria(int maiorPrimo);

//Controle de SEM
sem_t sem1;

//Objeto a ser compartilhado por SHM
typedef struct InfoCompartilhada {
	int maiorPrimo;
} InfoCompartilhada_t;

int main(int argc, char* args[]){	
        if (argc < 2)					//Validacao da entrada
    	{
    	    perror("Entrada inválida! Deve ser informado 1 parâmetro: valor entre 0 e 100.\n");
    	    exit(-1);
    	}

	int valor = atoi(args[1]);			//Converter parametro em inteiro
	if(valor < 0 || valor > 100){			//Validacao do valor	
	 	perror("Entrada inválida! Deve ser informado 1 parâmetro: valor entre 0 e 100.\n");
		exit(-1);
	}

	//Preparacao do valor a ser processado e suas 3 divisoes
	printf("Valor a ser processado: %d \n",valor);
	partes[0] = valor/3;		//primeira parte
	partes[1] = partes[0]*2;	//segunda parte
	partes[2] = valor;		//terceira parte

	pthread_t threads[3];		//Declaracao da Thread

	//Lancamento das Threads
	if (pthread_create(&threads[0],NULL,&fatorial,NULL)) {
		perror("Falha na criação da thread");
		exit(-1);
	}

	if (pthread_create(&threads[1],NULL,&fibonacci,NULL)) {
		perror("Falha na criação da thread");
		exit(-1);
	}

	if (pthread_create(&threads[2],NULL,&primalidade,NULL)) {
		perror("Falha na criação da thread");
		exit(-1);
	}

	//Joinable das Threads
	for(int t=0;t<3;t++) {
		if (pthread_join(threads[t], NULL)) {
			perror("Falha no join das threads");
			exit(-1);
		}
	}
	//Encerramento do programa
	pthread_exit(NULL);
}

//Thread do Fatorial
void* fatorial(void* p) {
	int fat = 1;
	for(int i=partes[0]; i>1; i--){
		fat*= i;
	}
	printf("Fatorial de %d: %d \n", partes[0], fat);
	return NULL;
}

//Thread do Fibonacci
void* fibonacci(void* p) {
	int fib[100];
	fib[0]=0;
	fib[1]=1;
	printf("Série de Fibonacci até %d: ", partes[1]);
	for(int i=0;i<=partes[1];i++){
		if(i>1){
			if((fib[i-1]+fib[i-2])<=partes[1]){
				fib[i]= fib[i-1]+fib[i-2];
			}
			else break;
		}
		printf("%d ", fib[i]);
	}
	printf("\n");
	return NULL;
}

//Thread da Primalidade
void* primalidade(void* p) {
	int maiorPrimo = 0;
	printf("Primos até %d: ", partes[2]);
	for(int i=1; i <= partes[2]; i++){
		int div=0;
		for(int j=1; j<=i; j++){
			if(i%j==0){
				div++;
			}
		}
		if(div <= 2){
			maiorPrimo = i;			//Valor do maior primo a ser compartilhado por SHM
			printf("%d, ", i);
		}
	}
	printf("\n");
	printf("O maior primo é (Informando na Thread de Origem) : %d \n", maiorPrimo);
	compartilharViaMemoria(maiorPrimo);		//Funcao que realiza o compartilhamento do valor por SHM
	return NULL;
}

//Funcao de SHM
void compartilharViaMemoria(int maiorPrimo){
	sem_init(&sem1, 0, 1);	//Inicialização do semaphoro

	//Criar a memória compartilhada
	int shfd = shm_open(CHAVE, O_RDWR | O_CREAT , 0600);
	if (shfd < 0) { perror("shm_open"); exit(1); }

	if (ftruncate(shfd, SIZE) != 0) { perror("ftruncate"); exit(1); }

	//Mapear a memória
	void* addr = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shfd, 0);
	if (addr == (void*) -1) { perror("mmap"); exit(1); }

	//Objeto a ser compartilhado
	InfoCompartilhada_t* v = (InfoCompartilhada_t*) addr;

	switch (fork()) {
	case -1: perror("fork"); exit(39);
	case 0: // no filho
		// escrever na memoria compartilhada
		printf("Filho iniciando...\n");
		// fecha semaforo
		if (sem_wait(&sem1) != 0) exit(85);
		sleep(2);
		v->maiorPrimo = maiorPrimo;
		// libera semaforo
		if (sem_post(&sem1) != 0) exit(85);
		exit(EXIT_SUCCESS);	//Finaliza o filho
	default: // no pai
		// fecha semaforo
		if (sem_wait(&sem1) != 0) exit(85);
		printf("Pai aguardando filho terminar...\n");
		wait(NULL); // esperar o filho terminar
		// ler da memoria compartilhada
		printf("Maior primo (Informando no Processo Filho via SHM) : %d \n", v->maiorPrimo);
		// libera semaforo
		if (sem_post(&sem1) != 0) exit(85);
	}
	//Remover SHM criada
	shm_unlink(CHAVE);

	//Destruicao do semaphoro
	sem_destroy(&sem1);

	printf("Execução do filho terminou!\n");
}
