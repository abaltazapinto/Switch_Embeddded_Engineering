| Teste                           |          Configuração | Tempo |
| ------------------------------- | --------------------: | ----: |
| 4P / 2C — P: 500 ms / C: 100 ms |     consumers rápidos |  ~5 s |
| 4P / 2C — P: 500 ms / C: 500 ms | consumers mais lentos | ~10 s |


40 items / 2 consumers = 20 items por consumer
20 × 500 ms = 10 000 ms = 10 s

## Exercise 2.3 — Producer-Consumer using Mutex-only Synchronisation

| Test | Producers | Consumers | P_INTERVAL | C_INTERVAL | Result | Observation |
|---|---:|---:|---:|---:|---|---|
| 1 | 1 | 1 | 500 ms | 200 ms | produced=10 consumed=10 | Producer slower; consumer waits for data |
| 2 | 1 | 1 | 200 ms | 500 ms | produced=10 consumed=10 | Consumer slower; producer waits for empty buffer |
| 3 | 1 | 1 | 100 ms | 800 ms | produced=10 consumed=10 | Consumer is bottleneck; execution took ~8 s |
| 4 | 4 | 2 | 500 ms | 100 ms | produced=40 consumed=40 | More interleaving; consumers fast enough |
| 5 | 4 | 2 | 500 ms | 500 ms | produced=40 consumed=40 | Consumers bottleneck; execution took ~10 s |

## Não — este último foi **mais lento**, mas está correto ✅

Comparação:

| Teste                           |          Configuração | Tempo |
| ------------------------------- | --------------------: | ----: |
| 4P / 2C — P: 500 ms / C: 100 ms |     consumers rápidos |  ~5 s |
| 4P / 2C — P: 500 ms / C: 500 ms | consumers mais lentos | ~10 s |

Porquê?

```text
40 items / 2 consumers = 20 items por consumer
20 × 500 ms = 10 000 ms = 10 s
```

Logo, os **consumers** limitaram a velocidade.

---

## Ação — 1 passo 🧭

Regista esta tabela no relatório do **2.3**:

```md
## Exercise 2.3 — Producer-Consumer using Mutex-only Synchronisation

| Test | Producers | Consumers | P_INTERVAL | C_INTERVAL | Result | Observation |
|---|---:|---:|---:|---:|---|---|
| 1 | 1 | 1 | 500 ms | 200 ms | produced=10 consumed=10 | Producer slower; consumer waits for data |
| 2 | 1 | 1 | 200 ms | 500 ms | produced=10 consumed=10 | Consumer slower; producer waits for empty buffer |
| 3 | 1 | 1 | 100 ms | 800 ms | produced=10 consumed=10 | Consumer is bottleneck; execution took ~8 s |
| 4 | 4 | 2 | 500 ms | 100 ms | produced=40 consumed=40 | More interleaving; consumers fast enough |
| 5 | 4 | 2 | 500 ms | 500 ms | produced=40 consumed=40 | Consumers bottleneck; execution took ~10 s |
```

---

## Objetivo

Fechar o **2.3** com evidência experimental:

```text
produced == consumed
```

Isto prova que o protocolo mutex-only funcionou.

---

## Como pensar

O buffer só tem uma posição:

```text
DATA_EMPTY → producer pode escrever
DATA_READY → consumer pode ler
```

O `usleep()` não sincroniza. Ele só reduz polling agressivo.
A sincronização real vem de:

```c
pthread_mutex_lock(&buffer.lock);
...
pthread_mutex_unlock(&buffer.lock);
```

---

## Pitfalls

1. `final_value` não é critério principal.
2. `produced == consumed` é o critério principal.
3. Mais threads não significa sempre mais rápido.
4. Buffer de 1 posição limita throughput.

## Pergunta de decisão

Queres avançar já para **3.1 — Producer-Consumer with Condition Variables**?


## Ação — 1 passo 🧭

Sim: **a 2.3 está resolvida funcionalmente** ✅

Marca no teu `notas.md`:

```md
## LAB2 — Exercise 2.3

Estado: resolvido.

Critério de correção observado:
- 1 producer / 1 consumer: produced=10 consumed=10
- 4 producers / 2 consumers: produced=40 consumed=40
- Não houve deadlock.
- O final_value varia/depende da sequência de offsets e da ordem das threads.
```

## Objetivo

Fechar a 2.3 como exercício implementado e testado.

O que provaste experimentalmente:

```text
items produzidos == items consumidos
```

Logo, o protocolo:

```text
DATA_EMPTY → producer escreve
DATA_READY → consumer lê
```

funcionou.

## Como pensar

A 2.3 não pede ainda eficiência máxima. Pede:

```text
mutex-only synchronisation
polling
back-off com usleep()
```

Tu fizeste isso.

A limitação também ficou clara:

```text
com consumer lento → programa demora mais
com buffer de 1 posição → throughput limitado
com polling → threads acordam várias vezes para testar estado
```

Isto prepara exatamente a próxima secção: **condition variables**.

## Pitfalls & troubleshooting

1. `final_value` não é critério principal.
2. O importante é `produced == consumed`.
3. Não misturar 2.3 com `pthread_cond_wait()`.
4. Mais threads não significa automaticamente mais rápido, porque o buffer só tem uma posição.

## Alternativas / tradeoffs

| Versão                                  | Estado             |
| --------------------------------------- | ------------------ |
| 2.3 mutex-only polling                  | ✅ feita            |
| 3.1 condition variables                 | próximo nível      |
| buffer circular com condition variables | depois             |
| semáforos                               | alternativa futura |

## Pergunta de decisão

Queres agora fazer só uma **conclusão escrita curta da 2.3** para relatório/notebook, sem avançar ainda para código da 3.1?
