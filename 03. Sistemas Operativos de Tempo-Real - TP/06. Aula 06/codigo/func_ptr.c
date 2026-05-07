#include <stdio.h>

int add(int a, int b)
{
    return (a + b);
}

int main(void)
{
    int (*fptr)(int, int);

    fptr = &add;

    printf("Endereco de add   : %p\n", add);
    printf("Endereco de &add  : %p\n", &add);
    printf("Valor dentro fptr : %p\n", fptr);

    return (0);
}
