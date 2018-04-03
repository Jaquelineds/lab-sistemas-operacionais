#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const char* CHAVE = "/compart1";
const int   SIZE  = 1024*4096;

typedef struct InfoCompartilhada {
	int a;
	double d;
	long n[200];
} InfoCompartilhada_t;

int main(void) {

	// criar a memória compartilhada
	int shfd = shm_open(CHAVE, O_RDWR | O_CREAT , 0600);
	if (shfd < 0) { perror("shm_open"); exit(1); }
	printf("shfd =  %d\n", shfd);

	if (ftruncate(shfd, SIZE) != 0) { perror("ftruncate"); exit(1); }

	// mapear a memória
	void* addr = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shfd, 0);
	if (addr == (void*) -1) { perror("mmap"); exit(1); }

	InfoCompartilhada_t* v = (InfoCompartilhada_t*) addr;

	v->a = 0;
	v->d = 0;
	v->n[35] = 0x0;

	switch (fork()) {
	case -1: perror("fork"); exit(39);
	case 0: // no filho
		// escrever na memoria compartilhada
		printf("Filho iniciando...\n");
		sleep(2);
		v->a = 35;
		v->d = 3.14158192;
		v->n[35] = 0xFFFF;
		exit(EXIT_SUCCESS);
	default: // no pai
		printf("Pai aguardando filho terminar...\n");
		wait(NULL); // esperar o filho terminar
		// ler da memoria compartilhada
		printf("\nv: a=%d d=%f n[35]=%lx\n", v->a, v->d, v->n[35]);
	}
	// remover
	shm_unlink(CHAVE);

	printf("Terminou!\n");
	return EXIT_SUCCESS;
}















