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
	double peso;
} TMensagem;

double pesoTotal = 0;

ssize_t get_msg_buffer_size(mqd_t queue);
void print_msg(TMensagem* m);

int main(void) {
	mqd_t queue;
	char* buffer = NULL;
	ssize_t tam_buffer;
	ssize_t nbytes;
	int sair = 0;		//Flag para encerrar

	//Loop para despacho controlado
	while(sair==0){
		printf("Aguardando a chegada de pacote para despachar... \n");

		//Receber a mensagem, quando ela estiver na fila
		nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
		if (nbytes == -1) {
			perror("receive");
			exit(4);
		}

		//Tamanho do pacote recebido
		printf("Bytes Recebidos: %ld\n", nbytes);
		print_msg((TMensagem*) buffer);

		//Controle de execucao
		printf("Deseja continuar despachando pacotes (0=SIM) (1=NÃO)? ");
		scanf("%d",&sair);
	}


	// liberar descritor (mq_close)
	mq_close(queue);
	printf("Fim!\n");
	exit(EXIT_SUCCESS);

}

void print_msg(TMensagem* m) {
	printf("Id = %d\nPeso = %lf\n", m->id, m->peso);
	printf("Peso total despachado: %f\n", pesoTotal+=m->peso);
}


ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	/* Determine max. msg size; allocate buffer to receive msg */
	if (mq_getattr(queue, &attr) != -1) {
		printf("Tamanho máximo da mensagem: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("Erro na alocação do buffer!");
	exit(3);
}











