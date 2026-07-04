# Estudo do Guião 4 — Confiabilidade e Cibersegurança

**Tema central:** construção de **regras de acesso** e **regras NAT** numa firewall OPNsense.

Este guião não é só “clicar em regras”. O objetivo é perceber **quem pode falar com quem**, **por que interface entra o tráfego**, **que regra deixa passar**, e **quando o NAT altera o destino ou a origem do pacote**. A estrutura segue o formato de estudo que pediste: execução separada da interpretação, comandos explicados, troubleshooting e resumo para imprimir. 

---

## 1. Ideia central do guião

O Guião 4 ensina a usar a OPNsense como firewall entre várias redes:

```text
ubuntu1 / LAN      → protegido atrás da firewall
ubuntu2 / LAN2     → nova rede criada no guião
ubuntuWAN / WAN    → simula máquina exterior
OPNsense           → decide o que passa, bloqueia ou traduz
```

A grande dificuldade é esta:

> **Firewall rule** decide se o pacote passa.
> **NAT rule** muda endereço ou porta do pacote.
> Para acesso vindo da WAN para um servidor interno, normalmente precisas dos dois.

Na OPNsense, as regras são avaliadas por ordem; com regras “quick”, a primeira regra que faz match ganha. Além disso, regras NAT são processadas antes das regras de filtro/firewall. Isto é fundamental para explicar NAT na avaliação. ([OPNsense Documentation][1])

---

## 2. O que este guião quer provar

O guião quer provar quatro coisas:

| Parte               | O que estás a provar                                                                              |
| ------------------- | ------------------------------------------------------------------------------------------------- |
| Nova interface LAN2 | A firewall pode ter mais do que uma rede interna                                                  |
| Regras de acesso    | Uma rede só comunica se houver regra que permita                                                  |
| NAT / Port Forward  | Um host externo pode aceder a um servidor interno através da firewall                             |
| DNS forcing         | Mesmo que o cliente tente usar outro DNS, a firewall pode redirecionar pedidos DNS para o Unbound |

Frase-base para avaliação:

> Neste guião estou a demonstrar que a firewall controla o tráfego entre redes diferentes. As regras de acesso definem o que é permitido ou bloqueado, enquanto o NAT permite traduzir endereços/portas para publicar serviços internos ou forçar destinos específicos, como DNS.

---

## 3. Topologia / cenário usado

### Topologia lógica

```text
                Internet / WAN
                    |
              [ OPNsense WAN ]
                    |
        -----------------------------
        |                           |
   [ LAN / vmbr1 ]             [ LAN2 / nova bridge ]
        |                           |
    ubuntu1                    ubuntu2
 Apache2                    Apache2
```

### Atenção importante

O guião manda criar uma bridge nova chamada `vmbr4`, mas depois diz para colocar `ubuntu2` no `vmbr2`.

Isto é uma possível inconsistência.

**Como pensar:**

O importante não é o número da bridge. O importante é isto:

```text
ubuntu2 tem de estar ligado à mesma bridge que a interface LAN2 da OPNsense.
```

Portanto:

| Se LAN2 da OPNsense está em... | ubuntu2 deve estar em... |
| ------------------------------ | ------------------------ |
| `vmbr4`                        | `vmbr4`                  |
| `vmbr2`                        | `vmbr2`                  |

Se estiverem em bridges diferentes, o DHCP da LAN2 não chega ao ubuntu2.

---

## 4. Conceitos necessários antes de executar

### Conceito: Interface de firewall

**Ideia simples:**
Uma interface é uma “porta de rede” da firewall.

**Analogia:**
Imagina a firewall como uma portaria de um edifício. Cada interface é uma porta: WAN, LAN, LAN2.

**Na prática do guião:**
Criar `LAN2` significa dar à OPNsense uma nova rede interna.

**Como explicar ao professor:**

> Uma interface representa uma rede ligada à firewall. Ao criar LAN2, crio uma nova zona de rede com IP próprio, gateway próprio e regras próprias.

---

### Conceito: DHCP

**Ideia simples:**
DHCP dá IP automaticamente aos clientes.

**Analogia:**
É como uma receção que entrega número de quarto aos hóspedes.

**Na prática do guião:**
LAN2 precisa de DHCP para o ubuntu2 receber IP, gateway e DNS.

**Como explicar ao professor:**

> O DHCP permite que os clientes da LAN2 recebam configuração IP automaticamente, incluindo endereço, gateway e DNS.

---

### Conceito: Regras de firewall

**Ideia simples:**
Uma regra diz se um pacote pode passar ou não.

**Analogia:**
É uma lista de permissões da portaria: “este pode entrar”, “este não pode”.

**Na prática do guião:**
ubuntu2 inicialmente não tem Internet porque a LAN2 ainda não tem regras permissivas.

**Como explicar ao professor:**

> As regras de firewall controlam tráfego por interface, origem, destino, protocolo e porta.

Na OPNsense, a política normalmente é aplicada na interface onde o tráfego entra. Por exemplo, tráfego vindo de LAN2 deve ser permitido ou bloqueado nas regras da LAN2. ([OPNsense Documentation][1])

---

### Conceito: NAT

