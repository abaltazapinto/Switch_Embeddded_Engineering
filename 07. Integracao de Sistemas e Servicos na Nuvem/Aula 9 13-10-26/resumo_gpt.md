# Aula 9 — Industrial IoT: Predictive Maintenance E2E Pipeline

**Fontes usadas**
- **Primária:** SRT da aula de 13/10/2026.
- **Secundária:** `INSISN-TP9(1).pdf`, 22 slides.
- Regra aplicada: **SRT > slides**.
- Quando o slide contém algo que o professor não explicou de forma clara, marco isso explicitamente.

A ideia desta aula foi sobretudo **fechar e integrar a matéria anterior numa pipeline completa de Industrial IoT**, usando como exemplo manutenção preditiva de um motor.

---

# 1. Reconstruct the Lecture

## 1.1 Objetivo da aula

Logo no início, o professor define a sessão como uma **conclusão/integração** do que tinha sido visto anteriormente.

O cenário escolhido foi:

> **Máquina industrial → sensores → recolha de temperatura/vibração → transporte → contexto atual → histórico → dashboard/alertas**

Exemplo físico:

- uma máquina/motor industrial;
- sensores medem:
  - **temperatura**;
  - **vibração**;
- pretende-se usar esses dados para detetar condições anormais e apoiar **manutenção antes da avaria**.

### Pipeline global ensinada

```text
Motor / Sensores
      ↓
    MQTT
      ↓
 Mosquitto
      ↓
 IoT Agent JSON
      ↓
 FIWARE Orion
      ↓
 Subscription / notification
      ↓
Persistence connector
      ↓
 TimescaleDB
      ↓
   Grafana
```

O professor volta a esta arquitetura várias vezes durante a aula.

---

## 1.2 Papel de cada componente

### 1. Mosquitto / MQTT

Os sensores produzem telemetria e publicam os valores através de **MQTT**.

Exemplo:

```json
{
  "t": 72.5,
  "v": 3.8
}
```

onde:

- `t` → temperature;
- `v` → vibration.

O **Mosquitto** funciona como MQTT broker.

Mentalmente:

```text
sensor → publica mensagem → broker MQTT → consumidor recebe
```

O objetivo é desacoplar quem produz os dados de quem os consome.

---

### 2. IoT Agent

O professor reforça explicitamente uma ideia importante:

> **o IoT Agent funciona como tradutor de protocolos.**

Neste caso:

```text
MQTT / dispositivo
       ↓
   IoT Agent
       ↓
NGSI / REST / FIWARE
```

Assim, o Orion não precisa de conhecer os detalhes específicos de comunicação do sensor.

O IoT Agent fica entre:

- o mundo dos dispositivos;
- o mundo FIWARE.

---

### 3. Orion Context Broker

O **Orion** mantém o **estado/contexto atual** da entidade.

Exemplo:

```text
Machine001

temperature = 72.5
vibration   = 3.8
```

Se chegar depois:

```text
temperature = 92.0
vibration   = 9.4
```

o Orion representa essencialmente a **imagem atual** da máquina.

Este ponto é fundamental:

> Orion não é apresentado na aula como a base de dados histórica da máquina.

Ele mantém o **contexto atual**.

---

### 4. TimescaleDB

Para responder a perguntas como:

- como variou a temperatura nas últimas duas horas?
- a vibração tem aumentado?
- quando começou a degradação?
- existe tendência antes da avaria?

é necessário guardar **histórico**.

Para isso foi usada **TimescaleDB**.

A separação ensinada foi:

```text
Orion
→ estado atual

TimescaleDB
→ evolução histórica
```

---

### 5. Grafana

Por fim:

```text
TimescaleDB
    ↓
 Grafana
```

O Grafana é usado para:

- gráficos temporais;
- estado atual;
- tendências;
- alertas.

Exemplos da aula:

- Temperature over time;
- Vibration over time;
- Last measured state;
- alertas de temperatura/vibração.

---

# 1.3 Estrutura do projeto com Docker Compose

O professor apresenta uma estrutura típica:

