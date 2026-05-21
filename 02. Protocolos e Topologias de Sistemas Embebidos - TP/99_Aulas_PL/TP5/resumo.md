## Ação — resumo para copiar/colar ✅

````md
# TP5 — IPv6 / Rotas / ULA / EUI-64 — Rede `maracas`

## Contexto

Exercício TP5 da disciplina PRSIEM — Protocolos e Topologias de Sistemas Embebidos.

Objetivo geral:
- Alocar endereços IPv6 GUA e ULA.
- Definir endereços dos encaminhadores.
- Preencher tabelas de encaminhamento.
- Compreender EUI-64 a partir de MAC.
- Trabalhar conceitos IPv6, SLAAC, DHCPv6 e routing.

A aula/lab IPv6 usa Kathará e pede ativação de IPv6 em `kathara settings`, importação da rede e arranque com `kathara lstart`. O Lab5 também trabalha endereços IPv6, EUI-64, link-local `FE80::/10`, Router Advertisement, Router Solicitation e SLAAC. :contentReference[oaicite:0]{index=0}

---

# 1. Dados pessoais do exercício

Número: `1200209`

Gama GUA atribuída:

```txt
2023:8c42:7ea9:6128::/61
````

Identificador ULA:

```txt
c7d82e12e9
```

Prefixo ULA usado:

```txt
fdc7:d82e:12e9::/48
```

---

# 2. Alocação GUA

A gama `/61` contém 8 redes `/64`:

```txt
2023:8c42:7ea9:6128::/64
2023:8c42:7ea9:6129::/64
2023:8c42:7ea9:612a::/64
2023:8c42:7ea9:612b::/64
2023:8c42:7ea9:612c::/64
2023:8c42:7ea9:612d::/64
2023:8c42:7ea9:612e::/64
2023:8c42:7ea9:612f::/64
```

Tabela usada:

```txt
A      2023:8c42:7ea9:6128::/64
Norte  2023:8c42:7ea9:6129::/64
B      2023:8c42:7ea9:6129:0000::/68
C      2023:8c42:7ea9:6129:1000::/68
D      2023:8c42:7ea9:6129:2000::/68
E      2023:8c42:7ea9:6129:3000::/68
F      2023:8c42:7ea9:612a::/64
Sul    2023:8c42:7ea9:612c::/62
G      2023:8c42:7ea9:612c::/64
H      2023:8c42:7ea9:612d::/64
I      2023:8c42:7ea9:612e::/64
J      2023:8c42:7ea9:612f::/64
```

Notas:

* Norte usa DHCPv6, por isso foi dividido em `/68`.
* Sul usa SLAAC, por isso G/H/I/J ficaram em `/64`.
* Em IPv6, SLAAC normalmente exige prefixo `/64`.

---

# 3. Endereços GUA dos encaminhadores

```txt
br eth0  2023:8c42:7ea9:612a::1/64
br eth1  2023:8c42:7ea9:6128::1/64
br eth2  2023:8c42:7ea9:612b::1/64

n1 eth0  2023:8c42:7ea9:6129:1000::1/68
n1 eth1  2023:8c42:7ea9:6129:3000::1/68
n1 eth2  2023:8c42:7ea9:6128::2/64

n2 eth0  2023:8c42:7ea9:6129:2000::1/68
n2 eth1  2023:8c42:7ea9:6129:3000::2/68

n3 eth0  2023:8c42:7ea9:6129::1/68
n3 eth1  2023:8c42:7ea9:6129:2000::2/68
n3 eth2  2023:8c42:7ea9:6129:1000::2/68

s1 eth0  2023:8c42:7ea9:612d::1/64
s1 eth1  2023:8c42:7ea9:612a::2/64
s1 eth2  2023:8c42:7ea9:612e::1/64

s2 eth0  2023:8c42:7ea9:612c::1/64
s2 eth1  2023:8c42:7ea9:612d::2/64
s2 eth2  2023:8c42:7ea9:612f::1/64

