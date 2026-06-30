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
