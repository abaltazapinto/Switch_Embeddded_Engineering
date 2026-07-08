# Estudo do Guião 5 — Confiabilidade e Cibersegurança

**Tema central:** utilização e proteção do protocolo **MQTT** em contexto IoT.

O guião 5 é sobre comunicação **cliente MQTT ↔ broker MQTT**, primeiro em claro, depois com broker remoto e finalmente com comunicação encriptada. O PDF indica que o MQTT é tratado como protocolo IoT principal da prática e que as próximas práticas continuam neste tema. O teu prompt pede explicitamente separar execução de interpretação, comandos, erros comuns e frases para avaliação. 

---

## 1. Ideia central do guião

O guião quer que percebas isto:

> Um dispositivo IoT raramente comunica diretamente com outro dispositivo.
> Normalmente publica mensagens num **broker MQTT**, e outros clientes subscrevem tópicos nesse broker.

Em termos simples:

```text
Sensor / Cliente MQTT
        |
        | publish
        v
   Broker MQTT
        |
        | deliver
        v
Aplicação / Cliente MQTT
```

Exemplo prático:

```text
ESP32 publica temperatura  →  broker MQTT  →  dashboard recebe temperatura
```

Neste guião, em vez de ESP32, usas containers Ubuntu.

---

## 2. O que este guião quer provar

O guião quer provar 4 coisas principais:

| Parte                           | O que estás a provar                                                    |
| ------------------------------- | ----------------------------------------------------------------------- |
| MQTT local                      | Cliente e broker conseguem comunicar na mesma rede                      |
| Observação com Wireshark/ntopng | O protocolo MQTT aparece no tráfego                                     |
| Broker remoto                   | O cliente consegue sair da rede local e comunicar com um broker público |
| MQTT com encriptação            | A comunicação pode existir sem expor o conteúdo das mensagens em claro  |

O ponto difícil, especialmente com **NAT/firewall**, é este:

> Quando o broker está dentro da tua rede, o cliente fala diretamente com o IP interno do broker.
> Quando o broker está fora, o tráfego tem de atravessar gateway, firewall e NAT.
> Quando alguém de fora quer chegar ao teu broker interno, precisas de port forwarding/NAT inbound.

---

## 3. Topologia / cenário usado

### 3.1 Topologia local simples

```text
Ubuntu Container Cliente MQTT
IP: 192.168.X.10
        |
        | bridge interna
        |
Ubuntu Container Broker MQTT
IP: 192.168.X.20
Porta: 1883
```

Aqui **não precisas de NAT** se ambos estiverem na mesma bridge/rede.

---

### 3.2 Topologia com broker remoto

```text
Cliente MQTT
        |
        | LAN
        v
OPNsense / Gateway
        |
        | NAT outbound
        v
Internet
        |
        v
broker.hivemq.com:1883
```

Aqui precisas de:

* IP correto no cliente;
* gateway correto;
* DNS funcional;
* regra de firewall a permitir saída;
* NAT outbound funcional.

---

### 3.3 Topologia com broker interno acessível de fora

```text
Cliente externo
        |
        | Internet
        v
WAN OPNsense
        |
        | Port Forward / NAT
        v
Broker MQTT interno
IP: 192.168.X.20
Porta: 1883 ou 8883
```

Aqui entra a dificuldade das regras NAT.

Se alguém de fora quiser aceder ao teu broker interno, precisas de:

```text
WAN:1883  →  Broker interno:1883
```

ou, com TLS:

```text
WAN:8883  →  Broker interno:8883
```

---

## 4. Conceitos necessários antes de executar

### Conceito: MQTT

**Ideia simples:**
MQTT é um protocolo leve de mensagens, muito usado em IoT.

**Analogia:**
Imagina um quadro de avisos. Um sensor escreve uma mensagem num tópico, e quem estiver interessado nesse tópico lê a mensagem.

**Na prática do guião:**
O cliente publica mensagens e outro cliente subscreve essas mensagens através do broker.

**Como explicar ao professor:**

> MQTT é um protocolo publish/subscribe usado em IoT, onde os clientes não comunicam diretamente entre si, mas através de um broker.

---

### Conceito: Broker MQTT

**Ideia simples:**
O broker é o intermediário. Recebe mensagens e entrega-as aos clientes interessados.

**Analogia:**
É como uma estação de correios: recebe cartas e entrega a quem subscreveu aquela caixa/tópico.

**Na prática do guião:**
O Mosquitto faz o papel de broker.

**Como explicar ao professor:**

> O broker MQTT centraliza a comunicação: recebe mensagens publicadas em tópicos e distribui-as aos clientes subscritos.

---

### Conceito: Publish / Subscribe

**Ideia simples:**
Um cliente publica numa categoria chamada **tópico**. Outro cliente subscreve esse tópico.

**Analogia:**
Como seguir um canal: quem publica mete lá mensagens; quem subscreve recebe.

**Na prática do guião:**

```text
mosquitto_pub  → publica
mosquitto_sub  → subscreve
```

**Como explicar ao professor:**

> O modelo publish/subscribe desacopla produtores e consumidores, porque o publisher não precisa de saber quem vai receber a mensagem.