**Ideia simples:**
NAT altera endereços ou portas dos pacotes.

**Analogia:**
É como uma receção que recebe cartas dirigidas ao edifício e as encaminha para uma sala interna.

**Na prática do guião:**
Um container na WAN tenta aceder ao Apache do ubuntu1, que está atrás da firewall. Para isso, crias um port forward.

**Como explicar ao professor:**

> O NAT permite traduzir tráfego destinado ao IP externo da firewall para um IP interno, por exemplo WAN:8080 para ubuntu1:80.

A documentação da OPNsense descreve NAT como mecanismo para separar redes internas e externas e partilhar ou redirecionar endereços. No caso de port forwarding, uma ligação para o IP externo da firewall é redirecionada para um host interno. ([OPNsense Documentation][2])

---

### Conceito: Port Forward / Destination NAT

**Ideia simples:**
Uma porta da firewall aponta para uma porta de uma máquina interna.

```text
WAN_IP:8080  →  ubuntu1_IP:80
```

**Analogia:**
Tocas à campainha 8080 do prédio; a receção encaminha-te para o quarto 80 do ubuntu1.

**Na prática do guião:**
Container na WAN carrega uma página web alojada no ubuntu1.

**Como explicar ao professor:**

> O port forward altera o destino do pacote: de IP/porta da firewall para IP/porta do servidor interno.

---

### Conceito: DNS forcing

**Ideia simples:**
Mesmo que o cliente tente usar `8.8.8.8`, a firewall apanha pedidos DNS na porta 53 e manda-os para o Unbound.

**Analogia:**
O aluno tenta entregar o pedido a outro professor, mas a portaria redireciona tudo para o professor oficial.

**Na prática do guião:**
Criar uma regra NAT que redireciona todos os pedidos DNS para o Unbound da OPNsense.

**Como explicar ao professor:**

> DNS forcing impede clientes de contornarem o resolver definido pela rede, redirecionando tráfego TCP/UDP 53 para o DNS controlado pela firewall.

---

## 5. Procedimento explicado passo a passo

## Etapa 0 — Backup da OPNsense

### Execução

Antes de alterar interfaces e regras:

```text
OPNsense → System → Configuration → Backups
```

Exportar configuração.

### Interpretação

Isto não prova segurança diretamente. Prova boa prática operacional: antes de alterar firewall, guardas estado conhecido.

| Campo              | Explicação                   |
| ------------------ | ---------------------------- |
| Etapa              | Backup                       |
| Objetivo           | Poder reverter erros         |
| Conceito           | Gestão de configuração       |
| Ação prática       | Exportar backup              |
| Comandos           | Não aplicável                |
| Resultado esperado | Ficheiro XML de configuração |
| Interpretação      | Tens ponto de recuperação    |
| Erros comuns       | Fazer alterações sem backup  |

> Nesta etapa estou a proteger a configuração da firewall.
> O resultado esperado é ter um backup exportado.
> Se uma regra bloquear acesso, posso restaurar.
> Em segurança, isto demonstra controlo de mudanças.

---

## Etapa 1 — Criar nova bridge no Proxmox

### Execução

No Proxmox:

```text
Datacenter / Node → System → Network → Create → Linux Bridge
Nome: vmbr4
```

Depois adicionar nova placa de rede à VM OPNsense:

```text
OPNsense VM → Hardware → Add → Network Device
Bridge: vmbr4
Model: VirtIO
```

### Interpretação

Isto cria uma nova rede virtual isolada.

| Campo              | Explicação                                       |
| ------------------ | ------------------------------------------------ |
| Etapa              | Criar `vmbr4`                                    |
| Objetivo           | Criar nova rede virtual                          |
| Conceito           | Bridge / segmentação                             |
| Ação prática       | Criar bridge e ligar à OPNsense                  |
| Comandos           | Feito via GUI Proxmox                            |
| Resultado esperado | OPNsense vê nova interface                       |
| Interpretação      | Há uma nova rede que pode tornar-se LAN2         |
| Erros comuns       | Adicionar bridge ao container mas não à firewall |

> Nesta etapa estou a criar uma nova zona de rede.
> O resultado esperado é a OPNsense detetar uma nova interface.
> Se não aparecer, significa que a placa não foi adicionada ou a VM precisa de reinício.
> Em segurança, isto demonstra segmentação de rede.

---

## Etapa 2 — Configurar LAN2 na OPNsense

### Execução

Na OPNsense:

```text
Interfaces → Assignments
Adicionar nova interface
Enable interface
Description: LAN2
```

Depois:

```text
Interfaces → LAN2
Enable
IPv4 Configuration Type: Static IPv4
IPv4 address: exemplo 192.168.20.1/24
```

Este IP será a gateway da LAN2.

### Interpretação

A firewall passa a ser o router/gateway da nova rede.

| Campo              | Explicação                                     |
| ------------------ | ---------------------------------------------- |
| Etapa              | Configurar LAN2                                |
| Objetivo           | Dar IP à nova rede                             |
| Conceito           | Gateway / interface L3                         |
| Ação prática       | Atribuir IP estático à LAN2                    |
| Comandos           | GUI OPNsense                                   |
| Resultado esperado | LAN2 ativa com IP                              |
| Interpretação      | Clientes LAN2 podem usar OPNsense como gateway |
| Erros comuns       | Usar subrede igual à LAN ou WAN                |

