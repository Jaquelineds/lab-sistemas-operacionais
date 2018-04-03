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

//Definicoes das funcoes
void abrir(char *nomearq);			//Abrir o arquivo
int indicarTamanho(void);			//Retorna tamanho do arquivo
void fechar(void);				//Fechar corretamente o arquivo
void contar(char* nomearq1, char* nomearq2);	//Retorna tamanho do arquivo
void* contarVogais(void *p);			//Retorna quantidade de vogais do primeiro arquivo
void* compararConteudo(void *p);		//Compara os conteudos dos arquivos
void comparar(void);				//Compara os tamanhos dos arquivos
void sair(void);				//Finaliza o programa

static int fd;					//Descritor do arquivo
static int tamTexto;				//Tamanho do texto do arquivo

//Setup da SHM
const char* CHAVE = "/shm1";
const int   SIZE  = 1024*4096;


ssize_t get_msg_buffer_size(mqd_t queue);

int tamArq1 = 0, tamArq2 = 0;
int main()
{

    mqd_t queue;		//Alocacao da fila
    char* buffer = NULL;	//Buffer para armazenar o pacote
    ssize_t tam_buffer;		//Tamanho do buffer
    ssize_t nbytes;		//Quantidade de bytes recebidos
    int opcao = 0;
    //Receber a mensagem, quando ela estiver na fila
    nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
	if (nbytes == -1) {
		perror("receive");
		exit(4);
	}

    TMensagem* m = (TMensagem*) buffer;

	pthread_t threads[2];		//Declaracao da Thread

	//Lancamento das Threads
	if (pthread_create(&threads[0],NULL,&contarVogais, m.nomearq1)) {
		perror("Falha na criação da thread");
		exit(-1);
	}

	if (pthread_create(&threads[1],NULL,&compararConteudo, m.nomearq1, m.nomearq2)) {
		perror("Falha na criação da thread");
		exit(-1);
	}

	while (m.opcao != 3){
		if (m.opcao == 1){
		   	contar(m.nomearq1, m.nomearq2);
		    	if (pthread_join(threads[0], NULL)) {
				perror("Falha no join das threads");
				exit(-1);
			}
		}	
		if (m.opcao == 2){
		    	comparar();
			if (pthread_join(threads[1], NULL)) {
			perror("Falha no join das threads");
			exit(-1);
			}		    
		}
	}

    sair();
}

//Implementacao do método abrir arquivo
void abrir(char *nomearq)
{
    fd = open(nomearq, O_RDONLY);		//Obtem descritor
    if (fd < 0)					//Valida a existencia do arquivo em disco
    {
        perror("Erro ao abrir arquivo! Arquivo inexistente!\n");
        exit(-1);
    }
}

//Implementacao do método ler o conteúdo do arquivo
int indicarTamanho(void)
{
    tamTexto = lseek(fd, 0, SEEK_END);	 //Obtem o tamanho do arquivo em bytes
    printf("Tamanho do arquivo: %d Bytes\n", tamTexto);
    return tamTexto;
}

//Implementacao de fechamento do arquivo
void fechar(void)
{
    close(fd);
}

void sair(void){
    mq_close(queue);
    printf("Programa encerrado com sucesso!\n");
    pthread_exit(NULL);
    exit(EXIT_SUCCESS);
}

void contar(char* nomearq1, char* nomearq2){
    abrir(nomearq1);				//Abre o arquivo e obtem descritor
    tamArq1 = indicarTamanho();			//Obtem o conteudo do arquivo
    fechar();					//Fecha o arquivo

    abrir(nomearq2);				//Abre o arquivo e obtem descritor
    tamArq2 = indicarTamanho();			//Obtem o conteudo do arquivo
    fechar();					//Fecha o arquivo
}

void comparar(){
    if (tamArq1 > tamArq2)
        printf("O primeiro arquivo indicado é maior que o segundo\n");
    else if (tamArq1 < tamArq2)
        printf("O segundo arquivo indicado é maior que o primeiro\n");
    else
        printf("Os arquivos têm o mesmo tamanho\n");
}

//Thread contar vogais
void contarVogais(void p*){
    int c;
    while ((c = getchar()) != 'a' && c = getchar()) != 'e' && c = getchar()) != 'i' && c = getchar()) != 'o' && c = getchar()) != 'u' && c != EOF)
        ;
    return NULL;
}

//Thread compararConteudo
void compararConteudo(void p*){  
   return NULL;
}
