# Avaliação — Guião 3 OPNsense

## Ação — 1 passo

Copia esta versão para o relatório/email do grupo e ajusta só os nomes dos elementos do grupo.

---

## 1) Ao colocar o IP no `vmbr3`, como é que as rotas são realizadas e como permitem o acesso à LAN?

Ao colocar o cliente C3 na bridge `vmbr3`, ele fica ligado à **LAN da OPNsense**.

No nosso caso:

```text
OPNsense LAN: 192.168.1.1/24
C3:           192.168.1.142/24
Gateway C3:   192.168.1.1
```

Como o C3 e a interface LAN da OPNsense estão na mesma rede `192.168.1.0/24`, o C3 consegue comunicar diretamente com a firewall.

A rota local é:

```text
192.168.1.0/24 dev eth0
```

A rota para tudo o que está fora da LAN é:

```text
default via 192.168.1.1
```

Isto significa que qualquer tráfego externo do C3 é enviado para a OPNsense. A firewall decide se permite o tráfego e, se permitido, encaminha-o pela WAN usando NAT.

**Frase curta:**

> O `vmbr3` coloca o cliente na LAN da OPNsense. A rota local permite acesso direto a `192.168.1.1`, e a rota default envia o tráfego externo para a firewall.

---

## 2) Verificar o que é e se pode ser ativado no ISEP

### a) `Allow DNS server list to be overridden by DHCP/PPP on WAN`

Esta opção permite que a OPNsense use os servidores DNS recebidos automaticamente pela interface WAN através de DHCP ou PPP. Segundo a documentação da OPNsense, esses DNS são usados pelo próprio sistema, incluindo serviços DNS, mas não são automaticamente entregues aos clientes DHCP/PPTP. ([OPNsense Documentation][1])

**No laboratório ISEP:**
Pode fazer sentido ativar, porque a WAN da OPNsense recebeu IP por DHCP:

```text
WAN: 10.42.0.227/24
```

Se o DHCP da rede do laboratório também fornecer DNS, esta opção permite que a OPNsense use esses DNS como upstream.

**Impacto:**
Ajuda a OPNsense a resolver nomes quando não queremos configurar DNS manualmente.

**Frase curta:**

> Ativei esta opção para permitir que a OPNsense use os DNS fornecidos por DHCP na WAN, o que é útil no laboratório porque a WAN está configurada por DHCP.

---

### b) Unbound DNS — `Enable DNSSEC`, `Harden DNSSEC`

Vou tratar “DNSSC” como **DNSSEC**, porque é o nome técnico da opção.

O **Unbound DNS** é o serviço DNS da OPNsense. A documentação descreve-o como um resolver DNS recursivo, validante e com cache. ([OPNsense Documentation][2])

**Enable DNSSEC:**
Ativa validação DNSSEC. Isto permite verificar criptograficamente se a resposta DNS não foi manipulada.

**Harden DNSSEC:**
Torna a validação mais rigorosa. O objetivo é reduzir ataques como respostas DNS falsas ou tentativas de enfraquecer a validação.

**No laboratório ISEP:**
Pode ser ativado, mas com cuidado. Se houver problemas de hora/NTP, upstream DNS ou forwarding, pode causar falhas de resolução DNS. A própria documentação da OPNsense avisa que DNS forwarding combinado com DNSSEC pode causar problemas se o upstream não suportar validação DNSSEC corretamente. ([OPNsense Documentation][2])

**Frase curta:**

> DNSSEC aumenta a segurança da resolução DNS, mas pode introduzir falhas se o upstream DNS ou a configuração de forwarding não suportarem corretamente validação DNSSEC.

---

## 3) Verificar o que são as opções e qual o seu impacto

### a) MAC spoofing

**MAC spoofing** é alterar o endereço MAC apresentado por uma interface de rede.

Na OPNsense, o campo **MAC Address** pode ser usado para forçar/spoofar um MAC diferente; normalmente deve ficar vazio para usar o MAC real da placa/interface. ([OPNsense Documentation][3])

**Impacto:**
Pode ser útil quando um ISP ou rede autentica equipamentos pelo MAC address. Também pode ser usado em ataques para imitar outro dispositivo.

**No laboratório:**
Normalmente não é necessário.

**Frase curta:**

> MAC spoofing permite alterar o MAC visível da interface. Pode ser útil para compatibilidade com redes que filtram por MAC, mas também pode ser usado de forma abusiva.

---

### b) MTU e MSS

