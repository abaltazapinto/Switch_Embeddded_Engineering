# Aula 2 — Perimeter Protection / Firewalls / Regras / NAT / NGFW

## 1. Reconstrução da aula

### 1.1. Ideia central da aula

A aula foi sobre **proteção de perímetro**: como uma firewall separa zonas de rede, controla tráfego, testa serviços expostos e reduz risco.

A lógica principal foi:

```text
Rede interna / zonas / VLANs
        ↓
Firewall com regras
        ↓
Tráfego permitido, bloqueado, rejeitado, traduzido ou limitado
        ↓
Testes para validar se a configuração está correta
```

A mensagem prática da aula foi: **não basta criar regras; é preciso testar se elas fazem mesmo o que pensávamos que faziam**.

---

### 1.2. Testes de firewall e serviços expostos

A aula começou, nos SRT fornecidos, já numa demonstração prática com ferramentas de análise/pentest.

O professor mostrou que, com poucos comandos/prompts, era possível obter informação sobre dispositivos na rede, por exemplo:

* tipo de equipamento;
* hostname;
* portas abertas;
* serviços ativos;
* versão de firmware;
* versão de software;
* se o acesso é HTTP ou HTTPS;
* se há serviços como MQTT, CoAP, mDNS ou UPnP expostos.

Exemplo discutido:

```text
Shelly Plus 2PM
Firmware: 1.7.4
Porta 80: filtrada
mDNS/Zeroconf: exposto
Sem MQTT, CoAP ou UPnP exposto
```

O ponto importante: mesmo que uma porta esteja filtrada, outros serviços podem revelar informação sensível, como **versão de firmware**.

**Intuição:**
É como uma casa com a porta da frente fechada, mas com uma etiqueta na janela a dizer o modelo da fechadura. A porta não abriu, mas o atacante já aprendeu algo útil.

---

### 1.3. Pen testing com IA + Kali

O professor mostrou a utilização de IA ligada a ferramentas de cibersegurança, como Kali Linux, para automatizar parte da análise.

Foram referidas ferramentas/ações como:

* scan de portas;
* deteção de serviços;
* análise de versões;
* Nikto;
* Gobuster;
* Nmap;
* pesquisa posterior por vulnerabilidades/exploits.

A ideia não foi ensinar pentest avançado, mas mostrar que hoje é **muito fácil obter informação inicial** sobre sistemas.

Ponto ético/legal muito reforçado:

> Só se devem correr estas ferramentas em sistemas próprios ou com autorização explícita.

O professor distinguiu:

* analisar os próprios sistemas: aceitável;
* atacar sistemas de terceiros: ilegal;
* investigar firmware de um dispositivo próprio: zona cinzenta, mas com responsabilidade moral de reportar falhas encontradas.

---

### 1.4. Exemplo Home Assistant

Outro exemplo foi um servidor Home Assistant.

Foi detetado:

* Linux;
* SSH aberto;
* DNS aberto;
* RPCbind aberto;
* Home Assistant na porta 8123;
* serviço HTTP;
* Python/aiohttp;
* ausência de HTTPS.

O problema principal não era apenas “a porta está aberta”. O problema era:

```text
Home Assistant acessível via HTTP
→ tráfego sem cifra
→ credenciais/tokens podem ficar expostos se houver acesso fora da rede segura
```

O professor também mostrou que Gobuster encontrou rotas como:

* `/app`
* `/config`
* `/home`
* `/history`
* `/map`
* `/profile`
* `/security`

Mas explicou que, por ser uma aplicação SPA, várias rotas podem devolver o mesmo ficheiro principal. Isso não significa automaticamente que tudo está vulnerável, mas indica que há superfícies a verificar.

---

### 1.5. Tipos de regras de firewall

A aula classificou regras de firewall em quatro grupos principais:

| Tipo de regra                | Função                                                             |
| ---------------------------- | ------------------------------------------------------------------ |
| **Access rules**             | Permitem, bloqueiam ou rejeitam tráfego por IP, porta ou protocolo |
| **Stateful filtering rules** | Consideram o estado da ligação                                     |
| **NAT rules**                | Traduzem endereços IP/portas                                       |
| **Traffic shaping / QoS**    | Controlam largura de banda/prioridade                              |

---

### 1.6. Regras de acesso: pass, block, reject

As ações principais são:

| Ação       | Significado                        |
| ---------- | ---------------------------------- |
| **Pass**   | permite o tráfego                  |
| **Block**  | bloqueia silenciosamente           |
| **Reject** | bloqueia e avisa quem tentou ligar |

O professor explicou que, teoricamente, `block` revela menos informação do que `reject`. Mas ferramentas modernas como Nmap ainda podem perceber que algo está filtrado.

**Intuição:**

```text
Pass   = porta abre
Block  = ninguém responde
Reject = alguém responde: “não podes entrar”
```

---

### 1.7. Stateless vs Stateful

Uma regra **stateless** olha para cada pacote isoladamente.

Uma regra **stateful** lembra-se do estado da ligação.

Exemplo mental:

```text
Stateless:
“Este pacote é permitido?” 
Pergunta feita para cada pacote.

Stateful:
“Esta ligação já foi autorizada antes?”
Se sim, continua a deixar passar.
```

A aula reforçou que muitas regras modernas são stateful por defeito.

---

### 1.8. Ordem das regras

As regras são avaliadas sequencialmente, de cima para baixo.

Isto é crítico:

```text
Regra 1: permitir tudo
Regra 2: bloquear SSH
```

Neste caso, a regra 2 pode nunca ser aplicada, porque a regra 1 já permitiu o tráfego.

Ordem referida nos slides/aula:

1. system rules;
2. floating rules;
3. interface groups;
4. interface rules.

Ideia essencial: **uma regra certa no sítio errado pode não fazer nada**.

---

### 1.9. Checklist para construção de regras

A aula referiu uma checklist inspirada no SANS Institute:

| Categoria            | Objetivo                                                              |
| -------------------- | --------------------------------------------------------------------- |
| **Anti-spoofing**    | impedir tráfego com IP de origem falso ou inválido                    |
| **User rules**       | permitir acesso normal dos utilizadores a serviços                    |
| **Management rules** | proteger acessos administrativos                                      |
| **Noise rules**      | limitar tráfego desnecessário, como routing dinâmico fora do contexto |
| **Alert rules**      | gerar alertas em tentativas relevantes                                |
| **Log rules**        | registar eventos para análise posterior                               |

O professor deu muita importância a **logs e alertas**, porque sem eles não se valida se a regra está a funcionar.

---

### 1.10. Anti-spoofing e IP spoofing

**IP spoofing** é alterar o IP de origem no pacote.

Objetivo possível:

```text
Atacante externo
→ falsifica IP de origem
→ tenta parecer tráfego interno ou de outra vítima
```

Foi ligado a ataques DDoS.

No DDoS, a ideia não é necessariamente “entrar” no sistema. Muitas vezes é apenas:

```text
encher a firewall / servidor de tráfego
→ consumir recursos
→ impedir funcionamento normal
```

---

### 1.11. Inbound vs outbound

Um ponto importante da aula: **inbound e outbound são vistos do ponto de vista da firewall/interface**, não do ponto de vista psicológico do utilizador.

| Direção            | Ideia                                         |
| ------------------ | --------------------------------------------- |
| **Inbound / IN**   | tráfego que entra numa interface da firewall  |
| **Outbound / OUT** | tráfego que sai por uma interface da firewall |

Erro comum: achar que inbound significa sempre “internet para dentro da empresa”. Nem sempre. Depende da interface/zona onde a regra está aplicada.

---

### 1.12. WAN não é “a Internet”

O professor reforçou:

```text
WAN interface ≠ Internet inteira
```

A WAN é apenas a interface da firewall virada para o operador ou ligação externa.

Permitir tráfego para a interface WAN não é a mesma coisa que permitir acesso livre à Internet.

---

### 1.13. Zonas, sub-redes e segmentação

A aula insistiu muito na ideia de **segmentar redes**.

Exemplos dados:

* rede de gestão;
* rede IoT;
* rede de convidados/hotspot;
* rede de servidores Proxmox;
* rede segregada;
* rede de POS num café;
* dispositivos embebidos isolados.

Ideia principal:

```text
Sub-rede = bloco técnico de IPs
Zona = grupo lógico de redes com o mesmo nível/função de segurança
```

Exemplo:

```text
VLAN IoT + VLAN sensores + VLAN câmaras
→ podem estar agrupadas numa zona “IoT”
```

A vantagem é criar regras por nível de segurança, não apenas por IP.

---

### 1.14. Rede de gestão

A rede de gestão deve ser separada da rede normal.