```text
industrial-iot-demo/
├── docker-compose.yml
├── .env
├── mosquitto/
│   └── mosquitto.conf
├── iot-agent/
│   └── config.js
└── scripts/
    └── simulate-telemetry.sh
```

A ideia é ter toda a infraestrutura reproduzível através de containers.

Os serviços apresentados foram aproximadamente:

```text
Orion
IoT Agent
Mosquitto
TimescaleDB
Grafana
```

e deveria também existir o componente responsável pela persistência, assunto que o próprio professor deteta mais tarde na aula.

---

# 1.4 Portas apresentadas

### Orion

```text
1026
```

Mapeamento:

```text
host:1026 → container:1026
```

---

### IoT Agent

```text
4041
```

O IoT Agent comunica:

```text
MQTT broker → 1883
Orion       → 1026
```

---

### Mosquitto

Nos slides:

```yaml
ports:
  - "1883:1883"
  - "9001:9001"
```

A porta principal usada no exemplo MQTT é:

```text
1883
```

---

### TimescaleDB/PostgreSQL

```text
5432
```

---

### Grafana

```text
3000
```

Portanto, um mapa simples para estudar:

| Componente | Porta |
|---|---:|
| Orion | 1026 |
| IoT Agent | 4041 |
| MQTT/Mosquitto | 1883 |
| PostgreSQL/TimescaleDB | 5432 |
| Grafana | 3000 |

📓 **Guardar no caderno:** estes números ajudam a reconstruir mentalmente a arquitetura.

---

# 1.5 Arranque da infraestrutura

O professor recomenda explicitamente três comandos:

```bash
docker compose config
```

```bash
docker compose up -d
```

```bash
docker compose ps
```

O ponto mais importante não foi decorar comandos, mas o raciocínio:

> Depois de subir uma infraestrutura com vários containers, **confirmar sempre que todos arrancaram corretamente**.

Porque pode acontecer:

```text
A → B → C → D
        ✗
```

e depois parecer que o problema está em D quando, na verdade, C nunca arrancou.

O professor deu precisamente esse exemplo baseado na sua experiência.

---

# 1.6 Provisioning do dispositivo

Depois da infraestrutura estar disponível, foi registado um dispositivo no **IoT Agent**.

Foi usado um pedido REST para:

```text
/iot/devices
```

O dispositivo:

```text
device_id: motor001
entity_name: Machine001
entity_type: IndustrialMachine
```

com dois atributos:

```text
t → temperature → Number
v → vibration   → Number
```

Mentalmente:

```text
motor001
   │
   ├── t → temperature
   └── v → vibration
```

Depois deste provisioning, o IoT Agent passa a conhecer:

- qual é o dispositivo;
- qual a entidade correspondente;
- como interpretar `t`;
- como interpretar `v`;
- qual o protocolo/transporte.

---

# 1.7 Simulação da telemetria

Como não havia uma máquina real ligada, a aula usa:

```text
mosquitto_pub
```

para simular o sensor.

Estado normal, por exemplo:

```json
{"t":72.5,"v":3.8}
```

Depois é simulado um estado mais grave:

```json
{"t":92.0,"v":9.4}
```

O objetivo era mostrar que podemos simular:

```text
normal → warning → anomaly
```

sem necessitar do hardware real.

---

# 1.8 O fluxo da mensagem

Esta sequência é muito importante:

```text
1. mosquitto_pub
        ↓
2. MQTT Broker
        ↓
3. IoT Agent
        ↓
4. Orion Context Broker
```

O IoT Agent recebe a mensagem MQTT e traduz os dados para o modelo compreendido pelo FIWARE.

---

# 1.9 Verificar o estado no Orion

Depois da publicação é possível consultar:

```text
Machine001
```

através da REST API do Orion.

A resposta é JSON contendo, entre outros dados:

```text
temperature
vibration
```

O professor relaciona isto diretamente com o conceito de contexto:

> consultar a entidade no Context Broker devolve o **estado atual daquela entidade**.

---

# 1.10 Porque precisamos de TimescaleDB?

