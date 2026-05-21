## Ação — 1 passo

Estuda esta disciplina como **uma cadeia de comunicação entre sistemas embebidos**, não como tópicos isolados:

```text
Dispositivo embebido
→ interface física / barramento
→ protocolo de comunicação
→ endereçamento
→ encaminhamento
→ aplicação distribuída
```

---

# Objetivo

Saber responder a perguntas do tipo:

> “Como é que dois nós embebidos comunicam, como são endereçados, que protocolo usam, que camada resolve cada problema, e como valido isso experimentalmente?”

A disciplina cobre **modelos de referência, IP, topologias, Ethernet, SENT, LIN, APIX, redes mesh, MQTT, CAN, TTP, Byteflight, FlexRay, MOST e Bluetooth** . A avaliação combina trabalhos práticos, exercícios TP e exame final .

---

# 1. Ideia central da disciplina

## Sistemas embebidos em rede

Um sistema embebido não é só “um microcontrolador”. É normalmente:

```text
sensor / atuador
+ eletrónica
+ sistema computacional
+ comunicação com outros nós
```

Nos slides da cadeira, o sistema embebido aparece ligado ao **mundo real** por sensores e atuadores, e em contexto IoT aparece ligado a uma **rede global** .

O raciocínio base é:

```text
O nó mede ou atua
→ transforma isso em dados
→ comunica com outro nó
→ outro nó interpreta
→ sistema global toma decisão
```

---

# 2. Modelos de referência: OSI e TCP/IP

## OSI

Tens de saber as 7 camadas:

| Camada             | Função principal                   |
| ------------------ | ---------------------------------- |
| 7 Aplicação        | Serviços para aplicações           |
| 6 Apresentação     | Formato, codificação, encriptação  |
| 5 Sessão           | Gestão da sessão                   |
| 4 Transporte       | Comunicação fim-a-fim, fiabilidade |
| 3 Rede             | Endereçamento lógico e routing     |
| 2 Ligação de dados | Frames, MAC, acesso ao meio        |
| 1 Física           | Sinais elétricos, óticos ou rádio  |

O modelo OSI serve como **referência conceptual** para explicar comunicação entre nós e interoperabilidade entre fabricantes .

## TCP/IP

No modelo TCP/IP da cadeira:

```text
Aplicação
Transporte
Rede
Físico + Data Link
```

O IP fica na camada de **rede** e TCP/UDP na camada de **transporte** .

---

# 3. IP: o que tens de dominar

## IPv4

Saber:

```text
endereço IP
máscara
prefixo CIDR
rede
host
gateway
rota por omissão
broadcast
loopback
```

Exemplo:

```text
203.0.114.1/24
```

significa:

```text
rede: 203.0.114.0
máscara: 255.255.255.0
host: .1
broadcast: 203.0.114.255
```

O IP é um protocolo de **camada de rede** que transfere datagramas entre origem e destino, sem garantia de entrega, sem circuito virtual, podendo haver caminhos diferentes, duplicação ou chegada fora de ordem .

## CIDR

Tens de calcular rapidamente:

```text
/24 → 256 endereços totais
/25 → 128
/26 → 64
/27 → 32
/28 → 16
/29 → 8
/30 → 4
```

Regra:

```text
nº endereços = 2^(32 - prefixo)
```

---

# 4. Routing

Um nó comunica diretamente se está na mesma rede.

Se o destino está fora da rede local:

```text
envia para o gateway
```

O gateway é normalmente o router local.

Exemplo:

```bash
route add -net 0.0.0.0/0 gw 203.0.114.254
```

significa:

```text
para qualquer destino desconhecido → envia para 203.0.114.254
```

Pitfall clássico:

```text
Ping falha ≠ IP errado sempre.
Pode faltar rota, gateway, NAT, forwarding ou firewall.
```

---

# 5. NAT e NAPT

## NAT

NAT altera endereços IP no cabeçalho dos pacotes. Serve para ligar redes privadas a redes públicas. Os slides definem NAT como a funcionalidade que substitui endereços IP à entrada ou saída de uma rede privada, permitindo comunicação transparente com a rede externa .

## NAPT / Masquerading

NAPT faz tradução de:

