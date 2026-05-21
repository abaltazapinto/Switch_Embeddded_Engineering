## Resumo — Lab2 NAT-STUN / Raspberry remoto / Redes com Kathará

### Objetivo geral

Este laboratório demonstrou como uma rede privada consegue comunicar com redes externas usando **routing**, **NAT**, **port forwarding**, **STUN** e **TURN**.

A ideia principal é:

```text
Redes privadas não são diretamente acessíveis da rede pública.
Para comunicar para fora usam NAT.
Para receber ligações de fora precisam de port forwarding, STUN/TURN ou outro mecanismo.
```

O enunciado define duas redes privadas, cada uma com 3 dispositivos, ligadas a uma rede pública através de routers com NAT. 

---

# 1. Topologia usada

```text
                 Internet / 8.8.8.8
                       |
                      gwi
           eth0: 203.0.113.254
           eth1: interface externa / ISP
                       |
              Rede pública 203.0.113.0/24
        -----------------------------------------
        |                   |                   |
      stun                 ra                  rb
  203.0.113.99      eth1:203.0.113.10   eth1:203.0.113.11
                           |                   |
                    Rede A privada       Rede B privada
                    10.0.10.0/24        10.0.11.0/24
                           |                   |
              da1 10.0.10.1        db1 10.0.11.1
              da2 10.0.10.2        db2 10.0.11.2
              da3 10.0.10.3        db3 10.0.11.3
```

---

# 2. Endereços importantes

| Nó     | Interface | IP              |
| ------ | --------- | --------------- |
| `gwi`  | `eth0`    | `203.0.113.254` |
| `stun` | `eth0`    | `203.0.113.99`  |
| `ra`   | `eth0`    | `10.0.10.254`   |
| `ra`   | `eth1`    | `203.0.113.10`  |
| `rb`   | `eth0`    | `10.0.11.254`   |
| `rb`   | `eth1`    | `203.0.113.11`  |
| `da1`  | `eth0`    | `10.0.10.1`     |
| `da2`  | `eth0`    | `10.0.10.2`     |
| `da3`  | `eth0`    | `10.0.10.3`     |
| `db1`  | `eth0`    | `10.0.11.1`     |
| `db2`  | `eth0`    | `10.0.11.2`     |
| `db3`  | `eth0`    | `10.0.11.3`     |

---

# 3. Rotas por omissão

## Hosts da rede A

```bash
route add default gw 10.0.10.254
```

Aplica-se a:

```text
da1
da2
da3
```

## Hosts da rede B

```bash
route add default gw 10.0.11.254
```

Aplica-se a:

```text
db1
db2
db3
```

## Routers `ra`, `rb` e servidor `stun`

```bash
route add default gw 203.0.113.254
```

Aplica-se a:

```text
ra
rb
stun
```

---

# 4. Conceito de routing

Um host só envia diretamente para destinos dentro da sua própria rede.

Exemplo:

```text
da1 = 10.0.10.1/24
gateway = 10.0.10.254
```

Se `da1` envia para:

```text
10.0.10.2
```

vai direto, porque está na mesma rede.

Se envia para:

```text
203.0.113.99
8.8.8.8
10.0.11.1
```

tem de passar pelo gateway:

```text
10.0.10.254
```

---

# 5. NAT interno

## Em `ra`

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

## Em `rb`

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

## Significado

O NAT interno permite que hosts privados saiam para a rede pública.

Exemplo:

```text
da2 → stun
origem inicial: 10.0.10.2
após NAT em ra: 203.0.113.10
destino: 203.0.113.99
```

Para a rede B:

```text
db2 → stun
origem inicial: 10.0.11.2
após NAT em rb: 203.0.113.11
destino: 203.0.113.99
```

O material de NAT explica que NAT substitui endereços IP no cabeçalho à entrada ou saída de uma rede privada, permitindo comunicação transparente entre rede privada e externa. 

---

# 6. NAT externo no `gwi`

## Em `gwi`

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

## Significado

Permite que a rede pública simulada `203.0.113.0/24` consiga sair para a Internet real.

Depois deste passo, passaram a funcionar:

```text
da2 → 8.8.8.8
db2 → 8.8.8.8
stun → 8.8.8.8
```

