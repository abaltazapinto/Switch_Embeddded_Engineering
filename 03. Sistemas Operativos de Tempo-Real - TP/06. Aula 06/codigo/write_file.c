#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_LENGTH 50

int main(void)
{
    char buf[BUF_LENGTH] = "hello world\n";
    int ret;
    int fd;

    fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        printf("Erro ao abrir ficheiro\n");
        return (1);
    }

    ret = write(fd, buf, strlen(buf));

    printf("Bytes escritos: %d\n", ret);

    close(fd);

    return (0);
}
