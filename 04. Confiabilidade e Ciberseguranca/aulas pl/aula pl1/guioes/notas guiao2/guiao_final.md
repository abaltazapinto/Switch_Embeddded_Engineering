## Guião 2 — OPNsense Firewall em Proxmox

> **Frase-guia para avaliação prática**
> Eu não quero apenas executar comandos. Quero saber explicar o que cada comando prova, que resultado espero, e que conclusão de segurança posso tirar.

---

# 1. Estratégia do guião

| Campo                           | Conteúdo                                                                                                                                                                  |
| ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Objetivo do guião**           | Criar uma firewall OPNsense no Proxmox com duas interfaces: **WAN em `vmbr2`** e **LAN em `vmbr3`**. Depois verificar conectividade IP, scans com `nmap` e resolução DNS. |
| **O que o exercício demonstra** | Demonstra separação entre redes, funcionamento de firewall, DHCP, routing, filtragem de portas e resolução DNS.                                                           |
| **Ideia principal**             | `C1` fica fora da firewall, no lado WAN. `C2` e `C3` ficam dentro da LAN protegida.                                                                                       |
| **Topologia esperada**          | `C1 → vmbr2 → WAN OPNsense → LAN OPNsense → vmbr3 → C2/C3`                                                                                                                |

---

# 2. Topologia final

```text
C1
|
vmbr2  ← lado WAN
|
OPNsense
|
vmbr3  ← lado LAN
|
C2 ---- C3
```

| Máquina        | Bridge  | Função             | IP observado       |
| -------------- | ------- | ------------------ | ------------------ |
| `C1`           | `vmbr2` | Host externo / WAN | `10.42.0.15/24`    |
| `OPNsense WAN` | `vmbr2` | Interface externa  | `10.42.0.227/24`   |
| `OPNsense LAN` | `vmbr3` | Gateway da LAN     | `192.168.1.1/24`   |
| `C2`           | `vmbr3` | Cliente LAN        | `192.168.1.159/24` |
| `C3`           | `vmbr3` | Alvo LAN           | `192.168.1.142/24` |

---

# 3. Checklist do Guião 2

| Secção  | Verificação          | Estado esperado                |
| ------- | -------------------- | ------------------------------ |
| **3.1** | Criar VM OPNsense    | 2 GB RAM, 10 GB disco, 2 cores |
| **3.1** | Interface WAN        | `net0 → vmbr2 → vtnet0`        |
| **3.1** | Interface LAN        | `net1 → vmbr3 → vtnet1`        |
| **3.2** | C1 ligado à WAN      | `C1 → vmbr2`                   |
| **3.2** | C2 ligado à LAN      | `C2 → vmbr3`                   |
| **3.2** | C3 ligado à LAN      | `C3 → vmbr3`                   |
| **3.2** | C2 chega ao C3       | `ping` responde                |
| **3.2** | C2 chega ao C1       | `ping` responde                |
| **3.2** | Scan C2 → C3         | Encontra portas abertas        |
| **3.2** | Scan C1 → Firewall   | Não encontra portas abertas    |
| **3.3** | OPNsense resolve DNS | Nome resolve para IP           |

---

# 4. Comandos usados

## Ver IP das máquinas

```bash
ip -4 addr show eth0
```

### O que prova?

Prova se a máquina recebeu IP na rede certa.

| Máquina | Resultado esperado  |
| ------- | ------------------- |
| `C1`    | IP `10.42.0.x/24`   |
| `C2`    | IP `192.168.1.x/24` |
| `C3`    | IP `192.168.1.x/24` |

### Interpretação

```text
Se C1 tem 10.42.0.x, está no lado WAN.
Se C2/C3 têm 192.168.1.x, estão no lado LAN.
```

---

## Testar conectividade C2 → C3

```bash
ping -c 4 192.168.1.142
```

### Resultado observado

```text
64 bytes from 192.168.1.142
0% packet loss
```

### Interpretação

```text
C2 consegue comunicar com C3.
Ambos estão na mesma LAN vmbr3.
Este tráfego não precisa atravessar a firewall.
```

---

## Testar conectividade C2 → C1

```bash
ping -c 4 10.42.0.15
```

### Resultado esperado

```text
64 bytes from 10.42.0.15
```

### Interpretação

```text
C2 consegue chegar ao C1 através da OPNsense.
Este tráfego atravessa a firewall entre LAN e WAN.
```

---

# 5. Scans Nmap

## Scan SYN de C2 para C3

```bash
nmap -sS -T4 192.168.1.142
```

### Resultado observado

```text
22/tcp open ssh
80/tcp open http
```

### Interpretação

| Porta    | Estado   | Serviço | Significado                        |
| -------- | -------- | ------- | ---------------------------------- |
| `22/tcp` | `open`   | SSH     | C3 aceita ligações SSH             |
| `80/tcp` | `open`   | HTTP    | C3 tem serviço web ativo           |
| Outras   | `closed` | —       | Host respondeu, mas não há serviço |

### Frase para avaliação

```text
O scan SYN (-sS) realizado a partir do C2 ao C3 encontrou as portas 22/tcp e 80/tcp abertas, indicando que o C3 expõe serviços SSH e HTTP na LAN.
```

---

## Scan ACK de C2 para C3

```bash
nmap -sA 192.168.1.142
```

### Resultado observado

```text
1000 unfiltered tcp ports
```

### Interpretação

