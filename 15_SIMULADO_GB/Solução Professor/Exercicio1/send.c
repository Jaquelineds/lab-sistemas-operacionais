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

int main(int argc, char* argv[]) {
	mqd_t queue;		//Alocacao da fila
	TMensagem m;		//Alocacao do objeto pacote (mensagem)
	int id, peso, sair = 0;	//Variaveis de apoio

	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("Erro na abertura da fila!");
		exit(2);
	}

	//Loop para despacho controlado
	while(sair==0){
		printf("Digite o id do pacote: ");
		scanf("%d",&id);
		printf("Digite o peso do pacote: ");
		scanf("%d",&peso);

		printf("Enviando um pacote para despachar... \n");

		//Montar pacote a ser enviado por mensagem
		m.id = id;
		m.peso = peso;

		//Enviar (mq_send)
		if (mq_send(queue, (const char*) &m, sizeof(TMensagem), 0) != 0) {
			perror("Erro no envio de pacotes!");
		}

		printf("Pacote enviado para o despacho!\n");

		printf("Deseja continuar despachando pacotes (0=SIM) (1=NÃO)? ");
		scanf("%d",&sair);
	}

	//Liberar descritor (mq_close)
	mq_close(queue);

	printf("Programa encerrado com sucesso!\n");
	exit(EXIT_SUCCESS);
}
























