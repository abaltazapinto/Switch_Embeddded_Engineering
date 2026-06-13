## Reset completo — Exercício 3.2: Loop Index Pitfall 🧵

O 3.2 tem **3 fases**. O objetivo é perceber o erro de passar `&i` às threads e depois corrigir isso com memória separada para cada thread. O enunciado pede: primeiro passar `&i`, depois usar array local na `main`, e por fim declarar o array como `static global`. 

---

# 3.2.1 — Versão errada: passar `&i`

## Ideia

```c
pthread_create(&threads[i], NULL, worker, &i);
```

Isto passa o **endereço da variável `i`**, não uma cópia do valor.

Todas as threads recebem o mesmo endereço:

```text
worker 0 → &i
worker 1 → &i
worker 2 → &i
worker 3 → &i
worker 4 → &i
```

Por isso aparecem valores repetidos ou aleatórios.

## Código errado de propósito

```c
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

void *worker(void *arg)
{
    int *value;

    value = (int *)arg;

    printf("worker received i = %d\n", *value);

    return NULL;
}

int main(void)
{
    pthread_t threads[NTHREADS];
    int i;

    i = 0;
    while (i < NTHREADS)
    {
        pthread_create(&threads[i], NULL, worker, &i);
        i++;
    }

    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    return 0;
}
```

## Conclusão para o caderno

```text
Passing &i is unsafe because all threads receive the address of the same loop variable.
The main thread continues modifying i while worker threads may read it later.
Therefore, the printed values are non-deterministic and may be repeated or unexpected.
```

---

# 3.2.2 — Correção com array local na `main`

## Ideia

Agora cada thread recebe uma célula diferente:

```text
worker 0 → &values[0]
worker 1 → &values[1]
worker 2 → &values[2]
worker 3 → &values[3]
worker 4 → &values[4]
```

## Código

```c
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

void *worker(void *arg)
{
    int *value;

    value = (int *)arg;

    printf("worker received i = %d\n", *value);

    return NULL;
}

int main(void)
{
    pthread_t threads[NTHREADS];
    int values[NTHREADS];
    int i;

    i = 0;
    while (i < NTHREADS)
    {
        values[i] = i;
        pthread_create(&threads[i], NULL, worker, &values[i]);
        i++;
    }

    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    return 0;
}
```

## Conclusão para o caderno

```text
Using a local array in main fixes the loop index bug because each thread receives the address of a different array cell.
This makes the values stable: each worker receives one of 0, 1, 2, 3, or 4.
The output order may still change because thread scheduling is non-deterministic.
```

## Atenção

Esta versão é segura **porque existe `pthread_join()`**.

Se a `main` terminasse antes das workers, o array local poderia deixar de ser válido.

---

# 3.2.3 — Versão com `static global`

## Ideia

Agora o array sai da `main()`:

```c
static int values[NTHREADS];
```

Isto dá ao array duração de vida global: ele existe durante toda a execução do programa.

---

## Código final do 3.2.3

```c
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

static int values[NTHREADS];

void *worker(void *arg)
{
    int *value;

    value = (int *)arg;

    printf("worker received i = %d\n", *value);

    return NULL;
}

int main(void)
{
    pthread_t threads[NTHREADS];
    int i;

    i = 0;
    while (i < NTHREADS)
    {
        values[i] = i;
        pthread_create(&threads[i], NULL, worker, &values[i]);
        i++;
    }

    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    return 0;
}
```

Compilar:

```bash
gcc -Wall -Wextra -o ex2a ex2_loop_index_pitfall2.c -lpthread
```

Executar:

```bash
./ex2a
./ex2a
./ex2a
```

---

# O que deves observar

Podes ver:

```text
worker received i = 0
worker received i = 1
worker received i = 2
worker received i = 3
worker received i = 4
```

Ou:

```text
worker received i = 3
worker received i = 1
worker received i = 4
worker received i = 0
worker received i = 2
```

Ambos estão corretos.

O importante:

```text
Os valores devem ser 0, 1, 2, 3, 4.
A ordem pode mudar.
```

---

# Diferença essencial

| Versão        | O que passa à thread | Resultado                                               |
| ------------- | -------------------- | ------------------------------------------------------- |
| Errada        | `&i`                 | todas partilham a mesma variável                        |
| Array local   | `&values[i]`         | cada thread recebe célula diferente                     |
| Static global | `&values[i]`         | cada thread recebe célula diferente com lifetime global |

---

# Data isolation — resposta importante

## Array local na `main`

Vantagem:

```text
Mais isolado.
A memória pertence à main.
Menos estado global espalhado.
```

Risco:

```text
Só é seguro enquanto a main não terminar antes das workers.
```

## Static global

Vantagem:

```text
A memória existe durante toda a vida do programa.
Não depende da stack da main.
```

Risco:

```text
Menor isolamento de dados.
Qualquer função neste ficheiro pode aceder ao array.
Se várias threads modificarem os mesmos dados, podes ter race conditions.
```

---

# Resposta curta para entregar

```text
Passing &i to all threads is unsafe because all worker threads receive the same memory address.
Since the main thread keeps modifying i inside the loop, each worker may read a different or repeated value depending on scheduling.

Using an array fixes the problem because each thread receives the address of a different array element.
A local array in main is safe here because the main thread waits for all workers using pthread_join() before returning.

Declaring the array as static global gives it lifetime for the entire program execution.
However, it reduces data isolation because the data becomes globally shared, which can make the program harder to reason about and may introduce race conditions if multiple threads write to the same locations.
```

---

## Próxima decisão

Queres agora avançar para o **3.3 — Structure Encapsulation**, onde passas vários argumentos para cada thread usando uma `struct`?



# 3.2.3

Passing &i to all threads is unsafe because all worker threads receive the same memory address.
Since the main thread keeps modifying i inside the loop, each worker may read a different or repeated value depending on scheduling.

Using an array fixes the problem because each thread receives the address of a different array element.
A local array in main is safe here because the main thread waits for all workers using pthread_join() before returning.

Declaring the array as static global gives it lifetime for the entire program execution.
However, it reduces data isolation because the data becomes globally shared, which can make the program harder to reason about and may introduce race conditions if multiple threads write to the same locations.

