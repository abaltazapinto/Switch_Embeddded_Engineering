![alt text](image.png)

    Q1. Num protocolo com ACK, qual afirmação é sempre verdadeira?

Eu escolhia a A - Se não há ACK, os dados não chegaram

mas era a B
b - Se há ACK, os dados chegaram corretamente
Regra correta:

ACK recebido → dados chegaram ✔️
ACK não recebido → incerteza, não conclusão

Conceito fraco:

semântica de ACK (continua crítico)

Aula: Aula 8

    Q2. O timeout deve ser

C - Ajustado ao atraso esperado da rede

    Q3. Qual destes não afeta diretamente o canal?

D - Escalonamento do CPU

    Q4. Num sistema com muitas retransmissões, qual pode ser a causa?

A-  Timeout demasiado curto

    Q5. Qual é a consequência de aumentar demasiado o timeout?

B - Maior latencia na deteccao de falhas

    Q6. Num sistema com sliding window, o que acontece se o canal piora?

B- O throughput pode cair devido a retransmissões

    Q7. Tens um sistema com perdas frequentes e decides aumentar taxa de transmissão. Resultado mais provável?

B- Mais interferência/erros → mais retransmissões

    Q8. Qual combinação é mais coerente num canal ruidoso?

C- Ignorar perdas + aumentar potência

    Q9. Num sistema IoT real:
    sensor envia dados
    canal com ruído variável
    uso de ACK + timeout

    Observas:

    muitas retransmissões
    mas o recetor mostra dados duplicados

    Qual explicação mais provável?

C- ACKs estão a perder-se, causando retransmissões de dados já recebidos