Exemplo do professor:

```text
Clientes / convidados
→ não devem conseguir aceder à firewall, Proxmox, POS, Home Assistant, etc.
```

Num café, por exemplo:

```text
Wi-Fi dos clientes
→ não deve aceder aos POS
```

Mesmo que os POS sejam “pequenos equipamentos”, devem ser tratados como sistemas críticos.

---

### 1.15. Complexidade vs segurança

A aula teve uma ideia de engenharia muito importante:

```text
Mais segmentação pode aumentar segurança,
mas também aumenta complexidade.
```

Se a rede ficar demasiado complexa:

* há mais regras;
* há mais exceções;
* há mais testes necessários;
* há maior probabilidade de erro;
* fica mais difícil provar que a configuração está correta.

Isto é raciocínio de engenharia: segurança não é só “fechar tudo”; é equilibrar risco, operação, custo e manutenção.

---

### 1.16. NAT

NAT significa **Network Address Translation**.

Serve para traduzir endereços entre redes, normalmente:

```text
IP público
↔
vários IPs privados
```

Exemplo doméstico:

```text
Router com IP público
→ traduz tráfego para vários dispositivos internos:
   192.168.1.10
   192.168.1.11
   192.168.1.12
```

A aula também referiu **CG-NAT**, quando o operador também usa IPs privados do lado dele.

Impacto prático: em alguns operadores pode ser mais difícil expor serviços internos, fazer port forwarding ou usar router próprio.

---

### 1.17. DNAT / Port forwarding

Port forwarding é uma forma de Destination NAT.

Exemplo:

```text
Pedido chega à WAN na porta 8123
→ firewall redireciona para
→ 192.168.13.101:8123
```

Isto permite expor um serviço interno para fora.

Risco: se o serviço interno estiver mal protegido, acabámos de criar uma entrada para a rede.

---

### 1.18. SNAT / Outbound NAT

SNAT é o caso inverso: tráfego que sai da rede privada para fora.

Exemplo:

```text
192.168.1.20 quer ir à Internet
→ firewall troca origem para o IP público
→ resposta volta à firewall
→ firewall devolve ao cliente interno
```

A aula não aprofundou muito isto; foi apresentado como algo que a firewall normalmente trata automaticamente.

---

### 1.19. UPnP

UPnP apareceu como ponto crítico.

UPnP permite que um cliente crie regras automaticamente na firewall.

Exemplo perigoso:

```text
Um dispositivo interno
→ pede à firewall: “abre esta porta para mim”
→ firewall cria port forwarding
→ utilizador nem percebe
```

O professor foi claro: isto é perigoso, especialmente em IoT.

Resumo:

```text
UPnP facilita funcionamento
mas reduz controlo
e pode abrir buracos sem o administrador reparar
```

---

### 1.20. Traffic shaping / QoS

Traffic shaping e QoS servem para controlar a qualidade ou prioridade do tráfego.

Conceitos:

| Conceito         | Significado                                                      |
| ---------------- | ---------------------------------------------------------------- |
| **Pipe**         | descrição da ligação: largura de banda, atraso, perda de pacotes |
| **Flow**         | tipo de tráfego, normalmente por porta/protocolo                 |
| **Queue / peso** | prioridade relativa desse tráfego                                |

Exemplo:

```text
Videochamada
→ mais prioridade

Download pesado
→ menos prioridade
```

O professor chamou atenção para o upload: em muitos cenários, o problema não é o download, mas sim o upload.

---

### 1.21. Regras auxiliares: floating rules e aliases

**Floating rules**: regras aplicadas independentemente da sub-rede/interface específica.

Boa ideia quando se quer evitar repetir a mesma regra em muitas VLANs.

**Aliases**: nomes simbólicos para IPs, redes ou grupos.

Exemplo:

```text
192.168.13.101
→ HOME_ASSISTANT
```

Isto reduz erro humano.

---

### 1.22. Bloqueios regionais e análise de risco

A aula discutiu bloqueios por país, por exemplo China/Rússia.

O professor não apresentou isto como regra universal. Pelo contrário: explicou como **análise de risco**.

Pergunta central:

```text
O que ganho em bloquear?
O que perco em funcionalidade?
Quanto trabalho extra crio?
```

Também foi discutido que bloqueios regionais podem ser contornados com VPN ou túneis. Logo, não são proteção absoluta.

---

