**********JAQUELINE DAHMER STEFFENON**********
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>

//Definicoes das funcoes
void abrir(char *nomearq);			//Abrir o arquivo
int indicarTamanho(void);			//Retorna tamanho do arquivo
void fechar(void);				//Fechar corretamente o arquivo

static int fd;					//Descritor do arquivo
static int tamTexto;				//Tamanho do texto do arquivo

int tamArq1 = 0, tamArq2 = 0;
int main(int argc, char *argv[])
{
    if (argc < 3)				//Validacao da entrada
    {
        perror("Entrada inválida! Devem ser informados 2 parâmetros com nome de 2 arquivos.\n");
        exit(-1);
    }

    abrir(argv[1]);				//Abre o arquivo e obtem descritor
    tamArq1 = indicarTamanho();			//Obtem o conteudo do arquivo
    fechar();					//Fecha o arquivo

    abrir(argv[2]);				//Abre o arquivo e obtem descritor
    tamArq2 = indicarTamanho();			//Obtem o conteudo do arquivo
    fechar();					//Fecha o arquiv

    if (tamArq1 > tamArq2)
	printf("O primeiro arquivo indicado é maior que o segundo\n");
    else if (tamArq1 < tamArq2)
	printf("O segundo arquivo indicado é maior que o primeiro\n");
    else
	printf("Os arquivos têm o mesmo tamanho\n");

    return 0;
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
    tamTexto = lseek(fd, 0, SEEK_END);	 	//Obtem o tamanho do arquivo em bytes
    printf("Tamanho do arquivo: %d Bytes\n", tamTexto);
    return tamTexto;
}

//Implementacao de fechamento do arquivo
void fechar(void)
{
    close(fd);
}
