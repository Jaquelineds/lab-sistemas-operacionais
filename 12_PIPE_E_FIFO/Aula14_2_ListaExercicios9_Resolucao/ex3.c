#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

volatile char nomearq[50];

int main(){
	printf("Digite o nome do arquivo:");
	scanf("%s", nomearq);
	
	if(strcmp(strrchr((char*)nomearq,'.'),".gz") == 0){
		int fd[2];
		char line[4096];
		if (pipe(fd) != 0){
			perror("Erro no pipe");
			exit(EXIT_FAILURE);
		}
		switch (fork()){
			case -1:
				perror("Erro no fork");
				exit(-1);
				break;
			case 0:
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				execlp("gzip", "cd", nomearq, NULL);
				perror("exec gzip");
				break;
			default:
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				int n=read(STDOUT_FILENO,line,4096);
				write(STDOUT_FILENO, line, n);
				break;
		}
	}else{
		int fd = open((char*)nomearq, O_RDONLY);
		int tamanho = lseek(fd, 0, SEEK_END);
		char conteudo[tamanho];
		lseek(fd, 0L, SEEK_SET);
		if (read(fd, (void*) conteudo, tamanho) == -1) perror("Falha de leitura");
		printf("\n%s\n",conteudo);
	}
}
