#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_LEN 50

int main(void)
{
    char buf[BUF_LEN];
    int ret;
    int fd;

    fd = open("foo.txt", O_RDONLY);

    if (fd == -1)
    {
        printf("Erro ao abrir ficheiro\n");
        return (1);
    }

    while ((ret = read(fd, buf, BUF_LEN - 1)) > 0)
    {
printf("Bytes lidos: %d\n", ret);
        buf[ret] = '\0';
        printf("%s", buf);
printf("Bytes lidos: %d\n", ret);
    }

    close(fd);

    return (0);
}
