# Condition Variables - PRASIE

## Ideia central

Uma condition variable serve para uma thread dormir enquanto espera por uma condição.

Exemplo mental:

- condição: done == 1
- mutex protege a variável done
- cond var permite dormir/acordar sem gastar CPU

Regra essencial:

Sempre usar:

while (!condition) {
    pthread_cond_wait(&cond, &mutex);
}

Nunca confiar apenas num if.