---

### Conceito: Porta 1883

**Ideia simples:**
É a porta normalmente usada por MQTT sem encriptação.

**Analogia:**
É uma porta de entrada sem vidro fumado: consegues ver o que passa se capturares tráfego.

**Na prática do guião:**
Quando usas `broker.hivemq.com:1883` ou Mosquitto local sem TLS.

**Como explicar ao professor:**

> A porta 1883 é usada para MQTT em claro; com captura de tráfego, é possível observar tópicos e mensagens.

---

### Conceito: Porta 8883

**Ideia simples:**
É a porta normalmente usada por MQTT com TLS.

**Analogia:**
É a mesma conversa, mas dentro de um túnel fechado.

**Na prática do guião:**
Na parte de certificados e encriptação.

**Como explicar ao professor:**

> A porta 8883 é normalmente usada para MQTT sobre TLS, protegendo a confidencialidade da comunicação.

---

### Conceito: TLS / Certificados

**Ideia simples:**
TLS cifra a comunicação entre cliente e broker.

**Analogia:**
Sem TLS, mandas um postal. Com TLS, mandas uma carta fechada.

**Na prática do guião:**
Usas certificados no Mosquitto para que o tráfego MQTT não apareça em claro no Wireshark.

**Como explicar ao professor:**

> A encriptação com TLS impede que o conteúdo das mensagens MQTT seja lido diretamente numa captura de rede.

---

### Conceito: NAT outbound

**Ideia simples:**
Permite que máquinas privadas saiam para a Internet usando o IP da firewall/router.

**Analogia:**
Várias pessoas de uma casa usam a mesma morada para enviar cartas.

**Na prática do guião:**
Quando o cliente MQTT interno comunica com `broker.hivemq.com`.

**Como explicar ao professor:**

> O NAT outbound traduz o IP privado do cliente para o IP da interface WAN, permitindo comunicação com brokers externos.

---

### Conceito: Port Forward / NAT inbound

**Ideia simples:**
Permite que tráfego vindo de fora chegue a um serviço interno.

**Analogia:**
A portaria recebe uma encomenda e encaminha para a sala certa.

**Na prática do guião:**
Se quiseres expor o teu broker interno para clientes externos.

**Como explicar ao professor:**

> O port forward redireciona tráfego recebido na WAN para um host interno específico, por exemplo WAN:8883 para Broker:8883.

---

## 5. Procedimento explicado passo a passo

## Exercício 3.1 — Instalação e teste de cliente e broker MQTT

### Objetivo

Criar dois containers:

```text
Container A: Broker MQTT
Container B: Cliente MQTT
```

E provar que conseguem comunicar via MQTT.

---

### Execução

#### Passo 1 — Confirmar IPs dos containers

**Ação:**
Em cada container:

```bash
ip a
```

**Objetivo:**
Descobrir o IP do cliente e do broker.

**Como pensar:**
Antes de testar MQTT, tens de provar que a rede básica existe.

**Resultado esperado:**

```text
cliente: 192.168.X.10
broker:  192.168.X.20
```

**Interpretação:**
Se ambos estiverem na mesma rede, devem conseguir comunicar diretamente.

**Erro comum:**
Usar o IP da bridge, do host Proxmox ou da OPNsense em vez do IP real do container.

---

#### Passo 2 — Testar conectividade básica

No cliente:

```bash
ping -c 4 <IP_DO_BROKER>
```

**Objetivo:**
Confirmar que o cliente consegue chegar ao broker.

**Resultado esperado:**

```text
4 packets transmitted, 4 received, 0% packet loss
```

**Interpretação:**
Isto prova que IP, bridge e conectividade básica estão corretos.

**Erro comum:**
Tentar resolver problemas MQTT quando o problema ainda é rede básica.

---

#### Passo 3 — Instalar Mosquitto

