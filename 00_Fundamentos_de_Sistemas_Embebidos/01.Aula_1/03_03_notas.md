**Functional Definition**

"An embedded system is a computing system designed to perform a dedicated function within a larger mechanical or electrical system."

**Ideias-chave: Funcao dedicada**

Um sistema embebido:
    Nao e geral (como um PC)
    Nao e multi proposito
    Existe para umma tarefa especifica
    Faz parte de um sistema maior

**Exemplos claros:**
    - Controlador de airbag num carro 
    - Firmaware de uma maquina de lavar
    - ECU (Engine Control Unit)
    - Termostato digital
    - Microcontrolador num drone

**Nao compras um embedded system como compras um laptop**
Ele esta escondido dentro de algo maior.

**2. Hardware-Software Integration Definition**
"Tightly coupled integration of hardware and software designed to interact with the physical wold under resource constraints."

***Ideias chave***
    1. Tight coupling HW + SW
    2. Interacao com o mundo fisico.
    3. Resource constraints.

***HW/SW Co-desing***
NUm sistema emvevidao, tu:
    . Escolhes o microcontrolador
    - Escolhes sensores e atuadores
    - Definis memoria disponivel
    - Depois escreves software adaptado a isso
Nao e como num PC onde o hardware ja esta claro.

Aqui tens decisoes do tipo:
    * buts chegam ?
    * Preciso de 32 bits?
    * Preciso de FPU ?
    * Quantos pinos GPIO?
    * Tenho RAM suficiente ?

***Isto e co-design ***- hardware e software eveloem juntos

***2. INteragir com o mundo fisico***
Embedded differs software pur

Um sistema embebido:
    * Le sensores (temperatura, pressao, aceleracao)
    * Controla atuadores (motores, reles, LEDS, valvulas)
    * Tem temporizacao real

Isto e fundamental:
    Esta ligado ao mundo real.

***3. Resource Constraints***

NUm embedded:
    - RAM limitada.
    - Flash limitada
    - CPU lenta
    - Latencia critica


***Quando desenvolvemos embedded, temos de desenhar hardware e software ao mesmo tempo***

MAS:
    * Normalmente nao desenhamos o microprocessador do zero.
    * Escolhemos um microcontrolador adequado.

Porque:
    * Mais consumo
    * Mais custo
    * Complexidade desnecessaria

Isto e engenharia racional

**Diferenca importante: Microprocessador vs Microcontrolador**

***Microprocessador***
    - Precisa de RAM externa
    - Precisa de perifericos externos
    - Exemplo: CPU de PC

***Microcontrolador***
    - CPU + RAM + Flash + GPIO + ADC tudo no mesmo chip
    - Exemplo: Arduino (ATmega328)
    Embedded tipico -> microcontrolador.

Resumo:
Embedded system =
    - Funcao dedicada
    - Parte de sistema maior
    - HW + SW co-design
    - Interage com mundo fisico
    - Recursos limitados

**Exemplo pratico**

***1. Sistema de monitorizacao automovel***
exemplo de:
    - Um dispositivo que liga a porta do carro (tipo OBD)
    - Le dados como
        . Acelaracap
        . RPM
        . Estado do motor
    - Comunica por Bluetooth
    - Mostra dados numa app no telemovel

Ideia central:
Mesmo um sistema simples e barato (~8euros) ja e um sistema embebido

***Constaints***
    - Temperatura do ambiente
    - Se esta dentro do habitaculo ou no motor.
    - Se esta exposto a agua.
    - Se precisa resistir a pressao.

Isto muda completamente o hardware.


***Conceito forte que ele esta a construir***
Se muda o ambiente -> muda o hardware -> muda o software.

Exemplo:
    . Temperatura elevada -> clock pode ter drift
    . Vibracao -> conectores podem falhar
    . Pouca energia -> tens de optimizar codigo

**TEMPO REAL (REAL-TIME SYSTEMS)**

***3. Real-Time-Oriented Definition***
    "An embedded system must produce correct results within defined timing constraints."

Ideia central: Nao basta estar correcto - tem de ser no tempo certo"
***Em sistemas normais ***
    - Se falha o tempo -> o sistema falhou.
    - Mesmo que o resultado esteja correcto.