> Nesta etapa estou a transformar uma placa de rede numa interface roteável.
> O resultado esperado é a LAN2 ter IP próprio.
> Se usar a mesma subrede da LAN, há conflito de routing.
> Em segurança, isto demonstra separação entre redes.

---

## Etapa 3 — Ativar DHCP na LAN2

### Execução

```text
Services → ISC DHCPv4 → LAN2
Enable DHCP server
Range: exemplo 192.168.20.100 - 192.168.20.200
DNS server: IP da firewall ou DNS indicado pelo professor
Gateway: LAN2 address
```

### Interpretação

O ubuntu2 deve receber IP automaticamente.

| Campo              | Explicação                        |
| ------------------ | --------------------------------- |
| Etapa              | DHCP LAN2                         |
| Objetivo           | Dar IP automático ao ubuntu2      |
| Conceito           | DHCP                              |
| Ação prática       | Ativar range DHCP                 |
| Comandos           | GUI OPNsense                      |
| Resultado esperado | ubuntu2 recebe IP da LAN2         |
| Interpretação      | LAN2 está operacional ao nível IP |
| Erros comuns       | Range fora da subrede             |

> Nesta etapa estou a testar se a LAN2 consegue configurar clientes.
> O resultado esperado é o ubuntu2 receber IP, gateway e DNS.
> Se não receber IP, a bridge/interface está errada ou o DHCP não está ativo.
> Em segurança, isto demonstra controlo centralizado da rede.

---

## Etapa 4 — Ligar ubuntu1 e ubuntu2 às redes corretas

### Execução

No Proxmox:

```text
ubuntu1 → bridge LAN/vmbr1
ubuntu2 → bridge LAN2/vmbr4 ou a bridge realmente usada pela LAN2
```

Dentro de cada container:

```bash
ip a
ip r
cat /etc/resolv.conf
```

### Interpretação

Aqui estás a confirmar identidade de rede.

| Campo              | Explicação                                     |
| ------------------ | ---------------------------------------------- |
| Etapa              | Confirmar IPs                                  |
| Objetivo           | Saber quem está em que rede                    |
| Conceito           | Endereço IP / rota / DNS                       |
| Ação prática       | Ver IP, gateway e DNS                          |
| Comandos           | `ip a`, `ip r`, `cat /etc/resolv.conf`         |
| Resultado esperado | IPs de subredes diferentes                     |
| Interpretação      | ubuntu1 e ubuntu2 estão separados por firewall |
| Erros comuns       | Ambos ficarem na mesma bridge                  |

> Nesta etapa estou a confirmar se cada máquina está na rede certa.
> O resultado esperado é ubuntu1 numa subrede e ubuntu2 noutra.
> Se ambos tiverem IP da mesma rede, não estou a testar firewall entre redes.
> Em segurança, isto demonstra isolamento entre zonas.

---

## Etapa 5 — Confirmar Internet em ubuntu1 e falha inicial em ubuntu2

### Execução

No ubuntu1:

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

No ubuntu2:

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

### Interpretação

O guião espera:

```text
ubuntu1 → consegue Internet
ubuntu2 → inicialmente não consegue Internet
```

Isto acontece porque a LAN normalmente já tem regra permissiva, mas LAN2 ainda não.

> Nesta etapa estou a comparar uma interface já configurada com uma nova interface sem regras suficientes.
> O resultado esperado é ubuntu1 conseguir Internet e ubuntu2 falhar.
> Se ubuntu2 falhar, significa provavelmente falta de regra LAN2 ou NAT outbound.
> Em segurança, isto demonstra que uma nova rede não deve ter permissões por defeito.

---

## Etapa 6 — Criar regra de acesso para LAN2 ter Internet

### Execução

Na OPNsense:

```text
Firewall → Rules → LAN2 → Add
Action: Pass
Interface: LAN2
Direction: In
Protocol: any
Source: LAN2 net
Destination: any
Description: Allow LAN2 to Internet
```

Aplicar alterações.

### Interpretação

Esta regra permite que tráfego originado na LAN2 entre na firewall e siga para outras redes.

| Campo              | Explicação                               |
| ------------------ | ---------------------------------------- |
| Etapa              | Regra LAN2 → Internet                    |
| Objetivo           | Permitir saída da LAN2                   |
| Conceito           | Firewall rule                            |
| Ação prática       | Criar regra Pass                         |
| Comandos           | GUI                                      |
| Resultado esperado | ubuntu2 passa a ter Internet             |
| Interpretação      | A firewall agora permite tráfego da LAN2 |
| Erros comuns       | Criar regra na WAN em vez da LAN2        |

> Nesta etapa estou a testar se a firewall permite tráfego originado na LAN2.
> O resultado esperado é o ubuntu2 passar a conseguir ping/curl para Internet.
> Se continuar sem Internet, verifico regra, gateway, DNS e NAT outbound.
> Em segurança, isto demonstra controlo explícito de permissões.

---

