Sim — **o Guião 3 está feito na parte prática essencial**. ✅

Tens as provas certas:

| Parte                        | Estado | Prova                                                                       |
| ---------------------------- | -----: | --------------------------------------------------------------------------- |
| **3.1 OPNsense com LAN/WAN** |      ✅ | LAN `192.168.1.1/24`, WAN `10.42.0.227/24`                                  |
| **3.2 LAN + DNS OPNsense**   |      ✅ | C3 usa `nameserver 192.168.1.1`                                             |
| **3.3 CT na LAN + Internet** |      ✅ | C3 tem `192.168.1.142/24`, gateway `192.168.1.1`, ping `8.8.8.8` OK         |
| **DNS por OPNsense**         |      ✅ | `ping google.com` OK e `getent ahostsv4 google.com` devolve `216.58.205.78` |

## O que isto prova

```text
C3 192.168.1.142
→ OPNsense LAN 192.168.1.1
→ OPNsense WAN 10.42.0.227
→ Internet
```

E também:

```text
C3 → DNS 192.168.1.1 → google.com → 216.58.205.78
```

## Frase para dizer ao professor

> No Guião 3 configurei a OPNsense com duas interfaces: LAN em `192.168.1.1/24` e WAN em `10.42.0.227/24`. Coloquei o C3 na LAN via `vmbr3`, recebeu IP `192.168.1.142` por DHCP, gateway `192.168.1.1` e DNS `192.168.1.1`. Validei conectividade com a firewall, saída para a Internet por IP com `ping 8.8.8.8`, e resolução DNS com `ping google.com` e `getent ahostsv4 google.com`.

## Ação — 1 passo

Guarda estes outputs para o relatório/apresentação:

```bash
ip a
ip route
cat /etc/resolv.conf
ping -c 4 192.168.1.1
ping -c 4 8.8.8.8
ping -c 4 google.com
getent ahostsv4 google.com
```

## Objetivo

Ter evidência limpa para provar:

* DHCP funcionou;
* gateway é a OPNsense;
* DNS é a OPNsense;
* Internet por IP funciona;
* DNS + Internet funcionam.

## Pitfall

Não digas “DHCP não funcionava”. O correto é:

> DHCP funcionava; o problema inicial era o DNS estar apontado para `192.168.1.21` em vez de `192.168.1.1`.

## Pergunta de decisão

Queres agora fazer **as respostas da avaliação do Guião 3** para enviares/submeteres?
