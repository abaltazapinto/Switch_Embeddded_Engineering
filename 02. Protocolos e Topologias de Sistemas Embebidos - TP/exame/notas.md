Como pensar

Para qualquer exercício:

bloco = 2^(32 - prefixo)

rede = maior múltiplo do bloco ≤ último octeto

broadcast = rede + bloco - 1

primeiro host = rede + 1

último host = broadcast - 1



---

## Correção ✅

Está **certo**.

Para:

```text
172.16.5.174/27
```

`/27` → bloco de **32**:

```text
0–31
32–63
64–95
96–127
128–159
160–191  ← 174 cai aqui
192–223
224–255
```

Logo:

```text
rede / broadcast / primeiro host / último host
160 / 191 / 161 / 190
```

## Ação — 1 passo

Agora faz este:

```text
192.168.20.89/26
```

`/26` dá bloco de **64**.

Formato:

```text
rede / broadcast / primeiro host / último host
```

Só os últimos octetos.

## Objetivo

Confirmar se consegues aplicar a mesma lógica com bloco maior.

---

## Correção ✅

Está **certo**.

Para:

```text
192.168.20.89/26
```

`/26` → bloco de **64**:

```text
0–63
64–127  ← 89 cai aqui
128–191
192–255
```

Logo:

```text
rede / broadcast / primeiro host / último host
64 / 127 / 65 / 126
```

## Ação — 1 passo

Faz este agora:

```text
10.10.3.222/28
```

`/28` dá bloco de **16**.

Formato:

```text
rede / broadcast / primeiro host / último host
```

Só os últimos octetos.


---

## Correção ✅

Está **certo**.

Para:

```text
192.168.50.200/29
```

`/29` → bloco de **8**:

```text
192–199
200–207  ← 200 cai aqui
208–215
```

Logo:

```text
rede / broadcast / primeiro host / último host
200 / 207 / 201 / 206
```

⚠️ Nota importante: aqui o IP dado `200` é exatamente o **endereço de rede**, portanto **não é host válido**.

## Ação — 1 passo

Agora responde só:

Para `192.168.50.200/29`, o endereço `192.168.50.200` pode ser atribuído a uma máquina?

A. Sim
B. Não