***Tempo Deterministico***

Palavra chave da aula Determinismo temporal

Significa:
    Cada accao tem um tempo maximo garantido.

Nao e media
Nao e normalmente rapido
E limite garantido.

**Exemplo do aviao (Hard Real - time)***

Quando o piloto puxa o comando:
    1. O sistema detecta input.
    2. Processa
    3. Envia sinal para atuadores.
    4. Superficies movem-se
    Nao pode haver atraso imprevisivel

Se houver falha temporal:
    -> Pode levar a queda do aviao

**Isto e Hard Real-Time System. 

**Resource-Constrained Definition**

***Sistema especializado sob limitacoes de memoria, CPU e energia***

Aqui junta se:
    - Tempo limitado
    - Memoria limitada
    - Energia limitada
    - Custo limitado

    Embedded e sempre compromisso

***Ligacao importante***
Quando comecar :
 - RTOS
 - SCHEDULERS
 _Interrupts
 - Latencia 
 - Jitter
 - Deadlines
 tudo isto vem daqui.


**5. Energy & Memory Constraints**

O professor reforcou:
    O foco esta nas limitacoes do sistema.


***Sistemas a bateria***
Se o sistema funciona a bateria:
    - Energia e recurso critico
    - Nao pode estar sempre activo
    - Precisa de:
        - Sleep modes 
        - Power management
        - Wake-up por interrupcao

***Regra pratica***
    Se nao esta a fazer nada -> deve estar desligado ou em lower power mode.

Isto e essencial em:
    . IOT
    . Sensores remotos
    . Wearables
    . Dispositivos medicos

**MEMORIA LIMITADA**

Em embedded:
    - RAM pode ser alguns KB
    - Flash pode ser dezenas de KB
    - As vezes nem ha heap.

Implica:
    - Nada de desperdicio
    - Cuidado com buffers 
    - Stack overflow e real
    - Estruturas simples
    - Codigo eficiente

**MEMORIA - conceitos fundamentais**

ROM / FLASH
    - Nao volatil
    - Mantem dados sem energia 
    - Guarda o programa (firmware)
    - Pode ser reprogramada (FLASH)

RAM 
    - Voltatil
    - Usada durante execucao
    - Variaveis, stack, buffers

Ponto importante:
    Surante execucao, podes modificar RAM.
    Flash normalmente nao e alterada em runtime.

**8051 - Arquitetura Classica**
O 8051 e um microcrontrolador historico mas extremamente importante.

CPU Core
    - 8-bit CPU
    - Arquitetura HARVARD
        - Memoria de programa separada da memoria de dados
    - CISC
    - 12 ciclos de clock por machine cycle (classico)

***Memoria de Programa***
- 4KB ROM interna
- Expansivel ate 64 KB externa
- Barramento de enderecos de 16 bits

***Memoria de Dados***
128 bytes RAM intera (!)
32 bytes -> bancos de registos
16 bytes -> bit-addressable
Expansivel ate 64 KB externa

Repara:
Estamos a falar de bytes, nao KB

***I/O Ports***
    - 4 portas de 8bits
    - 32 pinos programaveis
    - Alguns pinos tem funcoes alternativas:
        - Comunicacao serial
        - Interupcoes
        - Interface memoria externa
    Isto mostra integracao tipica de mecrocontrolados.

***Timers/Counters***
2 timers de 16 bits
Modos:
    - Timer (clock interno)
- Modos de operacao
    - 8-bit
    - 16-bit
    - Auto-reload
    - Split mode
Timers sao fundamentais para:
    - Temporizacao
    - Baud rate
    - Geracao de eventos periodicos

Comunicacao Serial
    - 1 UART full-duplex
    - Modo sincrono e assincrono
    - Baud rate configuravel (normalmente via Timer 1)

Sistema de interrupcoes
- 5 fontes de interrupcao:
    - 2 externas
    - 2 timers
    - 1 serial
- 2 niveis de prioridade

Interrupcoes permitem:
    Reagir a eventos sem polling constante

***CLock & Oscillator***

    - Oscilador interno
    - Cristal externo tipico: 11.0592 MHz
    - 12 ciclos de clock por instrucao

    Isto impacta 
        - Tempo de execucao
        - Determinismo
        - Calculo de delays

