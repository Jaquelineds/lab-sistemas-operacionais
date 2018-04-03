#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

// 1) O NOME DA FILA
const char* NOME_FILA = "/fila1";

// 2) ESTRUTURA DA MSG
typedef struct Mensagem {
	int id;
	char nome[30];
} TMensagem;

int main(int argc, char* argv[]) {
	mqd_t queue;
	TMensagem m;
	char* texto = argv[1];

	// obter descritor (mq_open+O_WRONLY+O_CREAT)
	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	// montar mensagem
	m.id = 1;
	strncpy(m.nome, texto, 29);

	// enviar (mq_send)
	if (mq_send(queue, (const char*) &m, sizeof(TMensagem), 29) != 0) {
		perror("send #29");
	}
	if (mq_send(queue, (const char*) &m, sizeof(TMensagem), 35) != 0) {
		perror("send #35");
	}

	// liberar descritor (mq_close)
	mq_close(queue);

	printf("Mensagem enviada!\n");
	exit(EXIT_SUCCESS);
}
























