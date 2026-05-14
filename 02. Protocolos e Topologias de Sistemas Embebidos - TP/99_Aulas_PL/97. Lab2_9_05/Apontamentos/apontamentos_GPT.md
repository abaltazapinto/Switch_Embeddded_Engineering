# Pergunta 1 - Rotas por omissao do servidor stun

Preencher a rota default do no stun. 

1st:
	- o stun esta na rede publica 203.0.113.0/24
	- quem liga a rede exterior / internet e o gwi
	- Portanto o gateway default do stun deve ser o endereco do gwi nessa mesma rede. 

Na topologia:	
Nos enderecos configurados stun = 203.0.113.99 e os touters ra . tb estao tambem nessa rede publica. 

	# Objetivo

Compreender: 
- como um host escolhe o next-hop
- porque o gateway default tem de estar na mesma subnet/interface local
- diferenca entre:
	- rede diretmente ligada
	- trafego remoto

# Como Pensar 

	Se o stun quiser enviar trafego para 8.8.8.8 , para quem entrega primeiro o pacote ? 

- Nao entrega diretamente ao destino remoto
- Entrega ao router que conhece caminhos extrenos. 

Logo:
	- Destino = default
	- Gateway = IP do gwi na rede 203.0.113.0/24


Para ra e rb:

estão ligados à rede pública pela eth1
o next-hop público é o gwi
portanto: gateway 203.0.113.254, porta eth1


