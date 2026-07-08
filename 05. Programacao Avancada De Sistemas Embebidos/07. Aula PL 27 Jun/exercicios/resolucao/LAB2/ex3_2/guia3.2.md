| Fase                  | Protegida por mutex? | Porquê                     |
| --------------------- | -------------------: | -------------------------- |
| Criar `sample` local  |                    ❌ | só esta thread usa         |
| Inserir no buffer     |                    ✅ | buffer é partilhado        |
| Dormir aleatoriamente |                    ❌ | não deve bloquear o buffer |


samples[]
count
write_idx
condition variables

## Ação — 1 passo 🧭

Sim ✅

Depois do **consumer** consumir uma sample e fazer:

```c
buffer.count--;
```

ele deve sinalizar:

```c
pthread_cond_signal(&buffer.buffer_can_write);
```

## Objetivo

Avisar os producers:

```text
há espaço livre no buffer
podem tentar escrever
```

## Como pensar

O consumer faz isto:

```text
remove uma sample
count diminui
buffer deixa de estar cheio
```

Logo, ele tornou verdadeira esta condição:

```text
buffer can write
```

Então sinaliza:

```c
buffer_can_write
```

Tabela final:

| Thread   | Quando bloqueia | Wait               | Depois de agir  | Signal             |
| -------- | --------------- | ------------------ | --------------- | ------------------ |
| Producer | buffer cheio    | `buffer_can_write` | escreveu sample | `buffer_can_read`  |
| Consumer | buffer vazio    | `buffer_can_read`  | consumiu sample | `buffer_can_write` |

## Pitfalls & troubleshooting

1. `wait` é aquilo que a thread precisa.
2. `signal` é aquilo que a thread acabou de tornar possível.
3. Producer não sinaliza `buffer_can_write`.
4. Consumer não sinaliza `buffer_can_read`.

## Alternativas / tradeoffs

| Função                     | Quando usar                   |
| -------------------------- | ----------------------------- |
| `pthread_cond_signal()`    | acordar uma thread            |
| `pthread_cond_broadcast()` | acordar várias threads        |
| Aqui                       | `signal()` chega para começar |

## Pergunta de decisão

Queres agora tentar escrever sozinho o bloco crítico do `producer()` com estas quatro linhas: escrever sample, avançar `write_idx`, fazer `count++`, sinalizar `buffer_can_read`?
## Ação — 1 passo 🧭

Sim ✅

Depois do **consumer** consumir uma sample e fazer:

```c
buffer.count--;
```

ele deve sinalizar:

```c
pthread_cond_signal(&buffer.buffer_can_write);
```

## Objetivo

Avisar os producers:

```text
há espaço livre no buffer
podem tentar escrever
```

## Como pensar

O consumer faz isto:

```text
remove uma sample
count diminui
buffer deixa de estar cheio
```

Logo, ele tornou verdadeira esta condição:

```text
buffer can write
```

Então sinaliza:

```c
buffer_can_write
```

Tabela final:

| Thread   | Quando bloqueia | Wait               | Depois de agir  | Signal             |
| -------- | --------------- | ------------------ | --------------- | ------------------ |
| Producer | buffer cheio    | `buffer_can_write` | escreveu sample | `buffer_can_read`  |
| Consumer | buffer vazio    | `buffer_can_read`  | consumiu sample | `buffer_can_write` |

## Pitfalls & troubleshooting

1. `wait` é aquilo que a thread precisa.
2. `signal` é aquilo que a thread acabou de tornar possível.
3. Producer não sinaliza `buffer_can_write`.
4. Consumer não sinaliza `buffer_can_read`.

## Alternativas / tradeoffs

| Função                     | Quando usar                   |
| -------------------------- | ----------------------------- |
| `pthread_cond_signal()`    | acordar uma thread            |
| `pthread_cond_broadcast()` | acordar várias threads        |
| Aqui                       | `signal()` chega para começar |

## Pergunta de decisão

Queres agora tentar escrever sozinho o bloco crítico do `producer()` com estas quatro linhas: escrever sample, avançar `write_idx`, fazer `count++`, sinalizar `buffer_can_read`?


---

# OSTEP

![alt text](image.png)