Aqui começa a segunda metade da pipeline.

O Orion responde essencialmente:

```text
"Como está a máquina agora?"
```

Mas para manutenção preditiva precisamos também:

```text
"Como chegou até este estado?"
```

Logo:

```text
estado atual     → Orion
histórico        → TimescaleDB
```

---

# 1.11 Estrutura da tabela temporal

Foi criada uma tabela semelhante a:

```sql
CREATE TABLE machine_telemetry (
    time TIMESTAMPTZ NOT NULL,
    machine_id TEXT NOT NULL,
    temperature DOUBLE PRECISION,
    vibration DOUBLE PRECISION
);
```

O professor explica campo a campo.

### `time`

É essencial porque temos uma série temporal.

Cada valor tem de responder:

```text
quando foi medido?
```

---

### `machine_id`

Permite distinguir máquinas diferentes.

Exemplo:

```text
motor001
motor002
motor003
```

---

### `temperature`

Número real.

---

### `vibration`

Número real.

---

### Porque temperatura e vibração não aparecem como `NOT NULL`?

O raciocínio dado foi:

uma máquina pode eventualmente fornecer apenas um dos parâmetros.

Assim podemos ter:

```text
timestamp ✔
machine_id ✔
temperature ✔
vibration NULL
```

sem invalidar toda a observação.

---

# 1.12 Hypertable

A tabela PostgreSQL é depois convertida numa **TimescaleDB hypertable**.

Conceito ensinado:

> otimizar a tabela para consultas baseadas no tempo.

A ideia apresentada pelo professor foi que TimescaleDB organiza/particiona os dados temporalmente para tornar consultas históricas mais eficientes.

Não foi explicado internamente **como** o TimescaleDB implementa essa otimização.

Portanto:

**Not clearly covered in the lecture:** funcionamento interno das hypertables, índices internos ou algoritmo de particionamento.

Para esta aula basta:

```text
normal PostgreSQL table
         ↓
 create_hypertable(...)
         ↓
time-series optimized table
```

---

# 1.13 Executar SQL dentro do container

Como a base de dados está num container:

```text
host
  ↓ docker exec
container TimescaleDB
  ↓
psql
  ↓
SQL
```

Foi mostrado o uso de:

```text
docker exec
```

com `psql`.

O professor também refere como alternativa uma ferramenta gráfica, como:

- DBeaver;
- pgAdmin.

Mas estas ferramentas não foram ensinadas em profundidade.

---

# 1.14 Container security — utilizador root

Durante esta parte o professor recupera uma ideia já discutida anteriormente:

> um processo dentro de um container não deveria desnecessariamente correr como `root`.

O raciocínio é de redução de privilégios.

Por isso questionou se o Compose deveria indicar explicitamente o utilizador PostgreSQL.

Contudo, ele próprio disse que precisava de confirmar a configuração.

Portanto:

**Not clearly covered in the lecture:** configuração final correta do utilizador PostgreSQL no `docker-compose.yml`.

---

# 1.15 Persistência através de subscriptions

Depois da tabela estar pronta surge uma pergunta:

> Como é que cada atualização do Orion chega automaticamente à base de dados?

Resposta:

## Subscription

É criada uma subscription no Orion para:

```text
Machine001
```

monitorizando:

```text
temperature
vibration
```

Quando há uma alteração:

```text
Orion
  ↓ HTTP notification
Persistence connector
  ↓
TimescaleDB
```

Isto é um conceito central desta aula.

---

# 1.16 O persistence connector

O professor explica que o connector:

1. recebe a notificação HTTP do Orion;
2. extrai os dados;
3. insere-os na tabela temporal.

Ou seja:

```text
Orion NÃO escreve diretamente na TimescaleDB.
```

Existe um intermediário.

```text
Orion
    ↓ notification
connector
    ↓ INSERT
TimescaleDB
```

O servidor do connector precisa de receber pedidos HTTP porque as notificações chegam dessa forma.

---

# 1.17 Grafana

Quando já existe histórico:

```text
TimescaleDB
     ↓
 Grafana
```

