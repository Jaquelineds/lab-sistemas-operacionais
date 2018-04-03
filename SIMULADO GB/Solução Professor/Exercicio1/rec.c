#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

//Nome da fila
const char* NOME_FILA = "/fila1";

//Estrutura da mensagem
typedef struct Mensagem {
	int id;
	int peso;
} TMensagem;

//Acumulador do peso
int pesoTotal = 0;

//Declaracoes
ssize_t get_msg_buffer_size(mqd_t queue);
void print_msg(TMensagem* m);

int main(void) {
	mqd_t queue;		//Alocacao da fila
	char* buffer = NULL;	//Buffer para armazenar o pacote
	ssize_t tam_buffer;	//Tamanho do buffer
	ssize_t nbytes;		//Quantidade de bytes recebidos
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

	//Liberar descritor (mq_close)
	mq_close(queue);
	printf("Programa encerrado com sucesso!\n");
	exit(EXIT_SUCCESS);

}

//Funcao para exibicao do pacote recebido
void print_msg(TMensagem* m) {
	printf("ID: %d, Peso: %d\n", m->id, m->peso);
	printf("Peso total despachado: %d\n", pesoTotal+=m->peso);
}

//Funcao para obter tamanho da mensagem
ssize_t get_msg_buffer_size(mqd_t queue) {
	struct mq_attr attr;

	/* Determine max. msg size; allocate buffer to receive msg */
	if (mq_getattr(queue, &attr) != -1) {
		printf("Tamanho max da mensagem: %ld\n", attr.mq_msgsize);
		return attr.mq_msgsize;
	}

	perror("Erro na alocacao de buffer!");
	exit(3);
}











