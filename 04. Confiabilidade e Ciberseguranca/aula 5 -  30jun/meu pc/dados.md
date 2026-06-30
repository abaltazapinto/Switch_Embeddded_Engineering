PC Ubuntu:        192.168.1.19
Interface:        wlp0s20f3
Gateway/router:   192.168.1.1
DNS local Ubuntu: 127.0.0.53
DNS público:      8.8.8.8
Google web:       142.251.xxx.xxx

default via 192.168.1.1 dev wlp0s20f3 proto dhcp src 192.168.1.19

Isto significa:

Quando o teu PC quer sair para a Internet, envia tráfego pela interface Wi-Fi wlp0s20f3, usando o router 192.168.1.1, com origem 192.168.1.19.

# a cadeia real e 

Aplicação/browser
   ↓
DNS local Ubuntu: 127.0.0.53
   ↓
Router/DNS: 192.168.1.1
   ↓
DNS externo / Internet
   ↓
www.google.com → 142.251.xxx.xxx

## Ação — 1 passo

Cola isto no teu `dados.md` para fechar a parte de DNS:

````md
## DNS — mapa do meu PC

### Endereços observados

| Elemento | IP / valor | Função |
|---|---|---|
| PC Ubuntu | `192.168.1.19` | máquina local na rede Wi-Fi |
| Interface Wi-Fi | `wlp0s20f3` | interface usada para sair para a Internet |
| Gateway/router | `192.168.1.1` | router da rede local |
| DNS local Ubuntu | `127.0.0.53` | `systemd-resolved`, resolver local do Ubuntu |
| DNS público Google | `8.8.8.8` | resolver DNS público |
| Google web | `142.251.xxx.xxx` | IPs reais devolvidos para `www.google.com` |

---

## Cadeia real de resolução DNS

Quando faço:

```bash
nslookup -type=A www.google.com.
````

o caminho lógico é:

```text
Aplicação / terminal
   ↓
127.0.0.53        DNS local do Ubuntu
   ↓
192.168.1.1       router / DNS da rede local
   ↓
DNS externo / Internet
   ↓
www.google.com → 142.251.xxx.xxx
```

---

## Cadeia DNS autoritativa

Quando faço manualmente a resolução DNS, sigo a hierarquia:

```text
Root server
   ↓
servidores .com
   ↓
servidores autoritativos de google.com
   ↓
registos A de www.google.com
```

Exemplo:

```bash
nslookup -type=NS com. j.root-servers.net
nslookup -type=NS google.com. a.gtld-servers.net
nslookup -type=A www.google.com. ns1.google.com
```

Interpretação:

* `j.root-servers.net` não sabe o IP de `google.com`, mas sabe quem gere `.com`.
* `a.gtld-servers.net` não sabe o IP final de `www.google.com`, mas sabe quem gere `google.com`.
* `ns1.google.com` é autoritativo para `google.com` e devolve IPs reais de `www.google.com`.

---

## Diferença entre resposta autoritativa e não autoritativa

### Resposta autoritativa

Vem diretamente de um servidor responsável pela zona DNS.

Exemplo:

```bash
nslookup -type=A www.google.com. ns1.google.com
```

Aqui pergunto diretamente ao servidor autoritativo da Google.

### Resposta não autoritativa

Vem de cache ou de um resolver intermédio.

Exemplo:

```bash
nslookup -type=A www.google.com. 8.8.8.8
nslookup -type=A www.google.com. 192.168.1.1
nslookup -type=A www.google.com.
```

Se aparecer:

```text
Non-authoritative answer
```

significa que a resposta não veio diretamente do servidor autoritativo da zona.

---

## Porque aparecem muitos IPs para [www.google.com](http://www.google.com)?

O DNS pode devolver vários registos `A` para o mesmo nome:

```text
www.google.com → 142.251.150.119
www.google.com → 142.251.151.119
www.google.com → 142.251.152.119
...
```

Isto serve para:

* balanceamento de carga;
* redundância;
* tolerância a falhas;
* distribuição geográfica;
* alta disponibilidade.

A ordem dos IPs pode mudar entre consultas. Isso é normal.

---

## Captura real com tcpdump

Para ver pacotes DNS reais na interface Wi-Fi:

```bash
sudo tcpdump -i wlp0s20f3 -n udp port 53
```

Noutro terminal, posso gerar uma consulta DNS:

```bash
nslookup -type=A www.google.com. 8.8.8.8
```

O que espero observar:

```text
192.168.1.19 → 8.8.8.8     DNS query
8.8.8.8 → 192.168.1.19     DNS response
```

Isto prova que DNS usa normalmente a porta `53/UDP`.

---

## Frase para avaliação

O meu PC tem o IP `192.168.1.19` na interface Wi-Fi `wlp0s20f3`.
Quando resolve um nome DNS normalmente, pergunta primeiro ao resolver local do Ubuntu `127.0.0.53`, que depois encaminha para o DNS configurado na rede, neste caso o router `192.168.1.1`.
Quando faço a resolução manual, consigo seguir a hierarquia DNS: root servers, servidores do TLD `.com`, servidores autoritativos de `google.com`, e finalmente os registos `A` de `www.google.com`.

````

## Objetivo

Ficas com uma nota completa que liga:

```text
nslookup
resolvectl
ip addr
ip route
tcpdump
DNS autoritativo vs não autoritativo
````

## Pergunta de decisão

Queres agora fazer só a captura `tcpdump` para tirares uma imagem/evidência prática para o relatório?



## Captura DNS com tcpdump

Comando usado:

```bash
sudo tcpdump -i wlp0s20f3 -n udp port 53