O professor apresenta três tipos de informação.

### Painel 1 — Temperature over time

Algo equivalente a:

```sql
SELECT
    time,
    temperature
FROM machine_telemetry
WHERE ...
ORDER BY time;
```

Resultado conceptual:

```text
Temperature
   ↑
90 |             *
80 |        *
70 | *  *
   +----------------→ time
```

---

### Painel 2 — Vibration over time

Mesma lógica:

```text
vibration(t)
```

Permite observar tendência/degradação.

---

### Painel 3 — Last measured state

Queremos apenas a medição mais recente.

A ideia do SQL apresentado é:

```sql
ORDER BY time DESC
LIMIT 1;
```

Mentalmente:

```text
mais recente
↓
10:30
10:25
10:20
10:15
```

e:

```text
LIMIT 1
```

fica apenas com:

```text
10:30
```

---

# 1.18 Exemplo de evolução da máquina

Foi mostrada uma sequência semelhante:

| Time | Temp. | Vibration | Interpretação |
|---|---:|---:|---|
| 18:30:00 | 71.2 | 3.5 | normal |
| 18:30:05 | 72.5 | 3.8 | normal |
| 18:30:10 | 78.9 | 5.2 | subida |
| 18:30:15 | 86.2 | 7.1 | warning |
| 18:30:20 | 92.0 | 9.4 | anomaly |

O ponto importante não são estes números específicos.

É perceber:

```text
uma medição isolada
        ↓
pouca informação

muitas medições ordenadas no tempo
        ↓
tendência
        ↓
possível degradação
```

---

# 1.19 Frequência de amostragem

Esta foi uma boa observação prática da aula.

Pode parecer que:

```text
mais medições = sempre melhor
```

mas isso não é verdade.

Mais frequência implica:

- mais mensagens;
- mais processamento;
- mais armazenamento;
- mais tráfego;
- potencialmente dados desnecessários.

O professor dá a ideia de que a frequência deve depender do processo observado.

Por exemplo:

```text
motor com dinâmica rápida
→ poderá precisar de aquisição frequente

processo térmico lento
→ poderá não precisar de uma amostra por segundo
```

A decisão deve ser feita com **especialistas do domínio**.

📓 **Guardar no caderno:**

> Sampling frequency must match the dynamics of the physical process.

---

# 1.20 Alertas

O Grafana pode gerar alertas quando os dados atingem estados considerados anormais.

No exemplo:

```text
temperature > 90 °C
```

ou:

```text
vibration > 8.0
```

Exemplo conceptual:

```sql
CASE
    WHEN temperature > 90.0 OR vibration > 8.0
    THEN 1
    ELSE 0
END
```

---

## OR vs AND

O professor explicou explicitamente a diferença.

### OR

```text
temperature > 90 OR vibration > 8
```

Alerta se **qualquer uma** das situações ocorrer.

---

### AND

```text
temperature > 90 AND vibration > 8
```

Só alerta quando **as duas** condições forem simultaneamente verdadeiras.

A analogia dada foi aproximadamente:

```text
uma lâmpada de alerta para duas situações
→ OR

duas indicações independentes
→ alertas separados
```

---

# 1.21 Conclusão conceptual da aula

O professor termina com duas ideias muito importantes.

## A. Desacoplamento

As aplicações do lado superior da arquitetura não precisam de saber:

- qual sensor físico existe;
- que protocolo específico utiliza;
- como a máquina comunica.

Elas comunicam através do contexto FIWARE.

```text
Sensors
   ↓
IoT Agent
   ↓
Orion
   ↓
Applications
```

O IoT Agent faz a tradução entre:

```text
linguagem específica do dispositivo
           ↓
linguagem comum/contextual
```

---

## B. Separação entre estado atual e histórico

```text
                ┌→ Orion
sensor updates ─┤  current state
                │
                └→ TimescaleDB
                   historical state
```

Mais precisamente, o histórico é alimentado através das notificações provenientes do Context Broker.

Esta é provavelmente a relação conceptual mais importante da Aula 9.

---

# 2. Explain Difficult Parts Simply

