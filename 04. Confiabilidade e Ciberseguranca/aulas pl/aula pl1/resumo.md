# Confiabilidade e Cibersegurança — Mapa de Conceitos

## Ideia central da cadeira

A disciplina estuda como construir, configurar e avaliar sistemas computacionais que sejam:

* **Disponíveis** — continuam acessíveis quando são necessários.
* **Confiáveis** — comportam-se de forma previsível.
* **Seguros** — protegem sistemas, redes e dados contra uso indevido.
* **Auditáveis** — permitem provar o que foi configurado, testado e validado.

A lógica principal é:

**não basta “funcionar”; é preciso provar que funciona, perceber porque funciona e saber o que falha quando deixa de funcionar.**

---

## Tríade CIA

### Confidencialidade

Só entidades autorizadas conseguem aceder à informação.

Exemplos:

* cifra
* autenticação
* controlo de acessos
* chaves privadas

### Integridade

A informação não é alterada sem deteção.

Exemplos:

* hashes
* assinaturas digitais
* permissões
* logs

### Disponibilidade

O sistema continua acessível e operacional.

Exemplos:

* redundância
* firewalls bem configuradas
* isolamento de falhas
* monitorização

---

## Conceitos base de segurança

### Ativo

Algo com valor que precisa de proteção.

Exemplos:

* servidor
* VM
* container
* rede
* chave privada
* dados

### Ameaça

Algo que pode causar dano.

Exemplos:

* atacante
* malware
* erro humano
* falha de rede
* má configuração

### Vulnerabilidade

Fraqueza explorável.

Exemplos:

* SSH root exposto
* password fraca
* serviço aberto desnecessário
* firewall permissiva

### Risco

Combinação entre probabilidade e impacto.

**Risco = ameaça + vulnerabilidade + impacto**

### Mitigação

Medida para reduzir o risco.

Exemplos:

* firewall
* segmentação de rede
* chaves SSH
* updates
* princípio do menor privilégio

---

## Modelo mental de redes

Uma rede deve ser analisada por camadas.

### Camada 2 — Ethernet / ARP / bridge

Pergunta principal:

**consigo descobrir o MAC do destino?**

Comandos úteis:

```bash
ip neigh show
ip -br link
```

Se aparecer:

```txt
FAILED
```

pode haver problema de ARP, bridge, Wi-Fi bridged ou camada 2.

---

### Camada 3 — IP / routing

Pergunta principal:

**tenho IP, máscara e gateway corretos?**

Comandos úteis:

```bash
ip -br addr
ip route
```

Ter IP não garante Internet. É preciso validar rota e gateway.

---

### Camada 4 — portas / serviços

Pergunta principal:

**a porta do serviço está aberta e acessível?**

Comandos úteis:

```bash
ss -tlnp
nmap
```

Exemplo:

```bash
ss -tlnp | grep ':22'
```

---

### Camada 7 — aplicação

Pergunta principal:

**o serviço funciona ao nível da aplicação?**

Exemplos:

```bash
ssh root@IP
curl http://IP
ping google.com
```

---

## Virtualização e Proxmox

### Hypervisor

Software que permite executar máquinas virtuais.

Exemplo:

* Proxmox VE
* VirtualBox
* VMware
* Hyper-V

### VM

Máquina virtual completa, com kernel próprio.

Exemplo no guião:

* Kali Linux

### Container LXC

Ambiente isolado que partilha o kernel do host.

Exemplo no guião:

* CT100
* CT101

### Bridge virtual

Funciona como um switch virtual.

Exemplos:

* `vmbr0`
* `vmbr2`
* `vmbr3`

---

## Bridges do laboratório

### `vmbr0`

Rede principal de gestão/acesso ao Proxmox.

### `vmbr2`

Rede de laboratório com acesso ao exterior.

Usada para:

* VM Kali
* WAN da firewall OPNsense
* containers com DHCP e Internet

### `vmbr3`

Rede isolada, sem interface física.

Usada para:

* containers internos
* LAN da firewall
* testes sem Internet

Modelo:

```txt
CT100 ---- vmbr3 ---- CT101
              |
              +---- sem acesso exterior
```

---

## Lição importante do Guião 1

### DHCP não prova que a rede está totalmente correta

No laboratório, a Kali recebeu IP por DHCP, mas inicialmente não conseguia comunicar com o gateway.

O problema estava na bridge sobre Wi-Fi.

A solução foi usar Ethernet:

```txt
Wi-Fi bridged     -> ARP falhava
Ethernet bridged  -> ARP funcionou
```

