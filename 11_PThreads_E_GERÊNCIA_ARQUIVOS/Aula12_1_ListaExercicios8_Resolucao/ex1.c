#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

#define NUM_THREADS 3
#define NUM_MSG 5
#define SLEEP_TIME 1

struct Param {
	pthread_t pai;
	char* param;
};

void* PrintHello(void *param) {
	int i;
	struct Param* p = param;
	printf("Meu ID: %ld, ID do Pai:%ld\n",pthread_self(),p->pai);
	for (i=0; i<NUM_MSG; i++) {
		sleep(SLEEP_TIME);
		printf("Ola, estou aqui! %s!\n", p->param);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t tids[NUM_THREADS];
	struct Param p[NUM_THREADS];
	int n;
	int terror;
	char* names[NUM_THREADS] = { "maria", "jose", "bento" };
	for (n=0; n<NUM_THREADS; n++) {
		p[n].pai = pthread_self();
		p[n].param = names[n];
		terror = pthread_create(&tids[n],NULL,&PrintHello,(void *) &p[n]);
		if (terror) {
			errno = terror;
			perror("Falha na criação da thread");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}