## 2.1 Orion vs TimescaleDB

Imagine um quadro branco numa fábrica.

No quadro está:

```text
Motor A
Temperature: 84 ºC
Vibration: 6.1
```

Quando chega uma medição nova, apaga-se o valor anterior e escreve-se o novo.

Isso é aproximadamente o papel do:

> **Orion → fotografia atual.**

Agora imagine que alguém tira uma fotografia ao quadro de 5 em 5 segundos e guarda tudo num arquivo.

Isso é:

> **TimescaleDB → filme histórico.**

Para manutenção preditiva, precisamos dos dois.

---

## 2.2 IoT Agent

Imagine que o sensor fala japonês e o Orion fala português.

O IoT Agent é o intérprete:

```text
sensor MQTT
"t = 72.5"
      ↓
IoT Agent
      ↓
Orion
"temperature = 72.5"
```

Assim o resto do sistema não precisa de aprender a linguagem específica de cada dispositivo.

---

## 2.3 Subscription

Uma subscription é semelhante a dizer ao Orion:

> “Sempre que `Machine001.temperature` ou `vibration` mudar, avisa este endereço.”

Sem subscription:

```text
DB: "Orion, tens novidades?"
DB: "E agora?"
DB: "E agora?"
```

Com subscription:

```text
Orion: "Mudou! Aqui estão os novos dados."
```

É um modelo muito mais orientado a eventos.

---

## 2.4 Hypertable

Uma tabela normal pode ser imaginada como um arquivo enorme.

A hypertable organiza esse arquivo tendo **tempo** como elemento central.

Em vez de procurar cegamente milhões de registos:

```text
2019
2020
2021
...
2026
```

TimescaleDB pode estruturar os dados em blocos temporais adequados para consultas de séries temporais.

A implementação interna:

**Not clearly covered in the lecture.**

---

## 2.5 Desacoplamento

Sem desacoplamento:

```text
Grafana → sabe como comunicar com sensor A
Grafana → sabe como comunicar com sensor B
App → sabe como comunicar com sensor A
...
```

Torna-se complexo.

Com a arquitetura:

```text
Sensors → IoT Agent → Orion ← Applications
```

as aplicações precisam conhecer essencialmente o **modelo contextual**, não cada protocolo físico.

---

# 3. Detect and Correct Issues

Há alguns pontos importantes em que o próprio professor mostrou incerteza ou os slides têm inconsistências.

## 3.1 `Dockerfile` vs `docker-compose.yml`

Durante a explicação, o professor chama várias vezes ao ficheiro mostrado **Dockerfile**.

Mas o slide e o conteúdo são claramente:

```text
docker-compose.yml
```

São conceitos diferentes.

### Correção

```text
Dockerfile
→ descreve como construir uma imagem

docker-compose.yml
→ descreve vários serviços/containers e como os ligar
```

Nesta aula está a ser usado **Docker Compose**, não um Dockerfile.

---

## 3.2 Mosquitto: 1883 vs 9001

O professor diz aproximadamente:

> 1883 para subscriptions e 9001 para publications

e imediatamente demonstra incerteza.

Isto **não deve ser decorado dessa forma**.

O slide apenas configura:

```yaml
1883:1883
9001:9001
```

Em configurações típicas:

- `1883` → MQTT TCP;
- `9001` pode ser configurada para WebSockets.

Publish e subscribe podem ambos ocorrer através de MQTT em `1883`.

Portanto a distinção:

```text
1883 = subscribe
9001 = publish
```

é uma **explicação incorreta/insegura da aula**.

---

## 3.3 Persistence connector em falta

Este é o erro mais evidente que o próprio professor encontra.

A arquitetura precisa:

```text
Orion
 ↓
telemetry/persistence connector
 ↓
TimescaleDB
```

Mas o Docker Compose mostrado inicialmente contém:

```text
Orion
IoT Agent
Mosquitto
TimescaleDB
Grafana
```

e não mostra claramente o `telemetry-connector`.

Mais tarde o professor repara nisso explicitamente.

### Portanto

