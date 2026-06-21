# Guião 1 — Proxmox, Bridges Virtuais, Rede Isolada e SSH

## Objetivo do guião

Este guião demonstra como configurar e validar redes virtuais em Proxmox VE, usando VMs e containers.

O objetivo principal é perceber que uma bridge virtual funciona como um switch virtual e que a conectividade deve ser provada por camadas:

1. interface ativa
2. IP configurado
3. rota/gateway
4. ARP
5. ping
6. DNS
7. serviço aplicacional, neste caso SSH

---

## Arquitetura usada

```txt
Host físico Linux
└── VirtualBox
    └── Proxmox VE
        ├── VM Kali
        ├── CT100
        └── CT101
```

Redes principais:

```txt
vmbr0 -> rede principal / gestão do Proxmox
vmbr2 -> rede de laboratório com acesso ao exterior
vmbr3 -> rede isolada sem Internet
```

---

## 3.2 — Criação da VM Kali na `vmbr2`

| Campo                 | Conteúdo                                                                                                                                                                                                                                        |
| --------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Objetivo do exercício | Criar uma VM Kali ligada à rede de laboratório `vmbr2`, obter IP por DHCP e validar acesso ao exterior por IP e por DNS.                                                                                                                        |
| Comandos usados       | `ip -br addr`, `ip route`, `ip neigh show dev eth0`, `ping -c 3 8.8.8.8`, `ping -c 3 google.com`                                                                                                                                                |
| Resultado observado   | A Kali recebeu IP por DHCP. Inicialmente houve falha de comunicação quando a bridge estava sobre Wi-Fi. Depois, ao usar Ethernet, o ping para `8.8.8.8` e `google.com` funcionou.                                                               |
| Interpretação         | Ter IP por DHCP não prova que a rede está totalmente funcional. É necessário validar ARP, rota, conectividade por IP e DNS. A falha inicial indicava problema de camada 2/ARP devido a bridged networking sobre Wi-Fi em nested virtualization. |
| Erros comuns          | Usar Wi-Fi como bridge no VirtualBox, interface errada, gateway inacessível, DNS não configurado, assumir que DHCP significa Internet funcional.                                                                                                |
| Frase para avaliação  | A VM Kali foi ligada à `vmbr2`, obteve IP por DHCP e o acesso exterior foi validado primeiro por IP com `ping 8.8.8.8` e depois por DNS com `ping google.com`. A falha inicial mostrou que DHCP sozinho não prova conectividade completa.       |

---

## 3.3 — Rede isolada com `vmbr3`

| Campo                 | Conteúdo                                                                                                                                                                                     |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Objetivo do exercício | Criar uma rede isolada usando a bridge `vmbr3` e ligar dois containers à mesma sub-rede sem acesso à Internet.                                                                               |
| Comandos usados       | `ip -br addr`, `ip route`, `ping -c 3 192.168.50.11`, `ping -c 3 8.8.8.8`                                                                                                                    |
| Resultado observado   | O CT100 tinha `192.168.50.10/24` e o CT101 tinha `192.168.50.11/24`. O ping entre CT100 e CT101 funcionou. O ping para `8.8.8.8` falhou com `Network is unreachable`.                        |
| Interpretação         | A comunicação local funciona porque os dois containers estão na mesma sub-rede e ligados à mesma bridge virtual. O acesso à Internet falha porque não existe gateway configurado na `vmbr3`. |
| Erros comuns          | Colocar o IP no campo Gateway, deixar DHCP numa rede sem servidor DHCP, usar `vmbr0` em vez de `vmbr3`, configurar gateway inexistente.                                                      |
| Frase para avaliação  | A `vmbr3` funcionou como uma rede isolada: os containers comunicaram entre si dentro da sub-rede `192.168.50.0/24`, mas não conseguiram sair para a Internet por ausência de gateway.        |

---

## 3.4 — SSH entre containers

| Campo                 | Conteúdo                                                                                                                                                                                                                                                                               |                                                                                                                                                                     |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Objetivo do exercício | Validar comunicação aplicacional entre containers usando SSH, primeiro por password e depois por chave pública/privada.                                                                                                                                                                |                                                                                                                                                                     |
| Comandos usados       | `systemctl is-active ssh`, `ss -tlnp                                                                                                                                                                                                                                                   | grep ':22'`, `ssh root@192.168.50.11`, `passwd root`, `ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""`, `ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.50.11` |
| Resultado observado   | O serviço SSH no CT101 estava ativo. O CT100 conseguiu ligar ao CT101 por SSH. Inicialmente o login root falhou, mas após ajustar a configuração e definir a password, o acesso funcionou. Depois foi configurada autenticação por chave e o login passou a entrar sem pedir password. |                                                                                                                                                                     |
| Interpretação         | O ping prova conectividade IP, mas o SSH prova que existe serviço aplicacional acessível na porta 22 e que a autenticação funciona. A chave privada ficou no CT100 e a chave pública foi copiada para o CT101.                                                                         |                                                                                                                                                                     |
| Erros comuns          | Criar a chave no servidor em vez do cliente, copiar a chave privada, root login bloqueado no SSH, password errada, serviço SSH inativo.                                                                                                                                                |                                                                                                                                                                     |
| Frase para avaliação  | Depois de validar a rede com ping, testei SSH do CT100 para o CT101. Primeiro confirmei acesso por password e depois configurei autenticação por chave pública/privada, mantendo a chave privada no cliente e copiando apenas a chave pública para o servidor.                         |                                                                                                                                                                     |