```text
IP + porto
```

Permite vários hosts privados usarem um só IP público.

Comando típico dos labs:

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

Interpretação:

```text
quando sair por eth1, traduz o endereço de origem
```

---

# 6. IPv6

## Estrutura

IPv6 tem **128 bits**, representados em hexadecimal por grupos de 16 bits separados por `:`. Zeros à esquerda podem ser omitidos e `::` substitui grupos de zeros .

Exemplo:

```text
2023:3:27:a:88b5:1fff:fe2d:314b
```

## Tipos importantes

| Tipo           | Exemplo              | Função                    |
| -------------- | -------------------- | ------------------------- |
| Global unicast | `2023:3:27:a::/64`   | Endereço roteável         |
| Link-local     | `fe80::/10`          | Comunicação local no link |
| Loopback       | `::1`                | Próprio nó                |
| Multicast      | `ff02::1`, `ff02::2` | Grupos de nós             |

Os slides indicam `FF02::1` como **All Nodes** e `FF02::2` como **All Routers** .

---

# 7. EUI-64 e SLAAC

## EUI-64

Transformação MAC → identificador IPv6 de 64 bits:

```text
MAC: 8a:b5:1f:2d:31:4b
```

1. Divide:

```text
8a:b5:1f    2d:31:4b
```

2. Insere `ff:fe`:

```text
8a:b5:1f:ff:fe:2d:31:4b
```

3. Inverte o bit U/L do primeiro byte:

```text
8a XOR 02 = 88
```

4. Resultado:

```text
88b5:1fff:fe2d:314b
```

## SLAAC

SLAAC = **Stateless Address Auto Configuration**.

O endereço é:

```text
prefixo anunciado pelo router + EUI-64
```

O lab diz que em IPv6 uma máquina pode autoconfigurar-se usando um prefixo de 64 bits obtido de um router e um identificador EUI-64 calculado localmente a partir do MAC; isso usa Router Advertisement e Router Solicitation via NDP .

Exemplo:

```text
prefixo: 2023:3:27:a::/64
EUI-64:  88b5:1fff:fe2d:314b
IPv6:    2023:3:27:a:88b5:1fff:fe2d:314b
```

---

# 8. NDP: RS e RA

## Router Solicitation — RS

Host pergunta:

```text
Há routers neste link?
```

Destino típico:

```text
ff02::2 = All Routers
```

Fluxo:

```text
host → ff02::2
```

## Router Advertisement — RA

Router anuncia:

```text
prefixo
gateway
flags de autoconfiguração
```

Destino típico:

```text
ff02::1 = All Nodes
```

Fluxo:

```text
router → ff02::1
```

No lab, o `radvd` é usado para gerar Router Advertisements; o ficheiro `/etc/radvd.conf` define o prefixo anunciado .

---

# 9. Kathará e validação experimental

Tens de saber usar:

```bash
kathara lstart
kathara lclean
ip addr show
ifconfig
route -n
ip -6 route
ping
ping -6
tcpdump
radvd -c
systemctl start radvd
./kathara-get rb -F /etc/radvd.conf
```

O raciocínio experimental é sempre:

```text
1. Ver endereços
2. Ver rotas
3. Testar ping local
4. Testar ping remoto
5. Capturar tráfego
6. Interpretar origem, destino e protocolo
```

---

# 10. Protocolos automóveis / industriais

Ainda que nem todos tenham sido trabalhados ao mesmo nível nos labs, tens de saber comparar:

| Protocolo  | Ideia principal                                            |
| ---------- | ---------------------------------------------------------- |
| CAN        | Barramento robusto, arbitration por ID, comum em automóvel |
| LIN        | Simples, barato, master-slave, baixa velocidade            |
| FlexRay    | Determinístico, tolerante a falhas, automóvel crítico      |
| MOST       | Multimédia automóvel                                       |
| TTP        | Time-triggered, determinístico                             |
| Byteflight | Comunicação automóvel orientada a segurança                |
| SENT       | Sensor → ECU, unidirecional, baixo custo                   |
| MQTT       | Publish/subscribe, IoT                                     |
| Bluetooth  | Comunicação sem fios curta distância                       |
| Mesh       | Nós encaminham tráfego entre si                            |

