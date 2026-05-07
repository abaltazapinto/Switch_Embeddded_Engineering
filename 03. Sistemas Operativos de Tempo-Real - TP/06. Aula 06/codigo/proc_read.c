#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_LEN 128

int main(void)
{
    char buf[BUF_LEN];
    int ret;
    int fd;

    fd = open("/proc/cpuinfo", O_RDONLY);

    if (fd == -1)
    {
        printf("Erro ao abrir /proc/cpuinfo\n");
        return (1);
    }

    ret = read(fd, buf, BUF_LEN - 1);

    if (ret == -1)
    {
        printf("Erro no read\n");
        close(fd);
        return (1);
    }

    buf[ret] = '\0';

    printf("%s\n", buf);

    close(fd);

    return (0);
}
