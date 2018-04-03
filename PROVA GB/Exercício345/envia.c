**********JAQUELINE DAHMER STEFFENON**********
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <mqueue.h>

//Nome da fila
const char* NOME_FILA = "/fila1";

//Estrutura da mensagem
typedef struct Mensagem {
	char* nomeArq1;
	char* nomeArq2;
	int opcao;
} TMensagem;


int main(int argc, char *argv[])
{
	if (argc < 4)	//Validacao da entrada
	{
		perror("Entrada inválida! Devem ser informados 2 parâmetros com nome de 2 arquivos.\n");
		exit(-1);
	}

	mqd_t queue;	//Alocacao da fila
	TMensagem m;	//Alocacao da mensagem

	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("Erro na abertura da fila!");
		exit(2);
	}
	//Montar a mensagem a ser enviada
	m.nomeArq1 = argv[0];
	m.nomeArq2 = argv[1];
	m.opcao = (double) argv[2];

	//Enviar (mq_send)
	if (mq_send(queue, (const char*) &m, sizeof(TMensagem), 0) != 0) {
		perror("Erro no envio de mensagem!");
	}

	//Liberar descritor (mq_close)
	mq_close(queue);

	printf("Programa encerrado com sucesso!\n");
	exit(EXIT_SUCCESS);
}