s3 eth0  2023:8c42:7ea9:612f::2/64
s3 eth1  2023:8c42:7ea9:612e::2/64
```

---

# 4. Alocação ULA

Conversão feita trocando:

```txt
2023:8c42:7ea9  ->  fdc7:d82e:12e9
```

Tabela ULA:

```txt
A      fdc7:d82e:12e9:6128::/64
Norte  fdc7:d82e:12e9:6129::/64
B      fdc7:d82e:12e9:6129:0000::/68
C      fdc7:d82e:12e9:6129:1000::/68
D      fdc7:d82e:12e9:6129:2000::/68
E      fdc7:d82e:12e9:6129:3000::/68
F      fdc7:d82e:12e9:612a::/64
Sul    fdc7:d82e:12e9:612c::/62
G      fdc7:d82e:12e9:612c::/64
H      fdc7:d82e:12e9:612d::/64
I      fdc7:d82e:12e9:612e::/64
J      fdc7:d82e:12e9:612f::/64
```

---

# 5. Endereços ULA dos encaminhadores

```txt
br eth0  fdc7:d82e:12e9:612a::1/64
br eth1  fdc7:d82e:12e9:6128::1/64
br eth2  fdc7:d82e:12e9:612b::1/64

n1 eth0  fdc7:d82e:12e9:6129:1000::1/68
n1 eth1  fdc7:d82e:12e9:6129:3000::1/68
n1 eth2  fdc7:d82e:12e9:6128::2/64

n2 eth0  fdc7:d82e:12e9:6129:2000::1/68
n2 eth1  fdc7:d82e:12e9:6129:3000::2/68

n3 eth0  fdc7:d82e:12e9:6129::1/68
n3 eth1  fdc7:d82e:12e9:6129:2000::2/68
n3 eth2  fdc7:d82e:12e9:6129:1000::2/68

s1 eth0  fdc7:d82e:12e9:612d::1/64
s1 eth1  fdc7:d82e:12e9:612a::2/64
s1 eth2  fdc7:d82e:12e9:612e::1/64

s2 eth0  fdc7:d82e:12e9:612c::1/64
s2 eth1  fdc7:d82e:12e9:612d::2/64
s2 eth2  fdc7:d82e:12e9:612f::1/64