A arquitetura conceptual está correta, mas o Compose mostrado é **incompleto para implementar exatamente o fluxo de persistência apresentado**.

---

## 3.4 `ORDER BY` para obter o valor mais recente

No slide aparece corretamente:

```sql
ORDER BY time DESC
LIMIT 1;
```

Em alguns momentos a transcrição SRT produz frases como “ordenar de crescente”.

Para obter **o valor mais recente primeiro**, precisamos:

```text
DESC
```

Exemplo:

```text
10:30 ← primeiro
10:20
10:10
```

Logo:

```sql
ORDER BY time DESC LIMIT 1
```

é a versão coerente com o objetivo explicado.

---

## 3.5 Postman / curl

A transcrição contém termos como:

```text
Postmaster
Carol
```

Isto resulta claramente da transcrição automática.

Os termos técnicos utilizados são:

```text
Postman
curl
```

O professor estava a comparar:

```text
Postman → GUI para HTTP requests
curl    → linha de comandos
```

---

## Algo presente nos slides mas não claramente desenvolvido no SRT

O último slide menciona:

- scalability;
- OAuth2;
- TLS;
- PEP proxies;
- edge computing;
- offline operation;
- store-and-forward.

Contudo, estes tópicos **não foram realmente desenvolvidos na explicação oral da Aula 9**.

Assim:

> **Not clearly covered in the lecture.**

Não os trataria como matéria central desta aula só porque aparecem no último slide.

---

# 4. 30-Min Notebook Summary

## 📓 Aula 9 — resumo para escrever

### Industrial IoT Predictive Maintenance

Objetivo:

```text
Monitorizar motor → detetar degradação → alertar antes da avaria
```

Sensores:

- temperatura;
- vibração.

---

### Pipeline

```text
Sensors
  ↓
MQTT
  ↓
Mosquitto
  ↓
IoT Agent
  ↓
Orion
  ↓
Subscription
  ↓
Persistence Connector
  ↓
TimescaleDB
  ↓
Grafana
```

---

### MQTT / Mosquitto

- protocolo de mensagens;
- sensores publicam telemetria;
- broker desacopla producer/consumer.

---

### IoT Agent

- traduz protocolo dispositivo → FIWARE/NGSI;
- MQTT → contexto FIWARE;
- conhece mapping dos atributos.

Ex.:

```text
t → temperature
v → vibration
```

---

### Orion Context Broker

- mantém **estado atual/contexto**;
- REST API;
- entidade:

```text
Machine001
temperature
vibration
```

---

### TimescaleDB

- mantém **histórico**;
- dados organizados temporalmente.

```sql
time
machine_id
temperature
vibration
```

Diferença:

```text
Orion = NOW
TimescaleDB = HISTORY
```

---

### Hypertable

```text
PostgreSQL table
↓
Timescale hypertable
```

- otimizada para time-series;
- particionamento temporal.

Implementação interna: **not covered**.

---

### Subscription

```text
context changes
↓
Orion notification
↓
connector
↓
TimescaleDB
```

Evita polling constante.

---

### Grafana

Mostra:

- temperature vs time;
- vibration vs time;
- last value;
- alerts.

Último valor:

```sql
ORDER BY time DESC
LIMIT 1
```

---

### Alertas

Exemplo:

```text
T > 90 °C
OR
vibration > 8
```

`OR` → uma condição basta.

`AND` → ambas necessárias.

---

### Sampling

Mais frequência:

```text
+ detalhe
- mais dados
- mais rede
- mais storage
- mais processamento
```

Frequência depende do processo físico.

---

### Docker Compose

Containers:

```text
Orion       1026
IoT Agent   4041
Mosquitto   1883
TimescaleDB 5432
Grafana     3000
```

Arranque/verificação:

```text
docker compose config
docker compose up -d
docker compose ps
```

---

### Ideias finais

**1. Decoupling**

```text
devices ≠ applications
```

IoT Agent + brokers escondem detalhes de comunicação.

**2. Separation of concerns**

```text
Orion = current context
TimescaleDB = historical context
Grafana = visualization
```