---

# O que deves saber “bem mesmo”

## Essencial para exame e TP

```text
OSI vs TCP/IP
camada física / ligação / rede / transporte
IPv4: rede, máscara, gateway, rota
CIDR: calcular redes e hosts
NAT/NAPT: o que muda no pacote
IPv6: global, link-local, multicast
ff02::1 e ff02::2
EUI-64 a partir de MAC
SLAAC = prefixo + EUI-64
RS vs RA
radvd.conf
tcpdump: origem > destino
Kathará: iniciar, testar, guardar ficheiros
CAN/LIN/FlexRay/MQTT: diferenças de uso
```

---

# 10 perguntas de escolha múltipla

## 1. No modelo OSI, qual camada trata do encaminhamento entre redes?

A. Física
B. Ligação de dados
C. Rede
D. Aplicação

---

## 2. Qual é a função principal de uma rota por omissão?

A. Enviar tráfego para o loopback
B. Definir o endereço MAC local
C. Encaminhar tráfego cujo destino não tem rota mais específica
D. Ativar NAT automaticamente

---

## 3. Em IPv6, o endereço `fe80::/10` é usado para:

A. Comunicação global na Internet
B. Comunicação local no mesmo link
C. Broadcast IPv6
D. NAT externo

---

## 4. Qual é o significado de `ff02::2`?

A. All Nodes
B. All Routers
C. Loopback
D. Unspecified address

---

## 5. Numa mensagem Router Solicitation, o destino típico é:

A. `::1`
B. `ff02::1`
C. `ff02::2`
D. `2023:3:27::99`

---

## 6. Numa mensagem Router Advertisement, normalmente o router anuncia:

A. Apenas o endereço MAC do switch
B. Prefixo IPv6 e informação de gateway
C. Apenas portas TCP abertas
D. Apenas o endereço IPv4 privado

---

## 7. O endereço IPv6 global por SLAAC é formado por:

A. Prefixo de 32 bits + porta TCP
B. Endereço IPv4 + MAC
C. Prefixo de 64 bits + identificador de interface de 64 bits
D. Gateway + broadcast

---

## 8. Em NAT masquerading, o comando `POSTROUTING -o eth1 -j MASQUERADE` significa:

A. Traduzir pacotes que saem por `eth1`
B. Bloquear pacotes que entram por `eth1`
C. Criar endereço IPv6 link-local
D. Ativar Router Advertisement

---

## 9. O protocolo CAN é especialmente conhecido por:

A. Ser usado apenas para páginas web
B. Usar broadcast IPv4
C. Arbitration por identificador e robustez em ambientes automóveis
D. Substituir completamente o IP

---

## 10. Num `tcpdump`, uma linha como:

```text
IP6 fe80::abcd > ff02::2: ICMP6, router solicitation
```

significa:

A. Um router anunciou um prefixo para todos os nós
B. Um host pediu informação aos routers do link
C. Um pacote TCP foi enviado para a Internet
D. Um NAT traduziu um endereço privado

---

# Soluções

```text
1. C
2. C
3. B
4. B
5. C
6. B
7. C
8. A
9. C
10. B
```

---

## Pitfalls & troubleshooting

* Confundir `ff02::1` com `ff02::2`: **All Nodes** vs **All Routers**.
* Usar `fe80::...` como se fosse endereço global: link-local não atravessa routers.
* Esquecer que `ping` falhar pode ser problema de rota, não de endereço.
* Em EUI-64, esquecer o `ff:fe` ou não inverter o bit U/L.

## Alternativas / tradeoffs

Para estudar, tens duas abordagens:

| Abordagem              | Vantagem                       | Risco                             |
| ---------------------- | ------------------------------ | --------------------------------- |
| Por camadas OSI/TCP-IP | Organiza o raciocínio          | Pode ficar abstrato               |
| Por labs Kathará       | Fixa comandos e sintomas reais | Pode virar “receita” sem conceito |

Melhor estratégia: **estudar conceito → validar no Kathará → escrever o que observaste**.

## Pergunta de decisão

Queres que eu faça agora uma **folha-resumo de 1 página para imprimir/escrever à mão antes do exame**?