Conclusão:

**validar sempre IP, rota, ARP, gateway, Internet por IP e DNS.**

---

## Firewall e perímetro

### Defesa de perímetro

Conjunto de mecanismos que controlam o tráfego entre redes.

Exemplos:

* firewall
* router de borda
* NAT
* regras inbound/outbound
* segmentação

### Firewall stateless

Analisa pacotes isolados.

Decide com base em:

* IP origem
* IP destino
* protocolo
* porta origem
* porta destino

### Firewall stateful

Guarda estado das ligações.

Sabe distinguir:

* ligação nova
* ligação estabelecida
* resposta legítima
* pacote inesperado

### Regra mental

```txt
Stateless -> olha para pacotes
Stateful  -> olha para conversas
```

---

## NAT

NAT permite que redes privadas comuniquem com redes externas usando tradução de endereços.

Uso típico:

```txt
LAN privada -> firewall/router -> Internet
```

Conceitos importantes:

* rede interna
* rede externa
* gateway
* tradução de IP
* tradução de portas
* controlo de saída

---

## Nmap

Ferramenta usada para descobrir hosts, portas e serviços.

### SYN scan

```bash
nmap -sS -T4 IP
```

Testa portas TCP usando SYN.

Muito usado para descobrir portas abertas, fechadas ou filtradas.

### ACK scan

```bash
nmap -sA IP
```

Ajuda a perceber se existe filtragem/firewall.

Não serve propriamente para descobrir serviços abertos; serve para inferir regras de firewall.

---

## Criptografia

### Cifra simétrica

Mesma chave para cifrar e decifrar.

Exemplo:

* AES

Vantagem:

* rápida
* eficiente

Problema:

* como partilhar a chave em segurança?

---

### Cifra assimétrica

Usa par de chaves:

```txt
chave pública
chave privada
```

Exemplos:

* RSA
* ECC
* Ed25519

Usos:

* SSH
* TLS/HTTPS
* assinaturas digitais
* troca segura de chaves

---

## SSH por chave

No SSH:

```txt
cliente tem chave privada
servidor tem chave pública autorizada
```

No guião:

```txt
CT100 = cliente SSH
CT101 = servidor SSH
```

Fluxo:

```txt
CT100 gera chave privada/pública
CT100 copia chave pública para CT101
CT100 entra no CT101 sem password
```

Comandos-chave:

```bash
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""
ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.50.11
ssh root@192.168.50.11
```

Regra de segurança:

**a chave privada nunca deve ser copiada para o servidor.**

---

## TLS / HTTPS

TLS usa os dois tipos de criptografia:

1. criptografia assimétrica no handshake
2. criptografia simétrica para a sessão

Razão:

* assimétrica é boa para autenticação e troca inicial
* simétrica é melhor para velocidade

---

## Diagnóstico essencial

Ordem recomendada de teste:

```txt
1. Tenho interface UP?
2. Tenho IP?
3. Tenho rota?
4. Tenho ARP para o gateway?
5. Consigo pingar gateway?
6. Consigo pingar 8.8.8.8?
7. Consigo resolver DNS?
8. O serviço está ativo?
9. A autenticação funciona?
```

Comandos:

```bash
ip -br link
ip -br addr
ip route
ip neigh show
ping -c 3 gateway
ping -c 3 8.8.8.8
ping -c 3 google.com
ss -tlnp
ssh user@IP
```

---

## Erros comuns

### Confundir IP com gateway

Errado:

```txt
Gateway: 192.168.50.11/24
```

Correto:

```txt
IPv4/CIDR: 192.168.50.11/24
Gateway: vazio
```

### Pensar que DHCP prova tudo

DHCP só prova que recebeste configuração.
Não prova ARP, routing, DNS ou Internet.

### Usar Wi-Fi para nested bridged networking

Pode falhar por causa de múltiplos MACs atrás da bridge.

### Expor SSH root

Aceitável em laboratório controlado.
Má prática em produção.

---

## Princípios para memorizar

* Segmentar redes reduz impacto.
* Bridge virtual funciona como switch.
* Sem gateway não há saída para outras redes.
* Firewall controla fronteiras entre redes.
* NAT traduz endereços entre redes.
* Nmap ajuda a observar a superfície de ataque.
* Chave privada fica sempre no cliente.
* Segurança deve ser testada por evidência, não por suposição.

---

## Frase-chave da cadeira

**Confiabilidade e cibersegurança exigem arquitetura, isolamento, controlo, validação e evidência.**