s3 eth0  fdc7:d82e:12e9:612f::2/64
s3 eth1  fdc7:d82e:12e9:612e::2/64
```

---

# 6. Rotas principais

## 6.1 Encaminhador br

```txt
A              2023:8c42:7ea9:6128::/64      direto        eth1
maraca_norte   2023:8c42:7ea9:6129::/64      via n1.eth2   2023:8c42:7ea9:6128::2      eth1
F              2023:8c42:7ea9:612a::/64      direto        eth0
maraca_sul     2023:8c42:7ea9:612c::/62      via s1.eth1   2023:8c42:7ea9:612a::2      eth0
ISP            isp.x.0.0/n                   direto        eth2
Default        ::/0                          via isp.gw    isp.x.0.gw                   eth2
```

## 6.2 Encaminhador n1

```txt
A        2023:8c42:7ea9:6128::/64             direto        eth2
B        2023:8c42:7ea9:6129:0000::/68        via n3.eth2   2023:8c42:7ea9:6129:1000::2   eth0
C        2023:8c42:7ea9:6129:1000::/68        direto        eth0
D        2023:8c42:7ea9:6129:2000::/68        via n2.eth1   2023:8c42:7ea9:6129:3000::2   eth1
E        2023:8c42:7ea9:6129:3000::/68        direto        eth1
Default  ::/0                                 via br.eth1   2023:8c42:7ea9:6128::1        eth2
```

## 6.3 Encaminhador n2

```txt
B        2023:8c42:7ea9:6129:0000::/68        via n3.eth1   2023:8c42:7ea9:6129:2000::2   eth0
D        2023:8c42:7ea9:6129:2000::/68        direto        eth0
E        2023:8c42:7ea9:6129:3000::/68        direto        eth1
Default  ::/0                                 via n1.eth1   2023:8c42:7ea9:6129:3000::1   eth1
```

## 6.4 Encaminhador n3

```txt
B        2023:8c42:7ea9:6129:0000::/68        direto        eth0
C        2023:8c42:7ea9:6129:1000::/68        direto        eth2
D        2023:8c42:7ea9:6129:2000::/68        direto        eth1
Default  ::/0                                 via n1.eth0   2023:8c42:7ea9:6129:1000::1   eth2
```

Nota importante:

* No Moodle inicialmente ficou `n1.eth2`, mas o correto é `n1.eth0`.
* O endereço estava certo: `2023:8c42:7ea9:6129:1000::1`.
* A porta de saída em n3 continua `eth2`.

## 6.5 Encaminhador s1

```txt
F        2023:8c42:7ea9:612a::/64             direto        eth1
H        2023:8c42:7ea9:612d::/64             direto        eth0
I        2023:8c42:7ea9:612e::/64             direto        eth2
G        2023:8c42:7ea9:612c::/64             via s2.eth1   2023:8c42:7ea9:612d::2        eth0
J        2023:8c42:7ea9:612f::/64             via s3.eth1   2023:8c42:7ea9:612e::2        eth2
Default  ::/0                                 via br.eth0   2023:8c42:7ea9:612a::1        eth1
```

## 6.6 Encaminhador s2

```txt
G        2023:8c42:7ea9:612c::/64             direto        eth0
H        2023:8c42:7ea9:612d::/64             direto        eth1
J        2023:8c42:7ea9:612f::/64             direto        eth2
Default  ::/0                                 via s1.eth0   2023:8c42:7ea9:612d::1        eth1
```

## 6.7 Encaminhador s3

```txt
I        2023:8c42:7ea9:612e::/64             direto        eth1
J        2023:8c42:7ea9:612f::/64             direto        eth0
G        2023:8c42:7ea9:612c::/64             via s2.eth2   2023:8c42:7ea9:612f::1        eth0
Default  ::/0                                 via s1.eth2   2023:8c42:7ea9:612e::1        eth1
```

## 6.8 Nó Host

```txt
B        2023:8c42:7ea9:6129:0000::/68        direto        eth0
Default  ::/0                                 via n3.eth0   2023:8c42:7ea9:6129::1        eth0
```

## 6.9 Servidores srv1, srv2, srv3

```txt
G        2023:8c42:7ea9:612c::/64             direto        eth0
Default  ::/0                                 via s2.eth0   2023:8c42:7ea9:612c::1        eth0
```

---

# 7. EUI-64

Tabela usada:

```txt
s1 eth0   MAC 56:00:00:00:01:10   EUI-64 5400:00ff:fe00:0110
s1 eth1   MAC 56:00:00:00:01:11   EUI-64 5400:00ff:fe00:0111
s1 eth2   MAC 56:00:00:00:01:12   EUI-64 5400:00ff:fe00:0112

s2 eth0   MAC 56:00:00:00:02:20   EUI-64 5400:00ff:fe00:0220
s2 eth1   MAC 56:00:00:00:02:21   EUI-64 5400:00ff:fe00:0221
s2 eth2   MAC 56:00:00:00:02:22   EUI-64 5400:00ff:fe00:0222

s3 eth0   MAC 56:00:00:00:03:30   EUI-64 5400:00ff:fe00:0330
s3 eth1   MAC 56:00:00:00:03:31   EUI-64 5400:00ff:fe00:0331
```

Regra EUI-64:

```txt
MAC original:
56:00:00:00:01:10

1. Inserir ff:fe no meio:
56:00:00:ff:fe:00:01:10

2. Inverter o bit U/L do primeiro byte:
56 XOR 02 = 54