## Etapa 7 — Instalar Apache2 nos dois containers

### Execução

Em ubuntu1 e ubuntu2:

```bash
apt update
apt install apache2 -y
```

Confirmar serviço:

```bash
systemctl status apache2
```

Se for container sem systemd:

```bash
service apache2 status
```

Confirmar IP:

```bash
hostname -I
```

### Interpretação

Agora cada container passa a ser um servidor web.

> Nesta etapa estou a criar um serviço visível na rede.
> O resultado esperado é a porta 80 estar ativa.
> Se o Apache não estiver ativo, o problema não é firewall; é serviço parado.
> Em segurança, isto separa problema de rede de problema de aplicação.

---

## Etapa 8 — Testar ubuntu1 → ubuntu2

### Execução

No ubuntu1:

```bash
ping -c 4 <IP_ubuntu2>
wget -O- http://<IP_ubuntu2>/index.html
```

### Interpretação

Aqui testas dois tipos de tráfego:

| Teste  | Protocolo   | O que prova               |
| ------ | ----------- | ------------------------- |
| `ping` | ICMP        | Há conectividade IP       |
| `wget` | TCP/80 HTTP | O serviço web é acessível |

> Nesta etapa estou a testar se a LAN consegue aceder à LAN2.
> O resultado esperado é ping responder e wget devolver HTML.
> Se ping funciona mas wget falha, a rede existe mas a porta 80 ou Apache está bloqueado/parado.
> Em segurança, isto demonstra controlo por protocolo/serviço.

---

## Etapa 9 — Testar ubuntu2 → ubuntu1

### Execução

No ubuntu2:

```bash
ping -c 4 <IP_ubuntu1>
wget -O- http://<IP_ubuntu1>/index.html
```

### Interpretação

Agora testas o sentido inverso.

Isto é importante porque firewall não é “bidirecional” de forma simples. Uma regra em LAN2 controla tráfego que entra pela LAN2. Uma regra em LAN controla tráfego que entra pela LAN.

> Nesta etapa estou a testar comunicação no sentido LAN2 para LAN.
> O resultado esperado depende das regras criadas.
> Se ubuntu2 não aceder ao ubuntu1, falta regra em LAN2 ou há regra de bloqueio.
> Em segurança, isto demonstra que cada sentido de comunicação deve ser analisado pela interface de entrada.

---

## Etapa 10 — Permitir apenas página web entre containers, mantendo Internet

### Execução esperada

Exemplo: permitir ubuntu2 aceder ao web server do ubuntu1, mas não permitir tudo.

Na LAN2:

```text
Firewall → Rules → LAN2
```

Ordem recomendada:

```text
1. Pass TCP from ubuntu2 to ubuntu1 port 80
2. Pass LAN2 net to Internet/DNS as necessário
3. Block LAN2 net to LAN net
4. Pass LAN2 net to any, se o objetivo for Internet geral
```

Mais limpo:

```text
Pass TCP
Source: ubuntu2
Destination: ubuntu1
Destination port: HTTP 80
```

Depois uma regra de bloqueio:

```text
Block
Source: LAN2 net
Destination: LAN net
```

Mas cuidado: se meteres `Pass LAN2 net to any` acima do block, o block nunca é atingido.

### Interpretação

Isto ensina a diferença entre:

```text
Permitir tudo
vs
Permitir só serviço específico
```

> Nesta etapa estou a restringir comunicação lateral entre redes.
> O resultado esperado é HTTP funcionar, mas outros protocolos falharem.
> Se tudo continuar a funcionar, a regra permissiva está demasiado acima ou demasiado larga.
> Em segurança, isto demonstra princípio do menor privilégio.

### Armadilha importante

O guião diz “só permita carregar a página index.html”.

Uma firewall normal de camada 3/4 **não consegue distinguir `/index.html` de `/outra-pagina.html`**. Ela vê IP, porta e protocolo, não o conteúdo HTTP.

Portanto, numa regra normal de firewall, o que consegues fazer é:

```text
Permitir TCP/80 para o servidor web
```

Não consegues dizer:

```text
Permitir só /index.html
```

Para permitir apenas uma página específica precisarias de proxy, WAF, reverse proxy ou configuração do Apache.

Esta é uma excelente frase para avaliação:

> Com regras de firewall tradicionais consigo permitir HTTP para o servidor, mas não filtrar o caminho `/index.html`, porque isso já é conteúdo de aplicação.

---

## Etapa 11 — Criar NAT para WAN aceder ao Apache do ubuntu1

### Cenário

```text
ubuntuWAN → OPNsense WAN:8080 → NAT → ubuntu1:80
```

### Execução

Na OPNsense:

```text
Firewall → NAT → Port Forward
```

Regra sugerida:

| Campo                   | Valor                      |
| ----------------------- | -------------------------- |
| Interface               | WAN                        |
| Protocol                | TCP                        |
| Source                  | any ou WAN net             |
| Destination             | WAN address                |
| Destination port        | 8080                       |
| Redirect target IP      | IP_ubuntu1                 |
| Redirect target port    | 80                         |
| Filter rule association | Add associated rule / Pass |

