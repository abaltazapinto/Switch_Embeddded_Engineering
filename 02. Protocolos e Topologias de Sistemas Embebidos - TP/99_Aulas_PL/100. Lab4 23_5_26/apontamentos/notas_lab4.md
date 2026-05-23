## Ação (1 passo) 🚀

Preenche a tabela assumindo **apenas conectividade direta entre vizinhos Norte/Sul/Este/Oeste**.

Topologia:

```text
dev0  dev1  dev2  dev3
dev4  dev5  dev6  dev7
dev8  dev9  deva  devb
```

Tabela:

| Origem \ Destino | dev1 | dev2 | dev4 | dev6 | dev7 |
| ---------------- | ---- | ---- | ---- | ---- | ---- |
| **dev0**         | Sim  | Não  | Sim  | Não  | Não  |
| **dev5**         | Sim  | Não  | Sim  | Sim  | Não  |
| **devb**         | Não  | Não  | Não  | Não  | Sim  |

## Objetivo

Provar que, nesta fase inicial do LAB4, os nós só conseguem comunicar com **vizinhos diretos**, porque ainda **não há rotas para nós remotos**.

## Como pensar

Não somes caminhos ainda. Pergunta sempre:

> “O destino está imediatamente acima, abaixo, à esquerda ou à direita da origem?”

Se sim → **ping deve funcionar**.
Se estiver a 2 saltos ou diagonal → **não deve funcionar** nesta fase.

## Pitfalls & troubleshooting ⚠️

* **dev0 → dev2** parece estar na mesma linha, mas não é vizinho direto; há o **dev1 no meio**.
* **dev5 → dev7** também está na mesma linha, mas não é direto; há o **dev6 no meio**.
* **devb → dev6** parece perto, mas é diagonal/indireto; não conta.
* Se um ping direto falhar, verifica primeiro `ip addr show` e depois se estás a usar IPv6 com `ping -6`.

## Alternativas / tradeoffs

Nesta pergunta, podes pensar de duas formas:

1. **Por coordenadas da grelha**: vizinho direto = diferença de 1 posição horizontal ou vertical.
2. **Por conectividade real com ping**: testas cada par e marcas Sim/Não.

## Pergunta de decisão

Queres que passemos já para a **Pergunta 1.2/1.3 com os comandos exatos de ping IPv6 no Kathará**?


---

