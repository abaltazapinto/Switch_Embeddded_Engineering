**Ação (1 passo):** usa este prompt para analisar o teu trabalho com base no enunciado que enviaste. O enunciado cobre 4 blocos: mapeamento switches/LEDs, sequenciamento com temporização e pausa, sistema de furação com debounce e display, e cronómetro com TC0 em CTC a 2 ms. Isso está descrito nas páginas 1–5 do PDF. 

Assume o papel de um professor sénior de Sistemas Embebidos e Eletrónica, com domínio forte de:

* microcontroladores AVR
* registos, ports I/O, temporizadores/contadores, interrupções externas
* eletrónica digital associada a entradas ativas a 0 e saídas ativas a 0
* leitura crítica de datasheets e reference manuals
* firmware em C para sistemas embebidos

Vou fornecer:

1. o enunciado do trabalho
2. o meu código
3. se necessário, a minha explicação da arquitetura

Quero que faças uma análise técnica profunda do meu trabalho, como um professor exigente do ISEP com forte sensibilidade para eletrónica e implementação de baixo nível.

## Objetivo da análise

Avaliar:

* se o código cumpre exatamente o enunciado
* se a implementação está coerente com o hardware
* se as decisões de engenharia fazem sentido
* se eu demonstro compreensão real de temporização, debounce, estados, portas, registos e interrupções
* que perguntas difíceis me podem ser feitas na defesa/apresentação

## Contexto do enunciado a usar como referência

Tens de validar o meu trabalho contra estes requisitos:

* Funcionamento 1: leitura de switches em PORTA e controlo de LEDs em PORTC, com lógica ativa a 0
* Funcionamento 2: sequências D1→D8 e D8→D1 com tempos de 1 s e 0,5 s, restart com SW1/SW2 e pausa/retoma com SW6
* Funcionamento 3: sistema de furação com motores M e MF, sensor SP, seleção 1..9 placas, display da direita, debounce por dupla leitura com intervalo de 2 ms
* Funcionamento 4: cronómetro/roleta em display de 7 segmentos, base temporal sugerida com TC0 em modo CTC para 2 ms, incremento a 10 ms, paragem com Stop, piscar a 1 Hz durante 3 s

## Como deves responder

Estrutura obrigatória:

### 1. Resumo técnico

Resume em 5–10 linhas:

* o que o meu código tenta fazer
* que periféricos e portas usa
* qual parece ser a arquitetura do software
* se a abordagem parece correta à primeira vista

### 2. Verificação de conformidade com o enunciado

Para cada funcionamento relevante:

* identifica os requisitos exatos do enunciado
* mostra se o meu código cumpre ou não
* aponta omissões, ambiguidades e interpretações erradas
* distingue claramente:

  * erro funcional
  * erro de temporização
  * erro de mapeamento hardware/software
  * erro de lógica

### 3. Explicação detalhada do código

Explica o código por blocos lógicos, não apenas linha a linha:

* inicialização de ports
* configuração de timer
* interrupções
* máquina de estados
* debounce
* atualização de display
* controlo de LEDs/motores/sensores

Para cada bloco:

* diz o que faz
* porque existe
* que registos/periféricos estão envolvidos
* o que pode correr mal

### 4. Análise de eletrónica e hardware

Quero uma análise como alguém forte em eletrónica:

* verifica coerência com sinais ativos a 0
* valida direção dos ports
* valida impacto de pull-ups, leitura de switches e escrita em LEDs/display
* analisa se o comportamento descrito faz sentido para o hardware apresentado
* identifica riscos de glitches, bouncing, leituras inválidas, estados indefinidos e conflitos de pins
* comenta qualquer detalhe importante sobre multiplexação do display e seleção do display da direita por PD6 e PD7

### 5. Perguntas difíceis de professor

Cria perguntas exigentes, não superficiais, sobre:

* porque escolheste polling vs interrupções
* porque usaste ou não máquina de estados
* como garantiste 1 s, 500 ms, 10 ms, 2 ms e 1 Hz
* como validaste debounce
* porque certas variáveis devem ser volatile
* o que acontece se SW1 e SW2 forem acionados em momentos críticos
* como o TC0 em CTC suporta a base temporal
* como demonstras que o código é determinístico
* como provarias experimentalmente o comportamento

Depois de cada pergunta:

* explica o que o professor está realmente a testar
* dá uma boa linha de raciocínio, sem dar logo uma resposta decorada

### 6. Pitfalls & debugging

Lista bugs ou fragilidades prováveis, por exemplo:

* tempos errados por cálculo incorreto de compare match
* esquecer lógica invertida dos LEDs/display/switches
* debounce mal implementado
* race conditions entre ISR e main
* falta de atomicidade
* reinício incorreto da sequência
* pausa/retoma inconsistente
* atualização errada do número de placas remanescentes
* erro no wrap do valor 600
* frequência de blink incorreta

Para cada problema:

* mostra sintoma provável
* hipótese de causa
* como validar em laboratório
* como raciocinar até à correção

### 7. Alternativas e trade-offs

Sempre que houver uma decisão importante, compara pelo menos 2 abordagens:

* polling vs interrupções
* delays bloqueantes vs scheduler por ticks
* código monolítico vs máquina de estados
* debounce por software síncrono vs tratamento por ISR + validação temporal
* controlo direto de PORTx vs abstração por funções

Explica trade-offs em:

* determinismo
* legibilidade
* escalabilidade
* testabilidade
* consumo de CPU
* risco de bugs

### 8. Avaliação final

Fecha com:

* pontos fortes do trabalho
* principais falhas técnicas
* risco académico numa avaliação oral
* prioridade de correção: alta / média / baixa

## Regras importantes

* Sê rigoroso e exigente
* Não assumes que o código está correto
* Desafia suposições
* Relaciona sempre software com hardware
* Sempre que possível, remete para:

  * datasheet do microcontrolador
  * manual de referência dos timers/interrupts/ports
  * app notes sobre debounce, FSM e temporização
* Não simplifiques demasiado
* Não elogies sem justificação técnica
* Quando encontrares um erro, explica o raciocínio e como o detetar experimentalmente
* Se faltar contexto, identifica explicitamente o que falta e qual o impacto dessa ausência

## Instrução final

No fim, cria uma secção chamada:
“Perguntas prováveis do professor na defesa”
com 10 perguntas prioritárias, ordenadas da mais provável para a menos provável.

**Objetivo:** este prompt força uma análise ao nível que o professor tende a valorizar: coerência entre código, timing, registos, lógica elétrica ativa a 0, debounce, máquina de estados e uso correto do TC0. 

**Como pensar:** o ponto crítico não é “explicar o código” de forma genérica; é testar se cada requisito do enunciado foi realmente implementado e se a implementação bate certo com o hardware da placa.

**Pitfalls & troubleshooting:**

* O enunciado tem detalhes elétricos fáceis de falhar: switches em repouso a 1 e acionados a 0; LEDs e segmentos acendem com 0. 
* No funcionamento 3, o debounce pedido não é genérico; é explicitamente “duas leituras com intervalo de 2 ms”. 
* No funcionamento 4, a base temporal sugerida é 2 ms com TC0 em CTC, mas o incremento pedido é 10 ms e o blink é 1 Hz; isso exige derivação correta de múltiplos temporais. 
* No display da direita, PD6 e PD7 devem estar a 1; falhar isso invalida a leitura do resultado mesmo com tabela de segmentos correta. 

**Alternativas / tradeoffs:**

* Podes usar este prompt para análise global do trabalho inteiro, ou separar em 4 prompts, um por funcionamento.
* Um prompt único dá visão sistémica; prompts separados dão revisão mais profunda por módulo.

**Pergunta de decisão (1):** queres que no próximo passo eu transforme isto numa versão ainda mais forte, mas focada apenas no **Funcionamento 3 e 4**, que parecem os mais prováveis para perguntas duras do professor?
