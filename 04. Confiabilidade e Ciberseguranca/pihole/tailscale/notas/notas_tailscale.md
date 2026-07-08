## Sim — já tens a tua rede Tailscale montada ✅

Do teu `tailscale status`:

| Dispositivo          |      IP Tailscale | Estado   |
| -------------------- | ----------------: | -------- |
| Este portátil        |  `100.123.108.17` | online ✅ |
| Android A56          | `100.104.253.113` | offline  |
| Desktop ThinkStation |    `100.99.35.94` | offline  |
| Desktop Windows      |  `100.113.176.35` | offline  |
| Raspberry Pi         |  `100.70.175.106` | online ✅ |

O ponto importante:

```text
raspberrypi = 100.70.175.106
```

Esse é o IP que poderá servir Pi-hole **fora de casa**, via Tailscale.

---

## Mas atenção ao aviso ⚠️

Tens isto:

```text
Tailscale can't reach the configured DNS servers.
```

Isto significa que alguma configuração DNS no Tailscale está a apontar para um DNS que o Tailscale não consegue alcançar. Pode ser por causa de DNS global configurado no painel Tailscale, ou porque o Pi-hole ainda não está a aceitar queries pela interface `tailscale0`.

---

## Ação: testar acesso ao Raspberry via Tailscale

No portátil, corre só isto:

```bash
ping -c 3 100.70.175.106
```

## Objetivo

Provar primeiro:

```text
Laptop → Tailscale → Raspberry Pi
```

Antes de mexermos no DNS fora de casa.

## Como pensar

Para usar Pi-hole no ISEP, a cadeia tem de ser:

```text
Laptop no ISEP
→ Tailscale
→ Raspberry Pi 100.70.175.106
→ Pi-hole
→ DNS filtrado
```

Mas antes de configurar DNS, temos de provar que o Raspberry responde via Tailscale.

## Pitfalls

* `192.168.1.21` só funciona em casa.
* `100.70.175.106` é o IP certo para fora de casa via Tailscale.
* Não abras a porta DNS `53` na Internet.
* O aviso de DNS do Tailscale ainda não está resolvido.

**Pergunta de decisão:** o `ping -c 3 100.70.175.106` responde?
