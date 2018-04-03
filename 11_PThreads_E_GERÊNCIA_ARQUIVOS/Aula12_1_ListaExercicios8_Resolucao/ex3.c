#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define READ_LENGTH 128

int gravar_arquivo(char *nome);
void ler_arquivo(int fd);
void flush(void);

int main()
{
    char nomearq[256];

    printf("Digire o nome do arquivo: ");
    scanf("%s", nomearq);

    int fd;
    fd = open(nomearq, O_RDONLY);
    if (fd == -1)
    {
        printf("\nO arquivo não existe.\n");
        fd = gravar_arquivo(nomearq);
    }
    else
    {
        printf("\nO arquivo existe!\n");
        ler_arquivo(fd);
        printf("\n\n");
    }

    close(fd);
    return 0;
}

int gravar_arquivo(char *nome)
{
    char texto[512];
    printf("Digite o texto: ");
    flush();
    fgets(texto, 512, stdin);
    flush();

    int fd = open(nome, O_RDWR | O_CREAT, S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH | S_IWOTH);
    if (fd < 0)
    {
        perror("\nErro na escrita.\n");
        return -1;
    }

    int length = strlen(texto);
    printf("\nTamanho do texto: %d\n", length);
    int status = write(fd, texto, length);

    if (status < 0)
    {
        perror("\nFalha na escrita do arquivo.\n");
        return -1;
    }

    close(fd);
    return fd;
}

void ler_arquivo(int fd)
{
    int tamanho = lseek(fd, 0, SEEK_END);
    printf("\nTamanho do arquivo: %d B\n", tamanho);
    lseek(fd, 0, SEEK_SET);

    printf("\nConteúdo do arquivo:\n");
    int total_read = READ_LENGTH;
    char c[READ_LENGTH];
    while (READ_LENGTH == total_read)
    {
        total_read = read(fd, c, READ_LENGTH);

        if (READ_LENGTH > total_read)
        {
            c[total_read] = '\0';
            printf("%s", c);
            break;
        }
        else
        {
            printf("%s", c);
        }
    }
}

void flush(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