3. Agrupar em formato IPv6:
5400:00ff:fe00:0110
```

Notas:

* O campo pedia só o identificador EUI-64, não o endereço completo.
* Por isso não foi colocado `fe80::`.
* Se fosse endereço link-local completo, seria algo como:
  `fe80::5400:00ff:fe00:0110`.

---

# 8. Conceitos importantes

## GUA

Global Unicast Address.

Endereço IPv6 global, roteável na Internet.

Exemplo:

```txt
2023:8c42:7ea9:6128::/64
```

## ULA

Unique Local Address.

Endereço local privado IPv6, semelhante ao uso de redes privadas em IPv4.

Exemplo:

```txt
fdc7:d82e:12e9:6128::/64
```

## Link-local

Endereço IPv6 local ao segmento/link.

Prefixo típico:

```txt
fe80::/10
```

Routers não encaminham pacotes link-local.

## SLAAC

Stateless Address Auto Configuration.

Permite que um nó configure o seu endereço IPv6 automaticamente através de:

* Prefixo anunciado pelo router.
* Identificador EUI-64 local calculado a partir do MAC.

O Lab5 explica que SLAAC usa Router Advertisement e Router Solicitation, definidos pelo protocolo NDP. 

## DHCPv6

Configuração dinâmica de endereços IPv6.

No exercício:

* Norte usa DHCPv6.
* Sul usa SLAAC.

## Routing

Regra mental:

```txt
Se a rede está diretamente ligada à interface:
  gateway = --
  porta = interface local

Se a rede está atrás de outro router:
  gateway = próximo router diretamente ligado
  porta = interface local que chega a esse router
```

---

# 9. Instalação Kathará na VM

Problema inicial:

```bash
sudo apt install kathara
```

Deu:

```txt
Unable to locate package kathara
```

Solução correta usada:

```bash
sudo add-apt-repository ppa:katharaframework/kathara
sudo apt update
sudo apt install kathara
```

Depois:

```bash
kathara --version
kathara check
```

Resultado:

* Kathará instalado.
* Docker ativo.
* `kathara check` passou.

Depois em:

```bash
kathara settings
```

Foi confirmado/ativado:

```txt
Enable IPv6: Yes
```

---

# 10. Docker

Kathará precisa de Docker para lançar cada nó da topologia como contentor.

Instalação usada:

```bash
sudo apt install -y docker.io
```

Verificação:

```bash
sudo systemctl status docker
```

Resultado esperado:

```txt
active (running)
```

---

# 11. Pitfalls importantes

1. Não copiar endereços dos colegas diretamente.

   * A gama depende do número de aluno.

2. B/C/D/E no Norte são `/68`, não `/64`.

3. G/H/I/J no Sul são `/64`, porque SLAAC precisa normalmente de `/64`.

4. Gateway não leva prefixo.

   * Certo:
     `2023:8c42:7ea9:6128::1`
   * Errado:
     `2023:8c42:7ea9:6128::1/64`

5. Rota default é sempre:

```txt
::/0
```

6. Gateway é sempre o próximo salto diretamente ligado, não o destino final.

7. Em `n3`, default correto:

```txt
Gateway nome: n1.eth0
Gateway endereço: 2023:8c42:7ea9:6129:1000::1
Porta: eth2
```

8. Em EUI-64:

   * Inserir `ff:fe`.
   * Inverter bit U/L do primeiro byte.
   * `56` passa para `54`.

---

# 12. Estado final

O TP5 ficou essencialmente resolvido com:

* Gama GUA correta.
* Prefixo ULA correto.
* Alocação de sub-redes coerente.
* Endereços de routers coerentes.
* Tabelas de rotas coerentes.
* EUI-64 calculado corretamente.
* Kathará instalado e funcional na VM.
* Docker ativo.
* IPv6 ativo nas settings do Kathará.

Este exercício foi muito importante porque consolidou:

* IPv6.
* CIDR.
* GUA vs ULA.
* SLAAC.
* DHCPv6.
* Routing.
* Gateway/default route.
* EUI-64.
* Uso de Kathará/Docker para simulação de redes.

```

## Objetivo

Fica como registo técnico no teu Git/notes do curso.

## Pitfalls

1. Corrige no Moodle/Git o detalhe do `n3`: `n1.eth0`, não `n1.eth2`.
2. Guarda também screenshots, porque ajudam a reconstruir a lógica da topologia.
3. Não trates os MACs EUI-64 como “reais”; foram uma escolha coerente para responder ao quiz.
4. Guarda a diferença entre **endereço de gateway** e **porta de saída**.

## Pergunta de decisão

Queres que eu transforme isto numa versão mais curta estilo `README.md` para o repositório Git?
```
