#include <stdio.h>
#include <stddef.h>

struct test
{
    char a;
    int  b;
    long c;
};

int main(void)
{
    printf("offset a: %zu\n", offsetof(struct test, a));
    printf("offset b: %zu\n", offsetof(struct test, b));
    printf("offset c: %zu\n", offsetof(struct test, c));

    return (0);
}
