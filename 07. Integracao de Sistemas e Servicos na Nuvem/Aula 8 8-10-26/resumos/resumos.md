# Aula 7 

O dispositivos de IoT tipicamente tem: 

	pouca RAM
	CPU limitado
	armazenamento limitado
	energia limitada
	comunicacoes frequentemente por radio

do ponto de vista energetico , o professor destacou dosi grandes consumidores

**CPU + radio**

logo, num sistema IoT queremos evitar processamentos desnecessario e transmitir o menor numero razoavel de bytes.

A rede tambems pode ser hostil: 

	> largura de banda reduzida;
	> latencia
	> qualidade variavel
	> interferencia
	> perda de pacotes
	> potencialmente muitos dispositivos

Porque HTTP pode ser inadequado ? 

O problema nao e que HTTP nao funcione.

E que e demasiado overhead relativamente a quantidade de informacao util..

Mentalmente : 

mensagem transmitida
┌─────────────────────┬───────────┐
│ metadata / headers  │ payload   │
└─────────────────────┴───────────┘
       overhead        dado útil

# 1.3 CoAP

O CoAP foi apresentado essecialmente como: 
	
	uma abordagem REST/request-response muito mais leve para dispositivos constrained. 

A analogia usada pelo professor foi bastante boa: e como retirar de um carro tudo o que nao e necessario.

# CoAP e UDP

A aula enftizou que CoAP normalmente usa UDP e evita uma ligacao TCP persistente. 

Consequencia: 

	sem TCP connect
	sem sessao TCP persistente
	menos estado
	menos overhead

e particularmente interessante para pedidos/respostas pequenos. 
O cenario ideal discutido foi algo que cabe aproximadamente num unico diagrama !!

---

Em protocolos onde pode haver retransmissoes, comandos idemportentes (SET ON , SET OFF ) sao muito seguros que comandos TOGGLE. 

# Aula 8 
# Fiware, Orion Context e Monitorizacao On-Premises

o Professor insistiu que o importante era compreender: 

	como representar, normalizar, manter e disponibilizar o estado atual de um sistema fisico heterogeneo. 
 