## Cadeia completa de tradução

Exemplo `da2 → 8.8.8.8`:

```text
da2
src = 10.0.10.2
        ↓
ra faz NAT interno
src = 203.0.113.10
        ↓
gwi faz NAT externo
src = IP externo real do gwi
        ↓
Internet
dst = 8.8.8.8
```

Na resposta:

```text
8.8.8.8
        ↓
gwi desfaz NAT externo
dst = 203.0.113.10
        ↓
ra desfaz NAT interno
dst = 10.0.10.2
        ↓
da2
```

---

# 7. Como interpretar packet loss

```text
0% packet loss   = sucesso
100% packet loss = falha
```

Exemplo:

```text
3 packets transmitted, 3 received, 0% packet loss
```

significa que a conectividade está boa.

```text
3 packets transmitted, 0 received, 100% packet loss
```

significa falha.

Mas atenção: na análise com `tcpdump`, o objetivo pode ser só ver o pacote passar. Nesse caso, pode haver `100% packet loss` e mesmo assim o teste ser útil.

---

# 8. Análise do NAT com `tcpdump`

## Em `ra`, lado privado

```bash
tcpdump -i eth0 icmp
```

Deve mostrar origem privada:

```text
10.0.10.1 > destino
```

## Em `ra`, lado público

```bash
tcpdump -i eth1 icmp
```

Deve mostrar origem traduzida:

```text
203.0.113.10 > destino
```

## Em `stun`

```bash
tcpdump icmp
```

Também deve ver pacotes já traduzidos:

```text
203.0.113.10 > destino
```

Conclusão:

```text
O pacote sai de da1 como 10.0.10.1.
Depois de passar pelo NAT em ra, aparece na rede pública como 203.0.113.10.
```

---

# 9. Diferença entre comandos `iptables`

## Adicionar regra

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

```text
-A = append / adicionar
```

## Listar regras

```bash
iptables -t nat -L POSTROUTING -n -v
```

```text
-L = list / listar
-n = numérico, mostra IPs sem resolver nomes
-v = verbose, mostra contadores
```

## Ver PREROUTING com números de linha

```bash
iptables -t nat -L PREROUTING -n -v --line-numbers
```

---

# 10. Port forwarding

## Objetivo

Permitir que alguém do exterior aceda a serviços HTTP dentro da rede privada A.

O exterior acede ao IP público do `ra`:

```text
203.0.113.10
```

O `ra` redireciona para máquinas privadas.

---

## Regra para `da1`

```bash
iptables -t nat -A PREROUTING -p tcp --dport 81 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.1:80
```

Teste em `gwi`:

```bash
wget -q -O - http://203.0.113.10:81
```

Resultado esperado:

```text
From: da1
```

---

## Regra para `da2`

```bash
iptables -t nat -A PREROUTING -p tcp --dport 82 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.2:80
```

Teste:

```bash
wget -q -O - http://203.0.113.10:82
```

Resultado:

```text
From: da2
```

---

## Regra para `da3`

```bash
iptables -t nat -A PREROUTING -p tcp --dport 83 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.3:80
```

Teste:

```bash
wget -q -O - http://203.0.113.10:83
```

Resultado:

```text
From: da3
```

---

## Tabela final

| Porto externo | Destino interno |
| ------------: | --------------- |
|          `81` | `da1:80`        |
|          `82` | `da2:80`        |
|          `83` | `da3:80`        |

---

# 11. Diferença entre MASQUERADE e DNAT

## MASQUERADE

Usado em `POSTROUTING`.

Muda o endereço de **origem** quando o pacote sai.

```text
privado → público
```

Exemplo:

```text
10.0.10.2 → 203.0.113.10
```

## DNAT

Usado em `PREROUTING`.

Muda o endereço de **destino** quando o pacote entra.

```text
público:porta → privado:porta
```

Exemplo:

```text
203.0.113.10:81 → 10.0.10.1:80
```

---

# 12. Load balancing na porta 90

## Regras corretas em `ra`