No broker:

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients -y
```

No cliente:

```bash
sudo apt update
sudo apt install mosquitto-clients -y
```

**Objetivo:**
Instalar o serviço broker e as ferramentas cliente.

**Resultado esperado:**
Instalação sem erros.

**Interpretação:**
O broker passa a poder aceitar ligações MQTT.

**Erro comum:**
Instalar só `mosquitto-clients` no broker e esquecer o serviço `mosquitto`.

---

#### Passo 4 — Confirmar que o Mosquitto está ativo

No broker:

```bash
systemctl status mosquitto
```

ou:

```bash
sudo systemctl enable --now mosquitto
```

**Objetivo:**
Verificar se o serviço está a correr.

**Resultado esperado:**

```text
active (running)
```

**Interpretação:**
O serviço está disponível no broker.

**Erro comum:**
A porta estar fechada porque o serviço não arrancou.

---

#### Passo 5 — Verificar se o broker escuta na porta 1883

No broker:

```bash
sudo ss -lntp | grep 1883
```

**Objetivo:**
Confirmar que existe um serviço TCP à escuta na porta MQTT.

**Resultado esperado:**

```text
LISTEN 0  ...  0.0.0.0:1883
```

ou:

```text
127.0.0.1:1883
```

**Interpretação importante:**

| Resultado        | Significado                           |
| ---------------- | ------------------------------------- |
| `0.0.0.0:1883`   | Aceita ligações externas ao container |
| `127.0.0.1:1883` | Só aceita ligações locais             |
| nada aparece     | Mosquitto não está a escutar          |

**Erro comum grave:**
O Mosquitto pode estar ativo, mas só a escutar em `localhost`. Nesse caso, o cliente remoto não consegue ligar.

---

#### Passo 6 — Configurar listener para laboratório

No broker, criar ficheiro:

```bash
sudo nano /etc/mosquitto/conf.d/lab.conf
```

Conteúdo:

```conf
listener 1883 0.0.0.0
allow_anonymous true
```

Depois:

```bash
sudo systemctl restart mosquitto
```

**Objetivo:**
Permitir que o broker aceite ligações MQTT vindas do cliente.

**Como pensar:**
Para laboratório, `allow_anonymous true` simplifica. Em produção, isto seria inseguro.

**Resultado esperado:**
O broker escuta em `0.0.0.0:1883`.

**Interpretação:**
O broker aceita ligações externas ao container.

**Erro comum:**
Esquecer `restart` depois de alterar configuração.

---

#### Passo 7 — Subscrever um tópico

No cliente ou num segundo terminal:

```bash
mosquitto_sub -h <IP_DO_BROKER> -t "isep/teste" -v
```

**Objetivo:**
Ficar à espera de mensagens no tópico `isep/teste`.

**Resultado esperado:**
O terminal fica parado à espera.

**Interpretação:**
Isto não é erro. O subscriber está a aguardar mensagens.

**Erro comum:**
Pensar que o comando bloqueou ou encravou.

---

#### Passo 8 — Publicar uma mensagem

Noutro terminal:

```bash
mosquitto_pub -h <IP_DO_BROKER> -t "isep/teste" -m "ola mqtt"
```

**Objetivo:**
Enviar uma mensagem para o broker.

**Resultado esperado no subscriber:**

```text
isep/teste ola mqtt
```

**Interpretação:**
Isto prova que o cliente publicou, o broker recebeu e o subscriber recebeu a mensagem.

**Erro comum:**
Usar tópicos diferentes:

```text
isep/teste
isep/test
```

São tópicos diferentes.

---

### Frase para avaliação

> Nesta etapa estou a testar se o cliente MQTT consegue comunicar com o broker local.
> O resultado esperado é a mensagem publicada aparecer no subscriber.
> Se a mensagem não aparecer, significa que pode haver problema de IP, porta, serviço Mosquitto, firewall ou tópico errado.
> Em termos de segurança, isto demonstra a existência de comunicação MQTT funcional dentro da rede local.

---

## Exercício 3.2 — Verificação do protocolo MQTT localmente

### Objetivo

Capturar tráfego e provar que MQTT está realmente a circular na rede.

---

### Execução com tcpdump

No broker:

```bash
sudo tcpdump -i any port 1883 -n
```

Depois publica uma mensagem a partir do cliente.

**Resultado esperado:**

```text
IP 192.168.X.10.xxxxx > 192.168.X.20.1883
IP 192.168.X.20.1883 > 192.168.X.10.xxxxx
```

**Interpretação:**
Isto prova que há tráfego TCP na porta MQTT.

---

### Execução com Wireshark

Filtro útil:

```text
mqtt
```

ou:

```text
tcp.port == 1883
```

**Resultado esperado:**
Pacotes MQTT como:

```text
CONNECT
CONNACK
PUBLISH
SUBSCRIBE
PINGREQ
PINGRESP
```

**Interpretação:**
Se o Wireshark mostrar `PUBLISH` e a mensagem em claro, significa que MQTT está sem encriptação.

---

### Frase para avaliação

> Nesta etapa estou a verificar se o protocolo MQTT aparece no tráfego capturado.
> O resultado esperado é ver pacotes MQTT na porta 1883.
> Se conseguir ver o tópico e a mensagem, significa que a comunicação não está cifrada.
> Em termos de segurança, isto demonstra que MQTT em claro expõe metadados e payload.

---

## Exercício 3.3 — Utilização de broker remoto

O guião indica:

```text
broker.hivemq.com
porta 1883
```

### Objetivo

Provar que o cliente consegue comunicar com um broker MQTT fora da rede local.

---

### Execução

#### Passo 1 — Testar DNS

```bash
getent hosts broker.hivemq.com
```

**Objetivo:**
Confirmar que o nome resolve para IP.

**Resultado esperado:**
Um ou mais IPs.

**Interpretação:**
DNS está funcional.

**Erro comum:**
Confundir falha DNS com falha MQTT.

---

#### Passo 2 — Testar ligação TCP à porta 1883

```bash
nc -vz broker.hivemq.com 1883
```

**Resultado esperado:**

```text
succeeded
```

ou semelhante.

**Interpretação:**
O caminho TCP até ao broker está aberto.

**Erro comum:**
Se isto falhar, ainda nem chegaste ao MQTT. O problema pode ser firewall, NAT, gateway ou Internet.

---

#### Passo 3 — Subscrever tópico remoto

```bash
mosquitto_sub -h broker.hivemq.com -p 1883 -t "isep/andre/teste" -v
```

#### Passo 4 — Publicar no mesmo tópico

```bash
mosquitto_pub -h broker.hivemq.com -p 1883 -t "isep/andre/teste" -m "teste remoto"
```

**Resultado esperado:**
O subscriber recebe:

```text
isep/andre/teste teste remoto
```

**Interpretação:**
Isto prova que o cliente consegue sair para a Internet e comunicar com um broker público.

---

### Onde entra NAT aqui?

Aqui entra **NAT outbound**.

```text
Cliente privado: 192.168.X.10
        |
        v