**MTU** significa *Maximum Transfer Unit*. É o tamanho máximo de um pacote que pode passar por uma interface sem fragmentação.

**MSS** significa *Maximum Segment Size*. É o tamanho máximo de dados TCP dentro de um segmento. A OPNsense apresenta MTU e MSS como opções de interface. ([OPNsense Documentation][3])

**Impacto:**
Se o MTU/MSS estiver mal configurado, podem aparecer problemas estranhos:

* alguns sites abrem e outros não;
* downloads falham;
* VPNs ficam instáveis;
* pacotes grandes perdem-se.

**No laboratório:**
Normalmente mantém-se o valor por defeito, por exemplo MTU 1500.

**Frase curta:**

> MTU controla o tamanho máximo do pacote na interface; MSS controla o tamanho máximo do payload TCP. Valores errados podem causar fragmentação ou falhas de conectividade.

---

### c) PPPoE e PPTP

**PPPoE** é *Point-to-Point Protocol over Ethernet*. É usado por alguns ISPs para autenticar ligações de Internet, especialmente em redes DSL/fibra com autenticação. A documentação da OPNsense indica que PPPoE encapsula frames PPP sobre Ethernet e é usado com autenticação pelo fornecedor. ([OPNsense Documentation][4])

**PPTP** é *Point-to-Point Tunneling Protocol*. É um protocolo antigo de túnel/VPN. A documentação da OPNsense refere que PPTP é considerado inseguro devido a mecanismos fracos de encriptação. ([OPNsense Documentation][4])

**Impacto:**

* PPPoE pode ser necessário em certos ISPs.
* PPTP deve ser evitado em produção por razões de segurança.

**No laboratório:**
Não foi necessário usar PPPoE nem PPTP para o Guião 3.

**Frase curta:**

> PPPoE é usado para autenticação de acesso à Internet em alguns ISPs. PPTP é um protocolo antigo de VPN/túnel e deve ser evitado por ser inseguro.

---

### d) RFC1918 — impacto previsto quando corre no laboratório

RFC1918 define os blocos IPv4 privados usados em redes internas:

```text
10.0.0.0/8
172.16.0.0/12
192.168.0.0/16
```

Estes endereços são reservados para redes privadas. ([IETF Datatracker][5])

No nosso laboratório, a WAN da OPNsense recebeu:

```text
10.42.0.227/24
```

Isto pertence ao bloco privado:

```text
10.0.0.0/8
```

Logo, se ativarmos uma opção de bloquear redes privadas/RFC1918 na WAN, podemos bloquear tráfego legítimo do laboratório. A documentação da OPNsense diz que **Block private networks** bloqueia tráfego que vem de endereços privados e que, numa WAN real pública, isso normalmente não deveria acontecer. ([OPNsense Documentation][3])

**Impacto no laboratório:**
Não convém ativar o bloqueio RFC1918 na WAN, porque a rede WAN do laboratório usa IP privado.

**Frase curta:**

> No laboratório, a WAN usa `10.42.0.227`, que é RFC1918. Se bloquearmos RFC1918 na WAN, podemos bloquear a própria rede do laboratório.

---

### e) Bogon networks

**Bogon networks** são redes inválidas, reservadas ou que não deveriam aparecer como origem legítima na Internet.

Na OPNsense, **Block bogon networks** bloqueia tráfego vindo de endereços inválidos ou reservados, também chamados *Martian packets*. A documentação indica ainda que isto pode incluir algum tráfego multicast usado por protocolos como OSPF/RTMP. ([OPNsense Documentation][3])

**Impacto:**
Aumenta a segurança numa WAN real, porque bloqueia tráfego suspeito ou malformado.

**No laboratório:**
Pode causar bloqueios inesperados se a rede do laboratório usar endereços, multicast ou tráfego especial. Por isso, para o guião, só ativaria se o professor pedir ou se for claramente necessário.

**Frase curta:**

> Bogon networks são endereços inválidos ou reservados. Bloqueá-los aumenta a segurança numa WAN real, mas em laboratório pode causar bloqueios inesperados.

---

## 4) Porque é que ativou a opção `Use System Nameservers` no Unbound?

Ativei **Use System Nameservers** para que o Unbound use os DNS configurados no sistema OPNsense como servidores upstream. A documentação da OPNsense indica que esta opção faz o Unbound encaminhar queries para os nameservers do sistema. ([OPNsense Documentation][2])

No nosso caso, isto permitiu:

```text
C3 → DNS 192.168.1.1 → OPNsense/Unbound → DNS upstream → resposta
```

**Frase curta:**

> Ativei `Use System Nameservers` para que o Unbound da OPNsense encaminhe pedidos DNS para os DNS configurados no sistema, permitindo aos clientes da LAN resolver nomes através da firewall.

---

## 5) Porque é que alterou o DNS server no CT?

Inicialmente, o CT C3 tinha:

```text
nameserver 192.168.1.21
```

Esse IP era o Pi-hole, não a OPNsense.

Para o Guião 3, o objetivo era validar a OPNsense como DNS da LAN. Por isso alterei o DNS do CT para:

```text
nameserver 192.168.1.1
```

Depois disso, o teste funcionou:

```bash
ping -c 4 google.com
getent ahostsv4 google.com
```

**Interpretação:**
O problema inicial não era DHCP. O DHCP funcionava, porque o C3 recebeu:

```text
IP:      192.168.1.142/24
Gateway: 192.168.1.1
```

O problema era o DNS estar apontado para o servidor errado.

**Frase curta:**

> Alterei o DNS server no CT para `192.168.1.1` porque o guião pretendia testar a OPNsense como DNS da LAN. Antes, o CT estava a usar `192.168.1.21`, que era o Pi-hole.

---

# Versão curta para enviar

```text
1) Ao colocar o cliente na bridge vmbr3, ele fica ligado à LAN da OPNsense. No nosso caso, o C3 recebeu 192.168.1.142/24 e a OPNsense LAN tem 192.168.1.1/24. A rota local 192.168.1.0/24 permite comunicação direta com a firewall, e a rota default via 192.168.1.1 envia o tráfego externo para a OPNsense.

2a) A opção “Allow DNS server list to be overridden by DHCP/PPP on WAN” permite que a OPNsense use os DNS recebidos por DHCP/PPP na WAN. No laboratório faz sentido porque a WAN recebeu IP por DHCP.

2b) O Unbound é o serviço DNS recursivo/cache da OPNsense. DNSSEC valida criptograficamente respostas DNS. Harden DNSSEC torna a validação mais rigorosa. Pode ser ativado, mas pode causar falhas se o upstream DNS ou a hora do sistema estiverem mal configurados.

3a) MAC spoofing permite alterar o MAC address apresentado pela interface. Pode ser útil por compatibilidade, mas também pode ser usado para imitar outro dispositivo.

3b) MTU é o tamanho máximo do pacote numa interface. MSS é o tamanho máximo do segmento TCP. Valores errados podem causar fragmentação ou falhas parciais de conectividade.

3c) PPPoE é usado por alguns ISPs para autenticação de acesso à Internet. PPTP é um protocolo antigo de túnel/VPN e deve ser evitado por ser inseguro.

3d) RFC1918 define redes privadas como 10.0.0.0/8, 172.16.0.0/12 e 192.168.0.0/16. No laboratório, a WAN usa 10.42.0.227, que é RFC1918; por isso bloquear RFC1918 na WAN poderia bloquear a própria rede do laboratório.

3e) Bogon networks são endereços inválidos ou reservados. Bloqueá-los melhora a segurança numa WAN real, mas em laboratório pode causar bloqueios inesperados.

4) Ativei “Use System Nameservers” no Unbound para que a OPNsense use os DNS configurados no sistema como upstream, permitindo ao CT resolver nomes através da firewall.

5) Alterei o DNS server no CT para 192.168.1.1 porque o guião pretendia testar a OPNsense como DNS. Antes, o CT estava a usar 192.168.1.21, que era o Pi-hole. O DHCP funcionava; o problema era apenas o DNS apontar para o servidor errado.
```

**Pergunta de decisão:** queres que eu compacte isto ainda mais para ficar com aspeto de resposta de email, sem explicações longas?

[1]: https://docs.opnsense.org/manual/settingsmenu.html "Settings — OPNsense  documentation"
[2]: https://docs.opnsense.org/manual/unbound.html "Unbound DNS — OPNsense  documentation"
[3]: https://docs.opnsense.org/manual/interfaces.html "Interface configuration — OPNsense  documentation"
[4]: https://docs.opnsense.org/manual/other-interfaces.html "Devices — OPNsense  documentation"
[5]: https://datatracker.ietf.org/doc/html/rfc1918?utm_source=chatgpt.com "RFC 1918 - Address Allocation for Private Internets"
