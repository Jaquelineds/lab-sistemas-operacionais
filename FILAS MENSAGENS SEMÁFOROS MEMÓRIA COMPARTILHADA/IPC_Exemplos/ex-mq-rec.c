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

ssize_t get_msg_buffer_size(mqd_t queue);
void print_msg(TMensagem* m);

int main(void) {
	mqd_t queue;
	char* buffer = NULL;
	ssize_t tam_buffer;
	ssize_t nbytes;

	// obter descritor (mq_open+O_RDONLY)
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	// alocar buffer para receber msg
	tam_buffer = get_msg_buffer_size(queue);
	buffer = calloc(tam_buffer, 1);

	// receber (mq_recv)
	nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
	if (nbytes == -1) {
		perror("receive");
		exit(4);
	}

	printf("bytes recebidos: %ld\n", nbytes);
	print_msg((TMensagem*) buffer);


	// liberar descritor (mq_close)
	mq_close(queue);
	printf("Fim!\n");
	exit(EXIT_SUCCESS);

}

void print_msg(TMensagem* m) {
	printf("a=%d, c=%s\n", m->id, m->nome);
}


ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	/* Determine max. msg size; allocate buffer to receive msg */
	if (mq_getattr(queue, &attr) != -1) {
		printf("max msg size: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("aloca_msg_buffer");
	exit(3);
}











