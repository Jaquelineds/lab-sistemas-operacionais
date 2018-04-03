#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


const char* NOME_FILA = "/xadrez";
int lock = 1;
int primeira_jogada = 1;
int jogada_atual = 1;

// 2) ESTRUTURA DA MSG
typedef struct Jogada {
	int id;
	int x;
	int y;
} TJogada;

ssize_t get_msg_buffer_size(mqd_t queue);
void print_msg(TJogada* j);
char tabuleiro[3][3];

//Parte principal
int main(void) {
	int vencedor = 0;
	mqd_t queue;
	char* buffer = NULL;
	ssize_t tam_buffer;
	ssize_t nbytes;

	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			tabuleiro[i][j] = ' ';

	//FILA TEM QUE SER CRIADA EM MODO READ ONLY + CREATE, SENÃO ELE NÃO CRIA COMUNICAÇÃO POR AQUI
	//obter descritor (mq_open+O_RDONLY+O_CREAT)
	queue = mq_open(NOME_FILA, O_RDONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}
	
	/*APENAS LÊ A FILA CRIADA PELO JOGADOR - POBREMINHA
	// obter descritor (mq_open+O_RDONLY)
	queue = mq_open(NOME_FILA, O_RDONLY);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}*/

	//alocar buffer para receber msg OK
	tam_buffer = get_msg_buffer_size(queue);
	buffer = calloc(tam_buffer, 1);
	while (vencedor == 0) {

		//receber (mq_recv) OK
		nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
		if (nbytes == -1) {
			perror("Recebimento de mensagem.");
			exit(4);
		}
			
		//Testa ganhador
		//Aqui é o lugar certo de dar espaço para o ganhador	
		vencedor = print_tab((TJogada*) buffer);
		if (vencedor == 1) printf("VENCEDOR 1\n");
		if (vencedor == 2) printf("VENCEDOR 2\n");
	}
	//liberar descritor (mq_close) OK
	mq_close(queue);
	mq_unlink(NOME_FILA);
	printf("Fim!\n\n");
	exit(EXIT_SUCCESS);
}

//Imprime a jogada e retorna vencedor
int print_tab(TJogada* j) {
	char symbol;
	//Se a mensagem vem do jogador 1
	if (j->id == 1) {
		//Simbolo é um X
		symbol = 'X';
		//Se for primeira jogada ou a jogada atual for do jogador 2
		if ((jogada_atual == 2) || (primeira_jogada == 1)) {
			//Jogada atual passa a ser do jogador 1
			jogada_atual = 1;
			//Primeira jogada já passou
			primeira_jogada = 0;
			//Destrava controle de jogada
			lock = 0;
		}
	}
	//Se a mensagem vem do jogador 2
	if (j->id == 2) {
		//Símbolo é um O
		symbol = 'O';
		//Se não é mais a primeira jogada e a atual é do jogador 1
		if ((jogada_atual == 1) && (primeira_jogada == 0)) {
			//Jogada atual passa a ser do jogador 2
			jogada_atual = 2;
			//Destrava controle de jogada
			lock = 0;
		}
	}

	//Somente mostra e conta a jogada na ordem correta de jogadores (1,2,1,...)
	if (lock == 0) {
		//Desenha o tabuleiro
		if (tabuleiro[j->x][j->y] == ' ') tabuleiro[j->x][j->y] = symbol;
		for (int i = -1; i < 3; i++) {
			if (i != -1) printf("%d  ", i);
			for (int j = 0; j < 3; j++) {
				if (i == -1) printf(" %d  ", j);
				else printf("%c  ", tabuleiro[i][j]);
			}
		printf("\n");
		}
	//Trava jogada até resolver lógica de próximo jogador	
	lock = 1;
	//Printa um expaço pra ficar bunitu
	printf("\n");
	}

	//Este print estava deixando espaços a cada jogada errada!!!
	//printf("\n");

	//Teste para linhas paralelas (jogador1)
	for (int i = 0; i < 3; i++) {
		if ((tabuleiro[0][i] == 'X') && (tabuleiro[1][i] == 'X') && (tabuleiro[2][i] == 'X')) return 1;
		if ((tabuleiro[i][0] == 'X') && (tabuleiro[i][1] == 'X') && (tabuleiro[i][2] == 'X')) return 1;
	}

	//Teste para linhas paralelas (jogador2)
	for (int i = 0; i < 3; i++) {
		if ((tabuleiro[0][i] == 'O') && (tabuleiro[1][i] == 'O') && (tabuleiro[2][i] == 'O')) return 2;
		if ((tabuleiro[i][0] == 'O') && (tabuleiro[i][1] == 'O') && (tabuleiro[i][2] == 'O')) return 2;
	}

	//Teste correto da diagonal (jogador1)
	if ((tabuleiro[0][0] == 'X') && (tabuleiro[1][1] == 'X') && (tabuleiro[2][2] == 'X')) return 1;
	if ((tabuleiro[0][2] == 'X') && (tabuleiro[1][1] == 'X') && (tabuleiro[2][0] == 'X')) return 1;

	//Teste correto da diagonal (jogador2)
	if ((tabuleiro[0][0] == 'O') && (tabuleiro[1][1] == 'O') && (tabuleiro[2][2] == 'O')) return 1;
	if ((tabuleiro[0][2] == 'O') && (tabuleiro[1][1] == 'O') && (tabuleiro[2][0] == 'O')) return 1;

	return 0;
}

//Verificar mensagem do buffer
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

/*TESTE DA DIAGONAL DO JOGO DA VELHA - ERRADO - POBREMÃO!!!
para i = 0 até 2
	se ((tabuleiro[i][i] == 'X') && (tabuleiro[i][i] == 'X') && (tabuleiro [i][i] == 'X')) retorna 2;
fim

TESTE DE MESA
1a Iteração: se ((tabuleiro[0][0] == 'X') && (tabuleiro[0][0] == 'X') && (tabuleiro [0][0] == 'X')) retorna 2;
1a Iteração: se ((tabuleiro[1][1] == 'X') && (tabuleiro[1][1] == 'X') && (tabuleiro [1][1] == 'X')) retorna 2;
1a Iteração: se ((tabuleiro[2][2] == 'X') && (tabuleiro[2][2] == 'X') && (tabuleiro [2][2] == 'X')) retorna 2;
*/


