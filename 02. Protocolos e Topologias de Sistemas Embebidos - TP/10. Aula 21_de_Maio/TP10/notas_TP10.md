TP10


Thought for 15s
TP10 — Pergunta 1 ✅
Ação — preencher a tabela TCP
Direção	Seq	Ack	Len
A -> B	203	232	151
B -> A	232	354	143
A -> B	354	375	93
B -> A	375	447	179
A -> B	447	554	0
A -> B	447	554	163
B -> A	554	610	180
A -> B	610	734	130
Objetivo

Perceber que em TCP:

Ack = próximo byte que espero receber do outro lado

e que:

próximo Seq = Seq atual + Len

⚠️ Se Len = 0, o número de sequência não avança.

Como pensar 🧠

Exemplo:

Primeira linha:

A -> B
Seq = 203
próximo Seq de A aparece depois como 354

Logo:

Len = 354 - 203 = 151

Outro exemplo:

B -> A
Seq = 232
Len = 143

Então A deve confirmar:

Ack = 232 + 143 = 375
Pitfalls
Ack não confirma a própria mensagem — confirma dados recebidos do outro lado.
Seq só avança com dados, isto é, com Len > 0.
Um pacote com Len = 0 é normalmente só ACK, logo mantém o mesmo Seq.
Não somar Ack + Len; o correto é Seq + Len.
Pergunta de decisão

Queres que façamos agora a Pergunta 2 do TP10 da mesma forma, com raciocínio TCP passo a passo?

ja estou perdido. estava a somar a Seq. com o akcnowledgement.. ahhh devo fazzer seq + len para o proximo passo ? ?  Nao sei que numros hei de por para seq.



Sim — para descobrir o próximo Seq do mesmo emissor, fazes:

próximo Seq desse emissor = Seq anterior desse emissor + Len anterior desse emissor

Mas cuidado: não somas Seq + Ack. O Ack pertence ao fluxo no sentido contrário.

Ação — pensa em duas linhas separadas

Mantém dois contadores mentais:

A envia com Seq: 203 → ...
B envia com Seq: 232 → ...

Agora atualizas cada lado só quando esse lado envia dados.

Fluxo A → B
Mensagem A → B	Seq	Len	Próximo Seq de A
1	203	151	203 + 151 = 354
2	354	93	354 + 93 = 447
3	447	0	447 + 0 = 447
4	447	163	447 + 163 = 610
5	610	130	610 + 130 = 740

Então os Seq que faltam em A são:

447
610
Fluxo B → A
Mensagem B → A	Seq	Len	Próximo Seq de B
1	232	143	232 + 143 = 375
2	375	179	375 + 179 = 554
3	554	180	554 + 180 = 734

Então o Seq que falta em B é:

375
Para preencher agora

Na tua tabela:

B -> A    Seq = 375
A -> B    Seq = 447
A -> B    Seq = 610

E o Ack em branco da linha:

A -> B    Seq 447    Ack = 554    Len 163

porque A já recebeu de B até:

375 + 179 = 554
Objetivo

Separar TCP em dois fluxos independentes:

Seq de A só depende dos dados enviados por A.
Seq de B só depende dos dados enviados por B.
Ack de A confirma dados recebidos de B.
Ack de B confirma dados recebidos de A.
Pitfalls
Nunca usar Seq + Ack.
Não misturar o contador de A com o contador de B.
Len = 0 mantém o mesmo Seq.
O Ack aponta para o próximo byte esperado, não para o último recebido.
Pergunta de decisão

Queres que eu valide contigo só os campos que ainda faltam antes de carregares em Página seguinte?

certo ? 

Quase tudo certo ✅

Só tens 1 campo errado:

B -> A   Seq 554   Ack 610   Len = 180

Tu puseste 55, mas o correto é 180.

Ação — corrige só este campo

Na linha:

B -> A   554   610   [ 55 ]

substitui por:

180
Objetivo

Esse Len vem do próximo Ack de A:

Ack final de A = 734
Seq de B atual = 554

Logo:

Len de B = 734 - 554 = 180
Tabela final correta
Direção	Seq	Ack	Len
A -> B	203	232	151
B -> A	232	375	143
A -> B	354	375	93
B -> A	375	447	179
A -> B	447	554	0
A -> B	447	554	163
B -> A	554	610	180
A -> B	610	734	130

Depois disso podes avançar para Página seguinte.