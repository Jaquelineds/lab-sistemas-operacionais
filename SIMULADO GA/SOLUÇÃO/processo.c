#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid;
	char url[100] = "";

	printf("Digite a URL: ");
	scanf("%s", url);

	switch(fork()){
	case -1:
		perror("Erro no fork\n");
		exit(-1);
		break;
	case 0:
		printf("Filho: Meu PID = %d, PPID = %d\n", getpid(), getppid());
		execlp("firefox", "--new-window", url, NULL);
		exit(13);
		break;
	default:
		printf("Pai: Meu PID = %d, PPID = %d\n", getpid(), getppid());
		pid = wait(&status);
		printf("Pai: Filho (PID = %d) terminou, Status = %d \n", pid, WEXITSTATUS(status));
	}
	printf("PID %d terminando...\n", getpid());
	return 0;
}