```bash
iptables -t nat -A PREROUTING -p tcp --dport 90 -m statistic --mode random --probability 0.33 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.1:80

iptables -t nat -A PREROUTING -p tcp --dport 90 -m statistic --mode random --probability 0.5 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.2:80

iptables -t nat -A PREROUTING -p tcp --dport 90 -d 203.0.113.10 -j DNAT --to-destination 10.0.10.3:80
```

## Importante

A ordem das regras é crítica.

Ordem correta:

```text
1. 33% → da1
2. 50% dos restantes → da2
3. resto → da3
```

Se a regra de `da3` ficar primeiro, tudo vai para `da3`.

---

## Teste 20 vezes

```bash
for i in $(seq 1 20); do wget -q -O - http://203.0.113.10:90 | grep From; done
```

## Resultado obtido

| Dispositivo | Ocorrências | Percentagem |
| ----------- | ----------: | ----------: |
| `da1`       |           7 |         35% |
| `da2`       |           5 |         25% |
| `da3`       |           8 |         40% |
| Falhas      |           0 |          0% |
| Total       |          20 |        100% |

Conclusão:

```text
A porta 90 distribuiu pedidos HTTP por da1, da2 e da3.
Como o modo é aleatório, as percentagens não têm de ser exatamente 33/33/33.
```

O material de NAT também refere o uso de NAT para balanceamento de carga, distribuindo pedidos recebidos num único endereço público por vários servidores privados. 

---

# 13. STUN

## Objetivo

Descobrir o endereço reflexivo de um nó privado.

Ou seja:

```text
Qual é o IP:porto que o servidor público vê quando da1 ou db1 comunicam para fora?
```

## Servidor em `stun`

```bash
turnserver -c /etc/turnserver.conf -v
```

Ou, se necessário:

```bash
turnserver -c /etc/turnserver.conf -v --listening-port 3478
```

---

## Cliente em `da1`

```bash
python3 stun.py --role A --stun-host 203.0.113.99 --local-port 4000
```

Resultado obtido:

```text
da1 → 203.0.113.10:4000
```

## Cliente em `db1`

```bash
python3 stun.py --role B --stun-host 203.0.113.99 --local-port 4000
```

Resultado obtido:

```text
db1 → 203.0.113.11:4000
```

## Tabela STUN

| Nó privado | Endereço reflexivo  |
| ---------- | ------------------- |
| `da1`      | `203.0.113.10:4000` |
| `db1`      | `203.0.113.11:4000` |

Conclusão:

```text
da1 sai pelo NAT de ra, por isso é visto como 203.0.113.10.
db1 sai pelo NAT de rb, por isso é visto como 203.0.113.11.
```

---

# 14. TURN

## Objetivo

Permitir comunicação entre `da1` e `db1`, mesmo estando ambos atrás de NATs diferentes.

Sem TURN:

```text
da1 não consegue aceder diretamente a db1
db1 não consegue aceder diretamente a da1
```

Com TURN:

```text
da1 → TURN server ← db1
```

O servidor `stun` atua como relay.

---

## Comandos

Em `da1`:

```bash
python3 turn-talk.py answer
```

Em `db1`:

```bash
python3 turn-talk.py offer
```

Fluxo:

```text
1. db1 gera offer
2. copiar offer para da1
3. da1 gera answer
4. copiar answer para db1
5. conversa inicia
```

Resultado final observado:

```text
APP conversa iniciada
```

e os dois nós começaram a trocar mensagens.

Conclusão:

```text
TURN funcionou.
da1 e db1 comunicaram através de relay, apesar de estarem atrás de NATs diferentes.
```

---

# 15. Copy/paste em XTerm

## Problema encontrado

O copy/paste entre xterms estava instável.

Problemas observados:

```text
Ctrl+Shift+C não funcionava
Shift+Insert inseria caracteres estranhos
botão do meio colava texto antigo
```

## Solução mais fiável

Usar seleção cuidadosa da linha JSON inteira:

```text
{"sdp":"...","type":"offer"}
```

e evitar copiar:

```text
=== COPIAR ESTA OFFER ===
=== FIM OFFER ===
root@...
Traceback
```

A string tem de começar em:

```text
{
```

e acabar em:

```text
}
```

---

# 16. Comandos principais usados

## Kathará

```bash
kathara lstart
kathara lclean
```

## Ver IPs