**BUS structure**
- address bus: 16-bit
- Data bus: 8-bit
- Sinais de controlo
    - PSEN
    - RD
    - WR
    - ALE

**Power Modes**
- Idle mode
- Power down ode
- Reset pin


***Super - Loop Architeture ***

    
        int main(void)
        {
            init_hardware();
            while(1)
            {
                reaf_inputs();
                process_data();
                update_outputs();
            }
        }
    

🔹 1990–2010: Networked Embedded Systems

Aqui há uma mudança arquitetural enorme.

🏗️ Architectural Shift

Antes:
→ Um microcontrolador isolado

Agora:
→ Muitos nós embebidos interligados

Comunicação via:

🚗 CAN (automóvel)

🏭 Profibus / Modbus / Industrial Ethernet

🏠 KNX (domótica)

✈️ ARINC 629 / AFDX (aviónica)

🔹 Introdução do RTOS

Sistemas passam a:

Ter múltiplas tarefas

Executar em paralelo lógico

Usar preemptive scheduling

Diferença para PC:

PC:
→ Maximizar throughput

RTOS:
→ Garantir deadlines

🎯 Objetivo do RTOS:
Executar tarefas prioritárias dentro do tempo definido.

🔹 Novos Problemas: Sincronização

Quando passamos para múltiplos nós, aparecem problemas novos.

⏱️ Clock Drift & No Global Time

Cada nó:

Tem o seu próprio clock

O clock deriva ao longo do tempo

Não existe tempo global perfeito

Consequências:

Timestamps inconsistentes

Erros de ordenação de eventos

🌐 Communication Delays

Latência variável

Jitter

Perda de pacotes

Atrasos assimétricos

Exemplo dado:
Rede 802.11 partilhada

Se muitos dispositivos comunicam:
→ Latência aumenta.

🔄 Concurrency & Shared Resources

Quando vários nós acedem a dados partilhados:

Race conditions

Deadlocks

Priority inversion

Resultado:
→ Estado inconsistente do sistema.

⚠️ Faults & Node Failures

Tipos:

Crash faults

Byzantine behavior

Network partitioning

Pode acontecer:

→ Nós discordam sobre o estado do sistema.

Isto é extremamente crítico em:

Automóvel

Aviónica

Sistemas industriais

🔹 Real-Time Constraints

Deadlines têm de ser cumpridas

Determinismo é obrigatório

Erros temporais podem causar falhas de segurança

**Syncronization - Solucoes**

***Tecnicas tupicas***
    - Clock syncronization ( NTP, PTP, TTP )
    - Time-triggered architectures
    - Mutual exclusion (mutexes)
    - Consensus algoritms
    - Redundancia de comunicacao

📌 Linha evolutiva resumida
Era	Complexidade	Problema Principal
1980 ->	Simples	Limitação de recursos
1995-> Comunicação	Sincronização
2005-> Distribuído	Consistência
2010+ -> Cloud/IoT	Segurança + Escala

Num sistema distribuído:

Múltiplos clocks

Drift

Logs desalinhados

Jitter

Eventos fora de ordem

👉 Debug pode passar de dias → semanas.

E isto é completamente real no mundo industrial.

🔧 Soluções Introduzidas

NTP / PTP / TTP

Time-triggered architectures

Mutex / exclusão mútua

Algoritmos de consenso

Comunicação redundante

Mas:

🔴 Nada elimina totalmente o problema.
Só o torna controlável.

***2010 - HOJE -> Cloud-Connected Architecture***
Agora temos:
    - Edge devices
    - Gateways
    - Cloud backends
    - AI / Analytics
    - Sistemas distribuidos em multiplas camadas.

Camadas:
    1. Physical layer
    2. Embedded mode
    3. Edge processing
    4. Cloud platform
    5. AI / Analytics

    Complexidade -> ainda maior.

Insight mais importante da Aula
em sistemas distribuidos nao se testa e ve-se

Tem de se: 

    - Pensar muito antes
    - Modelar antes
    - Definir garantias temporais antes
    - Garantir determinismo matematicamente

    Porque:
    Debug pode custar semanas

    