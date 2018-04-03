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

int main(int argc, char* argv[]) {
	mqd_t queue;
	TMensagem m;
	int id, sair = 0;	//Variaveis de apoio
	double peso;

	// obter descritor (mq_open+O_WRONLY+O_CREAT)
	queue = mq_open(NOME_FILA, O_WRONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}

	// montar mensagem
	printf("Digite o id do pacote: ");
	scanf("%d",&id);
	printf("Digite o peso do pacote: ");
	scanf("%lf",&peso);
	m.id = id;
	m.peso = peso;

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

	// liberar descritor (mq_close)
	mq_close(queue);

	printf("Mensagem enviada!\n");
	exit(EXIT_SUCCESS);
}
