```text
O C3 respondeu aos pacotes ACK.
Isto sugere que não há filtragem significativa entre C2 e C3.
Como ambos estão na LAN vmbr3, o tráfego não passa pela firewall.
```

### Frase para avaliação

```text
O scan ACK (-sA) ao C3 indicou portas em estado unfiltered, sugerindo ausência de filtragem por firewall entre C2 e C3 dentro da LAN.
```

---

## Scan SYN de C1 para a firewall

```bash
nmap -sS -T4 10.42.0.227
```

### Resultado observado

```text
Host is up
1000 filtered tcp ports
no-response
```

### Interpretação

```text
A firewall existe e está ativa.
No entanto, as portas TCP analisadas aparecem como filtered.
Isto significa que a OPNsense está a bloquear ou ignorar pacotes vindos da WAN.
```

### Frase para avaliação

```text
A partir do C1, o scan SYN à interface WAN da OPNsense mostrou 1000 portas TCP em estado filtered, indicando que a firewall não expõe serviços acessíveis externamente.
```

---

## Scan ACK de C1 para a firewall

```bash
nmap -sA 10.42.0.227
```

### Resultado observado

```text
Host is up
1000 filtered tcp ports
no-response
```

### Interpretação

```text
O scan ACK confirma filtragem na interface WAN.
A firewall não responde aos pacotes testados.
Isto indica comportamento restritivo na entrada pela WAN.
```

### Frase para avaliação

```text
O scan ACK (-sA) à interface WAN da OPNsense indicou portas filtered, sugerindo que a firewall está a filtrar tráfego vindo do lado externo.
```

---

# 6. Diferença entre `-sS` e `-sA`

| Comando             | Pergunta técnica                | Usar para                         |
| ------------------- | ------------------------------- | --------------------------------- |
| `nmap -sS -T4 <IP>` | “Que portas TCP estão abertas?” | Descobrir serviços expostos       |
| `nmap -sA <IP>`     | “Existe filtragem/firewall?”    | Inferir comportamento de firewall |

## Regra mental

```text
-sS → descobre portas abertas
-sA → ajuda a perceber filtragem/firewall
```

---

# 7. Estados importantes do Nmap

| Estado       | Significado                                                                         |
| ------------ | ----------------------------------------------------------------------------------- |
| `open`       | Existe serviço a escutar nessa porta                                                |
| `closed`     | Host respondeu, mas não há serviço nessa porta                                      |
| `filtered`   | Firewall/filtro bloqueou ou ignorou o pacote                                        |
| `unfiltered` | Pacote chegou ao host e houve resposta, mas não indica necessariamente porta aberta |

---

# 8. DNS — Secção 3.3

## Comando usado na OPNsense

```sh
ping -4 docs.opnsense.org
```

### Resultado observado

```text
PING docs.opnsense.org (89.149.225.137)
64 bytes from 89.149.225.137
```

### Interpretação

```text
A OPNsense conseguiu resolver o nome docs.opnsense.org para um endereço IP.
Também conseguiu comunicar com esse IP.
Logo, DNS e conectividade externa estão funcionais.
```

### Frase para avaliação

```text
A OPNsense resolveu o nome docs.opnsense.org para o endereço 89.149.225.137 e recebeu respostas ICMP, confirmando o funcionamento da resolução DNS e da conectividade externa.
```

---

# 9. Erros comuns

| Erro                          | Consequência                                               |
| ----------------------------- | ---------------------------------------------------------- |
| C1 em `vmbr0`                 | C1 fica fora da topologia correta                          |
| C1 em `vmbr3`                 | C1 fica na LAN, quando devia estar na WAN                  |
| C2/C3 em `vmbr2`              | C2/C3 ficam fora da LAN protegida                          |
| IP estático antigo            | Pode ficar numa rede errada                                |
| Esquecer DHCP                 | Máquina pode não receber IP correto                        |
| Escrever `nmap -sS-T4`        | Errado: falta espaço entre `-sS` e `-T4`                   |
| Confundir `filtered` com erro | `filtered` é resultado esperado numa firewall              |
| Testar DNS com IP             | Não testa DNS; DNS exige nome, exemplo `docs.opnsense.org` |

---

# 10. Conclusão final do Guião 2

```text
Foi criada uma firewall OPNsense no Proxmox com WAN ligada à vmbr2 e LAN ligada à vmbr3. O C1 foi colocado no lado WAN e recebeu IP 10.42.0.15/24. O C2 e o C3 foram colocados na LAN e receberam IPs 192.168.1.159/24 e 192.168.1.142/24. O C2 conseguiu comunicar com C3 e C1. O scan SYN do C2 ao C3 identificou as portas 22/tcp e 80/tcp abertas. O scan ACK ao C3 indicou ausência de filtragem relevante na LAN. A partir do C1, os scans à interface WAN da OPNsense não encontraram portas abertas, mostrando 1000 portas filtered. Por fim, a OPNsense conseguiu resolver docs.opnsense.org para um endereço IP, confirmando a operação do DNS.
```

---

# 11. Frase curta para avaliação prática

```text
Neste guião configurei uma firewall OPNsense com duas interfaces, WAN em vmbr2 e LAN em vmbr3. Usei ip addr para validar endereçamento, ping para testar conectividade, nmap -sS para descobrir portas abertas e nmap -sA para inferir filtragem. Concluí que C2 e C3 comunicam dentro da LAN, que o C3 expõe SSH e HTTP, e que a interface WAN da firewall filtra o tráfego vindo do C1.
```
