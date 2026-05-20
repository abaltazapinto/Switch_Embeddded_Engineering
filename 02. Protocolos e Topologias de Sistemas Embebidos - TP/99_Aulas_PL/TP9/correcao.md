## Ação — guardar correção TP9 no Git 🧠

Usa esta tabela como versão corrigida:

| Pergunta | Afirmação resumida                                                   | Resposta correta | A tua resposta | Estado |
| -------: | -------------------------------------------------------------------- | ---------------- | -------------- | ------ |
|        1 | MQTT usa modelo publish/subscribe                                    | **Verdadeiro**   | Verdadeiro     | ✅      |
|        2 | Clientes MQTT publicam diretamente para outros clientes, sem broker  | **Falso**        | Falso          | ✅      |
|        3 | Broker MQTT pode guardar mensagens *retained* para novos subscribers | **Verdadeiro**   | Verdadeiro     | ✅      |
|        4 | QoS 0 garante entrega exatamente uma vez                             | **Falso**        | Falso          | ✅      |
|        5 | Em HTTP/1.1, headers podem ser comprimidos com HPACK                 | **Falso**        | Verdadeiro     | ❌      |
|        6 | Pedidos POST podem usar HTTP/2                                       | **Verdadeiro**   | Verdadeiro     | ✅      |
|        7 | Em HTTP/2, headers são normalmente comprimidos com HPACK             | **Verdadeiro**   | Falso          | ❌      |
|        8 | O elemento `<head>` de HTML é transferido num cabeçalho HTTP         | **Falso**        | Verdadeiro     | ❌      |

## Correções importantes

### Q5 — **Falso**

**HPACK é compressão de headers do HTTP/2**, não do HTTP/1.1.
HTTP/1.1 transmite headers em texto, sem HPACK.

### Q7 — **Verdadeiro**

HTTP/2 usa compressão de cabeçalhos com **HPACK**.

### Q8 — **Falso**

O elemento HTML `<head>` faz parte do **corpo da resposta HTTP**, ou seja, do documento HTML.

Não confundir:

```txt
HTTP headers ≠ HTML <head>
```

Exemplo mental:

```txt
HTTP response
├── HTTP headers
│   ├── Content-Type: text/html
│   └── Content-Length: ...
└── Body
    └── <html>
        ├── <head>...</head>
        └── <body>...</body>
```

## Objetivo

Separar bem três conceitos:

```txt
MQTT → broker, topics, QoS, retained messages
HTTP/2 → HPACK
HTML <head> → conteúdo dentro do body HTTP
```

## Para o teu Git

```md
# TP9 — Correção

1. Verdadeiro — MQTT segue modelo publish/subscribe.
2. Falso — clientes MQTT comunicam através de broker.
3. Verdadeiro — broker pode guardar retained messages.
4. Falso — QoS 0 é at most once, não exactly once.
5. Falso — HPACK é do HTTP/2, não do HTTP/1.1.
6. Verdadeiro — POST pode ser usado em HTTP/2.
7. Verdadeiro — HTTP/2 comprime headers com HPACK.
8. Falso — HTML <head> pertence ao documento HTML, não aos headers HTTP.
```

## Pitfalls

* Confundir **HTTP headers** com a tag HTML **`<head>`**.
* Pensar que MQTT é cliente-cliente direto; na prática passa pelo **broker**.
* Trocar QoS 0 com QoS 2.
* Associar HPACK ao HTTP/1.1 em vez de HTTP/2.

## Pergunta de decisão

Queres que a seguir eu transforme isto numa explicação curta estilo **README.md para o Git**, com secção “conceitos-chave TP9”?