### 1.23. Segurança pessoal vs segurança corporativa

Houve uma discussão sobre produtos como antivírus/firewalls pessoais.

A posição do professor foi crítica:

* podem dar falsa sensação de segurança;
* consomem recursos;
* muitas ameaças atuais envolvem comportamento do utilizador;
* safe browsing e boas práticas continuam fundamentais.

Mas também distinguiu o contexto pessoal do corporativo.

Em contexto empresarial, pode fazer sentido usar soluções mais completas, políticas, logs, análise comportamental e NGFW.

---

### 1.24. Next Generation Firewall

A aula terminou com NGFW.

A ideia principal:

```text
NGFW = firewall com capacidades extra de inspeção,
controlo de aplicações, análise comportamental e prevenção de intrusões.
```

Capacidades referidas:

* application control;
* URL filtering;
* website access control;
* phishing/malicious site blocking;
* cloud threat intelligence;
* análise de JavaScript malicioso;
* políticas por utilizador/grupo;
* traffic analysis;
* DPI;
* inspeção de tráfego cifrado em alguns casos;
* prevenção de ataques;
* controlo de dispositivos.

Mas o professor reforçou o custo:

```text
Mais inspeção
→ mais CPU
→ mais memória
→ mais licenças
→ mais complexidade
```

---

## 2. Explicação simples das partes difíceis

### Firewall não é “um muro mágico”

Uma firewall não sabe automaticamente o que é bom ou mau. Ela aplica regras.

```text
Regra bem pensada + logs + testes
→ proteção útil

Regra mal pensada
→ falsa segurança
```

---

### Porta aberta, fechada e filtrada

| Estado   | Intuição                            |
| -------- | ----------------------------------- |
| Aberta   | há serviço a responder              |
| Fechada  | não há serviço, mas o host responde |
| Filtrada | algo bloqueia ou ignora o pedido    |

Uma porta filtrada é melhor do que aberta, mas não significa que o sistema esteja invisível.

---

### NAT não é segurança por si só

NAT esconde a rede interna, mas a sua função principal é tradução de endereços.

Quando fazemos port forwarding, criamos uma exceção:

```text
Antes:
Internet não chega diretamente ao serviço interno

Depois do port forwarding:
Internet pode chegar ao serviço interno
```

---

### Zonas são agrupamentos por risco

Uma zona é uma forma de dizer:

```text
“Estes dispositivos têm risco/função semelhante,
logo podem partilhar regras parecidas.”
```

Exemplo:

```text
IoT separado de laptops pessoais
convidados separados de servidores
POS separado de Wi-Fi público
```

---

### NGFW não é grátis em recursos

NGFW parece melhor, mas custa:

* CPU;
* memória;
* dinheiro;
* complexidade;
* falsos positivos;
* necessidade de manutenção.

---

## 3. Problemas, inconsistências e correções

### 3.1. Termos mal transcritos no SRT

| No SRT aparece                       | Correto                         |
| ------------------------------------ | ------------------------------- |
| farololo / farolô                    | firewall                        |
| Cali                                 | Kali Linux                      |
| Shell iPlus 2PM                      | Shelly Plus 2PM                 |
| MKTT                                 | MQTT                            |
| co-op                                | CoAP                            |
| universal play-in-play / plugin play | UPnP — Universal Plug and Play  |
| macista                              | Home Assistant                  |
| porto 8.823 / 1123                   | porta 8123                      |
| Sands Institute                      | SANS Institute                  |
| topaz factor authentication          | two-factor authentication / 2FA |
| Aregard                              | WireGuard                       |
| F2W                                  | UFW — Uncomplicated Firewall    |

---

### 3.2. Correções técnicas importantes

| Tema            | Correção                                                                      |
| --------------- | ----------------------------------------------------------------------------- |
| IPv4            | IPv4 tem **32 bits**, organizados em **4 octetos de 8 bits**                  |
| IPv6            | IPv6 tem **128 bits**, não 128 bytes                                          |
| WAN             | WAN não significa “Internet inteira”; é a interface externa da firewall       |
| Block vs reject | `block` não responde; `reject` responde; mas scanners podem inferir filtragem |
| UPnP            | facilita conectividade, mas pode abrir portas sem controlo explícito          |

---

### 3.3. Partes não claramente cobertas no SRT

A parte inicial dos slides sobre evolução histórica da firewall aparece no PDF, mas **não está claramente coberta nos SRT fornecidos**.

