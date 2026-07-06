
## Ação — próximo passo 3.4 DNS forcing

No **OPNsense**, confirma se o DNS/Unbound está a ouvir na porta 53:

```sh
sockstat -4 -l | grep ':53'
```

## Objetivo

Antes de redirecionar DNS, confirmar que existe um serviço DNS ativo na OPNsense.

## Resultado esperado

Algo com:

```text
unbound
:53
```

## Pergunta

Aparece `unbound` ou alguma linha com `:53`?


![alt text](image-24.png)

---

Sim. Está certo ✅

No output aparece:

```text
unbound udp4 *:53
unbound tcp4 *:53
```

Isto quer dizer:

| Protocolo  | Estado  |
| ---------- | ------- |
| DNS UDP/53 | ativo ✅ |
| DNS TCP/53 | ativo ✅ |

O `dnsmasq` em `53053` podes ignorar agora.

## Ação — 1 passo

No **ubuntu1-lan**, testa DNS contra um servidor externo antes do forcing:

```bash
nslookup example.com 8.8.8.8
```

## Objetivo

Ver se, antes da regra de forcing, o cliente consegue pedir DNS diretamente ao `8.8.8.8`.

## Como pensar

No 3.4 queremos forçar isto:

```text
cliente pede DNS ao 8.8.8.8
        ↓
OPNsense intercepta
        ↓
manda para Unbound local
```

## Pergunta

O `nslookup example.com 8.8.8.8` responde ou dá erro?


erro 
![alt text](image-25.png)

---

Causa provável

Esse erro é normal agora:

no servers could be reached

Porque quando carregaste:

pfctl -f /tmp/g33.pf

ficou ativa só a regra do NAT/RDR do 3.3. Ou seja, substituíste temporariamente as regras anteriores de NAT/internet.

Ação — 1 passo

No OPNsense, volta ao ruleset que já tinha NAT/internet:

pfctl -f /tmp/guiao4-323.pf
Objetivo

Recuperar o acesso do ubuntu1 à internet/DNS antes de fazer o 3.4 DNS forcing.

Como pensar

pfctl -f ficheiro.pf não “adiciona” regras. Ele substitui o ruleset ativo.

Portanto:

/tmp/g33.pf = só port-forward do 3.3
/tmp/guiao4-323.pf = regras anteriores com NAT

---

ja deu 

![alt text](image-26.png)

# 6

## 3.4 — DNS forcing

O `nslookup example.com 8.8.8.8` agora respondeu ✅
Isto prova que **antes do forcing** o `ubuntu1` consegue consultar DNS diretamente ao `8.8.8.8`.

## Ação — 1 passo

No **OPNsense**, adiciona só a regra DNS forcing para **UDP/53 da LAN1**:

```sh
echo 'rdr pass on vtnet1 proto udp from 192.168.1.0/24 to any port 53 -> 192.168.1.1 port 53' >> /tmp/guiao4-323.pf
```

Depois confirma:

```sh
tail -1 /tmp/guiao4-323.pf
```

## Objetivo

Preparar o redirecionamento:

```text
ubuntu1 pede DNS ao 8.8.8.8:53
        ↓
OPNsense intercepta na vtnet1
        ↓
manda para Unbound em 192.168.1.1:53
```

## Como pensar

Isto é o **DNS forcing**:

> O cliente pensa que está a usar `8.8.8.8`, mas a firewall força o pedido DNS para o resolvedor local da OPNsense.

## Pergunta

O `tail -1` mostra a regra `rdr pass on vtnet1 ... port 53 -> 192.168.1.1 port 53`?


![alt text](image-27.png)

# 7 