OPNsense traduz para IP WAN
        |
        v
broker.hivemq.com:1883
```

O broker remoto não conhece o IP privado do cliente. Vê apenas o IP público/WAN.

---

### Frase para avaliação

> Nesta etapa estou a testar se o cliente MQTT consegue comunicar com um broker remoto através da Internet.
> O resultado esperado é conseguir publicar e subscrever no broker `broker.hivemq.com:1883`.
> Se DNS resolver mas a ligação falhar, investigaria gateway, NAT outbound e regras de firewall.
> Em termos de segurança, isto demonstra comunicação MQTT para fora da rede local, normalmente dependente de NAT e regras de saída.

---

## Exercício 3.4 — MQTT com comunicações encriptadas

### Objetivo

Configurar MQTT com TLS para que a comunicação não apareça em claro.

---

### Diferença essencial

| Modo           | Porta típica | Segurança       | Wireshark mostra mensagem? |
| -------------- | -----------: | --------------- | -------------------------- |
| MQTT simples   |         1883 | Sem encriptação | Sim                        |
| MQTT sobre TLS |         8883 | Encriptado      | Não                        |

---

### Execução base no broker

Criar pasta:

```bash
sudo mkdir -p /etc/mosquitto/certs
cd /etc/mosquitto/certs
```

Criar uma CA de laboratório:

```bash
sudo openssl genrsa -out ca.key 2048
sudo openssl req -x509 -new -nodes -key ca.key -sha256 -days 365 -out ca.crt -subj "/CN=MQTT-LAB-CA"
```

Criar chave e certificado do broker:

```bash
sudo openssl genrsa -out server.key 2048
sudo openssl req -new -key server.key -out server.csr -subj "/CN=mqtt-broker"
```

Criar ficheiro SAN, importante se usares IP:

```bash
sudo nano server_ext.cnf
```

Conteúdo exemplo:

```conf
[v3_req]
subjectAltName = IP:<IP_DO_BROKER>,DNS:mqtt-broker
```

Assinar certificado:

```bash
sudo openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 365 -sha256 -extfile server_ext.cnf -extensions v3_req
```

Permissões:

```bash
sudo chown mosquitto:mosquitto /etc/mosquitto/certs/server.key
sudo chmod 640 /etc/mosquitto/certs/server.key
```

---

### Configurar Mosquitto com TLS

Criar:

```bash
sudo nano /etc/mosquitto/conf.d/tls.conf
```

Conteúdo:

```conf
listener 8883 0.0.0.0
cafile /etc/mosquitto/certs/ca.crt
certfile /etc/mosquitto/certs/server.crt
keyfile /etc/mosquitto/certs/server.key
allow_anonymous true
require_certificate false
```

Reiniciar:

```bash
sudo systemctl restart mosquitto
```

Confirmar porta:

```bash
sudo ss -lntp | grep 8883
```

---

### Testar cliente com TLS

Copiar `ca.crt` para o cliente.

No cliente:

```bash
mosquitto_sub -h <IP_DO_BROKER> -p 8883 --cafile ca.crt -t "isep/tls" -v
```

Noutro terminal:

```bash
mosquitto_pub -h <IP_DO_BROKER> -p 8883 --cafile ca.crt -t "isep/tls" -m "mensagem cifrada"
```

Se houver erro de hostname/certificado em laboratório, podes testar com:

```bash
mosquitto_pub -h <IP_DO_BROKER> -p 8883 --cafile ca.crt --insecure -t "isep/tls" -m "teste"
```

**Interpretação correta:**
`--insecure` não desliga a encriptação. Desliga a validação rigorosa do nome do certificado. Para produção, não é aceitável.

---

### Verificar no Wireshark

Filtro:

```text
tcp.port == 8883
```

**Resultado esperado:**
Vês TLS handshake e tráfego cifrado.

Não deves ver:

```text
PUBLISH isep/tls mensagem cifrada
```

**Interpretação:**
Isto prova que o conteúdo MQTT deixou de estar legível na captura.

---

### Frase para avaliação

> Nesta etapa estou a testar MQTT com TLS.
> O resultado esperado é a comunicação funcionar na porta 8883, mas o conteúdo da mensagem não aparecer em claro no Wireshark.
> Se a ligação falhar, verifico certificados, permissões, porta 8883, configuração do listener e firewall.
> Em termos de segurança, isto demonstra confidencialidade da comunicação MQTT.

---

## 6. Comandos e interpretação

### Comando

```bash
ip a
```

**O que faz:**
Mostra interfaces e IPs.

**Porque usamos:**
Para identificar o IP real do cliente e do broker.

**O que espero ver:**
Um IP na bridge correta.

**Como interpretar:**
Se cliente e broker estão na mesma subnet, podem comunicar diretamente.

**Erro comum:**
Confundir IP da VM host, bridge, OPNsense ou container.

---

### Comando

```bash
ping -c 4 <IP_DO_BROKER>
```

**O que faz:**
Testa conectividade ICMP.

**Porque usamos:**
Antes de testar MQTT, validamos rede básica.

**O que espero ver:**
`0% packet loss`.

**Como interpretar:**
A rede IP funciona.

**Erro comum:**
Se ping falha, ir logo mexer no Mosquitto. Primeiro corrige rede.

---

### Comando

```bash
sudo apt install mosquitto mosquitto-clients -y
```

**O que faz:**
Instala broker e clientes MQTT.

**Porque usamos:**
Mosquitto é o broker; `mosquitto_pub` e `mosquitto_sub` são ferramentas de teste.

**O que espero ver:**
Instalação sem erros.

**Como interpretar:**
A máquina já tem ferramentas MQTT.

**Erro comum:**
Instalar clientes mas não o broker.

---

### Comando

```bash
systemctl status mosquitto
```

**O que faz:**
Mostra estado do serviço Mosquitto.

**Porque usamos:**
Para confirmar que o broker está ativo.

**O que espero ver:**
`active (running)`.

**Como interpretar:**
O serviço está a correr.

**Erro comum:**
Serviço ativo mas a escutar só em `127.0.0.1`.

---

### Comando

```bash
sudo ss -lntp | grep 1883
```

**O que faz:**
Mostra se há processo à escuta na porta 1883.

**Porque usamos:**
Para confirmar que o broker aceita ligações MQTT.

**O que espero ver:**
`0.0.0.0:1883` ou `<IP_DO_BROKER>:1883`.

**Como interpretar:**
A porta MQTT está aberta localmente.

**Erro comum:**
Ver `127.0.0.1:1883` e achar que clientes remotos conseguem ligar.

---

### Comando

```bash
mosquitto_sub -h <IP_DO_BROKER> -t "isep/teste" -v
```

**O que faz:**
Subscreve um tópico MQTT.

**Porque usamos:**
Para receber mensagens publicadas nesse tópico.

**O que espero ver:**
O terminal fica à espera.

**Como interpretar:**
Está pronto para receber mensagens.

**Erro comum:**
Pensar que o terminal parado é erro.

---

### Comando

```bash
mosquitto_pub -h <IP_DO_BROKER> -t "isep/teste" -m "ola mqtt"
```

**O que faz:**
Publica uma mensagem no tópico.

**Porque usamos:**
Para testar comunicação MQTT.

**O que espero ver:**
A mensagem aparece no subscriber.

**Como interpretar:**
Cliente, broker, tópico e rede estão funcionais.

**Erro comum:**
Publicar num tópico diferente do subscrito.

---

### Comando

```bash
sudo tcpdump -i any port 1883 -n
```

**O que faz:**
Captura tráfego TCP na porta 1883.

**Porque usamos:**
Para provar que existe tráfego MQTT.

**O que espero ver:**
Pacotes entre cliente e broker.

**Como interpretar:**
Há comunicação na porta MQTT.

**Erro comum:**
Capturar na interface errada.

---

### Comando

```bash
nc -vz broker.hivemq.com 1883
```

**O que faz:**
Testa se a porta TCP 1883 está acessível.

**Porque usamos:**
Para separar problema TCP/rede de problema MQTT.

**O que espero ver:**
Ligação bem-sucedida.

**Como interpretar:**
O caminho até ao broker remoto está aberto.

**Erro comum:**
Usar `ping` como único teste. ICMP pode falhar mesmo que TCP funcione.

---

### Comando

```bash
mosquitto_pub -h broker.hivemq.com -p 1883 -t "isep/andre/teste" -m "teste remoto"
```

**O que faz:**
Publica mensagem num broker remoto.

**Porque usamos:**
Para provar comunicação MQTT via Internet.

**O que espero ver:**
Subscriber remoto recebe mensagem.

**Como interpretar:**
DNS, gateway, NAT e firewall outbound funcionam.

**Erro comum:**
Usar tópico público demasiado genérico e misturar mensagens de outras pessoas.

---

### Comando

```bash
mosquitto_pub -h <IP_DO_BROKER> -p 8883 --cafile ca.crt -t "isep/tls" -m "seguro"
```

**O que faz:**
Publica por MQTT com TLS.

**Porque usamos:**
Para testar encriptação.

**O que espero ver:**
Mensagem recebida, mas não legível no Wireshark.

**Como interpretar:**
A aplicação funciona e o conteúdo está cifrado.

**Erro comum:**
Achar que não ver `mqtt` no Wireshark significa que não há comunicação. Com TLS, o Wireshark vê TLS, não MQTT em claro.

---

## 7. Resultados esperados

| Teste                            | Resultado esperado                   | O que prova              |                   |
| -------------------------------- | ------------------------------------ | ------------------------ | ----------------- |
| `ping cliente → broker`          | Resposta ICMP                        | Rede básica OK           |                   |
| `ss -lntp                        | grep 1883`                           | Porta 1883 aberta        | Broker MQTT ativo |
| `mosquitto_pub/sub local`        | Mensagem recebida                    | MQTT local funcional     |                   |
| Wireshark porta 1883             | `CONNECT`, `PUBLISH`, tópico visível | MQTT sem encriptação     |                   |
| `getent hosts broker.hivemq.com` | IP resolvido                         | DNS OK                   |                   |
| `nc -vz broker.hivemq.com 1883`  | Ligação TCP OK                       | Internet/firewall/NAT OK |                   |
| MQTT remoto                      | Mensagem recebida                    | Broker remoto funcional  |                   |
| `ss -lntp                        | grep 8883`                           | Porta 8883 aberta        | Broker TLS ativo  |
| Wireshark porta 8883             | TLS, sem payload legível             | Comunicação cifrada      |                   |

---

## 8. Troubleshooting

| Problema                           | Sintoma                             | Causa provável                                    | Como confirmar                      | Como corrigir                                      |                       |
| ---------------------------------- | ----------------------------------- | ------------------------------------------------- | ----------------------------------- | -------------------------------------------------- | --------------------- |
| IP errado                          | Cliente não liga ao broker          | Usaste IP da bridge/host errado                   | `ip a` em cada container            | Usar IP real do broker                             |                       |
| Bridge errada                      | Ping falha                          | Containers em redes diferentes                    | Ver configuração Proxmox/containers | Colocar ambos na mesma bridge                      |                       |
| Mosquitto parado                   | Porta 1883 fechada                  | Serviço não arrancou                              | `systemctl status mosquitto`        | `sudo systemctl restart mosquitto`                 |                       |
| Mosquitto só local                 | Cliente recebe connection refused   | Broker em `127.0.0.1`                             | `ss -lntp`                          | Configurar `listener 1883 0.0.0.0`                 |                       |
| Firewall bloqueia                  | Ping funciona mas MQTT falha        | Porta 1883 bloqueada                              | `nc -vz <ip> 1883`                  | Abrir regra TCP 1883                               |                       |
| Tópico diferente                   | Subscriber não recebe               | Pub/Sub em tópicos diferentes                     | Comparar strings                    | Usar exatamente o mesmo tópico                     |                       |
| DNS falha                          | Broker remoto não resolve           | DNS errado no cliente                             | `getent hosts broker.hivemq.com`    | Corrigir DNS/gateway                               |                       |
| NAT outbound falha                 | DNS pode resolver mas TCP não liga  | OPNsense não faz NAT para fora                    | Testar `curl`, `nc`, firewall logs  | Corrigir outbound NAT/regra LAN                    |                       |
| Regra firewall na interface errada | Tráfego continua bloqueado          | Regra criada na WAN quando tráfego entra pela LAN | Ver interface de entrada            | Criar regra na interface por onde o pacote entra   |                       |
| Port forward errado                | Cliente externo não chega ao broker | NAT inbound mal configurado                       | Logs firewall / `tcpdump`           | WAN:1883 → broker:1883                             |                       |
| Porta TLS fechada                  | MQTT TLS não liga                   | Listener 8883 não configurado                     | `ss -lntp                           | grep 8883`                                         | Configurar `tls.conf` |
| Certificado inválido               | Erro TLS                            | CN/SAN não corresponde ao IP/nome                 | Ver erro do cliente                 | Usar SAN correto ou `--insecure` só em laboratório |                       |
| Permissões do certificado          | Mosquitto não arranca               | `server.key` sem permissões para Mosquitto        | `journalctl -u mosquitto`           | `chown mosquitto`, `chmod 640`                     |                       |
| Wireshark não mostra MQTT em TLS   | Só aparece TLS                      | Isto é esperado                                   | Filtrar `tcp.port == 8883`          | Explicar que payload está cifrado                  |                       |

---

## NAT explicado para conseguires defender oralmente

### Caso A — Cliente e broker na mesma bridge

```text
Cliente 192.168.10.10 → Broker 192.168.10.20:1883
```

Aqui **não há NAT**.

O tráfego é direto:

```text
origem: 192.168.10.10
destino: 192.168.10.20
porta destino: 1883
```

Frase para oral:

> Como cliente e broker estão na mesma rede, não preciso de NAT. Só preciso de conectividade local e de o broker estar a escutar na porta 1883.

---

### Caso B — Cliente interno usa broker remoto

```text
Cliente 192.168.10.10 → OPNsense → broker.hivemq.com:1883
```

Aqui há **NAT outbound**.

Antes do NAT:

```text
origem: 192.168.10.10
destino: broker.hivemq.com
porta: 1883
```

Depois do NAT:

```text
origem: IP_WAN_OPNsense
destino: broker.hivemq.com
porta: 1883
```

Frase para oral:

> Para comunicar com um broker remoto, o cliente usa o gateway. A firewall faz NAT outbound, substituindo o IP privado pelo IP da WAN.

---

### Caso C — Cliente externo quer aceder ao broker interno

```text
Cliente externo → WAN OPNsense:1883 → Broker interno:1883
```

Aqui precisas de **port forward**.

Regra conceptual:

```text
WAN TCP 1883  →  192.168.10.20 TCP 1883
```

Para TLS:

```text
WAN TCP 8883  →  192.168.10.20 TCP 8883
```

Frase para oral:

> Se o broker está dentro da rede privada e quero acesso externo, preciso de uma regra de port forwarding para encaminhar a ligação da WAN para o IP interno do broker.

---

### Erro mental mais comum sobre NAT

Pensar que NAT é o mesmo que firewall.

Não é.

| Função   | O que faz                   |
| -------- | --------------------------- |
| NAT      | Altera endereços/portas     |
| Firewall | Permite ou bloqueia tráfego |

Numa OPNsense podes precisar dos dois:

```text
NAT diz para onde vai.
Firewall decide se pode passar.
```

---

## 9. Perguntas típicas de avaliação

### Perguntas diretas

**1. O que é MQTT?**
MQTT é um protocolo leve de publish/subscribe usado em IoT, onde clientes comunicam através de um broker.

**2. O que é um broker MQTT?**
É o servidor que recebe mensagens publicadas em tópicos e as distribui aos clientes subscritos.

**3. Qual a diferença entre `mosquitto_pub` e `mosquitto_sub`?**
`mosquitto_pub` publica mensagens; `mosquitto_sub` subscreve tópicos e recebe mensagens.

**4. Para que serve a porta 1883?**
É a porta típica de MQTT sem encriptação.

**5. Para que serve a porta 8883?**
É a porta típica de MQTT sobre TLS.

**6. O que é TLS?**
É uma camada de segurança que cifra a comunicação entre cliente e broker.

**7. O que se vê no Wireshark com MQTT sem TLS?**
Podem ver-se pacotes MQTT, tópicos e payload em claro.

**8. O que se vê no Wireshark com MQTT sobre TLS?**
Vê-se tráfego TLS, mas não o conteúdo MQTT em claro.

---

### Perguntas de raciocínio

**1. Se o cliente não consegue publicar no broker local, onde investigas primeiro?**
Primeiro verifico IPs e conectividade com `ip a` e `ping`. Depois verifico se Mosquitto está ativo e se escuta em `0.0.0.0:1883`.

**2. Se o ping funciona mas MQTT não funciona, o que pode estar errado?**
Serviço Mosquitto parado, porta 1883 fechada, listener apenas em `127.0.0.1`, firewall a bloquear ou tópico errado.

**3. Se o DNS resolve `broker.hivemq.com`, mas a ligação à porta 1883 falha, qual é a hipótese?**
Pode haver problema de gateway, firewall outbound, NAT outbound ou bloqueio da porta TCP 1883.

**4. Se no Wireshark consegues ler a mensagem MQTT, o que significa?**
Significa que a comunicação está em claro, sem TLS.

**5. Se no Wireshark só aparece TLS e não aparece MQTT, isso é erro?**
Não. Se estiveres a usar porta 8883, é esperado. O MQTT está dentro do túnel TLS.

**6. Se um cliente externo não consegue chegar ao broker interno, o que verificas?**
Verifico port forward na WAN, regra firewall associada, IP interno do broker, porta correta e logs da firewall.

**7. Se criaste regra NAT mas continua sem funcionar, o que pode faltar?**
Pode faltar regra firewall a permitir o tráfego ou a regra pode estar na interface errada.

---

### Perguntas práticas

**1. Como confirmas o IP do broker?**

```bash
ip a
```

**2. Como confirmas que o Mosquitto está ativo?**

```bash
systemctl status mosquitto
```

**3. Como sabes se a porta 1883 está aberta?**

```bash
sudo ss -lntp | grep 1883
```

**4. Como testas publicação MQTT?**

```bash
mosquitto_pub -h <broker> -t "isep/teste" -m "teste"
```

**5. Como testas subscrição MQTT?**

```bash
mosquitto_sub -h <broker> -t "isep/teste" -v
```

**6. Como capturas MQTT em claro?**

```bash
sudo tcpdump -i any port 1883 -n
```

ou no Wireshark:

```text
mqtt
```

**7. Como verificas TLS?**

```text
tcp.port == 8883
```

Depois confirmas que a mensagem não aparece em claro.

---

## 10. Resumo para imprimir

# Resumo rápido — Guião 5

## Objetivo do guião

Estudar MQTT em contexto IoT:

* instalar broker e cliente MQTT;
* testar publish/subscribe;
* observar MQTT no tráfego;
* usar broker remoto;
* proteger MQTT com TLS/certificados.

---

## Conceitos principais

* **MQTT:** protocolo leve de mensagens usado em IoT.
* **Broker:** servidor que recebe e distribui mensagens.
* **Publisher:** cliente que envia mensagens.
* **Subscriber:** cliente que recebe mensagens.
* **Tópico:** nome/canal onde as mensagens são publicadas.
* **1883:** MQTT sem encriptação.
* **8883:** MQTT com TLS.
* **TLS:** cifra a comunicação.
* **NAT outbound:** permite cliente interno comunicar com broker externo.
* **Port forward:** permite cliente externo chegar a broker interno.

---

## Fluxo MQTT

```text
Publisher → Broker → Subscriber
```

Exemplo:

```text
mosquitto_pub → Mosquitto broker → mosquitto_sub
```

---

## Comandos essenciais

| Comando                                           | Para que serve                |                                  |
| ------------------------------------------------- | ----------------------------- | -------------------------------- |
| `ip a`                                            | Ver IPs das interfaces        |                                  |
| `ping -c 4 <ip>`                                  | Testar conectividade          |                                  |
| `sudo apt install mosquitto mosquitto-clients -y` | Instalar broker/clientes      |                                  |
| `systemctl status mosquitto`                      | Ver estado do broker          |                                  |
| `sudo ss -lntp                                    | grep 1883`                    | Ver se MQTT escuta na porta 1883 |
| `mosquitto_sub -h <broker> -t "topico" -v`        | Subscrever tópico             |                                  |
| `mosquitto_pub -h <broker> -t "topico" -m "msg"`  | Publicar mensagem             |                                  |
| `sudo tcpdump -i any port 1883 -n`                | Capturar MQTT em claro        |                                  |
| `getent hosts broker.hivemq.com`                  | Testar DNS                    |                                  |
| `nc -vz broker.hivemq.com 1883`                   | Testar TCP para broker remoto |                                  |
| `sudo ss -lntp                                    | grep 8883`                    | Ver porta MQTT TLS               |
| `mosquitto_pub -p 8883 --cafile ca.crt ...`       | Publicar com TLS              |                                  |

---

## Interpretações importantes

* Se `ping` falha, o problema é rede básica.
* Se `ping` funciona mas MQTT falha, verificar porta, serviço e firewall.
* Se `ss` mostra `127.0.0.1:1883`, o broker só aceita ligações locais.
* Se Wireshark mostra tópico e mensagem, MQTT está em claro.
* Se Wireshark mostra TLS mas não mostra payload, a comunicação está cifrada.
* Para broker remoto, precisas de DNS, gateway, firewall e NAT outbound.
* Para expor broker interno, precisas de port forward e regra firewall.

---

## Erros comuns

* IP errado do broker.
* Cliente e broker em bridges diferentes.
* Mosquitto parado.
* Mosquitto só a escutar em `localhost`.
* Porta 1883 bloqueada.
* Tópico publicado diferente do tópico subscrito.
* DNS errado no cliente.
* NAT outbound em falta.
* Port forward criado mas firewall não permite.
* Certificados TLS com permissões erradas.
* Certificado sem SAN correto para IP/nome usado.

---

## Frases para avaliação

* > MQTT usa modelo publish/subscribe, onde os clientes comunicam através de um broker.
* > A porta 1883 permite MQTT em claro, por isso o conteúdo pode ser observado numa captura.
* > A porta 8883 usa TLS, protegendo a confidencialidade das mensagens.
* > Se cliente e broker estão na mesma bridge, não preciso de NAT.
* > Se o cliente comunica com broker externo, preciso de gateway e NAT outbound.
* > Se quero expor broker interno para fora, preciso de port forwarding na firewall.
* > NAT altera endereços/portas; firewall decide se o tráfego passa ou não.

---

## 11. Checklist final

### Rede

* [ ] Cliente tem IP correto.
* [ ] Broker tem IP correto.
* [ ] Ambos estão na bridge/rede esperada.
* [ ] `ping cliente → broker` funciona.
* [ ] Gateway está correto para acesso externo.
* [ ] DNS resolve `broker.hivemq.com`.

### Broker local

* [ ] `mosquitto` instalado no broker.
* [ ] `mosquitto-clients` instalado no cliente.
* [ ] `systemctl status mosquitto` mostra `active`.
* [ ] `ss -lntp | grep 1883` mostra porta aberta.
* [ ] Listener está em `0.0.0.0`, não só em `127.0.0.1`.

### MQTT simples

* [ ] `mosquitto_sub` fica à espera.
* [ ] `mosquitto_pub` envia mensagem.
* [ ] Subscriber recebe mensagem.
* [ ] Wireshark/tcpdump mostra tráfego na porta 1883.
* [ ] Consegues explicar que a mensagem está em claro.

### Broker remoto

* [ ] `getent hosts broker.hivemq.com` funciona.
* [ ] `nc -vz broker.hivemq.com 1883` funciona.
* [ ] Publish/subscribe remoto funciona.
* [ ] Consegues explicar NAT outbound.

### MQTT com TLS

* [ ] Certificados criados.
* [ ] Mosquitto configurado na porta 8883.
* [ ] `ss -lntp | grep 8883` mostra porta aberta.
* [ ] Cliente usa `--cafile ca.crt`.
* [ ] Mensagem chega ao subscriber.
* [ ] Wireshark mostra TLS, não payload MQTT legível.

### NAT / Firewall

* [ ] Para saída para Internet: regra LAN permite TCP 1883/8883.
* [ ] NAT outbound está funcional.
* [ ] Para entrada externa: port forward WAN → broker interno.
* [ ] Regra firewall está na interface correta.
* [ ] Sabes explicar: **NAT encaminha/traduz; firewall permite/bloqueia.**
