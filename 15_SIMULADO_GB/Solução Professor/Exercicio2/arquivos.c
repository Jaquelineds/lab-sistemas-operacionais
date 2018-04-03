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
void ler(void);					//Ler o conteudo do arquivo
void contar(char *palavra);			//Contar o numero de ocorrencias da palavra, linearmente, dentro do arquivo
void fechar(void);				//Fechar corretamente o arquivo

static int fd;					//Descritor do arquivo
static int tamTexto;				//Tamanho do texto do arquivo

int main(int argc, char *argv[])
{
    if (argc < 3)				//Validacao da entrada
    {
        perror("Entrada inválida! Devem ser informados 2 parâmetros: nomearq palavra.\n");
        exit(-1);
    }

    abrir(argv[1]);				//Abre o arquivo e obtem descritor
    ler();					//Obtem o conteudo do arquivo
    contar(argv[2]);
    fechar();					//Fecha o arquivo 
    return 0;
}

//Implementacao do método abrir arquivo
void abrir(char *nomearq)
{
    fd = open(nomearq, O_RDONLY);		//Obtem descritor
    if (fd < 0)					//Valida a existencia do arquivo em disco
    {
        perror("Erro ao abrir arquivo!\n");
        exit(-1);
    }
}

//Implementacao do método ler o conteúdo do arquivo
void ler(void)
{
    tamTexto = lseek(fd, 0, SEEK_END);	 	//Obtem o tamanho do arquivo em bytes
    char conteudoArquivo[tamTexto];		//Variavel para armazenar o conteudo do arquivo
    printf("Tamanho do arquivo: %d Bytes\n", tamTexto);

    lseek(fd, 0, SEEK_SET);			//Reposiciona o ponteiro de leitura para o primeiro caracter do arquivo
    read(fd, conteudoArquivo, tamTexto);	//Ler o conteúdo do arquivo no disco e transferir para a memória
    printf("Conteúdo do arquivo: %s ", conteudoArquivo);
}

//Implementacao contar palavras
void contar(char *palavra)
{
    int posAtual = 0, qtdPalavra = 0;		//Controle da posicao atual do ponteiro
    int tamPalavra = strlen(palavra);		//Obtem o tamanho da palavra
    char palavraTexto[tamPalavra];		//Trecho do texto do arquivo a ser obtido

    while(posAtual < tamTexto) {		//Laco para percorrer o conteudo do arquivo
        lseek(fd, posAtual, SEEK_SET);		//Reposiciona o ponteiro de leitura para a posição inicial a ser lida do arquivo
	read(fd, palavraTexto, tamPalavra);	//Ler do arquivo a string do tamanho da palavra pesquisada
	if(!strcmp(palavraTexto,palavra)){	//Comparacao da palavra digitada com a palavra obtida do arquivo
		qtdPalavra++;			//Contador de palavras encontradas
		posAtual+=tamPalavra;		//Se encontrar a palavra, deslocar o contr. para posição posterior a palavra encontrada
	}
	posAtual++;				//Acumulador de posicao corrente
    }
    printf("Total de ocorrências de %s: %d \n", palavra, qtdPalavra);
}

//Implementacao de fechamento do arquivo
void fechar(void)
{
    close(fd);
}
