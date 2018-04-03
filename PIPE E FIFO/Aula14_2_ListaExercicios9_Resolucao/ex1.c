#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 4096

int main(){
	int n, fd[2];
	char line[MAXLINE];

	if (pipe(fd) != 0){
		perror("Erro de pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()){
	case -1:
		perror("Erro de fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		close(fd[0]);
		printf("Filho chamado\n");
		write(fd[1],"Ola sou o filho\n",15);
		break;
	default:
		close(fd[1]);
		printf("Pai esperando\n");
		n=read(fd[0],line,MAXLINE);
		printf("Pai chamado\n");
		write(STDOUT_FILENO, line, n);
		printf("\n");
		break;
	}
	exit(EXIT_SUCCESS);
}