A documentação da OPNsense indica que Destination NAT / Port Forward é configurado em `Firewall → NAT → Destination NAT (Port Forward)` e que o redirect target IP é o IP interno para onde o tráfego é encaminhado. ([OPNsense Documentation][2])

No container da WAN:

```bash
wget -O- http://<IP_WAN_OPNsense>:8080/
```

### Interpretação

Aqui está a parte difícil.

Sem NAT:

```text
ubuntuWAN tenta aceder ao ubuntu1
mas ubuntu1 está atrás da firewall
a WAN não sabe chegar diretamente ao IP interno
```

Com NAT:

```text
ubuntuWAN acede ao IP da firewall
a firewall altera o destino para ubuntu1
```

### Explicação oral forte

> A regra NAT altera o destino do pacote. O cliente externo pensa que está a aceder à OPNsense na porta 8080, mas a firewall reencaminha para o servidor interno ubuntu1 na porta 80. A regra de firewall associada permite que esse tráfego passe.

### NAT ≠ firewall rule

| Tipo          | Pergunta que responde                        |
| ------------- | -------------------------------------------- |
| Firewall rule | Este pacote pode passar?                     |
| NAT rule      | Para que IP/porta devo traduzir este pacote? |

---

## Etapa 12 — Criar DNS forcing para Unbound

### Objetivo

Forçar clientes da LAN/LAN2 a usar o DNS da OPNsense.

### Execução conceptual

Criar uma regra NAT de redirecionamento:

```text
Firewall → NAT → Port Forward
```

Regra típica:

| Campo                | Valor                             |
| -------------------- | --------------------------------- |
| Interface            | LAN/LAN2                          |
| Protocol             | TCP/UDP                           |
| Source               | LAN net ou LAN2 net               |
| Destination          | not This Firewall                 |
| Destination port     | DNS 53                            |
| Redirect target IP   | 127.0.0.1 ou endereço da firewall |
| Redirect target port | DNS 53                            |

Além disso, permitir DNS para a firewall:

```text
Firewall → Rules → LAN/LAN2
Pass TCP/UDP
Source: LAN/LAN2 net
Destination: This Firewall
Destination port: DNS
```

A própria documentação da OPNsense usa “This Firewall” como destino para permitir DNS quando o resolver é a firewall, porque o Unbound pode responder através de múltiplos endereços da firewall. ([OPNsense Documentation][3])

### Teste

No cliente:

```bash
dig google.com
dig @8.8.8.8 google.com
```

Se o forcing estiver correto, mesmo o pedido para `8.8.8.8` na porta 53 será redirecionado para o DNS da firewall.

### Interpretação

> Nesta etapa estou a testar se o cliente consegue contornar o DNS da rede.
> O resultado esperado é que pedidos DNS externos sejam redirecionados para o Unbound.
> Se `dig @8.8.8.8` sair diretamente, o forcing não está ativo.
> Em segurança, isto demonstra controlo de resolução DNS e prevenção de bypass.

### Limitações

DNS forcing na porta 53 não bloqueia automaticamente:

```text
DNS over HTTPS → porta 443
DNS over TLS   → porta 853
IPv6 DNS       → se só configuraste IPv4
```

---

## 6. Comandos e interpretação

### Comando

```bash
ip a
```

**O que faz:**
Mostra interfaces e endereços IP.

**Porque usamos:**
Para confirmar se ubuntu1, ubuntu2 e ubuntuWAN estão nas redes certas.

**O que espero ver:**
Cada máquina com IP da subrede correta.

**Como interpretar:**
Se ubuntu2 não tem IP da LAN2, a bridge ou DHCP estão errados.

**Erro comum:**
Olhar só para o IP e esquecer a gateway.

---

### Comando

```bash
ip r
```

**O que faz:**
Mostra a tabela de rotas.

**Porque usamos:**
Para confirmar a default gateway.

**O que espero ver:**

```text
default via <IP_da_OPNsense_naquela_rede>
```

**Como interpretar:**
Sem default route, o container não sabe sair da rede.

**Erro comum:**
Pensar que ter IP basta para ter Internet.

---

### Comando

```bash
cat /etc/resolv.conf
```

**O que faz:**
Mostra o DNS configurado.

**Porque usamos:**
Para perceber se falha de nomes é problema DNS.

**O que espero ver:**

```text
nameserver <DNS>
```

**Como interpretar:**
Se ping a `8.8.8.8` funciona mas `google.com` falha, o problema é DNS.

**Erro comum:**
Confundir falha de DNS com falha de Internet.

---

### Comando

```bash
ping -c 4 8.8.8.8
```

**O que faz:**
Envia 4 pacotes ICMP para testar conectividade IP.

**Porque usamos:**
Para testar saída para a Internet sem depender de DNS.

**O que espero ver:**

```text
4 packets transmitted, 4 received
```

**Como interpretar:**
Se responde, há conectividade IP.

**Erro comum:**
Assumir que ping bloqueado significa sempre sem Internet. Pode ser ICMP bloqueado.

---

### Comando

```bash
ping -c 4 google.com
```

**O que faz:**
Testa conectividade + resolução DNS.

**Porque usamos:**
Para ver se o sistema resolve nomes.