Inclui:

* border router;
* origem histórica do termo firewall;
* evolução 1988 → 2018;
* firewall as a service.

Pode sair como contexto, mas nos SRT fornecidos a aula prática focou muito mais:

```text
testes → regras → NAT → zonas → QoS → NGFW
```

---

## 4. Resumo para escrever à mão em 30 minutos

## Aula 2 — Perimeter Protection

### Ideia base

* Firewall controla tráfego entre redes/zonas.
* Segurança vem de:

  * regras bem feitas;
  * segmentação;
  * logs;
  * alertas;
  * testes.
* Não basta configurar: é preciso validar.

---

### Testes de firewall

* Usar scans para descobrir:

  * portas abertas;
  * serviços;
  * versões;
  * firmware;
  * HTTP/HTTPS;
  * serviços expostos.
* Ferramentas referidas:

  * Nmap;
  * Nikto;
  * Gobuster;
  * Kali;
  * IA como apoio.
* Só testar sistemas próprios ou autorizados.

---

### Estados de portas

* Aberta: serviço responde.
* Fechada: host responde, mas não há serviço.
* Filtrada: firewall bloqueia/ignora.

---

### Tipos de regras

* Access rules:

  * permitem/bloqueiam/rejeitam tráfego.
* Stateful rules:

  * consideram estado da ligação.
* NAT rules:

  * traduzem IPs/portas.
* Traffic shaping/QoS:

  * controlam prioridade/banda.

---

### Ações de firewall

* Pass: permite.
* Block: bloqueia sem avisar.
* Reject: bloqueia e avisa.

---

### Stateless vs Stateful

* Stateless:

  * cada pacote é avaliado sozinho.
* Stateful:

  * firewall lembra ligações autorizadas.
* Stateful é comum em firewalls modernas.

---

### Ordem das regras

* Regras lidas de cima para baixo.
* Primeira regra aplicável vence.
* Ordem errada pode anular regras boas.
* Existem:

  * system rules;
  * floating rules;
  * interface groups;
  * interface rules.

---

### Checklist SANS

* Anti-spoofing:

  * impedir IPs falsificados.
* User rules:

  * acessos de utilizadores.
* Management rules:

  * acessos administrativos.
* Noise rules:

  * reduzir tráfego desnecessário.
* Alert rules:

  * gerar alertas.
* Log rules:

  * guardar eventos.

---

### IP spoofing e DDoS

* IP spoofing:

  * falsificar IP de origem.
* DDoS:

  * sobrecarregar alvo/firewall.
* Objetivo pode ser indisponibilidade, não invasão.

---

### Inbound / Outbound

* IN:

  * entra na interface da firewall.
* OUT:

  * sai da interface da firewall.
* Sempre pensar do ponto de vista da firewall.

---

### WAN

* WAN é interface externa.
* WAN não é igual a Internet inteira.
* Regra para WAN não significa regra para toda a Internet.

---

### Zonas

* Zona = grupo lógico de redes.
* Usada por função/risco.
* Exemplos:

  * IoT;
  * gestão;
  * convidados;
  * servidores;
  * POS.
* Segmentação reduz impacto de falhas.

---

### Rede de gestão

* Deve ser isolada.
* Só administradores devem aceder.
* Convidados/clientes não devem aceder a:

  * firewall;
  * Proxmox;
  * POS;
  * Home Assistant;
  * servidores.

---

### NAT

* NAT traduz IPs.
* Normalmente:

  * IP público ↔ IPs privados.
* CG-NAT:

  * operador também usa NAT.

---

### DNAT / Port forwarding

* Entrada externa redirecionada para serviço interno.
* Exemplo:

  * WAN:8123 → 192.168.13.101:8123.
* Risco:

  * expõe serviço interno.

---

### SNAT

* Tradução para tráfego de saída.
* Normalmente automática na firewall.

---

### UPnP

* Permite clientes criarem regras NAT automaticamente.
* Risco:

  * abrir portas sem o administrador saber.
* Em IoT é especialmente perigoso.

---

### Traffic shaping / QoS

* Controla prioridade e largura de banda.
* Pipe:

  * descrição da ligação.
* Flow:

  * tipo de tráfego.
* Queue/peso:

  * prioridade relativa.

---

### Floating rules e aliases

* Floating rules:

  * regras independentes da subnet.
* Aliases:

  * nomes para IPs/redes/serviços.