```bash
ip addr show
```

## Ver rotas

```bash
ip route
route -n
```

## Adicionar rota default

```bash
route add default gw <gateway>
```

## Testar conectividade

```bash
ping <ip>
ping -c 3 <ip>
```

## NAT

```bash
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE
```

## Ver regras NAT

```bash
iptables -t nat -L -n -v
iptables -t nat -L POSTROUTING -n -v
iptables -t nat -L PREROUTING -n -v --line-numbers
```

## Port forwarding

```bash
iptables -t nat -A PREROUTING -p tcp --dport <porta_externa> -d <ip_publico_router> -j DNAT --to-destination <ip_privado>:80
```

## Apagar regras por número

```bash
iptables -t nat -D PREROUTING <numero>
```

Apagar sempre de baixo para cima:

```bash
iptables -t nat -D PREROUTING 6
iptables -t nat -D PREROUTING 5
iptables -t nat -D PREROUTING 4
```

## HTTP test

```bash
wget -q -O - http://203.0.113.10:81
wget -q -O - http://203.0.113.10:82
wget -q -O - http://203.0.113.10:83
wget -q -O - http://203.0.113.10:90
```

## tcpdump

```bash
tcpdump -i eth0 icmp
tcpdump -i eth1 icmp
tcpdump icmp
```

## STUN/TURN

```bash
turnserver -c /etc/turnserver.conf -v
python3 stun.py --role A --stun-host 203.0.113.99 --local-port 4000
python3 stun.py --role B --stun-host 203.0.113.99 --local-port 4000
python3 turn-talk.py answer
python3 turn-talk.py offer
```

---

# 17. Conceitos-chave para exame/prática

## Rota default

Usada quando o destino não pertence à rede local.

```text
default via gateway
```

## Gateway

Router para sair da rede local.

## NAT

Tradução de endereços IP.

## MASQUERADE

Tipo de NAT usado para tráfego de saída.

## DNAT

Altera o destino do pacote. Usado em port forwarding.

## POSTROUTING

Chain usada depois da decisão de routing, antes do pacote sair.

## PREROUTING

Chain usada quando o pacote entra, antes da decisão final de routing.

## STUN

Descobre o endereço externo/reflexivo visto do exterior.

## TURN

Relay para permitir comunicação quando NAT impede ligação direta.

## ICMP

Usado pelo `ping`.

## TCP

Usado pelo HTTP nos testes com `wget`.

## UDP/TCP

Usado por STUN/TURN dependendo da configuração.

---

# 18. Ligação ao teu Raspberry Pi

A aprendizagem prática deste lab ajuda diretamente a perceber como controlar um Raspberry remotamente.

Para aceder a um Raspberry de fora da rede tens normalmente estas opções:

| Método                | Ideia                                                         |
| --------------------- | ------------------------------------------------------------- |
| Port forwarding       | Router redireciona uma porta pública para o Raspberry         |
| VPN                   | Raspberry fica acessível como se estivesses na rede local     |
| Tailscale / WireGuard | Cria rede privada segura entre dispositivos                   |
| Reverse SSH tunnel    | Raspberry abre ligação para fora e tu entras por essa ligação |
| STUN/TURN             | Usado mais em comunicação peer-to-peer/WebRTC                 |

O que aprendeste aqui:

```text
Se o Raspberry está atrás de NAT, a Internet não consegue iniciar ligação direta para ele.
Para o controlar de fora, precisas de uma técnica que atravesse NAT:
port forwarding, VPN, reverse tunnel, STUN/TURN ou serviço semelhante.
```

---

# 19. Frase final para guardar

```text
Neste laboratório configurei e testei uma rede com duas LANs privadas atrás de routers NAT. Primeiro validei endereços IP, gateways e rotas default. Depois configurei NAT interno em ra/rb para permitir tráfego privado→público, NAT externo em gwi para saída para a Internet, port forwarding com DNAT para expor serviços HTTP internos, load balancing aleatório na porta 90, STUN para descobrir endereços reflexivos e TURN para permitir comunicação entre dois hosts privados atrás de NATs diferentes. O laboratório mostrou na prática a diferença entre routing, NAT, MASQUERADE, DNAT, STUN e TURN.
```