**O que espero ver:**
Resolução do nome e respostas ICMP.

**Como interpretar:**
Se `8.8.8.8` funciona mas `google.com` não, é DNS.

**Erro comum:**
Corrigir firewall quando o problema é DNS.

---

### Comando

```bash
apt update
apt install apache2 -y
```

**O que faz:**
Atualiza repositórios e instala Apache2.

**Porque usamos:**
Para criar um servidor HTTP nos containers.

**O que espero ver:**
Instalação concluída sem erro.

**Como interpretar:**
Se falha no `apt update`, pode ser Internet/DNS/firewall.

**Erro comum:**
Instalar Apache antes de confirmar Internet.

---

### Comando

```bash
systemctl status apache2
```

**O que faz:**
Mostra estado do serviço Apache.

**Porque usamos:**
Para confirmar se o servidor web está ativo.

**O que espero ver:**

```text
active (running)
```

**Como interpretar:**
Se não está ativo, `wget` pode falhar mesmo com firewall correta.

**Erro comum:**
Culpar firewall quando o Apache está parado.

---

### Comando

```bash
wget -O- http://<IP>/index.html
```

**O que faz:**
Descarrega a página web e imprime no terminal.

**Porque usamos:**
Para testar HTTP real na porta 80.

**O que espero ver:**
HTML da página Apache.

**Como interpretar:**
Se ping funciona mas wget falha, problema está em TCP/80, Apache ou regra específica.

**Erro comum:**
Testar só ping e dizer que “a comunicação funciona”.

---

### Comando

```bash
nmap -Pn -p 80 <IP>
```

**O que faz:**
Testa a porta 80 sem depender de ping.

**Porque usamos:**
Para distinguir serviço aberto, fechado ou filtrado.

**O que espero ver:**

```text
80/tcp open
```

**Como interpretar:**

| Estado   | Significado                          |
| -------- | ------------------------------------ |
| open     | Serviço responde                     |
| closed   | Host responde, mas porta fechada     |
| filtered | Firewall bloqueia ou não há resposta |

**Erro comum:**
Pensar que `filtered` significa host desligado.

---

### Comando

```bash
dig @8.8.8.8 google.com
```

**O que faz:**
Força consulta DNS ao servidor `8.8.8.8`.

**Porque usamos:**
Para testar se o DNS forcing está a redirecionar pedidos.

**O que espero ver:**
Resposta DNS.

**Como interpretar:**
Se a firewall redireciona, o cliente pode pensar que falou com `8.8.8.8`, mas a firewall interceptou o pedido.

**Erro comum:**
Não testar TCP e UDP na porta 53.

---

## 7. Resultados esperados

| Teste                             | Resultado esperado       | Interpretação                     |
| --------------------------------- | ------------------------ | --------------------------------- |
| ubuntu1 Internet                  | Funciona                 | LAN tem regra/NAT válido          |
| ubuntu2 Internet antes das regras | Falha                    | LAN2 ainda sem permissões         |
| ubuntu2 Internet após regra LAN2  | Funciona                 | Regra de acesso está correta      |
| ubuntu1 → ubuntu2 ping            | Depende das regras       | Testa ICMP entre redes            |
| ubuntu1 → ubuntu2 wget            | HTML Apache              | HTTP permitido                    |
| ubuntu2 → ubuntu1 wget            | HTML Apache se permitido | Comunicação LAN2 → LAN autorizada |
| WAN → ubuntu1 sem NAT             | Falha                    | Servidor interno não publicado    |
| WAN → OPNsense:8080 com NAT       | Funciona                 | Port forward correto              |
| `dig @8.8.8.8` com forcing        | Responde via firewall    | DNS externo redirecionado         |

---

## 8. Troubleshooting

| Problema                          | Sintoma                                    | Causa provável                         | Como confirmar                           | Como corrigir                                |
| --------------------------------- | ------------------------------------------ | -------------------------------------- | ---------------------------------------- | -------------------------------------------- |
| ubuntu2 sem IP                    | `ip a` sem IPv4 correto                    | Bridge errada ou DHCP LAN2 desligado   | Ver bridge no Proxmox e leases DHCP      | Ligar ubuntu2 à bridge da LAN2 e ativar DHCP |
| ubuntu2 tem IP mas sem Internet   | `ping 8.8.8.8` falha                       | Falta regra LAN2 ou gateway errado     | `ip r` e regras LAN2                     | Criar regra Pass LAN2 net → any              |
| Resolve IP mas não nomes          | `ping 8.8.8.8` OK, `ping google.com` falha | DNS errado                             | `cat /etc/resolv.conf`                   | Corrigir DNS/DHCP                            |
| Apache inacessível                | `wget` falha                               | Serviço parado ou porta bloqueada      | `systemctl status apache2`, `nmap -p 80` | Iniciar Apache ou criar regra TCP/80         |
| Ping funciona mas wget não        | ICMP permitido, TCP/80 bloqueado           | Regra só permite ICMP ou Apache parado | `nmap -Pn -p 80 <IP>`                    | Permitir TCP/80                              |
| Tudo passa apesar do block        | Block abaixo de regra allow any            | Ordem errada                           | Ver ordem das regras                     | Mover block acima do allow geral             |
| NAT não funciona                  | WAN não abre página                        | Falta port forward ou regra associada  | Ver NAT e firewall WAN                   | Criar port forward + regra pass              |
| Acede à firewall em vez do Apache | Usaste porta 80 da WAN                     | Conflito com Web UI da OPNsense        | Testar `:8080`                           | Usar WAN:8080 → ubuntu1:80                   |
| DNS forcing não funciona          | `dig @8.8.8.8` sai direto                  | Regra NAT errada ou só UDP/TCP parcial | Packet capture / logs firewall           | Redirecionar TCP/UDP 53                      |
| Confusão LAN/WAN/LAN2             | Regras no sítio errado                     | Regra criada na interface errada       | Ver por onde o tráfego entra             | Criar regra na interface de origem           |

