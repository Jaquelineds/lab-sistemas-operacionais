#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void* thr1(void* p);
void* thr2(void* p);

sem_t tela_lock;

int main(void) {
	pthread_t t[2];

	sem_init(&tela_lock, 0, 1);
	pthread_create(&t[0], NULL, &thr1, NULL);
	pthread_create(&t[1], NULL, &thr2, NULL);

	// aguarda finalização das threads para poder liberar o semáforo.
	sem_destroy(&tela_lock);
	pthread_exit(NULL);
}

void* thr1(void* p) {
	char* m[] = { "1Ola", "1eu", "1sou", "1a", "1thread", "1.", "\n" };

	for (int i = 0; i < 5; i++) {
		// fecha semaforo
		if (sem_wait(&tela_lock) != 0) exit(85);
		for (int j = 0; j < 7; j++) {
			write(1, m[j], strlen(m[j]));
			write(1, " ", 1);
			usleep(500000);
		}
		// libera semaforo
		if (sem_post(&tela_lock) != 0) exit(85);
	}
	return NULL;
}
void* thr2(void* p) {
	char* m[] = { "2Ola", "2eu", "2sou", "2a", "2thread", "2.", "\n" };
	for (int i = 0; i < 5; i++) {
		if (sem_wait(&tela_lock) != 0) exit(85);
		for (int j = 0; j < 7; j++) {
			write(1, m[j], strlen(m[j]));
			write(1, " ", 1);
			usleep(500000);
		}
		if (sem_post(&tela_lock) != 0) exit(85);
	}
	return NULL;
}









