#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

// 1) O NOME DA FILA
const char* NOME_FILA = "/xadrez";

// 2) ESTRUTURA DA MSG
typedef struct Jogada {
	int id;
	int x;
	int y;
} TJogada;

int main(int argc, char* argv[]) {
	mqd_t queue;
	TJogada j;
	j.id = 1;
	
	// obter descritor (mq_open+O_WRONLY+O_CREAT)
	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	// montar mensagem
	char input[3];
	printf("Digite a coordenada desejada: ");
	scanf("%s", input);
	j.x = input[0] - 48;
	j.y = input[1] - 48;
	
	// enviar (mq_send)
	if (mq_send(queue, (const char*) &j, sizeof(TJogada), 29) != 0) {
		perror("send #29");
	}
	
	//testar a jogada (ver número)
	void print_msg(TJogada* j);

	// liberar descritor (mq_close)
	mq_close(queue);

	printf("Mensagem enviada!\n");
	exit(EXIT_SUCCESS);
}