---

## 9. Perguntas típicas de avaliação

### Perguntas diretas

**1. O que é uma regra de firewall?**
É uma regra que decide se tráfego com certa origem, destino, protocolo e porta pode passar ou deve ser bloqueado.

**2. O que é NAT?**
É tradução de endereços ou portas. Pode alterar origem ou destino dos pacotes.

**3. O que é port forwarding?**
É Destination NAT: tráfego que chega à firewall numa porta é encaminhado para um host interno.

**4. Qual é a diferença entre firewall rule e NAT rule?**
Firewall rule permite ou bloqueia. NAT rule traduz endereço ou porta.

**5. O que significa `filtered` no nmap?**
Significa que não houve resposta suficiente; normalmente uma firewall está a bloquear ou a descartar pacotes.

**6. O que é DNS forcing?**
É redirecionar pedidos DNS dos clientes para o resolver controlado pela rede.

---

### Perguntas de raciocínio

**1. ubuntu2 não tem Internet. Onde investigas primeiro?**
Primeiro verifico `ip a`, `ip r` e DNS. Depois vejo regras da LAN2 e NAT outbound.

**2. Ping a 8.8.8.8 funciona, mas google.com não. O que concluis?**
A rede IP funciona; o problema provável é DNS.

**3. Ping entre containers funciona, mas wget falha. O que concluis?**
ICMP passa, mas HTTP/TCP 80 pode estar bloqueado ou o Apache pode estar parado.

**4. Criei NAT mas a WAN não acede ao servidor interno. Que hipótese levantas?**
Pode faltar regra firewall associada, o destino/porta NAT pode estar errado, ou o Apache pode estar parado.

**5. Porque usar WAN:8080 → ubuntu1:80?**
Para evitar conflito com a porta 80 da própria firewall e demonstrar tradução de porta.

**6. Porque é que uma firewall normal não permite “só index.html”?**
Porque regras L3/L4 veem IP, protocolo e porta. O caminho `/index.html` pertence à camada de aplicação HTTP.

---

### Perguntas práticas

**1. Como confirmas o IP de uma máquina?**

```bash
ip a
```

**2. Como confirmas a gateway?**

```bash
ip r
```

**3. Como confirmas DNS?**

```bash
cat /etc/resolv.conf
```

**4. Como confirmas que Apache está ativo?**

```bash
systemctl status apache2
```

ou:

```bash
service apache2 status
```

**5. Como testas HTTP?**

```bash
wget -O- http://<IP>/index.html
```

**6. Como testas se a porta 80 está aberta?**

```bash
nmap -Pn -p 80 <IP>
```

**7. Como sabes se a firewall está a bloquear?**
Comparo ping, wget, nmap e logs da OPNsense. Se o serviço está ativo mas o tráfego fica `filtered`, a hipótese forte é bloqueio na firewall.

---

## 10. Resumo para imprimir

# Resumo rápido — Guião 4

## Objetivo do guião

Configurar uma nova rede na OPNsense, criar regras de firewall, publicar um servidor interno com NAT e forçar DNS para o Unbound.

---

## Ideia central

```text
Firewall rule = permite ou bloqueia
NAT rule      = traduz endereço ou porta
```

---

## Topologia

```text
WAN / ubuntuWAN
      |
   OPNsense
   /      \
LAN      LAN2
ubuntu1  ubuntu2
Apache   Apache
```

---

## Conceitos principais

* **LAN/LAN2/WAN:** zonas de rede diferentes.
* **Bridge Proxmox:** rede virtual onde ligas VMs/containers.
* **DHCP:** dá IP automaticamente aos clientes.
* **Firewall rule:** controla tráfego por interface, origem, destino, protocolo e porta.
* **NAT:** altera IP/porta.
* **Port forward:** WAN:porta → servidor interno:porta.
* **DNS forcing:** redireciona pedidos DNS para o resolver da firewall.

---

## Regra mental das interfaces

```text
A regra deve estar na interface onde o tráfego ENTRA na firewall.
```

Exemplos:

| Tráfego                | Regra onde? |
| ---------------------- | ----------- |
| LAN2 → Internet        | LAN2        |
| LAN → LAN2             | LAN         |
| WAN → servidor interno | WAN + NAT   |
| LAN2 → LAN             | LAN2        |

---

## Comandos essenciais

