# Resumo — NAT, IPv4, IPv6, OSI e Kathará 🚀

## 1. Conceitos principais aprendidos

### Layering / Modelo em Camadas

A comunicação é dividida em camadas para reduzir complexidade. 

Exemplo:

```text
Application
↓
OS
↓
BIOS
↓
Hardware
```

No networking:

```text
Application
Transport
Network
Data Link
Physical
```

---

# 2. Modelo OSI

| Layer | Nome         | Função               |
| ----- | ------------ | -------------------- |
| 7     | Application  | aplicações           |
| 6     | Presentation | encoding/encriptação |
| 5     | Session      | sessões              |
| 4     | Transport    | TCP/UDP              |
| 3     | Network      | IP/routing           |
| 2     | Data Link    | frames               |
| 1     | Physical     | sinais físicos       |

Mnemonic:

```text
Please Do Not Throw Sausage Pizza Away
```



---

# 3. Modelo TCP/IP

```text
Application
Transport
Network
Physical + DLL
```

Protocolos:

* TCP
* UDP
* IP
* Ethernet
* ICMP
* ARP



---

# 4. Encapsulamento

Cada camada adiciona um header:

```text
Dados
↓
TCP Header
↓
IP Header
↓
Ethernet Header
```

Muito importante:

* encapsulamento
* desmultiplexagem

---

# 5. IPv4

IPv4:

* 32 bits
* dotted decimal notation

Exemplo:

```text
193.136.63.5
10.0.1.133
```

Número total:



---

# 6. Endereços especiais IPv4

| Endereço    | Significado    |
| ----------- | -------------- |
| 0.0.0.0     | máquina sem IP |
| 127.x.x.x   | loopback       |
| ff.ff.ff.ff | broadcast      |
| 0.x.x.x     | rede local     |

---

# 7. Máscaras e CIDR

Exemplo:

```text
192.168.1.0/24
```

`/24`:

* 24 bits rede
* 8 bits hosts

Hosts possíveis:

Máscara equivalente:

```text
255.255.255.0
```

---

# 8. NAT

NAT:

```text
Network Address Translation
```

Objetivo:

* permitir redes privadas acederem à Internet

Endereços privados:

* 10.x.x.x
* 172.16.x.x
* 192.168.x.x



---

# 9. Funcionamento NAT

Antes:

```text
10.0.1.2 → Internet
```

Depois NAT:

```text
128.143.71.21 → Internet
```

O router:

* troca IP privado por IP público
* mantém tabela de tradução

---

# 10. NAPT

NAPT:

```text
NAT + Port Translation
```

Permite:

* muitos hosts
* um único IP público

Usa:

* portas TCP/UDP

Exemplo:

```text
10.0.1.2:2001
↓
128.143.71.21:2100
```

---

# 11. Port Forwarding

Encaminhar portas externas para máquinas internas.

Exemplo:

```bash
iptables -t nat -A PREROUTING \
-p tcp --dport 81 \
-j DNAT --to-destination 10.0.1.2:80
```

Significa:

```text
porta 81 externa → servidor interno porta 80
```

---

# 12. Kathará

Kathará:

* simulador de redes Linux
* routers virtuais
* redes IPv4/IPv6
* usado nas TPs

Comandos importantes:

```bash
kathara lstart
kathara lstop
kathara connect ra
```

---

# 13. Comandos Linux importantes

## Ver IPs

```bash
ip addr show
```

## Ver rotas

```bash
route -n
```

## Adicionar rota default

```bash
route add default gw X.X.X.X
```

## Testar conectividade

```bash
ping IP
```

## Capturar tráfego

```bash
tcpdump
```

Exemplo:

```bash
tcpdump -i eth0
```

---

# 14. NAT com iptables

Ativar NAT:

```bash
iptables -t nat -A POSTROUTING \
-o eth1 -j MASQUERADE
```

Significado:

* traduz IPs saída
* masquerade automático

Muito usado:

* routers Linux
* Raspberry Pi
* gateways



---

# 15. IPv6

IPv6:

* 128 bits
* hexadecimal

Exemplo:

```text
2001:DF8:101::E0:F796:4F31
```

Número de endereços:



---

# 16. Características IPv6

✔ sem broadcast
✔ multicast
✔ anycast
✔ cabeçalho simplificado
✔ melhor routing
✔ enorme espaço de endereçamento

---

# 17. SLAAC

```text
Stateless Address Auto Configuration
```

Objetivo:

* máquina configura-se sozinha

Usa:

* Router Advertisement
* EUI-64
* ICMPv6

---

# 18. Link-local IPv6

Prefixo:

```text
FE80::/10
```

Só funciona:

* dentro da rede local

Teste:

```bash
ping FE80::xxxx%eth0
```

---

# 19. Router Advertisement (RA)

Router envia:

* prefixo IPv6
* default gateway

Daemon Linux:

```bash
radvd
```

Ficheiro:

```bash
/etc/radvd.conf
```



---

# 20. Router Solicitation (RS)

Máquina pergunta:

```text
"Existe algum router IPv6?"
```

Usa:

* ICMPv6
* multicast

---

# 21. Mental Models Importantes 🧠

## NAT

```text
porteiro do prédio
```

## Routing

```text
GPS dos pacotes
```

## Encapsulamento

```text
caixas dentro de caixas
```

## OSI

```text
dividir complexidade
```

---

# 22. O que provavelmente sai no exame ⚠️

Muito provável:

* OSI layers
* TCP/IP
* encapsulamento
* IPv4
* máscaras
* CIDR
* NAT
* NAPT
* port forwarding
* IPv6
* SLAAC
* Router Advertisement
* ICMPv6
* diferenças IPv4 vs IPv6

---

# 23. Relação com Embedded Systems 🔧

Tudo isto liga diretamente a:

* Raspberry Pi gateways
* IoT
* sensores distribuídos
* CAN gateways
* routers embedded Linux
* MQTT
* edge devices
* automotive networking



---

# 24. Livros extremamente alinhados contigo 📚

## Muito recomendados

### Making Embedded Systems

Excelente para:

* debugging
* embedded Linux
* constraints
* embedded mindset



---

### Code: The Hidden Language of Computer Hardware and Software

Excelente para:

* entender computadores do zero
* lógica digital
* redes
* bits
* CPU thinking



---

### Digital Design and Computer Architecture

Excelente para:

* arquitetura
* ARM
* lógica
* memória
* buses
* embedded systems



---

### Computer Organization and Design Fundamentals

Excelente base:

* hardware/software interface
* protocolos
* memória
* interrupções
* buses

