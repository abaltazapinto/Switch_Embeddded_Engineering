ARP address Resolution Protocol

The address Resolution Protocol (ARP) is a comunication protocolol
for discovering the link layer address. The protocol, part of the
Internet protocol suite, was defined in 1982 by RFC 826, which is Internet Standard STD 37.

# ARP NAO FUNCIONA ENTRE REDES DIFERENTES

- ARP so resolve enderecos dentro da mesma rede local / mesmo dominio de broadcast. 

	Ideia central 

ARP responde a pergunta:

	" Qual e o endereco MAC do dispositivo que tem este IP na minha rede local ? "

Exemplo
	
	PC A: 192.168.1.10/24
	PC B: 192.168.1.20/24

Aqui o PCA pode fazer ARP para descobrir o MAC do PC B, porque ambos estao na mesma rede
192.168.1.0/24 .

# Objetivo

- Perceber fronteira entre: 

| Protocolo |      Camada | Função                        |
| --------- | ----------: | ----------------------------- |
| ARP       | entre L2/L3 | IP local → MAC                |
| IP        |          L3 | comunicação entre redes       |
| Router    |          L3 | encaminha pacotes entre redes |


# Como pensar

Quando uma maquina quer enviar para um IP, ela pergunta primeiro:

	O IP de destino esta na mesma rede ? 

- Caso 1 - destino na mesma rede.

	192.168.1.10/24 -> 192.168.1.20/24

A maquina faz:

	ARP: quem tem 192.168.1.20?

- Depois envia a frame Ethernet diretamente para o MAC do destino. 

---

- Caso 2 -- destino noutra rede

	192.168.1.10/24 -> 10.0.0.5/24

A maquina nao faz ARP pelo MAC de 10.0.0.5/24

Ela faz ARP pelo MAC do gateway/router:

	ARP: quem tem 192.168.1.1 ?

Depois envia a frame Ethernet para o router. 

O pacote IP continua com:

	IP origem: 192.168.1.10
	IP destino: 10.0.0.5

Mas a frame Ethernet local vai para:

	MAC destino: MAC do router