| Comando                           | Para que serve            |
| --------------------------------- | ------------------------- |
| `ip a`                            | Ver IP da máquina         |
| `ip r`                            | Ver gateway/default route |
| `cat /etc/resolv.conf`            | Ver DNS                   |
| `ping -c 4 8.8.8.8`               | Testar Internet sem DNS   |
| `ping -c 4 google.com`            | Testar Internet com DNS   |
| `apt install apache2 -y`          | Instalar servidor web     |
| `systemctl status apache2`        | Ver se Apache está ativo  |
| `wget -O- http://<IP>/index.html` | Testar HTTP               |
| `nmap -Pn -p 80 <IP>`             | Testar porta 80           |
| `dig @8.8.8.8 google.com`         | Testar DNS forcing        |

---

## Interpretações importantes

* `ping 8.8.8.8` funciona, mas `google.com` falha → problema DNS.
* `ping` funciona, mas `wget` falha → problema TCP/80, Apache ou firewall.
* `nmap open` → serviço responde.
* `nmap closed` → host responde, porta fechada.
* `nmap filtered` → firewall provavelmente bloqueia.
* NAT sozinho não basta se a firewall bloquear.
* Regra `allow any` acima de `block` anula o bloqueio.
* Firewall tradicional não filtra `/index.html`; filtra IP/porta/protocolo.

---

## NAT explicado rápido

Para publicar ubuntu1 na WAN:

```text
Cliente WAN acede a:
http://<IP_WAN_OPNsense>:8080

OPNsense traduz para:
http://<IP_ubuntu1>:80
```

Explicação oral:

> O cliente externo não acede diretamente ao ubuntu1. Ele acede à firewall. A regra NAT altera o destino do pacote para o IP interno do ubuntu1 e a regra firewall permite a passagem.

---

## DNS forcing explicado rápido

```text
Cliente tenta usar 8.8.8.8:53
Firewall intercepta
Redireciona para Unbound
```

Explicação oral:

> Esta regra impede que clientes contornem o DNS da rede usando servidores externos na porta 53.

---

## Erros comuns

* Criar LAN2 mas ligar ubuntu2 à bridge errada.
* Esquecer DHCP da LAN2.
* Criar regra na WAN quando o tráfego entra pela LAN2.
* Criar regra permissiva demasiado larga.
* Colocar `allow any` acima do `block`.
* Confundir NAT outbound com port forward.
* Esquecer regra firewall associada ao NAT.
* Testar nomes DNS antes de testar IP.
* Pensar que firewall consegue filtrar `/index.html` sem proxy/WAF.

---

## Frases para avaliação

* > Estou a testar se a nova interface LAN2 consegue fornecer IP e gateway aos clientes.
* > Estou a testar se a firewall permite tráfego originado na LAN2.
* > Se ubuntu2 não tem Internet mas tem IP, verifico gateway, DNS e regras LAN2.
* > O NAT permite publicar um serviço interno através do IP externo da firewall.
* > A firewall rule permite ou bloqueia; a NAT rule traduz.
* > DNS forcing redireciona pedidos DNS para o resolver controlado pela firewall.
* > Se `nmap` mostra `filtered`, a hipótese principal é bloqueio por firewall.

---

## 11. Checklist final

### Antes de começar

* [ ] Backup da OPNsense feito.
* [ ] Sei qual é a WAN, LAN e LAN2.
* [ ] Sei que bridge Proxmox corresponde a cada interface.

### LAN2

* [ ] Bridge criada.
* [ ] Interface adicionada à OPNsense.
* [ ] LAN2 enabled.
* [ ] IP estático configurado.
* [ ] DHCP LAN2 ativo.
* [ ] ubuntu2 recebe IP da LAN2.

### Regras de acesso

* [ ] ubuntu1 tem Internet.
* [ ] ubuntu2 inicialmente testado.
* [ ] Regra LAN2 criada.
* [ ] ubuntu2 consegue Internet.
* [ ] Apache instalado nos dois containers.
* [ ] `wget` testado nos dois sentidos.

### Restrição de acesso

* [ ] Regra TCP/80 criada para servidor web.
* [ ] Outros protocolos bloqueados se pedido.
* [ ] Ordem das regras validada.
* [ ] Confirmado que firewall não filtra `/index.html` sem camada aplicacional.

### NAT

* [ ] ubuntuWAN ligado à WAN.
* [ ] Port forward criado.
* [ ] WAN:8080 redireciona para ubuntu1:80.
* [ ] Regra firewall associada criada.
* [ ] Teste com `wget http://<WAN_IP>:8080`.

### DNS forcing

* [ ] Unbound ativo.
* [ ] Regra NAT TCP/UDP 53 criada.
* [ ] Regra firewall DNS para This Firewall criada.
* [ ] Teste com `dig @8.8.8.8`.
* [ ] Confirmado que DNS externo é redirecionado.

[1]: https://docs.opnsense.org/manual/firewall.html "Rules — OPNsense  documentation"
[2]: https://docs.opnsense.org/manual/nat.html "Network Address Translation — OPNsense  documentation"
[3]: https://docs.opnsense.org/manual/captiveportal.html "Captive portal & GuestNET — OPNsense  documentation"