---

# Comandos importantes e o que provam

| Comando                   | O que prova                                                       |                                                   |
| ------------------------- | ----------------------------------------------------------------- | ------------------------------------------------- |
| `ip -br addr`             | Mostra interfaces e IPs configurados.                             |                                                   |
| `ip -br link`             | Mostra se as interfaces estão UP, DOWN ou UNKNOWN.                |                                                   |
| `ip route`                | Mostra rotas e gateway/default route.                             |                                                   |
| `ip neigh show`           | Mostra ARP/NDP, ou seja, se a máquina descobriu o MAC do destino. |                                                   |
| `ping -c 3 IP`            | Testa conectividade IP até um destino.                            |                                                   |
| `ping -c 3 8.8.8.8`       | Testa acesso ao exterior sem depender de DNS.                     |                                                   |
| `ping -c 3 google.com`    | Testa acesso ao exterior com resolução DNS.                       |                                                   |
| `systemctl is-active ssh` | Verifica se o serviço SSH está ativo.                             |                                                   |
| `ss -tlnp                 | grep ':22'`                                                       | Verifica se há processo à escuta na porta TCP 22. |
| `ssh root@192.168.50.11`  | Testa acesso SSH ao CT101.                                        |                                                   |
| `ssh-keygen -t ed25519`   | Cria par de chaves SSH.                                           |                                                   |
| `ssh-copy-id`             | Copia a chave pública para o servidor.                            |                                                   |

---

# Interpretação por camadas

## Camada 2 — Ethernet / ARP

Pergunta:

```txt
Consigo descobrir o MAC do destino?
```

Comando:

```bash
ip neigh show
```

Se aparecer `FAILED`, o problema pode estar na bridge, na interface física ou no modo de rede do VirtualBox.

---

## Camada 3 — IP / routing

Pergunta:

```txt
Tenho IP, máscara e gateway corretos?
```

Comandos:

```bash
ip -br addr
ip route
```

Exemplo importante:

```txt
Sem gateway -> não há saída para a Internet
```

---

## Camada 4 — Porta TCP

Pergunta:

```txt
O serviço está a escutar na porta correta?
```

Comando:

```bash
ss -tlnp | grep ':22'
```

---

## Camada 7 — Aplicação

Pergunta:

```txt
A aplicação funciona?
```

Exemplo:

```bash
ssh root@192.168.50.11
```

---

# Erros importantes que apareceram no guião

## 1. Confundir IP com gateway

Errado:

```txt
Gateway: 192.168.50.11/24
```

Correto:

```txt
IPv4/CIDR: 192.168.50.11/24
Gateway: vazio
```

## 2. Assumir que DHCP prova Internet

DHCP só prova que a máquina recebeu configuração.
Não prova que ARP, gateway, Internet e DNS funcionam.

## 3. Usar Wi-Fi em bridged nested virtualization

A bridge sobre Wi-Fi pode falhar porque o Wi-Fi nem sempre aceita bem múltiplos MACs atrás de uma VM.

## 4. Login SSH root bloqueado

O serviço SSH pode estar ativo, mas bloquear autenticação root.
Nesse caso, é necessário ajustar a configuração ou usar um utilizador normal.

---

# Checklist final do Guião 1

## Kali na `vmbr2`

```bash
ip -br addr
ip route
ip neigh show dev eth0
ping -c 3 8.8.8.8
ping -c 3 google.com
```

Evidência esperada:

```txt
IP por DHCP
default route presente
ping 8.8.8.8 funciona
ping google.com funciona
```

---

## CT100 e CT101 na `vmbr3`

No CT100:

```bash
ip -br addr
ping -c 3 192.168.50.11
ping -c 3 8.8.8.8
```

Evidência esperada:

```txt
ping 192.168.50.11 funciona
ping 8.8.8.8 falha
```

Conclusão:

```txt
Rede interna funciona.
Internet não funciona porque não há gateway.
```

---

## SSH CT100 para CT101

No CT101:

```bash
systemctl is-active ssh
ss -tlnp | grep ':22'
```

No CT100:

```bash
ssh root@192.168.50.11
```

Evidência esperada:

```txt
root@c2:~#
```

---

## SSH por chave

No CT100:

```bash
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""
ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.50.11
ssh root@192.168.50.11
```

Evidência esperada:

```txt
Login no CT101 sem pedir password.
```

---

# Conclusão do guião

Este guião mostrou que a configuração de rede deve ser validada por evidência, não por suposição. A `vmbr2` foi usada para dar acesso exterior à Kali, enquanto a `vmbr3` foi usada para criar uma rede isolada entre containers. O SSH permitiu validar comunicação aplicacional entre CT100 e CT101, primeiro por password e depois por chave pública/privada.

---

# Frase curta para avaliação prática

Eu configurei redes virtuais em Proxmox usando bridges. A `vmbr2` permitiu acesso exterior à Kali, validado por DHCP, ping por IP e DNS. A `vmbr3` criou uma rede isolada entre CT100 e CT101, onde o ping interno funcionou mas o acesso à Internet falhou por ausência de gateway. Por fim, validei SSH entre containers, primeiro por password e depois por chave pública/privada.