---

# 5. Explain Core Concepts — only hard ones

## Concept 1 — Context vs history

```text
Orion      = fotografia
TimescaleDB = álbum de fotografias
```

Uma fotografia diz como a máquina está agora.

O álbum permite perceber tendência e degradação.

---

## Concept 2 — IoT Agent as protocol adapter

```text
device-specific protocol
        ↓
     IoT Agent
        ↓
common FIWARE representation
```

O resto do sistema fica independente da tecnologia específica do sensor.

---

## Concept 3 — Subscription/event-driven persistence

Não queremos perguntar continuamente:

```text
"mudou?"
"mudou?"
"mudou?"
```

Registamos interesse uma vez.

Depois:

```text
mudança → notification
```

---

## Concept 4 — Time-series database

Numa base temporal, a pergunta quase sempre envolve:

```text
valor + instante
```

Ex.:

```text
temperature at 10:21
temperature at 10:22
temperature at 10:23
```

É a sequência que permite observar tendências.

---

## Concept 5 — End-to-end decoupling

Cada camada tem uma função:

```text
sensor        → acquisition
MQTT          → transport
IoT Agent     → translation
Orion         → context
TimescaleDB   → history
Grafana       → visualization
```

Se uma aplicação precisar de dados, não necessita conhecer diretamente o sensor.

---

# 6. Essential Exam Questions

## Q1 — Conceptual

**Qual é a diferença principal entre Orion Context Broker e TimescaleDB?**

**Resposta:**  
Orion mantém o **estado/contexto atual** das entidades; TimescaleDB mantém o **histórico temporal** das medições.

**Reasoning:** São responsabilidades diferentes: current state vs time-series history.

---

## Q2 — Conceptual

**Qual é o papel do IoT Agent nesta arquitetura?**

**Resposta:**  
Traduz a comunicação/protocolo utilizado pelos dispositivos para a representação compreendida pelo ecossistema FIWARE/Orion.

**Reasoning:** Desacopla o Context Broker dos detalhes específicos dos dispositivos.

---

## Q3 — Practical

Chega:

```json
{"t":92.0,"v":9.4}
```

com limites:

```text
temperature > 90
vibration > 8
```

e regra `OR`. Existe alerta?

**Resposta:** Sim.

**Reasoning:** As duas condições são verdadeiras; com `OR` bastaria apenas uma.

---

## Q4 — Practical

Pretendes obter apenas a medição mais recente de `motor001`. Que princípio SQL utilizarias?

**Resposta:**

```sql
ORDER BY time DESC
LIMIT 1
```

**Reasoning:** `DESC` coloca o timestamp mais recente primeiro e `LIMIT 1` seleciona apenas esse registo.

---

## Q5 — Multiple choice

Qual sequência representa melhor a pipeline ensinada?

**A.** Sensor → Grafana → Orion → MQTT  
**B.** Sensor → MQTT → IoT Agent → Orion → persistence → TimescaleDB → Grafana  
**C.** Sensor → TimescaleDB → MQTT → Orion  
**D.** Grafana → Sensor → IoT Agent → MQTT

**Resposta:** **B**

**Reasoning:** corresponde ao fluxo E2E usado durante toda a demonstração.

---

# 7. Common Pitfalls

- **Confundir Orion com uma base histórica.**  
  Orion representa principalmente o contexto atual; o histórico fica na TimescaleDB.

- **Pensar que o Orion escreve diretamente na TimescaleDB.**  
  Na arquitetura apresentada existe uma subscription/notificação e um persistence connector intermediário.

- **Confundir Dockerfile com `docker-compose.yml`.**  
  Nesta aula a infraestrutura é descrita com Docker Compose.

- **Usar `ORDER BY time ASC LIMIT 1` para o último valor.**  
  Isso devolveria o mais antigo. Para o mais recente: `DESC LIMIT 1`.

- **Pensar que aumentar indefinidamente a sampling frequency é sempre melhor.**  
  A frequência deve refletir a dinâmica real do processo e o custo de transporte/processamento/storage.
