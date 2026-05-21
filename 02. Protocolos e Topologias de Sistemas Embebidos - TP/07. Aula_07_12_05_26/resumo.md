# TP7 — CAN / CAN-FD — Resumo para guardar no Git

## Respostas do teste

| Pergunta | Resposta       |
| -------- | -------------- |
| 1        | **Falso**      |
| 2        | **Verdadeiro** |
| 3        | **Verdadeiro** |
| 4        | **Falso**      |
| 5        | **Falso**      |
| 6        | **Verdadeiro** |
| 7        | **Verdadeiro** |
| 8        | **Falso**      |
| 9        | **Verdadeiro** |
| 10       | **Falso**      |
| 11       | **Verdadeiro** |
| 12       | **Verdadeiro** |

---

## Conceitos essenciais — CAN clássico

### 1. Tamanho do campo de dados

No **CAN clássico**, o campo de dados transporta no máximo:

```text
8 bytes
```

Mesmo que a trama seja **extended frame**, continua a transportar no máximo **8 bytes**.

A diferença da trama extendida está no tamanho do identificador:

```text
Standard CAN frame: 11-bit identifier
Extended CAN frame: 29-bit identifier
```

Logo:

```text
Extended frame ≠ 64 bytes
```

64 bytes pertencem ao **CAN-FD**.

---

## 2. CAN-FD

O **CAN-FD** permite:

```text
Até 64 bytes no campo de dados
Taxas superiores durante a fase de dados
```

Diferença importante:

```text
CAN clássico: até 8 bytes
CAN-FD: até 64 bytes
```

O CAN-FD pode aumentar a velocidade na **data phase**, depois da fase de arbitragem.

---

## 3. Bit dominante e bit recessivo

No barramento CAN:

```text
Dominante = 0
Recessivo = 1
```

Um bit dominante sobrepõe-se sempre a um bit recessivo.

Ou seja:

```text
0 vence 1
```

Isto é fundamental para a arbitragem.

---

## 4. Arbitragem não destrutiva

O CAN usa **arbitragem não destrutiva** baseada no identificador da trama.

Se vários nós começarem a transmitir ao mesmo tempo, vence a mensagem com maior prioridade.

A trama vencedora **não é destruída** e continua a ser transmitida.

---

## 5. Prioridade dos identificadores

Em CAN:

```text
Identificador numericamente mais baixo = maior prioridade
```

Exemplo:

```text
ID 0x100 tem prioridade maior que ID 0x200
```

Isto acontece porque identificadores menores têm mais bits dominantes `0` nas posições mais significativas.

---

## 6. O identificador CAN não é endereço MAC

O identificador CAN **não serve apenas para identificar o emissor**.

Ele identifica sobretudo:

```text
Tipo de mensagem
Prioridade da mensagem
Conteúdo lógico da comunicação
```

CAN não funciona como Ethernet.

Não existe:

```text
Endereço MAC único obrigatório por dispositivo
```

Em CAN, os nós recebem mensagens e decidem se as aceitam com base no **CAN ID** e filtros.

---

## 7. Retransmissão automática

O protocolo CAN tem mecanismos de deteção de erro.

Quando ocorre erro numa trama:

```text
Os nós sinalizam erro
A trama é invalidada
O controlador CAN tenta retransmitir automaticamente
```

Isto aumenta a robustez do protocolo.

---

## 8. Topologia física

CAN normalmente usa:

```text
Topologia em barramento linear
```

Não usa normalmente estrela.

Forma típica:

```text
[Node]---[Node]---[Node]---[Node]
   |                         |
 terminação              terminação
```

As extremidades do barramento devem ter resistências de terminação, normalmente:

```text
120 Ω + 120 Ω
```

Topologia em estrela pode causar:

```text
Reflexões de sinal
Problemas de integridade elétrica
Erros de comunicação
```

---

## 9. CAN Low-Speed Fault-Tolerant vs CAN High-Speed

O **CAN Low-Speed Fault-Tolerant** foi feito para operar normalmente a velocidades mais baixas que o **CAN High-Speed**.

Comparação:

```text
CAN High-Speed:
- maior velocidade
- usado em sistemas críticos/rápidos
- barramento linear com terminação

CAN Low-Speed Fault-Tolerant:
- menor velocidade
- mais tolerante a falhas
- pode continuar a funcionar mesmo com algumas falhas físicas
```

---

## Frases-chave para exame

```text
CAN clássico suporta até 8 bytes.
CAN-FD suporta até 64 bytes.
Extended frame aumenta o identificador, não o campo de dados.
Dominante = 0.
Recessivo = 1.
Bit dominante vence bit recessivo.
CAN usa arbitragem não destrutiva.
Identificador menor tem maior prioridade.
CAN ID identifica a mensagem/prioridade, não obrigatoriamente o emissor.
CAN não usa endereço MAC.
CAN retransmite automaticamente tramas com erro.
CAN usa normalmente barramento linear, não estrela.
Low-Speed Fault-Tolerant é mais lento que High-Speed CAN.
```

---

## Resumo ultra-curto

```text
CAN clássico: 8 bytes.
CAN-FD: 64 bytes.
Extended CAN: ID de 29 bits, mas continua 8 bytes no clássico.
Dominante 0 vence recessivo 1.
Arbitragem CAN é não destrutiva.
ID menor = maior prioridade.
CAN ID não é MAC address.
CAN retransmite após erro.
CAN usa barramento linear.
CAN Low-Speed Fault-Tolerant é mais lento que CAN High-Speed.
```
