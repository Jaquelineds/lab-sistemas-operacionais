#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	int fd[2];

	if (pipe(fd) != 0){
		perror("Erro no pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()){
	case -1:
		perror("Erro no fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		close(fd[1]);
		printf("\nFilho trocando o pipe\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		printf("\nFilho vai rodar o exec\n");
		execlp("wc", "wc", NULL);
		perror("exec WC");
		break;
	default:
		close(fd[0]);
		printf("\nPai trocando o pipe\n");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		printf("\nPai vai rodar o exec\n");
		execlp("ls", "ls", NULL);
		perror("exec LS");
		break;
	}
	exit(EXIT_SUCCESS);
}
