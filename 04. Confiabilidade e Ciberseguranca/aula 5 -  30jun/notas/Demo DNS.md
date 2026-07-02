# Demo DNS — Pi-hole no Raspberry Pi 5 via Tailscale

## Topologia

Portátil no ISEP
    ↓ Tailscale
Raspberry Pi 5 — 100.70.175.106
    ↓ Pi-hole DNS
Quad9 / blocklists

## Teste 1 — DNS permitido

```bash
dig @100.70.175.106 google.com +short


dig @100.70.175.106 doubleclick.net +short


###

Frase para avaliação prática

Nesta etapa estou a demonstrar filtragem DNS usando um Pi-hole num Raspberry Pi 5.
O google.com resolve normalmente, provando que o DNS funciona.
O doubleclick.net devolve 0.0.0.0, provando que a política de bloqueio está ativa.
Como o acesso é feito por Tailscale, consigo demonstrar isto fora de casa sem expor a porta 53 à Internet pública.

## Objetivo

Ficas com uma evidência limpa: **comando → resultado → interpretação → segurança**. É exatamente o tipo de raciocínio pedido para os guiões: não apenas executar comandos, mas explicar o que cada comando prova. :contentReference[oaicite:0]{index=0}

## Como pensar

O essencial é esta diferença:

```text
google.com
→ permitido
→ devolve IP público

doubleclick.net
→ bloqueado
→ devolve 0.0.0.0

---

Objetivo

Confirmar se o Proxmox está a usar o teu Pi-hole como DNS.

Tu tens DNS server no Raspberry, não “dentro do Proxmox”.
O Proxmox só usa esse DNS se o ficheiro mostrar algo como:

nameserver 192.168.1.21

ou, via Tailscale:

nameserver 100.70.175.106
Como pensar

Há duas coisas diferentes:

Pi-hole no Raspberry = servidor DNS criado
Proxmox usar Pi-hole = cliente DNS configurado

Neste momento já provaste:

Raspberry Pi-hole LAN:       192.168.1.21
Raspberry Pi-hole Tailscale: 100.70.175.106

Mas ainda falta provar se o Proxmox está a perguntar a ele.

Para a cadeira, a frase certa é:

Ter um servidor DNS funcional não significa que todos os clientes o estejam a usar. Cada cliente precisa de ter esse DNS configurado ou recebido via DHCP.

Isto encaixa diretamente no objetivo dos guiões: distinguir execução, resultado e interpretação de segurança.

---
Ainda não. O Proxmox está a usar DNS público:

nameserver 1.1.1.1
nameserver 8.8.8.8

---

Nesta etapa estou a testar se o Proxmox consegue usar o Pi-hole como servidor DNS externo.
O dig @192.168.1.21 google.com devolveu um IP, logo há conectividade DNS entre Proxmox e Raspberry.
No entanto, o Proxmox ainda não usa esse DNS por defeito, porque o /etc/resolv.conf aponta para 1.1.1.1 e 8.8.8.8.

---

super importante

#   cat /etc/resolv.conf


---

Mas o Proxmox ainda não usa o Pi-hole por defeito, porque o /etc/resolv.conf ainda tem:

nameserver 1.1.1.1
nameserver 8.8.8.8

Portanto tens duas provas diferentes:

Teste	O que prova
dig @192.168.1.21 google.com	Proxmox consegue resolver através do Pi-hole
dig @192.168.1.21 doubleclick.net	Proxmox consegue receber bloqueio DNS do Pi-hole
Query count sobe 24 → 25	A query passou mesmo pelo Pi-hole
/etc/resolv.conf com 1.1.1.1/8.8.8.8	Proxmox ainda não usa Pi-hole por defeito

Isto é boa evidência para a cadeira: comando → resultado → interpretação → segurança.

---

O Proxmox conseguia consultar o Pi-hole manualmente, mas ainda não o usava como DNS por defeito. Ao alterar a configuração DNS do host, passo a centralizar também as queries do Proxmox no Pi-hole, permitindo observação e filtragem DNS.

---

## Ação — 1 passo

Guarda esta sequência no teu relatório/notas:

```bash
cat /etc/resolv.conf
dig google.com +short
dig doubleclick.net +short
```

Com os teus resultados:

```text
nameserver 192.168.1.21

google.com
→ 172.217.171.46

doubleclick.net
→ 0.0.0.0
```

## Objetivo

Agora está **confirmado**:

```text
Proxmox → Pi-hole no Raspberry → DNS / bloqueio
```

O Proxmox já não está a usar:

```text
1.1.1.1
8.8.8.8
```

Está a usar:

```text
192.168.1.21
```

## Como pensar

Tens três provas fortes:

| Prova                                          | Significado                          |
| ---------------------------------------------- | ------------------------------------ |
| `cat /etc/resolv.conf` mostra `192.168.1.21`   | Proxmox usa Pi-hole como DNS default |
| `dig google.com +short` devolve IP público     | DNS normal funciona                  |
| `dig doubleclick.net +short` devolve `0.0.0.0` | Pi-hole bloqueia por política DNS    |

Frase para avaliação:

> Configurei o Proxmox para usar o Raspberry Pi com Pi-hole como servidor DNS. O domínio `google.com` resolve normalmente, enquanto `doubleclick.net` devolve `0.0.0.0`, provando que a filtragem DNS está ativa. Isto demonstra centralização, observabilidade e controlo de resolução DNS. 