* Reduzem repetição e erro humano.

---

### Análise de risco

* Não há regra universal.
* Segurança exige equilíbrio:

  * risco;
  * custo;
  * usabilidade;
  * operação;
  * manutenção.
* Bloqueios regionais ajudam, mas podem ser contornados.

---

### NGFW

* Firewall com capacidades extra:

  * application control;
  * URL filtering;
  * phishing protection;
  * DPI;
  * políticas por utilizador;
  * análise comportamental.
* Custo:

  * CPU;
  * memória;
  * licenças;
  * complexidade.

---

## 5. Conceitos difíceis — modelo mental simples

### 5.1. Stateful firewall

Modelo mental:

```text
Segurança de um prédio com lista de visitantes.
```

Se a pessoa já entrou com autorização, a segurança reconhece a continuação da visita. Não precisa validar tudo do zero a cada segundo.

---

### 5.2. NAT

Modelo mental:

```text
Uma empresa tem um número de telefone principal
e várias extensões internas.
```

De fora só se vê o número principal. Internamente há muitos dispositivos.

---

### 5.3. Port forwarding

Modelo mental:

```text
“Tudo o que chegar ao número principal na extensão X
vai diretamente para esta sala interna.”
```

É útil, mas perigoso se essa sala não estiver protegida.

---

### 5.4. Zonas

Modelo mental:

```text
Dividir um edifício por áreas:
visitantes, funcionários, administração, sala de servidores.
```

Cada área tem permissões diferentes.

---

### 5.5. NGFW

Modelo mental:

```text
Firewall normal olha para morada e porta.
NGFW tenta olhar também para comportamento e conteúdo.
```

Mas isso exige mais processamento.

---

## 6. Essential Exam Questions — 5 perguntas

### Conceptual 1

**Pergunta:**
Qual é a diferença entre firewall stateless e stateful?

**Resposta:**
A stateless avalia cada pacote isoladamente. A stateful mantém informação sobre o estado das ligações.

**Raciocínio:**
A stateful sabe se uma ligação já foi autorizada; a stateless não tem essa memória.

---

### Conceptual 2

**Pergunta:**
Porque é que segmentar IoT numa zona própria melhora a segurança?

**Resposta:**
Porque limita o impacto caso um dispositivo IoT seja comprometido.

**Raciocínio:**
O atacante pode chegar ao dispositivo IoT, mas não deve conseguir saltar livremente para servidores, laptops ou rede de gestão.

---

### Practical 1

**Pergunta:**
Um scan mostra a porta 8123 aberta em HTTP num Home Assistant. Qual é o principal risco?

**Resposta:**
Tráfego sem HTTPS pode expor credenciais ou tokens se for acessível fora de uma rede controlada.

**Raciocínio:**
HTTP não cifra o tráfego; HTTPS ou reverse proxy com TLS reduzem esse risco.

---

### Practical 2

**Pergunta:**
Porque é perigoso deixar UPnP ativo numa rede com dispositivos IoT?

**Resposta:**
Porque dispositivos podem criar regras de port forwarding automaticamente sem o administrador perceber.

**Raciocínio:**
Isto pode abrir portas na firewall e expor serviços internos.

---

### Multiple Choice

**Pergunta:**
Qual ação de firewall bloqueia tráfego sem informar explicitamente o cliente?

A. Pass
B. Reject
C. Block
D. NAT

**Resposta:**
C. Block

**Raciocínio:**
`Block` descarta silenciosamente; `Reject` avisa que o tráfego foi rejeitado.

---

## 7. Common Pitfalls

### 1. Confundir WAN com Internet

WAN é a interface externa da firewall. Não é sinónimo de “toda a Internet”.

---

### 2. Confundir inbound/outbound

IN e OUT devem ser pensados do ponto de vista da interface/firewall, não apenas do ponto de vista do utilizador.

---

### 3. Achar que NAT é segurança suficiente

NAT ajuda a esconder a rede interna, mas não substitui regras corretas, segmentação e testes.

---

### 4. Criar muitas zonas sem capacidade de testar

Mais zonas podem melhorar segurança, mas também aumentam complexidade. Sem testes e logs, a rede pode ficar impossível de validar.

---

### 5. Deixar UPnP ativo por conveniência

UPnP facilita jogos/IoT, mas pode abrir portas automaticamente. Em redes sérias, deve ser tratado como risco elevado.
