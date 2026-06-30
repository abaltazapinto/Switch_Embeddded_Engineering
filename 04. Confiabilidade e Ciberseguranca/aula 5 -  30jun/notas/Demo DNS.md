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